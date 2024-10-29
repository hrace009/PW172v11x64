#ifndef __ONLINEGAME_GS_DBGPRT_H__
#define __ONLINEGAME_GS_DBGPRT_H__

#include <stdio.h>

extern bool __PRINT_FLAG;
extern bool __PRINT_INFO_FLAG;

inline void __SETPRTFLAG(bool flag)
{
	__PRINT_FLAG  = flag;
}

inline void __SETPRTFFLAG_INFO(bool flag)
{
	__PRINT_INFO_FLAG = flag;
}

#ifdef __NO_STD_OUTPUT__
inline int __PRINTF(const char * fmt, ...)
{
	return 0;
}

inline int __PRINTINFO(const char * fmt, ...)
{
	return 0;
}
#else
#include <stdarg.h>
inline int __PRINTF(const char * fmt, ...)
{
	if(!__PRINT_FLAG) return 0;
	va_list ap;
	va_start(ap, fmt);
	int rst = vprintf(fmt, ap);
	va_end(ap);
	return rst;
}

inline int __PRINTINFO(const char * fmt, ...)
{
	if(!__PRINT_INFO_FLAG) return 0;
	va_list ap;
	va_start(ap, fmt);
	int rst = vprintf(fmt, ap);
	va_end(ap);
	return rst;
}

#endif

#endif

