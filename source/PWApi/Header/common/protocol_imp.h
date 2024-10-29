#ifndef __ONLINEGAME_COMMON_PROTOCOL_IMP_H__
#define __ONLINEGAME_COMMON_PROTOCOL_IMP_H__

#include "protocol.h"

struct gplayer;
struct gobject;
struct gmatter;
struct gnpc;
struct item_data;
class gactive_imp;
struct gactive_object;
class world_manager;
class item;

namespace  S2C
{
	namespace CMD
	{
		template <typename T>
		struct Type2Type
		{
			typedef T O_Type;
		};
		
		template <typename CMD>
		struct Make;

		template <>
		struct Make<single_data_header>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,int command)
			{
				return wrapper <<(unsigned short)command;
			}
		};

		template <>
		struct Make<multi_data_header>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,int command,int count)
			{
				return wrapper <<(unsigned short)command << (unsigned short)count;
			}
		};
		
		template <>
		struct Make<INFO::self_info_1>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gplayer *pPlayer,int exp,int sp)
			{
				unsigned int state = MakeObjectState(pPlayer) | pPlayer->object_state;
				wrapper << exp << sp << pPlayer->ID.id << pPlayer->pos 
				<< (unsigned short)pPlayer->crc
				<< (unsigned short)pPlayer->custom_crc 
				<< (unsigned char)pPlayer->dir << (unsigned char) pPlayer->sec_level << state << pPlayer->object_state2; 
				return MakePlayerExtendState(wrapper,pPlayer,state,pPlayer->object_state2);
			}
		};

		template <>
		struct Make<CMD::self_info_1>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gplayer *pPlayer,int exp,int sp)
			{
				Make<single_data_header>::From(wrapper,SELF_INFO_1);
				return Make<INFO::self_info_1>::From(wrapper,pPlayer,exp,sp);
			}
		};

		template <>
		struct Make<INFO::player_info_1>
		{

			template <typename WRAPPER>
			static bool From(WRAPPER & wrapper,gplayer * pObject)
			{
				if(pObject->gm_invisible) return false;
				unsigned int state = MakeObjectState(pObject) | pObject->object_state;
				//临时的数据改变
				wrapper << pObject->ID.id << pObject->pos 
				<< (unsigned short)pObject->crc 
				<< (unsigned short)pObject->custom_crc 
				<< (unsigned char)pObject->dir << (unsigned char) pObject->sec_level << state << pObject->object_state2; 
				MakePlayerExtendState(wrapper,pObject,state,pObject->object_state2);
				return true;
			}

			template <typename WRAPPER>
			static bool From(WRAPPER & wrapper,gplayer * pObject,const A3DVECTOR &newpos)
			{
				if(pObject->gm_invisible) return false;
				unsigned int state = MakeObjectState(pObject) | pObject->object_state;
				//临时的数据改变
				wrapper << pObject->ID.id << newpos
				<< (unsigned short)pObject->crc 
				<< (unsigned short)pObject->custom_crc 
				<< (unsigned char)pObject->dir << (unsigned char) pObject->sec_level << state << pObject->object_state2;  
				MakePlayerExtendState(wrapper,pObject,state,pObject->object_state2);
				return true;
			}
		};

		template <>
		struct Make<CMD::player_enter_slice>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gplayer* pPlayer,const A3DVECTOR & pos)
			{
				Make<single_data_header>::From(wrapper,PLAYER_ENTER_SLICE);
				Make<INFO::player_info_1>::From(wrapper,pPlayer,pos);
				//这里要注意，不能在隐身状态下使用
				ASSERT(pPlayer->gm_invisible == false);
				return wrapper;
			}
		};

		template <>
		struct Make<INFO::npc_info>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gnpc * pObject)
			{
				unsigned int state = MakeObjectState(pObject) | pObject->object_state;
				wrapper << pObject->ID.id << pObject->tid  << pObject->vis_tid << pObject->pos 
					<< (unsigned short)pObject->crc << (unsigned char)pObject->dir << state << pObject->object_state2; 
				return MakeNPCExtendState(wrapper,pObject,state);
			}

			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gnpc * pObject,const A3DVECTOR &newpos)
			{
				unsigned int state = MakeObjectState(pObject) | pObject->object_state;
				wrapper << pObject->ID.id << pObject->tid << pObject->vis_tid << newpos
					<< (unsigned short)pObject->crc << (unsigned char)pObject->dir << state << pObject->object_state2; 
				return MakeNPCExtendState(wrapper,pObject,state);
			}
		};

		template <>
		struct Make<CMD::npc_enter_slice>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gnpc * pNPC,const A3DVECTOR & pos)
			{
				Make<single_data_header>::From(wrapper,NPC_ENTER_SLICE);
				return Make<INFO::npc_info>::From(wrapper,pNPC,pos);
			}
		};

		template <>
		struct Make<CMD::npc_enter_world>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gnpc * pNPC)
			{
				Make<single_data_header>::From(wrapper,NPC_ENTER_WORLD);
				return Make<INFO::npc_info>::From(wrapper,pNPC);
			}
		};


		template <>
		struct Make<CMD::leave_slice>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gobject * pObject)
			{
				Make<single_data_header>::From(wrapper,OBJECT_LEAVE_SLICE);
				return wrapper << pObject->ID.id;
			}
		};

		template <>
		struct Make<CMD::notify_pos>
		{
			template <typename WRAPPER, typename KEY>
			static WRAPPER & From(WRAPPER & wrapper,const A3DVECTOR & pos, int tag, const KEY & key)
			{
				Make<single_data_header>::From(wrapper,OBJECT_NOTIFY_POS);
				return wrapper <<  pos << tag << key.key1;
			}
		};

		template<typename T>
		inline unsigned int MakeObjectState(T * pObject)
		{
			unsigned int state = 0;
			if(pObject->IsZombie()) state = gactive_object::STATE_ZOMBIE;
			if(pObject->extend_state || pObject->extend_state2 || pObject->extend_state3 || pObject->extend_state4 || pObject->extend_state5 || pObject->extend_state6 || pObject->extend_state7 || pObject->extend_state8  || pObject->extend_state9 ) state |= gactive_object::STATE_EXTEND_PROPERTY;
			if(pObject->effect_count) state |= gactive_object::STATE_EFFECT;
			return state;
		}


		template <typename WRAPPER>
		inline WRAPPER & MakeNPCExtendState(WRAPPER & ar, gnpc * pObject,unsigned int state)
		{
			if(state & gactive_object::STATE_EXTEND_PROPERTY)
			{
				ar << pObject->extend_state << pObject->extend_state2 << pObject->extend_state3 << pObject->extend_state4 << pObject->extend_state5 << pObject->extend_state6 << pObject->extend_state7 << pObject->extend_state8  << pObject->extend_state9 ;
			}
			if(state & gactive_object::STATE_NPC_PET)
			{
				ar << pObject->master_id;
			}
			if(state & gactive_object::STATE_NPC_NAME)
			{
				unsigned char name_size = pObject->name_size;
				if(name_size >= sizeof(pObject->npc_name)) name_size = sizeof(pObject->npc_name);
				ar << name_size;
				ar.push_back(pObject->npc_name,name_size);
			}
			if(state & gactive_object::STATE_MULTIOBJ_EFFECT)
			{
				int count = pObject->multiobj_effect_count;
				ar << count;
				for(int i=0; i<count; i++)
				{
					ar << pObject->multiobj_effect_list[i].target << pObject->multiobj_effect_list[i].type;
				}
			}
			if(state & gactive_object::STATE_NPC_MAFIA)
			{
				ar << pObject->mafia_id;
			}
			return ar;
		}

		template <typename WRAPPER>
		inline WRAPPER & MakePlayerExtendState(WRAPPER & ar, gplayer* pPlayer,unsigned int state,unsigned int state2)
		{
			if(state & gactive_object::STATE_ADV_MODE)
			{
				ar << pPlayer->adv_data1 << pPlayer->adv_data2;
			}

			if(state & gactive_object::STATE_SHAPE)
			{
				ar << pPlayer->shape_form;
			}
			if(state & gactive_object::STATE_EMOTE)
			{
				ar << pPlayer->emote_form;
			}
			if(state & gactive_object::STATE_EXTEND_PROPERTY)
			{
				ar << pPlayer->extend_state << pPlayer->extend_state2 << pPlayer->extend_state3 << pPlayer->extend_state4 << pPlayer->extend_state5 << pPlayer->extend_state6 << pPlayer->extend_state7 << pPlayer->extend_state8 << pPlayer->extend_state9;
			}
			if(state & gactive_object::STATE_MAFIA)
			{
				ar << pPlayer->id_mafia << pPlayer->rank_mafia;
			}

			if(state & gactive_object::STATE_MARKET)
			{
				ar << pPlayer->market_id;
			}

			if(state & gactive_object::STATE_EFFECT)
			{
				unsigned char count = pPlayer->effect_count;
				ar << count;
				if(count)
				{
					ar.push_back(pPlayer->effect_list, sizeof(short)* count);
				}
			}

			if(state & gactive_object::STATE_PARIAH)
			{
				ar << (char) pPlayer->pariah_state;
			}

			if(state & gactive_object::STATE_MOUNT)
			{
				ar << (unsigned short) pPlayer->mount_color;
				ar << (int) pPlayer->mount_id;
			}

			if(state & gactive_object::STATE_IN_BIND)
			{
				ar << (char) pPlayer->bind_type;
				ar << (int) pPlayer->bind_target;
			}

			if(state & gactive_object::STATE_SPOUSE)
			{
				ar << (int)pPlayer->spouse_id;
			}

			if(state & gactive_object::STATE_EQUIPDISABLED)
			{
				ar << pPlayer->disabled_equip_mask;
			}

			if(state & gactive_object::STATE_PLAYERFORCE)
			{
				ar << pPlayer->force_id;
			}

			if(state & gactive_object::STATE_MULTIOBJ_EFFECT)
			{
				int count = pPlayer->multiobj_effect_count;
				ar << count;
				for(int i=0; i<count; i++)
				{
					ar << pPlayer->multiobj_effect_list[i].target << pPlayer->multiobj_effect_list[i].type;
				}
			}
			
			if(state & gactive_object::STATE_COUNTRY)
			{
				ar << pPlayer->GetCountryId();	
			}

			if(state2 & gactive_object::STATE_TITLE)
			{
				ar << pPlayer->title_id;
			}

			if(state2 & gactive_object::STATE_REINCARNATION)
			{
				ar << pPlayer->reincarnation_times;
			}

			if(state2 & gactive_object::STATE_REALMLEVEL)
			{
				ar << pPlayer->realmlevel;
			}

			if(state2 & gactive_object::STATE_MAFIA_PVP_MASK)
			{
				ar << pPlayer->mafia_pvp_mask;
			}
		
			if(state2 & gactive_object::STATE_MNFACTION_MASK)
			{
				ar << pPlayer->mnfaction_id;
			}

			if(state2 & gactive_object::STATE_CASH_VIP_MASK)
			{
				ar << pPlayer->cash_vip_level << pPlayer->cash_vip_score;
			}

			if(state & gactive_object::STATE_FASHION_MODE)
			{
				unsigned char reserve = 0;
				ar << reserve;
			}
			return ar;
		}
		
		template<>
		struct Make<INFO::matter_info_1>
		{
			template <typename WRAPPER>
			static WRAPPER & From(WRAPPER & wrapper,gmatter * pMatter)
			{
				wrapper << pMatter->ID.id << pMatter->matter_type << pMatter->pos
					<< pMatter->dir << pMatter->dir1 << pMatter->rad
					<< pMatter->matter_state << pMatter->matter_value;
				return wrapper;
			}
		};
		template<>
		struct Make<INFO::move_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int id,const A3DVECTOR & target, 
					unsigned short use_time,unsigned short speed,unsigned char move_mode)
			{
				return wrapper << id << target << use_time << speed << move_mode;
			}
		};

		template<>
		struct Make<CMD::object_move>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj,
					const A3DVECTOR & target, unsigned short use_time,
					unsigned short speed,unsigned char move_mode)
			{
				Make<single_data_header>::From(wrapper,OBJECT_MOVE);
				return Make<INFO::move_info>::From(wrapper,pObj->ID.id,target,use_time,speed,move_mode);
			}
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int id,
					const A3DVECTOR & target, unsigned short use_time,
					unsigned short speed,unsigned char move_mode)
			{
				Make<single_data_header>::From(wrapper,OBJECT_MOVE);
				return Make<INFO::move_info>::From(wrapper,id,target,use_time,speed,move_mode);
			}
		};

		template<>
		struct Make<CMD::object_stop_move>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj,
					const A3DVECTOR & target, unsigned short speed,
					unsigned char dir, unsigned char move_mode)
			{
				Make<single_data_header>::From(wrapper,OBJECT_STOP_MOVE);
				return wrapper << pObj->ID.id << target << speed << dir << move_mode;
			}
		};

		template<>
		struct Make<CMD::player_enter_world>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gplayer * pPlayer)
			{
				Make<single_data_header>::From(wrapper,PLAYER_ENTER_WORLD);
				Make<INFO::player_info_1>::From(wrapper,pPlayer);
				ASSERT(pPlayer->gm_invisible == false);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::matter_enter_world>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gmatter * pMatter)
			{
				Make<single_data_header>::From(wrapper,MATTER_ENTER_WORLD);
				return Make<INFO::matter_info_1>::From(wrapper,pMatter);
			}
		};
		

		template <>
		struct Make<CMD::player_leave_world>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pPlayer)
			{
				Make<single_data_header>::From(wrapper,PLAYER_LEAVE_WORLD);
				return wrapper << pPlayer->ID.id;
			}
		};

		template <>
		struct Make<CMD::npc_dead>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gnpc * pNPC,const XID & killer)
			{
				Make<single_data_header>::From(wrapper,NPC_DEAD);
				return wrapper << pNPC->ID.id << killer.id;
			}
		};

		template <>
		struct Make<CMD::object_disappear>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj)
			{
				Make<single_data_header>::From(wrapper,OBJECT_DISAPPEAR);
				return wrapper << pObj->ID.id;
			}

			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & id)
			{
				Make<single_data_header>::From(wrapper,OBJECT_DISAPPEAR);
				return wrapper << id.id;
			}
		};
		template <>
		struct Make<CMD::object_start_attack>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, int target,unsigned char attack_speed)
			{
				Make<single_data_header>::From(wrapper,OBJECT_START_ATTACK);
				return wrapper << pObj->ID.id << target << attack_speed;
			}
		};

		template <>
		struct Make<CMD::self_start_attack>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int target,unsigned char attack_speed, unsigned short ammo_remain)
			{
				Make<single_data_header>::From(wrapper,SELF_START_ATTACK);
				return wrapper << target << ammo_remain << attack_speed;
			}
		};
		
		template <>
		struct Make<CMD::self_stop_attack>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int flag)
			{
				Make<single_data_header>::From(wrapper,SELF_STOP_ATTACK);
				return wrapper << flag;
			}
		};

		template <>
		struct Make<CMD::self_attack_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & id, int damage, int attack_flag,unsigned char speed)
			{
				Make<single_data_header>::From(wrapper,SELF_ATTACK_RESULT);
				return wrapper << id.id << damage << attack_flag << speed;
			}
		};

		template <>
		struct Make<CMD::self_skill_attack_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & id,int skill_id, int damage, int attack_flag,unsigned char speed,unsigned char section)
			{
				Make<single_data_header>::From(wrapper,SELF_SKILL_ATTACK_RESULT);
				return wrapper << id.id << skill_id << damage << attack_flag << speed << section;
			}
		};

		template <>
		struct Make<CMD::object_attack_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & attacker, const XID & target, int damage, int attack_flag , char speed)
			{
				Make<single_data_header>::From(wrapper,OBJECT_ATTACK_RESULT);
				return wrapper << attacker.id << target.id << damage << attack_flag  << speed;
			}
		};

		template <>
		struct Make<CMD::object_skill_attack_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & attacker, const XID & target,int skill_id, int damage,int attack_flag , char speed,unsigned char section)
			{
				Make<single_data_header>::From(wrapper,OBJECT_SKILL_ATTACK_RESULT);
				return wrapper << attacker.id << target.id << skill_id << damage << attack_flag << speed << section;
			}
		};

		template <>
		struct Make<CMD::hurt_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & id, int damage)
			{
				Make<single_data_header>::From(wrapper,HURT_RESULT);
				return wrapper << id.id << damage;
			}
		};

		template <>
		struct Make<CMD::error_msg>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper , int err_msg)
			{
				Make<single_data_header>::From(wrapper,ERROR_MESSAGE);
				return wrapper << err_msg;
			}
		};
		template <>
		struct Make<CMD::be_attacked>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & attacker,int damage,unsigned char eq_index,bool is_orange,int attack_flag, char speed)
			{
				Make<single_data_header>::From(wrapper,BE_ATTACKED);
				eq_index &= 0x7F;
				eq_index |= is_orange ? 0x80:0;
				return wrapper << attacker.id << damage << eq_index << attack_flag << speed;
			}
		};

		template <>
		struct Make<CMD::be_skill_attacked>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & attacker,int skill_id , int damage,unsigned char eq_index,bool is_orange, int attack_flag, char speed,unsigned char section)
			{
				Make<single_data_header>::From(wrapper,BE_SKILL_ATTACKED);
				eq_index &= 0x7F;
				eq_index |= is_orange ? 0x80:0;
				return wrapper << attacker.id << skill_id << damage << eq_index << attack_flag << speed << section;
			}
		};

		template <>
		struct Make<CMD::be_hurt>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & attacker,int damage,bool invader)
			{
				Make<single_data_header>::From(wrapper,BE_HURT);
				return wrapper << attacker.id << damage << (unsigned char)invader;
			}
		};
		
		template <>
		struct Make<CMD::player_dead>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & killer,const XID & player)
			{
				Make<single_data_header>::From(wrapper,PLAYER_DEAD);
				return wrapper << killer.id << player.id;
			}
		};

		template <>
		struct Make<CMD::be_killed>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj,const XID & killer)
			{
				Make<single_data_header>::From(wrapper,BE_KILLED);
				return wrapper << killer.id  << pObj->pos;
			}
		};

		template <>
		struct Make<CMD::player_revival>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper , gobject * pObj, short type)
			{
				Make<single_data_header>::From(wrapper,PLAYER_REVIVAL);
				return wrapper << pObj->ID.id << type << pObj->pos;
			}
		};

		template <>
		struct Make<CMD::player_pickup_money>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int amount, unsigned char is_silver)
			{
				Make<single_data_header>::From(wrapper,PICKUP_MONEY);
				return wrapper << amount << is_silver;
			}
		};

		template <>
		struct Make<CMD::player_pickup_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type, int expire_date, unsigned int amount,unsigned int slot_amount,unsigned char where,unsigned char index)
			{
				Make<single_data_header>::From(wrapper,PICKUP_ITEM);
				return wrapper << type << expire_date << amount << slot_amount << where << index;
			}
		};

		template<>
		struct Make<INFO::npc_info_00>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int hp,struct basic_prop & bp, struct extend_prop & ep, int targetid)
			{
				return wrapper << hp << ep.max_hp << targetid;
				//return wrapper << bp.level << bp.hp << ep.max_hp;
			}
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const INFO::npc_info_00 & info,int targetid)
			{
				return wrapper << info.hp << info.max_hp << targetid;
			}
		};

		template <>
		struct Make<CMD::npc_info_00>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & id,int hp,struct basic_prop & bp, struct extend_prop & ep, int targetid)
			{
				Make<single_data_header>::From(wrapper,NPC_INFO_00);
				wrapper << id.id;
				return Make<INFO::npc_info_00>::From(wrapper,hp, bp,ep, targetid);
			}
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & id,const INFO::npc_info_00 & info, int targetid)
			{
				Make<single_data_header>::From(wrapper,NPC_INFO_00);
				wrapper << id.id;
				return Make<INFO::npc_info_00>::From(wrapper,info, targetid); 
			}
		};


		template<>
		struct Make<INFO::player_info_00>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int hp, struct basic_prop & bp, struct extend_prop & ep, char combat_state, int targetid)
			{
				return wrapper <<  bp.level << combat_state << (unsigned char)bp.sec_level 
					<< hp << ep.max_hp << bp.mp << ep.max_mp << targetid << 0;
			}

			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const INFO::player_info_00 & info, int targetid)
			{
				wrapper.push_back(&info,sizeof(info),targetid);
				return wrapper;
			}
		};


		template <>
		struct Make<CMD::player_info_00>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & id,int hp,struct basic_prop & bp,struct extend_prop & ep,char combat_state, int targetid)
			{
				Make<single_data_header>::From(wrapper,PLAYER_INFO_00);
				wrapper << id.id;
				return Make<INFO::player_info_00>::From(wrapper, hp, bp,ep,combat_state,targetid);
			}
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & id,const INFO::player_info_00 & info,int targetid)
			{
				Make<single_data_header>::From(wrapper,PLAYER_INFO_00);
				wrapper << id.id;
				return Make<INFO::player_info_00>::From(wrapper, info, targetid);
			}
		};

		template<>
		struct Make<INFO::self_info_00>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,struct basic_prop & bp, struct extend_prop & ep,char combat_state, char cheat_mode)
			{
				if(cheat_mode)
				{
					return wrapper << bp.level << combat_state << (unsigned char) bp.sec_level 
						<< 1 << ep.max_hp << 1 << ep.max_mp << bp.exp << bp.skill_point << 0 << ep.max_ap;
				}
				else
				{
					return wrapper << bp.level << combat_state << (unsigned char) bp.sec_level 
						<< bp.hp << ep.max_hp << bp.mp << ep.max_mp << bp.exp << bp.skill_point << bp.ap << ep.max_ap;
				}
			}
		};

		template<>
		struct Make<CMD::self_info_00>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,struct basic_prop & bp, struct extend_prop & ep,char combat_state, char cheat_mode)
			{
				Make<single_data_header>::From(wrapper,SELF_INFO_00);
				return Make<INFO::self_info_00>::From(wrapper, bp,ep,combat_state,cheat_mode);
			}
		};
		
		template <>
		struct Make<CMD::OOS_list>
		{
			
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int size,int id_list[])
			{
				Make<single_data_header>::From(wrapper,OUT_OF_SIGHT_LIST);
				wrapper << size;
				for(unsigned int i = 0; i < size; ++i)
				{
					wrapper << id_list[i];
				}
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::receive_exp>
		{
			
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int exp,int sp)
			{
				Make<single_data_header>::From(wrapper,RECEIVE_EXP);
				return wrapper << exp << sp;
			}
		};
		
		template <>
		struct Make<CMD::level_up>
		{
			
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject *pObject)
			{
				Make<single_data_header>::From(wrapper,LEVEL_UP);
				return wrapper << pObject->ID.id;
			}
		};
		
		template <>
		struct Make<CMD::unselect>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper,UNSELECT);
			}
		};
		
		template <>
		struct Make<CMD::self_item_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char index,const item_data & data,unsigned short crc)
			{
				Make<single_data_header>::From(wrapper,SELF_ITEM_INFO);
				//if(data.proc_type & item::ITEM_PROC_TYPE_BIND) state = 1;
				//if(data.proc_type & 0x8000) state = 1;
				//int state = 0;
				//state = item::Proctype2State(data.proc_type);
				//wrapper << where << index << data.type << data.expire_date << state;
				wrapper << where << index << data.type << data.expire_date << data.proc_type;
				wrapper << data.count << crc;
				wrapper << (int)time(NULL) << (int)(time(NULL) + 62208000u) << (unsigned short)(data.content_length);
				wrapper.push_back(data.item_content,data.content_length);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::self_item_empty_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char index)
			{
				Make<single_data_header>::From(wrapper,SELF_ITEM_EMPTY_INFO);
				return wrapper << where << index;
			}
		};
		
		template <>
		struct Make<CMD::self_inventory_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char where, unsigned char inv_size, const void * data,unsigned int len)
			{
				Make<single_data_header>::From(wrapper,SELF_INVENTORY_DATA);
				wrapper << where << inv_size << len;
				wrapper.push_back(data,len);
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::self_inventory_detail_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char where, unsigned char inv_size, const void * data,unsigned int len)
			{
				Make<single_data_header>::From(wrapper,SELF_INVENTORY_DETAIL_DATA);
				wrapper << where << inv_size << len;
				wrapper.push_back(data,len);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::exchange_inventory_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char idx1,unsigned char idx2)
			{
				Make<single_data_header>::From(wrapper,EXCHANGE_INVENTORY_ITEM);
				return wrapper << idx1 << idx2;
			}
		};
		
		template <>
		struct Make<CMD::move_inventory_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char src,unsigned char dest,unsigned int count)
			{
				Make<single_data_header>::From(wrapper,MOVE_INVENTORY_ITEM);
				return wrapper << src << dest << count;
			}
		};
		
		template <>
		struct Make<CMD::player_drop_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char index, int type, unsigned int count, const char drop_type)
			{
				Make<single_data_header>::From(wrapper,PLAYER_DROP_ITEM);
				return wrapper << where << index << count << type << drop_type;
			}
		};
		
		template <>
		struct Make<CMD::exchange_equipment_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char index1, unsigned char index2)
			{
				Make<single_data_header>::From(wrapper,EXCHANGE_EQUIPMENT_ITEM);
				return wrapper << index1 << index2;
			}
		};

		template <>
		struct Make<CMD::equip_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char idx_inv, unsigned char idx_eq,unsigned int count_inv,unsigned int count_eq )
			{
				Make<single_data_header>::From(wrapper,EQUIP_ITEM);
				return wrapper << idx_inv << idx_eq << count_inv << count_eq;
			}
		};
		
		template <>
		struct Make<CMD::move_equipment_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char idx_inv, unsigned char idx_eq,unsigned int amount)
			{
				Make<single_data_header>::From(wrapper,MOVE_EQUIPMENT_ITEM);
				return wrapper << idx_inv << idx_eq << amount;
			}
		};
		
		template <>
		struct Make<CMD::self_get_property>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int status_point,const struct extend_prop & prop,int attack_degree, int defend_degree, int crit_rate, int crit_damage_bonus, int invisible_degree, int anti_invisible_degree, int penetration, int resilience, int vigour, int anti_def_degree, int anti_resist_degree, const extend_prop & base_prop, int highest_level, int hp, int max_hp )
			{
				Make<single_data_header>::From(wrapper,SELF_GET_EXT_PROPERTY);
				wrapper << status_point << attack_degree << defend_degree << crit_rate << crit_damage_bonus << invisible_degree << anti_invisible_degree << penetration << resilience << vigour << anti_def_degree << anti_resist_degree << prop << highest_level << base_prop;
				int reserve1 = 0; for (unsigned int i = 0; i < 10 ; i++)
				wrapper << reserve1;
				wrapper << hp << max_hp;
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::set_status_point>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper,unsigned int vit,unsigned int eng,unsigned int str,unsigned int agi,unsigned int remain)
				{
					Make<single_data_header>::From(wrapper,SET_STATUS_POINT);
					return wrapper << vit << eng << str << agi << remain;
				}
		};
		
		template <>
		struct Make<CMD::player_select_target>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper,int id)
				{
					Make<single_data_header>::From(wrapper,SELECT_TARGET);
					return wrapper << id;
				}
		};
		
		template <>
		struct Make<CMD::player_extprop_base>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper,gactive_imp * pObject)
				{
					Make<single_data_header>::From(wrapper,PLAYER_EXTPROP_BASE);
					const struct extend_prop & ep = pObject->_cur_prop;
					return wrapper << pObject->_parent->ID.id
							<< ep.vitality << ep.energy << ep.strength
							<< ep.agility<< ep.max_hp<< ep.max_mp 
							<< ep.hp_gen<< ep.mp_gen;
				}
		};
		
		template <>
		struct Make<CMD::player_extprop_move>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper,gactive_imp * pObject)
				{
					Make<single_data_header>::From(wrapper,PLAYER_EXTPROP_MOVE);
					const struct extend_prop & ep = pObject->_cur_prop;
					return wrapper << pObject->_parent->ID.id
							<< ep.walk_speed << ep.run_speed
							<< ep.swim_speed << ep.flight_speed;
				}
		};
		
		template <>
		struct Make<CMD::player_extprop_attack>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper,gactive_imp * pObject)
				{
					Make<single_data_header>::From(wrapper,PLAYER_EXTPROP_ATTACK);
					const struct extend_prop & ep = pObject->_cur_prop;
					wrapper << pObject->_parent->ID.id
						<< ep.attack << ep.damage_low
						<< ep.damage_high << ep.attack_speed
						<< ep.attack_range;
					wrapper << ep.addon_damage[0].damage_low << ep.addon_damage[0].damage_high;
					wrapper << ep.addon_damage[1].damage_low << ep.addon_damage[1].damage_high;
					wrapper << ep.addon_damage[2].damage_low << ep.addon_damage[2].damage_high;
					wrapper << ep.addon_damage[3].damage_low << ep.addon_damage[3].damage_high;
					wrapper << ep.addon_damage[4].damage_low << ep.addon_damage[4].damage_high;
					return wrapper << ep.damage_magic_low << ep.damage_magic_high;
				}
		};
		
		template <>
		struct Make<CMD::player_extprop_defense>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper,gactive_imp * pObject)
				{
					Make<single_data_header>::From(wrapper,PLAYER_EXTPROP_DEFENSE);
					const struct extend_prop & ep = pObject->_cur_prop;
					return wrapper << pObject->_parent->ID.id
						<< ep.resistance[0]
						<< ep.resistance[1]
						<< ep.resistance[2]
						<< ep.resistance[3]
						<< ep.resistance[4]
						<< ep.defense
						<< ep.armor;
				}
		};
		
		template <>
		struct Make<CMD::team_leader_invite>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & leader, int seq,short pickupflag)
			{
				Make<single_data_header>::From(wrapper,TEAM_LEADER_INVITE);
				return wrapper << leader.id << seq << pickupflag;
			}
		};
		
		template <>
		struct Make<CMD::team_reject_invite>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & member)
			{
				Make<single_data_header>::From(wrapper,TEAM_REJECT_INVITE);
				return wrapper << member.id;
			}
		};
		
		template <>
		struct Make<CMD::team_join_team>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & leader,short pickup_flag)
			{
				Make<single_data_header>::From(wrapper,TEAM_JOIN_TEAM);
				return wrapper << leader.id << pickup_flag;
			}
		};
		
		template <>
		struct Make<CMD::team_member_leave>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & leader,const XID & member,short type)
			{
				Make<single_data_header>::From(wrapper,TEAM_MEMBER_LEAVE);
				return wrapper << leader.id << member.id << type;
			}
		};
		
		template <>
		struct Make<CMD::team_leave_party>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & leader,short type)
			{
				Make<single_data_header>::From(wrapper,TEAM_LEAVE_PARTY);
				return wrapper << leader.id << type;
			}
		};
		
		template <>
		struct Make<CMD::team_new_member>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & member)
			{
				Make<single_data_header>::From(wrapper,TEAM_NEW_MEMBER);
				return wrapper << member.id;
			}
		};
		
		template <>
		struct Make<CMD::team_leader_cancel_party>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & leader)
			{
				Make<single_data_header>::From(wrapper,TEAM_LEADER_CANCEL_PARTY);
				return wrapper << leader.id;
			}
		};
		
		template <>
		struct Make<CMD::team_member_data>
		{
			template <typename WRAPPER,typename MEMBER_ENTRY>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & leader,unsigned char team_count, unsigned char data_count, const MEMBER_ENTRY ** list)
			{
				Make<single_data_header>::From(wrapper,TEAM_MEMBER_DATA);
				wrapper << team_count << data_count << leader.id;
				for(unsigned int i = 0; i < data_count; i ++)
				{
					const MEMBER_ENTRY *ent = list[i];
					wrapper << ent->id.id << ent->data.level
						<< ent->data.combat_state << ent->data.sec_level << (unsigned char)ent->data.reincarnation_times << (char)(ent->data.wallow_level -1)
						<< ent->data.hp << ent->data.mp << ent->data.max_hp 
						<< ent->data.max_mp << ent->data.force_id << ent->data.profit_level;
				}
				return wrapper;
			}
			template <typename WRAPPER,typename MEMBER_ENTRY>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & leader,unsigned char team_count, const MEMBER_ENTRY * list)
			{
				Make<single_data_header>::From(wrapper,TEAM_MEMBER_DATA);
				wrapper << team_count << team_count << leader.id;
				for(unsigned int i = 0; i < team_count; i ++)
				{
					const MEMBER_ENTRY &ent = list[i];
					wrapper << ent.id.id << ent.data.level 
						<< ent.data.combat_state 
						<< ent.data.sec_level << (unsigned char)ent.data.reincarnation_times << (char)(ent.data.wallow_level - 1) << ent.data.hp 
						<< ent.data.mp << ent.data.max_hp << ent.data.max_mp << ent.data.force_id << ent.data.profit_level;
				}
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::teammate_pos>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & id,const A3DVECTOR & pos,int tag,char same_plane)
			{
				Make<single_data_header>::From(wrapper,TEAMMATE_POS);
				return wrapper << id.id << pos << tag << same_plane;
			}
		};
		
		template <>
		struct Make<CMD::send_equipment_info>
		{
			template <typename WRAPPER, typename OCTETS>
			inline static WRAPPER & From(WRAPPER & wrapper,gplayer* pPlayer,uint64_t mask,OCTETS &data)
			{
				Make<single_data_header>::From(wrapper,EQUIPMENT_DATA);
				wrapper << (unsigned short)pPlayer->crc << pPlayer->ID.id << mask;
				
				int reserve = 0;
				for(unsigned int i = 0; i < 10; i ++)
					wrapper << reserve;
				if(unsigned int rst = data.size())
				{
					ASSERT(rst % 6 == 0);
					wrapper.push_back(data.begin(),rst);
				}
				return  wrapper ;
			}
		};
		
		template <>
		struct Make<CMD::equipment_info_changed>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gplayer* pPlayer,uint64_t mask_add,uint64_t mask_del,const void * buf, unsigned int size)
			{
				Make<single_data_header>::From(wrapper,EQUIPMENT_INFO_CHANGED);
				wrapper << (unsigned short)pPlayer->crc << pPlayer->ID.id << mask_add << mask_del;
				if(size)
				{
					ASSERT(size % 6 == 0);
					wrapper.push_back(buf,size);
				}
				return  wrapper ;
			}
		};
		
		template <>
		struct Make<CMD::equipment_damaged>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char index,char reason)
			{
				Make<single_data_header>::From(wrapper,EQUIPMENT_DAMAGED);
				return wrapper << index << reason;
			}
		};
		
		template <>
		struct Make<CMD::team_member_pickup>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & id, int type, int count)
			{
				Make<single_data_header>::From(wrapper,TEAM_MEMBER_PICKUP);
				return wrapper << id.id << type << count;
			}
		};
		
		template <>
		struct Make<CMD::npc_greeting>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & provider)
			{
				Make<single_data_header>::From(wrapper,NPC_GREETING);
				return wrapper << provider.id;
			}
		};
		
		template <>
		struct Make<CMD::npc_service_content>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & self,int type, const void * buf ,unsigned int size)
			{
				Make<single_data_header>::From(wrapper,NPC_SERVICE_CONTENT);
				wrapper << self.id << type << size;
				if(size) wrapper.push_back(buf,size);
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::player_purchase_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & FirstStep(WRAPPER & wrapper, unsigned int cost, unsigned int yinpiao, unsigned short all_amount)
			{
				Make<single_data_header>::From(wrapper,PURCHASE_ITEM);
				return wrapper << cost << yinpiao << (unsigned char)0 << all_amount ;
			}

			template <typename WRAPPER>
			inline static WRAPPER & FirstStep(WRAPPER & wrapper, unsigned int cost, unsigned int yinpiao, unsigned short all_amount,bool)
			{
				Make<single_data_header>::From(wrapper,PURCHASE_ITEM);
				return wrapper << cost << yinpiao << (unsigned char)1 << all_amount;
			}
			template <typename WRAPPER>
			inline static WRAPPER & SecondStep(WRAPPER & wrapper,const item_data *pData,unsigned int count, unsigned short inv_index)
			{
				return wrapper << pData->type << pData->expire_date << count << inv_index << (unsigned char)0;
			}

			template <typename WRAPPER>
			inline static WRAPPER & SecondStep(WRAPPER & wrapper,int type, int expire_date,unsigned int count, unsigned short inv_index)
			{
				return wrapper << type << expire_date << count << inv_index << (unsigned char)0;
			}

			template <typename WRAPPER>
			inline static WRAPPER & SecondStep(WRAPPER & wrapper,int type ,int expire_date,unsigned int count, unsigned short inv_index, unsigned char stall_index)
			{
				return wrapper << type << expire_date << count << inv_index << stall_index;
			}
		};
		
		template <>
		struct Make<CMD::item_to_money>
		{
			template < typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned short index, int type, unsigned int count,unsigned int money, unsigned int silver_money, unsigned int guild_money)
			{
				Make<single_data_header>::From(wrapper,ITEM_TO_MONEY);
				return wrapper << index << type << count << money << silver_money << guild_money;
			}
		};
		
		template <>
		struct Make<CMD::repair_all>
		{
			template < typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int cost)
			{
				Make<single_data_header>::From(wrapper,REPAIR_ALL);
				return wrapper << cost;
			}
		};
		
		template <>
		struct Make<CMD::repair>
		{
			template < typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char where,unsigned char index,unsigned int cost)
			{
				Make<single_data_header>::From(wrapper,REPAIR);
				return wrapper << where << index << cost;
			}
		};
		
		template <>
		struct Make<CMD::renew>
		{
			template < typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper,RENEW);
			}
		};
		
		template <>
		struct Make<CMD::spend_money>
		{
			template < typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int cost)
			{
				Make<single_data_header>::From(wrapper,SPEND_MONEY);
				return wrapper << cost;
			}
		};
		
		template <>
		struct Make<CMD::player_pickup_money_in_trade>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int amount)
			{
				Make<single_data_header>::From(wrapper,PICKUP_MONEY_IN_TRADE);
				return wrapper << amount;
			}
		};

		template <>
		struct Make<CMD::player_pickup_item_in_trade>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type, unsigned int amount)
			{
				Make<single_data_header>::From(wrapper,PICKUP_ITEM_IN_TRADE);
				return wrapper << type << amount;
			}
		};

		template <>
		struct Make<CMD::player_pickup_money_after_trade>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int amount)
			{
				Make<single_data_header>::From(wrapper,PICKUP_MONEY_AFTER_TRADE);
				return wrapper << amount;
			}
		};

		template <>
		struct Make<CMD::player_pickup_item_after_trade>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type,int expire_date, unsigned int amount,unsigned int slot_amount,unsigned short index)
			{
				Make<single_data_header>::From(wrapper,PICKUP_ITEM_AFTER_TRADE);
				return wrapper << type << expire_date << amount << slot_amount << index;
			}
		};
		
		template <>
		struct Make<CMD::get_own_money>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int amount,unsigned int capacity,unsigned int silver_amount,unsigned int guild_amount)
			{
				Make<single_data_header>::From(wrapper,GET_OWN_MONEY);
				return wrapper << amount << capacity << silver_amount << guild_amount;
			}
		};

		template<>
		struct Make<CMD::object_attack_once>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char proj_amount)
			{
				Make<single_data_header>::From(wrapper,OBJECT_ATTACK_ONCE);
				return wrapper << proj_amount;
			}
		};

		template<>
		struct Make<CMD::object_cast_skill>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & caster, const XID & target, int skill,unsigned short time, unsigned char level)
			{
				Make<single_data_header>::From(wrapper,OBJECT_CAST_SKILL);
				return wrapper << caster.id << target.id << skill << time << level;
			}
		};

		template<>
		struct Make<CMD::skill_interrupted>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & caster)
			{
				Make<single_data_header>::From(wrapper,SKILL_INTERRUPTED);
				return wrapper << caster.id;
			}
		};
		
		template<>
		struct Make<CMD::self_skill_interrupted>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char reason)
			{
				Make<single_data_header>::From(wrapper,SELF_SKILL_INTERRUPTED);
				return wrapper << reason;
			}
		};

		template<>
		struct Make<CMD::skill_perform>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper,SKILL_PERFORM);
			}
		};

		template <>
		struct Make<object_be_attacked>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & id)
			{
				Make<single_data_header>::From(wrapper,OBJECT_BE_ATTACKED);
				return wrapper << id.id;
			}
		};

		template <>
		struct Make<skill_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const void *buf, unsigned int size)
			{
				Make<single_data_header>::From(wrapper,SKILL_DATA);
				wrapper.push_back(buf,size);
				return wrapper;
			}
		};

		template <>
		struct Make<player_use_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,char where, unsigned char index, int item_id, unsigned short use_count)
			{
				Make<single_data_header>::From(wrapper,PLAYER_USE_ITEM);
				return wrapper << where << index << item_id << use_count;
			}
		};

		template <>
		struct Make<embed_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char chip, unsigned char equip)
			{
				Make<single_data_header>::From(wrapper,EMBED_ITEM);
				return wrapper << chip << equip;
			}
		};

		template <>
		struct Make<clear_embedded_chip>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned short equip_idx, unsigned int cost)
			{
				Make<single_data_header>::From(wrapper,CLEAR_EMBEDDED_CHIP);
				return wrapper << equip_idx << cost;
			}
		};

		template <>
		struct Make<cost_skill_point>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int sp)
			{
				Make<single_data_header>::From(wrapper,COST_SKILL_POINT);
				return wrapper << sp;
			}
		};

		template <>
		struct Make<learn_skill>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int skill,int level)
			{
				Make<single_data_header>::From(wrapper,LEARN_SKILL);
				return wrapper << skill << level;
			}
		};

		template <>
		struct Make<object_takeoff>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject *pObj)
			{
				Make<single_data_header>::From(wrapper,OBJECT_TAKEOFF);
				return wrapper << pObj->ID.id;
			}
		};

		template <>
		struct Make<object_landing>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject *pObj)
			{
				Make<single_data_header>::From(wrapper,OBJECT_LANDING);
				return wrapper << pObj->ID.id;
			}
		};

		template <>
		struct Make<flysword_time_capacity>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char index, int cur_time)
			{
				Make<single_data_header>::From(wrapper,FLYSWORD_TIME_CAPACITY);
				return wrapper << where << index << cur_time;
			}
		};
		
		template <>
		struct Make<CMD::player_obtain_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type, int expire_date, unsigned int amount,unsigned int slot_amount,unsigned char where,unsigned char index)
			{
				Make<single_data_header>::From(wrapper,OBTAIN_ITEM);
				return wrapper << type << expire_date << amount << slot_amount << where << index;
			}
		};
		
		template <>
		struct Make<CMD::produce_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type, unsigned short use_time,unsigned short count)
			{
				Make<single_data_header>::From(wrapper,PRODUCE_START);
				return wrapper << use_time << count << type ;
			}
		};
		
		template <>
		struct Make<CMD::produce_once>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type, unsigned int amount,unsigned int slot_amount,unsigned char where,unsigned char index)
			{
				Make<single_data_header>::From(wrapper,PRODUCE_ONCE);
				return wrapper << type << amount << slot_amount << where << index;
			}
		};

		template <>
		struct Make<CMD::produce_end>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper,PRODUCE_END);
			}
		};
		
		template <>
		struct Make<CMD::decompose_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned short use_time, int type)
			{
				Make<single_data_header>::From(wrapper,DECOMPOSE_START);
				return wrapper << use_time << type;
			}
		};

		template <>
		struct Make<CMD::decompose_end>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper,DECOMPOSE_END);
			}
		};
		
		template <>
		struct Make<CMD::task_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const void * active,unsigned int asize, const void * finished, unsigned int fsize, const void * finished_time, unsigned int tsize, const void * finished_count, unsigned int csize, const void * storage_task, unsigned int ssize)
			{
				Make<single_data_header>::From(wrapper,TASK_DATA);
				wrapper << asize;
				wrapper.push_back(active,asize);
				wrapper << fsize;
				wrapper.push_back(finished,fsize);
				wrapper << tsize;
				wrapper.push_back(finished_time,tsize);
				wrapper << csize;
				wrapper.push_back(finished_count,csize);
				wrapper << ssize;
				wrapper.push_back(storage_task,ssize);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::task_var_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const void * buf,unsigned int size)
			{
				Make<single_data_header>::From(wrapper,TASK_VAR_DATA);
				wrapper << size;
				wrapper.push_back(buf,size);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::object_start_use>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gplayer * pPlayer,int type, unsigned short time)
			{
				Make<single_data_header>::From(wrapper,OBJECT_START_USE);
				return wrapper << pPlayer->ID.id << type << time;
			}
		};
		
		template <>
		struct Make<CMD::object_cancel_use>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gplayer * pPlayer)
			{
				Make<single_data_header>::From(wrapper,OBJECT_CANCEL_USE);
				return wrapper << pPlayer->ID.id;
			}
		};

		template <>
		struct Make<CMD::object_use_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gplayer * pPlayer,int type)
			{
				Make<single_data_header>::From(wrapper,OBJECT_USE_ITEM);
				return wrapper << pPlayer->ID.id  << type;
			}
		};

		template <>
		struct Make<CMD::object_start_use_with_target>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gplayer * pPlayer,int type, unsigned short time,const XID & target)
			{
				Make<single_data_header>::From(wrapper,OBJECT_START_USE_WITH_TARGET);
				return wrapper << pPlayer->ID.id << target.id << type << time;
			}
		};
		
		template <>
		struct Make<CMD::object_sit_down>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj)
			{
				Make<single_data_header>::From(wrapper,OBJECT_SIT_DOWN);
				//return wrapper << pObj->ID.id << pObj->pos; $$$$$$$4
				return wrapper << pObj->ID.id;
			}
		};

		template <>
		struct Make<CMD::object_stand_up>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj)
			{
				Make<single_data_header>::From(wrapper,OBJECT_STAND_UP);
				return wrapper << pObj->ID.id;
			}
		};
		template <>
		struct Make<CMD::object_do_emote>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj,unsigned short emotion)
			{
				Make<single_data_header>::From(wrapper, OBJECT_DO_EMOTE);
				return wrapper << pObj->ID.id << emotion ;
			}
		};

		template <>
		struct Make<CMD::server_timestamp>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int timestamp , int timezone, int lua_version)
			{
				Make<single_data_header>::From(wrapper, SERVER_TIMESTAMP );
				return wrapper << timestamp << timezone << lua_version;
			}
		};

		template <>
		struct Make<CMD::notify_root>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject *pObject)
			{
				Make<single_data_header>::From(wrapper, NOTIFY_ROOT);
				return wrapper << pObject->ID.id << pObject->pos;
			}
		};

		template <>
		struct Make<CMD::self_notify_root>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject *pObject,unsigned char type)
			{
				Make<single_data_header>::From(wrapper, SELF_NOTIFY_ROOT);
				return wrapper << pObject->pos << type;
			}
		};

		template <>
		struct Make<CMD::dispel_root>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper , unsigned char type)
			{
				return Make<single_data_header>::From(wrapper, DISPEL_ROOT) << type;
			}
		};

		template <>
		struct Make<CMD::invader_rise>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj)
			{
				Make<single_data_header>::From(wrapper, INVADER_RISE);
				return wrapper << pObj->ID.id;
			}
		};


		template <>
		struct Make<CMD::pariah_rise>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gplayer * pObj)
			{
				Make<single_data_header>::From(wrapper, PARIAH_RISE);
				return wrapper << pObj->ID.id << (char)(pObj->pariah_state);
			}
		};

		template <>
		struct Make<CMD::invader_fade>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj)
			{
				Make<single_data_header>::From(wrapper, INVADER_FADE);
				return wrapper << pObj->ID.id;
			}
		};

		template <>
		struct Make<CMD::self_stop_skill>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper, SELF_STOP_SKILL);
			}
		};
		

		template <>
		struct Make<CMD::update_visible_state>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject *pObj,unsigned int state, unsigned int state2, unsigned int state3, unsigned int state4, unsigned int state5, unsigned int state6, unsigned int state7, unsigned int state8, unsigned int state9)
			{
				Make<single_data_header>::From(wrapper, UPDATE_VISIBLE_STATE);
				return wrapper << pObj->ID.id << state << state2 << state3 << state4 << state5 << state6 << state7 << state8 << state9;
			}
		};
/*
		gplayer * x_get_player(int roleid)
		{
			int index;
			world_manager::GetInstance()->FindPlayer(roleid,index);
			if(!pPlayer) return 0;
			return pPlayer;
		}
*/


		template <>
		struct Make<CMD::object_state_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & id,unsigned short *state_list,unsigned int state_count,int * param_list,unsigned int param_count  
			, int * x_it )
			{
				Make<single_data_header>::From(wrapper, OBJECT_STATE_NOTIFY);
				unsigned short count = state_count;
				wrapper << id.id  << count;
				if(count) wrapper.push_back(state_list,((int)count)*sizeof(unsigned short));
				
				count = param_count;
				wrapper << count;
				if(count) wrapper.push_back(param_list,((int)count)*sizeof(int));
				
				count = state_count;
				wrapper << count;
				if(count) wrapper.push_back(x_it,((int)count)*(sizeof(int)*2));
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::player_gather_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & player, int mine,unsigned char use_time)
			{
				Make<single_data_header>::From(wrapper, PLAYER_GATHER_START);
				return wrapper << player.id << mine  << use_time;
			}
		};

		template <>
		struct Make<CMD::player_gather_stop>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & player)
			{
				Make<single_data_header>::From(wrapper, PLAYER_GATHER_STOP);
				return wrapper << player.id;
			}
		};

		template <>
		struct Make<CMD::trashbox_passwd_changed>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char has_passwd)
			{
				Make<single_data_header>::From(wrapper, TRASHBOX_PASSWD_CHANGED);
				return wrapper << has_passwd;
			}
		};

		template <>
		struct Make<CMD::trashbox_passwd_state>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char has_passwd)
			{
				Make<single_data_header>::From(wrapper, TRASHBOX_PASSWD_STATE);
				return wrapper << has_passwd;
			}
		};

		template <>
		struct Make<CMD::trashbox_open>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,char is_usertrashbox, unsigned short size,unsigned short size2, unsigned short size3)
			{
				return Make<single_data_header>::From(wrapper, TRASHBOX_OPEN) << is_usertrashbox << size << size2 << size3;
			}
		};

		template <>
		struct Make<CMD::trashbox_close>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,char is_usertrashbox)
			{
				return Make<single_data_header>::From(wrapper, TRASHBOX_CLOSE) << is_usertrashbox;
			}
		};

		template <>
		struct Make<CMD::trashbox_wealth>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char is_usertrashbox, unsigned int amount)
			{
				Make<single_data_header>::From(wrapper, TRASHBOX_WEALTH);
				return wrapper << is_usertrashbox << amount;
			}
		};

		template <>
		struct Make<CMD::exchange_trashbox_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char idx1,unsigned char idx2)
			{
				Make<single_data_header>::From(wrapper, EXCHANGE_TRASHBOX_ITEM);
				return wrapper << where << idx1 << idx2;
			}
		};

		template <>
		struct Make<CMD::move_trashbox_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char src,unsigned char dest, unsigned int amount)
			{
				Make<single_data_header>::From(wrapper, MOVE_TRASHBOX_ITEM);
				return wrapper << where << src << dest << amount;
			}
		};

		template <>
		struct Make<CMD::exchange_trashbox_inventory>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char idx_tra,unsigned char idx_inv)
			{
				Make<single_data_header>::From(wrapper, EXCHANGE_TRASHBOX_INVENTORY);
				return wrapper <<  where << idx_tra << idx_inv;
			}
		};

		template <>
		struct Make<CMD::inventory_item_to_trash>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char src,unsigned char dest, unsigned int amount)
			{
				Make<single_data_header>::From(wrapper, INVENTORY_ITEM_TO_TRASH);
				return wrapper <<  where << src << dest << amount;
			}
		};

		template <>
		struct Make<CMD::trash_item_to_inventory>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char where, unsigned char src,unsigned char dest, unsigned int amount)
			{
				Make<single_data_header>::From(wrapper, TRASH_ITEM_TO_INVENTORY );
				return wrapper <<  where << src << dest << amount;
			}
		};

		template <>
		struct Make<CMD::exchange_trash_money>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,char is_usertrashbox,int inv_money,int tra_money)
			{
				Make<single_data_header>::From(wrapper, EXCHANGE_TRASH_MONEY );
				return wrapper << is_usertrashbox << inv_money << tra_money;
			}
		};

		template <>
		struct Make<CMD::enchant_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj, const XID & caster, int skill, char level, char orange_name,int at_state,unsigned char section)
			{
				Make<single_data_header>::From(wrapper, ENCHANT_RESULT);
				return wrapper << caster.id << pObj->ID.id << skill << level << orange_name << at_state << section;
			}
		};

		template <>
		struct Make<CMD::object_do_action>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj,unsigned char action)
			{
				Make<single_data_header>::From(wrapper, OBJECT_DO_ACTION);
				return wrapper << pObj->ID.id << action;
			}
		};

		template <>
		struct Make<CMD::player_set_adv_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj,int data1,int data2)
			{
				Make<single_data_header>::From(wrapper, PLAYER_SET_ADV_DATA);
				return wrapper << pObj->ID.id << data1 << data2;
			}
		};

		template <>
		struct Make<CMD::player_clr_adv_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj)
			{
				Make<single_data_header>::From(wrapper, PLAYER_CLR_ADV_DATA);
				return wrapper << pObj->ID.id;
			}
		};

		template <>
		struct Make<CMD::player_in_team>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj,unsigned char state)
			{
				Make<single_data_header>::From(wrapper, PLAYER_IN_TEAM);
				return wrapper << pObj->ID.id << state;
			}
		};
		
		template <>
		struct Make<CMD::team_apply_request>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int id)
			{
				Make<single_data_header>::From(wrapper, TEAM_APPLY_REQUEST);
				return wrapper << id;
			}
		};

		template <>
		struct Make<CMD::object_do_emote_restore>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj,unsigned short emotion)
			{
				Make<single_data_header>::From(wrapper, OBJECT_DO_EMOTE_RESTORE);
				return wrapper << pObj->ID.id << emotion ;
			}
		};
		
		template <>
		struct Make<CMD::concurrent_emote_request>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int id, unsigned short action)
			{
				Make<single_data_header>::From(wrapper, CONCURRENT_EMOTE_REQUEST);
				return wrapper << id << action;
			}
		};

		template <>
		struct Make<CMD::do_concurrent_emote>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int self_id, int id, unsigned short action)
			{
				Make<single_data_header>::From(wrapper, DO_CONCURRENT_EMOTE);
				return wrapper << self_id << id << action;
			}
		};

		template <>
		struct Make<CMD::matter_pickup>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj,int who)
			{
				Make<single_data_header>::From(wrapper,MATTER_PICKUP);
				return wrapper << pObj->ID.id << who;
			}
		};

		template <>
		struct Make<CMD::mafia_info_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gplayer * pObj)
			{
				Make<single_data_header>::From(wrapper,MAFIA_INFO_NOTIFY);
				return wrapper << pObj->ID.id << pObj->id_mafia << pObj->rank_mafia << pObj->mnfaction_id;
			}
		};

		template <>
		struct Make<CMD::mafia_trade_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper,MAFIA_TRADE_START);
			}
		};

		template <>
		struct Make<CMD::mafia_trade_end>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper,MAFIA_TRADE_END);
			}
		};

		template <>
		struct Make<CMD::task_deliver_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type, int expire_date,unsigned int amount,unsigned int slot_amount,unsigned char where,unsigned char index)
			{
				Make<single_data_header>::From(wrapper,TASK_DELIVER_ITEM);
				return wrapper << type << expire_date << amount << slot_amount << where << index;
			}
		};

		template <>
		struct Make<CMD::task_deliver_reputaion>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int delta, int reputation) 
			{
				Make<single_data_header>::From(wrapper,TASK_DELIVER_REPUTATION);
				return wrapper << delta << reputation;
			}
		};

		template <>
		struct Make<CMD::task_deliver_exp>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int exp, int sp) 
			{
				Make<single_data_header>::From(wrapper,TASK_DELIVER_EXP);
				return wrapper << exp << sp;
			}
		};

		template <>
		struct Make<CMD::task_deliver_money>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int delta, unsigned int cur_money)
			{
				Make<single_data_header>::From(wrapper,TASK_DELIVER_MONEY);
				return wrapper << delta << cur_money;
			}
		};

		template <>
		struct Make<CMD::task_deliver_level2>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gplayer * pPlayer, int level2)
			{
				Make<single_data_header>::From(wrapper,TASK_DELIVER_LEVEL2);
				return wrapper << pPlayer->ID.id <<  level2;
			}
		};

		template <>
		struct Make<CMD::player_reputation>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int reputation)
			{
				Make<single_data_header>::From(wrapper,PLAYER_REPUTATION);
				return wrapper << reputation;
			}
		};
		
		template <>
		struct Make<CMD::identify_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,char index, char result)
			{
				Make<single_data_header>::From(wrapper,IDENTIFY_RESULT);
				return wrapper << index << result;
			}
		};

		template <>
		struct Make<CMD::player_change_shape>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj,char shape)
			{
				Make<single_data_header>::From(wrapper,PLAYER_CHANGE_SHAPE);
				return wrapper << pObj->ID.id << shape;
			}
		};

		template <>
		struct Make<CMD::object_enter_sanctuary>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id)
			{
				Make<single_data_header>::From(wrapper,OBJECT_ENTER_SANCTUARY);
				return wrapper << id;
			}
		};
		
		template <>
		struct Make<CMD::object_leave_sanctuary>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id)
			{
				Make<single_data_header>::From(wrapper,OBJECT_LEAVE_SANCTUARY);
				return wrapper << id;
			}
		};

		template <>
		struct Make<INFO::market_goods>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return wrapper << (int)0;
			}

			template <typename WRAPPER>
			inline static WRAPPER & SellItem(WRAPPER & wrapper, int type, int count, unsigned int price, const item_data & data)
			{
				ASSERT(type == data.type);
				int reserve = 0;
				wrapper << type << count << price << data.expire_date << reserve ;
				wrapper << (unsigned short)(data.content_length);
				wrapper.push_back(data.item_content,data.content_length);
				return wrapper;
			}

			template <typename WRAPPER>
			inline static WRAPPER & BuyItem(WRAPPER & wrapper, int type, int count, unsigned int price)
			{
				return wrapper << type << -count << price;
			}
		};

		template <>
		struct Make<CMD::player_market_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, int market_id, unsigned int count)
			{
				Make<single_data_header>::From(wrapper,PLAYER_MARKET_INFO);
				return wrapper << pObj->ID.id << market_id << count;
			}
			
		};

		template <>
		struct Make<CMD::player_open_market>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, unsigned char market_crc,const char * name, unsigned int len)
			{
				Make<single_data_header>::From(wrapper,PLAYER_OPEN_MARKET);
				wrapper << pObj->ID.id << market_crc; 
				if(len > 127) len = 127;
				wrapper << (unsigned char) len;
				wrapper.push_back(name,len);
				return wrapper;
			}
			
		};

		template <>
		struct Make<CMD::self_open_market>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char count, unsigned char offline)
			{
				Make<single_data_header>::From(wrapper,SELF_OPEN_MARKET);
				return wrapper << count << offline;
			}

			template <typename WRAPPER>
			inline static WRAPPER & AddGoods(WRAPPER & wrapper, int type, unsigned short index, unsigned int count ,unsigned int price)
			{
				return wrapper << type << index << count << price;
			}
		};

		template <>
		struct Make<CMD::player_cancel_market>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj)
			{
				Make<single_data_header>::From(wrapper,PLAYER_CANCEL_MARKET);
				return wrapper << pObj->ID.id;
			}
		};

		template <>
		struct Make<CMD::player_market_trade_success>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int trader)
			{
				Make<single_data_header>::From(wrapper,PLAYER_MARKET_TRADE_SUCCESS);
				return wrapper << trader;
			}
		};
		template <>
		struct Make<CMD::player_market_name>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gplayer * pPlayer,const char * name, unsigned int name_len)
			{
				Make<single_data_header>::From(wrapper,PLAYER_MARKET_NAME);
				wrapper << pPlayer->ID.id << pPlayer->market_id;
				if(name_len > 127) name_len = 127;
				wrapper << (unsigned char) name_len;
				wrapper.push_back(name,name_len);
				return wrapper;
			};
		};

		template <>
		struct Make<CMD::player_start_travel>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gplayer * pPlayer,unsigned char vehicle)
			{
				Make<single_data_header>::From(wrapper,PLAYER_START_TRAVEL);
				return wrapper << pPlayer->ID.id << vehicle;
			};
		};

		template <>
		struct Make<CMD::self_start_travel>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, float speed, const A3DVECTOR & dest, int line_no, unsigned char vehicle)
			{
				Make<single_data_header>::From(wrapper,SELF_START_TRAVEL);
				return wrapper << speed << dest << line_no << vehicle;
			};
		};

		template <>
		struct Make<CMD::player_complete_travel>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gplayer * pPlayer, unsigned char vehicle)
			{
				Make<single_data_header>::From(wrapper,PLAYER_COMPLETE_TRAVEL);
				return wrapper <<  pPlayer->ID.id << vehicle; 
			};
		};
		
		template <>
		struct Make<CMD::gm_toggle_invincible>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char tmp)
			{
				Make<single_data_header>::From(wrapper,GM_TOGGLE_INVINCIBLE);
				return wrapper <<  tmp;
			};
		};

		template <>
		struct Make<CMD::gm_toggle_invisible>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char tmp)
			{
				Make<single_data_header>::From(wrapper,GM_TOGGLE_INVISIBLE);
				return wrapper <<  tmp;
			};
		};

		template <>
		struct Make<CMD::self_trace_cur_pos>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const A3DVECTOR & pos, unsigned short seq)
			{
				Make<single_data_header>::From(wrapper,SELF_TRACE_CUR_POS);
				return wrapper <<  pos << seq;
			};
		};

		template <>
		struct Make<CMD::object_cast_instant_skill>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, const XID & target, int skill, unsigned char level)
			{
				Make<single_data_header>::From(wrapper,OBJECT_CAST_INSTANT_SKILL);
				return wrapper << pObj->ID.id << target.id << skill << level;
			};
		};

		template <>
		struct Make<CMD::activate_waypoint>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned short waypoint)
			{
				Make<single_data_header>::From(wrapper,ACTIVATE_WAYPOINT);
				return wrapper << waypoint;
			};
		};

		template <>
		struct Make<CMD::player_waypoint_list>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const unsigned short * wlist,unsigned int count)
			{
				Make<single_data_header>::From(wrapper,PLAYER_WAYPOINT_LIST);
				wrapper << count;
				if(count) wrapper.push_back(wlist,sizeof(unsigned short)* count);
				return wrapper;
			};
		};

		template <>
		struct Make<CMD::unlock_inventory_slot>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char where, unsigned short index)
			{
				Make<single_data_header>::From(wrapper,UNLOCK_INVENTORY_SLOT);
				return wrapper << where << index;
			};
		};

		template <>
		struct Make<CMD::team_invite_timeout>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int who)
			{
				Make<single_data_header>::From(wrapper,TEAM_INVITE_PLAYER_TIMEOUT);
				return wrapper << who;
			};
		};

		template <>
		struct Make<CMD::player_enable_pvp>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, char type)
			{
				Make<single_data_header>::From(wrapper,PLAYER_ENABLE_PVP);
				return wrapper << pObj->ID.id << type;
			};
		};

		template <>
		struct Make<CMD::player_disable_pvp>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, char type)
			{
				Make<single_data_header>::From(wrapper,PLAYER_DISABLE_PVP);
				return wrapper << pObj->ID.id << type;
			};
		};

		template <>
		struct Make<CMD::player_pvp_cooldown>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int cooldown, int max_cooldown)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PVP_COOLDOWN);
				return wrapper << cooldown << max_cooldown;
			};
		};

		template <>
		struct Make<CMD::cooldown_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const void * buf, unsigned int size)
			{
				Make<single_data_header>::From(wrapper,COOLDOWN_DATA);
				return wrapper.push_back(buf,size);
			};
		};

		template <>
		struct Make<CMD::skill_ability_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, int ability)
			{
				Make<single_data_header>::From(wrapper, SKILL_ABILITY_NOTFIY);
				return wrapper << id << ability;
			};
		};

		template <>
		struct Make<CMD::personal_market_available>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper, PERSONAL_MARKET_AVAILABLE);
			};
		};

		template <>
		struct Make<CMD::breath_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int breath, int breath_capacity)
			{
				Make<single_data_header>::From(wrapper, BREATH_DATA);
				return wrapper << breath << breath_capacity;
			};
		};

		template <>
		struct Make<CMD::player_stop_dive>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper, PLAYER_STOP_DIVE);
			};
		};

		template <>
		struct Make<CMD::trade_away_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int buyer,short inv_idx,int type, unsigned int count )
			{
				Make<single_data_header>::From(wrapper, TRADE_AWAY_ITEM);
				return wrapper << inv_idx << type << count << buyer;
			};
		};

		template <>
		struct Make<CMD::player_enable_fashion_mode>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject * pObj, unsigned char is_enable, unsigned char new_model)
			{
				Make<single_data_header>::From(wrapper, PLAYER_ENABLE_FASHION_MODE);
				return wrapper << pObj->ID.id << is_enable << new_model;
			};
		};

		template <>
		struct Make<CMD::enable_free_pvp_mode>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char is_enable)
			{
				Make<single_data_header>::From(wrapper, ENABLE_FREE_PVP_MODE);
				return wrapper << is_enable;
			}
		};

		template <>
		struct Make<CMD::object_is_invalid>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id)
			{
				Make<single_data_header>::From(wrapper, OBJECT_IS_INVALID);
				return wrapper << id;
			}
		};

		template <>
		struct Make<CMD::player_enable_effect>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, short effect)
			{
				Make<single_data_header>::From(wrapper, PLAYER_ENABLE_EFFECT);
				return wrapper << effect << id;
			}
		};

		template <>
		struct Make<CMD::player_disable_effect>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, short effect)
			{
				Make<single_data_header>::From(wrapper, PLAYER_DISABLE_EFFECT);
				return wrapper << effect << id;
			}
		};

		template <>
		struct Make<CMD::enable_resurrect_state>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, float exp_reduce)
			{
				Make<single_data_header>::From(wrapper, ENABLE_RESURRECT_STATE);
				return wrapper << exp_reduce;
			}
		};

		template <>
		struct Make<CMD::set_cooldown>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int time)
			{
				Make<single_data_header>::From(wrapper, SET_COOLDOWN);
				return wrapper << index << time;
			}
		};

		template <>
		struct Make<CMD::change_team_leader>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & old_leader, const XID & new_leader)
			{
				Make<single_data_header>::From(wrapper, CHANGE_TEAM_LEADER);
				return wrapper << old_leader.id << new_leader.id;
			}
		};

		template <>
		struct Make<CMD::kickout_instance>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int tag, char reason, int timeout)
			{
				Make<single_data_header>::From(wrapper, KICKOUT_INSTANCE);
				return wrapper << tag << reason << timeout;
			}
		};

		template <>
		struct Make<CMD::player_cosmetic_begin>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned short inv_index)
			{
				return Make<single_data_header>::From(wrapper, PLAYER_COSMETIC_BEGIN) << inv_index;
			}
		};

		template <>
		struct Make<CMD::player_cosmetic_end>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned short inv_index)
			{
				return Make<single_data_header>::From(wrapper, PLAYER_COSMETIC_END) << inv_index;
			}
		};

		template <>
		struct Make<CMD::cosmetic_success>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & self, unsigned short crc)
			{
				Make<single_data_header>::From(wrapper, COSMETIC_SUCCESS);
				return wrapper << crc << self.id;
			}
		};

		template <>
		struct Make<CMD::object_cast_pos_skill>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & self, const A3DVECTOR & pos, const XID &target, int skill, unsigned short time , unsigned char level)
			{
				Make<single_data_header>::From(wrapper, OBJECT_CAST_POS_SKILL);
				return wrapper << self.id << pos << target.id <<skill << time <<  level;
			}
		};

		template <>
		struct Make<CMD::change_move_seq>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned short seq)
			{
				Make<single_data_header>::From(wrapper, CHANGE_MOVE_SEQ);
				return wrapper << seq;
			}
		};

		template <>
		struct Make<CMD::server_config_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int mall_time, int mall2_time, int mall3_time)
			{
				Make<single_data_header>::From(wrapper, SERVER_CONFIG_DATA);
				return wrapper << world_manager::GetWorldTag() << world_manager::GetRegionTag() << world_manager::GetPrecinctTag() << mall_time << mall2_time << mall3_time;
			}
		};

		template <>
		struct Make<CMD::player_rush_mode>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char is_active)
			{
				Make<single_data_header>::From(wrapper, PLAYER_RUSH_MODE );
				return wrapper << is_active;
			}
		};

		template <>
		struct Make<CMD::trashbox_capacity_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char where, int cap)
			{
				Make<single_data_header>::From(wrapper, TRASHBOX_CAPACITY_NOTIFY );
				return wrapper << where << cap;
			}
		};

		template <>
		struct Make<CMD::npc_dead_2>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gnpc * pNPC,const XID & killer)
			{
				Make<single_data_header>::From(wrapper,NPC_DEAD_2);
				return wrapper << pNPC->ID.id << killer.id;
			}
		};

		template <>
		struct Make<CMD::produce_null>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int recipe_id)
			{
				Make<single_data_header>::From(wrapper,PRODUCE_NULL);
				return wrapper << recipe_id;
			}
		};

		template <>
		struct Make<CMD::double_exp_time>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int mode ,int end_time)
			{
				Make<single_data_header>::From(wrapper,DOUBLE_EXP_TIME);
				return wrapper << mode << end_time;
			}
		};

		template <>
		struct Make<CMD::available_double_exp_time>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int remain_time)
			{
				Make<single_data_header>::From(wrapper,AVAILABLE_DOUBLE_EXP_TIME);
				return wrapper << remain_time;
			}
		};

		template <>
		struct Make<CMD::active_pvp_combat_state>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gplayer * pPlayer,char is_active)
			{
				Make<single_data_header>::From(wrapper,ACTIVE_PVP_COMBAT_STATE);
				return wrapper << pPlayer->ID.id << is_active;
			}
		};

		template <>
		struct Make<CMD::duel_recv_request>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & target)
			{
				Make<single_data_header>::From(wrapper,DUEL_RECV_REQUEST);
				return wrapper << target.id;
			}
		};

		template <>
		struct Make<CMD::duel_reject_request>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & target,int reason)
			{
				Make<single_data_header>::From(wrapper,DUEL_REJECT_REQUEST);
				return wrapper << target.id << reason;
			}
		};

		template <>
		struct Make<CMD::duel_prepare>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & target,int delay)
			{
				Make<single_data_header>::From(wrapper,DUEL_PREPARE);
				return wrapper << target.id << delay;
			}
		};

		template <>
		struct Make<CMD::duel_cancel>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & target)
			{
				Make<single_data_header>::From(wrapper,DUEL_CANCEL);
				return wrapper << target.id ;
			}
		};

		template <>
		struct Make<CMD::duel_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & target)
			{
				Make<single_data_header>::From(wrapper,DUEL_START);
				return wrapper << target.id ;
			}
		};

		template <>
		struct Make<CMD::duel_stop>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & who)
			{
				Make<single_data_header>::From(wrapper,DUEL_STOP);
				return wrapper << who.id;
			}
		};

		template <>
		struct Make<CMD::duel_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & id1, const XID & id2, bool result)
			{
				Make<single_data_header>::From(wrapper,DUEL_RESULT);
				return wrapper << id1.id << id2.id << (char)(result?1:0);
			}
		};

		template <>
		struct Make<CMD::player_bind_request>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int param, const XID & who)
			{
				Make<single_data_header>::From(wrapper,PLAYER_BIND_REQUEST);
				return wrapper << param << who.id;
			}
		};

		template <>
		struct Make<CMD::player_bind_invite>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int param, const XID & who)
			{
				Make<single_data_header>::From(wrapper,PLAYER_BIND_INVITE);
				return wrapper << param << who.id;
			}
		};

		template <>
		struct Make<CMD::player_bind_request_reply>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & who,int param, int param_id)
			{
				Make<single_data_header>::From(wrapper,PLAYER_BIND_REQUEST_REPLY);
				return wrapper << param_id << who.id << param;
			}
		};

		template <>
		struct Make<CMD::player_bind_invite_reply>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & who,int param, int param_id)
			{
				Make<single_data_header>::From(wrapper,PLAYER_BIND_INVITE_REPLY);
				return wrapper << param_id << who.id << param;
			}
		};

		template <>
		struct Make<CMD::player_bind_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & mule, const XID & rider, int param)
			{
				Make<single_data_header>::From(wrapper,PLAYER_BIND_START);
				return wrapper << param << mule.id << rider.id;
			}
		};

		template <>
		struct Make<CMD::player_bind_stop>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & who)
			{
				Make<single_data_header>::From(wrapper,PLAYER_BIND_STOP);
				return wrapper << who.id;
			}
		};

		template <>
		struct Make<CMD::player_mounting>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & who, int mount_id, unsigned short mount_color)
			{
				Make<single_data_header>::From(wrapper,PLAYER_MOUNTING);
				return wrapper << who.id << mount_id << mount_color;
			}
		};

		template <>
		struct Make<CMD::player_equip_detail>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & self, const void * data, unsigned int size)
			{
				Make<single_data_header>::From(wrapper,PLAYER_EQUIP_DETAIL);
				wrapper << self.id << 0 << size;
				return wrapper.push_back(data,size);
			}
		};
		
		template <>
		struct Make<CMD::else_duel_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & self)
			{
				Make<single_data_header>::From(wrapper,ELSE_DUEL_START);
				return wrapper << self.id ;
			}
		};

		template <>
		struct Make<CMD::pariah_duration>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int t)
			{
				Make<single_data_header>::From(wrapper,PARIAH_DURATION);
				return wrapper << t;
			}
		};

		template <>
		struct Make<CMD::player_gain_pet>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, const void * data, unsigned int size)
			{
				Make<single_data_header>::From(wrapper,PLAYER_GAIN_PET);
				wrapper << index;
				return wrapper.push_back(data,size);
			}
		};

		template <>
		struct Make<CMD::player_free_pet>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int pet_id)
			{
				Make<single_data_header>::From(wrapper,PLAYER_FREE_PET);
				return wrapper << index << pet_id;
			}
		};

		template <>
		struct Make<CMD::player_summon_pet>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int pet_tid, int pet_id, int life_time)
			{
				Make<single_data_header>::From(wrapper,PLAYER_SUMMON_PET);
				return wrapper << index << pet_tid << pet_id << life_time;
			}
		};

		template <>
		struct Make<CMD::player_recall_pet>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int pet_id, char reason)
			{
				Make<single_data_header>::From(wrapper,PLAYER_RECALL_PET);
				return wrapper << index << pet_id << reason;
			}
		};

		template <>
		struct Make<CMD::player_start_pet_op>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int pet_id,int delay, int op)
			{
				Make<single_data_header>::From(wrapper,PLAYER_START_PET_OP);
				return wrapper << index << pet_id << delay << op;
			}
		};

		template <>
		struct Make<CMD::player_stop_pet_op>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				Make<single_data_header>::From(wrapper,PLAYER_STOP_PET_OP);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::player_pet_recv_exp>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int pet_id,int exp)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PET_RECV_EXP);
				return wrapper << index << pet_id << exp;
			}
		};

		template <>
		struct Make<CMD::player_pet_levelup>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int pet_id,int level,int exp)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PET_LEVELUP);
				return wrapper << index << pet_id << level << exp;
			}
		};

		template <>
		struct Make<CMD::player_pet_room_capacity>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int capacity)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PET_ROOM_CAPACITY);
				return wrapper << capacity;
			}
		};

		template <>
		struct Make<CMD::player_pet_room>
		{
			template <typename WRAPPER,typename PET_DATA>
			inline static WRAPPER & From(WRAPPER & wrapper, PET_DATA ** pData, unsigned int start, unsigned int end)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PET_ROOM);
				unsigned short count = 0;
				for(unsigned int i = start; i < end; i ++)
				{
					if(pData[i-start]) count ++;
				}
				wrapper << count;
				for(unsigned int i = start; i < end; i ++)
				{
					if(!pData[i-start]) continue;
					wrapper << i;
					wrapper.push_back(pData[i-start],sizeof(PET_DATA));
				}
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::player_pet_honor_point>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int p)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PET_HONOR_POINT);
				return wrapper << index << p;
			}
		};

		template <>
		struct Make<CMD::player_pet_hunger_gauge>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int p)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PET_HUNGER_GAUGE);
				return wrapper << index << p;
			}
		};

		template <>
		struct Make<CMD::enter_battleground>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int role, int battle_id, int end_time)
			{
				Make<single_data_header>::From(wrapper,ENTER_BATTLEGROUND);
				return wrapper << role << battle_id << end_time;
			}
		};

		template <>
		struct Make<CMD::turret_leader_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & self, int leader)
			{
				Make<single_data_header>::From(wrapper,TURRET_LEADER_NOTIFY);
				return wrapper << self.id << leader;
			}
		};

		template <>
		struct Make<CMD::battle_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int result)
			{
				Make<single_data_header>::From(wrapper,BATTLE_RESULT);
				return wrapper << result;
			}
		};

		template <>
		struct Make<CMD::battle_score>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int os, int og, int ds, int dg)
			{
				Make<single_data_header>::From(wrapper,BATTLE_SCORE);
				return wrapper << os << og << ds << dg;
			}
		};

		template <>
		struct Make<CMD::pet_dead>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int index)
			{
				Make<single_data_header>::From(wrapper,PET_DEAD);
				return wrapper << index;
			}
		};

		template <>
		struct Make<CMD::pet_revive>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int index, float hp_factor)
			{
				Make<single_data_header>::From(wrapper,PET_REVIVE);
				return wrapper << index << hp_factor;
			}
		};

		template <>
		struct Make<CMD::pet_hp_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int index, float hp_factor, int cur_hp, float mp_factor, int cur_mp)
			{
				Make<single_data_header>::From(wrapper,PET_HP_NOTIFY);
				return wrapper << index << hp_factor << cur_hp << mp_factor << cur_mp;
			}
		};

		template <>
		struct Make<CMD::pet_ai_state>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char aggro_state, char stay_state)
			{
				Make<single_data_header>::From(wrapper,PET_AI_STATE);
				return wrapper << aggro_state << stay_state;
			}
		};

		template <>
		struct Make<CMD::refine_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int result)
			{
				Make<single_data_header>::From(wrapper,REFINE_RESULT);
				return wrapper << result;
			}
		};

		template <>
		struct Make<CMD::pet_set_cooldown>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int cd_idx, int msec)
			{
				Make<single_data_header>::From(wrapper,PET_SET_COOLDOWN);
				return wrapper << index << cd_idx << msec;
			}
		};

		template <>
		struct Make<CMD::player_cash>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int cash)
			{
				Make<single_data_header>::From(wrapper,PLAYER_CASH);
				return wrapper << cash;
			}
		};

		template <>
		struct Make<CMD::player_bind_success>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned short inv_index, int id)
			{
				Make<single_data_header>::From(wrapper,PLAYER_BIND_SUCCESS);
				return wrapper << inv_index << id;
			}
		};

		template <>     
		struct Make<CMD::player_change_inventory_size>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper, int new_size)
				{
					Make<single_data_header>::From(wrapper,PLAYER_CHANGE_INVENTORY_SIZE); 
					return wrapper << new_size;
				}       
		}; 

		template <>     
		struct Make<CMD::player_pvp_mode>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper, unsigned char pvp_mode)
				{
					Make<single_data_header>::From(wrapper,PLAYER_PVP_MODE); 
					return wrapper << pvp_mode;
				}       
		}; 

		template <>     
		struct Make<CMD::player_wallow_info>
		{
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper, unsigned char active, unsigned char level, int play_time, int l_time, int h_time, int reason)
				{
					Make<single_data_header>::From(wrapper,PLAYER_WALLOW_INFO); 
					return wrapper << active << level << play_time << l_time << h_time << reason;
				}       
		}; 
		template <>
		struct Make<player_use_item_with_arg>
		{       
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper,char where, unsigned char index, int item_id, unsigned short use_count, const char * arg, unsigned int buf_size)
				{       
					Make<single_data_header>::From(wrapper,PLAYER_USE_ITEM_WITH_ARG);
					wrapper << where << index << item_id << use_count;
					wrapper << (unsigned short) buf_size;
					wrapper.push_back(arg, buf_size);
					return wrapper;
				}       
		};      

		template <>
		struct Make<CMD::object_use_item_with_arg>
		{       
			template <typename WRAPPER>
				inline static WRAPPER & From(WRAPPER & wrapper,gplayer * pPlayer,int type,const char * arg, unsigned int buf_size)
				{       
					Make<single_data_header>::From(wrapper,OBJECT_USE_ITEM_WITH_ARG);
					wrapper << pPlayer->ID.id  << type;
					wrapper << (unsigned short) buf_size;
					wrapper.push_back(arg,buf_size);
					return wrapper;
				}       
		};      

		template <>
		struct Make<CMD::player_change_spouse>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, int id)
			{
				Make<single_data_header>::From(wrapper,PLAYER_CHANGE_SPOUSE);
				return wrapper << pObj->ID.id << id;
			}
		};

		template <>
		struct Make<CMD::notify_safe_lock>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char active, int time, int max_time, bool passwd)
			{
				Make<single_data_header>::From(wrapper,NOTIFY_SAFE_LOCK);
				return wrapper << active << time << max_time << passwd;
			}
		};

		//lgc
		template<>
		struct Make<CMD::elf_vigor>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int vigor, int max_vigor, int vigor_gen)
			{
				Make<single_data_header>::From(wrapper,ELF_VIGOR);
				return wrapper << vigor << max_vigor << vigor_gen;
			}
		};

		template<>
		struct Make<CMD::elf_enhance>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, short str_en, short agi_en, short vit_en, short eng_en)
			{
				Make<single_data_header>::From(wrapper,ELF_ENHANCE);
				return wrapper << str_en << agi_en << vit_en << eng_en;
			}
		};
		
		template<>
		struct Make<CMD::elf_stamina>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int sta)
			{
				Make<single_data_header>::From(wrapper,ELF_STAMINA);
				return wrapper << sta;
			}
		};
		
		template<>
		struct Make<CMD::elf_cmd_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int cmd, int result, int param1, int param2)
			{
				Make<single_data_header>::From(wrapper,ELF_CMD_RESULT);
				return wrapper << cmd << result << param1 << param2;
			}
		};

		template<>
		struct Make<CMD::common_data_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				Make<single_data_header>::From(wrapper,COMMON_DATA_NOTIFY);
				return wrapper;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int key, int value)
			{
				return wrapper << key << value;
			}
		};

		template<>
		struct Make<CMD::common_data_list>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				Make<single_data_header>::From(wrapper,COMMON_DATA_LIST);
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::player_elf_refine_activate>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,  gobject * pObj, char status)
			{
				Make<single_data_header>::From(wrapper,PLAYER_ELF_REFINE_ACTIVATE);
				return wrapper << pObj->ID.id << status;
			}
		};
		
		template <>
		struct Make<CMD::player_cast_elf_skill>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, const XID & target, int skill, unsigned char level)
			{
				Make<single_data_header>::From(wrapper,PLAYER_CAST_ELF_SKILL);
				return wrapper << pObj->ID.id << target.id << skill << level;
			}
		};

		template <>
		struct Make<CMD::mall_item_price>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, short start, short end, unsigned short count)
			{
				Make<single_data_header>::From(wrapper,MALL_ITEM_PRICE);
				return wrapper << start << end << count;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & AddGoods(WRAPPER & wrapper, short index, char slot, int id, char expire_type, int expire_time, int price, char status, int min_vip_level)
			{
				return wrapper << index << slot << id << expire_type << expire_time << price << status << min_vip_level;
			}
			
		};
		
		template <>
		struct Make<CMD::mall_item_buy_failed>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, short index, char reason)
			{
				Make<single_data_header>::From(wrapper,MALL_ITEM_BUY_FAILED);
				return wrapper << index << reason; 
			}
		};
		
		template <>
		struct Make<CMD::player_elf_levelup>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj)
			{
				Make<single_data_header>::From(wrapper,PLAYER_ELF_LEVELUP);
				return wrapper << pObj->ID.id; 
			}
		};
		
		template <>
		struct Make<CMD::player_property>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const void * data, unsigned int size, const void* self_data, unsigned int self_size)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PROPERTY);
				ASSERT(size == sizeof(CMD::player_property::_data));
				ASSERT(self_size == sizeof(CMD::player_property::_self_data));
				wrapper.push_back(data,size);
				return wrapper.push_back(self_data,self_size);
			}
		};

		template<>
		struct Make<CMD::player_cast_rune_skill>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,const XID & caster, const XID & target, int skill,unsigned short time, unsigned char level)
			{
				Make<single_data_header>::From(wrapper,PLAYER_CAST_RUNE_SKILL);
				return wrapper << caster.id << target.id << skill << time << level;
			}
		};
		
		template <>
		struct Make<CMD::player_cast_rune_instant_skill>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, gobject * pObj, const XID & target, int skill, unsigned char level)
			{
				Make<single_data_header>::From(wrapper,PLAYER_CAST_RUNE_INSTANT_SKILL);
				return wrapper << pObj->ID.id << target.id << skill << level;
			};
		};
		
		template <>
		struct Make<CMD::equip_trashbox_item>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char where, unsigned char trash_idx,unsigned char equip_idx)
			{
				Make<single_data_header>::From(wrapper,EQUIP_TRASHBOX_ITEM);
				return wrapper << where << trash_idx << equip_idx; 
			}			
		};
		
		template <>
		struct Make<CMD::security_passwd_checked>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				Make<single_data_header>::From(wrapper,SECURITY_PASSWD_CHECKED);
				return wrapper; 
			}			
		};
		
		template <>
		struct Make<CMD::object_invisible>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gobject* pObject, int invisible_degree)
			{
				Make<single_data_header>::From(wrapper,OBJECT_INVISIBLE);
				return wrapper << pObject->ID.id << invisible_degree; 
			}			
		};
		
		template <>
		struct Make<CMD::hp_steal>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int hp)
			{
				Make<single_data_header>::From(wrapper,HP_STEAL);
				return wrapper << hp; 
			}			
		};
		
		template <>
		struct Make<CMD::player_dividend>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int dividend)
			{
				Make<single_data_header>::From(wrapper,PLAYER_DIVIDEND);
				return wrapper << dividend;
			}
		};
		
		template <>
		struct Make<CMD::dividend_mall_item_price>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, short start, short end, unsigned short count)
			{
				Make<single_data_header>::From(wrapper,DIVIDEND_MALL_ITEM_PRICE);
				return wrapper << start << end << count;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & AddGoods(WRAPPER & wrapper, short index, char slot, int id, char expire_type, int expire_time, int price, char status, int min_vip_level)
			{
				return wrapper << index << slot << id << expire_type << expire_time << price << status << min_vip_level;
			}
			
		};
		
		template <>
		struct Make<CMD::dividend_mall_item_buy_failed>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, short index, char reason)
			{
				Make<single_data_header>::From(wrapper,DIVIDEND_MALL_ITEM_BUY_FAILED);
				return wrapper << index << reason; 
			}
		};
		
		template<>
		struct Make<CMD::elf_exp>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int exp)
			{
				Make<single_data_header>::From(wrapper,ELF_EXP);
				return wrapper << exp;
			}
		};
		
		template<>
		struct Make<CMD::public_quest_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int task_id, int child_task_id, int score, int cls_place, int all_place)
			{
				Make<single_data_header>::From(wrapper,PUBLIC_QUEST_INFO);
				//int space_id = 0; //162
				return wrapper << task_id << child_task_id << score << cls_place << all_place;
			}
		};
		
		template<>
		struct Make<CMD::public_quest_ranks>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int task_id, int player_count)
			{
				Make<single_data_header>::From(wrapper,PUBLIC_QUEST_RANKS);
				//int space_id = 0; //162
				return wrapper << task_id << player_count;
			}

			template <typename WRAPPER>
			inline static WRAPPER & ClsRanksCount(WRAPPER & wrapper, unsigned int ranks_size)
			{
				return wrapper << ranks_size;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & ClsRanksEntry(WRAPPER & wrapper, int roleid, int race, int score, int rand, int place) //,  int reserve, int reserve1)
			{
				return wrapper << roleid << race << score << rand << place; // << reserve << reserve1;
			}
		};
		
		template<>
		struct Make<CMD::multi_exp_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int last_timestamp,	float enhance_factor)
			{
				Make<single_data_header>::From(wrapper,MULTI_EXP_INFO);
				return wrapper << last_timestamp << enhance_factor;
			}
		};
		
		template<>
		struct Make<CMD::change_multi_exp_state>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char state, int enchance_time, int buffer_time, int impair_time, int activate_times_left) 
			{
				Make<single_data_header>::From(wrapper,CHANGE_MULTI_EXP_STATE);
				return wrapper << state << enchance_time << buffer_time << impair_time << activate_times_left;
			}
		};
		
		template<>
		struct Make<CMD::world_life_time>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int life_time) 
			{
				Make<single_data_header>::From(wrapper,WORLD_LIFE_TIME);
				return wrapper << life_time;
			}
		};
		
		template<>
		struct Make<CMD::wedding_book_list>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int count) 
			{
				Make<single_data_header>::From(wrapper,WEDDING_BOOK_LIST);
				return wrapper << count;
			}

			template <typename WRAPPER>
			inline static WRAPPER & AddEntry(WRAPPER & wrapper,int start_time,int end_time,int groom,int bride,int scene,char status,char special)
			{
				return wrapper << start_time << end_time << groom << bride << scene << status << special;
			}
		};
		
		template<>
		struct Make<CMD::wedding_book_success>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type) 
			{
				Make<single_data_header>::From(wrapper,WEDDING_BOOK_SUCCESS);
				return wrapper << type;
			}
		};
		
		template<>
		struct Make<CMD::calc_network_delay>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int timestamp) 
			{
				Make<single_data_header>::From(wrapper,CALC_NETWORK_DELAY);
				return wrapper << timestamp;
			}
		};
		
		template<>
		struct Make<CMD::player_knockback>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, const A3DVECTOR & pos, int time) 
			{
				int fix_pos = 0;
				Make<single_data_header>::From(wrapper,PLAYER_KNOCKBACK);
				return wrapper << id << pos << time << fix_pos;
			}
		};
		
		template <>
		struct Make<CMD::player_summon_plant_pet>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int plant_tid, int plant_id, int life_time)
			{
				Make<single_data_header>::From(wrapper,PLAYER_SUMMON_PLANT_PET);
				return wrapper << plant_tid << plant_id << life_time;
			}
		};
		
		template <>
		struct Make<CMD::plant_pet_disappear>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, char reason)
			{
				Make<single_data_header>::From(wrapper,PLANT_PET_DISAPPEAR);
				return wrapper << id << reason;
			}
		};
		
		template <>
		struct Make<CMD::plant_pet_hp_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, float hp_factor, int cur_hp, float mp_factor, int cur_mp)
			{
				Make<single_data_header>::From(wrapper,PLANT_PET_HP_NOTIFY);
				return wrapper << id << hp_factor << cur_hp << mp_factor << cur_mp;
			}
		};

		template <>
		struct Make<CMD::pet_property>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int index,const struct extend_prop & prop)
			{
				Make<single_data_header>::From(wrapper,PET_PROPERTY);
				return wrapper << index << prop;
			}
		};
		
		template <>
		struct Make<CMD::faction_contrib_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int consume_contrib,int exp_contrib,int cumulate_contrib)
			{
				Make<single_data_header>::From(wrapper,FACTION_CONTRIB_NOTIFY);
				return wrapper << consume_contrib << exp_contrib << cumulate_contrib;
			}
		};
		
		template <>
		struct Make<CMD::faction_fortress_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				Make<single_data_header>::From(wrapper,FACTION_FORTRESS_INFO);
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::enter_factionfortress>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int role_in_war, int factionid, int offense_endtime)
			{
				Make<single_data_header>::From(wrapper,ENTER_FACTIONFORTRESS);
				return wrapper << role_in_war << factionid << offense_endtime;
			}
		};
		
		template <>
		struct Make<CMD::faction_relation_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				return Make<single_data_header>::From(wrapper,FACTION_RELATION_NOTIFY);
			}
		};

		template <>
		struct Make<CMD::player_equip_disabled>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & who, int64_t mask)
			{
				Make<single_data_header>::From(wrapper,PLAYER_EQUIP_DISABLED);
				return wrapper << who.id << mask; 
			}
		};

		template <>
		struct Make<CMD::player_spec_item_list>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & who, int type, const void * data, unsigned int size)
			{
				Make<single_data_header>::From(wrapper,PLAYER_SPEC_ITEM_LIST);
				wrapper << who.id << type;
				return wrapper.push_back(data,size);
			}
		};
		
		template <>
		struct Make<CMD::object_start_play_action>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & who, int play_times,int action_last_time,int interval_time,unsigned int name_length,char* action_name)
			{
				Make<single_data_header>::From(wrapper,OBJECT_START_PLAY_ACTION);
				wrapper << who.id << play_times << action_last_time << interval_time << name_length;
				return wrapper.push_back(action_name,name_length);
			}
		};

		template <>
		struct Make<CMD::object_stop_play_action>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & who)
			{
				Make<single_data_header>::From(wrapper,OBJECT_STOP_PLAY_ACTION);
				return wrapper << who.id; 
			}
		};
		
		template <>
		struct Make<CMD::congregate_request>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char type, int sponsor, int timeout)
			{
				Make<single_data_header>::From(wrapper,CONGREGATE_REQUEST);
				return wrapper << type << sponsor << timeout; 
			}
		};
		
		template <>
		struct Make<CMD::reject_congregate>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char type, int id)
			{
				Make<single_data_header>::From(wrapper,REJECT_CONGREGATE);
				return wrapper << type << id; 
			}
		};

		template <>
		struct Make<CMD::congregate_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char type, const XID& who, int time)
			{
				Make<single_data_header>::From(wrapper,CONGREGATE_START);
				return wrapper << type << who.id << time; 
			}
		};
		
		template <>
		struct Make<CMD::cancel_congregate>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char type, const XID& who)
			{
				Make<single_data_header>::From(wrapper,CANCEL_CONGREGATE);
				return wrapper << type << who.id; 
			}
		};
		
		template <>
		struct Make<CMD::engrave_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int recipe_id, int use_time)
			{
				Make<single_data_header>::From(wrapper,ENGRAVE_START);
				return wrapper << recipe_id << use_time; 
			}
		};

		template <>
		struct Make<CMD::engrave_end>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				Make<single_data_header>::From(wrapper,ENGRAVE_END);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::engrave_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int addon_num)
			{
				Make<single_data_header>::From(wrapper,ENGRAVE_RESULT);
				return wrapper << addon_num;
			}
		};
		
		template<>
		struct Make<CMD::dps_dph_rank>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int next_refresh_sec, unsigned char rank_count, unsigned char rank_mask)
			{
				Make<single_data_header>::From(wrapper, DPS_DPH_RANK);
				return wrapper << next_refresh_sec << rank_count << rank_mask;
			}

			template <typename WRAPPER>
			inline static WRAPPER & AddEntry(WRAPPER & wrapper, int roleid, unsigned char level, int dps_or_dph)
			{
				return wrapper << roleid << level << dps_or_dph;
			}
		};

		template <>
		struct Make<CMD::addonregen_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int recipe_id, int use_time)
			{
				Make<single_data_header>::From(wrapper,ADDONREGEN_START);
				return wrapper << recipe_id << use_time; 
			}
		};

		template <>
		struct Make<CMD::addonregen_end>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				Make<single_data_header>::From(wrapper,ADDONREGEN_END);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::addonregen_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int addon_num)
			{
				Make<single_data_header>::From(wrapper,ADDONREGEN_RESULT);
				return wrapper << addon_num;
			}
		};
		
		template <>
		struct Make<CMD::invisible_obj_list>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, gobject ** ppObject, unsigned int count)
			{
				Make<single_data_header>::From(wrapper,INVISIBLE_OBJ_LIST);
				wrapper << id << count;
				for(unsigned int i=0; i<count; i++)
				{
					wrapper << ppObject[i]->ID.id;
				}
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::set_player_limit>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, char b)
			{
				Make<single_data_header>::From(wrapper,SET_PLAYER_LIMIT);
				return wrapper << index << b;
			}
		};
		template <>
		struct Make<CMD::player_teleport>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, const A3DVECTOR & pos, unsigned short use_time, char mode)
			{
				Make<single_data_header>::From(wrapper,PLAYER_TELEPORT);
				return wrapper << id << pos << use_time << mode;
			}
		};
		template <>
		struct Make<CMD::object_forbid_be_selected>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, char b)
			{
				Make<single_data_header>::From(wrapper,OBJECT_FORBID_BE_SELECTED);
				return wrapper << id << b;
			}
		};
		
		template <>
		struct Make<CMD::player_inventory_detail>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & self, unsigned int money, unsigned char inv_size, const void * data, unsigned int size)
			{
				Make<single_data_header>::From(wrapper,PLAYER_INVENTORY_DETAIL);
				wrapper << self.id << money << inv_size << size;
				return wrapper.push_back(data,size);
			}
		};
		
		template <>
		struct Make<CMD::player_force_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int cur_force_id, unsigned int count, const void * data, unsigned int data_size)
			{
				Make<single_data_header>::From(wrapper,PLAYER_FORCE_DATA);
				wrapper << cur_force_id << count;
				return wrapper.push_back(data, data_size);
			}
		};
		
		template <>
		struct Make<CMD::player_force_changed>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, int cur_force_id)
			{
				Make<single_data_header>::From(wrapper,PLAYER_FORCE_CHANGED);
				return wrapper << id << cur_force_id;
			}
		};

		template <>
		struct Make<CMD::player_force_data_update>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int force_id, int reputation, int contribution)
			{
				Make<single_data_header>::From(wrapper,PLAYER_FORCE_DATA_UPDATE);
				return wrapper << force_id << reputation << contribution;
			}
		};
		
		template <>
		struct Make<CMD::force_global_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char data_ready, unsigned int count, const void * data, unsigned int data_size)
			{
				Make<single_data_header>::From(wrapper,FORCE_GLOBAL_DATA);
				wrapper << data_ready << count;
				if(count) wrapper.push_back(data,data_size);
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::add_multiobj_effect>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, int target, char type)
			{
				Make<single_data_header>::From(wrapper,ADD_MULTIOBJ_EFFECT);
				return wrapper << id << target << type;
			}
		};
		
		template <>
		struct Make<CMD::remove_multiobj_effect>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, int target, char type)
			{
				Make<single_data_header>::From(wrapper,REMOVE_MULTIOBJ_EFFECT);
				return wrapper << id << target << type;
			}
		};
		
		template <>
		struct Make<CMD::enter_wedding_scene>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int groom, int bride)
			{
				Make<single_data_header>::From(wrapper,ENTER_WEDDING_SCENE);
				return wrapper << groom << bride;
			}
		};
		
		template <>
		struct Make<CMD::produce4_item_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int stime, const item_data & data, unsigned short crc)
			{
				Make<single_data_header>::From(wrapper,PRODUCE4_ITEM_INFO);
				wrapper << stime;
				wrapper << data.type << data.expire_date << data.proc_type;
				wrapper << data.count << crc << (unsigned short)(data.content_length);
				wrapper.push_back(data.item_content,data.content_length);
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::online_award_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int total_award_time, unsigned int count, const void * data, unsigned int data_size)
			{
				Make<single_data_header>::From(wrapper,ONLINE_AWARD_DATA);
				wrapper << total_award_time << count;
				if(count) wrapper.push_back(data, data_size);
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::toggle_online_award>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type, char activate)
			{
				Make<single_data_header>::From(wrapper,TOGGLE_ONLINE_AWARD);
				return wrapper << type << activate;
			}
		};
		
		template <>
		struct Make<CMD::player_profit_time>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char flag, char profit_map, int profit_time, int profit_level)
			{
				Make<single_data_header>::From(wrapper,PLAYER_PROFIT_TIME);
				return wrapper << flag << profit_map << profit_time << profit_level;
			}
		};
		
		template <>
		struct Make<CMD::set_profittime_state>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char state)
			{
				Make<single_data_header>::From(wrapper,SET_PROFITTIME_STATE);
				wrapper << state;
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::enter_nonpenalty_pvp_state>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char state)
			{
				Make<single_data_header>::From(wrapper,ENTER_NONPENALTY_PVP_STATE);
				return wrapper << state;
			}
		};
		
		template <>
		struct Make<CMD::self_country_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int country_id)
			{
				Make<single_data_header>::From(wrapper,SELF_COUNTRY_NOTIFY);
				return wrapper << country_id;
			}
		};
		
		template <>
		struct Make<CMD::player_country_changed>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const XID & player, int country_id)
			{
				Make<single_data_header>::From(wrapper,PLAYER_COUNTRY_CHANGED);
				return wrapper << player.id << country_id;
			}
		};
		
		template <>
		struct Make<CMD::enter_countrybattle>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int role, int battle_id, int end_time, int offense_country, int defence_country)
			{
				Make<single_data_header>::From(wrapper,ENTER_COUNTRYBATTLE);
				return wrapper << role << battle_id << end_time << offense_country << defence_country;
			}
		};
		
		template <>
		struct Make<CMD::countrybattle_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int result)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_RESULT);
				return wrapper << result;
			}
		};

		template <>
		struct Make<CMD::countrybattle_score>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int os, int og, int ds, int dg)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_SCORE);
				return wrapper << os << og << ds << dg;
			}
		};
		
		template <>
		struct Make<CMD::countrybattle_resurrect_rest_times>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int times)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_RESURRECT_REST_TIMES);
				return wrapper << times;
			}
		};
		
		template <>
		struct Make<CMD::countrybattle_flag_carrier_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int roleid, const A3DVECTOR& pos, char offense)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_FLAG_CARRIER_NOTIFY);
				return wrapper << roleid << pos << offense;
			}
		};
		
		template <>
		struct Make<CMD::countrybattle_became_flag_carrier>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char is_carrier)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_BECAME_FLAG_CARRIER);
				return wrapper << is_carrier;
			}
		};
		
		template <>
		struct Make<CMD::countrybattle_personal_score>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int combat_time, int attend_time, int kill_count, int death_count, int country_kill_count, int country_death_count)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_PERSONAL_SCORE);
				return wrapper << combat_time << attend_time << kill_count << death_count << country_kill_count << country_death_count;
			}
		};
		
		template <>
		struct Make<CMD::countrybattle_flag_msg_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int msg, char offense)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_FLAG_MSG_NOTIFY);
				return wrapper << msg << offense;
			}
		};
		
		template <>
		struct Make<CMD::defense_rune_enabled>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char rune_type, char enable)
			{
				Make<single_data_header>::From(wrapper,DEFENSE_RUNE_ENABLED);
				return wrapper << rune_type << enable;
			}
		};
		
		template <>
		struct Make<CMD::countrybattle_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int attacker_count, int defender_count)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_INFO);
				return wrapper << attacker_count << defender_count;
			}
		};

		template <>
		struct Make<CMD::cash_money_exchg_rate>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char open, int rate)
			{
				Make<single_data_header>::From(wrapper,CASH_MONEY_EXCHG_RATE);
				return wrapper << open << rate;
			}
		};
		
		template<>
		struct Make<CMD::pet_rebuild_inherit_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER &From(WRAPPER & wrapper,unsigned int index,int use_time)
			{
				Make<single_data_header>::From(wrapper,PET_REBUILD_INHERIT_START);
				wrapper << index << use_time;
				return wrapper;
			}
		};
	
		template<>
		struct Make<CMD::pet_rebuild_inherit_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int stime,int pet_id,unsigned int index,int r_attack,int r_defense,int r_hp,int r_atk_lvl,int r_def_lvl)
			{
				Make<single_data_header>::From(wrapper,PET_REBUILD_INHERIT_INFO);
				wrapper << stime;
				wrapper << pet_id << index;
				wrapper << r_attack << r_defense << r_hp << r_atk_lvl << r_def_lvl;
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::pet_rebuild_inherit_end>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int index)
			{
				Make<single_data_header>::From(wrapper,PET_REBUILD_INHERIT_END);
				wrapper << index;
				return wrapper;
			}
		};
	
		template <>
		struct Make<CMD::pet_evolution_done>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int index)
			{
				Make<single_data_header>::From(wrapper,PET_EVOLUTION_DONE);
				wrapper << index;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::pet_rebuild_nature_start>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int index, int use_time)
			{
				Make<single_data_header>::From(wrapper,PET_REBUILD_NATURE_START);
				wrapper << index << use_time;
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::pet_rebuild_nature_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int stime,int pet_id,unsigned int index,int nature)
			{
				Make<single_data_header>::From(wrapper,PET_REBUILD_NATURE_INFO);
				wrapper << stime;
				wrapper << pet_id << index << nature;
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::pet_rebuild_nature_end>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int index)
			{
				Make<single_data_header>::From(wrapper,PET_REBUILD_NATURE_END);
				wrapper << index;
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::notify_meridian_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int meridian_level,int lifegate_times,int deathgate_times,int free_refine_times,int paid_refine_times,int continu_login_days,int trigrams_map[3])
			{
				Make<single_data_header>::From(wrapper,NOTIFY_MERIDIAN_DATA);
				wrapper << meridian_level << lifegate_times << deathgate_times << free_refine_times << paid_refine_times << continu_login_days << trigrams_map[0] << trigrams_map[1] << trigrams_map[2];
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::try_refine_meridian_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int index,int result)
			{
				Make<single_data_header>::From(wrapper,TRY_REFINE_MERIDIAN_RESULT);
				wrapper << index << result;
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::equip_addon_update_notify>
		{
			template <typename WRAPPER>

			inline static WRAPPER & From(WRAPPER & wrapper,unsigned char update_type,unsigned char equip_idx,unsigned char equip_socket_idx,int old_stone_type,int new_stone_type)
			{
				Make<single_data_header>::From(wrapper,EQUIP_ADDON_UPDATE_NOTIFY);
				wrapper << update_type << equip_idx << equip_socket_idx << old_stone_type << new_stone_type;
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::self_king_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char is_king, int expire_time)
			{
				Make<single_data_header>::From(wrapper,SELF_KING_NOTIFY);
				return wrapper << is_king << expire_time;
			}
		};
		
		template <>
		struct Make<CMD::player_king_changed>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, char is_king)
			{
				Make<single_data_header>::From(wrapper,PLAYER_KING_CHANGED);
				return wrapper << id << is_king;
			}
		};
		
		template <>
		struct Make<CMD::countrybattle_stronghold_state_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int count)
			{
				Make<single_data_header>::From(wrapper,COUNTRYBATTLE_STRONGHOLD_STATE_NOTIFY);
				return wrapper << count;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & AddState(WRAPPER & wrapper, int state)
			{
				return wrapper << state;
			}
		};
		
		template<>
		struct Make<CMD::query_touch_point>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int64_t income, int64_t remain, int retcode)
			{
				Make<single_data_header>::From(wrapper,QUERY_TOUCH_POINT);
				wrapper << income;
				wrapper << remain;
				wrapper << retcode;
				return wrapper;
			}

		};

		template<>
		struct Make<CMD::cost_touch_point>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int64_t income, int64_t remain, 
					unsigned int cost, unsigned int index, unsigned int lots, int retcode)	
			{
				Make<single_data_header>::From(wrapper, COST_TOUCH_POINT);
				wrapper << income;
				wrapper << remain;
				wrapper << cost;
				wrapper << index;
				wrapper << lots;
				wrapper << retcode;
				return wrapper;
			}
		};	

		template<>
		struct Make<CMD::query_addup_money>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int64_t addupmoney)
			{
				Make<single_data_header>::From(wrapper,QUERY_ADDUP_MONEY);
				wrapper << addupmoney;
				return wrapper;
			}

		};

		template<>
		struct Make<CMD::query_title>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int roleid,int count,int ecount,
					const void * data, unsigned int data_size,const void* edata, unsigned int edata_size)
			{
				Make<single_data_header>::From(wrapper,QUERY_TITLE);
				wrapper << roleid;
				wrapper << count;
				wrapper << ecount;
				if(data_size) wrapper.push_back(data, data_size);
				if(edata_size) wrapper.push_back(edata, edata_size);

				return wrapper;
			}

		};

		template<>
		struct Make<CMD::change_title>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int roleid,unsigned short titleid)
			{
				Make<single_data_header>::From(wrapper,CHANGE_CURR_TITLE);
				wrapper << roleid;
				wrapper << titleid;

				return wrapper;
			}

		};

		template<>
		struct Make<CMD::notify_title_modify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned short titleid,int expiretime,char flag)
			{
				Make<single_data_header>::From(wrapper,MODIFY_TITLE_NOTIFY);
				wrapper << titleid;
				wrapper << expiretime;
				wrapper << flag;

				return wrapper;
			}

		};

		template<>
		struct Make<CMD::refresh_signin>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char type,int lys, int moncal, int uptime, char latesignintimes, char awardedtimes, char awardedtimes2)
			{
				Make<single_data_header>::From(wrapper,REFRESH_SIGNIN);
				
				wrapper << type;
				wrapper << lys; // reserve0
				wrapper << moncal; //битмаска месяцев
				wrapper << uptime;	// последнее время обновления 
				wrapper << latesignintimes; // итемы открытые для регистрации
                wrapper << awardedtimes; // итемы открытые в этом месяце
                wrapper << awardedtimes2; //итемы открытые в прошлом месяце

				/*
				wrapper << type;
				wrapper << moncal;
				wrapper << cys;
				wrapper << lys;
				wrapper << uptime;
				wrapper << localtime;
                wrapper << awardedtimes;
                wrapper << latesignintimes;
				*/
				return wrapper;
			}

		};

		template <>
		struct Make<CMD::parallel_world_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int worldtag, int count)
			{
				Make<single_data_header>::From(wrapper,PARALLEL_WORLD_INFO);
				return wrapper << worldtag << count;
			}
			
			template <typename WRAPPER, typename KEY>
			inline static WRAPPER & Add(WRAPPER & wrapper, const KEY & key, float load)
			{
				return wrapper << key.key1 << load;
			}
		};
		
		template<>
		struct Make<CMD::unique_data_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int count)
			{
				Make<single_data_header>::From(wrapper,UNIQUE_DATA_NOTIFY);
				wrapper << count;
				return wrapper;
			}

			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int key,int type,const void* p, unsigned int sz)
			{
				wrapper << key << type << sz;
				wrapper.push_back(p, sz);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::notify_giftcard_redeem>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int retcode, int cardtype, int parenttype, const char (&cardnumber)[20])
			{
				Make<single_data_header>::From(wrapper,GIFTCARD_REDEEM_NOTIFY);
				wrapper << retcode << cardtype << parenttype;
				wrapper.push_back(cardnumber,20);
				return wrapper;
			}	
		};
		
		template <>
		struct Make<CMD::player_reincarnation>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int id, int reincarnation_times)
			{
				Make<single_data_header>::From(wrapper,PLAYER_REINCARNATION);
				return wrapper << id << reincarnation_times;
			}
		};

		template <>
		struct Make<CMD::reincarnation_tome_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int tome_exp, char tome_active, int count)
			{
				Make<single_data_header>::From(wrapper,REINCARNATION_TOME_INFO);
				return wrapper << tome_exp << tome_active << count;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int level, int timestamp, int exp)
			{
				return wrapper << level << timestamp << exp;
			}
		};
		
		template <>
		struct Make<CMD::activate_reincarnation_tome>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, char active)
			{
				Make<single_data_header>::From(wrapper,ACTIVATE_REINCARNATION_TOME);
				return wrapper << active;
			}
		};

		template <>
		struct Make<CMD::realm_exp>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int exp,int receive_exp)
			{
				Make<single_data_header>::From(wrapper,REALM_EXP);
				return wrapper << exp << receive_exp << 0;
			}
		};
		
		template <>
		struct Make<CMD::realm_level_up>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int roleid, unsigned char level)
			{
				Make<single_data_header>::From(wrapper,REALM_LEVEL_UP);
				return wrapper << roleid << level;
			}
		};

		template <>
		struct Make<CMD::enter_trickbattle>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int role, int battle_id, int end_time)
			{
				Make<single_data_header>::From(wrapper,ENTER_TRICKBATTLE);
				return wrapper << role << battle_id << end_time;
			}
		};
		
		template <>
		struct Make<CMD::trickbattle_personal_score>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int kill, int death, int score, int multi_kill)
			{
				Make<single_data_header>::From(wrapper,TRICKBATTLE_PERSONAL_SCORE);
				return wrapper << kill << death << score << multi_kill;
			}
		};
		
		template <>
		struct Make<CMD::trickbattle_chariot_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int chariot, int energy)
			{
				Make<single_data_header>::From(wrapper,TRICKBATTLE_CHARIOT_INFO);
				return wrapper << chariot << energy;
			}
		};
		
		template <>
		struct Make<CMD::player_leadership>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int leadership, int inc_leadership)
			{
				Make<single_data_header>::From(wrapper,PLAYER_LEADERSHIP);
				return wrapper << leadership << inc_leadership; 
			}
		};
		
		template <>
		struct Make<CMD::generalcard_collection_data>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, const void * buf, unsigned int size)
			{
				Make<single_data_header>::From(wrapper,GENERALCARD_COLLECTION_DATA);
				wrapper << (unsigned int)size;
				if(size) wrapper.push_back(buf, size);
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::add_generalcard_collection>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int colloction_idx)
			{
				Make<single_data_header>::From(wrapper,ADD_GENERALCARD_COLLECTION);
				return wrapper << (unsigned int)colloction_idx;
			}
		};
		
		template <>
		struct Make<CMD::refresh_fatering>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int gain_times, unsigned int count)
			{
				Make<single_data_header>::From(wrapper,REFRESH_FATERING);
				return wrapper << gain_times << (unsigned int)count;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int level, int power)
			{
				return wrapper << level << power;
			}
		};
		
		template <>
		struct Make<CMD::mine_gatherd>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int mid, int pid, int item_type)
			{
				Make<single_data_header>::From(wrapper,MINE_GATHERD);
				return wrapper << mid << pid << item_type;
			}
		};

		template<>
		struct Make<CMD::player_active_combat>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,gplayer * pPlayer, bool is_active)
			{
				Make<single_data_header>::From(wrapper,PLAYER_ACTIVE_COMBAT);
				return wrapper << pPlayer->ID.id << is_active;
			}
		};

		template <>
		struct Make<CMD::player_query_chariots>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned int attacker_count, unsigned int defender_count)
			{
				Make<single_data_header>::From(wrapper,PLAYER_QUERY_CHARIOTS);
				return wrapper << (unsigned int)attacker_count << (unsigned int)defender_count;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int type, int count)
			{
				return wrapper << type << count;
			}
		};

		template <>
		struct Make<CMD::countrybattle_live_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper)
			{
				Make<single_data_header>::From(wrapper, COUNTRYBATTLE_LIVE_RESULT);
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::random_mall_shopping_result>	
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int eid,int opt,int res,int itemid,int price,bool flag)
			{
				Make<single_data_header>::From(wrapper,RANDOM_MALL_SHOPPING_RESULT);
				return wrapper << eid << opt << res << itemid << price << flag;
			}
		};

		template<>
		struct Make<CMD::player_mafia_pvp_mask_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int roleid,unsigned char mafia_pvp_mask)
			{
				Make<single_data_header>::From(wrapper,PLAYER_MAFIA_PVP_MASK_NOTIFY);
				return wrapper << roleid << mafia_pvp_mask;
			}
		};

		template<>
		struct Make<CMD::player_world_contribution>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int contrib,int change,int total_cost)
			{
				Make<single_data_header>::From(wrapper,PLAYER_WORLD_CONTRIB);
				return wrapper << contrib << change << total_cost;
			}
		};
		
		template<>
		struct Make<CMD::random_map_order>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,int wt,int row,int col,const int* r_src)
			{
				Make<single_data_header>::From(wrapper,RANDOM_MAP_ORDER);
				wrapper << wt << row << col;
				wrapper.push_back(r_src,sizeof(int)*row*col);
				return wrapper;				
			}
		};
		
		template<>
		struct Make<CMD::scene_service_npc_list>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,unsigned int count,int * data)
			{
				Make<single_data_header>::From(wrapper,SCENE_SERVICE_NPC_LIST);
				wrapper << count;
				if(count) wrapper.push_back(data, count * sizeof(int) * 2);
				return wrapper;
			}
		};

		template<>
		struct Make<CMD::npc_visible_tid_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper , int nid, int vtid)
			{
				Make<single_data_header>::From(wrapper,NPC_VISIBLE_TID_NOTIFY);
				wrapper << nid << vtid;
				return wrapper;
			}
		};

		template<>
		struct Make<CMD::client_screen_effect>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper , int type, int eid, int state)
			{
				Make<single_data_header>::From(wrapper,CLIENT_SCREEN_EFFECT);
				wrapper << type << eid << state;
				return wrapper;
			}
		};

        template<>
            struct Make<CMD::equip_can_inherit_addons>
            {
                template <typename WRAPPER>
                    inline static WRAPPER & From(WRAPPER & wrapper, int equip_id, unsigned char inv_idx, unsigned char addon_num, const int* addon_id_list)
                    {
                        Make<single_data_header>::From(wrapper, EQUIP_CAN_INHERIT_ADDONS);
                        wrapper << equip_id << inv_idx << addon_num;
                        if (addon_num > 0) wrapper.push_back(addon_id_list, addon_num * sizeof(int));
                        return wrapper;
                    }
            };
		
		template<>
		struct Make<CMD::combo_skill_prepare>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper , int skillid, int timestamp, 
					int arg1, int arg2, int arg3)
			{
				Make<single_data_header>::From(wrapper,COMBO_SKILL_PREPARE);
				wrapper << skillid << timestamp << arg1 << arg2 << arg3;
				return wrapper;
			}
		};

		template<>
		struct Make<CMD::instance_reenter_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int tag, int timeout)
			{
				Make<single_data_header>::From(wrapper,INSTANCE_REENTER_NOTIFY);
				wrapper << tag << timeout;
				return wrapper;
			}
		};

		template<>
		struct Make<CMD::pray_distance_change>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, float pd)
			{
				Make<single_data_header>::From(wrapper,PRAY_DISTANCE_CHANGE);
				wrapper << pd;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::solo_challenge_award_info_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int max_layer_climbed, int total_first_climbing_time, int total_score_earned,int cur_score, int last_success_stage_level, int last_success_stage_cost_time, int total_draw_item_times, int have_drawn_award_times)
			{
				Make<single_data_header>::From(wrapper,SOLO_CHALLENGE_AWARD_INFO_NOTIFY);
				wrapper <<  max_layer_climbed << total_first_climbing_time << total_score_earned << cur_score << last_success_stage_level << last_success_stage_cost_time << total_draw_item_times << have_drawn_award_times;
				return wrapper;
			}

			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int item_id, int item_count)
			{
				return wrapper << item_id << item_count;
			}
		};

		template<>
		struct Make<CMD::solo_challenge_operate_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int opttype, int retcode,int arg0, int arg1, int arg2)
			{
				Make<single_data_header>::From(wrapper,SOLO_CHALLENGE_OPERATE_RESULT);
				wrapper << opttype << retcode << arg0 << arg1 << arg2;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::solo_challenge_challenging_state_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int climbed_layer, unsigned char notify_type)
			{
				Make<single_data_header>::From(wrapper, SOLO_CHALLENGE_CHALLENGING_STATE_NOTIFY);
				wrapper << climbed_layer << notify_type;
				return wrapper;
			}
		};

		template<>
		struct Make<CMD::solo_challenge_buff_info_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int buff_num, int cur_score)
			{
				Make<single_data_header>::From(wrapper, SOLO_CHALLENGE_BUFF_INFO_NOTIFY);
				wrapper << buff_num << cur_score;
				return wrapper;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int filter_index, int filter_layer)
			{
				return wrapper << filter_index << filter_layer;
			}
		};
		
		template<>
		struct Make<CMD::astrolabe_info_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, unsigned char level, int exp)
			{
				Make<single_data_header>::From(wrapper,ASTROLABE_INFO_NOTIFY);
				wrapper << level << exp;
				return wrapper;
			}
		};

		template<>
		struct Make<CMD::astrolabe_operate_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int opt, int ret, int arg0,int arg1,int arg2)
			{
				Make<single_data_header>::From(wrapper,ASTROLABE_OPERATE_RESULT);
				wrapper << opt << ret << arg0 << arg1 << arg2;
				return wrapper;
			}
		};

        template <>
        struct Make<CMD::property_score_result>
        {
            template <typename WRAPPER>
            inline static WRAPPER& From(WRAPPER& wrapper, int fighting_score, int viability_score, int client_data)
            {
                Make<single_data_header>::From(wrapper, PROPERTY_SCORE_RESULT);
                wrapper << fighting_score << viability_score << client_data;
                return wrapper;
            }
        };

        template <>
        struct Make<CMD::lookup_enemy_result>
        {
            template <typename WRAPPER>
            inline static WRAPPER& From(WRAPPER& wrapper, int rid, int worldtag, const A3DVECTOR& pos)
            {
                Make<single_data_header>::From(wrapper, LOOKUP_ENEMY_RESULT);
                wrapper << rid << worldtag << pos;
                return wrapper;
            }
        };

		template<>
		struct Make<CMD::mnfaction_player_faction_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int player_faction, int domain_id)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_PLAYER_FACTION_INFO);
				wrapper << player_faction << domain_id;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::mnfaction_resource_point_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int attacker_resource_point, int defender_resource_point)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_RESOURCE_POINT_INFO);
				wrapper << attacker_resource_point << defender_resource_point;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::mnfaction_player_count_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int attend_attacker_player_count, int attend_defender_player_count)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_PLAYER_COUNT_INFO);
				wrapper << attend_attacker_player_count << attend_defender_player_count;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::mnfaction_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int result)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_RESULT);
				wrapper << result;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::mnfaction_resource_tower_state_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int num)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_RESOURCE_TOWER_STATE_INFO);
				wrapper << num;
				return wrapper;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int index, int own_faction, int state ,int time_out)
			{
				return wrapper << index << own_faction << state << time_out;
			}
		};
		template<>
		struct Make<CMD::mnfaction_switch_tower_state_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int num)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_SWITCH_TOWER_STATE_INFO);
				wrapper << num;
				return wrapper;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int index, int own_faction, int state, int time_out)
			{
				return wrapper << index << own_faction << state << time_out;
			}
		};
		template<>
		struct Make<CMD::mnfaction_transmit_pos_state_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int num)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_TRANSMIT_POS_STATE_INFO);
				wrapper << num;
				return wrapper;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int index, int own_faction, int state, int time_out)
			{
				return wrapper << index << own_faction << state << time_out;
			}
		};

		template<>
		struct Make<CMD::mnfaction_resource_point_state_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int cur_degree)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_RESOURCE_POINT_STATE_INFO);
				wrapper << index << cur_degree;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::mnfaction_battle_ground_have_start_time>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int battle_ground_have_start_time)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_BATTLE_GROUND_HAVE_START_TIME);
				wrapper << battle_ground_have_start_time;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::mnfaction_faction_killed_player_num>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int attacker_killed_player_count, int defender_killed_player_count)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_FACTION_KILLED_PLAYER_NUM);
				wrapper << attacker_killed_player_count << defender_killed_player_count;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::mnfaction_shout_at_the_client>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int type, int args)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_SHOUT_AT_THE_CLIENT);
				wrapper << type << args;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::mnfaction_player_pos_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int num)
			{
				Make<single_data_header>::From(wrapper, MNFACTION_PLAYER_POS_INFO);
				wrapper << num;
				return wrapper;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int role_id, float pos_x, float pos_y, float pos_z)
			{
				return wrapper << role_id << pos_x << pos_y << pos_z;
			}
		};
		
		template<>
		struct Make<CMD::fix_position_transmit_add_position>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, int world_tag, float posx, float posy, float posz, unsigned int position_length, const char *position_name)
			{
				Make<single_data_header>::From(wrapper, FIX_POSITION_TRANSMIT_ADD_POSITION);
				wrapper << index << world_tag << posx << posy << posz;
				wrapper.push_back(position_name, position_length);
				return wrapper;
			}
		};

		template<>
		struct Make<CMD::fix_position_transmit_delete_position>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index)
			{
				Make<single_data_header>::From(wrapper, FIX_POSITION_TRANSMIT_DELETE_POSITION);
				wrapper << index;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::fix_position_transmit_rename>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int index, unsigned int position_length, char *position_name)
			{
				Make<single_data_header>::From(wrapper, FIX_POSITION_TRANSMIT_RENAME);
				wrapper << index;
				wrapper.push_back(position_name, position_length);
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::fix_position_energy_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,char is_login, int cur_energy)
			{
				Make<single_data_header>::From(wrapper, FIX_POSITION_ENERGY_INFO);
				wrapper << is_login << cur_energy;
				return wrapper;
			}
		};
		
		template<>
		struct Make<CMD::fix_position_all_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int count)
			{
				Make<single_data_header>::From(wrapper, FIX_POSITION_ALL_INFO);
				wrapper << count;
				return wrapper;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper, int index, int world_tag, float pos_x, float pos_y, float pos_z, unsigned int position_name_length, const char *position_name)
			{
				wrapper << index << world_tag << pos_x << pos_y << pos_z;
				wrapper.push_back(position_name, position_name_length);
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::cash_vip_mall_item_price>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, short start, short end, unsigned short count)
			{
				Make<single_data_header>::From(wrapper,CASH_VIP_MALL_ITEM_PRICE);
				return wrapper << start << end << count;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & AddGoods(WRAPPER & wrapper, short index, char slot, int id, char expire_type, int expire_time, int price, char status, int min_vip_level)
			{
				return wrapper << index << slot << id << expire_type << expire_time << price << status << min_vip_level;
			}
			
		};
		
		template <>
		struct Make<CMD::cash_vip_mall_item_buy_result>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper,char result, short index, char reason)
			{
				Make<single_data_header>::From(wrapper,CASH_VIP_MALL_ITEM_BUY_RESULT);
				return wrapper << result << index << reason; 
			}
		};

		template <>
		struct Make<CMD::cash_vip_info_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int level, int score)
			{
				Make<single_data_header>::From(wrapper,CASH_VIP_INFO_NOTIFY);
				return wrapper << level << score; 
			}
		};
		
		template<>
		struct Make<CMD::purchase_limit_info_notify>
		{
			template <typename WRAPPER>
			inline static WRAPPER & From(WRAPPER & wrapper, int count, char reserve)
			{
				Make<single_data_header>::From(wrapper, PURCHASE_LIMIT_INFO_NOTIFY);
				wrapper << count << reserve;
				return wrapper;
			}
			
			template <typename WRAPPER>
			inline static WRAPPER & Add(WRAPPER & wrapper,int limit_type, int item_id, int have_purchase_count)
			{
				wrapper << limit_type << item_id << have_purchase_count;
				return wrapper;
			}
		};

        template <>
        struct Make<CMD::cash_resurrect_info>
        {
            template <typename WRAPPER>
            inline static WRAPPER& From(WRAPPER& wrapper, int cash_need, int cash_left)
            {
                Make<single_data_header>::From(wrapper, CASH_RESURRECT_INFO);
                wrapper << cash_need << cash_left;
                return wrapper;
            }
        };
		
		template <>
		struct Make<CMD::get_lotery_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER& From(WRAPPER& wrapper, unsigned int manager, unsigned int score, unsigned int count, unsigned int * item )
			{
				Make<single_data_header>::From(wrapper, GET_LOTERY_INFO);
				wrapper << manager << score << count;
				
				get_lotery_info::ITEM * it = (get_lotery_info::ITEM *)item;
				for(size_t i = 0; i < count && i < 5; i++)
				{
					wrapper << it[i].id << it[i].rank_item << it[i].rank_lot << it[i].is_open;
				}
				return wrapper;
			}
		};

		template <>
		struct Make<CMD::get_treasure_info>
		{
			template <typename WRAPPER>
			inline static WRAPPER& From(WRAPPER& wrapper, unsigned char manager, unsigned int score, unsigned int free_count, unsigned int lot_count, unsigned int box_count, void * _lot, void * _box )
			{
				Make<single_data_header>::From(wrapper, GET_TREASURE_INFO);
				wrapper << manager << score << free_count << lot_count << box_count;
				
				get_treasure_info::LOT * lot = (get_treasure_info::LOT *)_lot; // закрытый лот
				get_treasure_info::BOX * box = (get_treasure_info::BOX *)_box; // открытый лот
				
				for(size_t i = 0; i < lot_count && i < 10; i++)
				{
					wrapper << lot[i].id << lot[i].count << lot[i].lot;
				}

				for(size_t i = 0; i < box_count && i < 10; i++)
				{
					wrapper << box[i].id << box[i].box << box[i].count << box[i].lot;
				}				
				return wrapper;
			}
		};
		
		template <>
		struct Make<CMD::get_lotery_items>
		{
			template <typename WRAPPER>
			inline static WRAPPER& From(WRAPPER& wrapper, unsigned int count, unsigned int * item )
			{
				Make<single_data_header>::From(wrapper, GET_LOTERY_ITEMS);
				wrapper << count;
				get_lotery_items::ITEM * it = (get_lotery_items::ITEM *)item;
				for(size_t i = 0; i < count && i < 30; i++)
				{
					wrapper << it[i].id << it[i].count;
				}
				return wrapper;
			}
		};
		

	};
}

#endif
