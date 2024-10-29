#ifndef __ONLINEGAME_GS_BASE_WRAPPER_H__
#define __ONLINEGAME_GS_BASE_WRAPPER_H__

#include "types.h"
#include "ASSERT.h"

inline unsigned short byteorder_16(unsigned short _Val)
{
	return (((_Val << 8) | (_Val >> 8)));
}
inline unsigned int byteorder_32(unsigned int _Val)
{
	return ((_Val << 24) | ((_Val << 8) & 0x00FF'0000) | ((_Val >> 8) & 0x0000'FF00) | (_Val >> 24));
}
inline unsigned long long byteorder_64(unsigned long long _Val)
{
	return ((_Val << 56) | ((_Val << 40) & 0x00FF'0000'0000'0000) | ((_Val << 24) & 0x0000'FF00'0000'0000) 
			| ((_Val << 8) & 0x0000'00FF'0000'0000) | ((_Val >> 8) & 0x0000'0000'FF00'0000) 
			| ((_Val >> 24) & 0x0000'0000'00FF'0000) | ((_Val >> 40) & 0x0000'0000'0000'FF00) | (_Val >> 56));
}

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
	virtual base_wrapper & operator<<(long val) = 0;
	virtual base_wrapper & operator<<(unsigned long val) = 0;
	virtual base_wrapper & operator<<(long long val) = 0;
	virtual base_wrapper & operator<<(unsigned long long val) = 0;
	virtual base_wrapper & operator<<(float val) = 0;
	virtual base_wrapper & operator<<(double val) = 0;
	virtual base_wrapper & operator<<(const A3DVECTOR & vec) = 0;
	virtual base_wrapper & operator<<(const char * str) = 0;
	virtual base_wrapper & push_back(const void * buf,size_t size) = 0;

	inline base_wrapper &operator <<(const bool val)
	{
		return operator<< ((char)val);
	}
	inline base_wrapper &operator >>(bool &val)
	{
		ASSERT(sizeof(char) == sizeof(bool));
		return operator>>((char&)val);
	}

	virtual base_wrapper & operator>>(int &val) = 0;
	virtual base_wrapper & operator>>(unsigned int &val) = 0;
	virtual base_wrapper & operator>>(short &val) = 0;
	virtual base_wrapper & operator>>(unsigned short &val) = 0;
	virtual base_wrapper & operator>>(char &val) = 0;
	virtual base_wrapper & operator>>(unsigned char &val) = 0;
	virtual base_wrapper & operator>>(long &val) = 0;
	virtual base_wrapper & operator>>(unsigned long &val) = 0;
	virtual base_wrapper & operator>>(long long &val) = 0;
	virtual base_wrapper & operator>>(unsigned long long &val) = 0;	
	virtual base_wrapper & operator>>(float &val) = 0;
	virtual base_wrapper & operator>>(double &val) = 0;
	virtual base_wrapper & operator>>(A3DVECTOR & vec) = 0;
	virtual base_wrapper & get_string(char * buf,size_t size) = 0;
	virtual base_wrapper & pop_back(void * buf,size_t size) = 0;

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
