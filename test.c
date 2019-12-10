#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "strfmt.h"

#define CHECK(s1,s2,msg) if(strcmp(s1,s2)){printf("Test failed: %s (%s != %s) (%s:%u)\n", msg, s1, s2,__FILE__,__LINE__);}\
                         else{printf("Test passed: %s (%s == %s)\n", msg, s1, s2);}

int main(void) {
    char buf[100];
    CHECK(strfmt(buf, 10, "0123456789abcdef"), "012345678", "limit buffer, no format");
    CHECK(strfmt(buf, 10, "%s", "0123456789abcdef"), "012345678", "limit buffer, string arg");
    CHECK(strfmt(buf, 10, "01234567%x", 0xc0de), "01234567c", "limit buffer, hex arg");
    CHECK(strfmt(buf, 100, "_%x_", 0), "_0_", "hex zero");
    CHECK(strfmt(buf, 100, "_%x_", 1), "_1_", "hex one");
    CHECK(strfmt(buf, 100, "_%x_", 2), "_2_", "hex two");
    CHECK(strfmt(buf, 100, "_%x_", 3), "_3_", "hex three");
    CHECK(strfmt(buf, 100, "_%x_", 4), "_4_", "hex four");
    CHECK(strfmt(buf, 100, "_%x_", 5), "_5_", "hex five");
    CHECK(strfmt(buf, 100, "_%x_", 15), "_f_", "hex fifteen");
    CHECK(strfmt(buf, 100, "_%x_", 16), "_10_", "hex sixteen");
    CHECK(strfmt(buf, 100, "_%x_", 17), "_11_", "hex seventeen");
    CHECK(strfmt(buf, 100, "_%x_", -1), "_ffffffff_", "hex minus one");
    CHECK(strfmt(buf, 100, "%s%x%s%x", "one",2,"three",4), "one2three4", "multiple mixed args");
}
