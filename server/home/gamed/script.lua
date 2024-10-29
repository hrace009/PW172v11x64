--======================================================================================
--Lua manager by Deadraky (C) 2022
--======================================================================================

--======================================================================================
--Константы (не меняйте их, иначе код работать не будет корректно)
--======================================================================================

MIN  					= 60
HOUR 					= MIN*60
DAY  					= HOUR*24
WEEK 					= DAY*7

COOLDOWN_IDX			= 8500
COOLDOWN_CHECK			= 0
COOLDOWN_SET			= 1
COOLDOWN_CHECK_AND_SET	= 2
COOLDOWN_MAX_COUNT		= 4

MAX_ROLE_COUNT 			= 6000
MAX_TAGS				= 128
MAX_SKILL				= 128
MAX_ITEM				= 128

TYPE_INTERVAL  			= 1   --событие по интервалу
TYPE_TIME_WEEK 			= 2   --событие в определённое время раз в неделю
TYPE_TIME_DAY  			= 3   --событие раз в день
TYPE_TIME_HOUR 			= 4   --событие раз в час
EVENT_VECTOR_COUNT		= 32

MAX_LVL_ELF 			= 105
MAX_LVL_PET 			= 999
MAX_LVL 				= 999
LVLUP_COOLDOWN_TIME		= 15000

PACKET_CLEAN 			= 0 -- game__Packet type
PACKET_PUSH 			= 1 -- game__Packet type
PACKET_ADDR		 		= 2 -- game__Packet type
PACKET_SIZE 			= 3 -- game__Packet type

WORLD_LOCAL				= 0 -- не сохраняется в базу
WORLD_DB				= 1 -- сохраняется в базу для каждого данжа в свою
WORLD_GLOBAL			= 2 -- сохроняется в базу глобально для всех локаций

WORLD_MAX_POS			= 32
WORLD_MAX_VAR			= 3
	
TYPE_CHAR 				= 0 -- game__Patch & game__Get type
TYPE_SHORT 				= 1 -- game__Patch & game__Get type
TYPE_INT 				= 2 -- game__Patch & game__Get type
TYPE_INT64 				= 3 -- game__Patch & game__Get type
TYPE_FLOAT 				= 4 -- game__Patch & game__Get type
TYPE_DOUBLE 			= 5 -- game__Patch & game__Get type
	
CHAT_SINGLE				= 0 -- game__ChatMsg type
CHAT_INSTANCE			= 1 -- game__ChatMsg type
CHAT_WORLD				= 2 -- game__ChatMsg type
CHAT_MAX				= 3 -- game__ChatMsg type
	
NAME_ROLE				= 0 -- game__GetName type
NAME_ITEM				= 1 -- game__GetName type
	
NPC_TID_BY_ID			= 0 -- game__GetObjectVar type
NPC_ID_BY_TID			= 1 -- game__GetObjectVar type
NPC_COORDS_BY_TID		= 2 -- game__GetObjectVar type
MINE_GET_TID_BY_ID		= 3 -- game__GetObjectVar type
	
ITEM_CHANGE_PROCTYPE	= 0 -- game__PlayerUpdateItemsProctype type
ITEM_ADD_PROCTYPE		= 1 -- game__PlayerUpdateItemsProctype type
ITEM_CHANGE_PROCTYPE_ALL= 2 -- game__PlayerUpdateItemsProctype type
ITEM_ADD_PROCTYPE_ALL	= 3 -- game__PlayerUpdateItemsProctype type

PIMP_CLS                = 0 -- game__GetRoleVar type
PIMP_SEC_LEVEL          = 1 -- game__GetRoleVar type
PIMP_LEVEL              = 2 -- game__GetRoleVar type
PIMP_SP                 = 3 -- game__GetRoleVar type
PIMP_MONEY              = 4 -- game__GetRoleVar type
PIMP_USERID             = 5 -- game__GetRoleVar type
PIMP_REPUTATION         = 6 -- game__GetRoleVar type

CTRL_GM                 = 100   -- game__GetRoleVar type
CTRL_DEBUG              = 101   -- game__GetRoleVar type
CTRL_TARGET             = 102   -- game__GetRoleVar type

CMD_DELAY				= 5000  -- command handler delay
CMD_INSTANCE_REFRESH 	= 700   -- command handler cmd
CMD_MONEY 				= 701   -- command handler cmd
CMD_MONEYS 				= 702   -- command handler cmd
CMD_OFFLINE_ROLE 		= 721   -- command handler cmd
CMD_OFFLINE_CAT 		= 722   -- command handler cmd
CMD_SKILL_SET 			= 703   -- command handler cmd
CMD_SKILL_SENDER 		= 704   -- command handler cmd
CMD_SKILL_SCRIPT 		= 705   -- command handler cmd
CMD_PLAYER_DUMP 		= 706   -- command handler cmd
CMD_PLAYER_INFO 		= 707   -- command handler cmd
CMD_AUTOSWAP 			= 708   -- command handler cmd
CMD_ELEMENTSKILL 		= 709   -- command handler cmd
CMD_TEST 				= 710   -- command handler cmd
CMD_CLIENT_SKILL 		= 711   -- command handler cmd
CMD_FILTER_SKILL 		= 712   -- command handler cmd
CMD_SEND_HWID 			= 713   -- command handler cmd
CMD_DEBUG_PWD			= 777   -- command handler cmd
CMD_LUA_BEGIN			= 800   -- command handler cmd
CMD_LUA_END				= 900   -- command handler cmd

MASK_DELAY_LUA			= 5000    -- use iyem delay 
MASK_GOLDADD_ITEM 		= 400400  -- use iyem cmd 
MASK_AUTOSWAP_ITEM 		= 400401  -- use iyem cmd 
MASK_SKILLSENDER_ITEM 	= 400402  -- use iyem cmd 
MASK_LVLUP 				= 400403  -- use iyem cmd 
MASK_PETLVLUP 			= 400404  -- use iyem cmd 
MASK_ELFLVLUP 			= 400405  -- use iyem cmd 
MASK_VIPADD 			= 400406  -- use iyem cmd 
MASK_LUA 				= 400407  -- use iyem cmd 

CREATE_MOB				= 0       -- game__CreateObj type
CREATE_NPC				= 1       -- game__CreateObj type
CREATE_MINE				= 2       -- game__CreateObj type

--чатики
GN_CHAT_CHANNEL_LOCAL		= 0		--белый 
GN_CHAT_CHANNEL_FARCRY		= 1		--мир
GN_CHAT_CHANNEL_TEAM		= 2		--пати
GN_CHAT_CHANNEL_FACTION		= 3		--клан
GN_CHAT_CHANNEL_WHISPER		= 4		--пм
GN_CHAT_CHANNEL_DAMAGE		= 5		--урон
GN_CHAT_CHANNEL_FIGHT		= 6		--бой
GN_CHAT_CHANNEL_TRADE		= 7		--торг
GN_CHAT_CHANNEL_SYSTEM		= 8		--системный
GN_CHAT_CHANNEL_BROADCAST	= 9		--ГМ
GN_CHAT_CHANNEL_MISC		= 10	--синий
GN_CHAT_CHANNEL_INSTANCE	= 11	--Красный
GN_CHAT_CHANNEL_SUPERFARCRY = 12	--Горн
GN_CHAT_CHANNEL_BATTLE		= 13	--Тв
GN_CHAT_CHANNEL_COUNTRY		= 14	--БД
GN_CHAT_CHANNEL_GLOBAL		= 15	--Межсервер
GN_CHAT_CHANNEL_ALLIANCE	= 16	--Альянс
GN_CHAT_CHANNEL_CENTER		= 17	--В центре экрана

USER_CLASS_SWORDSMAN		= 0
USER_CLASS_MAGE				= 1
USER_CLASS_NEC				= 2
USER_CLASS_HAG				= 3
USER_CLASS_ORGE				= 4
USER_CLASS_ASN				= 5
USER_CLASS_ARCHER			= 6
USER_CLASS_ANGEL			= 7
USER_CLASS_BLADE			= 8
USER_CLASS_GENIE			= 9
USER_CLASS_SHADOW			= 10
USER_CLASS_FAIRY			= 11
USER_CLASS_SHOOTER			= 12
USER_CLASS_PALADIN			= 13
USER_CLASS_COUNT			= 14

--======================================================================================
--Используемые функции 
--======================================================================================

-- void game__Patch(size_t address, int type, double value);
-- double game__Get(size_t address, int type, size_t offset);
-- size_t game__Packet(size_t cmd, int type, double value );
-- void game__SaveFile(size_t Src, size_t size, const char* name);
-- size_t game__LoadFile(size_t Src, size_t size, const char* name);
-- void game__ChatMsg(int type , int roleid, int channel, const char * utf8_msg, int shift_pos);
-- const char * game__GetName(int type, int id);
-- int game__GetWorldTag();
-- int game__GetWorldIndex();
-- size_t game__InvPlayerGiveItem(int roleid, int inv, int id, int count, int time, int proctype);
-- size_t game__InvPlayerSpendItem(int roleid, int inv, int id, int count);
-- size_t game__InvGetCountPlayerItem(int roleid, int inv, int id);
-- size_t game__GetObjectVar(int type, int id, int tid);
-- size_t game__GetPQContrib(int task_id, int role_id);
-- void game__SetPQContrib(int task_id, int role_id, int value);
-- size_t game__GetStorage(int roleid, int pos);
-- void game__SetStorage(int roleid, int pos, int value);
-- void game__PlayerUpdateItemsProctype(int roleid, int inv, int id, int proctype, int type);
-- void game__DestroyProctypeItems(int roleid, int inv, int proctype);
-- void game__TestItemProctype(int roleid, int pos, int proctype);
-- void game__AddItemProctype(int roleid, int pos, int proctype);
-- void game__PlayerTeleport(int roleid, int tag, float x, float y, float z);
-- size_t game__PlayerCheckCoord(int roleid, int tag, float radius, float x, float y, float z);
-- void game__PlayerLearnSkill(int roleid, int skill_id, int skill_level);
-- double game__GetRoleVar(int type , int roleid);
-- void game__ActivateTriggerId(int trigger);
-- void game__DeactivateTriggerId(int trigger);
-- void game__CreateObj(int type ,int roleid, int id, int time, int count);
-- void game__PlayerObtainTitle(int roleid, int title, int time);
-- void game__PlayerDeleteTitle(int roleid, int title);
-- void game__PlayerAddGold(int roleid, int count);
-- void game__PlayerAddVip(int roleid, int count);
-- size_t game__PlayerLvlUp(int roleid, int max_level, int count);
-- size_t game__PetLvlUp(int roleid, int max_level, int count);
-- size_t game__ElfLvlUp(int roleid, int max_level, int count, int exp, int sp );
-- void game__Send(int roleid);
-- void game__SendBroadCast(int roleid);
-- void game__AddEventPool(int id,int type, int delay);
-- void game__CleanEventPool();
-- void game__PlayerDisconnect(int roleid);
-- void game__SetPlayerHwid(int roleid, int64_t hwid);
-- int64_t game__GetPlayerHwid(int roleid);
-- int game__Cooldown(int type, int roleid, int idx, time_t time);
-- int game__MassiveCooldown(int type, int roleid, size_t * table);
-- int game__InsRefresh(int roleid);
-- int game__GetInvPosItemTable(int roleid, int inv, int* table);
-- void game__PlayerGiveGold(int roleid, size_t money);
-- void game__PlayerSpendGold(int roleid, size_t money);
-- void game__PlayerGiveSilver(int roleid, size_t money);
-- void game__PlayerSpendSilver(int roleid, size_t money);
-- void game__LoadLuaStorage(int type, int key);
-- void game__SaveLuaStorage(int type, int key, size_t data, size_t size);
-- void game__LearnSkill(int roleid, int skill_id, int skill_level);
-- void game__RemoveSkill(int roleid, int skill_id);
-- double game__GetWorldVar(int var_id, int type, size_t pos);
-- void game__SetWorldVar(int var_id, int type, size_t pos, double value);

--======================================================================================
--Глобальные переменные
--======================================================================================

--Режим отладки
lua_idx 						= 6660 -- уникальный индекс
lua_log							= 0 -- включить режим логов (Включайте если что-то падает!)
lua_debug						= 0 -- включить режим отладки (Если сервер не является тестовым выключайте!)
DebugPasswd 					= 3444 -- дебаг пароль (макс 9 символов) d 777
max_load_state 					= 749 -- 449 -- максимальный лимит нагрузки для одного игрока (защита от флуда)
need_load_state					= 20 -- 10 -- на сколько уменьшать мараметр нагрузки каждую секунду

--различные переменные-- 
SummonPet136 					= 0 -- требовать убрать питомца перед перепризывом нового
CountryBattleIsTeam 			= 0 -- разрешить вход на бд в пати
MaxVigour 						= 0 -- максимальный боевой дух
shutdown_ap 					= 100 -- сколько чи давать за медитацию
IdDistanceShop 					= 80080 -- ид дистанционного шопа
ChangeElfStatusTime 			= 86400 -- время привязки джина
townscroll_ccoldown				= 400 -- время отката руны переноса
enable_safelock					= 0 -- выключить замок
vip_enable						= 1 -- выключить вип систему
min_refine_level				= 1 -- минимальный уровень заточки (чтобы сделать точку в 1 клик сделайте 12)
max_refine_level				= 9 -- максимальный уровень заточки
battle_bid_item					= 21652 -- итем для ставок
enable_patch_equip				= 0 -- заточка и инкрустация через перенос итемов в инвентаре (1 включено, 0 выключено)
atk_def_enable					= 0 -- бафы на атаку и защиту во время территориальных воин (1 включено, 0 выключено)
--скиллы--			
asm_skill_mod136				= 0 -- использовать мод скиллов для 136
asm_skill_main136				= 0 -- использовать увеличенные райские пассивки для 136
asm_skill_soul					= 72000 -- максимальная сила духа
asm_shaman_soul					= 56000 -- максимальный дух шаманов
asm_skill_free_sp 				= 0 --не требовать дух
asm_skill_free_money 			= 0 --не требовать монеты
asm_skill_free_item 			= 0 --не требовать итемы
--пве/пвп режимы			
pvp_cooldown_time				= 3600*1 --3600*10 -- откат выхода из пк режима
pvp_protect_level_min			= 29 -- уровень новичка(синий ник)
pvp_protect_level_max			= 69 -- уровень новичка(пве кнопка)
--меридианы
meredian_max					= 0
meredian_inc					= 0

--календаоь
LATE_DAY_SIGNIN_ITEM			= 39960
SIGNIN_PERFECT_AWARD			= 39959
SIGNIN_YEAR_AWARD				= 39958
SIGNIN_MONTH_AWARD				= 39957
MAX_LATE_SIGNIN_TIMES			= 4

--карты
GENERALCARD_RANK_S				= 4 -- максимальный ранг поглащаемой карты

--квесты
TASK_DEFAULT_MAX_COUT 			= 40 -- максимальное количество квестов по умолчанию
TASK_MAX_COUT					= 50 -- максимальное количество квестов после расширения
TASK_HIDDEN_COUNT           	= 50 -- максимальное количество скрытых квестов
TASK_TITLE_TASK_COUNT			= 30 -- максимальное количество титульных квестов

--массивы
HWID_TAGS_LIMIT				    = 0 -- adress ; 
INCAST_SKILL					= 0 -- adress ;
INCAST_CLS					    = 0 -- adress ;
INCAST_FIRSTRUN				    = 0 -- adress ;
INCAST_COOLDOWN				    = 0 -- adress ;
SKILLSENDER_COOLDOWN			= 0 -- adress ;
SKILLSENDER_INVALID_NPC_BUFF	= 0 -- adress ;
SWAP_EQUIP_COMBAT				= 0 -- adress ;
SWAP_COOLDOWN					= 0 -- adress ;
AUTOSWAP_COOLDOWN				= 0 -- adress ;
BALANCE_DAMAGE				    = 0 -- adress ;
ATTACK_SPEED					= 0 -- adress ;
BUG_SKILL						= 0 -- adress ;
BUG_SKILL_CLS					= 0 -- adress ;
ITEM_POPPET_DUMMY_TABLE		    = 0 -- adress ;
ITEM_WORLD_SPEAKER_TABLE		= 0 -- adress ;
ITEM_SUPERWORLD_SPEAKER_TABLE	= 0 -- adress ;
ITEM_GATCHER_SPEED			    = 0 -- adress ;
ITEM_MASS_PICKUP				= 0 -- adress ;
ITEM_PET_RENAME				    = 0 -- adress ;
ITEM_REFINE_FULL				= 0 -- adress ;
OTHER_MINE_SPEED				= 0 -- adress ;
ITEM_SCROLL_TOWN				= 0 -- adress ;
ITEM_OFFLINE_MARKET			    = 0 -- adress ;
ITEM_REFINE					    = 0 -- adress ;
ITEM_REVIVE_SCROLL			    = 0 -- adress ;
ITEM_ALLIANCE_SPEAKER_TABLE	    = 0 -- adress ;
DISTANCE_SERVICE_TAG			= 0 -- adress ;
MASS_PICKUP_DISTABLE_TAG		= 0 -- adress ;
DISTANCE_SERVICE_TYPE			= 0 -- adress ;
GOOD_ITEMS_TABLE				= 0 -- adress ;
GOOD_AMULETS_TAG				= 0 -- adress ;
ELF_DISTABLE_LOCATIONS		    = 0 -- adress ;
PATTY_DISTABLE_TAGS			    = 0 -- adress ;
SHIELD_SKILL_TABLE			    = 0 -- adress ;
ITEM_GLOBAL_SPEAKER_TABLE		= 0 -- adress ;
VIP_SCORE_LEVEL_TABLE			= 0 -- adress ;
ALLIANCE_CONGREGATE_TAG			= 0 -- adress ;
RATE_LIST_TABLE					= 0 -- adress ;
REFINE_TABLE					= 0 -- adress ;
REFINE_FACTOR					= 0 -- adress ;
ITEM_NEW_ENGRAVE				= 0 -- adress ;
ITEM_BIBLE_REFINE				= 0 -- adress ;

--======================================================================================
--Математические функции
--======================================================================================

-- Получить время суток
function get_time_dey()
	return int(os.time() / 86400)
end

function strtoint(inputstr)
        if inputstr == nil then
			return 0
        end
		return tonumber(inputstr)
end

-- Конвертировать текст в хекс
function string.fromhex(str)
    return (str:gsub('..', function (cc)
        return string.char(tonumber(cc, 16))
    end))
end

-- конвертировать хекс в текст
function string.tohex(str)
    return (str:gsub('.', function (c)
        return string.format('%02X', string.byte(c))
    end))
end

-- Конвертировать число в int
function int(numb)
	return math.floor(numb)
end

-- получить дату и время
function mydata()
	return os.date("%d/%m/%Y %H:%M:%S")
end

-- Запись в лог файл
function mylogfunc(text)
	local outstr = mydata().." ["..game__GetWorldTag().."] "..text.."\n"
	local file = io.open("lualog.txt", "a")
	file:write(outstr)
	file:close()
	io.write(outstr)
end

-- фан чатик
function funnytext (message)
str = message
as = {'а', 'о', 'е', 'ы', 'ё', 'э'}
whereat = {'у', 'а', 'ы', 'а', 'о', 'е'}
if #as == #whereat then
    for i=1,#as do
        str = str:gsub(as[i], whereat[i])
    end
end
	return str

end

-- разбить чатик на слова
function mysplit(inputstr, sep)
        if sep == nil then
                sep = "%s"
        end
        local t={} ; i=1
        for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
                t[i] = str
                i = i + 1
        end
        return t
end

-- проверить таблицу на верный итем
function check_true_item(item , items)

	if items[item] == nil then
		return 0
	end
	return items[item]

end
--======================================================================================
--Игровые функции
--======================================================================================

--дать pq очки
function game__PlayerAddCountrib(quest, roleid, value)

	local countrib = game__GetPQContrib(quest, roleid) -- получить очки
	countrib = countrib + value
	game__SetPQContrib(quest, roleid, countrib) -- вставить очки
end

--======================================================================================

--отнять pq очки
function game__PlayerSpendCountrib(quest, roleid, value)

	local countrib = game__GetPQContrib(quest, roleid) -- получить очки
	countrib = countrib - value
	game__SetPQContrib(quest, roleid, countrib) -- вставить очки
end

--======================================================================================
--=====================================[PATCH FUNC]=====================================
--======================================================================================

--Патчинг таблицы из 1 инта
function IntTable(pushd, value)

	game__Patch(pushd,TYPE_INT,value)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 2х интов
function IntIntTable(pushd, value1, value2)

	game__Patch(pushd,TYPE_INT,value1)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_INT,value2)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 3х интов
function IntIntIntTable(pushd, value1, value2, value3)

	game__Patch(pushd,TYPE_INT,value1)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_INT,value2)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_INT,value3)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 1 флоата
function FloatTable(pushd, value)

	game__Patch(pushd,TYPE_FLOAT,value)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 2х флоатов
function FloatFloatTable(pushd, value1, value2)

	game__Patch(pushd,TYPE_FLOAT,value1)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_FLOAT,value2)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 3х флоатов
function FloatFloatFloatTable(pushd, value1, value2, value3)

	game__Patch(pushd,TYPE_FLOAT,value1)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_FLOAT,value2)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_FLOAT,value3)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 4х флоатов
function FloatFloatFloatFloatTable(pushd, value1, value2, value3, value4)

	game__Patch(pushd,TYPE_FLOAT,value1)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_FLOAT,value2)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_FLOAT,value3)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_FLOAT,value4)
	pushd = pushd + 4
	return pushd
end

-- XID++
function HashIDX()
	lua_idx = lua_idx+1
end

--======================================================================================
--Coordinate Func
--======================================================================================
--Получить серверные координаты 
function game__GetCoordData(addres)

	return game__Get(addres, TYPE_FLOAT, 0), game__Get(addres, TYPE_FLOAT, 4), game__Get(addres, TYPE_FLOAT, 8)
end
--Получить клиентские координаты
function game__GetCoordDataClient(addres)

	return (game__Get(addres, TYPE_FLOAT, 0) +4000)/10, game__Get(addres, TYPE_FLOAT, 4) /10, (game__Get(addres, TYPE_FLOAT, 8) +5500)/10
end

--======================================================================================
--BALANCE EDITOR DATA
--======================================================================================

--Редактор баланса между классами 136
function LUA_BALANCE_EDITOR136()

	local pushd = 0 -- float BALANCE_DAMAGE[4*2*14];
	--[CLS::0]--------------[Дамаг вара]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_SWORDSMAN   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	--[CLS::1]--------------[Дамаг мага]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_MAGE   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	--[CLS::3]--------------[Дамаг друида]---------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_HAG   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	--[CLS::4]--------------[Дамаг оборотня]-------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_ORGE   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	--[CLS::6]--------------[Дамаг лучника]--------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_ARCHER   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	--[CLS::7]--------------[Дамаг жреца]----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_ANGEL   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню
	pushd = pushd + 8
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	-----------------------------------------------------------
	
	if lua_debug == 1 then mylogfunc("Patching Balance 136 OK") end
	return 0
end

--======================================================================================

--Редактор баланса между классами
function LUA_BALANCE_EDITOR()

	--[CLS::0]--------------[Дамаг вара]------------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_SWORDSMAN   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::1]--------------[Дамаг мага]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_MAGE   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::2]--------------[Дамаг шамана]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_NEC   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::3]--------------[Дамаг друида]---------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_HAG   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::4]--------------[Дамаг оборотня]-------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_ORGE   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::5]--------------[Дамаг убийцы]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_ASN   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::6]--------------[Дамаг лучника]--------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_ARCHER   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::7]--------------[Дамаг жреца]----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_ANGEL   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::8]--------------[Дамаг стража]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_BLADE   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::9]--------------[Дамаг мистика]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_GENIE   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::10]--------------[Дамаг призрака]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_SHADOW   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу	
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::11]--------------[Дамаг жнеца]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_FAIRY   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу	
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::11]--------------[Дамаг стрелка]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_SHOOTER   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу	
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку
	--[CLS::11]--------------[Дамаг стрелка]-----------------------
	pushd = BALANCE_DAMAGE + 8 * USER_CLASS_COUNT * USER_CLASS_PALADIN   
	-----------------------------[физ, маг]---------------------
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу	
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По паладину
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стрелку	

	if lua_debug == 1 then mylogfunc("Patching Balance OK") end
	return 0
end

--======================================================================================
--Incast editor 
--======================================================================================

--Редактор инкаста
function LUA_INCAST_EDITOR()
	
	local pushd = 0

	--Редактор инкаста и перекаста для каждого класса
	pushd = INCAST_FIRSTRUN --Incast::FirstRun(инкаст, перекаст)
	pushd = IntIntTable(pushd,99,90) --CLS 0 ; вар
	pushd = IntIntTable(pushd,99,90) --CLS 1 ; маг
	pushd = IntIntTable(pushd,99,90) --CLS 2 ; шаман
	pushd = IntIntTable(pushd,99,90) --CLS 3 ; друид
	pushd = IntIntTable(pushd,99,90) --CLS 4 ; обор
	pushd = IntIntTable(pushd,99,90) --CLS 5 ; син
	pushd = IntIntTable(pushd,99,90) --CLS 6 ; лучник
	pushd = IntIntTable(pushd,99,90) --CLS 7 ; жрец
	pushd = IntIntTable(pushd,99,90) --CLS 8 ; страж
	pushd = IntIntTable(pushd,99,90) --CLS 9 ; мистик

	--Редактор всех скиллов глобально для каждого класса при 99 пения
	pushd = INCAST_CLS --Incast::Editor(Ускорение пения от 0 до 32(0 - стандарт, 32+ инкаст как на 136))
	pushd = IntTable(pushd,32) --CLS 0 ; вар
	pushd = IntTable(pushd,32) --CLS 1 ; маг
	pushd = IntTable(pushd,0 ) --CLS 2 ; шаман
	pushd = IntTable(pushd,32) --CLS 3 ; друид
	pushd = IntTable(pushd,32) --CLS 4 ; обор
	pushd = IntTable(pushd,0 ) --CLS 5 ; син
	pushd = IntTable(pushd,32) --CLS 6 ; лучник
	pushd = IntTable(pushd,32) --CLS 7 ; жрец
	pushd = IntTable(pushd,0 ) --CLS 8 ; страж
	pushd = IntTable(pushd,0 ) --CLS 9 ; мистик

	--Редактор инкаста отдельных скиллов при -99 пения
	pushd = INCAST_SKILL --Skill::IncastTable(Ид скилла, Ускорение пения от 0 до 32(0 - стандарт, 32+ инкаст как на 136))
	pushd = IntIntTable(pushd,87 ,32) --Маг: Огненный шторм
	pushd = IntIntTable(pushd,454,32) --Маг: Огненный шторм светлый
	pushd = IntIntTable(pushd,455,32) --Маг: Огненный шторм темный
	pushd = IntIntTable(pushd,93 ,32) --Маг: Ярость водного дракона
	pushd = IntIntTable(pushd,470,32) --Маг: Ярость водного дракона светлый
	pushd = IntIntTable(pushd,471,32) --Маг: Ярость водного дракона темный
	pushd = IntIntTable(pushd,99 ,32) --Маг: Сила гор
	pushd = IntIntTable(pushd,484,32) --Маг:Сила гор светлый
	pushd = IntIntTable(pushd,485,32) --Маг: Сила гор темный
	pushd = IntIntTable(pushd,130,32) --Жрец: Ярость небес
	pushd = IntIntTable(pushd,585,32) --Жрец: Ярость небес светлый
	pushd = IntIntTable(pushd,587,32) --Жрец: Ярость небес темный
	pushd = IntIntTable(pushd,305,32) --Дру: Нашествие саранчи
	pushd = IntIntTable(pushd,646,32) --Дру: Нашествие саранчи светлый
	pushd = IntIntTable(pushd,647,32) --Дру: Нашествие саранчи темный	
	pushd = IntIntTable(pushd,253,32) --Лук: Когти небес
	pushd = IntIntTable(pushd,610,32) --Лук: Когти небес светлый	
	pushd = IntIntTable(pushd,611,32) --Лук: Когти небес темный

	--Защита от кликеров
	pushd = INCAST_COOLDOWN --Skill::LockTimer
	pushd = IntIntTable(pushd, lua_idx, 400) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 300) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 200) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 100) HashIDX()

	if lua_debug == 1 then mylogfunc("Patching incast OK") end
	return 0
end

--Редактор защиты от скиллсендеров
function LUA_SKILL_SENDER_EDITOR()
	
	local pushd = 0

	pushd = SKILLSENDER_COOLDOWN --защита флуда на серверный скилл сендер
	pushd = IntIntTable(pushd, lua_idx, 4000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 3000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 2000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 1000) HashIDX()	
	
	if lua_debug == 1 then mylogfunc("Patching skill_sender_asm OK") end
	return 0
end

--список скиллов которые запрещено применять к нипам(нахилы, бафы итд)
function LUA_SKILL_BUFF_EDITOR()
	
	local pushd = 0
	pushd = SKILLSENDER_INVALID_NPC_BUFF
	
	pushd = IntTable(pushd,90 )
	pushd = IntTable(pushd,91 )
	pushd = IntTable(pushd,113)
	pushd = IntTable(pushd,114)
	pushd = IntTable(pushd,115)
	pushd = IntTable(pushd,116)
	pushd = IntTable(pushd,120)
	pushd = IntTable(pushd,189)
	pushd = IntTable(pushd,191)
	pushd = IntTable(pushd,192)
	pushd = IntTable(pushd,193)
	pushd = IntTable(pushd,306)
	pushd = IntTable(pushd,462)
	pushd = IntTable(pushd,463)
	pushd = IntTable(pushd,466)
	pushd = IntTable(pushd,467)
	pushd = IntTable(pushd,542)
	pushd = IntTable(pushd,543)
	pushd = IntTable(pushd,544)
	pushd = IntTable(pushd,545)
	pushd = IntTable(pushd,546)
	pushd = IntTable(pushd,547)
	pushd = IntTable(pushd,550)
	pushd = IntTable(pushd,551)
	pushd = IntTable(pushd,552)
	pushd = IntTable(pushd,553)
	pushd = IntTable(pushd,554)
	pushd = IntTable(pushd,555)
	pushd = IntTable(pushd,564)
	pushd = IntTable(pushd,565)
	pushd = IntTable(pushd,566)
	pushd = IntTable(pushd,567)
	pushd = IntTable(pushd,568)
	pushd = IntTable(pushd,569)
	pushd = IntTable(pushd,570)
	pushd = IntTable(pushd,571)
	pushd = IntTable(pushd,648)
	pushd = IntTable(pushd,649)
	
	pushd = IntTable(pushd,0  ) --последний элемент массива
	
	if lua_debug == 1 then mylogfunc("Patching skill_buff_asm OK") end
	return 0
end

--======================================================================================
--Attack Speed Editor
--======================================================================================

--Редактор скорости автоатаки с различной культивацией и разными типами оружия
function LUA_ATTACK_SPEED_EDITOR()

	local pushd = 0

	-- Скорость атаки для культивации 0 - 8 пример: (4 = 5.00 ; 5 = 4.00 ; 6 = 3.33) и далее по аналогии
	pushd = ATTACK_SPEED + 80*0 --AttackSpeed::Editor(Тип оружия, скорость атаки)
	pushd = IntIntTable(pushd,1,    4) -- мечи 
	pushd = IntIntTable(pushd,5,    4) -- копья 
	pushd = IntIntTable(pushd,9,    4) -- топоры 
	pushd = IntIntTable(pushd,13,   4) -- дальнобойное 
	pushd = IntIntTable(pushd,182,  4) -- кастеты 
	pushd = IntIntTable(pushd,291,  4) -- бичи 
	pushd = IntIntTable(pushd,292,  4) -- магическое оружие 
	pushd = IntIntTable(pushd,23749,4) -- кинжалы 
	pushd = IntIntTable(pushd,25333,4) -- сферы 
	pushd = IntIntTable(pushd,44878,4) -- Сабля
	pushd = IntIntTable(pushd,44879,4) -- Коса
	pushd = IntIntTable(pushd,59830,4) -- Щит
	pushd = IntIntTable(pushd,59831,4) -- Пушка

	-- Скорость атаки для культивации 20 - 22 пример: (4 = 5.00 ; 5 = 4.00 ; 6 = 3.33) и далее по аналогии
	pushd = ATTACK_SPEED + 80*1 --AttackSpeed::Editor(Тип оружия, скорость атаки)
	pushd = IntIntTable(pushd,1,    4) -- мечи 
	pushd = IntIntTable(pushd,5,    4) -- копья 
	pushd = IntIntTable(pushd,9,    4) -- топоры 
	pushd = IntIntTable(pushd,13,   4) -- дальнобойное 
	pushd = IntIntTable(pushd,182,  4) -- кастеты 
	pushd = IntIntTable(pushd,291,  4) -- бичи 
	pushd = IntIntTable(pushd,292,  4) -- магическое оружие 
	pushd = IntIntTable(pushd,23749,4) -- кинжалы 
	pushd = IntIntTable(pushd,25333,4) -- сферы 
	pushd = IntIntTable(pushd,44878,4) -- Сабля
	pushd = IntIntTable(pushd,44879,4) -- Коса
	pushd = IntIntTable(pushd,59830,4) -- Щит
	pushd = IntIntTable(pushd,59831,4) -- Пушка

	-- Скороcть атаки для культивации 30 - 32 пример: (4 = 5.00 ; 5 = 4.00 ; 6 = 3.33) и далее по аналогии
	pushd = ATTACK_SPEED + 80*2 --AttackSpeed::Editor(Тип оружия, скорость атаки)
	pushd = IntIntTable(pushd,1,    4) -- мечи 
	pushd = IntIntTable(pushd,5,    4) -- копья 
	pushd = IntIntTable(pushd,9,    4) -- топоры 
	pushd = IntIntTable(pushd,13,   4) -- дальнобойное 
	pushd = IntIntTable(pushd,182,  4) -- кастеты 
	pushd = IntIntTable(pushd,291,  4) -- бичи 
	pushd = IntIntTable(pushd,292,  4) -- магическое оружие 
	pushd = IntIntTable(pushd,23749,4) -- кинжалы 
	pushd = IntIntTable(pushd,25333,4) -- сферы 
	pushd = IntIntTable(pushd,44878,4) -- Сабля
	pushd = IntIntTable(pushd,44879,4) -- Коса
	pushd = IntIntTable(pushd,59830,4) -- Щит
	pushd = IntIntTable(pushd,59831,4) -- Пушка

	if lua_debug == 1 then mylogfunc("Patching attack_speed OK") end
	return 0
end

--======================================================================================
--Bug Skill Editor
--======================================================================================

--Редактор баг скиллов 
function LUA_BUG_SKILL_EDITOR()

	local pushd = 0

	--Редактор всех скиллов глобально для каждого класса
	pushd = BUG_SKILL_CLS --BugSkill::Editor(0 выключить - 1 включить)
	pushd = IntTable(pushd,1) --CLS == 0 ; вар
	pushd = IntTable(pushd,1) --CLS == 1 ; маг
	pushd = IntTable(pushd,0) --CLS == 2 ; шаман
	pushd = IntTable(pushd,1) --CLS == 3 ; друид
	pushd = IntTable(pushd,1) --CLS == 4 ; обор
	pushd = IntTable(pushd,0) --CLS == 5 ; син
	pushd = IntTable(pushd,1) --CLS == 6 ; лучник
	pushd = IntTable(pushd,1) --CLS == 7 ; жрец
	pushd = IntTable(pushd,0) --CLS == 8 ; страж
	pushd = IntTable(pushd,0) --CLS == 9 ; мистик

	--Редактор отдельных скиллов
	pushd = BUG_SKILL --BugSkill::Table(Ид скилла, 0 выключить - 1 включить)
	pushd = IntIntTable(pushd,58  ,0) -- Вар: парящий дракон
	pushd = IntIntTable(pushd,59  ,0) -- Вар: прыжок тигра
	pushd = IntIntTable(pushd,100 ,0) -- Маг: сдвиг земли
	pushd = IntIntTable(pushd,478 ,0) -- Маг: сдвиг земли светлый
	pushd = IntIntTable(pushd,479 ,0) -- Маг: сдвиг земли темный

	if lua_debug == 1 then mylogfunc("Patching bug_skill OK") end
	return 0
end

--======================================================================================
--SWAP ITEM & COOLDOWN
--======================================================================================

function LUA_SWAP_ITEM_EDITOR()

	local pushd = 0
	
	-- Список позиций (из PWA) снаряжений которые нельзя использовать в бою
	-- 0 - можно, 1 - нельзя(джинн), 2 нельзя вообще(хирки)
	pushd = SWAP_EQUIP_COMBAT
	pushd = IntTable(pushd,0) -- оружие
	pushd = IntTable(pushd,0) -- шлем
	pushd = IntTable(pushd,0) -- ожирелье
	pushd = IntTable(pushd,0) -- накидка
	pushd = IntTable(pushd,0) -- броня
	pushd = IntTable(pushd,0) -- пояс
	pushd = IntTable(pushd,0) -- штаны
	pushd = IntTable(pushd,0) -- сапоги
	pushd = IntTable(pushd,0) -- наручи
	pushd = IntTable(pushd,0) -- кольцо 1
	pushd = IntTable(pushd,0) -- кольцо 2
	pushd = IntTable(pushd,0) -- стрелы
	pushd = IntTable(pushd,0) -- полёт
	pushd = IntTable(pushd,0) -- стиль куртка
	pushd = IntTable(pushd,0) -- стиль штаны
	pushd = IntTable(pushd,0) -- стиль сапоги
	pushd = IntTable(pushd,0) -- стиль перчатки
	pushd = IntTable(pushd,0) -- соски на атаку
	pushd = IntTable(pushd,0) -- трактат
	pushd = IntTable(pushd,0) -- смайлы
	pushd = IntTable(pushd,2) -- хирка на жс
	pushd = IntTable(pushd,2) -- хирка на ману
	pushd = IntTable(pushd,0) -- цитатник
	pushd = IntTable(pushd,1) -- джинн
	pushd = IntTable(pushd,0) -- торговая лавка
	pushd = IntTable(pushd,0) -- стиль шапка
	pushd = IntTable(pushd,0) -- грамата альянса
	pushd = IntTable(pushd,0) -- печать воителя 1
	pushd = IntTable(pushd,0) -- печать воителя 2
	pushd = IntTable(pushd,0) -- стиль пуха
	pushd = IntTable(pushd,0) -- ???
	pushd = IntTable(pushd,0) -- ???
	pushd = IntTable(pushd,0) -- ???	

	--Таблица задержки от флуда на свап (защита от стороннего свапа)
	pushd = SWAP_COOLDOWN
	pushd = IntIntTable(pushd, lua_idx, 800) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 600) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 400) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 200) HashIDX() 

	--Таблица задержки от флуда на автосвап
	pushd = AUTOSWAP_COOLDOWN
	pushd = IntIntTable(pushd, lua_idx, 4000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 3000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 2000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 1000) HashIDX()

	if lua_debug == 1 then mylogfunc("swap_editor OK") end
	return 0
end

--======================================================================================
--TABLES & TRUE ITEMS
--======================================================================================

--редактор кукол замены
function LUA_ITEM_POPPET_DUMMY_TABLE()

	local pushd = 0
	pushd = ITEM_POPPET_DUMMY_TABLE

	pushd = IntTable(pushd,86403)
	pushd = IntTable(pushd,31878)
	pushd = IntTable(pushd,12361)
	pushd = IntTable(pushd,36309)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_POPPET_DUMMY_TABLE OK!") end
	return 1
end

--редактор рупоров
function LUA_ITEM_WORLD_SPEAKER_TABLE()

	local pushd = 0
	pushd = ITEM_WORLD_SPEAKER_TABLE

	pushd = IntTable(pushd,86401)
	pushd = IntTable(pushd,12979)
	pushd = IntTable(pushd,36092)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_WORLD_SPEAKER_TABLE OK!") end
	return 1
end

--редактор горнов
function LUA_ITEM_SUPERWORLD_SPEAKER_TABLE()

	local pushd = 0
	pushd = ITEM_SUPERWORLD_SPEAKER_TABLE

	pushd = IntTable(pushd,86402)
	pushd = IntTable(pushd,27728)
	pushd = IntTable(pushd,27729)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_SUPERWORLD_SPEAKER_TABLE OK!") end
	return 1
end

--редактор ускорителей выкапывания шахт
function LUA_ITEM_GATCHER_SPEED()

	local pushd = 0
	pushd = ITEM_GATCHER_SPEED

	pushd = IntTable(pushd,86404)
	pushd = IntTable(pushd,86405)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_GATCHER_SPEED OK!") end
	return 1
end

--редактор итемов для масс подбора лута
function LUA_ITEM_MASS_PICKUP()

	local pushd = 0
	pushd = ITEM_MASS_PICKUP

	pushd = IntTable(pushd,86406)
	pushd = IntTable(pushd,86407)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_MASS_PICKUP OK!") end
	return 1
end

--редактор итемов для смены имени пета
function LUA_ITEM_PET_RENAME()

	local pushd = 0
	pushd = ITEM_PET_RENAME

	pushd = IntTable(pushd,12403)
	pushd = IntTable(pushd,86408)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_PET_RENAME OK!") end
	return 1
end

--редактор мгновенных заточек +12 в 1 клик
function LUA_ITEM_REFINE_FULL()

	local pushd = 0
	pushd = ITEM_REFINE_FULL

	pushd = IntTable(pushd,86409)
	pushd = IntTable(pushd,86410)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_REFINE_FULL OK!") end
	return 1
end

--редактор рун которым разрешено телепортироваться между локациями
function LUA_ITEM_SCROLL_TOWN()

	local pushd = 0
	pushd = ITEM_SCROLL_TOWN

	pushd = IntTable(pushd,59410)
	pushd = IntTable(pushd,51130)
	pushd = IntTable(pushd,51252)
	pushd = IntTable(pushd,59411)
	pushd = IntTable(pushd,59412)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_SCROLL_TOWN OK!") end
	return 1
end

--редактор бесконечных итемов
function LUA_GOOD_ITEMS_TABLE()

	local pushd = 0
	pushd = GOOD_ITEMS_TABLE

	pushd = IntTable(pushd,59410) --руна переноса
	pushd = IntTable(pushd,59411) --руна переноса
	pushd = IntTable(pushd,59412) --руна переноса
	pushd = IntTable(pushd,86401) --рупор
	pushd = IntTable(pushd,86402) --горн
	pushd = IntTable(pushd,86403) --кукла
	pushd = IntTable(pushd,86411) --бесконечная хирка хп
	pushd = IntTable(pushd,86412) --бесконечная хирка мп
	
	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_GOOD_ITEMS_TABLE OK!") end
	return 1
end

--Локации в которых хирки бесконечные
function LUA_GOOD_AMULETS_TAG()

	local pushd = 0
	pushd = GOOD_AMULETS_TAG

	pushd = IntTable(pushd,143)	--Основная локация Битвы династий
	pushd = IntTable(pushd,144)	--Поле боя Битвы династий Захват флага
	pushd = IntTable(pushd,145)	--Поле боя Битвы династий Бой за кристаллы
	pushd = IntTable(pushd,146)	--Поле боя Битвы династий Битва на мосту
	pushd = IntTable(pushd,147)	--Лока для ивента Битва катапульт

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_GOOD_AMULETS_TAG OK!") end
	return 1
end

--Локации в которых джинн выключен
function LUA_ELF_DISTABLE_LOCATIONS()

	local pushd = 0
	pushd = ELF_DISTABLE_LOCATIONS

	pushd = IntTable(pushd,120)	--Остров змей -- Скачки
	pushd = IntTable(pushd,201)	--ГМ Арена -- Асуры
	pushd = IntTable(pushd,147)	--Лока для ивента Битва катапульт
	
	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ELF_DISTABLE_LOCATIONS OK!") end
	return 1
end

--Локации в которых выключено пати 
function LUA_PATTY_DISTABLE_TAGS()

	local pushd = 0
	pushd = PATTY_DISTABLE_TAGS

	pushd = IntTable(pushd,201)	--ГМ Арена -- Асуры
	
	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_PATTY_DISTABLE_TAGS OK!") end
	return 1
end

--Локации в которых выключен масс сбор лута
function LUA_MASS_PICKUP_DISTABLE_TAG()

	local pushd = 0
	pushd = MASS_PICKUP_DISTABLE_TAG

	pushd = IntTable(pushd,201)	--ГМ Арена -- Асуры
	
	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_MASS_PICKUP_DISTABLE_TAG OK!") end
	return 1
end

--локации в которых работают дистанционные сервисы
function LUA_DISTANCE_SERVICE_TAG()

	local pushd = 0
	pushd = DISTANCE_SERVICE_TAG

	pushd = IntTable(pushd,1  )	--[PvE] Мир
	pushd = IntTable(pushd,121)	--[PvE] Рай
	pushd = IntTable(pushd,122)	--[PvE] Ад
	pushd = IntTable(pushd,133)	--[PvE] Прошлое
	pushd = IntTable(pushd,135)	--[PvE] База гильдии
	pushd = IntTable(pushd,137)	--[PvE] Морай
	pushd = IntTable(pushd,161)	--[???] переправа душ 152+
	pushd = IntTable(pushd,162)	--[???] переправа душ 151+
	pushd = IntTable(pushd,168)	--[PvP] Таинственный мир
	pushd = IntTable(pushd,198)	--[PvE] Персиковая обитель
	pushd = IntTable(pushd,226)	--[PvE] Нирвана
	
	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_DISTANCE_SERVICE_TAG OK!") end
	return 1
end

--Редактор дистанционных сервисов
function LUA_DISTANCE_SERVICE_TYPE()

	local pushd = 0
	pushd = DISTANCE_SERVICE_TYPE
	
	pushd = IntTable(pushd,1 ) --покупка итемов(другой обработчик)
	pushd = IntTable(pushd,2 ) --продажа итемов	
	pushd = IntTable(pushd,3 ) --починка итемов
	pushd = IntTable(pushd,9 ) --изучение скиллов
	pushd = IntTable(pushd,35) --заточка снаряжения
	pushd = IntTable(pushd,10) --вплавка камней
	pushd = IntTable(pushd,11) --очистка снаряжения
	pushd = IntTable(pushd,47) --создание ячеек
	pushd = IntTable(pushd,14) --пароль от банка
	pushd = IntTable(pushd,15) --банк
	pushd = IntTable(pushd,25) --почта
	pushd = IntTable(pushd,28) --инкубация петов
	pushd = IntTable(pushd,29) --восстановление яиц петов
	pushd = IntTable(pushd,36) --сменить имя питомца
	--pushd = IntTable(pushd,69) --дистанционная гравировка

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_DISTANCE_SERVICE_TYPE OK!") end
	return 1
end

--редактор требуемых очков для vip уровней
function LUA_VIP_SCORE_LEVEL_TABLE()

	local pushd = 0
	pushd = VIP_SCORE_LEVEL_TABLE

	pushd = IntTable(pushd,0)
	pushd = IntTable(pushd,15)
	pushd = IntTable(pushd,75)
	pushd = IntTable(pushd,150)
	pushd = IntTable(pushd,375)
	pushd = IntTable(pushd,900)
	pushd = IntTable(pushd,2250)
	pushd = IntTable(pushd,999999999)
	pushd = IntTable(pushd,999999999)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_VIP_SCORE_LEVEL_TABLE OK!") end
	return 1
end

--редактор дополнительных идов шахт которые копаются быстрее итемами ускорялками 
function LUA_OTHER_MINE_SPEED()

	local pushd = 0
	pushd = OTHER_MINE_SPEED

	pushd = IntTable(pushd,86440)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_OTHER_MINE_SPEED OK!") end
	return 1
end

--редактор рупоров алианса
function LUA_ITEM_ALLIANCE_SPEAKER_TABLE()

	local pushd = 0
	pushd = ITEM_ALLIANCE_SPEAKER_TABLE

	pushd = IntTable(pushd,86441)
	pushd = IntTable(pushd,52018)
	pushd = IntTable(pushd,52019)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_ALLIANCE_SPEAKER_TABLE OK!") end
	return 1
end

--теперь эта функйция находится в gdeliveryd
--редактор ограничения окон по локациям
--function LUA_HWID_TAGS_LIMIT()
--
--	local pushd = 0
--	pushd = HWID_TAGS_LIMIT
--	
--	pushd = IntIntTable(pushd,128,3) -- Долина бездушия ( Гуй )
--	pushd = IntIntTable(pushd,127,3) -- Долина священной луны ( Данж: Луна )
--	pushd = IntIntTable(pushd,129,3) -- Город инея ( Данж: Иней )
--	pushd = IntIntTable(pushd,131,3) -- Сумеречный храм ( Данж: ХХ )
--	
--	-- pushd = IntIntTable(pushd,132,3) -- Куб судьбы(Куб)
--	-- pushd = IntIntTable(pushd,138,2) -- Ущелье Феникса
--	-- pushd = IntIntTable(pushd,143,1) -- Зал пяти императоров ( Основная локация Битвы династий )
--	-- pushd = IntIntTable(pushd,144,1) -- Поле боя Битвы династий "Захват флага"
--	-- pushd = IntIntTable(pushd,145,1) -- Поле боя Битвы династий "Бой за кристаллы"
--	-- pushd = IntIntTable(pushd,146,1) -- Поле боя Битвы династий "Битва на мосту"
--	-- pushd = IntIntTable(pushd,147,1) -- Долина заката ( Лока для ивента "Битва катапульт" )
--	-- pushd = IntIntTable(pushd,226,2) -- Зал перерождения ( Данж: Луна )	
--	
--	pushd = IntIntTable(pushd,0  ,0) -- Последний Элемент Массива
--	if lua_debug == 1 then mylogfunc("LUA_HWID_TAGS_LIMIT OK!") end
--	return 1
--end

--редактор итемов для оффлайн котов
function LUA_ITEM_OFFLINE_MARKET()

	local pushd = 0	
	pushd = ITEM_OFFLINE_MARKET
	
	pushd = IntTable(pushd,86413)
	pushd = IntTable(pushd,86414)
	
	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_OFFLINE_MARKET OK!") end
	return 1
end

--Локации в которых работает призыв алианса
function LUA_ALLIANCE_CONGREGATE_TAG()

	local pushd = 0
	pushd = ALLIANCE_CONGREGATE_TAG

	pushd = IntTable(pushd,1)	--Мир
	pushd = IntTable(pushd,121)	--Рай
	pushd = IntTable(pushd,122)	--Ад
	pushd = IntTable(pushd,137)	--Хроно
	pushd = IntTable(pushd,163)	--
	pushd = IntTable(pushd,168)	--
	pushd = IntTable(pushd,185)	--

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ALLIANCE_CONGREGATE_TAG OK!") end
	return 1
end

--редактор межсерверных горнов
function LUA_ITEM_GLOBAL_SPEAKER_TABLE()

	local pushd = 0
	pushd = ITEM_GLOBAL_SPEAKER_TABLE

	pushd = IntTable(pushd,86416)
	pushd = IntTable(pushd,48179)
	pushd = IntTable(pushd,48178)

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_ITEM_GLOBAL_SPEAKER_TABLE OK!") end
	return 1
end

--редактор шанса заточки через миражи
function LUA_REFINE_TABLE()

	local pushd = 0
	pushd = REFINE_TABLE
	
	pushd = IntTable(pushd,0)
	pushd = FloatFloatFloatFloatTable(pushd, 0.50, 0.7,  0 ,0 )
	pushd = IntTable(pushd,1)
	pushd = FloatFloatFloatFloatTable(pushd, 0.30, 0,    0 ,1 )
	pushd = IntTable(pushd,2)
	pushd = FloatFloatFloatFloatTable(pushd, 0.30, 0,    0 ,1 )
	pushd = IntTable(pushd,3)
	pushd = FloatFloatFloatFloatTable(pushd, 0.30, 0,    0 ,1 )
	pushd = IntTable(pushd,4)
	pushd = FloatFloatFloatFloatTable(pushd, 0.30, 0,    0 ,1 )
	pushd = IntTable(pushd,5)
	pushd = FloatFloatFloatFloatTable(pushd, 0.30, 0,    0 ,1 )
	pushd = IntTable(pushd,6)
	pushd = FloatFloatFloatFloatTable(pushd, 0.30, 0,    0 ,1 )
	pushd = IntTable(pushd,7)
	pushd = FloatFloatFloatFloatTable(pushd, 0.30, 0,    0 ,1 )
	pushd = IntTable(pushd,8)
	pushd = FloatFloatFloatFloatTable(pushd, 0.25, 0,    0 ,1 )
	pushd = IntTable(pushd,9)
	pushd = FloatFloatFloatFloatTable(pushd, 0.20, 0,    0 ,1 )
	pushd = IntTable(pushd,10)
	pushd = FloatFloatFloatFloatTable(pushd, 0.12, 0,    0 ,1 )
	pushd = IntTable(pushd,11)
	pushd = FloatFloatFloatFloatTable(pushd, 0.05, 0,    0 ,1 )
	
	if lua_debug == 1 then mylogfunc("LUA_REFINE_TABLE OK!") end
end

--редактор усиления заточки
function LUA_REFINE_FACTOR()

	local pushd = 0
	pushd = REFINE_FACTOR
	
	pushd = FloatTable(pushd,0)
	pushd = FloatTable(pushd,1.0)
	pushd = FloatTable(pushd,2.0)
	pushd = FloatTable(pushd,3.05)
	pushd = FloatTable(pushd,4.3)
	pushd = FloatTable(pushd,5.75)
	pushd = FloatTable(pushd,7.55)
	pushd = FloatTable(pushd,9.95)	
	pushd = FloatTable(pushd,13)
	pushd = FloatTable(pushd,17.05)
	pushd = FloatTable(pushd,22.3)
	pushd = FloatTable(pushd,29)
	pushd = FloatTable(pushd,37.5)	
	
	if lua_debug == 1 then mylogfunc("LUA_REFINE_FACTOR OK!") end
end

function LUA_RATE_PATCH( _tag , _exp , _sp, _item, _money, _task_exp, _task_sp, _task_money  )

	pushd = RATE_LIST_TABLE
	if ( game__GetWorldTag() == _tag or -1 == _tag ) then
	
		--pushd = pushd+4 -- punitive_param 0 active
		pushd = IntTable(pushd,1) --опыт
		pushd = FloatTable(pushd,_exp) --опыт
		pushd = FloatTable(pushd,_sp) --дух
		pushd = FloatTable(pushd,_item) --дроп
		pushd = FloatTable(pushd,_money) --деньги
		pushd = FloatTable(pushd,_task_exp) --кв опыт
		pushd = FloatTable(pushd,_task_sp) --кв дух
		pushd = FloatTable(pushd,_task_money) --кв деньги

		--pushd = pushd+4 -- punitive_param 1 active
		pushd = IntTable(pushd,1) --опыт
		pushd = FloatTable(pushd,_exp) --опыт
		pushd = FloatTable(pushd,_sp) --дух
		pushd = FloatTable(pushd,_item) --дроп
		pushd = FloatTable(pushd,_money) --деньги
		pushd = FloatTable(pushd,_task_exp) --кв опыт
		pushd = FloatTable(pushd,_task_sp) --кв дух
		pushd = FloatTable(pushd,_task_money) --кв деньги

		--pushd = pushd+4 -- punitive_param 2 active
		pushd = IntTable(pushd,1) --опыт
		pushd = FloatTable(pushd,_exp) --опыт
		pushd = FloatTable(pushd,_sp) --дух
		pushd = FloatTable(pushd,_item) --дроп
		pushd = FloatTable(pushd,_money) --деньги
		pushd = FloatTable(pushd,_task_exp) --кв опыт
		pushd = FloatTable(pushd,_task_sp) --кв дух
		pushd = FloatTable(pushd,_task_money) --кв деньги

		--pushd = pushd+4 -- punitive_param 3 active
		pushd = IntTable(pushd,1) --опыт
		pushd = FloatTable(pushd,_exp) --опыт
		pushd = FloatTable(pushd,_sp) --дух
		pushd = FloatTable(pushd,_item) --дроп
		pushd = FloatTable(pushd,_money) --деньги
		pushd = FloatTable(pushd,_task_exp) --кв опыт
		pushd = FloatTable(pushd,_task_sp) --кв дух
		pushd = FloatTable(pushd,_task_money) --кв деньги
	end
	
end

function LUA_RATE_TAGS()

	 LUA_RATE_PATCH -- мир дефолтный опыт
	 ( 
	 	1, --Tag локации
	 	1.0, --опыт 
	 	1.0, --дух
	 	1.0, --дроп
	 	1.0, --деньги
	 	1.0, --кв опыт
	 	1.0, --кв дух
	 	1.0  --кв деньги
	 )

end

--======================================================================================
--FUNCTIONS EXEQUTER
--======================================================================================

--Инициализация функций конфигураций
function InitLuaConfig()

	game__Packet(PACKET_CLEAN,0,0) -- почистить буфер пакета
	LUA_BALANCE_EDITOR()
	LUA_INCAST_EDITOR()
	LUA_SKILL_SENDER_EDITOR()
	LUA_SKILL_BUFF_EDITOR()
	LUA_ATTACK_SPEED_EDITOR()
	LUA_BUG_SKILL_EDITOR()
	LUA_SWAP_ITEM_EDITOR()
	LUA_ITEM_POPPET_DUMMY_TABLE()
	LUA_ITEM_WORLD_SPEAKER_TABLE()
	LUA_ITEM_SUPERWORLD_SPEAKER_TABLE()
	LUA_ITEM_GATCHER_SPEED()
	LUA_ITEM_MASS_PICKUP()
	LUA_ITEM_PET_RENAME()
	LUA_ITEM_REFINE_FULL()
	LUA_ITEM_SCROLL_TOWN()
	LUA_GOOD_ITEMS_TABLE()
	LUA_GOOD_AMULETS_TAG()
	LUA_ELF_DISTABLE_LOCATIONS()
	LUA_PATTY_DISTABLE_TAGS()
	LUA_MASS_PICKUP_DISTABLE_TAG()
	LUA_DISTANCE_SERVICE_TAG()
	LUA_DISTANCE_SERVICE_TYPE()
	LUA_OTHER_MINE_SPEED()
	LUA_ITEM_ALLIANCE_SPEAKER_TABLE()
	LUA_ITEM_OFFLINE_MARKET()
	LUA_ITEM_GLOBAL_SPEAKER_TABLE()
	LUA_VIP_SCORE_LEVEL_TABLE()
	LUA_REFINE_TABLE()
	LUA_REFINE_FACTOR()

end

--======================================================================================
--EVENTS ON SERVER
--======================================================================================

--		void Init();
--		void Update();
--		void HeartBeat(int tick);
--		int  EventTimerExec(int id, int count);
--		void PlayerEnterWorld(int roleid);
--		void PlayerLeaveWorld(int roleid);
--		void SetHwidData(int roleid, int64_t hwid);
--		void EventOnPlayerKilled(int roleid, int killer, int killtype, int is_pariah, int attacker_mode );
--		void EventOnMonsterKilled(int mobid,int killer, int tid);
--		void EventOnCommandHandler(int roleid, int cmd_type, char* buf, size_t size);
--		int  EventOnPlayerUseItem(int roleid, unsigned int item_id);
--		int  EventOnPlayerTryGather(int roleid, int mineid, int tid, int task_id);
--		void EventOnPlayerAttackMsg(int roleid, int attacker, void * d);
--		void EventOnRecvCmd(int roleid, int cmd_type, void * buf, int size);
--		void EventOnSendCmd(int roleid, int cmd_type, void * buf, int size);
--		void EventPlayerRefineItem(int roleid, int item_id, int refine_level, int index);
--		void EventPlayerRefineItemFail(int roleid, int item_id, int refine_level, int index);
--		void EventPlayerObtianItem(int roleid, int pos, int id, int count, int proc_type);
--		void EventPlayerHeartBeat(int roleid, int tick);
--		void EventNpcHeartBeat(int npcid, int tick);
--		void EventOnPlayerEquipChange(int roleid);
--		void EventPlayerGetInventory(int roleid, int inv);
--		void EventPlayerSave(int roleid);
--		int  EventOnPlayerChat(int roleid, int cannel, const void * message);
--		int  EventOnSendServiceRequest(int roleid, int npcid, int service_type);
--		int  EventOnPlayerDoShopping(int roleid, int id, int count, int point);
--		int  EventOnPlayerDoDividendShopping(int roleid, int id,int count, int point);
--		int  EventOnCanActivateItem(int roleid, int id, int slot, int location);

-- загрузка скрипта
function Init()

	InitLuaConfig()
	
	LUA_RATE_PATCH -- рейты по умолчанию
	( 
	 	-1, --Tag локации
	 	1.0, --опыт 
	 	1.0, --дух
	 	1.0, --дроп
	 	1.0, --деньги
	 	1.0, --кв опыт
	 	1.0, --кв дух
	 	1.0  --кв деньги
	)
	
	if lua_debug == 1 then mylogfunc("LUA: EVENT=Init ") end
end

-- функция после инициализации локации
function InitWorld()

	LUA_RATE_TAGS()
	if lua_debug == 1 then mylogfunc("LUA: EVENT=InitWorld ") end
end

-- обновление скрипта
function Update()

	InitLuaConfig()
	LUA_RATE_TAGS()
	if game__GetWorldTag() == 1 then game__ChatMsg(CHAT_WORLD,0,9,"^CC0000LUA::^FF6600GS: ^00FF00System reload!",-1) end
	
	if lua_debug == 1 then mylogfunc("LUA: EVENT=Update ") end
end

-- счётчик луа движка 
function HeartBeat(tick)


	if lua_debug == 1 and lua_debug == 1 then mylogfunc("LUA: EVENT=HeartBeat , tick="..tick) end
end

-- таймер выполнения событий 
function EventTimerExec(id, count)

	local tag = game__GetWorldTag()
	
	--if id == MMOTOP_MSG and tag == 1 then
	--	game__ChatMsg(CHAT_WORLD,0,9,"Уважаемые игроки, голосуйте за наш сервер!",-1)
	--end

	if lua_debug == 1 then mylogfunc("LUA: EVENT=HeartBeat , tick="..tick) end
	return 1 -- повторять 1 закончить 0
end

-- игрок вошёл 
function PlayerEnterWorld(roleid)


	if lua_debug == 1 then mylogfunc("LUA: EVENT=PlayerEnterWorld , tick="..roleid) end
end

-- игрок вышел 
function PlayerLeaveWorld(roleid)


	if lua_debug == 1 then mylogfunc("LUA: EVENT=PlayerLeaveWorld , tick="..roleid) end
end

-- игрок сохранился 
function EventPlayerSave(roleid)


	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventPlayerSave , tick="..roleid) end
end

--Счетчик игрока, выполняется каждую секунду
function EventPlayerHeartBeat(roleid, tick)

	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventPlayerHeartBeat, roleid="..int(roleid)..", tick="..int(tick)) end
end

-- Игрок послал ид железа на сервер
function SetHwidData(roleid,hwid)

	if lua_debug == 1 then mylogfunc("LUA: EVENT=SetHwidData , roleid = "..roleid.." , hwid = "..hwid ) end
end

-- Игрок был убит
function EventOnPlayerKilled (roleid, killer, killtype, is_pariah, attacker_mode)

	-- Оповещение о том что вы убили игрока
	game__ChatMsg(CHAT_SINGLE,killer,8,"Вы убили персонажа "..game__GetName(NAME_ROLE,roleid).."!",-1)
	
	--if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnPlayerKilled, roleid="..int(roleid)..", killer="..int(killer)..", killtype="..int(killtype)..", is_pariah="..int(is_pariah)..", attacker_mode="..int(attacker_mode)) end
end

-- Моб был убит
function EventOnMonsterKilled(mobid,killer,tid)


	--if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnMonsterKilled, mobid="..int(mobid)..", killer="..int(killer)..", tid="..int(tid)) end
end

-- Игрок хочет вскопать шахту
function EventOnPlayerTryGather(roleid,mineid,tid,task_id)

	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnPlayerTryGather, roleid="..int(roleid)..", mineid="..int(mineid)..", tid="..int(tid)..", task_id="..int(task_id)) end
	return 0 --(return 0 - можно , 1 - нельзя)
end

--Игрок заточил итем успешно
function EventPlayerRefineItem(roleid, item_id, refine_lvl, pos)

	if refine_lvl >= 9 then
		game__ChatMsg(CHAT_WORLD,roleid,11,"Заточил <1><> на +"..int(refine_lvl), pos)
	end
	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventPlayerRefineItem, roleid="..int(roleid)..", item_id="..int(item_id)..", refine_lvl="..int(refine_lvl)..", pos="..int(pos)) end
end

--Игрок заточил итем неудачно
function EventPlayerRefineItemFail(roleid, item_id, refine_lvl, pos)

	if refine_lvl >= 9 then
		game__ChatMsg(CHAT_WORLD,roleid,11,"Cбил заточку <1><> с +"..int(refine_lvl).." до 0", pos)
	end
	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventPlayerRefineItemFail, roleid="..int(roleid)..", item_id="..int(item_id)..", refine_lvl="..int(refine_lvl)..", pos="..int(pos)) end
end

--Игрок получил итем
function EventPlayerObtianItem(roleid, pos, id, count, proc_type)

	--if lua_debug == 1 then mylogfunc("LUA: EVENT=EventPlayerObtianItem, roleid="..int(roleid)..", pos="..int(pos)..", id="..int(id)..", count="..int(count)..", proc_type="..int(proc_type)) end
end

-- Игрок переоделся
function EventOnPlayerEquipChange (roleid)
	
	--if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnPlayerEquipChange, roleid = "..int(roleid)) end
end

--Получить инвентарь игрока
function EventPlayerGetInventory(roleid, inv)

	--инвентарь: 0 обычный, 1 эквип, 2 квестовый
	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventPlayerGetInventory, roleid = "..int(roleid)..", inv="..int(inv)) end
end

-- Игрок хочт воспользоваться сервисом у НПСа (return 0 - можно , 1 - нельзя)
function EventOnSendServiceRequest(roleid, npcid, service_type)
	
	if lua_debug == 1 then game__ChatMsg(CHAT_SINGLE,roleid,11,"^FF8000NPC:^FFFFFF id = ^FF8000"..int(npcid).."^FFFFFF , service = ^FF8000"..int(service_type),-1) end
	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnSendServiceRequest, roleid="..int(roleid)..", npcid="..int(npcid)..", service_type="..int(service_type)) end
	return 0
end

-- Игрок хочет купить итем в шопе (return 0 - можно , 1 - нельзя)
function EventOnPlayerDoShopping(roleid, id, count, price)
	
	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnPlayerDoShopping, roleid="..int(roleid)..", id="..int(id)..", count="..int(count)..", price="..int(price)) end
	return 0
end

-- Игрок хочет купить итем в ярмарке (return 0 - можно , 1 - нельзя)
function EventOnPlayerDoDividendShopping(roleid, id, count, price)

	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnPlayerDoDividendShopping, roleid="..int(roleid)..", id="..int(id)..", count="..int(count)..", price="..int(price)) end
	return 0
end

-- Игрок хочет одеть шмотку(return 0 - можно , 1 - нельзя)
function EventOnCanActivateItem(roleid,id,slot,location)
	
	--if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnCanActivateItem, roleid="..int(roleid)..", id="..int(id)..", slot="..int(slot)..", location="..int(location)) end
	return 0
end

--Игрок обновил локации
function EventOnInsRefresh(roleid)

	game__ChatMsg(CHAT_SINGLE,roleid,8,"Локации успешно обновлены!",-1)
	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnInsRefresh, roleid="..int(roleid)) end
end

--Сообщение о состоянии автоассиста
function EventOnSetAutoAssist(roleid, is_enable)

	if is_enable == 0 then game__ChatMsg(CHAT_SINGLE,roleid, GN_CHAT_CHANNEL_INSTANCE,  "^FF0000[Автоассист]: ^FFFFFFВыключен!",-1) end
	if is_enable == 1 then game__ChatMsg(CHAT_SINGLE,roleid, GN_CHAT_CHANNEL_INSTANCE,  "^00FF00[Автоассист]: ^FFFFFFВключен!",-1) end
end


-- Игрок использовал итем
function EventOnPlayerUseItem (roleid, item_id)
	-- return 0 продолжать по дефолту функцию 
	-- return 1 не удалять итем и завершать функцию 
	-- return 2 удалять итем и завершать функцию 

	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnPlayerUseItem, roleid = "..int(roleid)..", item_id = "..(item_id)) end
	return 0
	
end

--отправляем информацию в деливери
function SendPlayerLuaInfo(roleid, buf, size)


	if lua_debug == 1 then mylogfunc("LUA: EVENT=SendPlayerLuaInfo, roleid = "..int(roleid)) end
end


--игрок использовал команду
function EventOnCommandHandler(roleid, cmd_type, buf, size)

	local level    = game__GetRoleVar(PIMP_LEVEL, roleid)
	local is_gm    = game__GetRoleVar(CTRL_GM, roleid)
	local is_debug = game__GetRoleVar(CTRL_DEBUG, roleid)

	if cmd_type == 801 then
		local pNpc = game__GetObjectVar(NPC_COORDS_BY_TID,0,39184) --Посланник Шао Хао
		if pNpc == 0 then 
			game__ChatMsg(CHAT_SINGLE,roleid,8,"НИП не найден в данной локации, Посланник Шао Хао обитает в Морае.",-1)
			return 0 
		end
		local x, y, z = game__GetCoordDataClient(pNpc)
		game__ChatMsg(CHAT_SINGLE,roleid,8,"Посланник Шао Хао сейчас тут: "..int(x)..", "..int(z)..", "..int(y),-1)
		return 1
	end

	if cmd_type == 802 then
		local pNpc = game__GetObjectVar(NPC_COORDS_BY_TID,0,11517) --Вей Сяо Бао
		if pNpc == 0 then 
			game__ChatMsg(CHAT_SINGLE,roleid,8,"НИП не найден в данной локации, Вэй Сяобао обитает в Идеальном Мире.", -1)
			return 0 
		end
		local x, y, z = game__GetCoordDataClient(pNpc)
		game__ChatMsg(CHAT_SINGLE,roleid,8,"Вэй Сяобао сейчас тут: "..int(x)..", "..int(z)..", "..int(y),-1)
		return 1
	end
	
	if is_gm == 1 and is_debug == 1 then
	
		if cmd_type == 803 then
			game__RemoveSkill(roleid,77)
		end

		if cmd_type == 804 then
			game__LearnSkill(roleid,77,5)
		end	

		if cmd_type == 805 then
		
			--WORLD_LOCAL			= 0 -- не сохраняется в базу
			--WORLD_DB				= 1 -- сохраняется в базу для каждого данжа в свою
			--WORLD_GLOBAL			= 2 -- сохроняется в базу глобально для всех локаций
		
			local var_local = game__GetWorldVar(WORLD_LOCAL, TYPE_INT, 1)
			local var_db = game__GetWorldVar(WORLD_DB, TYPE_INT, 1)
			local var_global = game__GetWorldVar(WORLD_GLOBAL, TYPE_INT, 1)
			
			var_local = var_local + 1
			var_db = var_db + 1
			var_global = var_global + 1
			
			game__SetWorldVar(WORLD_LOCAL, TYPE_INT, 1, var_local);
			game__SetWorldVar(WORLD_DB, TYPE_INT, 1, var_db); 
			game__SetWorldVar(WORLD_GLOBAL, TYPE_INT, 1, var_global); 
			
			game__ChatMsg(CHAT_SINGLE,roleid,GN_CHAT_CHANNEL_GLOBAL,"GetVar: "..int(var_local)..", "..int(var_db)..", "..int(var_global),-1)
			
		end

		if cmd_type == 806 then
		
			game__Packet(PACKET_CLEAN,0,0)
			game__Packet(PACKET_PUSH,TYPE_SHORT,442)
			game__Packet(PACKET_PUSH,TYPE_INT,3)
			game__Packet(PACKET_PUSH,TYPE_INT,1)
			game__Packet(PACKET_PUSH,TYPE_INT,-64)
			game__Send(roleid)
			
			--game__Packet(PACKET_CLEAN,0,0)
			--game__Packet(PACKET_PUSH,TYPE_SHORT,443)
			--game__Packet(PACKET_PUSH,TYPE_INT,-64)
			--game__Packet(PACKET_PUSH,TYPE_INT,0)
			--game__Packet(PACKET_PUSH,TYPE_INT,2)
			--game__Packet(PACKET_PUSH,TYPE_INT,0)
			--game__Packet(PACKET_PUSH,TYPE_INT,2)
			--game__Packet(PACKET_PUSH,TYPE_INT,1120)
			--game__Packet(PACKET_PUSH,TYPE_INT,1120)
			--game__Send(roleid)
			
		end
		
		if cmd_type == 807 then
		
			game__InvPlayerGiveItem(roleid, 0, 80041, 1, 0, 0) --
		end


	end

	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnCommandHandler, roleid = "..int(roleid).." cmd_type = "..cmd_type) end
	return 0
end

-- Игрок написал в чат
function EventOnPlayerChat(roleid,chanel,message)

	local cmdlist = mysplit(message)
	
	local level    = game__GetRoleVar(PIMP_LEVEL, roleid)
	local is_gm    = game__GetRoleVar(CTRL_GM, roleid)
	local is_debug = game__GetRoleVar(CTRL_DEBUG, roleid)

	--if chanel == 1 or chanel == 12 or chanel == 15 then
	--	
	--	if level < 15 then
	--		game__ChatMsg(CHAT_SINGLE,roleid,11,"^3399FFВы должны достигнуть 15 уровня!",-1)
	--		return 1
	--	end
	--end
	
	--if chanel == 0 and cmdlist[1] == "Секрет" then
	--	
	--	if game__PlayerCheckCoord(roleid, 1, 10, 350, 266, 3350) == 1 then
	--		game__PlayerObtainTitle(roleid, 60616, 0)
	--		return 1
	--	end
	--end	
	if is_gm == 1 and is_debug == 1 then
		
		--тестовые сообщения 
		--...
	end 



	if lua_debug == 1 then mylogfunc("LUA: EVENT=EventOnPlayerChat, roleid = "..int(roleid).." chanel = "..int(chanel).." msg = "..message) end
	return 0 --Функция возвращает значение: 0 продолжить сообщение ; 1 завершить функцию и не отправлять сообщение 
end

--======================================================================================
-- DEBUG LUA FUNCTIONS -- используется тллько если включен дебаг мод -- lua_debug
--======================================================================================

--Счетчик монстров, выполняется каждую секунду (Не используется, тестировалось для нагрузки)
function EventNpcHeartBeat(npcid, tick)

	--mylogfunc("LUA_NPC_HEARTBEAT: npcid = "..int(npcid).." tick = "..int(tick))
end

--Вывод всех пакетов отправленных игроком на ГС
function EventOnRecvCmd(roleid, cmd_type, buf, size)
	
	--if lua_debug == 1 then game__ChatMsg(CHAT_SINGLE,roleid,11,"^FF0000C2S:^FFFFFF cmd = ^FF0000"..int(cmd_type).."^FFFFFF , size = ^FF0000"..int(size),-1) end
	--mylogfunc("LUA_HANDLE_USE_CMD: roleid = "..int(roleid).." cmd_type = "..int(cmd_type).." size = "..int(size))
end

--Вывод всех пакетов отправленных игроку гсом
function EventOnSendCmd(roleid, cmd_type, buf, size)

	--if lua_debug == 1 then game__ChatMsg(CHAT_SINGLE,roleid,11,"^3399FFS2C:^FFFFFF cmd = ^3399FF"..int(cmd_type).."^FFFFFF , size = ^3399FF"..int(size),-1) end
	--mylogfunc("LUA_SEND_LS_CMD: roleid = "..int(roleid).." cmd_type = "..int(cmd_type).." size = "..int(size))
end

--Игрок получает урон (Не используется, тестировалось для нагрузки)
function EventOnPlayerAttackMsg(roleid , attacker)
	
	--mylogfunc("LUA_PLAYER_ATTACK: roleid = "..int(roleid).." attacker = "..int(attacker))
end

--======================================================================================



