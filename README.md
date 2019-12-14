# strfmt
This library provides a tiny string formatting function `strfmt` for C. It is
basically a (very limited) `snprintf` replacement intended for embedded applications
with very limited space. 

The function `vstrfmt` is the corresponding `vsnprintf` replacement.

`const char * strfmt(char* buf, const size_t buflen, const char* format, ...)`

`const char * vstrfmt(char* buf, const size_t bufLen, const char* format, va_list argp);`

Differences to snprintf:
* only `%s` (for strings) and `%x` (for unsigned int, printed as hex) are supported, no flags/precision/aligning
* all other `%` are printed directly, so don't quote `%`
* instead of the number of characters written the function returns a pointer to the buffer, allowing to use it directly in a function call (`log(strfmt(...))`)
* the buffer will always be null terminated (unless buf or bufLen are 0)

See the test.c file for example code.

For a more full-featured (and a bit larger) printf/snprintf implementation see [here](https://github.com/mpaland/printf).
