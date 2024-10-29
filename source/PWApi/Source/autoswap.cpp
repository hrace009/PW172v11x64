#include <iostream>
#include <cstring>

#include "../Header/config.h"
#include "../Header/asm.h"
#include "../Header/packet.h"
#include "../Header/autoswap.h"

AutoSwap* AutoSwap::instance = 0;

void AutoSwap::Init()
{
	save = false;
	Clear();
}

void AutoSwap::Clear()
{
	memset(equip, 0xff, sizeof(equip));
}

void AutoSwap::Set(unsigned char inv, unsigned char equip)
{
	if (save == true && inv < MAX_ITEM && equip < MAX_EQUIP)
	{
		this->equip[equip] = inv;
	}
}

void AutoSwap::Packet()
{
	C2S_AUTOSWAP ca;
	memset(&ca, 0x00, sizeof(ca));

	for (size_t i = 0; i < MAX_EQUIP; i++)
	{
		if (equip[i] != 0xff)
		{
			ca.item[ca.count].equip = i; ca.item[ca.count++].inv = equip[i];
		}
	}

	if (ca.count > 0)
	{
		ca.cmd = Packet::CMD_AUTOSWAP;
		ASM_SendPacket(&ca, ca.size());
	}
}

void AutoSwap::Change()
{
	(save ^= 1) ? Clear() : Packet();
}