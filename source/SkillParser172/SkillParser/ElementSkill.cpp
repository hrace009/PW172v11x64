#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/timeb.h>
#include <cstring>
#include <tchar.h>

#include "config.h"
#include "ElementSkill.h"

int GNET::ElementSkill::GetCoolingTime(ID id, int level)
{
    int res = 0;
    ElementSkill* s = Create(id, level);
    if (s)
    {
        res = s->GetCoolingTime();
        s->Destroy();
    }
    return res;
}

float GNET::ElementSkill::GetPraydistance(ID id, int level)
{
    float res = 0;
    ElementSkill* s = Create(id, level);
    if (s)
    {
        char stype = s->skill->type;
        bool sautoattack = s->skill->auto_attack;
        s->skill->type = GNET::TYPE_ATTACK;
        s->skill->auto_attack = 0;
        res = s->GetPrayRange(0, 0, 0, 0, 0);
        s->skill->type = stype;
        s->skill->auto_attack = sautoattack;
        s->Destroy();
    }
    return res;
}

float GNET::ElementSkill::GetMpcost(ID id, int level)
{
    float res = 0;
    ElementSkill* s = Create(id, level);
    if (s)
    {
        res = s->GetMpCost();
        s->Destroy();
    }
    return res;
}

int GNET::ElementSkill::GetCoolDownLimit(ID id, int level)
{
    int res = 0;
    ElementSkill* s = Create(id, level);
    if (s)
    {
        res = s->GetCoolDownLimit();
        s->Destroy();
    }
    return res;
}

int GNET::ElementSkill::GetCostShieldEnergy(ID id, int level)
{
    int res = 0;
    ElementSkill* s = Create(id, level);
    if (s)
    {
        res = s->GetCostShieldEnergy();
        s->Destroy();
    }
    return res;
}

int GNET::ElementSkill::GetCoolingTime(ID id, int level, int defform)
{
    int res = 0;
    ElementSkill* s = Create(id, level);
    if (s)
    {
        s->SetDefForm(defform);
        res = s->GetCoolingTime();
        s->Destroy();
    }
    return res;
}