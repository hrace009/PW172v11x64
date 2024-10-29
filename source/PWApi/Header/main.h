//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

#include "../cskill/ElementSkill.h"

class MainApi
{
public:
	enum
	{
		TEXT  = 0,
		RDATA = 1,
		IDATA = 2,
	};
private:
	struct IDATA_FUNCTIONS
	{
		size_t GetNativeName;			//ElementSkill::GetNativeName(uint)
		size_t GetRequiredBook;			//ElementSkill::GetRequiredBook(uint, int)
		size_t GetExecuteTime;			//ElementSkill::GetExecuteTime(uint, int)
		size_t GetVersion;				//ElementSkill::GetVersion(void)
		size_t SetAbility;				//ElementSkill::SetAbility(uint, int)
		size_t SetLevel;				//ElementSkill::SetLevel(uint, int)
		size_t LoadSkillData;			//ElementSkill::LoadSkillData(void*)
		size_t GetGfxFileName;			//ElementSkill::GetGfxFileName(int)
		size_t GetGfxHangPoint;			//ElementSkill::GetGfxHangPoint(int)
		size_t GetGfxTarget;			//ElementSkill::GetGfxTarget(int)
		size_t Create;					//ElementSkill::Create(uint, int)
		size_t Destroy;					//ElementSkill::Destroy(void)
		size_t GetEffect;				//ElementSkill::GetEffect(uint)
		size_t GetName;					//ElementSkill::GetName(uint)
		size_t IsValidForm;				//ElementSkill::IsValidForm(uint, char)
		size_t GetCommonCoolDown;		//ElementSkill::GetCommonCoolDown(uint)
		size_t GetIcon;					//ElementSkill::GetIcon(uint)
		size_t InitStaticData;			//ElementSkill::InitStaticData(void)
		size_t GetComboSkPreSkill;		//ElementSkill::GetComboSkPreSkill(uint)
		size_t NextSkill;				//ElementSkill::NextSkill(uint)
		size_t IsMovingSkill;			//ElementSkill::IsMovingSkill(uint)
		size_t GetMaxAbility;			//ElementSkill::GetMaxAbility(uint, int)
		size_t GetAbility;				//ElementSkill::GetAbility(uint)
		size_t IsOverridden;			//ElementSkill::IsOverridden(uint)
		size_t GetSkillRuneAttr;		//ElementSkill::GetSkillRuneAttr(int)
		size_t GetType;					//ElementSkill::GetType(uint)
		size_t IsGoblinSkill;			//ElementSkill::IsGoblinSkill(uint)
		size_t GetRequiredMoney;		//ElementSkill::GetRequiredMoney(uint, int)
		size_t GetRequiredSp;			//ElementSkill::GetRequiredSp(uint, int)
		size_t GetRequiredRealmLevel;	//ElementSkill::GetRequiredRealmLevel(uint, int)
		size_t GetRequiredLevel;		//ElementSkill::GetRequiredLevel(uint, int)
		size_t GetAbilityPercent;		//ElementSkill::GetAbilityPercent(uint)
		size_t Condition; // static int __cdecl GNET::ElementSkill::Condition(unsigned int, struct GNET::UseRequirement &, int)

		void init(size_t address, size_t & old_address, size_t lib_address);
	};


private:
	static size_t logs;
	static IDATA_FUNCTIONS Skill;
	bool fashion_weapon_enable;

public:

	void Init();
	void HeartBeat(size_t tick);
	void Patch(size_t type);
	void Log(const char* Src);
	void Dump(void* Src, size_t len, const char* name);
	void EnterWorld();
	void LeaveWorld();


	inline void ChkFashionWeapon() { fashion_weapon_enable ^= true; }

	static const char* GetTimeStr();

#ifdef _WIN64
	//hook api win64
	static char __fastcall CgameSendPacket(void* base, void* it, unsigned int size);
	static long long __fastcall CgameRecvPacket(void* base, int type, void* it, unsigned int size);
	static char __fastcall CnetSendPacket(void* base, void* it, char c);
	static char __fastcall CnetRecvPacket(void* base, void* it);
	static char __fastcall ClickButton(void*, const char*);
	static int __fastcall PvPPause(void* RCX, int iSevTime, int iTimeZoneBias, int pvp);
	static void* __fastcall GetNPC(void* RCX, int nid, int born);
	static int __fastcall GetItemCount(void* inv, int item_id);

	static int __fastcall GetRequiredBook(unsigned int id, int level);
	static int __fastcall GetRequiredMoney(unsigned int id, int level);
	static int __fastcall GetRequiredSp(unsigned int id, int level);
	static int __fastcall SkillCondition(unsigned int id, void * info, int ilevel);
	static void* __fastcall SkillCreate(unsigned int id, int level);
	static void* __fastcall ElsePlayerEnter(void* RCX, int* Info, int iCmd);
	static void __fastcall ElsePlayerLeave(void* RCX, int cid, bool bExit, bool bUpdateMMArray);
	static int __fastcall GetColorName(void* RCX);
	static bool __fastcall IsFashionWeaponTypeFit(int weapon_type, int fashion_weapon_type);
	static void* __fastcall ResponseMarshal(void* RCX, void* Buf, void* v1, void* v2, char v3);
#else
	//hook api win32
	static void* __fastcall ResponseMarshal(void* ECX, void* EDX, void* Buf);
	static int __fastcall CgameSendPacket(void* ECX, void* EDX, void* it, size_t size);
	static int _stdcall CgameRecvPacket(int type, void* it, int size);
	static int __fastcall CnetSendPacket(void* ECX, void* EDX, void * it, int size);
	static int __fastcall CnetRecvPacket(void* ECX, void* EDX, void * it);
	static int __fastcall ClickButton(void* ECX, void* EDX, char* str);
	static int __fastcall PvPPause(void* ECX, void* EDX, int iSevTime, int iTimeZoneBias, int pvp);
	static void* __fastcall GetNPC(void* ECX, void* EDX, int nid, int born);
	static int __fastcall GetItemCount(void* inv, void* EDX, int item_id);

	static int __cdecl GetRequiredBook(unsigned int id, int level);
	static int __cdecl GetRequiredMoney(unsigned int id, int level);
	static int __cdecl GetRequiredSp(unsigned int id, int level);
	static int __cdecl SkillCondition(unsigned int id, GNET::UseRequirement& info, int ilevel);
	static void* __cdecl SkillCreate(unsigned int id, int level);

	static void * __fastcall ElsePlayerEnter(void* ECX, void* EDX, int* Info, int iCmd);
	static void __fastcall ElsePlayerLeave(void* ECX, void* EDX, int cid, bool bExit, bool bUpdateMMArray);

	static int __fastcall GetColorName(void* ECX, void* EDX);
	static bool __cdecl IsFashionWeaponTypeFit(int weapon_type, int fashion_weapon_type);

#endif
	inline size_t GetLog() { return logs; }
	inline void ChangeLog() { logs ^= 1;  }




	static MainApi* GetInstance()
	{
		if (!instance)
			instance = new MainApi();
		return instance;
	}
	static MainApi* instance;
};

#endif
