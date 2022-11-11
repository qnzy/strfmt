#include <limits.h>
#include <stdio.h>
#include <string.h>
#define STRFMT_IMPLEMENTATION
#include "strfmt.h"

#define TEXT_RED printf("\033[0;31m")
#define TEXT_GREEN printf("\033[0;32m")
#define TEXT_RESET printf("\033[0m")
#define CHECKSTR(s1,s2,msg) if(strcmp(s1,s2) != 0){TEXT_RED;printf("Test failed: %s (%s != %s) (%s:%u)\n", msg, s1, s2,__FILE__,__LINE__);TEXT_RESET;}\
                         else{TEXT_GREEN;printf("Test passed: %s (%s == %s)\n", msg, s1, s2);TEXT_RESET;}
#define CHECKCOND(cond,msg) if(!(cond)){TEXT_RED;printf("Test failed: %s (%s:%u)\n", msg,__FILE__,__LINE__);TEXT_RESET;}\
                         else{TEXT_GREEN;printf("Test passed: %s\n", msg);TEXT_RESET;}

int main(void) {
    char buf[100];
    CHECKSTR("not", "equal", "intentionally failing CHECKSTR");
    CHECKCOND(1==0, "intentionally failing CHECKCOND");
    CHECKSTR(strfmt(buf, 10, "0123456789abcdef"), "012345678", "limit buffer, no format");
    CHECKSTR(strfmt(buf, 10, "%s", "0123456789abcdef"), "012345678", "limit buffer, string arg");
    CHECKSTR(strfmt(buf, 10, "01234567%x", 0xc0de), "01234567c", "limit buffer, hex arg");
    CHECKSTR(strfmt(buf, 100, "_%x_", 0), "_0_", "hex zero");
    CHECKSTR(strfmt(buf, 100, "_%x_", 1), "_1_", "hex one");
    CHECKSTR(strfmt(buf, 100, "_%x_", 2), "_2_", "hex two");
    CHECKSTR(strfmt(buf, 100, "_%x_", 3), "_3_", "hex three");
    CHECKSTR(strfmt(buf, 100, "_%x_", 4), "_4_", "hex four");
    CHECKSTR(strfmt(buf, 100, "_%x_", 5), "_5_", "hex five");
    CHECKSTR(strfmt(buf, 100, "_%x_", 15), "_f_", "hex fifteen");
    CHECKSTR(strfmt(buf, 100, "_%x_", 16), "_10_", "hex sixteen");
    CHECKSTR(strfmt(buf, 100, "_%x_", 17), "_11_", "hex seventeen");
    CHECKSTR(strfmt(buf, 100, "_%x_", -1), "_ffffffff_", "hex minus one");
    CHECKSTR(strfmt(buf, 100, "%s%x%s%x", "one",2,"three",4), "one2three4", "multiple mixed args");
    CHECKSTR(strfmt(buf, 100, ""), "", "empty format string");
    CHECKSTR(strfmt(buf, 100, NULL), "", "NULL format string");
    CHECKCOND(strfmt(NULL, 100, "") == NULL, "NULL buffer");
    CHECKCOND(strfmt(buf, 0, "") == NULL, "bufLen zero");
    CHECKSTR(strfmt(buf, 1, "test"), "", "buflen one");
    CHECKSTR(strfmt(buf, 2, "test"), "t", "buflen two");
    CHECKSTR(strfmt(buf, 2, "%"), "", "buflen two, only %");
    CHECKSTR(strfmt(buf, 2, "%%"), "%", "buflen two, only %%");
    CHECKSTR(strfmt(buf, 100, "%s", NULL), "", "string argument NULL");
    CHECKSTR(strfmt(buf, 100, "10%% or %x%%", 5), "10% or 5%", "quoting percent sign");
    CHECKSTR(strfmt(buf, 100, "_% %"), "_", "lonely percent sign");
    CHECKSTR(strfmt(buf, 2, "_%x_", 0), "_", "hex zero limit buffer");
    CHECKSTR(strfmt(buf, 3, "10%%"), "10", "quoting percent sign, limit buffer");
    CHECKSTR(strfmt(buf, 10, "012345678"), "012345678", "limit buffer, no format");
    return 0;
}
