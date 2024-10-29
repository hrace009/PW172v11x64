#ifndef __ABASE_HASH_TABLE_H__
#define __ABASE_HASH_TABLE_H__

struct _hash_function
{
	_hash_function() {}
	_hash_function(const _hash_function & hf) {}

	inline size_t operator()(char data) const {return data;}
	inline size_t operator()(short data) const {return data;}
	inline size_t operator()(int data) const {return data;}
	inline size_t operator()(long data) const {return data;}
	inline size_t operator()(unsigned char data) const {return data;}
	inline size_t operator()(unsigned short data) const {return data;}
	inline size_t operator()(unsigned int data) const {return data;}
	inline size_t operator()(unsigned long data) const {return data;}
	inline size_t operator()(void *data) const {return (size_t)data;}

	inline size_t operator()(__int64 data) const
	{
		return (unsigned long)((data >> 32) + (data & 0xffffffff));
	}

	inline size_t operator()(unsigned __int64 data) const
	{
		return (unsigned long)((data >> 32) + (data & 0xffffffff));
	}

	inline unsigned long operator()(char *s) const
	{
		unsigned long h = 0;
		for(;*s; s++)
		{
			h = h * 31 + *(unsigned char *)s;
		}
		return h;
	}
	inline unsigned long operator()(const char *s) const
	{
		unsigned long h = 0;
		for(;*s; s++)
		{
			h = h * 31 + *(unsigned char *)s;
		}
		return h;
	}
	inline unsigned long operator()(const wchar_t *s) const
	{
		unsigned long h = 0;
		for(;*s; s++)
		{
			h = h * 31 + *s;
		}
		return h;
	}	

};

#endif

