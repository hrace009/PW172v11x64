#ifndef __ONLINEGAME_GS_ATTACK_H__
#define __ONLINEGAME_GS_ATTACK_H__


#include "config.h"
#include <common/types.h>

//��ͼ����ʱ�伶��
enum
{
	PROFIT_LEVEL_NONE,	//�����������
	PROFIT_LEVEL_YELLOW,//λ�������ͼ������ʱ�����1Сʱ
	PROFIT_LEVEL_NORMAL,//����ܻ����������
};

//����������������������� �� ���ó��﹥�������ҵĹ���
struct attacker_info_t
{
	XID attacker;			//�����ߵ�ID ���ڳ�� ��ID����ϢID��һ��
	short level;			//�����߼���
	short eff_level;		//��Ч���� Ϊ�����׼����
	int team_id;			//��������id
	int team_seq;			//������������
	int cs_index;			//�����player����ʾ��player��cs_index
	int sid;			//�����player����ʾ��player��cs_index ��Ӧ��sid 
	int mafia_id;			//������ţ���0��Ϊ���Ź������˹�������Ӱ�����ڳ�Ա
	int wallow_level;		//���Եȼ� npc
	int profit_level;		//����ȼ�
	int force_id;			//����������id, ��0��ʾ������ͬ�������
};

struct attack_msg
{
	attacker_info_t ainfo;		//�����ߵ���Ϣ

	float attack_range;		//�˴ι����ķ�Χ������������Ϣ���棩
	float short_range;		//�˴ι����Ľ������룬����ʱ������˺�����
	float short_range_adjust_factor;	//�������˺����� >1 ���� >0&&<1 ���� 1 ���䣬�����ܹ���ʱʹ��
	int target_layer_adjust_mask;	//0x00-�˺����� 0x01-����Ŀ���˺����� 0x02-����Ŀ���˺����� 0x04-ˮ��Ŀ���˺����� �ɸ�ѡ
	float target_layer_adjust_factor;	//�յ�Ŀ���˺������ >1
	int physic_damage;		//�����������˺���
	int attack_rate;		//��������������
	int magic_damage[MAGIC_CLASS];	//ħ���˺���
	int attacker_faction;		//��������Ӫ
	int target_faction;		//�����ߵĵ�����Ӫ(�Լ�����Ӫֻ�з��������Ӫ���ܱ���ǿ�ƹ����˺�)
	int crit_rate;
	int crit_damage_bonus;	//���Ⱪ���˺��ӳ�
	int attack_degree;		//��������
	int penetration;
	char attack_attr;		//�������ԣ���ֵ��enum ATTACK_ATTR����
	char force_attack;		//�Ƿ�ǿ�ƹ���
	char attacker_layer;		//�����ߴ���ʲôλ�� 0 ���� 1 ���� 2 ˮ�� 
	int _attack_state;		//0x01 �ػ�  0x02 �����Ż���
	short speed;
	char attacker_mode;		//�����ߵ�״̬(0x01 PK , 0x02 FREE, 0x04 �ѽ���PKģʽ)
	char is_invader;		//�Ƿ��ӹ���,������ǰ�ж���
	int hp_steal_rate;		//��Ѫ�ٷֱȣ�ֻ������������Ч
	int skill_id;			//�Ƿ��ܹ����� �����Ӧ�ļ��ܺ�
	int skill_modify[3];
	struct
	{
		int skill;
		int level;
	} attached_skill;
	int skill_enhance;		//��ǿʹ�ü��ܵ��˺���ֻ��Ŀ����npc����Ч
	int skill_enhance2;		//��ǿʹ�ü��ܵ��˺�������Ŀ��
	int vigour;				//����
	unsigned char section;  //���ܽ׶�
	int weapon_class;
	int feedback_filter;
	int anti_defense_degree; //��������ȼ�
	int anti_resistance_degree; // ���ӷ����ȼ�
	int highest_level;
	struct
	{
		int skill;
		int level;
	} infected_skill;
	enum 
	{
		PVP_ENABLE 	= 0x01,		//����PK����
		PVP_FREE   	= 0x02,		//����PK
		PVP_DURATION 	= 0x04,		//�Ѿ��ں����PK
		PVP_DUEL	= 0x08,		//�˴��Ǿ�������
		PVP_FEEDBACK_KILL = 0x10,	//ɱ����Һ���Ҫ��Ŀ�����Ϣ���͸��Լ�
	};

	enum ATTACK_ATTR
	{
		MAGIC_ATTACK = 0,		//��������
		PHYSIC_ATTACK = 1,		//��������
		MAGIC_ATTACK_GOLD = 2,		//����������
		MAGIC_ATTACK_WOOD = 3,		//��������ľ
		MAGIC_ATTACK_WATER = 4,		//��������ˮ
		MAGIC_ATTACK_FIRE = 5,		//����������
		MAGIC_ATTACK_EARTH = 6,		//����������
		PHYSIC_ATTACK_HIT_DEFINITE = 7,	//������������
	};
};

struct enchant_msg
{
	attacker_info_t ainfo;		//�����ߵ���Ϣ

	int attacker_faction;		//��������Ӫ
	int target_faction;		//�����ߵĵ�����Ӫ(�Լ�����Ӫֻ�з��������Ӫ���ܱ���ǿ�ƹ����˺�)
	float attack_range;
	int skill;
	int skill_reserved1;		//�����ڲ�ʹ��
	int skill_modify[3];
	int attack_degree;		//��������
	int penetration;
	char force_attack;		//�Ƿ�ǿ�ƹ���
	char skill_level;
	char attacker_layer;
	char helpful;			//0:���� 1:ף�� 2:����ף��
	char attacker_mode;		//�����ߵ�״̬(0 ��PK,1:PK)
	char is_invader;		//�Ƿ��ӹ���,������ǰ�ж���
	int _attack_state;		//0x01 �ػ�  0x02 �����Ż���  0x80 ���ߴ˴ι���
	int vigour;				//����
	unsigned char section;  //���ܽ׶�
	struct
	{
		int skill;
		int level;
	} infected_skill;
};

struct damage_entry
{
	float physic_damage;
	float magic_damage[MAGIC_CLASS];
	float distance;
};

#endif

