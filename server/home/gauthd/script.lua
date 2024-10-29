--======================================================================================
--Lua manager by Deadraky (C) 2022
--======================================================================================

--======================================================================================
--Константы (не меняйте их, иначе код работать не будет корректно)
--======================================================================================

MIN  						= 60
HOUR 						= MIN*60
DAY  						= HOUR*24
WEEK 						= DAY*7

TYPE_CHAR 					= 0 -- game__Patch & game__Get type
TYPE_SHORT 					= 1 -- game__Patch & game__Get type
TYPE_INT 					= 2 -- game__Patch & game__Get type
TYPE_INT64 					= 3 -- game__Patch & game__Get type
TYPE_FLOAT 					= 4 -- game__Patch & game__Get type
TYPE_DOUBLE 				= 5 -- game__Patch & game__Get type

-- error reason

ERR_SUCCESS                	= 0  -- 成功
ERR_TOBECONTINUE           	= 1  -- 成功，并且还有更多数据未传递完，目前未用
ERR_INVALID_ACCOUNT        	= 2  -- 帐号不存在
ERR_INVALID_PASSWORD       	= 3  -- 密码错误
ERR_TIMEOUT                	= 4  -- 超时
ERR_INVALID_ARGUMENT       	= 5  -- 参数错误
ERR_FRIEND_SYNCHRONIZE     	= 6  -- 好友信息保存到数据库时无法同步
ERR_SERVERNOTSUPPLY        	= 7  -- 该服务器不支持该请求
ERR_COMMUNICATION          	= 8  -- 网络通讯错误
ERR_ACCOUNTLOCKED          	= 9  -- 多次重复登陆，当前用户的一个登陆正在被处理，处于锁定状态
ERR_MULTILOGIN             	= 10 -- 多次重复登陆，且用户选择自动下线
ERR_INVALID_NONCE          	= 11 -- 无效的nonce值
ERR_LOGOUT_FAIL            	= 12 -- AUTH登出失败
ERR_GAMEDB_FAIL            	= 13 -- 游戏服务器获取玩家角色信息失败
ERR_ENTERWORLD_FAIL        	= 14 -- 登陆游戏服务器失败
ERR_EXCEED_MAXNUM          	= 15 -- 游戏服务器人数已达上限
ERR_IN_WORLD               	= 16 -- 玩家角色已经在世界
ERR_EXCEED_LINE_MAXNUM	   	= 17 -- 该线角色数已达到上限
ERR_INVALID_LINEID	   		= 18 -- 没有这个线号
ERR_NO_LINE_AVALIABLE	   	= 19 -- 没有可用的线
ERR_DELIVER_SEND           	= 21 --  转发失败
ERR_DELIVER_TIMEOUT        	= 22 --  转发超时
ERR_ACCOUNTEMPTY           	= 23 -- 帐户余额不足
ERR_ACCOUNTFORBID          	= 24 -- 帐号被GameMaster锁定，不允许登陆
ERR_INVALIDCHAR            	= 25 -- 文字中含有非法的字符
ERR_IP_LOCK		   			= 26 --
ERR_ID_LOCK		   			= 27 --
ERR_MATRIXFAILURE	   		= 28 --
ERR_LOGINFAIL              	= 31 -- 登陆游戏失败
ERR_KICKOUT                	= 32 -- 被踢下线
ERR_CREATEROLE             	= 33 -- 创建角色失败
ERR_DELETEROLE             	= 34 -- 删除角色失败
ERR_ROLELIST               	= 35 -- 获得角色列表失败
ERR_UNDODELROLE            	= 36 -- 撤销删除角色失败
ERR_SRVMAINTAIN            	= 37 -- 服务器维护中，暂时不能登陆
ERR_ROLEFORBID             	= 38 -- 角色被GM封杀，不允许登陆游戏
ERR_SERVEROVERLOAD         	= 39 -- 服务器人数已达上限
ERR_ACKICKOUT              	= 40 -- 被反外挂程序踢下线
ERR_ROLEBACKED             	= 20 -- 角色数据保存在backdbd中，尚未恢复

--======================================================================================
--Глобальные переменные
--======================================================================================

lua_debug			= 0 -- дебаг режим

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
--TABLES & TRUE ITEMS
--======================================================================================


--======================================================================================
--FUNCTIONS EXEQUTER
--======================================================================================

--Инициализация функций конфигураций
function InitLuaConfig()

end

--======================================================================================
--Глобальные функции
--======================================================================================

--заблокировать игрока по железу
function EventOnUserLogin(userid, login, ip, hwid)

	mylogfunc("EventOnUserLogin: userid = "..userid.." , login = "..login.." , ip = "..ip.." , hwid = "..hwid)
	
	--if hwid == "-597941228148359738" then return ERR_ACCOUNTLOCKED end -- заблокировать железо
	
	return ERR_SUCCESS
end

--глобальный счётчик
function HeartBeat(tick)

	--mylogfunc("HeartBeat: tick = "..tick)
end

--======================================================================================

-- Релог Lua файла 
function Update()

	InitLuaConfig()
	mylogfunc("Update: --OK-- ")
end

--======================================================================================

-- Патчинг при запуске GS 
function Init()

	InitLuaConfig()
	mylogfunc("Init: --OK-- ")
end

