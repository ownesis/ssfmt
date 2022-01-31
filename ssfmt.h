#ifndef __SIMPLE_STRING_FORMAT_H__
#define __SIMPLE_STRING_FORMAT_H__

#include <stddef.h>

#define BP_MAX_KEY_LEN 255

#define SSFMT_INIT(a, l, c) \
    { .array = (a), .array_len = (l), .case_sensitve = (c) }

/**
 * @struct SSFMTDict
 * @brief Struct used for make correspondance between identifiers and their values.
 */
struct SSFMTDict {
    char *identifier; /**< The identifier to match */
    char *value; /**< The value of identifier */
};

/**
 * @struct SSFMT_ctx
 * @brief Contextuel structure for `ssfmt_parser` function.
 */
struct SSFMT_ctx {
    struct SSFMTDict *array; /**< An array of `strcut Dict` used for replace the identifier of a format. */
    size_t array_len; /**< Size of the `array`? */
    _Bool case_sensitve; /**< set to 1 if want to make identifier case sensitive; set 0 for not. */
};

typedef struct SSFMT_ctx ssfmt_ctx_t;

/**
 * @fn char *ssfmt_parser(const ssfmt_ctx_t *ctx, const char *format, char *buf, size_t buf_len)
 * @brief This function produce output according to the format `format`.
 *  An format is represented with braces `{` `}` and an identifier inside the block of braces: `{identifier}`.
 *  An identifier have a limit of 255 characters (without null byte '\0'), if an identifier are greater than 255 character, only the first 255 char are compared.
 *
 * @param[in] ctx Address of an initilalized ssfmt_ctx_t structure.
 * @param[in] format const String with format.
 * @param[out] buf Address of a char buffer will store the result of the formatted character string.
 * @param[in] buf_len Len of the buffer `buf`.
 * @return NULL if error occured or address of `buf`.
 */
char *ssfmt_parser(const ssfmt_ctx_t *ctx, const char *format, char *buf, size_t buf_len);

#endif /* __SIMPLE_STRING_FORMAT_H__ */
