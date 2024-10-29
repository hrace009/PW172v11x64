#ifndef __ONLINEGAME_GS_BASE_WRAPPER_H__
#define __ONLINEGAME_GS_BASE_WRAPPER_H__

#include <assert.h>
#include "types.h"
class base_wrapper
{
public:
	virtual ~base_wrapper(){}
	virtual base_wrapper & operator<<(int val) = 0;
	virtual base_wrapper & operator<<(unsigned int val) = 0;
	virtual base_wrapper & operator<<(short val) = 0;
	virtual base_wrapper & operator<<(unsigned short val) = 0;
	virtual base_wrapper & operator<<(char val) = 0;
	virtual base_wrapper & operator<<(unsigned char val) = 0;
	virtual base_wrapper & operator<<(int64_t val) = 0;
	virtual base_wrapper & operator<<(uint64_t val) = 0;
	virtual base_wrapper & operator<<(float val) = 0;
	virtual base_wrapper & operator<<(const A3DVECTOR & vec) = 0;
	virtual base_wrapper & operator<<(const char * str) = 0;
//	virtual base_wrapper & operator<<(const abase::octets& buf) = 0;
	virtual base_wrapper & push_back(const void * buf,size_t size) = 0;

	inline base_wrapper &operator <<(const bool val)
	{
		return operator<< ((char)val);
	}
	inline base_wrapper &operator >>(bool &val)
	{
		assert(sizeof(char) == sizeof(bool));
		return operator>>((char&)val);
	}

	virtual base_wrapper & operator>>(int &val) = 0;
	virtual base_wrapper & operator>>(unsigned int &val) = 0;
	virtual base_wrapper & operator>>(short &val) = 0;
	virtual base_wrapper & operator>>(unsigned short &val) = 0;
	virtual base_wrapper & operator>>(char &val) = 0;
	virtual base_wrapper & operator>>(unsigned char &val) = 0;
	virtual base_wrapper & operator>>(int64_t &val) = 0;
	virtual base_wrapper & operator>>(uint64_t &val) = 0;
	virtual base_wrapper & operator>>(float &val) = 0;
	virtual base_wrapper & operator>>(A3DVECTOR & vec) = 0;
	virtual base_wrapper & get_string(char * buf,size_t size) = 0;
	virtual base_wrapper & pop_back(void * buf,size_t size) = 0;

//	virtual abase::octets & get_buf() = 0;
	virtual void * data() = 0;
	virtual void * cur_data() = 0;
	virtual size_t size() = 0;
	virtual void clear() = 0;
	virtual size_t offset() = 0;
	virtual bool is_eof() = 0;
	virtual bool shift(int offset) = 0;
};
typedef base_wrapper archive;

#endif
