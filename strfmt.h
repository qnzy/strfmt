/* 
 * strfmt: tiny header only string formatting library
 * public domain / CC0
 *
 * this is a header only library. to use it you need
 * to define STRFMT_IMPLEMENTATION in exactly one
 * compilation unit before including this file.
 */

#pragma once

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__GNUC__) || defined(__clang__)
    #define STRFMT_ATTR __attribute__((format(printf, 3, 4)))
    #define VSTRFMT_ATTR __attribute__((format(printf, 3, 0)))
#else
    #define STRFMT_ATTR 
    #define VSTRFMT_ATTR
#endif


const char * strfmt(char* buf, size_t bufLen, const char* format, ...) STRFMT_ATTR;
const char * vstrfmt(char* buf, size_t bufLen, const char* format, va_list argp) VSTRFMT_ATTR;


#undef STRFMT_ATTR
#undef VSTRFMT_ATTR

/* --------------- Implementation --------------- */

#ifdef STRFMT_IMPLEMENTATION

#define STRFMT_ADD_CHAR(c) if(bufptr<bufLen-1){buf[bufptr++]=c;}else{buf[bufLen-1]='\0';return buf;}
const char * vstrfmt(char* buf, const size_t bufLen, const char* format, va_list argp) {
    bool inSpecifier = false;
    unsigned int bufptr = 0;
    if (buf == NULL || bufLen == 0) {
        return NULL;
    }
    if (format == NULL) {
        buf[0] = '\0';
        return buf;
    }
    while(*format != '\0') {
        if (inSpecifier) {
            if (*format == 'x') {
                const unsigned int num = va_arg(argp, unsigned int);
                unsigned int nibblesCount = 0;
                while((1U << (4 * nibblesCount)) <= num) {
                    nibblesCount++;
                    if ((1U << (4 * nibblesCount)) > UINT_MAX >> 4U) {
                        nibblesCount++;
                        break;
                    }
                }
                if (nibblesCount == 0) {
                    STRFMT_ADD_CHAR('0');
                } else {
                    unsigned int i = 0;
                    for (i = 0; i < nibblesCount; i++) {
                        STRFMT_ADD_CHAR("0123456789abcdef"
                                [(num >> (4 * (nibblesCount - i - 1))) & 0xfU]);
                    }
                }
            } else if (*format == 's') {
                char * strptr = va_arg(argp, char*);
                if (strptr != NULL) {
                    while (*strptr != '\0') {
                        STRFMT_ADD_CHAR(*strptr++);
                    }
                }
            } else if (*format == '%') {
                STRFMT_ADD_CHAR('%');
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
    const char* retval = NULL;
    va_start(argp, format);
    retval = vstrfmt(buf, bufLen, format, argp);
    va_end(argp);
    return retval;
}

#endif
