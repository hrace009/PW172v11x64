#ifndef __ELEMENT_SKILL_H
#define __ELEMENT_SKILL_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ELEMENTSKILL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ELEMENTSKILL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef ELEMENTSKILL_EXPORTS
#define ELEMENTSKILL_API __declspec(dllexport)
#else
#define ELEMENTSKILL_API //__declspec(dllimport)
#endif

#include "../Header/asm.h"
#include <vector>
#include <utility>

namespace GNET
{
enum skill_type{
    TYPE_ATTACK   = 1,  // ����0�9�0�0��0�2�0�3��
    TYPE_BLESS    = 2,  // ����0�9�0�0���0�1�ׁ0�1
    TYPE_CURSE    = 3,  // ����0�9�0�0���٧���
    TYPE_SUMMON   = 4,  // ���᧨���0�6�0�6����
    TYPE_PASSIVE  = 5,  // ���0�3�0�9�0�0
    TYPE_ENABLED  = 6,  // ���է���ׁ0�8�0�6��
    TYPE_LIVE     = 7,  // ����0�3��
    TYPE_JUMP     = 8,  // ���0�9����
	TYPE_PRODUCE  = 9,  // ����0�9��(�0�3�0�2�0�4��)
	TYPE_BLESSPET = 10,  // �0�4�ڧ��᧹�0�1�ׁ0�1
	TYPE_NEUTRALBLESS = 11,	//�����������0�1�ׁ0�1
};

enum range_type{
	TYPE_POINT = 0,          // �0�8�� 
	TYPE_LINE  = 1,          // ���� 
	TYPE_SELFSPHERE  = 2,    // �������ߧ��0�7���������0�8������
	TYPE_TARGETSPHERE = 3,   // ���0�5���ܧ��0�7���������0�8������
	TYPE_TAPER  = 4,         // ���0�9���0�9
	TYPE_SLEF  = 5,          // ��������
};

enum form{
	FORM_MASK_HIGH	= 0xC0,
	FORM_NORMAL		= 0,	//���������������0�1
	FORM_CLASS		= 1,	//���㧴�0�8���է���
	FORM_BEASTIE	= 2,	//���է��0�7�0�9�0�0����
};

struct LearnRequirement
{
	int level;		//���؁0�6���0�6�0�9����
	int sp;         //�0�6�0�6�����0�8��
	int money;      //�0�8�⧩�0�3
	int profession; //���㧴�0�8
	int rank;       //�������؁0�6�0�9����
	int realm_level;//�0�3�0�4�0�8�ف0�8���0�6�0�9
};

struct PetRequirement
{
	int  level;		 //�0�4�ڧ���0�6�0�9����
	int  sp;         //���駪���0�6�0�6�����0�8��
	int* list;       //���������0�6�0�6������������
	int  lsize;      //�������߁0�3�姲�0�7
};

struct GoblinRequirement
{
	int  genius[5];	  //���0�7�0�3�0�0���ہ0�6�0�6�������ާׁ0�4�0�8��
	int  profession;  //���㧴�0�8
	int  sp;		  //���駪�����0�7����
	int  money;		  //���駪���0�8�⧩�0�3
	int  level;		  //���0�7�0�3�0�0���ہ0�8���0�6�0�9
	int  mp;		  //���0�7�0�3�0�0���ہ0�8�����㧥�����0�5��������
};

struct ComboSkillState
{
	enum{ MAX_COMBO_ARG = 3 };
	unsigned int skillid;
	int arg[MAX_COMBO_ARG];
	ComboSkillState():skillid(0)
	{
		memset(arg, 0, sizeof(arg));
	}
};

struct UseRequirement
{
	int mp;            //���졤��
	int ap;            //���0�2���꧸�0�8
	int form;          //���է��ߧ��0�3���0�1
	int weapon;        //���է���
	int freepackage;   //�����ק��0�1���ѧ��痢�0�5
	int arrow;         //������ׁ0�6�笠�짬�痢�0�5
	int move_env;	//�����0�9�0�0�0�3���0�3�0�4
	bool is_combat;   //�������㧷�0�8�0�9�����0�3���0�1
	int hp;				//�0�8������hp
	int max_hp;			//�����0�3��hp
	ComboSkillState combo_state;	//���0�1����0�6�0�6����0�3��
};

struct GoblinUseRequirement
{
	int mp;			//�������0�5(���0�7����)
	int ap;			//���֧��0�7(�������0�7)
	int genius[5];	//���0�7�0�3�0�0���ہ0�6�0�6�������ާׁ0�4�0�8��
	int profession; //���駪�����㧴�0�8
	int level;		//���0�7�0�3�0�0���ہ0�8���0�6�0�9�0�1�0�1���������0�6�����ԧ������0�7����0�2��
	int move_env;	//���駪���0�8�����㧴���0�9�0�0�0�3���0�3�0�4 
};

class SkillStub;

class ELEMENTSKILL_API SkillStr
{
public:
	virtual wchar_t* Find(int id) const {  return NULL; }
};

class ELEMENTSKILL_API ElementSkill
{
public:
	enum {
		SKILL_PERFORM,
		SKILL_DONE,
	};
	typedef unsigned int ID;
	
	static ID NextSkill(ID id = 0);

	// �0�6�0�6��������0�4��
	virtual const wchar_t* GetName() { return NULL;}
	virtual const char* GetNativeName() { return NULL;}
	// �0�6�0�6�������ѡ���,�0�6��skill_type
	virtual char GetType() const { return 1; }        
	// �0�6�0�6�������0�6����
	virtual const char* GetIcon() { return NULL; }
	// �0�6�0�6�������0�8����
	virtual const wchar_t* GetIntroduction(wchar_t* buf,int len,const SkillStr& table) { return L""; }
	// �0�6�0�6�������㧴�0�8��������
	virtual int GetCls() const { return -1; }
	// �0�6�0�6�������է��0�3�����0�6�Ձ0�1�0�1�0�8�0�2���0�3�0�2������
	virtual int GetCoolingTime() { return 5000; }
	// �0�6�0�6�������0�3���������0�6�Ձ0�1�0�1�0�8�0�2���0�3�0�2������
	virtual int GetExecuteTime() { return 1000; }
	// ���0�5���ܧ��ѧ�����������, 0:�������ڧ��0�5���܁0�1�0�11:���ڧ��0�7���0�5���܁0�1�0�12:���0�5���܁0�8�觱���������0�1����, 3:���0�5���ܡ������ݧ��0�7������, 4:���0�5���ܡ������ݧ��0�7�0�4�ڧ��� 
	virtual int GetTargetType(){return 0;}
	// �0�6�0�6�����������짬�������0�3�ѧ���: <-0.001�������ڧ��0�5���� -0.001-0.001 ���0�1������0�2�0�3��0�3�ѧ��݁0�1�0�1>0.001 ���������0�3�ѧ���
	virtual float GetPrayRange(float range, float prayplus) { return 0; }  


	// �0�6�0�6�����������؁0�6�0�9����
	virtual int GetRank() { return 0; }
	// ���짱��n�0�6�0�9�0�6�0�6�������0�7����0�8�����؁0�6���0�6�0�9����
	virtual int GetRequiredLevel() { return 0;}
	// ���짱��n�0�6�0�9�0�6�0�6�������ڧ��0�7�0�8���0�6�0�6�����0�8��
	virtual int GetRequiredSp() { return 0;}
	// ���짱��n�0�6�0�9���ڧ��0�7�0�8���0�6�0�6��������
	virtual int GetRequiredBook() { return 0;}
	// ���짱�㧲�ڧ��0�7�0�8�⧩�0�3
	virtual int GetRequiredMoney() { return 0;}
	// ���짱�㧲�ڧ���0�3�0�4�0�8�ف0�8���0�6�0�9
	virtual int GetRequiredRealmLevel() { return 0; }
	// ���㧮�ҁ0�6�0�6����
	virtual const std::vector<std::pair<unsigned int, int> > & GetRequiredSkill() = 0;
	// �������0�3���0�4����
	virtual int GetShowOrder() { return 0; }
	// ���ڧ����0�6�0�6�����0�6�0�9����
	virtual int SetLevel(int) { return 0; } 
	// �0�6�0�6���������0�3��0�6�0�9����
	virtual int GetMaxLevel() { return 0; }

	// �������㧲�ৢ�0�7�0�6�0�6����
	virtual bool IsWarmup() { return false; }
	// �������0�2�姬�����㧹���0�9�0�0��0�2�0�3��
	virtual bool IsAutoAttack(){return false;}
	// ���0�9���0�2�0�6�0�6����
	virtual bool IsInstant(){return false;}
	// ��������0�4������0�6�0�6����
	virtual bool IsDurative() { return false; }
	// �����������0�9����0�8�����ѧ���
	virtual int  GetRangeType() { return 0; }
	// ���������0�3���0�3�0�4�0�1�0�2�0�5�������0�7�0�2�0�8�����؁0�7�0�2���0�3����
	virtual int  GetCastEnv() { return 0; }
	// �0�3�㧪�0�7���0�7�0�3�0�0���ۧ��짱��0�2�����������0�6�0�6�������맲�ڧ��ާׁ0�4�0�8��
	virtual int* GetRequiredGenius(int idSkill) { return NULL; }

	// ���������0�6�𧤧�
	virtual const char* GetEffect() { return NULL;}
	virtual const char* GetElseEffect() { return NULL;}

	// ���������ڧ��0�7MP
	virtual int GetMpCost(){return 1;}

	// ���������ڧ��0�7AP
	virtual int GetApCost(){return 0;}

	// �0�6�笠�짱��0�2��
	virtual int GetArrowCost(){return 0;}

	// ���է��駮��0�6�𧦧��0�9��
	virtual bool ValidWeapon(int w) const { return true; }
	// 0, �0�4����0�7�0�1�0�31�0�1�0�1���է���0�9�0�3���0�2���Ձ0�1�0�32, mp�0�9�0�3���ԁ0�1�0�33�0�1�0�1���0�3��������0�6���0�9�0�3���짹�ԁ0�1�0�34�0�1�0�1����0�4������0�6���0�9�0�3���짹�ԁ0�1�0�35�0�1�0�1�0�3�ߧ���ID, 6�0�1�0�1���0�3���0�7���㧥�0�5����
	int Condition(UseRequirement& info);

	virtual bool IsAllowLand(){ return true; }
	virtual bool IsAllowWater(){ return true; }
	virtual bool IsAllowAir(){ return true; }
	virtual bool GetNotuseInCombat(){ return false; }
	//�������㧴���0�9�0�0���0�8����
	virtual bool IsMovingSkill() { return false; }
	// �0�6�0�6�����������㧶���0�8��������է��ߧ��0�3���0�1����������
	bool IsValidForm(char form);
	virtual char GetAllowForms() { return 0; }
	virtual bool Interrupt() { return true; }
	int GetAbilityPercent();

	// �0�3�㧪�0�7���с0�9�����0�7�0�8���0�4��0�6�0�9�0�6�0�6����
	virtual std::vector<std::pair<unsigned int, int> > GetJunior() { return std::vector<std::pair<unsigned int, int> >(); };

	// �0�3�㧪�0�7���0�7�0�3�0�0���ہ0�6�0�6�������㧴�0�8��������
	virtual int GetClsLimit() { return 0; }
	
	//�0�3�㧪�0�7��0�0��0�9���է��0�3mask bit0-4 �0�6�0�6�������է��0�30-4 bit5-9 ���᧨�����է��0�30-4
	virtual int GetCommonCoolDown() { return 0; }

	//�0�3�㧪�0�7��0�0��0�9���է��0�3�����0�6�Ձ0�1�0�1�0�8�0�2���0�3�0�2������
	virtual int GetCommonCoolDownTime() { return 0; }

	//�0�3�㧪�0�7����0�4�0�7���맲�ڧ��᧨��
	virtual int GetItemCost() { return 0; }

	//�0�3�㧪�0�7���0�1����0�6�0�6���0�8�������㧮��
	virtual int GetComboSkPreSkill(){ return 0; }

	//�0�6�ށ0�9�ۧ��0�8��������hp��������
	virtual bool CheckHpCondition(int hp, int max_hp) { return true; }

	//�0�6�ށ0�9�ۧ��0�1����0�6�0�6�0�9�৯�ӧ���0�6��
	virtual bool CheckComboSkExtraCondition(){ return true; } 
	
	// 0:�0�4����0�7            1:SP�0�9�0�3����            2:�0�6�0�9����0�9�0�3��0�3
	// 3:����0�6�0�9            4:�������ց0�9�0�3���0�2����        5:�0�3�ߧ���ID
	// 6:�0�8�⧩�0�3�0�9�0�3����        7:�������؁0�6�0�9����0�9�0�3���짹��    8:���0�3�����0�6�0�6��������
	// 9:���0�3�������㧮�ҁ0�6�0�6����    10:���ާ����0�9���0�9�0�3����       11:�����0�3�0�2����0�8�0�8�����ק��0�6�0�9�0�6�0�6����
	// 12:�0�3�0�4�0�8�٧���0�6���0�9�0�3���짹��
	static int LearnCondition(ID id, LearnRequirement& info, int level ); 

	// 0:�0�4����0�7            1:���է���0�9�0�3���0�2����        2:mp�0�9�0�3����
	// 3:���0�3��������0�6���0�9�0�3���짹��  4:����0�4������0�6���0�9�0�3���짹��    5:�0�3�ߧ���ID
	// 6:���0�3���0�7���㧥�0�5����      7:���է��ߧ��0�3���0�1�0�3�ߧ���      8:���0�2���꧸�0�8�0�9�0�3����
	// 9:�0�6�笠��0�9�0�3����        10:�����ק��0�3�������0�1���ѧ��0�3���� 11: �0�9�0�3�����������0�8�0�9������������
	// 12:HP����0�6���0�9�0�3���짹��   13:���0�1����0�6�0�6���㧮�ҁ0�9�0�3���짹��
	static int Condition(ID id, UseRequirement& performer, int level );

	// 0:�0�4����0�7            1:���駪��SP�0�9�0�3����        2:�0�6�0�9����0�9�0�3��0�3
	// 3:����0�6�0�9            9:���㧮�ҁ0�6�0�6�����0�6�0�9����0�9�0�3��0�3  5:�0�3�ߧ���ID
	static int PetLearn(ID id, PetRequirement& info, int level); 

	// 0:�0�4����0�7            1:���駪��SP�0�9�0�3����        2:�0�6�0�6�������ާׁ0�4�0�8�ԁ0�9�0�3����
	// 3:����0�6�0�9            4:�0�6�0�6�����ק觬�隣������		 5:�0�3�ߧ���ID
	// 6:�0�8�⧩�0�3�0�9�0�3����		 7:�������0�7�0�3�0�0���ہ0�6�0�6����		 8:���0�3�����0�6�0�6��������
	// 9:�0�8���0�6�0�9�0�9�0�3����       10:�������0�5���������0�9�0�3����     11:���㧴�0�8�0�9�0�3���0�2����
    // 12:�������0�5���������0�9�0�3���ԁ0�1�0�1�������㧴�0�8�0�9�0�3���0�2����
	static int GoblinLearn(ID id, GoblinRequirement& info, int level); 

	// 0:�0�4����0�7            1:���㧴�0�8�0�9�0�3���0�2����        2:mp�0�9�0�3����
	// 3:AP�0�9�0�3����			 4:���ާׁ0�4�0�8�ԁ0�9�0�3����		 5:�0�3�ߧ���ID
	// 6:���0�3���0�7���㧥�0�5����      7:�������0�7�0�3�0�0���ہ0�6�0�6����      8:�����0�9�0�0�0�3���0�3�0�4�0�9�0�3���짹��
	static int GoblinCondition(ID id, GoblinUseRequirement& info, int level );

	//�0�3�㧪�0�7���㧴�0�8���ާ���0�6�0�6����
	static const std::vector<ID>& GetInherentSkills(int cls);

	//�0�3�㧪�0�7�0�6��0�3���0�8�����0�1����0�6�0�6��������
	static void GetComboSkActivated(const ComboSkillState & combo_state, std::vector<std::pair<ID, int> >& list);
	//�������㧴���0�9�0�0���0�8����
	static bool IsMovingSkill(ID id);

	static char GetType(ID id);  
	static const char* GetIcon(ID id);
	static const wchar_t* GetName(ID id);
	static const char* GetNativeName(ID id);
	static const char* GetEffect(ID id);
	static const char* GetElseEffect(ID id);
	static const wchar_t* GetIntroduction(ID id, int level, wchar_t* buf, unsigned int len, const SkillStr& table);
	static int GetRequiredLevel(ID id, int level);
	static int GetRequiredSp(ID id, int level);
	static int GetRequiredBook(ID id, int level);
	static int GetRequiredMoney(ID id, int level);
	static int GetRequiredRealmLevel(ID id, int level);
	static bool IsValidForm(ID id, char form);
	static int GetExecuteTime(ID id, int level);
	static int GetAbilityPercent(ID id);
	static std::vector<std::pair<unsigned int, int> > GetJunior(ID id);
	static int GetCommonCoolDown(ID id);
	static int GetCommonCoolDownTime(ID id);
	static int GetItemCost(ID id);
	
	static bool IsGoblinSkill(ID id);
	static int GetComboSkPreSkill(ID id);
	
	//����0�8���0�6�0�6�������ާ����0�9��  <0���0�3��������0�3�ҁ0�3���0�6�0�6���� >=0 ���ާ����0�9��
	static int GetAbility(ID id); 
	static int SetAbility(ID id, int ability);
	static int SetLevel(ID id, int level);
	static int GetLevel(ID id);
	static bool IsOverridden(ID id);
	static int GetMaxAbility(ID id, int level);

	static void LoadSkillData(void * data);

	static ElementSkill* Create(ID id, int level);
	void Destroy();

	static int GetVersion();
	
	//
	// �0�4�秬�0�6�0�3�0�0�0�6�0�6���������0�9�0�5�0�3�0�9���0�1����0�3���0�1�0�1�����������0�5�ӧ��0�3����0�8�駵���0�1�0�7�0�1�0�7�0�1�0�7
	//
	static void InitStaticData();
};

class ELEMENTSKILL_API VisibleState
{
public:
	virtual const int GetID() const { return 0; }
	virtual const wchar_t* GetName() const {  return NULL; }
	virtual const char* GetHH() const { return NULL; }
	virtual const char* GetEffect() const {  return NULL; }
	static const VisibleState* Query(int profession, int id);
};

class ELEMENTSKILL_API TeamState
{
public:
	virtual const int GetID() const { return 0; }
	virtual const wchar_t* GetName() const {  return NULL; }
	virtual const char* GetIcon() const { return NULL; }
	static const TeamState* Query(int id);
};

void InitSkillStub1();
void InitSkillStub2();
void InitSkillStub3();
void InitSkillStub4();
void InitSkillStub5();
void InitSkillStub6();
void InitSkillStub7();
void InitSkillStub8();
void InitSkillStub9();
void InitSkillStub10();
void InitSkillStub11();
void InitSkillStub12();

}

#endif
