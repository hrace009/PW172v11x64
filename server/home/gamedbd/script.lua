--======================================================================================
--Глобальные переменные
--======================================================================================

lua_debug	= 0
max_member1 = 50
max_member2 = 80
max_member3 = 100
battle_bid_item = 21652
alliance_off = 0

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






--======================================================================================
--Глобальные функции
--======================================================================================

--глобальный счётчик
function HeartBeat(tick)

	if lua_debug == 1 then mylogfunc("HeartBeat: tick = "..tick) end
end

--======================================================================================

-- Релог Lua файла 
function Update()

	mylogfunc("Update: --OK-- ")
end

--======================================================================================

-- Патчинг при запуске GS 
function Init()

	mylogfunc("Init: --OK-- ")
end



