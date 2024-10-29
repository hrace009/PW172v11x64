//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _CLASS_INFORMEF_H_
#define _CLASS_INFORMEF_H_

class ClassInformer
{
private:
    struct PROTOCOL
    {
        size_t addr;
        size_t count;
        size_t str_size;
        char str[512];
    };
    struct CNET
    {
        int count;
		PROTOCOL protocol[5200];
    };
private:
    static CNET cnet;
	static const char * cgame_r[];
	static const char* cgame_s[];
	
public:
	void Init();
	void SetCnet(size_t addr, size_t count, const char* str);
	PROTOCOL GetCnet(size_t addr);
	const char* GetCGameSend(size_t type);
	const char* GetCNameRecv(size_t type);
	
	static ClassInformer* GetInstance()
	{
		if (!instance)
			instance = new ClassInformer();
		return instance;
	}
	static ClassInformer* instance;
};	
	
#endif