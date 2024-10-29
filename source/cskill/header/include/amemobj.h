#ifndef __CMLIB_MEM_OBJECT_H__
#define __CMLIB_MEM_OBJECT_H__

#include <stdlib.h>
namespace abase
{
class ASmallObject
{
public:
	void * operator new(size_t size);
	void operator delete(void * p, size_t size);
};

void RecordMemAlloc(const void * ,size_t);
void RecordMemFree(const void * ,size_t);
}
#endif
