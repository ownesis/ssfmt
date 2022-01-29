#ifndef __BRACES_PARSER_H__
#define __BRACES_PARSER_H__

#include <stddef.h>

#define BP_MAX_KEY_LEN 255

/**
 * @struct Dict
 * @brief Struct used for make correspondance between identifiers and their values.
 */
struct Dict {
    char *identifier; /**< The identifier to match */
    char *value; /**< The value of identifier */
};

/**
 * @struct Braces_parser_ctx
 * @brief Contextuel structure for `braces_parser` function.
 */
struct Braces_parser_ctx {
    struct Dict *array; /**< An array of `strcut Dict` used for replace the identifier of a format. */
    size_t array_len; /**< Size of the `array`? */
    _Bool case_sensitve; /**< set to 1 if want to make identifier case sensitive; set 0 for not. */
};

typedef struct Braces_parser_ctx braces_ctx_t;

/**
 * @fn char *braces_parser(const braces_ctx_t *ctx, const char *format, char *buf, size_t buf_len)
 * @brief This function produce output according to the format `format`.
 *  An format is represented with braces `{` `}` and an identifier inside the block of braces: `{identifier}`.
 *  An identifier have a limit of 255 characters (without null byte '\0'), if an identifier are greater than 255 character, only the first 255 char are compared.
 *
 * @param[in] ctx Address of an initilalized braces_ctx_t structure.
 * @param[in] format const String with format.
 * @param[out] buf Address of a char buffer will store the result of the formatted character string.
 * @param[in] buf_len Len of the buffer `buf`.
 * @return NULL if error occured or address of `buf`.
 */
char *braces_parser(const braces_ctx_t *ctx, const char *format, char *buf, size_t buf_len);

#endif /* __BRACES_PARSER_H__ */
