#ifndef __ONLINEGAME_GS_OBJ_PROPERTY_H__
#define __ONLINEGAME_GS_OBJ_PROPERTY_H__ 
#include <cstring>
#include "config.h"

struct player_sec_level
{
	// 1-8 = 0 flag
	// 20-22 = 1 flag
	// 30-32 = 2 flag
	
	// 41 = 297 - good , 553 - evil
	// 42 = 553 - good , 554 - evil
	
	union
	{
		struct
		{
			char level; // sec level 1-42
			char flag; // 0 - 2
		};
		short value; // sec mask on save
	};
};

struct basic_prop
{
	short level;		//����
	player_sec_level sec;	//���漶��
	int exp;		//����ֵ
	int skill_point;	//ʣ��ļ��ܵ�
	int hp;			//��ǰhp
	int mp;			//��ǰmp
	int status_point;	//ʣ������Ե�
	int ap;			//��ǰŭ��ֵ
};

template <typename WRAPPER>
WRAPPER & operator >>(WRAPPER & wrapper, basic_prop &rhs)
{
	wrapper >> rhs.level >> rhs.exp >> rhs.skill_point;
	return wrapper;
}


template <typename WRAPPER>
WRAPPER & operator <<(WRAPPER & wrapper, basic_prop &rhs)
{
	wrapper << rhs.level << rhs.exp << rhs.skill_point;
	return wrapper;
}

//��չ���ԣ���ʱ���յ����Ӱ�������
struct extend_prop
{
	/* �������� */
	int vitality;		//��
	int energy;		//��
	int strength;		//��
	int agility;		//��
	int max_hp;		//���hp
	int max_mp;		//���mp
	int hp_gen;		//hp�ָ��ٶ�
	int mp_gen;		//mp�ָ��ٶ� 

	/* �˶��ٶ�*/
	float walk_speed;	//�����ٶ� ��λ  m/s
	float run_speed;	//�����ٶ� ��λ  m/s
	float swim_speed;	//��Ӿ�ٶ� ��λ  m/s
	float flight_speed;	//�����ٶ� ��λ  m/s

	/* ��������*/
	int attack;		//������ attack rate
	int damage_low;		//���damage
	int damage_high;	//�������damage
	int attack_speed;	//����ʱ���� ��tickΪ��λ
	float attack_range;	//������Χ
	struct 			//������������ħ���˺�
	{
		int damage_low;
		int damage_high;
	} addon_damage[MAGIC_CLASS];		
	int damage_magic_low;		//ħ����͹�����
	int damage_magic_high;		//ħ����߹�����

	/* �������� */	
	int resistance[MAGIC_CLASS];	//ħ������
	int defense;		//������
	int armor;		//�����ʣ�װ�׵ȼ���
	int max_ap;		//���ŭ��ֵ
};

	template <typename WRAPPER>
WRAPPER & operator <<(WRAPPER & wrapper, const extend_prop &rhs)
{
	wrapper.push_back(&rhs,sizeof(rhs));
	return wrapper;
}

	template <typename WRAPPER>
WRAPPER & operator >>(WRAPPER & wrapper, extend_prop &rhs)
{
	wrapper.pop_back(&rhs,sizeof(rhs));
	return wrapper;
}

//װ�������ı�����ǿ
struct item_prop
{
	short weapon_type;		//�����������melee,range,missile��
	short weapon_delay;		//������������ӳ�ʱ�� ��λ����һ��tick
	int attack_delay;		//�������ӳ�ʱ�䣬������ݲ���ֱ�Ӵ�����������
	int weapon_class;		//�����Ĺ�������
	int weapon_level;		//�����ļ���
	int damage_low;			//������͹�����
	int damage_high;		//������߹�����
	int damage_magic_low;		//ħ��������͹�����
	int damage_magic_high;		//ħ��������߹�����
	int attack_speed;		//���������ٶ�����
	float attack_range;		//����������Χ
	float short_range;		//��������С�������루����������뽫�ܵ������ͷ���
	/*
	   int attack;			//���������Ĺ���������
	 */
	//	int defense;			//װ�������ķ���
	//	int armor;			//װ����������
};

//�����Ż�����ʹ�õ�����
struct property_rune
{
	int rune_type;				// 0 ���������� 1 �Ƿ�������
	short rune_level_min;
	short rune_level_max;
	int rune_enhance;
};

//���ֲ��������ķǱ�����ǿ������Ϊ��ֵ
struct enhanced_param
{
	/*��������*/
	int max_mp;			//���mana��ֵ
	int max_hp;			//���������ֵ
	int hp_gen;
	int mp_gen;
	int vit;
	int eng;
	int agi;
	int str;

	/*��������*/
	//int weapon_damage;		//����������ֵ	��������ӳ�
	int damage_low;
	int damage_high;		//����������ֵ
	int attack;			//������
	int attack_speed;
	float attack_range;
	float walk_speed;
	float run_speed;
	float flight_speed;		//����
	
	int addon_damage[MAGIC_CLASS];	//������������ħ���˺�
	/*ħ������*/
	int resistance[MAGIC_CLASS];	//ħ������
	int magic_dmg_low;			//ħ��������ֵ
	int magic_dmg_high;			//ħ��������ֵ
	//	int magic_weapon_dmg;		//ħ������������ֵ ��������ӳ�

	/*��������*/	
	int defense;			//������ֵ(װ��)
	int armor;			//�����ֵ(װ��)

	float override_speed;		//�����ٶȣ�ֻ��½����Ч
};

//���ֲ��������ķǱ�����ǿ(���ǰٷֱ�)������Ϊ��ֵ
struct scale_enhanced_param
{
	int max_mp;			//���mana��ֵ
	int max_hp;			//���������ֵ

	int hp_gen;			//hp�ָ��ٶ����ӱ���
	int mp_gen;			//mp�ָ��ٶ����ӱ���

	int walk_speed;			//��·
	int run_speed;			//�ܲ�
	int swim_speed;			//��Ӿ	
	int flight_speed;		//����
	int mount_speed;		//����ٶ�

	int attack_speed;		//�����ٶ�

	int damage;			//����������ֵ
	int attack;			//������

	int base_damage;		//�ɱ������ݲ����İٷֱȼӳ�
	int base_magic;			//�ɱ������ݲ�����ħ�������ٷֱȼӳ�

	int magic_dmg;			//ħ��������ֵ
	int resistance[MAGIC_CLASS];	//ħ������

	int defense;			//������ֵ(װ��)
	int armor;			//�����ֵ(װ��)
};

class world_manager;
struct team_mutable_prop
{
	short level;
	char  combat_state;
	unsigned char sec_level;
	int hp;
	int mp;
	int max_hp;
	int max_mp;
	int world_tag;
	int plane_index;
	int wallow_level;
	int profit_level;
	int force_id;
	int reincarnation_times;
	team_mutable_prop(){}
	template <typename ACTIVE_IMP>
		explicit team_mutable_prop(ACTIVE_IMP * pImp)
		{
			Init(pImp);
		}

/*	team_mutable_prop(const basic_prop & bp, const extend_prop &ep,char cs, int tag)
		:level(bp.level),combat_state(cs),sec_level(bp.sec_level),hp(bp.hp),mp(bp.mp),max_hp(ep.max_hp),max_mp(ep.max_mp)
		{}*/
	int GetWorldTag();
	template <typename ACTIVE_IMP>
		void Init(ACTIVE_IMP * pImp)
		{
			const basic_prop & bp = pImp->_basic;
			const extend_prop &ep = pImp->_cur_prop;
			level = bp.level;
			combat_state = pImp->IsCombatState()?1:0;
			sec_level = bp.sec.level;
			hp = bp.hp;
			mp = bp.mp;
			max_hp = ep.max_hp;
			max_mp = ep.max_mp;
			world_tag = GetWorldTag();
			plane_index = pImp->_plane->w_plane_index;
			wallow_level = pImp->_wallow_level;
			profit_level = pImp->_profit_level;
			force_id = pImp->_player_force.GetForce();
			reincarnation_times = pImp->GetReincarnationTimes(); 
		}

	bool operator == (const team_mutable_prop & rhs)
	{
		return memcmp(this,&rhs,sizeof(rhs)) == 0;
	}

	bool operator != (const team_mutable_prop & rhs)
	{
		return memcmp(this,&rhs,sizeof(rhs));
	}
};

template <typename WRAPPER>
WRAPPER & operator <<(WRAPPER & wrapper, const team_mutable_prop & rhs)
{
	wrapper.push_back(&rhs,sizeof(rhs));
	return wrapper;
}

template <typename WRAPPER>
WRAPPER & operator >>(WRAPPER & wrapper, team_mutable_prop &rhs)
{
	wrapper.pop_back(&rhs,sizeof(rhs));
	return wrapper;
}

/*
struct  team_member_data
{
	int id;
	team_mutable_prop data;
	team_member_data()
	{}

	team_member_data(int member,const team_mutable_prop &prop):id(member),data(prop)
	{}
};
*/

struct plus_enhanced_param
{
	int damage;
	int magic_dmg;
	int defence;
	int resistance[MAGIC_CLASS];
	int max_hp;
};

template <typename WRAPPER>
WRAPPER & operator >>(WRAPPER & wrapper, plus_enhanced_param &rhs)
{
	wrapper.pop_back(&rhs,sizeof(rhs));
	return wrapper;
}


template <typename WRAPPER>
WRAPPER & operator <<(WRAPPER & wrapper, plus_enhanced_param &rhs)
{
	wrapper.push_back(&rhs,sizeof(rhs));
	return wrapper;
}
#endif
