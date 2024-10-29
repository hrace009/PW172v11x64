#ifndef __ONLINEGAME_GS_PACKET_WRAPPER_H__
#define __ONLINEGAME_GS_PACKET_WRAPPER_H__

#include <vector.h>
#include <octets.h>
#include "types.h"
#include "base_wrapper.h"


class packet_raw_wrapper 
{
	abase::octets _buf;
	template <typename T>
	void push_byte(T t)
	{
		_buf.push_back(&t,sizeof(t));
	}
	void push_byte(const void * buf,size_t size)
	{
		_buf.push_back(buf,size);
	}
public:
	int _counter;
	packet_raw_wrapper():_buf(),_counter(0){}
	explicit packet_raw_wrapper(size_t size):_buf(size),_counter(0){}
	bool empty() { return _buf.empty();}
	void swap(packet_raw_wrapper &rhs)
	{
		_buf.swap(rhs._buf);
		std::swap(_counter,rhs._counter);
	}
	
	packet_raw_wrapper & operator<<(int val)		{push_byte(val);return *this;}
	packet_raw_wrapper & operator<<(unsigned int val) 	{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(short val) 		{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(unsigned short val)	{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(char val)		{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(unsigned char val)	{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(bool val)		{return operator<<((char)val);}
	packet_raw_wrapper & operator<<(float val)		{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(int64_t val)		{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(uint64_t val)		{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(double val)		{push_byte(val);return *this;} 
	packet_raw_wrapper & operator<<(const A3DVECTOR & vec)	{push_byte(vec);return *this;} 
	packet_raw_wrapper & operator<<(const char * str) {push_byte(str,strlen(str)+1);return *this;} 
	packet_raw_wrapper & operator<<(const abase::octets& buf)
	{
		return 	push_back(buf.begin(),buf.size());
	}
	packet_raw_wrapper & operator<<(const packet_raw_wrapper& wrapper)
	{
		_buf.push_back(wrapper._buf.begin(),wrapper._buf.size());
		return *this;
	}
	packet_raw_wrapper & push_back(const void * buf,size_t size)
	{
		_buf.push_back(buf,size);
		return *this;
	}
	abase::octets & get_buf() { return _buf;}
	void * data() { return _buf.begin();}
	size_t size() { return _buf.size();}
	size_t raw_size() { return _buf.size();}
	void clear() { 
		_buf.clear();
		_counter = 0;
	}
	int get_counter() { return _counter;}
};

class packet_baked_wrapper 
{
	abase::octets _buf;
	size_t _raw_size;
	template <typename T>
	void push_byte(T t)
	{
		_buf.push_back(&t,sizeof(t));
		_raw_size += sizeof(t);
	}
	void push_byte(const void * buf,size_t size)
	{
		_buf.push_back(buf,size);
	}
	void push_type(int type)
	{
		_buf.push_back(&type,sizeof(type));
	}
public:
	int _counter;
	enum
	{
		T_INT,
		T_UNSIGNED_INT,
		T_SHORT,
		T_UNSIGNED_SHORT,
		T_CHAR,
		T_UNSIGNED_CHAR,
		T_FLOAT,
		T_A3DVECTOR,
		T_STRING,
		T_BINARY,
	};
	packet_baked_wrapper():_buf(),_raw_size(0),_counter(0){}
	explicit packet_baked_wrapper(size_t size):_buf(size),_raw_size(0),_counter(0){}
	bool empty() { return _buf.empty();_raw_size = 0;}
	void swap(packet_baked_wrapper &rhs)
	{
		_buf.swap(rhs._buf);
		std::swap(_counter,rhs._counter);
	}
	
	packet_baked_wrapper & operator<<(int val)		{push_type((char)T_INT);push_byte(val);return *this;}
	packet_baked_wrapper & operator<<(unsigned int val) 	{push_type((char)T_UNSIGNED_INT);push_byte(val);return *this;} 
	packet_baked_wrapper & operator<<(short val) 		{push_type((char)T_SHORT);push_byte(val);return *this;} 
	packet_baked_wrapper & operator<<(unsigned short val)	{push_type((char)T_UNSIGNED_SHORT);push_byte(val);return *this;} 
	packet_baked_wrapper & operator<<(char val)		{push_type((char)T_CHAR);push_byte(val);return *this;} 
	packet_baked_wrapper & operator<<(unsigned char val)	{push_type((char)T_UNSIGNED_CHAR);push_byte(val);return *this;} 
	packet_baked_wrapper & operator<<(bool val)		{return operator<<((char)val);}
	packet_baked_wrapper & operator<<(float val)		{push_type((char)T_FLOAT);push_byte(val);return *this;} 
	packet_baked_wrapper & operator<<(const A3DVECTOR & vec){push_type((char)T_A3DVECTOR);push_byte(vec);return *this;} 
	packet_baked_wrapper & operator<<(const char * str) {push_type((char)T_STRING);push_byte(str,strlen(str)+1);return *this;} 
	packet_baked_wrapper & operator<<(const abase::octets& buf)
	{
		return 	push_back(buf.begin(),buf.size());
	}
	packet_baked_wrapper & operator<<(const packet_baked_wrapper& wrapper)
	{
		_raw_size += wrapper._raw_size;
		_buf.push_back(wrapper._buf.begin(),wrapper._buf.size());
		return *this;
	}
	packet_baked_wrapper & push_back(const void * buf,size_t size)
	{
		push_type((char)T_BINARY);
		push_byte(size);
		_raw_size += size;
		_buf.push_back(buf,size);
		return *this;
	}
	abase::octets & get_buf() { return _buf;}
	void * data() { return _buf.begin();}
	size_t size() { return _buf.size();}
	size_t raw_size() { return _raw_size;}
	void clear() { 
		_buf.clear();
		_counter = 0;
	}
	int get_counter() { return _counter;}

};
class packet_in_wrapper 
{
public:
	const unsigned char * data;
	size_t size;
	size_t offset;
	template <typename T>
	void pop_byte(T & t)
	{
		if(offset + sizeof(t) <= size)
		{
			memcpy(&t,data + offset,sizeof(t));
			offset += sizeof(t);
		}
		else
		{
			ASSERT(false && "»º³åÇøÇ·ÔØ");
			memset(&t,0,sizeof(t));
		}
	}

public:
	packet_in_wrapper(const void * buf,size_t len):data((const unsigned char*)buf),size(len),offset(0){}
	packet_in_wrapper & operator>>(int &val)		 	{pop_byte(val);return *this;}
	packet_in_wrapper & operator>>(unsigned int &val)	{pop_byte(val);return *this;}
	packet_in_wrapper & operator>>(short &val) 		{pop_byte(val);return *this;}
	packet_in_wrapper & operator>>(unsigned short &val)	{pop_byte(val);return *this;}
	packet_in_wrapper & operator>>(char &val)		{pop_byte(val);return *this;}
	packet_in_wrapper & operator>>(unsigned char &val)	{pop_byte(val);return *this;}
	packet_in_wrapper & operator>>(bool &val)		{return operator>>((char&)val);}
	packet_in_wrapper & operator>>(float &val)		{pop_byte(val);return *this;}
	packet_in_wrapper & operator>>(A3DVECTOR & vec)	{pop_byte(vec);return *this;}
	packet_in_wrapper & get_string(char * str,size_t len)
	{
		size_t cplen = size - offset;
		if(cplen > len ) cplen = len;
		str[cplen - 1] = 0;
		strncpy(str,(const char *)data + offset, cplen -1);
		offset += strlen(str);
		return *this;
	}
	packet_in_wrapper & pop_back(void * __buf,size_t __size)
	{
		if(offset + __size <= size)
		{
			memcpy(__buf,data + offset,__size);
			offset += __size;
		}
		else
		{
			ASSERT(false && "»º³åÇøÇ·ÔØ");
			memset(__buf,0,__size);
		}
		return *this;
	}
};

class raw_wrapper : public base_wrapper
{
	abase::octets _buf;
	size_t _offset;
	char _check_save;
	template <typename T>
	void push_byte(T t)
	{
		ASSERT(_check_save != LOAD_ONLY);
		_buf.push_back(&t,sizeof(t));
	}
	void push_byte(const void * buf,size_t size)
	{
		ASSERT(_check_save != LOAD_ONLY);
		_buf.push_back(buf,size);
	}

	template <typename T>
	void pop_byte(T & t)
	{
		ASSERT(_check_save != SAVE_ONLY);
		if(_offset + sizeof(t) <= _buf.size())
		{
			memcpy(&t,_buf.begin()+ _offset,sizeof(t));
			_offset += sizeof(t);
		}
		else
		{
			Failed();
		}
	}
	void Failed()
	{
		throw "»º³åÇøÇ·ÔØ";
	}
public:
	enum
	{
		NO_LIMIT,
		SAVE_ONLY,
		LOAD_ONLY,
	};
	raw_wrapper():_buf(),_offset(0),_check_save(0){}
	explicit raw_wrapper(size_t size):_buf(size),_offset(0),_check_save(0){}
	explicit raw_wrapper(const void * buf,size_t size):_buf(buf,size),_offset(0),_check_save(0){}
	void SetLimit(char check_save) { _check_save = check_save; }
	bool empty() { return _buf.empty();}
	void swap(raw_wrapper &rhs)
	{
		_buf.swap(rhs._buf);
		abase::swap(_offset,rhs._offset);
	}
	void swap(abase::octets &rhs)
	{
		_buf.swap(rhs);
		_offset = 0;
	}
	
	raw_wrapper & operator<<(int val)		{push_byte(val);return *this;}
	raw_wrapper & operator<<(unsigned int val) 	{push_byte(val);return *this;} 
	raw_wrapper & operator<<(short val) 		{push_byte(val);return *this;} 
	raw_wrapper & operator<<(unsigned short val)	{push_byte(val);return *this;} 
	raw_wrapper & operator<<(char val)		{push_byte(val);return *this;} 
	raw_wrapper & operator<<(unsigned char val)	{push_byte(val);return *this;} 
	raw_wrapper & operator<<(int64_t val)	{push_byte(val);return *this;} 
	raw_wrapper & operator<<(uint64_t val)	{push_byte(val);return *this;} 
	raw_wrapper & operator<<(double val)	{push_byte(val);return *this;} 
	raw_wrapper & operator<<(float val)		{push_byte(val);return *this;} 
	raw_wrapper & operator<<(const A3DVECTOR & vec)	{push_byte(vec);return *this;} 
	raw_wrapper & operator<<(const char * str) {push_byte(str,strlen(str)+1);return *this;} 
	raw_wrapper & operator<<(const abase::octets& buf)
	{
		return 	push_back(buf.begin(),buf.size());
	}
	raw_wrapper & operator<<(const raw_wrapper& wrapper)
	{
		push_byte(wrapper._buf.begin(),wrapper._buf.size());
		return *this;
	}
	raw_wrapper & push_back(const void * buf,size_t size)
	{
		push_byte(buf,size);
		return *this;
	}
	abase::octets & get_buf() { return _buf;}
	void * data() { return _buf.begin();}
	void * cur_data() { return _buf.begin() + _offset;}
	size_t offset() { return _offset;}
	size_t size() { return _buf.size();}
	void clear() { _buf.clear(); }
	bool shift(int offset) { _offset += offset; return _offset <= _buf.size();}

	raw_wrapper & operator>>(int &val) { pop_byte(val);return *this; } 
	raw_wrapper & operator>>(unsigned int &val) { pop_byte(val);return *this; } 
	raw_wrapper & operator>>(short &val) { pop_byte(val);return *this; } 
	raw_wrapper & operator>>(unsigned short &val) { pop_byte(val);return *this; } 
	raw_wrapper & operator>>(char &val) { pop_byte(val);return *this; } 
	raw_wrapper & operator>>(unsigned char &val){ pop_byte(val);return *this; } 
	raw_wrapper & operator>>(int64_t &val){ pop_byte(val);return *this; } 
	raw_wrapper & operator>>(uint64_t &val){ pop_byte(val);return *this; } 
	raw_wrapper & operator>>(double &val){ pop_byte(val);return *this; } 
	raw_wrapper & operator>>(float &val) { pop_byte(val);return *this; } 
	raw_wrapper & operator>>(A3DVECTOR & vec){ pop_byte(vec);return *this; } 
	raw_wrapper & get_string(char * str,size_t len)
	{
		if(_buf.size() > _offset)
		{
			size_t cplen = _buf.size() - _offset;
			unsigned char * tmp = _buf.begin() + _offset;
			len --;
			while(len > 0 && cplen > 0 && *tmp)
			{
				*str++ = (char)(*tmp++);
				len --;
				cplen --;
				_offset ++;
			}
			if(*tmp == 0 && cplen > 0)
			{
				*str = 0;
				_offset ++;
			}
			else
			{
				Failed();
			}
		}
		else
		{
			Failed();
		}
		return *this;
	}
	
	raw_wrapper & pop_back(void * buf,size_t size)
	{
		if(_offset + size <= _buf.size())
		{
			memcpy(buf,_buf.begin() + _offset, size);
			_offset += size;
		}
		else
		{
			Failed();
		}
		return *this;
	}
	bool is_eof() { return _offset >= _buf.size(); }
};

typedef packet_raw_wrapper packet_wrapper;
#endif
