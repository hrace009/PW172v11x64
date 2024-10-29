//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include <vector>

#pragma pack(push, 1)
namespace GPARSER
{

	struct CSKILL /*cskill 172 data*/
	{
		typedef unsigned int ID;

		struct Range
		{
			char    type;
		};

		
		struct CSkill
		{
			void* SkillStub__vftable;			// base info
			ID				id;					// 唯一数字标识
			int				cls;				// 职业
			const wchar_t* name;               // 技能名字
			const char*		nativename;			// 技能名
			const char*		icon;				// 技能图标
			int				max_level;			// 技能最大级别
			char            type;               // 技能类别 1主动攻击 2主动辅助 3主动召唤 4被动 5激活

			// execute condition
			bool			allow_ride;			// 骑乘有效
			short           attr;               // 主技能属性, 1物理、2金、3木、4水、5火、6土 六选一 默认（物理）
			int             rank;               // 修真级别
			int             eventflag;
			char            is_senior;
			char			is_inherent;		//天生技能，不用学就能用
			char			is_movingcast;		//移动施法
			int             npcdelay;
			int             showorder;
			char            allow_forms;
			int             apcost;
			int             apgain;
			char            doenchant;
			char            dobless;
			int             arrowcost;
			std::vector<std::pair<unsigned int, int> > pre_skills;

			// execute condition
			bool            allow_land;             // 陆地有效
			bool            allow_air;              // 空中有效
			bool            allow_water;            // 水中有效
			bool			notuse_in_combat;	//战斗状态不可用
			int             restrict_corpse;        // 只对尸体有效
			bool            restrict_change;        // 是否必须变身后
			bool            restrict_attach;        // 是否必须附体后
			bool            auto_attack;            // 使用后是否自动攻击
			char            time_type;              // 瞬发技能
			char            long_range;
			char			posdouble;				// 空地选择
			int				clslimit;				// 职业限制

			int				commoncooldown;					//公共冷却mask bit0-4 技能冷却0-4 bit5-9 物品冷却0-4
			int				commoncooldowntime;			//冷却时间，单位毫秒

			int				itemcost;		//吟唱时所需物品 >0有效
			int				reserve1;
			//连续技
			int				combosk_preskill;
			int				combosk_interval;
			int				combosk_nobreak;

			const char* effect;
			const char* aerial_effect;

			Range range;

			bool has_stateattack;
			bool reserve2;

			void* reserve_offt1;
			void* reserve_offt2;

			char reserve3[13];
			
			std::vector<int> restrict_weapons;

			int				reserve5;
			int				reserve6;
			int				reserve7;

			bool ValidWeapon(int weapon) const
			{
				unsigned int i;
				for (i = 0; i < restrict_weapons.size(); i++)
				{
					if (weapon == restrict_weapons[i])
						return true;
				}
				if (i > 0 && i >= restrict_weapons.size())
					return false;
				return true;
			}
		};
		

		void* offt;
		CSkill * skill;

		int GetMpCost();
		int GetRequiredBook();
		int GetRequiredLevel();
		int GetRequiredMoney();
		int GetRequiredSp();
		int GetRequiredRealmLevel();
		int GetExecuteTime();
		int GetCoolingtime();
		void Destroy();

	};


	void SKILL_STUBS_PARSER(size_t count, size_t stubs_size);

}
#pragma pack(pop)
#endif
