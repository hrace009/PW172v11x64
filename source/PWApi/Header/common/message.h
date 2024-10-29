#ifndef __ONLINEGAME_COMMON_MESSAGE_H__
#define __ONLINEGAME_COMMON_MESSAGE_H__

#include <stdlib.h>
#include "ASSERT.h"
#include <amemory.h>
struct MSG 
{
	int 	message;	//消息的类型
	struct XID target;	//收消息的目标，可能是服务器，玩家，物品，NPC等
	struct XID source;	//从哪里发过来的，可能的id和上面一样
	A3DVECTOR pos;		//消息发出时的位置，有的消息可能位置并无作用
	int	ttl;		//time to live,这个值如果小于0，那么就不会进行再次转发了
	int	param;		//一个参数，如果这个参数够用，那么就使用这个参数
	size_t 	content_length;	//消息的具体数据长度
	const void * content;	//消息的具体数据 网络上传播时这个字段无效
private:
	enum {FAST_ALLOC_LEN = 128};
	friend void * SerializeMessage(const MSG &);
	friend void FreeMessage(MSG *);
};

inline void * SerializeMessage(const MSG & msg)
{
	void * buf;
	size_t length = msg.content_length;
	if(length <= MSG::FAST_ALLOC_LEN)
	{
	//	printf("%d %dalloced\n",sizeof(MSG) + length,msg.message);
		buf = abase::fast_allocator::align_alloc(sizeof(MSG) + length);		//必须对齐，考虑多个msg
		memcpy(buf,&msg,sizeof(MSG));
		if(length)
		{
			memcpy((char*)buf + sizeof(MSG),msg.content,length);
		}
	}
	else
	{
		buf = abase::fast_allocator::raw_alloc(sizeof(MSG) + length);
		memcpy(buf,&msg,sizeof(MSG));
		memcpy((char*)buf + sizeof(MSG),msg.content,msg.content_length);
	}
	return buf;
}

inline MSG * DupeMessage(const MSG & msg)
{
	MSG * pMsg = (MSG*)SerializeMessage(msg);
	pMsg->content = ((char*)pMsg) + sizeof(MSG);
	return pMsg;
}

inline void FreeMessage(MSG * pMsg)
{
	ASSERT(pMsg->content == ((char*)pMsg) + sizeof(MSG));
	size_t length = pMsg->content_length;
	if(length <= MSG::FAST_ALLOC_LEN)
	{
		abase::fast_allocator::align_free(pMsg, sizeof(MSG) + length);
	}
	else
	{
		abase::fast_allocator::raw_free(pMsg);
	}
}
inline void BuildMessage(MSG & msg, int message, const XID &target, const XID & source,
			const A3DVECTOR & pos,int param = 0,
			const void * content = NULL,size_t content_length = 0)
{
	msg.message = message;
	msg.target = target;
	msg.source = source;
	msg.pos = pos;
	msg.ttl = 2;
	msg.param = param;
	msg.content_length = content_length;
	msg.content = content;
}

enum
{
//	normal message
	GM_MSG_NULL,				//空消息
	GM_MSG_FORWARD_USERBC,			//转发的用户广播
	GM_MSG_FORWARD,				//转发的消息，内容应该作为一条新的消息内容来解释
	GM_MSG_FORWARD_BROADCAST,		//转发的消息广播消息,content是另外一条完整的消息
	GM_MSG_USER_GET_INFO,			//用户取得必要的数据

//5
	GM_MSG_IDENTIFICATION,			//服务器告知自己的身份,原的类型必须是server并且id是他的符号
	GM_MSG_SWITCH_GET,			//取得用户数据,服务器切换，取得用户数据 param是 tag,content是key
	GM_MSG_SWITCH_USER_DATA,		//用户数据,SWITCH_GET的回应
	GM_MSG_SWITCH_NPC,			//NPC切换服务器
	GM_MSG_USER_MOVE_OUTSIDE,		//用户在边界移动

//10	
	GM_MSG_USER_NPC_OUTSIDE,		//NPC在边界处移动，不同之处在于NPC不需要取得新看到区域的对象
	GM_MSG_ENTER_WORLD,			//给controller的，表示用户已经进入了世界
	GM_MSG_ATTACK,				//目标和源都必须是个体
	GM_MSG_SKILL,				//目标和源都必须是个体
	GM_MSG_PICKUP,				//拣起物品,目标一般是物品

//15
	GM_MSG_FORCE_PICKUP,			//强制捡起物品，不校验所书者ID和组队ID
	GM_MSG_PICKUP_MONEY,			//物品通知用户拣到钱 param是钱数  content是谁丢弃的
	GM_MSG_PICKUP_TEAM_MONEY,		//物品通知队长拣到钱 param是钱数  content是谁丢弃的
	GM_MSG_RECEIVE_MONEY,			//通知玩家得到钱（可能是组队)
	GM_MSG_PICKUP_ITEM,			//物品通知用户拣到物品 param是 palyer_id | 0x80000000(如果组队）

//20
	GM_MSG_ERROR_MESSAGE,			//让player发送一个error message
	GM_MSG_NPC_SVR_UPDATE,			//NPC发生了服务器切换，这个消息只发给处于移走状态的原生NPC
	GM_MSG_EXT_NPC_DEAD,			//外部的NPC的死亡消息(真正删除)，这个消息只发给处于移走状态的原生NPC
	GM_MSG_EXT_NPC_HEARTBEAT,		//外部NPC的心跳，用于判断是否超时 
	GM_MSG_WATCHING_YOU,			//主动怪物激活的消息,由玩家或npc发出，后面是一个watching_t的结构

//25
//	AGGRO  message 
	GM_MSG_GEN_AGGRO,			//生成aggro，后面附加了一个aggro_info_t的结构
	GM_MSG_TRANSFER_AGGRO,			//aggro的传送 目前只传送第一位 content是一个XID,如果该XID的id为-1    则清空仇恨列表 param是该人仇恨值
	GM_MSG_AGGRO_ALARM,			//aggro警报，当受到攻击时会发送，后面附加了一个aggro_alarm_t未使用
	GM_MSG_AGGRO_WAKEUP,			//aggro警报，将休眠的怪物惊醒,后面附加了一个aggro_alarm_t未使用
	GM_MSG_AGGRO_TEST,			//aggro测试,只有当发送者在aggro列表中，才会引发新的aggro，后面附加了一个aggro_info_t未使用
	
//30
	GM_MSG_OBJ_SESSION_END,			//对象的session完成
	GM_MSG_OBJ_SESSION_REPEAT,		//表示session要继续执行 
	GM_MSG_OBJ_ZOMBIE_END,			//表示要结束僵尸状态
	GM_MSG_EXPERIENCE,			//得到经验值	content 是一个msg_exp_t
	GM_MSG_GROUP_EXPERIENCE,		//得到组队经验值 conennt 是多个msg_grp_exp_t , param 造成的总伤害
	
//35
	GM_MSG_TEAM_EXPERIENCE,			//得到组队经验值 conennt 是msg_exp_t 超过距离经验值会被忽略 param 是杀死的npcid 如刮?则不是本队伍杀死的
	GM_MSG_QUERY_OBJ_INFO00,		//取得对象的info00 param是发送者的sid ,content是一个int代表cs_index
	GM_MSG_HEARTBEAT,			//发给自己的心跳消息  参数是这次Heartbeat的秒数
	GM_MSG_HATE_YOU,
	GM_MSG_TEAM_INVITE,			//请求某人加入队伍param是teamseq, content是一个int 表示pickup_flag

//40	
	GM_MSG_TEAM_AGREE_INVITE,		//被邀请人同意加入队伍 content是一个int(表示职业)+ team_mutable_prop
	GM_MSG_TEAM_REJECT_INVITE,		//拒绝加入邀请
	GM_MSG_JOIN_TEAM,			//队长同意某人加入队伍 param高位是捡取方式 param低位是队员个数，content是member_entry的表 
	GM_MSG_JOIN_TEAM_FAILED,		//对象无法加入队伍，应该从队伍中去除
	GM_MSG_MEMBER_NOTIFY_DATA,		//组队成员通知其他人自己的基础信息 content 是一个team_mutable_prop

//45	
	GM_MSG_NEW_MEMBER,			//leader通知新成员加入，content是一个member_entry list param是数量
	GM_MSG_LEAVE_PARTY_REQUEST,
	GM_MSG_LEADER_CANCEL_PARTY,
	GM_MSG_MEMBER_NOT_IN_TEAM,
	GM_MSG_LEADER_KICK_MEMBER,

//50	
	GM_MSG_MEMBER_LEAVE,
	GM_MSG_LEADER_UPDATE_MEMBER,
	GM_MSG_GET_MEMBER_POS,			//要求队友发送位置 param是发送者的sid ,content是一个int代表cs_index
	GM_MSG_QUERY_PLAYER_EQUIPMENT,		//取得特定玩家的数据，要求平面距离在一定范围之内param是发送者的sid ,content是一个int代表cs_index
	GM_MSG_TEAM_PICKUP,			//队友分配到物品， param 是 type, content 是count

//55	
	GM_MSG_TEAM_CHAT,			//组队聊天 param 是channel, content 是内容
	GM_MSG_SERVICE_REQUEST,			//player要求服务的消息 param 是服务类型 content 是具体数据 ?	
	GM_MSG_SERVICE_DATA,			//服务的数据到达 param 是服务类型  content 是 具体数据
	GM_MSG_SERVICE_HELLO,			//player 向服务商问好  param 是 player自己的faction
	GM_MSG_SERVICE_GREETING,		//服务商进行回话 可能需要在里面返回服务列表$$$$(现在未做)

//60	
	GM_MSG_SERVICE_QUIERY_CONTENT,		//取得服务内容 	 param 是服务类型, content可看作pair<cs_index,sid>
	GM_MSG_EXTERN_OBJECT_APPEAR,		//content 是extern_object_manager::object_appear
	GM_MSG_EXTERN_OBJECT_DISAPPEAR,		//消失或者
	GM_MSG_EXTERN_OBJECT_REFRESH,		//更新位置和血值，param中保存的是血值 
	GM_MSG_USER_APPEAR_OUTSIDE,		//用户在外面出现，要发送必要的数据给该玩家，content 里是sid,param是linkd id

//65
	GM_MSG_FORWARD_BROADCAST_SPHERE,	//转发的消息广播消息,content是另外一条完整的消息
	GM_MSG_FORWARD_BROADCAST_CYLINDER,	//转发的消息广播消息,content是另外一条完整的消息
	GM_MSG_FORWARD_BROADCAST_TAPER,		//转发的消息广播消息,content是另外一条完整的消息
	GM_MSG_ENCHANT,				//使用辅助魔法
	GM_MSG_ENCHANT_ZOMBIE,			//使用辅助魔法,专门给死人用的

//70
	GM_MSG_OBJ_SESSION_REPEAT_FORCE,	//表示session要repeat ，后面即使有任务也要继续执行
	GM_MSG_NPC_BE_KILLED,			//消息发给杀死npc的玩家，param 表示被杀死npc的类型 content是NPC的级别
	GM_MSG_NPC_CRY_FOR_HELP,		//npc 进行求救操作
	GM_MSG_PLAYER_TASK_TRANSFER,		//任务在player之间进行传送和通讯的函数
	GM_MSG_PLAYER_BECOME_INVADER,		//成为粉名 msg.param 是增加的时间

//75
	GM_MSG_PLAYER_BECOME_PARIAH,		//成为红名 
	GM_MSG_FORWARD_CHAT_MSG,		//转发的用户聊天信息,param是rlevel,source是XID(-channel,self_id)
	GM_MSG_QUERY_SELECT_TARGET,		//取得队友选择的对象
	GM_MSG_NOTIFY_SELECT_TARGET,		//取得队友选择的对象
	GM_MSG_SUBSCIBE_TARGET,			//要求订阅一个对象

//80
	GM_MSG_UNSUBSCIBE_TARGET,		//要求订阅一个对象
	GM_MSG_SUBSCIBE_CONFIRM,		//确认订阅是否存在
	GM_MSG_PRODUCE_MONEY,			//通知系统产生金钱 发送源是所属者，param是组id， content是钱数
	GM_MSG_PRODUCE_MONSTER_DROP,		//通知系统产生怪物掉落物品和金钱， 发送源是所属者，param是money， content 是 struct { int team_id; int team_seq;int npc_id;int item_count; int item[];}
	GM_MSG_GATHER_REQUEST,			//请求收集原料，  param 是玩家的faction, content 分别是玩家级别、采集工具和任务ID

//85
	GM_MSG_GATHER_REPLY,			//通知可以进行采集  param 是采集需要的时间
	GM_MSG_GATHER_CANCEL,			//取消采集
	GM_MSG_GATHER,				//进行采集，要求取得物品
	GM_MSG_GATHER_RESULT,			//采集完成，param 内是采集到的物品id, content是数量 和可能附加的任务ID
	GM_MSG_HP_STEAL,				//收到吸血的结果

//90
	GM_MSG_INSTANCE_SWITCH_GET,		//取得用户数据,服务器切换，取得用户数据 用于副本间的切换 param是key
	GM_MSG_INSTANCE_SWITCH_USER_DATA,	//用户数据,SWITCH_SWITCH_GET的回应
	GM_MSG_EXT_AGGRO_FORWARD,		//通知原生npc进行仇恨转发 param 是rage大小， content是产生仇恨的id
	GM_MSG_TEAM_APPLY_PARTY,		//申请进入队伍选项
	GM_MSG_TEAM_APPLY_REPLY,		//申请成功回复 其中的param是seq	

//95
	GM_MSG_QUERY_INFO_1,			//查询INFO1，可以发给玩家或者NPC,param的内容是cs_index,content是sid
	GM_MSG_CON_EMOTE_REQUEST,		//进行协同动作的请求 param 是 action
	GM_MSG_CON_EMOTE_REPLY,			//进行协同动作的回应 param 是action和同意与否的两个字节的组合
	GM_MSG_TEAM_CHANGE_TO_LEADER,		//通知别人要成为leader
	GM_MSG_TEAM_LEADER_CHANGED,		//通知队友队长的改变

//100
	GM_MSG_OBJ_ZOMBIE_SESSION_END,		//死亡后进行session的操作，其他定义和正常的session操作一样
	GM_MSG_QUERY_PERSONAL_MARKET_NAME,	//取得摆摊的名字，param是发送者的sid ,content是一个int代表cs_index
	GM_MSG_HURT,				//对象产生伤害 content 是msg_hurt_extra_info_t
	GM_MSG_DEATH,				//强行让对象死亡,param=0非任务=1任务有损=2任务无损(此param仅对player有效) 
	GM_MSG_PLANE_SWITCH_REQUEST,		//请求开始传送，content是key，如果进行传送，则返回 SWITCH_REPLAY

//105
	GM_MSG_PLANE_SWITCH_REPLY,		//传送请求被确认，content是key
	GM_MSG_SCROLL_RESURRECT,		//卷轴复活  param表示复活者是否开启了pvp模式1表示开启了
	GM_MSG_LEAVE_COSMETIC_MODE,		//脱离整容状态
	GM_MSG_DBSAVE_ERROR,			//数据库保存错误
	GM_MSG_SPAWN_DISAPPEAR,			//通知NPC和物品消失 param是condition

//110
	GM_MSG_PET_CTRL_CMD,			//玩家发来的控制消息会用这个消息发给宠物
	GM_MSG_ENABLE_PVP_DURATION,		//激活PVP状态
	GM_MSG_PLAYER_KILLED_BY_NPC,		//玩家被NPC杀死后NPC的逻辑
	GM_MSG_PLAYER_DUEL_REQUEST,             //玩家发出要求duel的请求
	GM_MSG_PLAYER_DUEL_REPLY,               //玩家回应duel的请求，param是是否答应duel

//115
	GM_MSG_PLAYER_DUEL_PREPARE,      	//决斗准备开始 3秒倒计时后开始
	GM_MSG_PLAYER_DUEL_START,               //决斗开始 
	GM_MSG_PLAYER_DUEL_CANCEL,		//停止决斗
	GM_MSG_PLAYER_DUEL_STOP,		//决斗结束
	GM_MSG_DUEL_HURT,			//PVP对象产生伤害content 被忽略

//120
	GM_MSG_PLAYER_BIND_REQUEST,		//请求骑在别人身上
	GM_MSG_PLAYER_BIND_INVITE,		//邀请别人骑在自己身上
	GM_MSG_PLAYER_BIND_REQUEST_REPLY,	//请求骑的回应
	GM_MSG_PLAYER_BIND_INVITE_REPLY,	//邀请骑的回应
	GM_MSG_PLAYER_BIND_PREPARE,		//准备开始连接

//125
	GM_MSG_PLAYER_BIND_LINK,		//连接开始
	GM_MSG_PLAYER_BIND_STOP,		//停止连接
	GM_MSG_PLAYER_BIND_FOLLOW,		//要求玩家跟随
	GM_MSG_QUERY_EQUIP_DETAIL,		//param 为faction, content 为cs_index 和cs_sid
	GM_MSG_PLAYER_RECALL_PET,		//让玩家强制消除召唤状态

//130
	GM_MSG_CREATE_BATTLEGROUND,		//要求战场服务器创建一个战场的消息，主要用于测试
	GM_MSG_BECOME_TURRET_MASTER,		//成为攻城车的master,param是tid, content 是faction
	GM_MSG_REMOVE_ITEM,			//删除一个物品的消息，用于攻城车控制后的物品减少 param是tid
	GM_MSG_NPC_TRANSFORM,			//NPC变形效果，content里保存 中间状态，中间时间 中间标志 最后状态
	GM_MSG_NPC_TRANSFORM2,			//NPC变形效果2，param 是目标ID 如果本来就和目标ID一致了，那么就不变形了

//135
	GM_MSG_TURRET_NOTIFY_LEADER,		//攻城车通知leader自己存在，让其无法再次进行召唤
	GM_MSG_PET_RELOCATE_POS,		//宠物要求重新定位坐标
	GM_MSG_PET_CHANGE_POS,			//主人修改了宠物的坐标
	GM_MSG_PET_DISAPPEAR,			//数据不正确,或者其它情况,主人要求宠物消失
	GM_MSG_PET_NOTIFY_HP,			//宠物通知主人，告知自己的血量 param 是 stamp,content 是float hp ratio

//140
	GM_MSG_PET_NOTIFY_DEATH,		//宠物通知主人自己的死亡
	GM_MSG_PET_MASTER_INFO,			//主人通知宠物自己的数据
	GM_MSG_PET_LEVEL_UP,			//主人通知宠物升级了 ,content是 level
	GM_MSG_PET_HONOR_MODIFY,		//主人通知宠物的忠诚度发生变化
	GM_MSG_MASTER_ASK_HELP,			//主人要求宠物帮助

//145	
	GM_MSG_PET_SET_COOLDOWN,		//宠物通知主人设置冷却时间 msg.param是 cooldown id, content 是 msec
	GM_MSG_MOB_BE_TRAINED,			//怪物被驯服，传送宠物蛋给施法者
	GM_MSG_PET_AUTO_ATTACK,			//主人通知宠物自动攻击 msg.param 是force attack, content是目标
	GM_MSG_PET_SKILL_LIST,			//主人通知宠物新的技能列表
	GM_MSG_SWITCH_FAILED,			//副本通知说传送失败

//150	
	GM_MSG_PET_ANTI_CHEAT,
	GM_MSG_QUERY_PROPERTY,			//查询其他人的属性，param是查询道具在包裹栏索引
	GM_MSG_QUERY_PROPERTY_REPLY,	//查询其他人的属性返回，param是查询道具在包裹栏索引，content是属性数据
	GM_MSG_TRY_CLEAR_AGGRO,			//自身隐身等级大于npc反隐等级则清除npc对自己的仇恨，param是自己的隐身等级
	GM_MSG_NOTIFY_INVISIBLE_DATA,	//将自身的隐身数据通知给宠物,让宠物隐身或现身

//155
	GM_MSG_NOTIFY_CLEAR_INVISIBLE,	//宠物解除隐身通知主人，让主人也解除隐身
	GM_MSG_CONTRIBUTION_TO_KILL_NPC,//玩家杀死npc后，npc发送给玩家的消息，param是npc world_tag content是结构msg_contribution_t
	GM_MSG_GROUP_CONTRIBUTION_TO_KILL_NPC,//队伍杀死npc后，npc发送给玩家的消息，param是npc world_tag content是结构msg_group_contribution_t
	GM_MSG_REBUILD_TEAM_INSTANCE_KEY_REQ,	//队员发给队长的重建组队副本key的请求,param是worldtag,content是重建前的team_instance_key
	GM_MSG_REBUILD_TEAM_INSTANCE_KEY,		//队长发给队员的重建组队副本key,param是worldtag,content是旧的和新的team_instance_key

//160
	GM_MSG_TRANSFER_FILTER_DATA,		//filter转移，param是filter个数，content是filter数据
	GM_MSG_PLANT_PET_NOTIFY_DEATH,		//植物宠通知主人死亡，参数是pet_stamp
	GM_MSG_PLANT_PET_NOTIFY_HP,			//植物宠通知主人信息，参数是pet_stamp，data是msg_plant_pet_hp_notify
	GM_MSG_PLANT_PET_NOTIFY_DISAPPEAR,	//植物宠通知主人消失，参数是pet_stamp
	GM_MSG_PLANT_PET_SUICIDE,			//主人通知植物使其自爆，参数是pet_stamp

//165
	GM_MSG_MASTER_NOTIFY_LAYER,		//主人通知宠物自身layer,参数是petstamp data是char layer
	GM_MSG_INJECT_HP_MP,			//给目标增加hp和mp,data是msg_hp_mp_t
	GM_MSG_DRAIN_HP_MP,				//使目标消耗hp和mp,data是msg_hp_mp_t
	GM_MSG_CONGREGATE_REQUEST,		//集结请求, param集结类型 data:msg_congregate_req_t
	GM_MSG_REJECT_CONGREGATE,		//拒绝集结请求, param集结类型

//170
	GM_MSG_NPC_BE_KILLED_BY_OWNER,	//NPC被玩家杀死,param是npc tid,content是msg_dps_dph_t
	GM_MSG_EXCHANGE_POS,			//玩家之间交换位置，会同时发给两个人
	GM_MSG_EXTERN_HEAL,				//给某某对象加血的消息
	GM_MSG_QUERY_INVENTORY_DETAIL,	//查询玩家包裹详细数据
	GM_MSG_TURRET_OUT_OF_CONTROL,	//解除攻城车的控制

//175
	GM_MSG_TRANSFER_FILTER_GET,		//filter转移, param是filter_mask content是转移的数量
	GM_MSG_PET_TEST_SANCTUARY,		//通知宠物进入了安全区
	GM_MSG_PLAYER_KILLED_BY_PLAYER,	//玩家被玩家杀死，param是msg_player_killed_info_t
	GM_MSG_CREATE_COUNTRYBATTLE,	//要求国战战场服务器创建一个战场的消息，主要用于测试
	GM_MSG_COUNTRYBATTLE_HURT_RESULT,	//国战中通知攻击者实际造成的伤害，param为伤害值，content受攻击者魂力(player)或0(npc)
	
//180
	GM_MSG_LONGJUMP,				//玩家瞬移，param是worldtag, content是pos
	GM_MSG_TRICKBATTLE_PLAYER_KILLED,
	GM_MSG_COUNTRYBATTLE_PLAYER_KILLED,	//国战中玩家死亡
	GM_MSG_MAFIA_PVP_AWARD, //帮派pvp特殊活动奖励
	GM_MSG_MAFIA_PVP_STATUS, //帮派pvp 状态通知
//185	
	GM_MSG_MAFIA_PVP_ELEMENT,// 帮派pvp 加载请求
	GM_MSG_PUNISH_ME,	// 请求对方对己enchant技能
	GM_MSG_REDUCE_CD,	// 给目标降cd
	GM_MSG_DELIVER_TASK, // 发放任务给目标
	GM_MSG_OBJ_ACTION_END,			//对象的action完成
//190	
	GM_MSG_OBJ_ACTION_REPEAT,		//表示action要继续执行 
	GM_MSG_SUBSCIBE_SUBTARGET,			//要求订阅一个次级目标
	GM_MSG_UNSUBSCIBE_SUBTARGET,		//要求取消订阅一个次级目标
	GM_MSG_SUBSCIBE_SUBTARGET_CONFIRM, // 确认次级目标订阅是否存在
	GM_MSG_NOTIFY_SELECT_SUBTARGET,	   // 通知订阅者次级订阅者改变
//195
	GM_MSG_ATTACK_CRIT_FEEDBACK,
	GM_MSG_DELIVER_STORAGE_TASK,       // 发放随机库任务
    GM_MSG_CHANGE_GENDER_LOGOUT,       // 角色变性成功后下线
	GM_MSG_CLEAR_TOWER_TASK,           // 清除单人副本任务
	GM_MSG_CREATE_MNFACTION,	//要求跨服帮派战场服务器创建一个战场的消息，主要用于测试
//200
    GM_MSG_LOOKUP_ENEMY,
    GM_MSG_LOOKUP_ENEMY_REPLY,

//GM所采用的消息	
	GM_MSG_GM_GETPOS=600,			//取得指定玩家的坐标 param 是 cs_index, content 是sid
	GM_MSG_GM_MQUERY_MOVE_POS,		//GM要求查询坐标 用于下一步跳转到玩家处 
	GM_MSG_GM_MQUERY_MOVE_POS_REPLY,	//GM要求查询坐标的回应,用于GM的跳转命令 content是当前的instance key
	GM_MSG_GM_RECALL,			//GM要求进行跳转
	GM_MSG_GM_CHANGE_EXP,			//GM增加exp 和sp , param 是 exp , content 是sp
	GM_MSG_GM_ENDUE_ITEM,			//GM给与了若干物品 ，param 是item id, content 是数目 
	GM_MSG_GM_ENDUE_SELL_ITEM,		//GM给与了商店里卖的物品，其他同上
	GM_MSG_GM_REMOVE_ITEM,			//GM要求删除某些物品，param 是item id, content 是数目
	GM_MSG_GM_ENDUE_MONEY,			//GM增加或者减少金钱
	GM_MSG_GM_RESURRECT,			//GM要求复活
	GM_MSG_GM_OFFLINE,			//GM要求下线 
	GM_MSG_GM_DEBUG_COMMAND,		//GM要求下线 
	GM_MSG_GM_RESET_PP,			//GM进行洗点操作
	GM_MSG_GM_QUERY_SPEC_ITEM,	//GM查询玩家是否存在指定物品
	GM_MSG_GM_REMOVE_SPEC_ITEM,	//GM删除玩家指定物品

	GM_MSG_PICKUP_MONEY2,			//物品通知用户拣到钱 param是钱数  content是谁丢弃的 172
	GM_MSG_PICKUP_TEAM_MONEY2,		//物品通知队长拣到钱 param是钱数  content是谁丢弃的 172
	GM_MSG_RECEIVE_MONEY2,			//通知玩家得到钱（可能是组队) 172

	GM_MSG_MAX,

};

struct msg_usermove_t	//用户移动并且跨越边界的消息
{
	int cs_index;
	int cs_sid;
	int user_id;
	A3DVECTOR newpos;	//消息里面有oldpos
	size_t leave_data_size;	//离开发送的消息大小（该消息附加在后面)
	size_t enter_data_size;	//离开发送的消息大小（该消息附加在后面)
};

struct msg_aggro_info_t
{
	XID source;		//谁生成了这些仇恨
	int aggro;		//仇恨的大小
	int aggro_type;		//仇恨的类型
	int faction;		//对方所属的派系
	int level;		//对方的级别
};

struct msg_watching_t
{
	int level;		//源的级别
	int faction;		//源的派系
	int invisible_degree;//源的隐身级别
};

struct msg_aggro_list_t
{
	int count;
	struct 
	{
		XID id;
		int aggro;
	}list[1];
};

struct msg_cry_for_help_t
{
	XID attacker;
	int lamb_faction;
	int helper_faction;
};

struct msg_aggro_alarm_t
{
	XID attacker;	//攻击者
	int rage;	
	int faction;	//发送者的派系
	int target_faction;	//目标的接受求救类型
};

struct team_exp_entry
{
	int exp;
	int sp;
	XID who;
};

struct msg_exp_t
{
	int level;
	int exp;
	int sp;
};

struct msg_grp_exp_t
{
	int level;
	int exp;
	int sp;
	float rand;
};

struct msg_grpexp_t
{
	XID who;
	int damage;
	int reserve;
	/*
		组队的数据较多
		组队的经验由多个人的伤害组成
		所以附带了所有人的伤害列表,
		列表的第一个元素分别在who.type,who.id damage里保存了 经验值 level/sp 和队伍的team_seq
		其中who.id的高16位为级别，低16位为sp的数目
		这个结构在npc.cpp内部的对象类型为TempDmgNode(备查)

		如果是该队伍造成了最大伤害，则列表的第二个元素保存了杀死的怪物名称和级别
		其中who.type 保存npc tid,who.id 保存了一个随机数,使得大家任务奖励一致

		第二个元素的damage 始终保存怪物的世界tag，无论是否该队伍造成最大伤害
	*/
};

struct gather_reply
{
	int can_be_interrupted;
	int eliminate_tool;	//消耗工具的ID
	unsigned short gather_time_min;
	unsigned short gather_time_max;
};

struct gather_result
{
	int amount;
	int task_id;
	int eliminate_tool;		//如果删除物品则附加此ID
	int mine_tid;
	int life;		//采集到物品的寿命
	char mine_type;	//矿物的类型
};

struct msg_pickup_t
{
	XID who;
	int team_seq;
};

struct msg_gen_money
{
	int team_id;
	int team_seq;
};

struct msg_npc_transform
{
	int id_in_build;
	int time_use;
	int flag;
	int id_buildup;
	enum 
	{
		FLAG_DOUBLE_DMG_IN_BUILD = 1,
	};
};

struct msg_pet_pos_t
{
	A3DVECTOR pos;
	char inhabit_mode;
};

struct msg_pet_hp_notify
{
	float hp_ratio;
	int   cur_hp;
	char  aggro_state;		//三种仇恨状态  0 被动 1 主动 2 发呆
	char  stay_mode;		//两种跟随方式: 0 跟随，1　停留
	char  combat_state;		//是否在战斗
	char  attack_monster;	//是否攻击怪物
	float mp_ratio;
	int   cur_mp;
};

struct msg_invisible_data
{
	int invisible_degree;
	int anti_invisible_degree;
};

struct msg_contribution_t
{
	int npc_id;				//npc的模板id
	bool is_owner;			//是否是怪物所属，所属判定同任务杀怪
	float team_contribution;//队伍贡献，如玩家不在队伍中则为个人贡献
	int team_member_count;	//队伍人数，如玩家不在队伍中则为1
	float personal_contribution;	//个人贡献度
};

struct msg_group_contribution_t
{
	int npc_id;				//npc的模板id
	bool is_owner;			//是否是怪物所属，所属判定同任务杀怪
	int count;
	struct _list{
		XID xid;	
		float contribution;
	}list[];
};

struct msg_plant_pet_hp_notify
{
	float hp_ratio;
	int   cur_hp;
	float mp_ratio;
	int   cur_mp;
};

struct msg_hp_mp_t
{
	int hp;
	int mp;
};

struct msg_query_spec_item_t
{
	int type;
	int cs_index;
	int cs_sid;
};

struct msg_remove_spec_item_t
{
	int type;
	unsigned char where;
	unsigned char index;
	size_t count;
	int cs_index;
	int cs_sid;
};

struct msg_congregate_req_t
{
	int world_tag;
	int level_req;
	int sec_level_req;
    int reincarnation_times_req;
};

struct msg_dps_dph_t
{
	int level;
	int dps;
	int dph;
	bool update_rank;
};

struct msg_player_t
{
	int id;
	int cs_index;
	int cs_sid;
};

struct msg_player_killed_info_t
{
	int cls;
	bool gender;
	int level;
	int force_id;
};

struct msg_hurt_extra_info_t
{
	bool orange_name;
	char attacker_mode;
};

struct msg_mafia_pvp_award_t
{
	int mafia_id;
	int domain_id;
};

struct msg_punish_me_t
{
	int skill_id;
	int skill_lvl;
};

struct msg_reduce_cd_t
{
	int skill_id;
	int msec;
};

#endif

