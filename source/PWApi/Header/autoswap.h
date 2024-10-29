//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _AUTOSWAP_H_
#define _AUTOSWAP_H_

#include <iostream>
#include <cstring>

class AutoSwap
{
private:
	enum
	{
		MAX_EQUIP = 64,
		MAX_ITEM = 127,
	};
private:
#pragma pack(push, 1)

	struct C2S_AUTOSWAP
	{
		unsigned short cmd;
		unsigned short count;
		struct
		{
			char inv;
			char equip;
		}	item[MAX_EQUIP];

		size_t size()
		{
			return sizeof(this[0]) - ((sizeof(item) - (sizeof(item[0]) * count)));
		}
	};
#pragma pack(pop)
private:
	bool save;
	unsigned char equip[MAX_EQUIP];

public:
	void Init();
	void Clear();
	void Set(unsigned char inv, unsigned char equip);
	void Packet();
	void Change();

public:
	static AutoSwap* GetInstance()
	{
		if (!instance)
			instance = new AutoSwap();
		return instance;
	}
	static AutoSwap* instance;
};











#endif