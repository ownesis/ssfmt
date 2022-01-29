#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "braces_parser.h"

static char *_string_upper(char *s) {
    for (; *s; *s++)
        *s = toupper(*s);

    return s;
}

static char *_to_upper_if_case_sensitive(_Bool casse, char *identifier) {
    if (casse)
        return _string_upper(identifier);

    return identifier;
}

static char *_get_val_of_id(const braces_ctx_t *ctx, char *identifier, int *res) {
    char *_array_identifer = NULL;

    /* if not ctx or array or if the len is lower or equal to 0, set res to -1 and return NULL */
    if (!ctx || !ctx->array || ctx->array_len <= 0) {
        *res = -1;
        return NULL;
    }
    
    for (size_t i = 0; i < ctx->array_len; i++) {
        /* duplicate the identifier for not change the default identifier */
        _array_identifer = strdup(ctx->array[i].identifier);
        
        /* if case sensitive is set, turn both identifier to upper */
        _to_upper_if_case_sensitive(ctx->case_sensitve, identifier);
        _to_upper_if_case_sensitive(ctx->case_sensitve, _array_identifer);

        /* if identifier match, return the attributed value */
        if (strncmp(identifier, _array_identifer, BP_MAX_KEY_LEN) == 0) {
            free(_array_identifer);
            return ctx->array[i].value;
        }

        free(_array_identifer);
    }

    /* no identifier matched but is not an error, return NULL with res to 0 */
    *res = 0;
    return NULL;
}

char *braces_parser(const braces_ctx_t *ctx, const char *format, char *buf, size_t buf_len) {
    char *value = NULL;
    char key[BP_MAX_KEY_LEN+1] = {0};
    size_t key_index = 0;
    size_t buf_index = 0;
    size_t format_len = 0;
    int i = 0;
    int res = -1;

    if (!buf || !format || !ctx || buf_len <= 0)
        return NULL;

    format_len = strlen(format);

    for (; i < format_len && buf_index < buf_len;) {
        memset(key, 0, BP_MAX_KEY_LEN);
        key_index = 0;

        if (format[i] == '{') {
            /* if escaped brace */
            if (i > 0 && format[i-1] == '\\') {
                /* erase backslash with brace */
                buf[buf_index-1] = format[i++];

            /* if not escaped brace */
            } else {
                i++;

                while (format[i] != '}') {
                    if (key_index == buf_len)
                        return buf;

                    key[key_index++] = format[i++];
                }
               
                i++; 

                value = _get_val_of_id(ctx, key, &res);

                /* key/identifier found */
                if (value) {
                    strcat(buf, value);
                    buf_index += strlen(value);

                /* key/identifier not found but no error */
                } else if (!value && res == 0){
                    strcat(buf, "");

                /* something wrong */
                } else {
                    return NULL;
                }
            }
        } else {
            buf[buf_index++] = format[i++];
        }
        
        if (format[i] == '}' && format[i-1] == '\\') {
            /* replace backslash with brace */
            buf_index--;
        }
    }

    return buf;
}
