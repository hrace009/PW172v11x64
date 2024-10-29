//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include <vector>

#define EXPORT_API __declspec(dllexport)

#pragma pack(push, 1)

	class SkillImport
	{
	public:
		enum 
		{
			MAX_STRLEN = 80000,
			
			MAX_SKILL = 6780,
			MAX_DEF_SKILL = 2865,

			MAX_NAME_LEN = 32,
			MAX_STRING = 1024,
			MAX_STUBS = 12,

			SECTION_NULL = 0,
			SECTION_CLT = 1,
			SECTION_SEV = 2,

			USER_CLASS_SWORDSMAN = 0,
			USER_CLASS_MAGE,	
			USER_CLASS_NEC,		
			USER_CLASS_HAG,		
			USER_CLASS_ORGE,	
			USER_CLASS_ASN,		
			USER_CLASS_ARCHER,	
			USER_CLASS_ANGEL,	
			USER_CLASS_BLADE,	
			USER_CLASS_GENIE,	
			USER_CLASS_SHADOW,	
			USER_CLASS_FAIRY,	
			USER_CLASS_SHOOTER,
			USER_CLASS_PALADIN,
			USER_CLASS_MONKY,
			USER_CLASS_COUNT
		};


	private:
		std::vector<std::string> ids[MAX_SKILL];
		std::vector<std::string> SkillRes;
		std::vector<std::string> skillstr[MAX_SKILL];
		std::vector<std::string> skillstr_all;
		CRITICAL_SECTION cs_file;

	public:
		void Init();
		void Log(const char* Src);
		void Dump(void* Src, size_t len, const char* name);
		void Restore(void* Src, size_t len, const char* name);
		const char* CheckNullStr(const char* str);
		const char* WtoGB2312(const wchar_t* wstr);

		bool Load();
		bool LoadScript();
		bool LoadStrScript();
		bool LoadSkillScript(int skill);
		void Print(const char * src);
		size_t Search(int skill, const char* src, size_t n = 0);
		size_t CountItem(int skill, const char* src);

		bool PrintItem(int skill, size_t num);
		bool PrintItem(int skill, size_t begin, size_t end, int section = SECTION_NULL);
		bool PrintStub(int skill, size_t stub);
		bool PrintStubDef(int skillis, size_t stub, size_t count);
		bool PrintFunc(int skill, const char* src, int section = SECTION_NULL);

		//elementskill
		void GenSkillCreate(int skillid, size_t count);
		void GenSkillRelease(int skillid);
		void GenSkillAdd(const char * str);
		bool GenSkillStubs(int skillid, size_t count);
		void GenSkillBase(int skillid, size_t count_stubs);
		void GenCreateScript(int skillid);
		void GenCreateMacro(int skillid);

		//clt+sev
		void GenSkillGetExecutetime				(int skillid);
		void GenSkillGetCoolingtime				(int skillid);
		void GenSkillGetRequiredSp				(int skillid);
		void GenSkillGetRequiredLevel			(int skillid);
		void GenSkillGetRequiredItem			(int skillid);
		void GenSkillGetRequiredMoney			(int skillid);
		void GenSkillGetRequiredRealmLevel		(int skillid);
		void GenSkillGetRadius					(int skillid);
		void GenSkillGetAttackdistance			(int skillid);
		void GenSkillGetAngle					(int skillid);
		void GenSkillGetPraydistance			(int skillid);
		void GenSkillGetMpcost					(int skillid);
		void GenSkillCheckComboSkExtraCondition	(int skillid);
		void GetCoolDownLimit					(int skillid);
		void GenSkillGetCostShieldEnergy		(int skillid);
		//clt										
		void GenSkillGetIntroduction			(int skillid);
		//sev										
		void GenSkillGetEnmity					(int skillid);
		void GenSkillGetMaxAbility				(int skillid);
		void GenSkillStateAttack				(int skillid);
		void GenSkillBlessMe					(int skillid);
		void GenSkillGetEffectdistance			(int skillid);
		void GenSkillGetTalent0					(int skillid);
		void GenSkillGetTalent1					(int skillid);
		void GenSkillGetTalent2					(int skillid);
		void GenSkillGetTalent3					(int skillid);
		void GenSkillGetTalent4					(int skillid);
		void GenSkillGetAttackspeed				(int skillid);
		void GenSkillTakeEffect					(int skillid);
		void GenSkillGetHitrate					(int skillid);
		void GenSkillComboSkEndAction			(int skillid);

		void GenGetChargeMerc					(int skillid);

		//global
		void SkillCreator(int skill);
		void StubsCreator(size_t num, size_t count, size_t max_count);
		void Creator(size_t count, size_t stubs_size);

		//glyph
		int GetBaseSkillGlyph(int skill);

		inline const char* GetIdsStr(int skill, int pos) { return ids[skill][pos].c_str(); }

		static SkillImport* GetInstance()
		{
			if (!instance)
				instance = new SkillImport();
			return instance;
		}
		static SkillImport* instance;
		static bool is_logs;
		static const char LogFileName[];
		static const char DumpFileName[];
	};


#pragma pack(pop)
#endif