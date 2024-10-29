#ifndef __ONLINEGAME_COMMON_PROTOCOL_H__
#define __ONLINEGAME_COMMON_PROTOCOL_H__

#include "types.h"

#pragma pack(1)

namespace S2C //server part
{

	namespace INFO
	{
		struct player_info_1
		{
			int cid;
			A3DVECTOR pos;
			unsigned short crc;
			unsigned short custom_crc;	//自定义数据的crc值
			unsigned char  dir;		//256的定点数表示度数
			unsigned char  sec_level;	//修真级别
			unsigned int   object_state;	//当前状态，第0位表示是否死亡
			unsigned int   object_state2;	//当前状态
		};

		struct player_info_2			//name ,customize data 不常改变
		{
			unsigned char size;
			char data[];
		};

		struct player_info_3			//viewdata of equipments and special effect
		{
			unsigned char size;
			char  data[];
		};

		struct player_info_4			//detail
		{
			unsigned short size;
			char	data[];
		};
		struct player_info_00			//自己会经常改变的内容
		{
			short lvl;
			unsigned char combat_state;
			unsigned char sec_level;
			int hp;
			int max_hp;
			int mp;
			int max_mp;
			int target_id;  //todo ddr 1023
			int reserve;
		};
		struct self_info_00
		{
			short lvl;
			unsigned char combat_state;
			unsigned char sec_level;
			int hp;
			int max_hp;
			int mp;
			int max_mp;
			int exp;
			int sp;
			int ap;
		};

		struct npc_info
		{
			int nid;			//npc id
			int tid;			//template id
			int vis_id;			//visible template id
			A3DVECTOR pos;
			unsigned short seed;		// seed of customize data
			unsigned char dir;
			unsigned int  object_state;
			unsigned int  object_state2;
		};

		struct npc_info_00
		{
			int hp;
			int max_hp;
			int target_id;  //todo ddr 1023
		};

		struct matter_info_1
		{
			int mid;
			int tid;
			A3DVECTOR pos;
			unsigned char dir0;
			unsigned char dir1;
			unsigned char rad;
			unsigned char state;
			unsigned char value;
		};
		struct matter_info_2
		{
			int mid;
			unsigned char size;
			unsigned char data[];
		};

		struct self_info_1
		{
			int exp;
			int sp;
			int cid;
			A3DVECTOR pos;
			unsigned short crc;
			unsigned short custom_crc;	//自定义数据的crc值
			unsigned char  dir;		//256的定点数表示度数
			unsigned char  sec_level;	//修真级别
			unsigned int object_state;
			unsigned int object_state2;
		};

		struct move_info
		{
			int cid;
			A3DVECTOR dest;
			unsigned short use_time;
			unsigned short speed;
			unsigned char  move_mode;
		};
			
		union  market_goods
		{
			struct 
			{
				int type;		//物品类型  如果是0 表示没有内容了
			}empty_item;
			struct 
			{
				int type;		//物品类型
				int count;		//剩余多少个 负数表示是买
				unsigned int price;		//单价
				int reserve;
				unsigned short content_length;
				char content[];
			}item;

			struct 
			{
				int type;		//物品类型
				int count;		//剩余多少个 负数表示是买
				unsigned int price;		//单价
				int reserve;
			}order_item;
			

			
		};

	}

	enum		//CMD
	{
		PLAYER_INFO_1,
		PLAYER_INFO_2,
		PLAYER_INFO_3,
		PLAYER_INFO_4,
		PLAYER_INFO_1_LIST,

		PLAYER_INFO_2_LIST,			//5
		PLAYER_INFO_3_LIST,
		PLAYER_INFO_23_LIST,
		SELF_INFO_1,
		NPC_INFO_LIST,

		MATTER_INFO_LIST,			//10
		NPC_ENTER_SLICE,
		PLAYER_ENTER_SLICE,
		OBJECT_LEAVE_SLICE,
		OBJECT_NOTIFY_POS,		//这个命令时暂时的？
		
		OBJECT_MOVE,				//15
		NPC_ENTER_WORLD,
		PLAYER_ENTER_WORLD,
		MATTER_ENTER_WORLD,
		PLAYER_LEAVE_WORLD,
		
		NPC_DEAD,				//20
		OBJECT_DISAPPEAR,
		OBJECT_START_ATTACK,			//已经作废 ，完全没有用 
		SELF_STOP_ATTACK,			//
		SELF_ATTACK_RESULT,
		
		ERROR_MESSAGE,				//25	
		BE_ATTACKED,
		PLAYER_DEAD,
		BE_KILLED,
		PLAYER_REVIVAL,
		
		PICKUP_MONEY,				//30
		PICKUP_ITEM,
		PLAYER_INFO_00,
		NPC_INFO_00,
		OUT_OF_SIGHT_LIST,
		
		OBJECT_STOP_MOVE,			//35
		RECEIVE_EXP,
		LEVEL_UP,
		SELF_INFO_00,
		UNSELECT,

		SELF_ITEM_INFO,				//40
		SELF_ITEM_EMPTY_INFO,
		SELF_INVENTORY_DATA,
		SELF_INVENTORY_DETAIL_DATA,
		EXCHANGE_INVENTORY_ITEM,

		MOVE_INVENTORY_ITEM,			//45
		PLAYER_DROP_ITEM,
		EXCHANGE_EQUIPMENT_ITEM,
		EQUIP_ITEM,
		MOVE_EQUIPMENT_ITEM,	

		SELF_GET_EXT_PROPERTY,			//50
		SET_STATUS_POINT,
		SELECT_TARGET,
		PLAYER_EXTPROP_BASE,
		PLAYER_EXTPROP_MOVE,

		PLAYER_EXTPROP_ATTACK,			//55
		PLAYER_EXTPROP_DEFENSE,
		TEAM_LEADER_INVITE,
		TEAM_REJECT_INVITE,
		TEAM_JOIN_TEAM,

		TEAM_MEMBER_LEAVE,			//60
		TEAM_LEAVE_PARTY,
		TEAM_NEW_MEMBER,
		TEAM_LEADER_CANCEL_PARTY,
		TEAM_MEMBER_DATA,
							
		TEAMMATE_POS,				//65
		EQUIPMENT_DATA,			//用户的装备数据，影响表现
		EQUIPMENT_INFO_CHANGED,	
		EQUIPMENT_DAMAGED,		//装备损坏
		TEAM_MEMBER_PICKUP,		//队友捡起装备

		NPC_GREETING,				//70
		NPC_SERVICE_CONTENT,
		PURCHASE_ITEM,
		ITEM_TO_MONEY,	
		REPAIR_ALL,

		REPAIR,					//75
		RENEW,
		SPEND_MONEY,
		PICKUP_MONEY_IN_TRADE,
		PICKUP_ITEM_IN_TRADE,

		PICKUP_MONEY_AFTER_TRADE,		//80
		PICKUP_ITEM_AFTER_TRADE,
		GET_OWN_MONEY,
		OBJECT_ATTACK_ONCE,			//已经作废 ，完全没有用
		SELF_START_ATTACK,
	
		OBJECT_CAST_SKILL,			//85
		SKILL_INTERRUPTED,
		SELF_SKILL_INTERRUPTED,
		SKILL_PERFORM,
		OBJECT_BE_ATTACKED,			//已经作废 ，完全没有用

		SKILL_DATA,				//90
		PLAYER_USE_ITEM,
		EMBED_ITEM,
		CLEAR_EMBEDDED_CHIP,
		COST_SKILL_POINT,

		LEARN_SKILL,				//95
		OBJECT_TAKEOFF,
		OBJECT_LANDING,
		FLYSWORD_TIME_CAPACITY,
		OBTAIN_ITEM,

		PRODUCE_START,				//100
		PRODUCE_ONCE,
		PRODUCE_END,
		DECOMPOSE_START,
		DECOMPOSE_END,

		TASK_DATA,				//105
		TASK_VAR_DATA,
		OBJECT_START_USE,
		OBJECT_CANCEL_USE,
		OBJECT_USE_ITEM,

		OBJECT_START_USE_WITH_TARGET,		//110
		OBJECT_SIT_DOWN,
		OBJECT_STAND_UP,
		OBJECT_DO_EMOTE,
		SERVER_TIMESTAMP,

		NOTIFY_ROOT,				//115
		DISPEL_ROOT,
		INVADER_RISE,
		PARIAH_RISE,
		INVADER_FADE,

		OBJECT_ATTACK_RESULT,			//120
		BE_HURT,
		HURT_RESULT,
		SELF_STOP_SKILL,
		UPDATE_VISIBLE_STATE,

		OBJECT_STATE_NOTIFY,			//125
		PLAYER_GATHER_START,
		PLAYER_GATHER_STOP,
		TRASHBOX_PASSWD_CHANGED,
		TRASHBOX_PASSWD_STATE,

		TRASHBOX_OPEN,				//130
		TRASHBOX_CLOSE,	
		TRASHBOX_WEALTH,
		EXCHANGE_TRASHBOX_ITEM,
		MOVE_TRASHBOX_ITEM,
		
		EXCHANGE_TRASHBOX_INVENTORY,		//135
		INVENTORY_ITEM_TO_TRASH,
		TRASH_ITEM_TO_INVENTORY,
		EXCHANGE_TRASH_MONEY,
		ENCHANT_RESULT,

		SELF_NOTIFY_ROOT,			//140
		OBJECT_DO_ACTION,
		SELF_SKILL_ATTACK_RESULT,
		OBJECT_SKILL_ATTACK_RESULT,
		BE_SKILL_ATTACKED,

		PLAYER_SET_ADV_DATA,			//145
		PLAYER_CLR_ADV_DATA,
		PLAYER_IN_TEAM,		
		TEAM_APPLY_REQUEST,
		OBJECT_DO_EMOTE_RESTORE,

		CONCURRENT_EMOTE_REQUEST,		//150
		DO_CONCURRENT_EMOTE,			
		MATTER_PICKUP,
		MAFIA_INFO_NOTIFY,
		MAFIA_TRADE_START,
		
		MAFIA_TRADE_END,			//155
		TASK_DELIVER_ITEM,
		TASK_DELIVER_REPUTATION,
		TASK_DELIVER_EXP,
		TASK_DELIVER_MONEY,

		TASK_DELIVER_LEVEL2,			//160
		PLAYER_REPUTATION,
		IDENTIFY_RESULT,
		PLAYER_CHANGE_SHAPE,
		OBJECT_ENTER_SANCTUARY,

		OBJECT_LEAVE_SANCTUARY,			//165
		PLAYER_OPEN_MARKET,
		SELF_OPEN_MARKET,
		PLAYER_CANCEL_MARKET,
		PLAYER_MARKET_INFO,

		PLAYER_MARKET_TRADE_SUCCESS,		//170
		PLAYER_MARKET_NAME,
		PLAYER_START_TRAVEL,
		SELF_START_TRAVEL,
		PLAYER_COMPLETE_TRAVEL,

		GM_TOGGLE_INVINCIBLE,			//175
		GM_TOGGLE_INVISIBLE,
		SELF_TRACE_CUR_POS,
		OBJECT_CAST_INSTANT_SKILL,	
		ACTIVATE_WAYPOINT,

		PLAYER_WAYPOINT_LIST,			//180
		UNLOCK_INVENTORY_SLOT,
		TEAM_INVITE_PLAYER_TIMEOUT,
		PLAYER_ENABLE_PVP,
		PLAYER_DISABLE_PVP,

		PLAYER_PVP_COOLDOWN,			//185
		COOLDOWN_DATA,
		SKILL_ABILITY_NOTFIY,
		PERSONAL_MARKET_AVAILABLE,
		BREATH_DATA,

		PLAYER_STOP_DIVE,			//190
		TRADE_AWAY_ITEM,
		PLAYER_ENABLE_FASHION_MODE,
		ENABLE_FREE_PVP_MODE,
		OBJECT_IS_INVALID,

		PLAYER_ENABLE_EFFECT,			//195
		PLAYER_DISABLE_EFFECT,
		ENABLE_RESURRECT_STATE,		
		SET_COOLDOWN,
		CHANGE_TEAM_LEADER,		

		KICKOUT_INSTANCE,			//200
		PLAYER_COSMETIC_BEGIN,
		PLAYER_COSMETIC_END,
		COSMETIC_SUCCESS,
		OBJECT_CAST_POS_SKILL,

		CHANGE_MOVE_SEQ,			//205
		SERVER_CONFIG_DATA,
		PLAYER_RUSH_MODE,
		TRASHBOX_CAPACITY_NOTIFY,
		NPC_DEAD_2,

		PRODUCE_NULL,				//210
		ACTIVE_PVP_COMBAT_STATE,
		DOUBLE_EXP_TIME,
		AVAILABLE_DOUBLE_EXP_TIME,
		DUEL_RECV_REQUEST,

		DUEL_REJECT_REQUEST,			//215
		DUEL_PREPARE,
		DUEL_CANCEL,
		DUEL_START,
		DUEL_STOP,
		
		DUEL_RESULT,				//220
		PLAYER_BIND_REQUEST,
		PLAYER_BIND_INVITE,
		PLAYER_BIND_REQUEST_REPLY,
		PLAYER_BIND_INVITE_REPLY,

		PLAYER_BIND_START,			//225
		PLAYER_BIND_STOP,
		PLAYER_MOUNTING,
		PLAYER_EQUIP_DETAIL,
		ELSE_DUEL_START,

		PARIAH_DURATION,			//230
		PLAYER_GAIN_PET,
		PLAYER_FREE_PET,
		PLAYER_SUMMON_PET,
		PLAYER_RECALL_PET,

		PLAYER_START_PET_OP,			//235
		PLAYER_STOP_PET_OP,
		PLAYER_PET_RECV_EXP,
		PLAYER_PET_LEVELUP,
		PLAYER_PET_ROOM,

		PLAYER_PET_ROOM_CAPACITY,		//240
		PLAYER_PET_HONOR_POINT,
		PLAYER_PET_HUNGER_GAUGE,
		ENTER_BATTLEGROUND,
		TURRET_LEADER_NOTIFY,

		BATTLE_RESULT,				//245
		BATTLE_SCORE,
		PET_DEAD,
		PET_REVIVE,
		PET_HP_NOTIFY,

		PET_AI_STATE,				//250
		REFINE_RESULT,
		PET_SET_COOLDOWN,
		PLAYER_CASH,
		PLAYER_BIND_SUCCESS,

		PLAYER_CHANGE_INVENTORY_SIZE,		//255
		PLAYER_PVP_MODE,
		PLAYER_WALLOW_INFO,
		PLAYER_USE_ITEM_WITH_ARG,
		OBJECT_USE_ITEM_WITH_ARG,

		PLAYER_CHANGE_SPOUSE,			//260
		NOTIFY_SAFE_LOCK,
		ELF_VIGOR,		//lgc
		ELF_ENHANCE,
		ELF_STAMINA,
		
		ELF_CMD_RESULT,		//265
		COMMON_DATA_NOTIFY,
		COMMON_DATA_LIST,
		PLAYER_ELF_REFINE_ACTIVATE,
		PLAYER_CAST_ELF_SKILL,

		MALL_ITEM_PRICE,		//270
		MALL_ITEM_BUY_FAILED,
		PLAYER_ELF_LEVELUP,
		PLAYER_PROPERTY,
		PLAYER_CAST_RUNE_SKILL,

		PLAYER_CAST_RUNE_INSTANT_SKILL,	//275
		EQUIP_TRASHBOX_ITEM,
		SECURITY_PASSWD_CHECKED,
		OBJECT_INVISIBLE,
		HP_STEAL,
		
		PLAYER_DIVIDEND,                //280
		DIVIDEND_MALL_ITEM_PRICE,
		DIVIDEND_MALL_ITEM_BUY_FAILED,
		ELF_EXP,
		PUBLIC_QUEST_INFO,

		PUBLIC_QUEST_RANKS,				//285
		MULTI_EXP_INFO,
		CHANGE_MULTI_EXP_STATE,
		WORLD_LIFE_TIME,
		WEDDING_BOOK_LIST,
		
		WEDDING_BOOK_SUCCESS,		//290
		CALC_NETWORK_DELAY,
		PLAYER_KNOCKBACK,
		PLAYER_SUMMON_PLANT_PET,
		PLANT_PET_DISAPPEAR,

		PLANT_PET_HP_NOTIFY,		//295
		PET_PROPERTY,
		FACTION_CONTRIB_NOTIFY,
		FACTION_FORTRESS_INFO,
		ENTER_FACTIONFORTRESS,

		FACTION_RELATION_NOTIFY,	//300
		PLAYER_EQUIP_DISABLED,
		PLAYER_SPEC_ITEM_LIST,
		OBJECT_START_PLAY_ACTION,
		OBJECT_STOP_PLAY_ACTION,

		CONGREGATE_REQUEST,			//305
		REJECT_CONGREGATE,
		CONGREGATE_START,
		CANCEL_CONGREGATE,
		ENGRAVE_START,

		ENGRAVE_END,				//310
		ENGRAVE_RESULT,
		DPS_DPH_RANK,
		ADDONREGEN_START,
		ADDONREGEN_END,
		
		ADDONREGEN_RESULT,			//315
		INVISIBLE_OBJ_LIST,
		SET_PLAYER_LIMIT,
		PLAYER_TELEPORT,
		OBJECT_FORBID_BE_SELECTED,

		PLAYER_INVENTORY_DETAIL,	//320
		PLAYER_FORCE_DATA,
		PLAYER_FORCE_CHANGED,
		PLAYER_FORCE_DATA_UPDATE,
		FORCE_GLOBAL_DATA,

		ADD_MULTIOBJ_EFFECT,		//325
		REMOVE_MULTIOBJ_EFFECT,
		ENTER_WEDDING_SCENE,
		PRODUCE4_ITEM_INFO,
		ONLINE_AWARD_DATA,

		TOGGLE_ONLINE_AWARD,		//330
		PLAYER_PROFIT_TIME,
		ENTER_NONPENALTY_PVP_STATE,
		SELF_COUNTRY_NOTIFY,
		PLAYER_COUNTRY_CHANGED,

		ENTER_COUNTRYBATTLE,		//335
		COUNTRYBATTLE_RESULT,
		COUNTRYBATTLE_SCORE,
		COUNTRYBATTLE_RESURRECT_REST_TIMES,
		COUNTRYBATTLE_FLAG_CARRIER_NOTIFY,
		
		COUNTRYBATTLE_BECAME_FLAG_CARRIER,	//340
		COUNTRYBATTLE_PERSONAL_SCORE,
		COUNTRYBATTLE_FLAG_MSG_NOTIFY,
		DEFENSE_RUNE_ENABLED,
		COUNTRYBATTLE_INFO,
		
		SET_PROFITTIME_STATE,		//345
		CASH_MONEY_EXCHG_RATE,
		PET_REBUILD_INHERIT_START,
		PET_REBUILD_INHERIT_INFO,
		PET_REBUILD_INHERIT_END,
		
		PET_EVOLUTION_DONE,			//350
		PET_REBUILD_NATURE_START,
		PET_REBUILD_NATURE_INFO,
		PET_REBUILD_NATURE_END,
		EQUIP_ADDON_UPDATE_NOTIFY,

		SELF_KING_NOTIFY,			//355
		PLAYER_KING_CHANGED,
		NOTIFY_MERIDIAN_DATA,	
		TRY_REFINE_MERIDIAN_RESULT,
		COUNTRYBATTLE_STRONGHOLD_STATE_NOTIFY,
	
		QUERY_TOUCH_POINT,		//360
		COST_TOUCH_POINT,
		QUERY_ADDUP_MONEY,
		QUERY_TITLE,
		CHANGE_CURR_TITLE,	

		MODIFY_TITLE_NOTIFY, 		//365
		REFRESH_SIGNIN,
		PARALLEL_WORLD_INFO,
		PLAYER_REINCARNATION,
		REINCARNATION_TOME_INFO,

		ACTIVATE_REINCARNATION_TOME,	//370
		UNIQUE_DATA_NOTIFY,
		GIFTCARD_REDEEM_NOTIFY,
		REALM_EXP,
		REALM_LEVEL_UP,     
		
		ENTER_TRICKBATTLE,				//375
		TRICKBATTLE_PERSONAL_SCORE,		
		TRICKBATTLE_CHARIOT_INFO,	
		PLAYER_LEADERSHIP,
		GENERALCARD_COLLECTION_DATA,
		
		ADD_GENERALCARD_COLLECTION,		//380
		REFRESH_FATERING,
		MINE_GATHERD,
		PLAYER_ACTIVE_COMBAT,
		PLAYER_QUERY_CHARIOTS,

		COUNTRYBATTLE_LIVE_RESULT,		//385
		RANDOM_MALL_SHOPPING_RESULT,
		PLAYER_MAFIA_PVP_MASK_NOTIFY,
		PLAYER_WORLD_CONTRIB,
		RANDOM_MAP_ORDER,

		SCENE_SERVICE_NPC_LIST,			//390
		NPC_VISIBLE_TID_NOTIFY,
		CLIENT_SCREEN_EFFECT,
        EQUIP_CAN_INHERIT_ADDONS,
		COMBO_SKILL_PREPARE,

		INSTANCE_REENTER_NOTIFY,		//395
		PRAY_DISTANCE_CHANGE,
		ASTROLABE_INFO_NOTIFY,
		ASTROLABE_OPERATE_RESULT,
		SOLO_CHALLENGE_AWARD_INFO_NOTIFY,
		
		SOLO_CHALLENGE_OPERATE_RESULT,  //400
		SOLO_CHALLENGE_CHALLENGING_STATE_NOTIFY,
		SOLO_CHALLENGE_BUFF_INFO_NOTIFY,
        PROPERTY_SCORE_RESULT,
		MNFACTION_RESOURCE_POINT_INFO,
		
		MNFACTION_PLAYER_COUNT_INFO,  //405
		MNFACTION_RESULT,               
		MNFACTION_RESOURCE_TOWER_STATE_INFO,
		MNFACTION_SWITCH_TOWER_STATE_INFO,
		MNFACTION_TRANSMIT_POS_STATE_INFO,
		
		MNFACTION_RESOURCE_POINT_STATE_INFO, //410
		MNFACTION_PLAYER_FACTION_INFO,
		MNFACTION_BATTLE_GROUND_HAVE_START_TIME,
		MNFACTION_FACTION_KILLED_PLAYER_NUM,
		MNFACTION_SHOUT_AT_THE_CLIENT,

		MNFACTION_PLAYER_POS_INFO,          //415
		FIX_POSITION_TRANSMIT_ADD_POSITION,
		FIX_POSITION_TRANSMIT_DELETE_POSITION,
		FIX_POSITION_TRANSMIT_RENAME,
		FIX_POSITION_ENERGY_INFO,

		FIX_POSITION_ALL_INFO,              // 420
		CASH_VIP_MALL_ITEM_PRICE,
		CASH_VIP_MALL_ITEM_BUY_RESULT,
		CASH_VIP_INFO_NOTIFY,
		PURCHASE_LIMIT_INFO_NOTIFY,

        LOOKUP_ENEMY_RESULT,                // 425
        CASH_RESURRECT_INFO,
		
		//162+
		GET_EQUIP_DATA = 507,
		GET_SHIELD_ENERGY = 513,
		
		GET_LOTERY_ITEMS = 433,
		GET_TREASURE_INFO = 434,
		GET_LOTERY_INFO = 523,
		
		
	};

	enum 
	{
		ERR_SUCCESS,			//0
		ERR_INVALID_TARGET,
		ERR_OUT_OF_RANGE,
		ERR_FATAL_ERR,
		ERR_COMMAND_IN_ZOMBIE,
		ERR_ITEM_NOT_IN_INVENTORY, //5
		ERR_ITEM_CANT_PICKUP,
		ERR_INVENTORY_IS_FULL,
		ERR_ITEM_CANNOT_EQUIP,
		ERR_CANNOT_ATTACK,
		ERR_TEAM_CANNOT_INVITE,  //10
		ERR_TEAM_JOIN_FAILED,
		ERR_TEAM_ALREADY_INVITE,
		ERR_TEAM_INVITE_TIMEOUT,
		ERR_SERVICE_UNAVILABLE,
		ERR_SERVICE_ERR_REQUEST,  //15
		ERR_OUT_OF_FUND,
		ERR_CANNOT_LOGOUT,
		ERR_CANNOT_USE_ITEM,
		ERR_TASK_NOT_AVAILABLE,
		ERR_SKILL_NOT_AVAILABLE, //20
		ERR_CANNOT_EMBED,
		ERR_CANNOT_LEARN_SKILL,
		ERR_CANNOT_HEAL_IN_COMBAT,
		ERR_CANNOT_RECHARGE,
		ERR_NOT_ENOUGH_MATERIAL, //25
		ERR_PRODUCE_FAILED,
		ERR_DECOMPOSE_FAILED,
		ERR_CANNOT_SIT_DOWN,
		ERR_CANNOT_EQUIP_NOW,
		ERR_MINE_HAS_BEEN_LOCKED,//30
		ERR_MINE_HAS_INVALID_TOOL,
		ERR_MINE_GATHER_FAILED,
		ERR_OTHER_SESSION_IN_EXECUTE,
		ERR_INVALID_PASSWD_FORMAT,
		ERR_PASSWD_NOT_MATCH,//35
		ERR_TRASH_BOX_NOT_OPEN,
		ERR_ENOUGH_MONEY_IN_TRASH_BOX,
		ERR_TEAM_REFUSE_APPLY,
		ERR_CONCURRENT_EMOTE_REFUSED,
		ERR_EQUIPMENT_IS_LOCKED,//40
		ERR_CANNOT_OPEN_PLAYER_MARKET,
		ERR_INVALID_ITEM,
		ERR_YOU_HAS_BEEN_BANISHED,
		ERR_CAN_NOT_DROP_ITEM,
		ERR_INVALID_PRIVILEGE,//45
		ERR_PLAYER_NOT_EXIST,
		ERR_CAN_NOT_DISABLE_PVP_STATE,
		ERR_CAN_NOT_UNLEARN_SKILL,
		ERR_COMMAND_IN_IDLE,
		ERR_COMMAND_IN_SEALED,//50
		ERR_LEVEL_NOT_MATCH,
		ERR_CANNOT_ENTER_INSTANCE,
		ERR_SKILL_IS_COOLING,
		ERR_OBJECT_IS_COOLING,
		ERR_CANNOT_FLY,//55
		ERR_CAN_NOT_RESET_INSTANCE,
		ERR_INVENTORY_IS_LOCKED,
		ERR_TOO_MANY_PLAYER_IN_INSTANCE,
		ERR_TOO_MANY_INSTANCE,
		ERR_FACTION_BASE_NOT_READY,//60
		ERR_FACTION_BASE_DENIED,
		ERR_CAN_NOT_JUMP_BETWEEN_INSTANCE,
		ERR_NOT_ENOUGH_REST_TIME,
		ERR_CANNOT_DUEL_TWICE,
		ERR_CREATE_DUEL_FAILED,//65
		ERR_INVALID_OPERATION_IN_COMBAT,
		ERR_INVALID_GENDER,
		ERR_INVALID_BIND_REQUEST,
		ERR_INVALID_BIND_REPLY,
		ERR_FORBIDDED_OPERATION,//70
		ERR_PET_IS_ALEARY_ACTIVE,
		ERR_PET_IS_NOT_EXIST,
		ERR_PET_IS_NOT_ACTIVE,
		ERR_PET_FOOD_TYPE_NOT_MATCH,
		ERR_BATTLEFIELD_IS_CLOSED,//75
		ERR_PET_CAN_NOT_BE_HATCHED,
		ERR_PET_CAN_NOT_BE_RESTORED,
		ERR_FACTION_IS_NOT_MATCH,
		ERR_CANNOT_QUERY_ENEMY_EQUIP,
		ERR_NPC_SERVICE_IS_BUSY,//80
		ERR_PET_CAN_NOT_MOUNT,
		ERR_CAN_NOT_RESET_PP,
		ERR_BATTLEFIELD_IS_FINISHED,
		ERR_HERE_CAN_NOT_DUEL,
		ERR_SUMMON_PET_INVALID_POS,//85
		ERR_CONTROL_TOO_MANY_TURRETS,
		ERR_CANNOT_SUMMON_DEAD_PET,
		ERR_PET_IS_NOT_DEAD,
		ERR_CANNOT_BIND_HERE,
		ERR_INVALID_PLAYER_CALSS,//90
		ERR_RUNE_IS_IN_EFFECT,
		ERR_REFINE_CAN_NOT_REFINE,
		ERR_PET_SKILL_IN_COOLDOWN,
		ERR_GSHOP_INVALID_REQUEST,
		ERR_CAN_NOT_STOP_DESTROY_BIND_ITEM,//95
		ERR_ITEM_CANNOT_UNEQUIP,
		ERR_USE_ITEM_FAILED,
		ERR_DYE_FAILED,
		ERR_FASHION_CAN_NOT_BE_DYED,
		ERR_DYE_NOT_ENOUGH,//100
		ERR_CAN_NOT_TRANSMIT_REFINE,
		ERR_LOW_LEVEL_TRANSMIT_REFINE,
		ERR_DEST_CAN_NOT_TRANSMIT_REFINE,
		ERR_TRANSMIT_REFINE_NEED_BIND,
		ERR_TRANSMIT_REFINE_NO_MATERIAL,//105
		ERR_MAKE_SLOT_FAILURE,
		ERR_MAKE_SLOT_SUCCESS,
		ERR_FORBIDDED_OPERATION_IN_SAFE_LOCK,
		ERR_ELF_ADD_ATTRIBUTE_FAILED,	//lgc
		ERR_ELF_ADD_GENIUS_FAILED,//110
		ERR_ELF_PLAYER_INSERT_EXP_FAILED,
		ERR_ELF_INSERT_EXP_USE_PILL_FAILED,
		ERR_ELF_EQUIP_ITEM_FAILED,
		ERR_ELF_CHANGE_SECURE_STATUS_FAILED,
		ERR_ELF_DEC_ATTRIBUTE_FAILED,//115
		ERR_ELF_FLUSH_GENIUS_FAILED,
		ERR_ELF_LEARN_SKILL_FAILED,
		ERR_ELF_FORGET_SKILL_FAILED,
		ERR_ELF_REFINE_CANNOT_REFINE,
		ERR_ELF_REFINE_TRANSMIT_FAILED,//120
		ERR_ELF_REF_TRANS_FROM_TRADE_TO_UNTRADE,
		ERR_ELF_DECOMPOSE_FAILED,
		ERR_DECOMPOSE_UNTRADABLE_ELF,
		ERR_ELF_DECOMPOSE_EXP_ZERO,
		ERR_ELF_DESTROY_ITEM_FAILED,//125
		ERR_ELF_NOT_ENOUGH_VIGOR,
		ERR_ELF_NOT_ENOUGH_STAMINA,
		ERR_CAST_ELF_SKILL_FAILED,
		ERR_ELF_REFINE_ACTIVATE_FAILED,
		ERR_ELF_CANNOT_UNEQUIP_IN_COMBAT_STATE,//130
		ERR_CAST_ELF_SKILL_IN_COOLDOWN,
		ERR_ELF_CMD_IN_COOLDOWN,
		ERR_TRADER_MONEY_REACH_UPPER_LIMIT,
		ERR_TRADER_MONEY_ISNOT_ENOUGH,
		ERR_BUYER_MONEY_REACH_UPPER_LIMIT,//135
		ERR_CANNOT_EQUIP_TRASHBOX_FASHION_ITEM,
		ERR_SECURITY_PASSWD_UNCHECKED,
		ERR_OPERTION_DENYED_IN_INVISIBLE,
		ERR_CANNOT_TOGGLE_MULTI_EXP,
		ERR_WEDDING_NOT_ONGOING,//140
		ERR_WEDDING_CANNOT_BOOK,
		ERR_WEDDING_CANNOT_CANCELBOOK,
		ERR_ITEM_CANNOT_SHARPEN,
		ERR_FACTION_FORTRESS_OP_DENYED,
		ERR_FACTION_FORTRESS_OP_FAILED,//145
		ERR_NOT_ENOUGH_FACTION_CONTRIB,
		ERR_FACTION_FORTRESS_ISKICK,
		ERR_SPOUSE_NOT_IN_SAME_SCENE,
		ERR_PET_CAN_NOT_BE_DYED,
		ERR_OPERTION_DENYED_IN_CUR_SCENE,//150
		ERR_NOT_ENOUGH_FORCE_CONTRIB,
		ERR_NOT_ENOUGH_FORCE_REPU,
		ERR_NOT_ENOUGH_AWARD_TIME,
		ERR_ALREADY_JOIN_COUNTRY,
		ERR_NOT_JOIN_COUNTRY,//155
		ERR_NOT_TEAM_LEADER,
		ERR_EQUIP_SIGNATURE_WRONG,
		ERR_ITEM_PRICE_MISMATCH,
		ERR_PET_CANNOT_EVOLUTION,
		ERR_PET_TYPE_WRONG,	//160
		ERR_ITEM_FORBID_SHOP,
		ERR_ITEM_FORBID_SELL,
		ERR_CANNOT_CHANGEDS,
		ERR_SEC_LEVEL_NOT_MATCH,
		ERR_PLAYER_RENAME,//165
		ERR_NO_EQUAL_EQUIPMENT_FAIL,//  没有合适装备或装备孔
		ERR_NO_EQUAL_RECIPE_FAIL, // 和配方不匹配
		ERR_NO_EQUAL_SOURCE_FAIL, // 源魂石不匹配
		ERR_NO_EQUAL_DEST_FAIL, // 目标魂石不匹配
	    ERR_MODIFY_ADDON_FAIL, // 魂石转化或替换执行出现错误 170
		ERR_SHOP_NOT_OPEN,		//商城没有开放
		ERR_TRY_REFINE_MERIDIAN_FAIL,
		ERR_CANNOT_REBUILD,
		ERR_CANNOT_SWITCH_IN_PARALLEL_WORLD,
		ERR_PARALLEL_WORLD_NOT_EXIST,			//175
		ERR_TOO_MANY_PLAYER_IN_PARALLEL_WORLD,
		ERR_REINCARNATION_CONDITION,
		ERR_REINCARNATION_REWRITE_TOME,
		ERR_REINCARNATION_ACTIVE_TOME,
		ERR_MINE_NOT_OWNER,					//180
		ERR_GENERALCARD_REBIRTH_CONDITION,
		ERR_GENERALCARD_INSERT_EXP,
		ERR_CANNOT_EQUIP_TRASHBOX_ITEM,
		ERR_MINE_SOUL_GATHER_TOO_MUCH,	//达到每日采集元魂上限
		ERR_USE_SOUL_TOP_LEVEL,	//命轮到满级了，不能使用元魂 185
		ERR_USE_SOUL_EXP_FULL,	//命轮经验满了，不能使用元魂
		ERR_MINE_GATHER_IS_COOLING,	//采矿正在冷却中
		ERR_ITEM_CANNOT_IMPROVE,	//无法进行改良
		ERR_MAFIA_NO_PERMISSION,	//帮派操作无权
		ERR_OTHER_ACTION_IN_EXECUTE,		//190
		ERR_ACTION_DENYED_IN_NON_MOVE_SESSION,
		ERR_ATTACK_SESSION_DENYED_IN_ACTION,
		ERR_INSTANCE_REENTER_FAIL,
        ERR_CHANGE_GENDER_STATE,        // 194 状态不是normal
        ERR_CHANGE_GENDER_GENDER,       // 195 变成相同性别
        ERR_CHANGE_GENDER_CLS,          // 196 职业限制
        ERR_CHANGE_GENDER_MARRIED,      // 197 角色已婚
        ERR_CHANGE_GENDER_FASHION,      // 198 佩戴时装或者时装武器
        ERR_CHANGE_GENDER_PROFILE,      // 199 登记过情缘系统
		ERR_CHANGE_GENDER_TASK,         // 200 存在性别相关任务
        ERR_MAKE_SLOT_FOR_DECOR_PROB,   // 201 概率打孔失败 即未命中
		ERR_ASTROLABE_OPT_FAIL,
		ERR_ASTROLABE_SWALLOW_LIMIT,	// 203
		ERR_SOLO_CHALLENGE_TOP_STAGE,    // 204 已到达单人副本最高等级
		ERR_SOLO_CHALLENGE_FAILURE,      // 205 进入单人副本失败
		ERR_SOLO_CHALLENGE_AWARD_FAILURE,// 206 单人副本发奖失败
		ERR_SOLO_CHALLENGE_SCORE_COST,   // 207
		ERR_SOLO_CHALLENGE_SCORE_TOO_FEW,   // 208 积分不足
		ERR_SOLO_CHALLENGE_SCORE_COST_COOLDOWN, //209 COOLDOWN
		ERR_SOLO_CHALLENGE_SELECT_STAGE_COOLDOWN,//210
		ERR_MNFACTION_NOT_IN_BATTLE,     //211 不在跨服帮战战场中
		ERR_NOT_IN_FACTION,             //212  没有跨服帮派信息
		ERR_MNFACTION_TRANSMIT_POS_FACTION, //213 当前传送点不归属于本帮
		ERR_MNFACTION_SIGN_UP_C_NOT_ENOUGH_CITY,//214 报名C级城不够5块
		ERR_MNFACTION_SIGN_UP_LOWER_TYPE,//215 报名A级或B级，无低级领地
		ERR_MNFACTION_GATHER_FAILED,     //216 采矿失败
		ERR_MNFACTION_FACTION_GATHERING, //217 本帮成员正在采集
		ERR_MNFACTION_BELONG_TO_OWN_FACTION,    //218 资源已归属本帮
		ERR_MNFACTION_HAVE_DESTROYED,           //219 资源塔已损毁
		ERR_REALM_LEVEL_NOT_MATCH,//220 境界等级不够
		ERR_CARNIVAL_COUNT_LIMIT, //221 跨服活动人数限制
		ERR_SOLO_CHALLENGE_FILTER_STACK_MAX,//222 单人副本状态包叠加达到上限
		ERR_MNFACTION_MULTI_DOMAIN,             //223 一个角色只能进入一个战场
		ERR_MNFACTION_INVITE_COUNT_PERDOMAIN_MAXMUM,    //224 进入战场的角色太多
		ERR_MNFACTION_FORBID_ENTER,                           //225 本帮派不允许进入
		ERR_CASH_VIP_LIMIT,		// 226 消费vip等级不够
		ERR_FIX_POSITION_TRANSMIT_CANNOT_ADD_IN_THIS_WORLDTAG, //227 此地图不支持定位传送
		ERR_FIX_POSITION_TRANSMIT_CANNOT_FIND, //228 无此传送点
		ERR_FIX_POSITION_TRANSMIT_ENERGY_NOT_ENOUGH,//229 定点传送能量不足
		ERR_SHOPPING_TIMES_LIMIT, //230 达到限购次数
		ERR_FIX_POSITION_TRANSMIT_MAX_NUM, //231 定位传送点达到最高数量
		ERR_FIX_POSITION_TRANSMIT_ENERGY_MAX, //232 定位传送能量达到最大值
		ERR_SHOPPING_TIMES_LIMIT_ITEM_CANNOT_GIVE,//233 限购商品不允许赠送
		ERR_SHOPPING_TIMES_LIMIT_ITEM_CANNOT_ASK_FOR,//234 限购商品不允许索取
		ERR_SHOPPING_VIP_LIMIT_ITEM_CANNOT_GIVE,//235 VIP等级限制物品不允许赠送
		ERR_SHOPPING_VIP_LIMIT_ITEM_CANNOT_ASK_FOR,//236 VIP等级限制物品不允许索取
	};

	enum
	{
		DROP_TYPE_GM,
		DROP_TYPE_PLAYER,
		DROP_TYPE_TAKEOUT,
		DROP_TYPE_TASK,
		DROP_TYPE_RECHARGE,
		DROP_TYPE_DESTROY,
		DROP_TYPE_DEATH,
		DROP_TYPE_PRODUCE,
		DROP_TYPE_DECOMPOSE,
		DROP_TYPE_TRADEAWAY,
		DROP_TYPE_RESURRECT,
		DROP_TYPE_USE,
		DROP_TYPE_RUNE,
		DROP_TYPE_EXPIRE,

	};

	enum		//elf cmd lgc
	{
		ELF_LEVELUP,
		ELF_LEARN_SKILL,
		ELF_FORGET_SKILL,
		ELF_REFINE,
		ELF_DECOMPOSE,
		ELF_DEC_ATTRIBUTE,
		ELF_ADD_GENIUS,
		ELF_EQUIP_ITEM,
		ELF_DESTROY_ITEM,
		ELF_RECHARGE,
	};

	namespace CMD
	{
		using namespace INFO;

		struct player_enter_slice	//player进入可见区域
		{	
			single_data_header header;
			player_info_1 data;
		};

		struct npc_enter_slice
		{
			single_data_header header;
			npc_info data;
		};

		struct leave_slice	//player离开可见区域
		{	
			single_data_header header;
			int id;
		};

		struct notify_pos		//player更新位置
		{	
			single_data_header header;
			A3DVECTOR pos;
			int tag;
			int key;
		};

		struct self_info_1
		{
			single_data_header header;
			INFO::self_info_1 info;
		};

		struct	player_info_1_list 		//player list
		{
			multi_data_header header;
			player_info_1 list[];
		};

		struct player_info_2_list 
		{
			multi_data_header header;
			/*
			   struct		//假设的代码，实际上由于info2是变长的结构，所以无法这样组织
			   {
			   int cid;
			   player_info_2 info;
			   }list[];
			 */
			char data[1];
		};

		struct player_info_3_list 
		{
			multi_data_header header;
			/*
			   struct		//假设的代码，实际上由于info3是变长的结构，所以无法这样组织
			   {
			   int cid;
			   player_info_3 info;
			   }list[];
			 */
			char data[1];
		};

		struct player_info_23_list 
		{
			multi_data_header header;
			/*
			   struct		//假设的代码，实际上由于info2/3是变长的结构，所以无法这样组织
			   {
			   int cid;
			   player_info_2 info2;
			   player_info_3 info3;
			   }list[];
			 */
			char data[1];
		};

		struct	npc_info_list 		// npc list
		{
			multi_data_header header;
			npc_info list[1];
		};

		struct matter_info_list
		{
			multi_data_header header;
			matter_info_1 list[1];
		};

		struct matter_enter_world
		{
			single_data_header header;
			matter_info_1 data;
		};

		struct npc_enter_world
		{
			single_data_header header;
			npc_info info;
		};

		struct player_info_00
		{
			single_data_header header;
			int pid;
			INFO::player_info_00 info;
		};

		struct self_info_00
		{
			single_data_header header;
			INFO::self_info_00 info;
			
		};

		struct npc_info_00
		{
			single_data_header header;
			int nid;
			INFO::npc_info_00 info;
		};
		
		struct object_move
		{
			single_data_header header;
			move_info data;
		};
		struct player_enter_world
		{
			single_data_header header;
			player_info_1	info;
		};
		struct player_leave_world
		{
			single_data_header header;
			int	   cid;
		};
		struct player_select_target
		{
			single_data_header header;
			int	id;
		};

		struct npc_dead
		{
			single_data_header header;
			int	   nid;
			int 	   attacker;
		};
		struct object_disappear
		{
			single_data_header header;
			int	   nid;
		};
		struct object_start_attack
		{
			single_data_header header;
			int	oid;
			int	tid;	//target id
			unsigned char	attack_speed;
		};

		struct self_start_attack
		{
			single_data_header header;
			int	tid;	//target id
			unsigned short ammo_remain;
			unsigned char attack_speed;
		};
		struct self_stop_attack
		{	
			single_data_header header;
			int	flag;
		};

		struct self_attack_result 
		{
			single_data_header header;
			int 	target_id;
			int	damage;			//如果是0表示没有击中
			int attack_flag;	//标记该攻击是否有攻击优化符和防御优化符和重击发生
			unsigned char speed;
		};

		struct self_skill_attack_result 
		{
			single_data_header header;
			int 	target_id;
			int 	skill_id;
			int	damage;			//如果是0表示没有击中
			int attack_flag;	//标记该攻击是否有攻击优化符和防御优化符和重击发生
			unsigned char speed;
			unsigned char section;	// 技能段数
		};
		
		struct hurt_result //hurt_result
		{
			single_data_header header;
			int 	target_id;
			int	damage;
		};

		struct object_attack_result
		{
			single_data_header header;
			int attacker_id;
			int target_id;
			int damage;
			int attack_flag;	//标记该攻击是否有攻击优化符和防御优化符和重击发生
			char speed;			//攻击速度
			
		};

		struct object_skill_attack_result
		{
			single_data_header header;
			int attacker_id;
			int target_id;
			int skill_id;
			int damage;
			int attack_flag;	//标记该攻击是否有攻击优化符和防御优化符和重击发生
			char speed;			//攻击速度
			unsigned char section;	// 技能段数
		};

		struct error_msg
		{
			single_data_header header;
			int  msg;
		};

		struct be_attacked
		{
			single_data_header header;
			int 	attacker_id;
			int 	damage;
			unsigned char eq_index; //高位代表这次攻击是不是应该变橙色
			int attack_flag;	//标记该攻击是否有攻击优化符和防御优化符和重击发生
			char speed;			//攻击速度
		};

		struct be_skill_attacked
		{
			single_data_header header;
			int 	attacker_id;
			int 	skill_id;
			int 	damage;
			unsigned char eq_index; //高位代表这次攻击是不是应该变橙色
			int attack_flag;	//标记该攻击是否有攻击优化符和防御优化符和重击发生
			char speed;			//攻击速度
			unsigned char section;	// 技能段数
		};


		struct be_hurt
		{
			single_data_header header;
			int 	attacker_id;
			int 	damage;
			unsigned char invader;
		};
		
		struct player_dead
		{
			single_data_header header;
			int  killer;
			int  player;
		};
		struct be_killed
		{
			single_data_header header;
			int  killer;
			A3DVECTOR pos;
		};

		struct player_revival
		{
			single_data_header header;
			int id;
			short type;	//复活的类型 0 回城复活，1 开始复活 2：复活完全完成
			A3DVECTOR pos;
		};
		struct player_pickup_money
		{
			single_data_header header;
			int amount;
			unsigned char is_silver;
		};
		struct player_pickup_item
		{
			single_data_header header;
			int type;
			int expire_date;
			unsigned int amount;
			unsigned int slot_amount;
			unsigned char where;		//在哪个包裹栏，0 标准，2 任务，1 装备
			unsigned char index;		//最后部分放在哪个位置
		};

		struct player_purchase_item
		{
			single_data_header header;
			unsigned int cost;
			unsigned int yinpiao;			//仅在顾客购买时有效
			unsigned char type;		//表示顾客买入还是卖出
			unsigned short item_count;
			struct
			{
				int item_id;
				int expire_date;
				unsigned int count;
				unsigned short inv_index;
				unsigned char  stall_index;
			} item_list[];
		};
		
		struct OOS_list
		{
			single_data_header header;
			unsigned int count;
			int id_list[1];
		};
		struct object_stop_move
		{
			single_data_header header;
			int id;
			A3DVECTOR pos;
			unsigned short speed;
			unsigned char dir;
			unsigned char move_mode;
		};
		struct receive_exp
		{
			single_data_header header;
			int exp;
			int sp;
		};

		struct level_up
		{
			single_data_header header;
			int id;
		};

		struct unselect 
		{
			single_data_header header;
		};
		
		struct self_item_info
		{
			single_data_header header;
			unsigned char where;
			unsigned char index;
			int type;
			int expire_date;
			//int item_state;
			int proc_type;
			unsigned int count;
			//unsigned int pile_limit;
			//int equip_mask;
			//int guid1;
			//int guid2;
			//int price;
			unsigned short crc;
			int pickup_date;
			int pickup_expire;
			unsigned short content_length;
			char content[];
		};
		struct self_item_empty_info
		{
			single_data_header header;
			unsigned char where;
			unsigned char index;
		};
		struct self_inventory_data
		{
			single_data_header header;
			unsigned char where;
			unsigned char inv_size;
			unsigned int content_length;
			char content[];
		};

		struct self_inventory_detail_data
		{
			single_data_header header;
			unsigned char where;
			unsigned char inv_size;
			unsigned int content_length;
			char content[];
		};

		struct  exchange_inventory_item
		{
			single_data_header header;
			unsigned char index1;
			unsigned char index2;
		};
		
		struct move_inventory_item
		{
			single_data_header header;
			unsigned char src;
			unsigned char dest;
			unsigned int count;
		};

		struct player_drop_item
		{
			single_data_header header;
			unsigned char where;
			unsigned char index;
			unsigned int count;
			int type;
			unsigned char drop_type;
		};
		struct exchange_equipment_item
		{
			single_data_header header;
			unsigned char index1;
			unsigned char index2;
		};

		struct equip_item
		{
			single_data_header header;
			unsigned char index_inv;
			unsigned char index_equip;
			unsigned int count_inv;
			unsigned int count_equip;
		};

		struct move_equipment_item
		{
			single_data_header header;
			unsigned char index_inv;
			unsigned char index_equip;
			unsigned int amount;
		};

		struct self_get_property
		{
			single_data_header header;
			unsigned int status_point;
			int 	attack_degree;
			int	defend_degree;
			int crit_rate;
			int crit_damage_bonus;
			int invisible_degree;
			int anti_invisible_degree;
			int penetration;
			int resilience;
			int vigour;
			int anti_defense_degree;
			int anti_resistance_degree;
		//	extend_prop prop;		//不想引用头文件，所以注释掉了
		};

		struct set_status_point
		{
			single_data_header header;
			unsigned int vit;
			unsigned int eng;
			unsigned int str;
			unsigned int agi;
			unsigned int remain_point;
		};

		struct player_extprop_base
		{
			single_data_header header;
			int id;
			int vitality;		//命
			int energy;		//神
			int strength;		//力
			int agility;		//敏
			int max_hp;		//最大hp
			int max_mp;		//最大mp
			int hp_gen;		//hp恢复速度
			int mp_gen;		//mp恢复速度 
		};

		struct player_extprop_move
		{
			single_data_header header;
			int id;
			float walk_speed;	//行走速度 单位  m/s
			float run_speed;	//奔跑速度 单位  m/s
			float swim_speed;	//游泳速度 单位  m/s
			float flight_speed;	//飞行速度 单位  m/s
		};

		struct player_extprop_attack
		{
			single_data_header header;
			int id;
			int attack;		//攻击率 attack rate
			int damage_low;		//最低damage
			int damage_high;	//最大物理damage
			int attack_speed;	//攻击时间间隔 以tick为单位
			float attack_range;	//攻击范围
			struct 			//物理攻击附加魔法伤害
			{
				int damage_low;
				int damage_high;
			} addon_damage[5];		
			int damage_magic_low;		//魔法最低攻击力
			int damage_magic_high;		//魔法最高攻击力
		};

		struct player_extprop_defense
		{
			single_data_header header;
			int id;
			int resistance[5];	//魔法抗性
			int defense;		//防御力
			int armor;		//闪躲率（装甲等级）
		};
		
		struct team_leader_invite
		{
			single_data_header header;
			int leader;
			int seq;
			short pickup_flag;
		};

		struct team_reject_invite
		{
			single_data_header header;
			int member;
		};

		struct team_join_team
		{
			single_data_header header;
			int leader;
			short pickup_flag;
		};

		struct  team_member_leave
		{
			single_data_header header;
			int leader;
			int member;
			short type;
		};
		
		//表明自己离开了队伍
		struct team_leave_party
		{
			single_data_header header;
			int leader;
			short type;
		};

		struct team_new_member
		{
			single_data_header header;
			int member;
		};

		struct team_leader_cancel_party
		{
			single_data_header header;
			int leader;
		};

		struct team_member_data
		{
			single_data_header header;
			unsigned char member_count;
			unsigned char data_count;
			int leader;
			struct 
			{
				int id;
				short level;
				unsigned char combat_state;
				unsigned char sec_level;
				unsigned char reincarnation_times;
				char wallow_level;
				int hp;
				int mp;
				int max_hp;
				int max_mp;
				int force_id;
				int profit_level;
			} data[1];
		};

		struct teammate_pos
		{
			single_data_header header;
			int id;
			A3DVECTOR pos;
			int tag;
			char same_plane;
		};

		struct send_equipment_info
		{
			single_data_header header;
			unsigned short crc;
			int id;		//who
			uint64_t mask;
			struct 
			{
				unsigned int item;
				unsigned short mask;
			}data[];	//0 ~ 16
		};
		
		struct equipment_info_changed
		{
			single_data_header header;
			unsigned short crc;
			int id;		//who
			uint64_t mask_add;
			uint64_t mask_del;
			struct 
			{
				unsigned int item;
				unsigned short mask;
			}data_add[];	//0 ~ 16
		};

		struct equipment_damaged
		{
			single_data_header header;
			unsigned char index;
			char reason;	// 0:无耐久了 1:死亡后引起的装备损毁
		};

		struct team_member_pickup
		{
			single_data_header header;
			int id;
			int type;
			int count;
		};

		struct npc_greeting
		{
			single_data_header header;
			int id;
		};

		struct npc_service_content
		{
			single_data_header header;
			int id;
			int type;	//服务的类型
			unsigned int length;
			char data[];
		};

		struct item_to_money
		{
			single_data_header header;
			unsigned short index;		//在包裹栏里的索引号码
			int type;			//物品的类型
			unsigned int count;
			unsigned int money;
			unsigned int silver_money;
			unsigned int guild_money;
		};

		struct repair_all
		{
			single_data_header header;
			unsigned int cost;
		};
		
		struct repair
		{
			single_data_header header;
			unsigned char where;
			unsigned char index;
			unsigned int cost;
		};

		struct renew
		{
			single_data_header header;
		};

		struct spend_money
		{
			single_data_header header;
			unsigned int cost;
		};

		struct player_pickup_money_in_trade
		{
			single_data_header header;
			int amount;
		};
		struct player_pickup_item_in_trade
		{
			single_data_header header;
			int type;
			unsigned int amount;
		};

		struct player_pickup_money_after_trade
		{
			single_data_header header;
			unsigned int amount;
		};
		struct player_pickup_item_after_trade
		{
			single_data_header header;
			int type;
			int expire_date;
			unsigned int amount;
			unsigned int slot_amount;
			unsigned short index;
		};
		struct get_own_money
		{	
			single_data_header header;
			unsigned int amount;
			unsigned int capacity;
			unsigned int silver_amount;
			unsigned int guild_amount;
		};
		struct object_attack_once
		{
			single_data_header header;
			unsigned char arrow_dec;
		};

		struct object_cast_skill
		{
			single_data_header header;
			int caster;
			int target;
			int skill;
			unsigned short time;
			unsigned char level;
		};

		struct skill_interrupted
		{
			single_data_header header;
			int caster;
		};

		struct self_skill_interrupted
		{
			single_data_header header;
			unsigned char reason;
		};

		struct skill_perform
		{
			single_data_header header;
		};

		struct object_be_attacked
		{
			single_data_header header;
			int id;
		};
		
		struct skill_data
		{
			single_data_header header;
			char content[];
		};

		struct player_use_item
		{
			single_data_header header;
			unsigned char where;
			unsigned char index;
			int item_id;
			unsigned short use_count;
		};

		struct embed_item
		{
			single_data_header header;
			unsigned char chip_idx;
			unsigned char equip_idx;
		};

		struct clear_embedded_chip
		{
			single_data_header header;
			unsigned short equip_idx;
			unsigned int  cost;
		};

		struct cost_skill_point
		{
			single_data_header header;
			int skill_point;
		};

		struct learn_skill
		{
			single_data_header header;
			int skill_id;
			int skill_level;
		};

		struct object_takeoff
		{
			single_data_header header;
			int object_id;
		};

		struct object_landing
		{
			single_data_header header;
			int object_id;
		};

		struct flysword_time_capacity
		{
			single_data_header header;
			unsigned char where;
			unsigned char index;
			int cur_time;
		};

		struct player_obtain_item
		{
			single_data_header header;
			int type;
			unsigned int amount;
			unsigned int slot_amount;
			unsigned char where;		//在哪个包裹栏，0 标准，2 任务，1 装备
			unsigned char index;		//最后部分放在哪个位置
		};

		struct produce_start
		{
			single_data_header header;
			unsigned short use_time;
			unsigned short count;
			int type;
		};

		struct produce_once
		{
			single_data_header header;
			int type;
			unsigned int amount;
			unsigned int slot_amount;
			unsigned char where;		//在哪个包裹栏，0 标准，2 任务，1 装备
			unsigned char index;		//最后部分放在哪个位置
		};
		
		struct produce_end
		{
			single_data_header header;
		};

		struct decompose_start
		{
			single_data_header header;
			unsigned short use_time;
			int type;
		};

		struct decompose_end
		{
			single_data_header header;
		};

		struct task_data
		{
			single_data_header header;
			unsigned int active_list_size;
			char active_list[1];
			unsigned int finished_list_size;
			char finished_list[1];
			unsigned int finished_time_size;
			char finished_time[1];
			unsigned int finished_count_size;
			char finished_count[1];
			unsigned int storage_task_size;
			char storage_task[1];
		};

		struct task_var_data
		{
			single_data_header header;
			unsigned int size;
			char data[1];
		};

		struct object_start_use
		{
			single_data_header header;
			int user;
			int item;
			unsigned short time;
		};
		
		struct object_cancel_use
		{
			single_data_header header;
			int user;
		};

		struct object_use_item
		{
			single_data_header header;
			int user;
			int item;
		};
		
		struct object_start_use_with_target
		{
			single_data_header header;
			int user;
			int target;
			int item;
			unsigned short time;
		};

		struct object_sit_down
		{
			single_data_header header;
			int id;
		//		A3DVECTOR pos; $$$$$$$$$$$$$
		};

		struct object_stand_up
		{
			single_data_header header;
			int id;
		};

		struct object_do_emote
		{
			single_data_header header;
			int id;
			unsigned short emotion;
		};

		struct server_timestamp
		{
			single_data_header header;
			int timestamp;
			int timezone;
			int lua_version;
		};

		struct notify_root
		{
			single_data_header header;
			int id;
			A3DVECTOR pos;
		};

		struct self_notify_root
		{
			single_data_header header;
			A3DVECTOR pos;
			unsigned char type;
		};

		struct dispel_root
		{
			single_data_header header;
			unsigned char type;
		};

		struct invader_rise
		{
			single_data_header header;
			int id;
		};

		struct pariah_rise
		{
			single_data_header header;
			int id;
			char pariah_state;
		};

		struct invader_fade
		{
			single_data_header header;
			int id;
		};

		struct self_stop_skill
		{
			single_data_header header;
		};

		struct update_visible_state
		{
			single_data_header header;
			int oid;
			unsigned int newstate;
			unsigned int newstate2;
			unsigned int newstate3;
			unsigned int newstate4;
			unsigned int newstate5;
			unsigned int newstate6;
			unsigned int newstate7;
			unsigned int newstate8;
			unsigned int newstate9;
		};

		struct x_timer
		{
			unsigned int time;
			int unc;
		};

		struct object_state_notify
		{
			single_data_header header;
			int oid;
			unsigned short scount;
			//unsigned short state[];
			unsigned short pcount;
			//int param[];
			unsigned short x_tcount;
			x_timer x_timers[];
		};

		struct player_gather_start
		{
			single_data_header header;
			int pid;		//player id
			int mid;		//mine id
			unsigned char use_time; //use time in sec;
		};

		struct player_gather_stop
		{
			single_data_header header;
			int pid;		//player id
		};

		struct trashbox_passwd_changed
		{
			single_data_header header;
			unsigned char has_passwd;
		};

		struct trashbox_passwd_state
		{
			single_data_header header;
			unsigned char has_passwd;
		};
		
		struct trashbox_open
		{
			single_data_header header;
			char is_usertrashbox;		//1—帐号仓库  0—角色仓
			unsigned short trashbox_size;
			unsigned short trashbox2_size;
			unsigned short trashbox3_size;
		};

		struct trashbox_close
		{
			single_data_header header;
			char is_usertrashbox;		//1—帐号仓库  0—角色仓
		};

		struct trashbox_wealth
		{
			single_data_header header;
			char is_usertrashbox;		//1—帐号仓库  0—角色仓
			unsigned int money;
		};

		struct exchange_trashbox_item 
		{
			single_data_header header;
			char where;
			unsigned char idx1;
			unsigned char idx2;
		};
		struct move_trashbox_item
		{
			single_data_header header;
			char where;
			unsigned char src;
			unsigned char dest;
			unsigned int amount;
		};
		
		struct exchange_trashbox_inventory 
		{
			single_data_header header;
			char where;
			unsigned char idx_tra;
			unsigned char idx_inv;
		};
		
		struct trash_item_to_inventory	 
		{
			single_data_header header;
			char where;
			unsigned char src;
			unsigned char dest;
			unsigned int amount;
		};
		
		struct inventory_item_to_trash  
		{
			single_data_header header;
			char where;
			unsigned char src;
			unsigned char dest;
			unsigned int amount;
		};
		
		struct exchange_trash_money
		{
			single_data_header header;
			char is_usertrashbox;		//1—帐号仓库  0—角色仓
			int inv_delta;
			int tra_delta;
		};

		struct enchant_result
		{
			single_data_header header;
			int 	caster;
			int 	target;
			int 	skill;
			char 	level;
			char	orange_name;
			int 	at_state;
			unsigned char section;	// 技能段数
		};
		
		struct object_do_action
		{
			single_data_header header;
			int id;
			unsigned char emotion;
		};

		struct player_set_adv_data
		{
			single_data_header header;
			int id;
			int data1;
			int data2;
			
		};

		struct player_clr_adv_data 
		{
			single_data_header header;
			int id;
		};

		struct player_in_team
		{
			single_data_header header;
			int id;
			unsigned char state;	// 0 no team 1, leader, 2 member
		};

		struct team_apply_request
		{
			single_data_header header;
			int id;			//who
		};
		
		struct object_do_emote_restore
		{
			single_data_header header;
			int id;
			unsigned short emotion;
		};

		struct concurrent_emote_request
		{
			single_data_header header;
			int id;
			unsigned short emotion;
		};

		struct do_concurrent_emote 
		{
			single_data_header header;
			int id1;
			int id2;
			unsigned short emotion;
		};

		struct matter_pickup
		{
			single_data_header header;
			int matter_id;
			int who;
		};

		struct mafia_info_notify
		{
			single_data_header header;
			int pid;
			int mafia_id;
			char mafia_rank;
			int64_t mnfaction_id;
		};

		struct mafia_trade_start
		{
			single_data_header header;
		};

		struct mafia_trade_end
		{
			single_data_header header;
		};
		
		struct task_deliver_item
		{
			single_data_header header;
			int type;
			int expire_date;
			unsigned int amount;
			unsigned int slot_amount;
			unsigned char where;		//在哪个包裹栏，0 标准，2 任务，1 装备
			unsigned char index;		//最后部分放在哪个位置
		};

		struct task_deliver_reputaion
		{
			single_data_header header;
			int delta;
			int cur_reputaion;
		};

		struct task_deliver_exp
		{
			single_data_header header;
			int exp;
			int sp;
		};

		struct task_deliver_money
		{
			single_data_header header;
			unsigned int amount;
			unsigned int cur_money;
		};

		struct task_deliver_level2
		{
			single_data_header header;
			int level2;
		};

		struct player_reputation
		{
			single_data_header header;
			int reputation;
		};

		struct identify_result
		{
			single_data_header header;
			char index;
			char result;	//0 	
		};

		struct player_change_shape
		{
			single_data_header header;
			int pid;
			char shape;
		};

		struct object_enter_sanctuary
		{
			single_data_header header;
			int id;		//self id or pet id
		};

		struct object_leave_sanctuary
		{
			single_data_header header;
			int id;		//self id or pet id
		};

		struct player_open_market
		{
			single_data_header header;
			int pid;
			unsigned char market_crc;
			unsigned char name_len;
			char name[];		//最大62
		};

		struct self_open_market
		{
			single_data_header header;
			unsigned char count;
			unsigned char off;
			struct 
			{
				int type;		//物品类型
				unsigned short index;	//如果是0xFFFF，表示是购买
				unsigned int count;	//卖多少个
				unsigned int price;		//单价
			} item_list;
			
		};

		struct player_cancel_market
		{
			single_data_header header;
			int pid;
		};

		struct player_market_info
		{
			single_data_header header;
			int pid;
			int market_id;
			unsigned int count;
			market_goods item_list[];
		};

		struct player_market_trade_success
		{
			single_data_header header;
			int trader;
		};

		struct player_market_name
		{
			single_data_header header;
			int pid;
			unsigned char market_crc;
			unsigned char name_len;
			char name[];	//最大62字节
		};

		struct player_start_travel
		{
			single_data_header header;
			int pid;
			unsigned char vehicle;
		};

		struct self_start_travel
		{
			single_data_header header;
			float speed;
			A3DVECTOR dest;
			int line_no;
			unsigned char vehicle;
		};

		struct player_complete_travel
		{
			single_data_header header;
			int pid;
			unsigned char vehicle;
		};

		struct gm_toggle_invisible
		{
			single_data_header header;
			unsigned char is_visible;
		};

		struct gm_toggle_invincible
		{
			single_data_header header;
			unsigned char is_invincible;
		};

		struct self_trace_cur_pos
		{
			single_data_header header;
			A3DVECTOR pos;
			unsigned short seq;
		};

		struct object_cast_instant_skill
		{
			single_data_header header;
			int id;
			int target;
			int skill;
			unsigned char level;
		};

		struct activate_waypoint
		{
			single_data_header header;
			unsigned short waypoint;
		};

		struct player_waypoint_list
		{
			single_data_header header;
			unsigned int count;
			unsigned short list[];
		};
		
		struct unlock_inventory_slot
		{
			single_data_header header;
			unsigned char where;
			unsigned short index;
		};

		struct team_invite_timeout
		{
			single_data_header header;
			int who;
		};

		struct player_enable_pvp
		{
			single_data_header header;
			int who;
			char type;
		};

		struct player_disable_pvp
		{
			single_data_header header;
			int who;
			char type;
		};

		struct player_pvp_cooldown
		{
			single_data_header header;
			int cooldown_time;
			int max_cooldown_time;
		};

		struct cooldown_data
		{
			single_data_header header;
			unsigned short count;
			struct
			{
				unsigned short idx;
				int cooldown;
			}list[1];
		};

		struct skill_ability_notify
		{
			single_data_header header;
			int skill_id;
			int skill_ability;
		};

		struct personal_market_available
		{
			single_data_header header;
		};

		struct breath_data
		{
			single_data_header header;
			int breath;
			int breath_capacity;
		};

		struct player_stop_dive
		{
			single_data_header header;
		};

		struct trade_away_item
		{
			single_data_header header;
			short inv_index;
			int item_type;
			unsigned int item_count;
			int buyer;
		};

		struct player_enable_fashion_mode
		{
			single_data_header header;
			int who;
			unsigned char is_enable;
			unsigned char new_model;
		};

		struct enable_free_pvp_mode
		{
			single_data_header header;
			unsigned char is_enable;
		};

		struct object_is_invalid
		{
			single_data_header header;
			int id;
		};

		struct player_enable_effect
		{
			single_data_header header;
			short effect;
			int id;
		};

		struct player_disable_effect
		{
			single_data_header header;
			short effect;
			int id;
		};
		
		struct enable_resurrect_state
		{
			single_data_header header;
			float exp_reduce;
		};

		struct set_cooldown
		{
			single_data_header header;
			int cooldown_index; 
			int cooldown_time;
		};

		struct change_team_leader
		{
			single_data_header header;
			int old_leader; 
			int new_leader;
		};

		struct kickout_instance
		{
			single_data_header header;
			int instance_tag; 
			char reason;
			int timeout;		//如果是-1表示取消此次踢出
		};

		struct player_cosmetic_begin
		{
			single_data_header header;
			unsigned short index;
		};

		struct player_cosmetic_end
		{
			single_data_header header;
			unsigned short index;
		};

		struct cosmetic_success
		{
			single_data_header header;
			unsigned short crc;
			int id;
		};

		struct object_cast_pos_skill
		{
			single_data_header header;
			int id;
			A3DVECTOR pos;
			int target;
			int skill;
			unsigned short time;
			unsigned char level;
		};

		struct change_move_seq
		{
			single_data_header header;
			unsigned short seq;
		};

		struct server_config_data
		{
			single_data_header header;
			int world_tag;
			int region_time;
			int precinct_time;
			int mall_timestamp;
			int mall2_timestamp;
			int mall3_timestamp;
		};

		struct player_rush_mode
		{
			single_data_header header;
			char is_active;
		};

		struct trashbox_capacity_notify
		{
			single_data_header header;
			char where;
			int capacity;
		};

		struct npc_dead_2
		{
			single_data_header header;
			int nid;
			int attacker;
		};

		struct produce_null
		{
			single_data_header header;
			int recipe_id;
		};

		struct double_exp_time
		{
			single_data_header header;
			int mode;
			int end_time;		//结束时间
		};
		
		struct available_double_exp_time
		{
			single_data_header header;
			int available_time;	//剩余时间
		};

		struct active_pvp_combat_state
		{
			single_data_header header;
			int who;
			char is_active;
		};

		struct duel_recv_request
		{
			single_data_header header;
			int player_id;
		};

		struct duel_reject_request
		{
			single_data_header header;
			int player_id;
			int reason;
		};

		struct duel_prepare
		{
			single_data_header header;
			int player_id;
			int delay;		//sec
		};
		
		struct duel_cancel
		{
			single_data_header header;
			int player_id;
		};

		struct duel_start
		{
			single_data_header header;
			int player_id;
		};
		
		struct duel_stop
		{
			single_data_header header;
			int player_id;
		};
		
		struct duel_result
		{
			single_data_header header;
			int id1;
			int id2;
			char result;	//1 id1 win 2 draw
		};

		struct player_bind_request
		{
			single_data_header header;
			int who;
		};

		struct player_bind_invite
		{
			single_data_header header;
			int who;
		};

		struct player_bind_request_reply
		{
			single_data_header header;
			int who;
			int param;
		};

		struct player_bind_invite_reply
		{
			single_data_header header;
			int who;
			int param;
		};

		struct player_bind_start
		{
			single_data_header header;
			int param;
			int mule;
			int rider;
		};

		struct player_bind_stop
		{
			single_data_header header;
			int who;
		};

		struct player_mounting
		{
			single_data_header header;
			int id;
			int mount_id;
			unsigned short mount_color;
		};

		struct player_equip_detail
		{
			single_data_header header;
			int id;
			int reserve;
			unsigned int content_length;
			char content[];
		};

		struct else_duel_start
		{
			single_data_header header;
			int player_id;
		};

		struct pariah_duration
		{
			single_data_header header;
			int time_left;
		};

		struct player_gain_pet
		{
			single_data_header header;
			int slot_index;
			char content[];	//pet_data
		};

		struct player_free_pet
		{
			single_data_header header;
			int slot_index;
			int pet_id;
		};

		struct player_summon_pet
		{
			single_data_header header;
			int slot_index;
			int pet_tid; 	//宠物的实际id
			int pet_id;	//世界内的 ID 0 代表无 id 
			int life_time;	//0永久 >0秒数
		};


		struct player_recall_pet
		{
			single_data_header header;
			int slot_index;
			int pet_id;
			char reason;
		};

		struct player_start_pet_op
		{
			single_data_header header;
			int slot_index;
			int pet_id;
			int delay;	//延迟时间，单位是50ms的tick
			int op;		//操作类型  0:放出 1:召回 2:放生
		};

		struct player_stop_pet_op
		{
			single_data_header header;
		};

		struct player_pet_recv_exp
		{
			single_data_header header;
			int slot_index;
			int pet_id;
			int exp;
		};

		struct player_pet_levelup
		{
			single_data_header header;
			int slot_index;
			int pet_id;
			int level;		//新级别
			int exp;		//当前的经验值 

		};

		struct player_pet_room
		{
			single_data_header header;
			unsigned short count;
			int slot_index;
			char pet_data[];
			/*
			//重复 count 次
			   int index;
			   char pet_data[];
			*/
		};

		struct player_pet_room_capacity
		{
			single_data_header header;
			unsigned int capacity;
		};
		
		struct player_pet_honor_point
		{
			single_data_header header;
			int index;
			int cur_honor_point;
		};

		struct player_pet_hunger_gauge
		{
			single_data_header header;
			int index;
			int cur_hunge_gauge;
		};

		struct enter_battleground
		{
			single_data_header header;
			int role_in_war;	//0 中立/或不在战场  1 攻方 2 守方
			int battle_id;
			int end_time;
		};

		struct turret_leader_notify
		{
			single_data_header header;
			int turret_id;
			int leader_id;
		};

		struct battle_result
		{
			single_data_header header;
			int result;
			
		};

		struct battle_score
		{
			single_data_header header;
			int offense_score;
			int offense_goal;
			int defence_score;
			int defence_goal;
			
		};

		struct pet_dead
		{
			single_data_header header;
			unsigned int pet_index;
		};

		struct pet_revive
		{
			single_data_header header;
			unsigned int pet_index;
			float hp_factor;
		};

		struct pet_hp_notify
		{
			single_data_header header;
			unsigned int pet_index;
			float hp_factor;
			int cur_hp;
			float mp_factor;
			int cur_mp;
		};

		struct pet_ai_state
		{
			single_data_header header;
			char stay_state;
			char aggro_state;
		};

		struct refine_result
		{
			single_data_header header;
			int result;
		};

		struct pet_set_cooldown
		{
			single_data_header header;
			int pet_index;
			int cooldown_index;
			int cooldown_msec;
		};

		struct player_cash
		{
			single_data_header header;
			int cash;
		};

		struct player_bind_success
		{
			single_data_header header;
			unsigned short inv_index;
			int item_id;
		};

		struct player_change_inventory_size
		{
			single_data_header header;
			int new_size;
		};

		struct player_pvp_mode
		{
			single_data_header header;
			unsigned char pvp_mode;
		};

		struct player_wallow_info
		{
			single_data_header header;
			unsigned char anti_wallow_active;
			unsigned char wallow_level;
			int play_time;
			int light_timestamp;
			int heavy_timestamp;
			int reason;
		};
		
		struct player_use_item_with_arg
		{
			single_data_header header;
			unsigned char where;
			unsigned char index;
			int item_id;
			unsigned short use_count;
			unsigned short arg_size;
			char arg[];
		};

		struct object_use_item_with_arg
		{
			single_data_header header;
			int user;
			int item;
			unsigned short arg_size;
			char arg[];
		};

		struct player_change_spouse
		{
			single_data_header header;
			int who;
			int spouse_id;
		};

		struct notify_safe_lock
		{       
			single_data_header header;
			unsigned char active;
			int time;
			int max_time;                
			bool passwd;
		};
		
		//lgc
		struct elf_vigor
		{
			single_data_header header;
			int vigor;
			int max_vigor;
			int vigor_gen;//元气恢复速度的100倍				
		};

		struct elf_enhance
		{
			single_data_header header;
			short str_en;
			short agi_en;
			short vit_en;
			short eng_en;
		};

		struct elf_stamina
		{
			single_data_header header;	
			int stamina;	 
		};

		struct elf_cmd_result
		{
			single_data_header header;	
			int cmd;
			int result;
			int param1;
			int param2;
		};

		struct common_data_notify
		{
			single_data_header header;	
			/*
			struct 
			{
				int key;
				int value;
			} nodes[];
			*/
		};

		struct common_data_list
		{
			single_data_header header;	
			/*
			struct 
			{
				int key;
				int value;
			} nodes[];
			*/
		};

		struct player_elf_refine_activate
		{
			single_data_header header;
			int pid;
			char status;
		};
		
		struct player_cast_elf_skill
		{
			single_data_header header;
			int id;
			int target;
			int skill;
			unsigned char level;
		};

		struct mall_item_price
		{
			single_data_header header;
			short start_index;
			short end_index;
			short count;
			struct 
			{
				short good_index;
				char good_slot;
				int good_id;
				char expire_type;
				int expire_time;
				int good_price;
				char good_status;
				int min_vip_level;
			}list[];
		};

		struct mall_item_buy_failed
		{
			single_data_header header;
			short index;
			char reason;
		};

		struct player_elf_levelup
		{
			single_data_header header;
			int player_id;
		};
		
		struct player_property
		{
			single_data_header header;
			struct _data{
				int id;
				int hp;
				int mp;
				int damage_low;			//最低damage
				int damage_high;		//最大物理damage
				int damage_magic_low;	//魔法最低攻击力
				int damage_magic_high;	//魔法最高攻击力
				int defense;			//防御力
				int resistance[5];		//魔法抗性
				int attack;				//攻击率 attack rate
				int armor;				//闪躲率（装甲等级）
				int attack_speed;		//攻击时间间隔 以tick为单位
				float run_speed;		//奔跑速度 单位  m/s
				int attack_degree;		//攻击等级
				int defend_degree;		//防御等级
				int crit_rate;			//暴击
				int damage_reduce;		//伤害减免百分比，可正负
				int prayspeed;			//吟唱速度增加百分比,可正负	
				int	crit_damage_bonus;	//额外的暴击伤害加成 
				int invisible_degree;	//隐身等级
				int anti_invisible_degree;//反隐等级
				int vigour;				//气魄值
				int anti_defense_degree;	// 破物理防
				int anti_resistance_degree;	// 破属性防
				int reserve1;
			}data;
			struct _self_data
			{
				int damage_reduce;
				int prayspeed;
			}self_data;
		};
		
		struct player_cast_rune_skill
		{
			single_data_header header;
			int caster;
			int target;
			int skill;
			unsigned short time;
			unsigned char level;
		};
		
		struct player_cast_rune_instant_skill
		{
			single_data_header header;
			int id;
			int target;
			int skill;
			unsigned char level;
		};
		
		struct equip_trashbox_item
		{
			single_data_header header;
			unsigned char where;
			unsigned char trash_idx;	
			unsigned char equip_idx;
		};

		struct security_passwd_checked
		{
			single_data_header header;	
		};

		struct object_invisible
		{
			single_data_header header;
			int id;
			int invisible_degree;
		};

		struct hp_steal
		{
			single_data_header header;
			int hp;
		};
		
		struct player_dividend
		{
			single_data_header header;
			int dividend;
		};
		
		
		struct dividend_mall_item_price
		{
			single_data_header header;
			short start_index;
			short end_index;
			short count;
			struct 
			{
				short good_index;
				char good_slot;
				int good_id;
				char expire_type;
				int expire_time;
				int good_price;
				char good_status;
				int min_vip_level;
			}list[];
		};

		struct dividend_mall_item_buy_failed
		{
			single_data_header header;
			short index;
			char reason;
		};

		struct elf_exp
		{
			single_data_header header;	
			int exp;	 
		};
		
		struct public_quest_info
		{
			single_data_header header;
			//int space_id; //162
			int task_id;	
			//int child_space_id; //162
			int child_task_id;
			int score;
			int cls_place;
			int all_place;
		};

		struct public_quest_ranks
		{
			single_data_header header;
			//int _space_id; //162
			int _task_id;		
			int player_count;
			unsigned int ranks_size[13];	//依次是武侠、法师、 ...、羽灵、总 排行榜大小
			struct{
				int roleid;
				int race;
				int score;
				int rand;
				int place;
				//162
				int reserve1;
				int reserve2;
				
			}ranks_entry[];
		};

		struct multi_exp_info
		{
			single_data_header header;
			int last_timestamp;
			float enhance_factor;
		};

		struct change_multi_exp_state
		{
			single_data_header header;
			char state;
			int enchance_time;
			int buffer_time;
			int impair_time;
			int activate_times_left;
		};

		struct world_life_time
		{
			single_data_header header;
			int life_time;	//>=0:剩余时间 -1:无限 
		};

		struct wedding_book_list
		{
			single_data_header header;
			int count;
			struct{
				int start_time;
				int end_time;
				int groom;
				int bride;
				int scene;
				char status;
				char special;
			}list[];
		};

		struct wedding_book_success
		{
			single_data_header header;
			int type;	//1 预定 2 取消预定
		};

		struct calc_network_delay
		{
			single_data_header header;
			int	timestamp;
		};

		struct player_knockback
		{
			single_data_header header;
			int id;
			A3DVECTOR pos;
			int time;		//毫秒
			int fix_pos;
		};
		
		struct player_summon_plant_pet
		{
			single_data_header header;
			int plant_tid; 	//宠物的实际id
			int plant_id;	//世界内的 ID 0 代表无 id 
			int life_time;	//0永久 >0秒数
		};
		
		struct plant_pet_disappear
		{
			single_data_header header;
			int plant_id;	//世界内的 ID 0 代表无 id 
			char reason;	//0死亡 1寿命到 2超出范围
		};
		
		struct plant_pet_hp_notify
		{
			single_data_header header;
			int plant_id;	//世界内的 ID 0 代表无 id 
			float hp_factor;
			int cur_hp;
			float mp_factor;
			int cur_mp;
		};

		struct pet_property
		{
			single_data_header header;
			int pet_index;
		//	extend_prop prop;		//不想引用头文件，所以注释掉了
		};

		struct faction_contrib_notify
		{
			single_data_header header;
			int consume_contrib;
			int exp_contrib;
			int cumulate_contrib;
		};
		
		struct faction_fortress_info
		{
			single_data_header header;
			int factionid;	
			int level;
			int exp;			
			int exp_today;
			int exp_today_time;
			int tech_point;
			int technology[5];
			int material[8];
			int building_count;
			struct building_data
			{
				int id; 
				int finish_time;
			}building[1];
			int health;
		};
		
		struct enter_factionfortress
		{
			single_data_header header;
			int role_in_war;	//0 中立/或不在战场  1 攻方 2 守方
			int factionid;
			int offense_endtime;
		};
		
		struct faction_relation_notify
		{
			single_data_header header;
			unsigned int alliance_size;
			int alliance[1];
			unsigned int hostile_size;
			int hostile[1];
		};
		
		struct player_equip_disabled
		{
			single_data_header header;
			int id;
			int64_t mask;
		};

		struct player_spec_item_list
		{
			single_data_header header;
			int roleid;
			int type;
			struct entry{
				unsigned char where;
				unsigned char index;
				unsigned int count;
			}list[];
		};

		struct object_start_play_action
		{
			single_data_header header;
			int id;
			int play_times;
			int action_last_time;
			int interval_time;
			unsigned int name_length;
			char action_name[];
		};

		struct object_stop_play_action
		{
			single_data_header header;
			int id;
		};

		struct congregate_request
		{
			single_data_header header;
			char type;
			int sponsor;
			int timeout;
		};

		struct reject_congregate
		{
			single_data_header header;
			char type;
			int id;
		};

		struct congregate_start
		{
			single_data_header header;
			char type;
			int id;
			int time;	//单位毫秒
		};

		struct cancel_congregate
		{
			single_data_header header;
			char type;
			int id;
		};
		
		struct engrave_start 
		{
			single_data_header header;
			int recipe_id;
			int use_time;
		};
		
		struct engrave_end
		{
			single_data_header header;
		};
		
		struct engrave_result
		{
			single_data_header header;
			int addon_num;
		};

		struct dps_dph_rank
		{
			single_data_header header;
			int next_refresh_sec;
			unsigned char rank_count;
			unsigned char rank_mask;
			struct _entry
			{
				int roleid;
				unsigned char level;
				int dps_or_dph;
			}entry_list[];
		};

		struct addonregen_start 
		{
			single_data_header header;
			int recipe_id;
			int use_time;
		};
		
		struct addonregen_end
		{
			single_data_header header;
		};
		
		struct addonregen_result
		{
			single_data_header header;
			int addon_num;
		};

		struct invisible_obj_list
		{
			single_data_header header;
			int id;
			unsigned int count;
			int id_list[];	
		};

		struct set_player_limit
		{
			single_data_header header;
			int index;
			char b;
		};

		struct player_teleport
		{
			single_data_header header;
			int id;
			A3DVECTOR pos;
			unsigned short use_time;
			char mode;
		};

		struct object_forbid_be_selected
		{
			single_data_header header;
			int id;
			char b;
		};

		struct player_inventory_detail
		{
			single_data_header header;
			int id;
			unsigned int money;
			unsigned char inv_size;
			unsigned int content_length;
			char content[];
		};

		struct player_force_data
		{
			single_data_header header;
			int cur_force_id;
			unsigned int count;
			struct{
				int force_id;
				int reputation;
				int contribution;
			}list[];
		};

		struct player_force_changed
		{
			single_data_header header;
			int id;
			int cur_force_id;
		};

		struct player_force_data_update
		{
			single_data_header header;
			int force_id;
			int reputation;
			int contribution;
		};
		
		struct force_global_data
		{
			single_data_header header;
			char data_ready;
			unsigned int count;
			struct{
				int force_id;
				int player_count;
				int development;
				int construction;
				int activity;
				int activity_level;
			}list[];
		};

		struct add_multiobj_effect
		{
			single_data_header header;
			int id;
			int target;
			char type;
		};
		
		struct remove_multiobj_effect
		{
			single_data_header header;
			int id;
			int target;
			char type;
		};

		struct enter_wedding_scene
		{
			single_data_header header;
			int groom;
			int bride;
		};

		struct produce4_item_info
		{
			single_data_header header;
			int stime;
			int type;
			int expire_date;
			int proc_type;
			unsigned int count;
			unsigned short crc;
			unsigned short content_length;
			char content[];
		};

		struct online_award_data 
		{
			single_data_header header;
			int total_award_time;
			unsigned int count;
			struct {
				int type;
				int time;
				int reserved;
			}list[];
		};

		struct toggle_online_award
		{
			single_data_header header;
			int type;
			char activate;
		};


		struct player_profit_time
		{
			enum
			{
				PLAYER_QUERY,	//主动请求
				PLAYER_ONLINE,	//玩家上线
				PLAYER_SWITCH_SERVER,//切换地图
				PROFIT_LEVEL_CHANGE,//收益级别变化
			};

			single_data_header header;
			char flag;		//标志发送收益时间的原因
			char profit_map;//是否是收益地图(0:否;1:收益地图;2:收益地图2)
			int profit_time;//剩余收益时间
			int profit_level;//当前收益级别
		};

		struct set_profittime_state
		{
			single_data_header header;
			char state;	//1:开始;0:停止
		};

		struct enter_nonpenalty_pvp_state
		{
			single_data_header header;
			char state;
		};

		struct self_country_notify
		{
			single_data_header header;
			int country_id;
		};

		struct player_country_changed
		{
			single_data_header header;
			int id;
			int country_id;
		};
		
		struct enter_countrybattle
		{
			single_data_header header;
			int role_in_war;	//0 中立/或不在战场  1 攻方 2 守方
			int battle_id;
			int end_time;
			int offense_country;
			int defence_country;
		};

		struct countrybattle_result
		{
			single_data_header header;
			int result;
		};

		struct countrybattle_score
		{
			single_data_header header;
			int offense_score;
			int offense_goal;
			int defence_score;
			int defence_goal;
		};

		struct countrybattle_resurrect_rest_times
		{
			single_data_header header;
			int times;
		};

		struct countrybattle_flag_carrier_notify
		{
			single_data_header header;
			int roleid;
			A3DVECTOR pos;
			char offense;
		};

		struct countrybattle_became_flag_carrier
		{
			single_data_header header;
			char is_carrier;
		};

		struct countrybattle_personal_score
		{
			single_data_header header;
			int combat_time;
			int attend_time;
			int kill_count;
			int death_count;
			int country_kill_count;
			int country_death_count;
		};

		struct countrybattle_flag_msg_notify
		{
			single_data_header header;
			int msg;
			char offense;
		};

		struct defense_rune_enabled
		{
			single_data_header header;
			char rune_type;
			char enable;
		};

		struct countrybattle_info
		{
			single_data_header header;
			int attacker_count;
			int defender_count;
		};
		
		struct cash_money_exchg_rate
		{
			single_data_header header;
			char open;
			int rate;
		};
		
		struct pet_rebuild_inherit_start
		{
			single_data_header header;
			unsigned int index;
			int use_time;
		};

		struct pet_rebuild_inherit_info
		{
			single_data_header header;
			int stime;
			int pet_id;
			unsigned int index;
			int r_attack;
			int r_defense;
			int r_hp;
			int r_atk_lvl;
			int r_def_lvl;
		};
		
		struct pet_rebuild_inherit_end
		{
			single_data_header header;
			unsigned int index;
		};

		struct pet_evolution_done
		{
			single_data_header header;
			unsigned int index;
		};

		struct pet_rebuild_nature_start
		{
			single_data_header header;
			unsigned int index;
			int use_time;
		};
		
		struct pet_rebuild_nature_info
		{
			single_data_header header;
			int stime;
			int pet_id;
			unsigned int index;
			int nature;
		};

		struct pet_rebuild_nature_end
		{
			single_data_header header;
			unsigned int index;
		};

		struct equip_addon_update_notify
		{
			single_data_header header;
			unsigned char update_type; //0 for change 1 for replace
			unsigned char equip_idx;
			unsigned char equip_socket_idx;
			int old_stone_type;
			int new_stone_type;
		};
		
		struct notify_meridian_data
		{
			single_data_header header;
			int meridian_level;
			int lifegate_times;
			int deathgate_times;
			int free_refine_times;
			int paid_refine_times;
			int continu_login_days;
			int trigrams_map[3];
		};

		struct try_refine_meridian_result
		{
			single_data_header header;
			int index;
			int result;
		};

		struct self_king_notify
		{
			single_data_header header;
			char is_king;
			int	expire_time;
		};

		struct player_king_changed
		{
			single_data_header header;
			int id;
			char is_king;
		};

		struct countrybattle_stronghold_state_notify
		{
			single_data_header header;
			int count;
			int state[];
		};
		
		struct query_touch_point 
		{ 
			single_data_header header; 
			int64_t income;   // 点数总数
			int64_t remain;   // 可用点数
			int retcode;
		};

		struct cost_touch_point 
		{  
			single_data_header header; 
			int64_t income; // 点数总数
			int64_t remain; // 可用点数
			unsigned int costval; // 本次花费数
			unsigned int index; // 商品索引
			unsigned int lots; // 批量数
			int retcode; // 0 成功
		};

		struct query_addup_money 
		{ 
			single_data_header header; 
			int64_t addupmoney;   // 点数总数
		};

		struct query_title
		{
			single_data_header header;
			int roleid;
			int titlescount;  // 称号个数
			int expirecount;
			//unsigned short titles[];   // 已获得称号vec
			char data[];    //  pair<unsigned short, int>  vec
		};

		struct change_title
		{
			single_data_header header;
			int roleid;
			unsigned short titleid;
		};

		struct notify_title_modify
		{
			single_data_header header;
			unsigned short titleid;
			int expiretime; //0 代表永久
			char flag;  	//0 rmv | 1 add
		};

		struct refresh_signin
		{
			single_data_header header;
			char type;			// 同步原因 0初始1数据不同步2签到3补签4领奖
			int lastyearstate; 	// 去年月份签到状态
			int monthcalenadr; 	// 当前月签到日历
			int updatetime;  	// 签到数据最后一次变更时间
			char latesignintimes;   // 当前月已补签次数
			char awardedtimes;      //当前月已领奖次数
			char awardedtimes2;      //当前月已领奖次数
			
			/*
			char type; // Причины синхронизации 0 Начальная 1 Данные не синхронизированы 2 Вход 3 Дополнительный знак 4 Награда
			int reserve0; // ???
			int monthcalenadr; // битмаска наград за месяцы
			int updatetime;  	// Дата последнего изменения регистрационных данных
			char reserve1; // ???
			char awardedtimes;      // Количество наград, полученных в текущем месяце
			char latesignintimes;   // Количество наград, полученных в прошедшем месяце
			
			
			single_data_header header;
			char type;			// 同步原因 0初始1数据不同步2签到3补签4领奖
			int monthcalenadr; 	// 当前月签到日历
			int curryearstate; 	// 当前年月份签到状态
			int lastyearstate; 	// 去年月份签到状态
			int updatetime;  	// 签到数据最后一次变更时间
			int localtime;   	// 当前服务器时间
            char awardedtimes;      //当前月已领奖次数
            char latesignintimes;   // 当前月已补签次数
			*/
        };

		struct parallel_world_info
		{
			single_data_header header;
			int worldtag;
			int count;
			struct{
				int key;
				float load;
			}list[];
		};

		struct unique_data_notify 
		{ 
			single_data_header header;
			int count;
			struct{
				int key;
		 		int type; //全局数据类型 |0 未初始化|1 INT| 2 DOUBLE| 3 变长
				unsigned int size;
				char data[1];
			}elems[]; 
		 };

		struct notify_giftcard_redeem
		{
			single_data_header header;
			int  retcode;
			int  cardtype;
			int  parenttype;
			char cardnumber[20];
		};

		struct player_reincarnation
		{
			single_data_header header;
			int id;
			int reincarnation_times;
		};

		struct reincarnation_tome_info
		{
			single_data_header header;
			int tome_exp;
			char tome_active;
			int count;
			struct
			{
				int level;
				int timestamp;
				int exp;
			}records[];
		};

		struct activate_reincarnation_tome
		{
			single_data_header header;
			char active;	
		};
		
		struct realm_exp
		{
			single_data_header header;
			int exp;
			int receive_exp;
			int unc1;
		};
		
		struct realm_level_up
		{
			single_data_header header;
			int roleid;
			unsigned char level;
		};

		struct enter_trickbattle
		{
			single_data_header header;
			int role_in_war;	//0 中立/或不在战场  1 攻方 2 守方
			int battle_id;
			int end_time;
		};

		struct trickbattle_personal_score
		{
			single_data_header header;
			int kill;
			int death;
			int score;
			int multi_kill;
		};

		struct trickbattle_chariot_info
		{
			single_data_header header;
			int chariot;
			int energy;
		};

		struct player_leadership
		{
			single_data_header header;
			int leadership;
			int inc_leadership;
		};

		struct generalcard_collection_data
		{
			single_data_header header;
			unsigned int size;
			char buf[];
		};

		struct add_generalcard_collection
		{
			single_data_header header;
			unsigned int colloction_idx;
		};

		struct refresh_fatering
		{
			single_data_header header;
			int gain_times;
			unsigned int count;
			struct
			{
				int level;
				int power;
			}fatering[];
		};

		struct mine_gatherd
		{
			single_data_header header;
			int mid;	//mine id
			int pid;	//player id
			int item_type;
		};

		struct player_active_combat
		{
			single_data_header header;
			int who;
			bool is_active;
		};

		struct player_query_chariots
		{
			single_data_header header;
			unsigned int attacker_count;
			unsigned int defender_count;
			struct
			{
				int type;
				int count;
			}chariots[];
		};

		struct countrybattle_live_result
		{
			single_data_header header;
			struct score_rank_entry
			{
				int roleid;
				int rank_val;
				A3DVECTOR pos;
			};
			struct death_entry
			{
				int roleid;
				int timestamp;
				A3DVECTOR pos;
			};

			unsigned int defence_rank_count;
			//score_rank_entry defence_ranks[];
			unsigned int defence_death_count;
			//death_entry defence_death_list[];
			unsigned int offense_rank_count;
			//score_rank_entry offense_ranks[];
			unsigned int offense_death_count;
			death_entry offense_death_list[];
		};

		struct random_mall_shopping_result 
		{ 
			single_data_header header; 
			int entryid;     // 
			int opt;
			int result;		 // 0 成功 -1 entryid错误 -2 状态错误 -3 带确认状态错误 -4元宝不足 -5背包不足
			int itemid;    // 待付款物品id
			int price;  	 // 待付款价格
			bool firstflag;  // 首次购买标识 
		};

		struct player_mafia_pvp_mask_notify
		{
			single_data_header header;
			int roleid;
			unsigned char mafia_pvp_mask; // 1 矿车可攻击 2 基地可攻击
		};

		struct player_world_contribution
		{
			single_data_header header;
			int contrib;
			int change;
			int total_cost;
		};

		struct random_map_order
		{
			single_data_header header;
			int world_tag;
			int row;
			int col;
			int room_src[];     // count = row * col
		};

		struct scene_service_npc_list
		{
			single_data_header header;
			unsigned int count;
			struct{
				int tid;
				int id;
			}list[];
		};

		struct npc_visible_tid_notify
		{
			single_data_header header;
			int nid;			//npc id
			int vistid;			//visible template id
		};

		struct client_screen_effect
		{
			single_data_header header;
			int type;			//effect type   0: screen 1: gfx
			int eid;			//effect id
			int state;			//state			0: close 1: open
		};
        
        struct equip_can_inherit_addons
        {
            single_data_header header;
            int equip_id;
            unsigned char inv_idx;
            unsigned char addon_num;
            int addon_id_list[];
        };

		struct combo_skill_prepare
		{
			single_data_header header;
			int skillid;
			int timestamp;
			int args[3];
		};

		struct instance_reenter_notify
		{
			single_data_header header;
			int instance_tag;    // 重入的副本id
			int time_out;		 // 重入倒计时截止(服务器)时间
		};

		struct pray_distance_change
		{
			single_data_header header;
			float pray_distance_plus;
		};


		struct astrolabe_info_notify
		{
			single_data_header header;
			unsigned char level;
			int exp;
		};

		struct astrolabe_operate_result
		{
			single_data_header header;
			int opttype;
			int retcode;
			int args[3];
		};

        struct property_score_result
        {
            single_data_header header;
            int fighting_score;
            int viability_score;
            int client_data;
        };

        struct lookup_enemy_result
        {
            single_data_header header;
            int rid;
            int worldtag;
            A3DVECTOR pos;
        };

		struct solo_challenge_award_info_notify
		{
			single_data_header header;
			int max_layer_climbed;
			int total_first_climbing_time;
			int total_score_earned;
			int cur_score;

			struct{
				int climbed_layer;
				int climbing_time;
				int total_draw_item_times;
				int drawn_item_times;
				struct 
				{
					int item_id;
					int item_count;
				}drawn_items[];
			}layer_climbed_award;
		};

		struct solo_challenge_challenging_state_notify
		{
			single_data_header header;
			int climbed_layer;
			unsigned char notify_type;
		};

		struct solo_challenge_operate_result
		{
			single_data_header header;
			int opttype;
			int retcode;
			int args[3];
		};

		struct solo_challenge_buff_info_notify
		{
			single_data_header header;
			int buff_num;
			int cur_score;
			struct
			{
				int filter_index;
				int filter_layer;
			}buff_info[];
		};
	
		struct mnfaction_player_faction_info
		{
			single_data_header header;
			int player_faction;
			int domain_id;
		};
		
		struct mnfaction_resource_point_info
		{
			single_data_header header;
			int attacker_resource_point;
			int defender_resource_point;
		};

		struct mnfaction_player_count_info
		{
			single_data_header header;
			int attend_attacker_player_count;
			int attend_defender_player_count;
		};

		struct mnfaction_result
		{
			single_data_header header;
			int result;
		};

		struct mnfaction_resource_tower_state_info
		{
			single_data_header header;
			int num;
			struct
			{
				int index;
				int own_faction;
				int state;
				int time_out;
			}state_info[];
		};

		struct mnfaction_switch_tower_state_info
		{
			single_data_header header;
			int num;
			struct
			{
				int index;
				int own_faction;
				int state;
				int time_out;
			}state_info[];
		};

		struct mnfaction_transmit_pos_state_info
		{
			single_data_header header;
			int num;
			struct
			{
				int index;
				int own_faction;
				int state;
				int time_out;
			}state_info[];
		};

		struct mnfaction_resource_point_state_info
		{
			single_data_header header; 
			int index;
			int cur_degree;
		};

		struct mnfaction_battle_ground_have_start_time
		{
			single_data_header header;
			int battle_ground_have_start_time;
		};

		struct mnfaction_faction_killed_player_num
		{
			single_data_header header;
			int attacker_killed_player_count;
			int defender_killed_player_count;
		};

		struct mnfaction_shout_at_the_client
		{
			single_data_header header;
			int type;
			int args;
		};

		struct mnfaction_player_pos_info
		{
			single_data_header header;
			int num;
			struct
			{
				int roleid;
				float player_pos[3];
			}player_pos_info[];
		};
		
		struct fix_position_transmit_add_position
		{
			single_data_header header;
			int     index;
			int     world_tag;
			float   pos[3];
			char    position_name[32];
		};

		struct fix_position_transmit_delete_position
		{
			single_data_header header;
			int index;
		};

		struct fix_position_transmit_rename
		{
			single_data_header header;
			int		index;
			char    position_name[32];
		};

		struct fix_position_energy_info
		{
			single_data_header header;
			char is_login;
			int cur_energy;
		};

		struct fix_position_all_info
		{
			single_data_header header;
			int count;
			struct
			{
				int     index;
				int     world_tag;
				float   pos[3];
				char    position_name[32];
			}position_info[];
		};
		
		struct cash_vip_mall_item_price
		{
			single_data_header header;
			short start_index;
			short end_index;
			short count;
			struct 
			{
				short good_index;
				char good_slot;
				int good_id;
				char expire_type;
				int expire_time;
				int good_price;
				char good_status;
				int min_vip_level;
			}list[];
		};

		struct cash_vip_mall_item_buy_result
		{
			single_data_header header;
			char result;
			short index;
			char reason;
		};

		struct cash_vip_info_notify
		{
			single_data_header header;
			int level;
			int score;
		};

		struct purchase_limit_info_notify
		{
			single_data_header header;
			int count;
			char reserve;
			struct
			{
				int limit_type;
				int item_id;
				int have_purchase_count;
			}item_info[];
		};

        struct cash_resurrect_info
        {
            single_data_header header;
            int cash_need;
            int cash_left;
        };
		
		struct get_sheild_energy
		{
			single_data_header header;
			short shgen;
			short shmax;
		};

		struct get_equip_data
		{
			single_data_header header;
			int roleid;
			int equip_data0[12];
			int equip_data1[12];
		};
		
		struct get_lotery_items
		{
			struct ITEM
			{
				unsigned int id;
				unsigned int count;
			};
			
			unsigned int count;
			ITEM item[];
		};
		
		struct get_lotery_info
		{
			struct ITEM
			{
				unsigned int id; // Ид итема
				unsigned int rank_item; //open 0 - серый , 1 - синий , 2 фиол , 3 голд , 4 оранж , 5 ред 
				unsigned int rank_lot; //close 0 - серый , 1 - синий
				unsigned int is_open; // 0 закрытый , 1 открытый 
			};

			unsigned int manager; //2 номер менеджера 1 - сундуки, 2 карты
			unsigned int score; //колличество очков
			unsigned int count; // количество итемов
			ITEM item[];
		};

		struct get_treasure_info
		{
			struct LOT
			{
				unsigned int id; // Ид итема
				unsigned int count; //количество
				char lot; // номер лота
			};
			
			struct BOX
			{
				unsigned int id; //ид итема
				unsigned int box; // // номер сундучка слева
				unsigned int count; //количество
				char lot; // номер лота
			};
			
			unsigned char manager; //менеджер ( 0 просто информация , 1 поиск сокровищь начался , 2 - сокровище открыто
			unsigned int score; //очки 
			unsigned int free_count; //колличество бесплатных попыток
			unsigned int lot_count; //количество закрытых сундучков
			unsigned int box_count; //колличество открытых сундучков
			LOT lot[];
			//BOX box[];
		};

	}
}

namespace C2S //client part
{
	enum MOVE_MODE
	{
		MOVE_MODE_WALK		= 0x00,
		MOVE_MODE_RUN		= 0x01,
		MOVE_MODE_STAND		= 0x02,
		MOVE_MODE_FALL		= 0x03,
		MOVE_MODE_SLIDE		= 0x04,
		MOVE_MODE_KNOCK		= 0x05,
		MOVE_MODE_FLY_FALL 	= 0x06,
		MOVE_MODE_RETURN	= 0x07,
		MOVE_MODE_JUMP		= 0x08,
		MOVE_MODE_PULL		= 0x09,
		MOVE_MODE_BLINK		= 0x0A,
		MOVE_MASK_DEAD		= 0x20,
		MOVE_MASK_SKY		= 0x40,
		MOVE_MASK_WATER		= 0x80

	};

	enum FORCE_ATTACK_MASK
	{	
		FORCE_ATTACK		= 0x01,		//强制攻击
		FORCE_ATTACK_NO_MAFIA	= 0x02,		//不攻击帮派成员
		FORCE_ATTACK_NO_WHITE	= 0x04,		//不攻击白名
		FORCE_ATTACK_NO_MAFIA_ALLIANCE	= 0x08,		//不攻击帮派同盟
		FORCE_ATTACK_NO_SAME_FORCE		= 0x10,		//不攻击同势力玩家
		FORCE_ATTACK_MASK_ALL	= 0x1F,
	};

	enum REFUSE_BLESS_MASK
	{
		REFUSE_NEUTRAL_BLESS = 0x01,		//不接受中性祝福
		REFUSE_NON_TEAMMATE_BLESS = 0x02,	//不接受非队友祝福
		REFUSE_BLESS_MASK_ALL = 0x03,
	};

	enum ASTROLABE_OPT_TYPE
	{
		ASTROLABE_OPT_SWALLOW,
		ASTROLABE_OPT_ADDON_ROLL,
		ASTROLABE_OPT_APTIT_INC,
		ASTROLABE_OPT_SLOT_ROLL,
	};

	enum SOLO_CHALLENGE_OPT_TYPE
	{
		SOLO_CHALLENGE_OPT_SELECT_STAGE,
		SOLO_CHALLENGE_OPT_SELECT_AWARD,
		SOLO_CHALLENGE_OPT_SCORE_COST,
		SOLO_CHALLENGE_OPT_CLEAR_FILTER,
		SOLO_CHALLENGE_OPT_DELIVERSCORE,
		SOLO_CHALLENGE_OPT_LEAVE_THE_ROOM,
	};

	enum FIX_POSITION_TRANSMIT_OPT_TYPE
	{
		FIX_POSITION_TRANSMIT_OPT_ADD_POSITION,
		FIX_POSITION_TRANSMIT_OPT_DELETE_POSITION,
		FIX_POSITION_TRANSMIT_OPT_TRANSMIT,
		FIX_POSITION_TRANSMIT_OPT_RENAME,
	};

	namespace INFO
	{
		struct move_info
		{
			A3DVECTOR cur_pos;
			A3DVECTOR next_pos;
			unsigned short use_time;	//使用的时间 单位是ms
							//使用的时间对于逻辑服务器来说，只是一个参考值
							//同时用于检测用户的指令是否正确，无论如何，
							//用户的移动都会在固定的0.5秒钟以后进行
			unsigned short speed;
			unsigned char  move_mode;		//walk run swim fly .... walk_back run_back
		};

		struct astrolabe_opt_swallow
		{
			int type;
			int inv_index;
			int itemid;
		};
		
		struct astrolabe_opt_addon_roll
		{
			int times;
			int addon_limit;
			int inv_index;
			int itemid;
		};

		struct astrolabe_opt_aptit_inc
		{
			int inv_index;
			int itemid;
		};

		struct astrolabe_opt_slot_roll
		{
			int inv_index;
			int itemid;
		};
		
		struct solo_challenge_opt_select_award
		{
			int max_stage_level;
		};

		struct solo_challenge_opt_score_cost
		{
			int filter_index;
		};

		struct fix_position_transmit_opt_add_position
		{
			float pos[3];
			char   position_name[32];
		};
		
		struct fix_position_transmit_opt_delete_position
		{
			int index;
		};

		struct fix_position_transmit_opt_transmit
		{
			int index;
		};

		struct fix_position_transmit_opt_rename
		{
			int    index;
			char   position_name[32];
		};
	}

	enum
	{
		PLAYER_MOVE,
		LOGOUT,
		SELECT_TARGET,
		NORMAL_ATTACK,
		RESURRECT_IN_TOWN,	//城镇复生
//5		
		RESURRECT_BY_ITEM,	//物品复生
		PICKUP,			//检起物品或者金钱
		STOP_MOVE,
		UNSELECT,		//中止当前选定的目标
		GET_ITEM_INFO,		//取得物品特定位置的信息

//10
		GET_INVENTORY,		//取得某个位置上的所有物品列表
		GET_INVENTORY_DETAIL,	//取得某个位置上的所有物品列表，包含详细的物品数据
		EXCHANGE_INVENTORY_ITEM,
		MOVE_INVENTORY_ITEM,
		DROP_INVENTORY_ITEM,

//15		
		DROP_EQUIPMENT_ITEM,
		EXCHANGE_EQUIPMENT_ITEM,
		EQUIP_ITEM,		//装备物品，将物品栏上和装备栏上的两个位置进行调换
		MOVE_ITEM_TO_EQUIPMENT,
		GOTO,

//20		
		DROP_MONEY,		//扔出钱到地上
		SELF_GET_PROPERTY,
		SET_STATUS_POINT,	//设置属性点数
		GET_EXTPROP_BASE,
		GET_EXTPROP_MOVE,

//25
		GET_EXTPROP_ATTACK,
		GET_EXTPROP_DEFENSE,
		TEAM_INVITE,
		TEAM_AGREE_INVITE,
		TEAM_REJECT_INVITE,
//30
		TEAM_LEAVE_PARTY,
		TEAM_KICK_MEMBER,
		TEAM_GET_TEAMMATE_POS,
		GET_OTHERS_EQUIPMENT,
		CHANGE_PICKUP_FLAG,

//35		
		SERVICE_HELLO,
		SERVICE_GET_CONTENT,
		SERVICE_SERVE,
		GET_OWN_WEALTH,
		GET_ALL_DATA,
//40		
		USE_ITEM,
		CAST_SKILL,
		CANCEL_ACTION,
		RECHARGE_EQUIPPED_FLYSWORD,
		RECHARGE_FLYSWORD,
//45		
		USE_ITEM_WITH_TARGET,
		SIT_DOWN,
		STAND_UP,
		EMOTE_ACTION,
		TASK_NOTIFY,
//50
		ASSIST_SELECT,
		CONTINUE_ACTION,
		STOP_FALL,	//终止跌落
		GET_ITEM_INFO_LIST,
		GATHER_MATERIAL,
//55		
		GET_TRASHBOX_INFO,
		EXCHANGE_TRASHBOX_ITEM,
		MOVE_TRASHBOX_ITEM,
		EXHCANGE_TRASHBOX_INVENTORY,
		MOVE_TRASHBOX_ITEM_TO_INVENTORY,
//60		
		MOVE_INVENTORY_ITEM_TO_TRASHBOX,
		EXCHANGE_TRASHBOX_MONEY,
		TRICKS_ACTION,
		SET_ADV_DATA,
		CLR_ADV_DATA,
//65		
		TEAM_LFG_REQUEST,
		TEAM_LFG_REPLY,
		QUERY_PLAYER_INFO_1,
		QUERY_NPC_INFO_1,
		SESSION_EMOTE_ACTION,
//70 	
		CONCURRECT_EMOTE_REQUEST,
		CONCURRECT_EMOTE_REPLY,
		TEAM_CHANGE_LEADER,
		DEAD_MOVE,
		DEAD_STOP_MOVE,

//75
		ENTER_SANCTUARY,
		OPEN_PERSONAL_MARKET,
		CANCEL_PERSONAL_MARKET,
		QUERY_PERSONAL_MARKET_NAME,
		COMPLETE_TRAVEL,

//80
		CAST_INSTANT_SKILL,
		DESTROY_ITEM,
		ENABLE_PVP_STATE,
		DISABLE_PVP_STATE,
		TEST_PERSONAL_MARKET,

//85
		SWITCH_FASHION_MODE,
		REGION_TRANSPORT,
		RESURRECT_AT_ONCE,
		NOTIFY_POS_TO_MEMBER,
		CAST_POS_SKILL,

//90	
		ACTIVE_RUSH_MODE,
		QUERY_DOUBLE_EXP_INFO,
		DUEL_REQUEST,
		DUEL_REPLY,
		BIND_PLAYER_REQUEST,

//95
		BIND_PLAYER_INVITE,
		BIND_PLAYER_REQUEST_REPLY,
		BIND_PLAYER_INVITE_REPLY,
		BIND_PLAYER_CANCEL,
		QUERY_OTHER_EQUIP_DETAIL,

//100
		SUMMON_PET,
		RECALL_PET,
		BANISH_PET,
		PET_CTRL_CMD,
		DEBUG_DELIVERY_CMD,
	
//105
		DEBUG_GS_CMD,
		MALL_SHOPPING,
		GET_WALLOW_INFO,
		TEAM_DISMISS_PARTY,
		USE_ITEM_WITH_ARG,

//110		
		QUERY_CASH_INFO,
		ELF_ADD_ATTRIBUTE,//lgc
		ELF_ADD_GENIUS,
		ELF_PLAYER_INSERT_EXP,
		ELF_EQUIP_ITEM,

//115
		ELF_CHANGE_SECURE_STATUS,
		CAST_ELF_SKILL,
		RECHARGE_EQUIPPED_ELF,
		GET_MALL_ITEM_PRICE,
		EQUIP_TRASHBOX_FASHION_ITEM,	//装备时装，将时装仓库中的时装与身上的交换
		
//120
		CHECK_SECURITY_PASSWD,		//验证安全密码(同仓库密码)，当使用受保护的功能时需要输入
		NOTIFY_FORCE_ATTACK,
		DIVIDEND_MALL_SHOPPING,
		GET_DIVIDEND_MALL_ITEM_PRICE,
		CHOOSE_MULTI_EXP,
	
//125
		TOGGLE_MULTI_EXP,
		MULTI_EXCHANGE_ITEM,
		SYSAUCTION_OP,
		CALC_NETWORK_DELAY,
		GET_FACTION_FORTRESS_INFO,

//130
		CONGREGATE_REPLY,
		GET_FORCE_GLOBAL_DATA,
		PRODUCE4_CHOOSE,	// 新继承生产，生产结束之后玩家选择新物品还是旧物品
		RECHARGE_ONLINE_AWARD,
		TOGGLE_ONLINE_AWARD,
		
//135
		QUERY_PROFIT_TIME,	//客户端请求收益时间数据
		ENTER_PK_PROTECTED,	// 进入新手保护区
		COUNTRYBATTLE_GET_PERSONAL_SCORE,
		GET_SERVER_TIMESTAMP,
		COUNTRYBATTLE_LEAVE,

//140	
		GET_CASH_MONEY_EXCHG_RATE,
		EVOLUTION_PET,
		ADD_PET_EXP,
		REBUILD_PET_NATURE,
		REBUILD_PET_INHERIT_RATIO,

//145
		PET_REBUILDINHERIT_CHOOSE,
		PET_REBUILDNATURE_CHOOSE,
		EXCHANGE_WANMEI_YINPIAO,
		PLAYER_GIVE_PRESENT,
		PLAYER_ASK_FOR_PRESENT,

//150
		TRY_REFINE_MERIDIAN,
		COUNTRYBATTLE_GET_STRONGHOLD_STATE,
		QUERY_TOUCH_POINT,
		COST_TOUCH_POINT,
		QUERY_TITLE,

//155
		CHANGE_CURR_TITLE,
		DAILY_SIGNIN,
		LATE_SIGNIN,
		APPLY_SIGNIN_AWARD,
		REFRESH_SIGNIN,

//160
		SWITCH_IN_PARALLEL_WORLD,
		QUERY_PARALLEL_WORLD,
		GET_REINCARNATION_TOME,
		REWRITE_REINCARNATION_TOME,
		ACTIVATE_REINCARNATION_TOME,

//165
		QUERY_UNIQUE_DATA,
		AUTO_TEAM_SET_GOAL,
		AUTO_TEAM_JUMP_TO_GOAL,
		TRICKBATTLE_LEAVE,
		TRICKBATTLE_UPGRADE_CHARIOT,

//170
		SWALLOW_GENERALCARD,
		EQUIP_TRASHBOX_ITEM,
		QUERY_TRICKBATTLE_CHARIOTS,
		COUNTRYBATTLE_LIVE_SHOW,
		SEND_MASS_MAIL,
//175
		RANDOM_MALL_SHOPPING,
		QUERY_MAFIA_PVP_INFO,
        QUERY_CAN_INHERIT_ADDONS,
        ACTIVATE_REGION_WAYPOINTS,
	 	INSTANCE_REENTER_REQUEST,
//180
		ASTROLABE_OPERATE_REQUEST,
        SOLO_CHALLENGE_OPERATE_REQUEST,
        PROPERTY_SCORE_REQUEST,
		MNFACTION_GET_DOMAIN_DATA,
		PICKUP_ALL,
//185
		FIX_POSITION_TRANSMIT_OPERATE_REQUEST,
		REMOTE_REPAIR,
		GET_CASH_VIP_MALL_ITEM_PRICE,
		CASH_VIP_MALL_SHOPPING,
        UPDATE_ENEMYLIST,
//190
        LOOKUP_ENEMY,
        RESURRECT_BY_CASH,
		
		LOTTERY_MANAGER = 197,
		CAST_SHIELD_SKILL = 227,
		CHANGE_GOLD_SILVER = 234,
		LOTTERY2_MANAGER = 236,

//200
		GM_COMMAND_START = 10000,
		GMCMD_MOVE_TO_PLAYER,		//201
		GMCMD_RECALL_PLAYER,		//202
		GMCMD_OFFLINE,			//203
		GMCMD_TOGGLE_INVISIBLE,		//204
		GMCMD_TOGGLE_INVINCIBLE,	//205
		GMCMD_DROP_GENERATOR,		//206
		GMCMD_ACTIVE_SPAWNER,		//207
		GMCMD_GENERATE_MOB,             //208

		GMCMD_PLAYER_INC_EXP,		//209
		GMCMD_RESURRECT,		//210
		GMCMD_ENDUE_ITEM,		//211	
		GMCMD_ENDUE_SELL_ITEM,		//212
		GMCMD_REMOVE_ITEM,		//213
		GMCMD_ENDUE_MONEY,		//214
		GMCMD_ENABLE_DEBUG_CMD,		
		GMCMD_RESET_PROP,
		GMCMD_GET_COMMON_VALUE,	//217
		GMCMD_QUERY_SPEC_ITEM,
		GMCMD_REMOVE_SPEC_ITEM,
		GMCMD_OPEN_ACTIVITY,	//220
		GMCMD_CHANGE_DS,
		GMCMD_QUERY_UNIQUE_DATA,//222
		GM_COMMAND_END,

	};

	namespace CMD
	{
		using namespace INFO;
		struct player_move
		{
			cmd_header header;
			move_info info;
			unsigned short cmd_seq;		//命令序号
		};
		struct player_logout
		{
			cmd_header header;
		};
		struct select_target
		{	
			cmd_header header;
			int id;
		};
		struct normal_attack
		{
			cmd_header header;
			char force_attack;		//强制攻击位 0x01 强制攻击 0x02 不攻击本帮派 0x04不攻击白名
							//技能和物品的的定义与此相同
		};

		struct pickup_matter
		{
			cmd_header header;
			int mid;
			int type;
		};
	
		struct pickup_matter_all
		{
			cmd_header header;

			int count;
			struct entry_t
			{
				int mid;
				int type;
			} matter[];
		};

		struct resurrect
		{
			cmd_header header;
			int param;
		};
		struct player_stop_move
		{
			cmd_header header;
			A3DVECTOR pos;
			unsigned short speed;
			unsigned char dir;
			unsigned char move_mode;		//walk run swim fly .... walk_back run_back
			unsigned short cmd_seq;		//命令序号
			unsigned short use_time;
		};

		struct get_item_info
		{
			cmd_header header;
			unsigned char where;
			unsigned char index;
		};

		struct get_inventory
		{
			cmd_header header;
			unsigned char where;
		};

		struct get_inventory_detail
		{
			cmd_header header;
			unsigned char where;
		};
		
		struct exchange_inventory_item
		{
			cmd_header header;
			unsigned char index1;
			unsigned char index2;
		};

		struct move_inventory_item
		{
			cmd_header header;
			unsigned char src;
			unsigned char dest;
			unsigned int amount;
		};

		struct drop_inventory_item
		{
			cmd_header header;
			unsigned char index;
			unsigned int amount;
		};

		struct drop_equipment_item
		{
			cmd_header header;
			unsigned char index;
		};

		struct exchange_equip_item
		{
			cmd_header header;
			unsigned char idx1;
			unsigned char idx2;
		};

		struct equip_item
		{
			cmd_header header;
			unsigned char idx_inv;
			unsigned char idx_eq;
		};

		struct move_item_to_equipment
		{
			cmd_header header;
			unsigned char idx_inv;  //src
			unsigned char idx_eq;	 //dest
		};

		struct player_goto
		{
			cmd_header header;
			A3DVECTOR pos;
		};

		struct drop_money
		{
			cmd_header header;
			unsigned int amount; 
		};

		struct self_get_property
		{
			cmd_header header;
		};

		struct set_status_point
		{
			cmd_header header;
			unsigned int vit;
			unsigned int eng;
			unsigned int str;
			unsigned int agi;
		};

		struct get_extprop_base
		{
			cmd_header header;
		};

		struct get_extprop_move
		{
			cmd_header header;
		};

		struct get_extprop_attack
		{
			cmd_header header;
		};

		struct get_extprop_defense
		{
			cmd_header header;
		};

		struct team_invite
		{
			cmd_header header;
			int id;		//想谁发起邀请 
		};

		struct team_agree_invite
		{
			cmd_header header;
			int id;		//谁进行的邀请
			int team_seq;
		};

		struct team_reject_invite
		{
			cmd_header header;
			int id;		//谁进行的邀请
		};

		struct team_leave_party
		{
			cmd_header header;
		};

		struct team_kick_member
		{
			cmd_header header;
			int id;
		};
		
		struct team_get_teammate_pos
		{
			cmd_header header;
			unsigned short count;
			int id[];
		};

		struct get_others_equipment
		{
			cmd_header header;
			unsigned short size;
			int idlist[];
		};


		struct set_pickup_flag
		{
			cmd_header header;
			short pickup_flag;
		};


		struct service_hello
		{
			cmd_header header;
			int id;
		};

		struct service_get_content
		{
			cmd_header header;
			int service_type;
		};

		struct service_serve
		{
			cmd_header header;
			int service_type;
			unsigned int len;
			char content[];
		};

		struct logout
		{
			cmd_header header;
			int logout_type;
		};

		struct get_own_wealth
		{
			cmd_header header;
			char detail_inv;
			char detail_equip;
			char detail_task;
		};

		struct get_all_data
		{
			cmd_header header;
			char detail_inv;
			char detail_equip;
			char detail_task;
		};

		struct use_item
		{
			cmd_header header;
			unsigned char where;
			unsigned char count;
			unsigned short index;
			int  item_id;
		};


		struct cast_skill
		{
			cmd_header header;
			int skill_id;
			unsigned char force_attack;
			unsigned char target_count;
			int  targets[];
		};

		struct cancel_action
		{
			cmd_header header;
		};

		struct recharge_equipped_flysword
		{	
			cmd_header header;
			unsigned char element_index; 
			int count;
		};
		
		struct recharge_flysword
		{	
			cmd_header header;
			unsigned char element_index; 
			unsigned char flysword_index;
			int count;
			int flysword_id;
		};

		struct use_item_with_target
		{
			cmd_header header;
			unsigned char where;
			unsigned char force_attack; //只对攻击性物品有效
			unsigned short index;
			int  item_id;
		};

		struct sit_down
		{
			cmd_header header;
		};

		struct stand_up
		{
			cmd_header header;
		};
		
		struct emote_action 
		{
			cmd_header header;
			unsigned short action;
		};

		struct task_notify
		{
			cmd_header header;
			unsigned int size;
			char buf[0];
		};

		struct assist_select
		{
			cmd_header header;
			int partner;
		};

		struct continue_action
		{
			cmd_header header;
		};

		struct get_item_info_list
		{
			cmd_header header;
			char  where;
			unsigned char  count;
			unsigned char  item_list[];
		};

		struct gather_material
		{
			cmd_header header;
			int mid;
			short tool_where;
			short tool_index;
			int tool_type;
			//int space_id; //162
			int task_id;
		};

		struct get_trashbox_info
		{
			cmd_header header;
			char is_usertrashbox;		//1—帐号仓库  0—角色仓
			char detail;
		};

		struct exchange_trashbox_item
		{
			cmd_header header;
			char where;
			unsigned char index1;
			unsigned char index2;
		};

		struct move_trashbox_item
		{
			cmd_header header;
			char where;
			unsigned char src;
			unsigned char dest;
			unsigned int amount;
		};

		struct exchange_trashbox_inventory
		{
			cmd_header header;
			char where;
			unsigned char idx_tra;
			unsigned char idx_inv;
		};

		struct move_trashbox_item_to_inventory
		{
			cmd_header header;
			char where;
			unsigned char idx_tra;
			unsigned char idx_inv;
			unsigned int amount;
		};

		struct move_inventory_item_to_trashbox
		{
			cmd_header header;
			char where;
			unsigned char idx_inv;
			unsigned char idx_tra;
			unsigned int amount;
		};
		
		struct excnahge_trashbox_money
		{
			cmd_header header;
			char is_usertrashbox;		//1—帐号仓库  0—角色仓
			unsigned int inv_money;
			unsigned int trashbox_money;
		};

		struct tricks_action 
		{
			cmd_header header;
			unsigned char action;
		};

		struct set_adv_data
		{
			cmd_header header;
			int data1;
			int data2;
		};

		struct clr_adv_data
		{
			cmd_header header;
		};

		struct team_lfg_request
		{
			cmd_header header;
			int id;
		};

		struct team_lfg_reply
		{
			cmd_header header;
			int id;
			bool result;
		};

		struct query_player_info_1
		{
			cmd_header header;
			unsigned short count;
			int id[];
		};

		struct query_npc_info_1
		{
			cmd_header header;
			unsigned short count;
			int id[];
		};

		struct session_emote_action
		{
			cmd_header header;
			//限制为256之内
			unsigned char action;
		};

		struct concurrent_emote_request
		{
			cmd_header header;
			unsigned short action;
			int target;
		};

		struct concurrent_emote_reply
		{
			cmd_header header;
			unsigned short result;
			unsigned short action;
			int target;
		};

		struct team_change_leader
		{
			cmd_header header;
			int new_leader;
		};

		struct dead_move 
		{
			cmd_header header;
			float y;
			unsigned short use_time;	//使用的时间 单位是ms
							//使用的时间对于逻辑服务器来说，只是一个参考值
							//同时用于检测用户的指令是否正确，无论如何，
							//用户的移动都会在固定的0.5秒钟以后进行
			unsigned short speed;
			unsigned char  move_mode;		//walk run swim fly .... walk_back run_back
			unsigned short cmd_seq;
		};
		
		struct dead_stop_move 
		{
			cmd_header header;
			float y;
			unsigned short speed;
			unsigned char dir;
			unsigned char move_mode;		//walk run swim fly .... walk_back run_back
			unsigned short cmd_seq;
		};

		struct enter_sanctuary
		{
			cmd_header header;
			int id;		//self id or pet id
		};

		struct enter_pk_protected
		{
			cmd_header header;
		};

		struct open_personal_market
		{
			cmd_header header;
			unsigned short count;
			char name[62];
			struct entry_t
			{
				int type;
				unsigned int index;
				unsigned int count;
				unsigned int price;
			} list[];
		};

		struct cancel_personal_market
		{
			cmd_header header;
		};

		struct query_personal_market_name
		{
			cmd_header header;
			unsigned short count;
			int list[];
		};

		struct complete_travel
		{
			cmd_header header;
		};

		struct cast_instant_skill
		{
			cmd_header header;
			int skill_id;
			unsigned char force_attack;
			unsigned char target_count;
			int  targets[];
		};

		struct destroy_item
		{
			cmd_header header;
			unsigned char where;		//在哪个包裹栏，0 标准，2 任务，1 装备
			unsigned char index;		//索引
			int type;			//是哪种物品
		};

		struct enable_pvp_state
		{
			cmd_header header;
		};

		struct disable_pvp_state
		{
			cmd_header header;
		};

		struct switch_fashion_mode
		{
			cmd_header header;
		};

		struct region_transport
		{
			cmd_header header;
			int region_index;
			int target_tag;
		};

		struct cast_pos_skill
		{
			cmd_header header;
			int skill_id;
			A3DVECTOR pos;
			unsigned char force_attack;
			unsigned char target_count;
			int  targets[];
		};

		struct active_rush_mode
		{
			cmd_header header;
			int is_active;
		};

		struct query_double_exp_info
		{
			cmd_header header;
		};

		struct duel_request
		{
			cmd_header header;
			int target;
		};

		struct duel_reply
		{
			cmd_header header;
			int who;
			int param; // 0 同意  1 不同意
		};

		struct bind_player_request
		{
			cmd_header header;
			int param_id;
			int who;
		};

		struct bind_player_invite
		{
			cmd_header header;
			int param_id;
			int who;
		};

		struct bind_player_request_reply
		{
			cmd_header header;
			int param_id;
			int who;
			int param;
		};

		struct bind_player_invite_reply
		{
			cmd_header header;
			int param_id;
			int who;
			int param;
		};

		struct query_other_equip_detail
		{
			cmd_header header;
			int target;
		};


		struct summon_pet
		{
			cmd_header header;
			unsigned int pet_index;
		};

		struct banish_pet
		{
			cmd_header header;
			unsigned int pet_index;
		};

		struct pet_ctrl_cmd
		{
			cmd_header header;
			int  target;
			int pet_cmd;
			char buf[];
		};

		struct debug_delivery_cmd
		{
			cmd_header header;
			short  type;
			char buf[];
		};

		struct debug_gs_cmd
		{
			cmd_header header;
			char buf[];
		};

		struct mall_shopping
		{       
			cmd_header header;
			unsigned int count;
			struct __entry
			{
				int goods_count;
				int goods_id;
				int goods_index;
				int goods_slot;
			}list[];
			//.....
		};
		
		struct use_item_with_arg
		{       
			cmd_header header;
			unsigned char where;
			unsigned char count;
			unsigned short index;
			int  item_id;
			char arg[];
		};

		//lgc elf相关命令
		struct elf_add_attribute
		{
			cmd_header header;
			short str;
			short agi;
			short vit;
			short eng;
		};

		struct elf_add_genius
		{
			cmd_header header;
			short genius[5];
		};

		struct elf_player_insert_exp
		{
			cmd_header header;
			unsigned int exp;
			char use_sp;
		};

		struct elf_equip_item
		{
			cmd_header header;
			unsigned char index_inv;
		};

		struct elf_change_secure_status
		{
			cmd_header header;
			unsigned char status;
		};
		
		struct cast_elf_skill
		{
			cmd_header header;
			unsigned short skill_id;
			unsigned char force_attack;
			unsigned char target_count;
			int  targets[];
		};

		struct recharge_equipped_elf
		{	
			cmd_header header;
			unsigned char element_index; 
			int count;
		};

		struct get_mall_item_price
		{
			cmd_header header;
			short start_index;  //若两参数均为0, 则表示扫描整个表
			short end_index;	//否则[start_index,end_index)内的商品被扫描
		};

		struct equip_trashbox_fashion_item
		{
			cmd_header header;
			unsigned char trash_idx_body;	//将时装仓库中时装分别与身上的时装衣服裤子鞋手套交换,255代表不交换
			unsigned char trash_idx_leg;
			unsigned char trash_idx_foot;
			unsigned char trash_idx_wrist;			
			unsigned char trash_idx_head;
			unsigned char trash_idx_weapon;
		};
	
		struct check_security_passwd
		{
			cmd_header header;
			unsigned int passwd_size;
			char passwd[];
		};

		struct notify_force_attack
		{
			cmd_header header;
			char force_attack;
			char refuse_bless;
		};
		
		struct dividend_mall_shopping
		{       
			cmd_header header;
			unsigned int count;
			struct __entry
			{
				int goods_id;
				int goods_index;
				int goods_slot;
			}list[];
			//.....
		};
		
		struct get_dividend_mall_item_price
		{
			cmd_header header;
			short start_index;  //若两参数均为0, 则表示扫描整个表
			short end_index;	//否则[start_index,end_index)内的商品被扫描
		};

		struct choose_multi_exp
		{
			cmd_header header;
			int index;
		};

		struct toggle_multi_exp
		{
			cmd_header header;
			char is_activate;
		};
		
		struct multi_exchange_item
		{
			cmd_header header;
			unsigned char location;
			unsigned char count;
			struct _operation
			{
				unsigned char index1;
				unsigned char index2;
			}operations[];
		};

		struct sysauction_op
		{
			cmd_header header;
			int type;
			char buf[];
		};
		
		struct calc_network_delay
		{
			cmd_header header;
			int	timestamp;
		};

		struct get_faction_fortress_info 
		{
			cmd_header header;
		};

		struct congregate_reply
		{
			cmd_header header;
			char type;
			char agree;
			int sponsor;
		};

		struct get_force_global_data
		{
			cmd_header header;
		};

		struct produce4_choose
		{
			cmd_header header;
			char remain; //是否保留旧装备(0 玩家选择新装备 1 保留旧装备)
		};

		struct recharge_online_award
		{
			cmd_header header;
			int type;
			unsigned int count;
			struct entry
			{
				int type;
				unsigned int index; 
				unsigned int count;
			}list[];
		};

		struct toggle_online_award
		{
			cmd_header header;
			int type;
			char activate;
		};

		struct query_profit_time
		{
			cmd_header header;
		};

		struct countrybattle_get_personal_score
		{
			cmd_header header;
		};

		struct get_server_timestamp
		{
			cmd_header header;
		};

		struct countrybattle_leave 
		{
			cmd_header header;
		};
		
		struct get_cash_money_exchg_rate
		{
			cmd_header header;
		};

		struct evolution_pet
		{
			cmd_header header;
			unsigned int pet_index;
			unsigned int formula_index;
		};
		
		struct add_pet_exp
		{
			cmd_header header;
			unsigned int pet_index;
			unsigned int item_num;
		};
		
		struct rebuild_pet_nature
		{
			cmd_header header;
			unsigned int pet_index;
			unsigned int formula_index;
		};

		struct rebuild_pet_inherit_ratio
		{
			cmd_header header;
			unsigned int pet_index;
			unsigned int formula_index;
		};
		
		struct pet_rebuildinherit_choose
		{
			cmd_header header;
			char isaccept;
		};

		struct pet_rebuildnature_choose
		{
			cmd_header header;
			char isaccept;
		};

		struct exchange_wanmei_yinpiao
		{
			cmd_header header;
			char is_sell;				//1-卖银票 0-买银票
			unsigned int count;
		};

		struct try_refine_meridian
		{
			cmd_header header;
			int index;
		};

		struct player_give_present
		{
			cmd_header header;
			int roleid;					//赠予对象的roleid
			int mail_id;				//索取物品邮件的索引，没有的话为-1
			int goods_id;				//赠予物品的id
			int goods_index;			//赠予物品在商城中的索引
			int goods_slot;				//赠予物品的销售信息索引
		};

		struct player_ask_for_present
		{
			cmd_header header;
			int roleid;					//索取对象的roleid
			int goods_id;				//索取物品的id
			int goods_index;			//索取物品在商城中的索引
			int goods_slot;				//索取物品的销售信息索引
		};

		struct countrybattle_get_stronghold_state
		{
			cmd_header header;
		};
		
		struct query_touch_point 
		{ 
			cmd_header header;
		};

		struct cost_touch_point 
		{ 
			cmd_header header; 
			unsigned int  index;  // 商品索引
			unsigned int  lots;   // 批量数
			int  itemid; // 以下4个和客户端表中值对应 冗余校检用
			unsigned int  count;
			unsigned int  price;
			int	 expiretime;
		};

		struct query_title
		{
			cmd_header header;
			int roleid;
		};

		struct change_title
		{
			cmd_header header;
			unsigned short titleid;
		};

		struct daily_signin
		{
			cmd_header header;
		};

		struct late_signin
		{
			cmd_header header;
			char type;    	// 0 天补签 1 月补签 2 年补签
			int itempos;   	// 消耗物品位置
			//int desttime;   // 补签时间点 当月第一未签订日|月第一天|年第一天
		};

		struct apply_signinaward 
		{
			cmd_header header;
			char type;  // 0x01 月度 0x02 年度 0x04 全勤 0x08 每日签到领奖
			int mon;    // 月份
		};

		struct refresh_signin
		{
			cmd_header header;
		};

		struct switch_in_parallel_world
		{
			cmd_header header;
			int key;
		};

		struct query_parallel_world
		{
			cmd_header header;
		};
		
		struct query_unique_data 
		{ 
			cmd_header header;
			int count;
			int keys[];
		};

		struct get_reincarnation_tome
		{
			cmd_header header;
		};

		struct rewrite_reincarnation_tome
		{
			cmd_header header;
			unsigned int record_index;
			int record_level;
		};

		struct activate_reincarnation_tome
		{
			cmd_header header;
			char active;
		};
		
		struct auto_team_set_goal
		{
			cmd_header header;
			char goal_type;
			char op;
			int goal_id;
		};
		
		struct auto_team_jump_to_goal
		{
			cmd_header header;
			int goal_id;
		};

		struct trickbattle_leave
		{
			cmd_header header;
		};

		struct trickbattle_upgrade_chariot
		{
			cmd_header header;
			int chariot;	
		};

		struct swallow_generalcard
		{
			cmd_header header;
			unsigned char equip_idx;
			unsigned char is_inv;	//1-包裹 0-卡牌仓库
			unsigned char inv_idx;
			unsigned int count;
		};

		struct equip_trashbox_item
		{
			cmd_header header;
			unsigned char where;
			unsigned char trash_idx;
			unsigned char equip_idx;
		};
		
		struct send_mass_mail
		{
			cmd_header header;
			int	service_id;
			char data[];
		};

		struct random_mall_shopping 
		{ 
			cmd_header header;
			int entryid;
			int opt;
		};

		struct query_mafia_pvp_info
		{
			cmd_header header;
			int mafia_id;
		};

        struct query_can_inherit_addons
        {
            cmd_header header;
            int equip_id;
            unsigned char inv_idx;
        };

        struct activate_region_waypoints
        {
            cmd_header header;
            unsigned char num;
            int waypoints[];
        };

		struct instance_reenter_request
		{
			cmd_header header;
			bool agree_reenter;
		};

		struct solo_challenge_operate_request
		{
			cmd_header header;
			int opttype;
			char data[];
		};

		struct astrolabe_operate_request
		{
			cmd_header header;
			int  opttype;
			char data[];
		};

        struct property_score_request
        {
            cmd_header header;
            int client_data;
        };
		
		struct fix_position_transmit_operate_request
		{
			cmd_header header;
			int opttype;
			char data[];
		};
		
		struct get_cash_vip_mall_item_price
		{
			cmd_header header;
			short start_index;  //若两参数均为0, 则表示扫描整个表
			short end_index;	//否则[start_index,end_index)内的商品被扫描
		};
		
		struct cash_vip_mall_shopping
		{       
			cmd_header header;
			unsigned int count;
			struct __entry
			{
				int goods_id;
				int goods_index;
				int goods_slot;
			}list[];
			//.....
		};

        struct update_enemylist
        {
            cmd_header header;
            char optype;
            int rid;
        };

        struct lookup_enemy
        {
            cmd_header header;
            int rid;
        };


/*------------------------------内部GM 命令------------------------------------*/		
		struct  gmcmd_move_to_player
		{
			cmd_header header;
			int id;
		};

		struct gmcmd_recall_player
		{
			cmd_header header;
			int id;
		};

		struct gmcmd_player_inc_exp
		{
			cmd_header header;
			int exp;
			int sp;
		};

		struct gmcmd_endue_item
		{
			cmd_header header;
			int item_id;
			unsigned int count;
		};

		struct gmcmd_endue_sell_item
		{
			cmd_header header;
			int item_id;
			unsigned int count;
		};

		struct gmcmd_remove_item
		{
			cmd_header header;
			int item_id;
			unsigned int count;
		};

		struct gmcmd_endue_money
		{
			cmd_header header;
			int money;
		};


		struct gmcmd_offline
		{
			cmd_header header;
		};

		struct gmcmd_resurrect
		{
			cmd_header header;
		};

		struct gmcmd_enable_debug_cmd
		{
			cmd_header header;
		};

		struct gmcmd_drop_generator
		{
			cmd_header header;
			int id;
		};

		struct gmcmd_active_spawner
		{
			cmd_header header;
			bool is_active;
			int sp_id;
		};

		struct gmcmd_generate_mob
		{
			cmd_header header;
			int mob_id;
			int vis_id;
			short count;
			short life;
			unsigned int name_len;
			char name[];
		};
		
		struct gmcmd_get_common_value
		{
			cmd_header header;
			int key;
		};

		struct gmcmd_query_spec_item
		{
			cmd_header header;
			int roleid;
			int type;
		};

		struct gmcmd_remove_spec_item
		{
			cmd_header header;
			int roleid;
			int type;
			unsigned char where;
			unsigned char index;
			unsigned int count;
		};

		struct gmcmd_open_activity
		{
			cmd_header header;
			int activity_id;
			char is_open;
		};
		
		struct gmcmd_change_ds
		{
			cmd_header header;
			int flag;
		};
		
		struct gmcmd_query_unqiue_data
		{
			cmd_header header;
			int key;
		};
		
		struct change_gold_silver
		{
			cmd_header header;
			unsigned char is_silver;
			unsigned int money;
		};

		struct lottery_manager
		{
			cmd_header header;
			unsigned int manager;
			unsigned char param[];
		};

		struct lottery2_manager
		{
			cmd_header header;
			unsigned int manager;
			unsigned char param[];
		};

	}
}

#pragma pack()
#endif

