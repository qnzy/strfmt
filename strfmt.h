#pragma once

const char * strfmt(char* buf, const size_t buflen, const char* format, ...);
const char * vstrfmt(char* buf, const size_t bufLen, const char* format, va_list argp);
