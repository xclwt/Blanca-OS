#ifndef _INC_VSPRINT_H
#define _INC_VSPRINT_H

typedef char* va_list

#define _times_of_int(TYPE) ((sizeof(TYPE) + sizeof(int) - 1) / sizeof(int)) * sizeof(int)

#define va_start(AP, LAST_ARG) (AP = (char*)(&LAST_ARG) + _times_of_int(LAST_ARG))
#define va_arg(AP, TYPE) (*(TYPE*)((AP += _times_of_int(TYPE)) - _times_of_int(TYPE)))
#define va_end(AP) (AP = 0)

#endif
