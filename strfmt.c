/*
 * strfmt: tiny string formatting
 * yves kunz 2019
 * Public Domain / CC0
 * */
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#define STRFMT_ADD_CHAR(c) if(bufptr<bufLen-1){buf[bufptr++]=c;}else{buf[bufLen-1]='\0';return buf;}
const char * vstrfmt(char* buf, const size_t bufLen, const char* format, va_list argp) {
    if (buf == NULL || bufLen == 0) {
        return NULL;
    }
    if (format == NULL) {
        buf[0] = '\0';
        return buf;
    }
    bool inSpecifier = false;
    unsigned int bufptr = 0;
    while(*format != '\0') {
        if (inSpecifier) {
            if (*format == 'x') {
                unsigned int num = va_arg(argp, unsigned int);
                unsigned int nibblesCount = 0;
                while((1 << (4 * nibblesCount)) <= num) {
                    nibblesCount++;
                    if ((1 << (4 * nibblesCount)) > UINT_MAX >> 4) {
                        nibblesCount++;
                        break;
                    }
                }
                if (nibblesCount == 0) {
                    STRFMT_ADD_CHAR('0');
                } else {
                    for (int i = 0; i < nibblesCount; i++) {
                        STRFMT_ADD_CHAR("0123456789abcdef"
                                [(num >> (4 * (nibblesCount - i - 1))) & 0xf]);
                    }
                }
            } else if (*format == 's') {
                char * strptr = va_arg(argp, char*);
                while (*strptr != '\0') {
                    STRFMT_ADD_CHAR(*strptr++);
                }
            } else {
                STRFMT_ADD_CHAR('%');
                STRFMT_ADD_CHAR(*format);
            }
            inSpecifier = false;
        } else if (*format == '%') {
            inSpecifier = true;
        } else {
            STRFMT_ADD_CHAR(*format);
        }
        ++format;
    }
    STRFMT_ADD_CHAR('\0');
    return buf;
}

#undef STRFMT_ADD_CHAR

const char * strfmt(char* buf, const size_t bufLen, const char* format, ...) {
    va_list argp;
    va_start(argp, format);
    const char* retval = vstrfmt(buf, bufLen, format, argp);
    va_end(argp);
    return retval;
}
