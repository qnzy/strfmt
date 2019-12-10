#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#define STRFMT_ADD_CHAR(c) if(bufptr<bufLen-1){buf[bufptr++]=c;}else{buf[bufLen-1]='\0';return buf;}

const char * strfmt(char* buf, size_t bufLen, const char* format, ...) {
    bool inSpecifier = false;
    va_list argp;
    va_start(argp, format);
    unsigned int bufptr = 0;
    while(*format != '\0') {
        if (inSpecifier == true) {
            if (*format == 'x') {
                unsigned int num = va_arg(argp, unsigned int);
                unsigned int nibblesCount = 0;
                while((1<<(4*nibblesCount))<num) nibblesCount++;
//                unsigned int temp = num;
//                while (temp > 0) {
//                    temp = temp >> 4;
//                    nibblesCount++;
//                }
                for (int i = 0; i < nibblesCount; i++) {
                    STRFMT_ADD_CHAR("0123456789abcdef"[(num >> (4 * (nibblesCount - i - 1))) & 0xf]);
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
    va_end(argp);
    if (bufptr < bufLen - 1) {
        buf[bufptr++]='\0';
    }
    buf[bufLen-1] = '\0';
    return buf;
}

#undef STRFMT_ADD_CHAR
