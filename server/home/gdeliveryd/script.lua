--======================================================================================
--Lua manager by Deadraky (C) 2022
--======================================================================================

--======================================================================================
--Константы (не меняйте их, иначе код работать не будет корректно)
--======================================================================================

--время
MIN  = 60
HOUR = MIN*60
DAY  = HOUR*24
WEEK = DAY*7

TYPE_CHAR 				= 0 -- game__Patch & game__Get type
TYPE_SHORT 				= 1 -- game__Patch & game__Get type
TYPE_INT 				= 2 -- game__Patch & game__Get type
TYPE_INT64 				= 3 -- game__Patch & game__Get type
TYPE_FLOAT 				= 4 -- game__Patch & game__Get type
TYPE_DOUBLE 			= 5 -- game__Patch & game__Get type

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
GN_CHAT_CHANNEL_ALLIANCE	= 16	--Алианс
GN_CHAT_CHANNEL_CENTER		= 17	--В центре экрана

--======================================================================================
--Глобальные переменные
--======================================================================================

lua_debug 				= 0 -- включить отладочные функции 
lua_idx 				= 6660 -- уникальный индекс
COUNTRY_MAX_BONUS		= 10000 -- максимальный бонус для игрока на бд

--======================================================================================

HW_TAGS = 0 -- адрес локаций с ограничением по окнам
COUNTRY_PLAYERS_CNT = 0 -- адрес указателя на количество игроков в локацииях на бд

--======================================================================================
--Используемые функции 
--======================================================================================

-- void game__Patch(size_t address, int type, double value);
-- double game__Get(size_t address, int type, size_t offset);
-- void game__SingleChatMsg(int roleid, int channel, const char * utf8_msg);
-- void game__ChatBroadCast(int roleid, int channel, const char * utf8_msg);


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
	local outstr = mydata().." [LUA] "..text.."\n"
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
--=====================================[PATCH FUNC]=====================================
--======================================================================================

--Патчинг таблицы из 1 инта
function IntTable(pushd, value)

	game__Patch(pushd,TYPE_INT,value)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 1 флоата
function FloatTable(pushd, value)

	game__Patch(pushd,TYPE_FLOAT,value)
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

--Патчинг таблицы из 2х флоатов
function FloatFloatTable(pushd, value1, value2)

	game__Patch(pushd,TYPE_FLOAT,value1)
	pushd = pushd + 4
	game__Patch(pushd,TYPE_FLOAT,value2)
	pushd = pushd + 4
	return pushd
end

-- XID++
function HashIDX()
	lua_idx = lua_idx+1
end


--======================================================================================
--Территориальные войны
--======================================================================================

function BattleManagerLogic( now ) -- каждый день

	local logic_day = (now / DAY)

	if  logic_day  < 1 then 
		logic_day  = 0 --Воскресенье
		return logic_day
	end

	if  logic_day  < 2 then 
		logic_day  = 1 --Понедельник
		return logic_day
	end

	if  logic_day  < 3 then 
		logic_day  = 2 --Вторник
		return logic_day
	end
	
	if  logic_day  < 4 then 
		logic_day  = 3 --Среда
		return logic_day
	end

	if  logic_day  < 5 then 
		logic_day  = 4 --Четверг
		return logic_day
	end

	if  logic_day  < 6 then 
		logic_day  = 5 --Пятница
		return logic_day
	end

		logic_day  = 6 --Суббота
		return logic_day
end

--======================================================================================

function BidBeginTime( now ) --начало ставок

	--mylogfunc("BidBeginTime: now = "..now)
	return 3*DAY + 19*HOUR + 0*MIN -- среда в 19.00 
end

--======================================================================================

function BidEndTime( now ) --конец ставок

	--mylogfunc("BidEndTime: now = "..now)
	return 4*DAY + 19*HOUR + 0*MIN -- четверг в 19.00 
end

--======================================================================================

function BattleTime( now ) --начало сражений

	--mylogfunc("BattleTime: now = "..now)
	return 0 --(domain sev)--5*DAY + 19*HOUR + 0*MIN -- пятница в 19.00 
end

--======================================================================================

function RewardTime( now ) --Выдача награды

	--mylogfunc("RewardTime: now = "..now)
	return 5*DAY + 12*HOUR -- пятница в 12.00 
end

--======================================================================================

function BattleInterval( id_battle ) --Выдача награды

	--mylogfunc("BattleInterval: id_battle = "..id_battle)
	return 180 -- редактировать ли интервал между битвами
end

--======================================================================================
--Битва династий
--======================================================================================

function CountryBattleStartTime() --Начало бд

	return 20*HOUR + 20*MIN
end

--======================================================================================

function CountryBattleBonusTime() --Выдача бонусов

	return 21*HOUR + 21*MIN
end

--======================================================================================

function CountryBattleClearTime() --Очищение таблиц

	return 22*HOUR + 30*MIN
end

--======================================================================================

function CountryMaxCount() --Количество фракций

	return 4 
end

--======================================================================================

function CountryBattleBonus() --Банк битвы династий

	return 85000  
end

--======================================================================================

function CountryBattleItem() --Итем битвы династий

	return 36343
end


--======================================================================================
--Редакторы массивов
--======================================================================================

--редактор ограничения окон по локациям
function LUA_HWID_TAGS_LIMIT()

	local pushd = 0
	pushd = HW_TAGS
	
	-- первый элемент (index локации в gs.conf) , второй элемент - лимиты
	pushd = IntIntTable(pushd,57,3) -- Долина священной луны ( Данж: Луна )
	pushd = IntIntTable(pushd,58,3) -- Долина бездушия ( Гуй ) 
	pushd = IntIntTable(pushd,59,3) -- Город инея ( Данж: Иней )
	pushd = IntIntTable(pushd,71,3) -- Сумеречный храм ( Данж: ХХ )
	
	-- pushd = IntIntTable(pushd,132,3) -- Куб судьбы(Куб)
	-- pushd = IntIntTable(pushd,138,2) -- Ущелье Феникса
	-- pushd = IntIntTable(pushd,143,1) -- Зал пяти императоров ( Основная локация Битвы династий )
	-- pushd = IntIntTable(pushd,144,1) -- Поле боя Битвы династий "Захват флага"
	-- pushd = IntIntTable(pushd,145,1) -- Поле боя Битвы династий "Бой за кристаллы"
	-- pushd = IntIntTable(pushd,146,1) -- Поле боя Битвы династий "Битва на мосту"
	-- pushd = IntIntTable(pushd,147,1) -- Долина заката ( Лока для ивента "Битва катапульт" )
	-- pushd = IntIntTable(pushd,226,2) -- Зал перерождения ( Данж: Луна )	
	
	pushd = IntIntTable(pushd,0  ,0) -- Последний Элемент Массива
	if lua_debug == 1 then mylogfunc("LUA_HWID_TAGS_LIMIT OK!") end
	return 1
end

--Редактор количества игроков на локациях битвы династий 
function LUA_COUNTRY_PLAYERS_CNT()

	local pushd = 0
	pushd = COUNTRY_PLAYERS_CNT
	
	pushd = IntTable(pushd,30)	-- Количество игроков на локации бд 
	pushd = IntTable(pushd,20)	-- Количество игроков на локации бд
	pushd = IntTable(pushd,40)	-- Количество игроков на локации бд

	pushd = IntTable(pushd,0) --последний элемент массива
	if lua_debug == 1 then mylogfunc("LUA_COUNTRY_PLAYERS_CNT OK!") end
	return 1
end

--======================================================================================
--Глобальные функции
--======================================================================================

--функция запускающая редакторы массивов
function InitLuaConfig()

	LUA_COUNTRY_PLAYERS_CNT()
	LUA_HWID_TAGS_LIMIT()
				 

end


--глобальный счётчик
function HeartBeat(tick)

	if lua_debug == 1 then mylogfunc("HeartBeat: tick = "..tick) end
end

--======================================================================================

-- Релог Lua файла 
function Update()

	InitLuaConfig()
	game__ChatBroadCast(0, GN_CHAT_CHANNEL_BROADCAST, "^FFFFFF[GDELIVERYD]: ^FF0000Lua System Reload!!!") 
	mylogfunc("Update: --OK-- ")
end

--======================================================================================

-- Патчинг при запуске
function Init()

	InitLuaConfig()
	mylogfunc("Init: --OK-- ")
end
