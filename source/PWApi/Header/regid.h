//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _REGID_H_
#define _REGID_H_

class Regid
{
private:
#pragma pack(push, 1)
	struct KEY
	{
		unsigned short command;
		unsigned long long data;
	};
#pragma pack(pop)
private:
	static KEY REG;
	static wchar_t REG_DIR[];
	static wchar_t REG_VALUE[];
public:
	void Init();
	unsigned long long RegOpen();
	unsigned long long RegCreate();
	inline void* Get() { return &REG; }
	inline size_t Size() { return sizeof(KEY); }

	inline void* WhGet() { return &REG.data; }
	inline size_t WhSize() { return sizeof(REG.data); }

public:
	static Regid* GetInstance()
	{
		if (!instance)
			instance = new Regid();
		return instance;
	}
	static Regid* instance;
};











#endif