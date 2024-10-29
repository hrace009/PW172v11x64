#include <Windows.h>
#include "../Header/colorname.h"

GameColorName* GameColorName::instance = 0;


void GameColorName::Init()
{
	enable = true;
}

unsigned int GameColorName::SET_RGBA(int red, int grin, int blue)
{
	return (_byteswap_ulong(RGB(red, grin, blue)) >> 8) | 0xff000000;
}

int GameColorName::UIColor_svetofor()
{
	time_t a = game_tick() / 20 % 200;
	char r, g, b;
	if (a > 0 && a < 70) return  SET_RGBA(255, 0, 0);
	if (a > 100 && a < 170) return  SET_RGBA(0, 255, 0);
	return  SET_RGBA(255, 255, 0);
}

int GameColorName::UIColor_infarkt()
{
	time_t a = game_tick() / 10 % 100;
	if (a < 50 && a % 10) return SET_RGBA(255 - a, 0, 0);
	if (a > 50 && a < 60) return SET_RGBA(a, 0, 0);
	if (a > 60 && a < 70) return SET_RGBA(255, 0, 0);
	return  SET_RGBA(220, 0, 0);
}

int GameColorName::UIColor_police()
{
	time_t a = game_tick() / 10 % 100;
	if (a > 0 && a < 40 && (a % 4)) return  SET_RGBA(255, 0, 0);
	if (a > 50 && a < 80 && (a % 4)) return  SET_RGBA(0, 0, 255);
	return (a % 2) ? SET_RGBA(255, 255, 255) : SET_RGBA(0, 0, 0);
}

int GameColorName::UIColor_black()
{
	time_t a = game_tick() / 15 % 500;
	if (a < 250) return SET_RGBA(255 - (a % 250), 255 - (a % 250), 255 - (a % 250));
	return SET_RGBA(5 + (a % 250), 5 + (a % 250), 5 + (a % 250));
}

int GameColorName::UIColor_Chamelion()
{
	time_t a = game_tick() / 10 % 1020;
	if (a < 255 && (a % 4)) return SET_RGBA(255, (a % 255), 0);
	if (a < 510 && (a % 4)) return SET_RGBA((a % 255), 255, 0);
	if (a < 765 && (a % 4)) return SET_RGBA(0, (255 - a % 255), (a % 255));
	if (a && (a % 4)) return SET_RGBA((a % 255), 0, (255 - a % 255));
	return (a % 2) ? SET_RGBA(250, 250, 250) : SET_RGBA(5, 5, 5);
}

int GameColorName::UIColor_raduga()
{
	time_t a = game_tick() / 10 % 1020;

	int r, g, b;


	if (a < 255)
	{
		g = a % 255;
		return SET_RGBA(255, g, 0);
	}
	else if (a < 510)
	{
		r = 255 - a % 255;
		return SET_RGBA(r, 255, 0);
	}
	else if (a < 765)
	{
		g = 255 - a % 255;
		b = a % 255;
		return SET_RGBA(0, g, b);
	}
	else
	{
		r = a % 255;
		b = 255 - a % 255;
		return SET_RGBA(r, 0, b);
	}
}

int GameColorName::UIColor_sweet()
{
	time_t a = game_tick() / 40 % 10;

	if (a < 7)
	{
		return SET_RGBA(57, 67, 120);
	}
	else if (a < 8)
	{
		return SET_RGBA(255, 255, 255);
	}

	else if (a < 9)
	{
		return SET_RGBA(51, 53, 255);
	}
	else
	{
		return SET_RGBA(255, 255, 255);
	}
}

int GameColorName::UIColor_disko()
{
	int tk = game_tick();
	int a = tk / 200 % 3;
	int r = tk % 200 + 50;
	int g = tk % 255;
	int b = tk % 180 + 70;

	if (a == 1)
	{
		return SET_RGBA(r, g, b);
	}

	else if (a == 2)
	{
		return SET_RGBA(b, r, g);
	}
	else
	{
		return SET_RGBA(g, r, b);
	}
}

int GameColorName::UIColor_fireice()
{
	time_t a = game_tick() / 5 % 510;

	int r, g, b;

	if (a < 255)
	{
		r = a % 255;
		b = a % 255;
		return SET_RGBA(r, 130, 255 - b);
	}
	else
	{
		r = a % 255;
		b = a % 255;
		return SET_RGBA(255 - r, 130, b);
	}
}

int GameColorName::UIColor_vio()
{
	time_t a = game_tick() / 2 % 500;

	int r, g, b;

	if (a < 250)
	{
		r = a % 250 / 2;
		b = a % 250 / 3;
		return SET_RGBA(125 + r, 10, 167 + b);
	}
	else
	{
		r = a % 250 / 2;
		b = a % 250 / 3;
		return SET_RGBA(250 - r, 10, 250 - b);
	}
}

int GameColorName::UIColor_nebo()
{
	time_t a = game_tick() / 5 % 300;

	int r, g, b;

	if (a < 150)
	{
		r = a % 150 / 3;
		g = a % 150;
		return SET_RGBA(50 - r, 150 - g, 255);
	}
	else
	{
		r = a % 150 / 3;
		g = a % 150;
		return SET_RGBA(r, g, 255);
	}
}

int GameColorName::UIColor_izumrud()
{
	time_t a = game_tick() / 5 % 530;

	int r, g, b;

	if (a < 255)
	{
		b = a % 255;

		return SET_RGBA(0, 255, 255 - b);
	}
	else if (a < 510)
	{
		b = a % 255;

		return SET_RGBA(0, 255, b);
	}
	else if (a < 518)
	{
		return SET_RGBA(255, 255, 255);
	}
	else if (a < 524)
	{
		return SET_RGBA(0, 255, 0);
	}
	else
	{
		return SET_RGBA(0, 0, 0);
	}
}

int GameColorName::UIColor_puls_red()
{
	time_t a = game_tick() / 15 % 500;

	int r, g, b, c;

	c = a % 10;

	if (c < 8)
	{
		if (a < 250)
		{
			r = a % 250;
			return SET_RGBA(r, 0, 0);
		}
		else
		{
			r = a % 250;
			return SET_RGBA(250 - r, 0, 0);
		}
	}
	return SET_RGBA(255, 0, 0);
}

int GameColorName::UIColor_red()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		g = a % 200;
		b = a % 200;
		return SET_RGBA(255, 200 - g, 200 - b);
	}
	else
	{
		g = a % 200;
		b = a % 200;
		return SET_RGBA(255, g, b);
	}

}

int GameColorName::UIColor_beryza()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		r = a % 200;
		return SET_RGBA(200 - r, 255, 255);
	}
	else
	{
		r = a % 200;
		return SET_RGBA(r, 255, 255);
	}
}

int GameColorName::UIColor_orange()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		g = a % 200 / 2;
		b = a % 200;
		return SET_RGBA(255, 200 - g, 200 - b);
	}
	else
	{
		g = a % 200 / 2;
		b = a % 200;
		return SET_RGBA(255, 100 + g, b);
	}
}

int GameColorName::UIColor_violet()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		r = a % 200 / 2;
		g = a % 200;
		return SET_RGBA(200 - r, 200 - g, 255);
	}
	else
	{
		r = a % 200 / 2;
		g = a % 200;
		return SET_RGBA(100 + r, g, 255);
	}
}

int GameColorName::UIColor_roz()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		g = a % 200;
		return SET_RGBA(255, 200 - g, 255);
	}
	else
	{
		g = a % 200;
		return SET_RGBA(255, g, 255);
	}
}

int GameColorName::UIColor_sin()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		r = a % 200;
		g = a % 200;
		return SET_RGBA(200 - r, 200 - g, 255);
	}
	else
	{
		r = a % 200;
		g = a % 200;
		return SET_RGBA(r, g, 255);
	}
}

int GameColorName::UIColor_green()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		r = a % 200;
		b = a % 200;
		return SET_RGBA(200 - r, 255, 200 - b);
	}
	else
	{
		r = a % 200;
		b = a % 200;
		return SET_RGBA(r, 255, b);
	}
}

int GameColorName::UIColor_yellow()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		b = a % 200;
		return SET_RGBA(255, 255, 200 - b);
	}
	else
	{
		b = a % 200;
		return SET_RGBA(255, 255, b);
	}
}

int GameColorName::UIColor_kislot()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		r = a % 200;
		return SET_RGBA(255 - r, 255, 0);
	}
	else
	{
		r = a % 200;
		return SET_RGBA(55 + r, 255, 0);
	}
}

int GameColorName::UIColor_cold()
{
	time_t a = game_tick() / 10 % 400;
	int r, g, b;

	if (a < 200)
	{
		r = a % 200;
		return SET_RGBA(255 - r, 0, 255);
	}
	else
	{
		r = a % 200;
		return SET_RGBA(55 + r, 0, 255);
	}
}

int GameColorName::UIColor_puls_green()
{
	time_t a = game_tick() / 15 % 500;
	int r, g, b, c;
	c = a % 10;

	if (c < 8)
	{
		if (a < 250)
		{
			g = a % 250;
			return SET_RGBA(0, 250 - g, 0);
		}
		else
		{
			g = a % 250;
			return SET_RGBA(0, g, 0);
		}
	}
	return SET_RGBA(0, 255, 0);
}

int GameColorName::UIColor_puls_blue()
{
	time_t a = game_tick() / 15 % 500;
	int r, g, b, c;
	c = a % 10;

	if (c < 8)
	{
		if (a < 250)
		{
			b = a % 250;
			return SET_RGBA(0, 0, 250 - b);
		}
		else
		{
			b = a % 250;
			return SET_RGBA(0, 0, b);
		}
	}
	return SET_RGBA(0, 0, 255);
}

int GameColorName::UIColor_puls_black()
{
	time_t a = game_tick() / 15 % 500;
	int r, g, b, c;
	c = a % 10;

	if (c < 8)
	{
		if (a < 250)
		{
			r = a % 250;
			g = a % 250;
			b = a % 250;
			return SET_RGBA(250 - r, 250 - g, 250 - b);
		}
		else
		{
			r = a % 250;
			g = a % 250;
			b = a % 250;
			return SET_RGBA(r, g, b);
		}
	}
	return SET_RGBA(0, 0, 0);
}

int GameColorName::UIColor_emocore()
{
	time_t a = game_tick() / 15 % 500;
	int r, g, b, c;
	c = a % 10;

	if (c & 4)
	{
		if (a < 200)
		{
			r = a % 50;
			b = a % 50;
			return SET_RGBA(200 - r, 0, 200 - b);
		}
		else
		{
			r = a % 50;
			b = a % 50;
			return SET_RGBA(r, 0, b);
		}
	}
	return SET_RGBA(255, 0, 255);
}

int GameColorName::UIColor_puls_ellow()
{
	time_t a = game_tick() / 15 % 500;
	int r, g, b, c;
	c = a % 10;

	if (c < 8)
	{
		if (a < 250)
		{
			r = a % 250;
			b = a % 250;
			return SET_RGBA(250 - r, 250 - b, 0);
		}
		else
		{
			r = a % 250;
			b = a % 250;
			return SET_RGBA(r, b, 0);
		}
	}
	return SET_RGBA(255, 255, 0);
}

int GameColorName::UIColor_puls_multi()
{
	time_t a = game_tick() / 500 % 100;
	if (a < 30 && (a % 2)) return  UIColor_puls_green();
	if (a < 60 && (a % 2)) return  UIColor_puls_blue();
	if (a < 90 && (a % 2)) return  UIColor_puls_red();
	return UIColor_puls_black();
}

int GameColorName::GetColorName(int color)
{
	int blue = color & 0xff;
	int grin = ((color & (0xff << 8)) >> 8);
	int red = ((color & (0xff << 16)) >> 16);
	int alpha = ((color & (0xff << 24)) >> 24);
	
	if (!red && !grin && !blue)
	{
		switch (alpha)
		{
		case 1:  return UIColor_svetofor();   //мигающий светофор
		case 2:  return UIColor_infarkt();    //мигающий инфаркт
		case 3:  return UIColor_police();     //мигающий полиция
		case 4:  return UIColor_black();      //перелив черный
		case 5:  return UIColor_Chamelion();  //пульс хамелион
		case 6:  return UIColor_raduga();     //перелив радуга
		case 7:  return UIColor_sweet();      //мигающий молния
		case 8:  return UIColor_disko();      //мигающий дискотека
		case 9:  return UIColor_fireice();    //перелив лёд и пламя
		case 10: return UIColor_vio();        //перелив ультрафиолет
		case 11: return UIColor_nebo();       //перелив небо
		case 12: return UIColor_izumrud();    //перелив изумруд
		case 13: return UIColor_puls_red();   //пульс красный
		case 14: return UIColor_emocore();    //пульс розовый
		case 15: return UIColor_red();        //перелив красный
		case 16: return UIColor_beryza();     //перелив берюзовый
		case 17: return UIColor_orange();     //перелив оранж
		case 18: return UIColor_violet();        //перелив фил
		case 19: return UIColor_roz();        //перелив розовый
		case 20: return UIColor_sin();        //перелив синий
		case 21: return UIColor_green();      //перелив зелёный
		case 22: return UIColor_yellow();     //перелив желтый
		case 23: return UIColor_kislot();     //перелив кислотный
		case 24: return UIColor_cold();       //перелив холодный
		case 25: return UIColor_puls_green(); //пульс зелёный
		case 26: return UIColor_puls_blue();  //пульс синий
		case 27: return UIColor_puls_black(); //пульс черный
		case 28: return UIColor_puls_ellow(); //пульс желтый
		case 29: return UIColor_puls_multi(); //Мультипульсар
		default: return 0;
		}
	}
	return color;
}
