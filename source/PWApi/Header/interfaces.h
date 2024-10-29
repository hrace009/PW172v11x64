//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _INTERFACES_H_
#define _INTERFACES_H_

class Interfaces
{
private:
#pragma pack(push, 1)
	struct AUILabel
	{
		const wchar_t* GetText();
		void SetText(const wchar_t* pszText);
	};

	struct AUIListBox
	{

	};

#pragma pack(pop)
private:
	bool timer_enable;
	int cur_hp;
	int max_hp;
	int cur_level;
	size_t instance_timer;
	const wchar_t* chFile;
	void * m_pLstColors;
public:

	inline void GET_RGBA(int value, int& red, int& grin, int& blue, int& alpha)
	{
		blue = value & 0xff;
		grin = ((value & (0xff << 8)) >> 8);
		red = ((value & (0xff << 16)) >> 16);
		alpha = ((value & (0xff << 24)) >> 24);
	}

	inline int SET_RGBA(int red, int grin, int blue, int alpha)
	{
		return (_byteswap_ulong(RGB(red, grin, blue)) >> 8) | (alpha << 24);
	}


	void Init();
	void HeartBeat(size_t tick);
	inline void Enable() { timer_enable = true; }
	inline void Distable() { timer_enable = false; }
	
	int Btn_c2scmd(const char* str);
	void OnClick(const char* str);

	void* GetInGameUIMan();
	void* GetDialog(const char* str);
	bool ShowDialog(const char* str);
	void* GetDlgItem(void* DIALOG, const char* label);

	void InsRefreshOnTick();
	void HpMpOtherBOnTick();
	bool InsRefreshCmd();
	void DistanceNpcShop(int);
	void SetSelfProperty(int* table);
	void ArenaSetInfo(const char* lab, int value);
	void SetTargetLevel(int level);
	void SetInsTimer(int ins_timer);
	void SetTargetHP(int hp, int max_hp);
	void SetStging(const char* win_dlg, const char* label, const wchar_t* value);

	void LoadName();

public:

	static Interfaces* GetInstance()
	{
		if (!instance)
			instance = new Interfaces();
		return instance;
	}
	static Interfaces* instance;
};


#endif