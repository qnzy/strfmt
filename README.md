# strfmt
This library provides a tiny string formatting function `strfmt` for C. It is
basically a (very limited) `snprintf` replacement intended for embedded applications
with very limited space. 

This is a header only library. To use it you have to define `STRFMT_IMPLEMENTATION` in 
exactly one file including the header (before the `#include`). The header can be included
in other files without the definition. 

The function `vstrfmt` is the corresponding `vsnprintf` replacement.

`const char * strfmt(char* buf, const size_t buflen, const char* format, ...)`

`const char * vstrfmt(char* buf, const size_t bufLen, const char* format, va_list argp)`

Differences to snprintf:
* only `%s` (for strings) and `%x` (for unsigned int, printed as hex) are supported, no flags/precision/aligning
* use `%%` to print a percent sign
* instead of the number of characters written the function returns a pointer to the buffer, allowing to use it directly in a function call (`log(strfmt(...))`)

The buffer will always be null terminated (unless buf is NULL or bufLen is 0 in which case NULL is returned).

See the test.c file for example code.

For a more full-featured (and a bit larger) printf/snprintf implementation see [here](https://github.com/mpaland/printf).

Public Domain / CC0
