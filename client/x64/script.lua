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

TYPE_CHAR 				= 0 -- game__Patch & game__Get type
TYPE_SHORT 				= 1 -- game__Patch & game__Get type
TYPE_INT 				= 2 -- game__Patch & game__Get type
TYPE_INT64 				= 3 -- game__Patch & game__Get type
TYPE_FLOAT 				= 4 -- game__Patch & game__Get type
TYPE_DOUBLE 			= 5 -- game__Patch & game__Get type

--======================================================================================
--Глобальные переменные
--======================================================================================

lua_idx 			= 6660 -- уникальный индекс
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

--глобальный счётчик
function EventOnHeartBeat(tick)

	--mylogfunc("EventOnHeartBeat: tick = "..tick)
end

--======================================================================================

-- Релог Lua файла 
function EventOnReloadScript()

	InitLuaConfig()
	mylogfunc("EventOnReloadScript: --OK-- ")
end

--======================================================================================

-- Патчинг при запуске GS 
function EventOnStartScript()

	InitLuaConfig()
	mylogfunc("EventOnStartScript: --OK-- ")
end

