# SSFMT
(**S**imple **S**tring **F**or**m**a**t**) is an syntax of format and a library for parse this.

# SSFMT != \{fmt\}
SSFMT is **NOT** an API/library for parse [{fmt}](https://fmt.dev/latest/index.html) syntax !

# Syntax
The syntax of SSFTM is very simple, its use braces `{` `}` for "declare" a format, and an `identifier` inside the braces block for identifie the format.

Example: `{name}` *(is a format with "name" like indentifier)*

> You can escape braces with backslash `\` for do not consider the followed braces like an format but like a braces.

> Example: `\{name\}` *(Here, "name" will not be interpreted like as format)*

An identifier have a limit of `255` charaters. If an identifer len greater than this limit, only the first `255` char are compared.

A identifier can be represented with any of  ascii table characters, but its better to use only alphabet `[a-z]+`upper/lower, digits `[0-9]+` and underscore `_`.

# Download
`git clone https://github.com/ownesis/ssfmt.git`

# Compile the library
`cd ssfmt/`

`mkdir build && cd build/`

`cmake .. && make`

# Install library in system
*as root*

`make install`
> This copies:

> - Header file `ssfmt.h` inside `/usr/local/include`.
- Shared object library `libssfmt.so` inside `/usr/local/lib`.
- Static object library `libssfmt.a` inside `/usr/local/lib`.

# Library Documentation

## The dictionnary
To change a format with its value, you must specify a "dictionnary" with identifier/value correspondence.

The "dictionnary" is a structure with two `char *` fields (for the identifier and its value).

```c
struct Dict {
    char *identifier;
    char *value;
};
```

## The context
Now, for specify this array of "dictionnary", you must to set it to a context structure: `ssfmt_ctx_t (struct SSFMT_ctx)`.

```c
struct SSFMT_ctx {
	struct Dict *array;
	size_t array_len;
	_Bool case_sensitibe;
};
```

This context structure take `3` fields:

  - `array`: (struct Dict \*), *This pointer take address of the array of Dict structure*.
  - `array_len`: (size\_t), *This object take len of* `array`.
  - `case_sensitive`: (\_Bool), *If set to `1` the identifer will become case sensitive; If set to `0` the identifer will become not case sensitive*.

The library propose a macro function for init a context:
```c
#define SSFMT_INIT(a, l, c) \
    { .array = (a), .array_len = (l), .case_sensitve = (c) }
```

- `a`: is the array.
- `l`: is the len of array.
- `c`: (`1` or `0`) its for enable (`1`) or not (`0`), the case sensitive of identifiers. 

Example of use: 
```c
ssfm_ctx_t ctx = SSFMT_INIT(the_dict_array, 5, 0);
```

## The parser function
For parsing and get a string with the identifier replaced with its value, you must to call a function for do this.

```c
char *ssfmt_parser(const ssfmt_ctx_t *ctx, const char *format, char *buf, size_t buf_len);
```

This function take `4` arguments:

- `ctx`: (const ssfmt\_ctx\_t \*), is a **input** argument, *is take address of the initialized*`struct SSFMT_ctx`.
- `format`: (const char \*), is a **input** argument, *is a null terminated string with formats to replace*.
- `buf`: (char *buf), is a **output** argument, *is take address of a buffer will store the result of the formatted character string* `format`.
- `buf_len`: (size\_t): is a **input** argument, *is the size of the buffer* `buf`.

The return value is the address of `buf` or `NULL` if an error occured.

### Note
if a format is used with a unknown identifier (a identifer not in dictionnary array), it's just been ignored and will be removed of the result string. 

If the length result formatted string is greater than `buf_size`, the `buf` will have the result of the formats that  have been formatted and a finished with a null byte `'\0'`.

# Example usage
## code
```c
#include <stdio.h>
#include <ssfmt.h>

#define ARRAY_SIZE 4
#define BUF_SIZE  1024 

#define FORMAT "{lastname} {firstname}:\n - Planet: {planet} ({dimension})"

int main(void) {
	char buf[BUF_SIZE] = {0};
	struct Dict array[ARRAY_SIZE] = {
		[0] = {
			.identifier = "firstname",
			.value = "Rick"	
		},

		[1] = {
			.identifier = "lastname",
			.value = "Sanchez"
		},

		[2] = {
			.identifier = "dimension",
			.value = "C-137"	
		},

		[3] = {
			.identifier = "planet",
			.value = "Earth"	
		}
	};

	ssfmt_ctx_t ctx = SSFMT_INIT(array, ARRAY_SIZE, 1);

	ssfmt_parser(&ctx, FORMAT, buf, BUF_SIZE);

	puts(buf);

	return 0;
}
```

## compiling
`gcc -o example example_code.c -I/usr/local/include/ -L/usr/local/lib -lssfmt`