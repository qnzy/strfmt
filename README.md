# strfmt
This library provides a tiny string formatting function for C. It is intended to be 
used in memory limited situations, mainly embedded.

const char * strfmt(char* buf, size_t bufLen, const char* format, ...)

* The strfmt format string understands only two format specifiers: 
  * %s for strings
  * %x for unsigned ints, printed as hex values
* The buffersize is given with the bufLen parameter, the buffer is guaranteed to be NULL terminated
* buf is also returned, allowing to do log(strfmt(...))
