#include "skillwrapper.h"
#include "skill.h"
#include "skillfilter.h"
#include "playerwrapper.h"

DEFINE_SUBSTANCE(filter_Incdefence ,filter,CLASS_INCDEFENCE);
DEFINE_SUBSTANCE(filter_Incattack ,filter, CLASS_INCATTACK );
DEFINE_SUBSTANCE(filter_Incresist ,filter,CLASS_INCRESIST);
DEFINE_SUBSTANCE(filter_Incmagic ,filter,CLASS_INCMAGIC);
DEFINE_SUBSTANCE(filter_Speedup ,filter,CLASS_SPEEDUP);
DEFINE_SUBSTANCE(filter_Inchp ,filter,CLASS_INCHP);
DEFINE_SUBSTANCE(filter_Incmp ,filter,CLASS_INCMP);
DEFINE_SUBSTANCE(filter_Decmp ,filter,CLASS_DECMP);
DEFINE_SUBSTANCE(filter_Dechp ,filter,CLASS_DECHP);
DEFINE_SUBSTANCE(filter_Fastmpgen ,filter,CLASS_FASTMPGEN);
DEFINE_SUBSTANCE(filter_Fasthpgen ,filter,CLASS_FASTHPGEN);
DEFINE_SUBSTANCE(filter_Incdodge ,filter,CLASS_INCDODGE);
DEFINE_SUBSTANCE(filter_Decdodge ,filter,CLASS_DECDODGE);
DEFINE_SUBSTANCE(filter_Decdefence ,filter,CLASS_DECDEFENCE);
DEFINE_SUBSTANCE(filter_Decattack ,filter,CLASS_DECATTACK);
DEFINE_SUBSTANCE(filter_Decresist ,filter,CLASS_DECRESIST);
DEFINE_SUBSTANCE(filter_Decmagic ,filter,CLASS_DECMAGIC);
DEFINE_SUBSTANCE(filter_Slow ,filter,CLASS_SLOW);
DEFINE_SUBSTANCE(filter_Burning,filter,CLASS_BURNING);
DEFINE_SUBSTANCE(filter_Bleeding,filter,CLASS_BLEEDING);
DEFINE_SUBSTANCE(filter_Thunder,filter,CLASS_THUNDER);
DEFINE_SUBSTANCE(filter_Fallen,filter,CLASS_FALLEN);
DEFINE_SUBSTANCE(filter_Toxic,filter,CLASS_TOXIC);
DEFINE_SUBSTANCE(filter_Sleep ,filter,CLASS_SLEEP);
DEFINE_SUBSTANCE(filter_Dizzy ,filter,CLASS_DIZZY);
DEFINE_SUBSTANCE(filter_Sealed ,filter,CLASS_SEALED);
DEFINE_SUBSTANCE(filter_Fix ,filter,CLASS_FIX);
DEFINE_SUBSTANCE(filter_Slowpray ,filter,CLASS_SLOWPRAY);
DEFINE_SUBSTANCE(filter_Feathershield ,filter,CLASS_FEATHERSHIELD);
DEFINE_SUBSTANCE(filter_Retort ,filter,CLASS_RETORT);
DEFINE_SUBSTANCE(filter_Blind ,filter,CLASS_BLIND);
DEFINE_SUBSTANCE(filter_Crazy ,filter,CLASS_CRAZY);
DEFINE_SUBSTANCE(filter_Tardy ,filter,CLASS_TARDY);
DEFINE_SUBSTANCE(filter_Magicleak ,filter,CLASS_MAGICLEAK);
DEFINE_SUBSTANCE(filter_Inchurt ,filter,CLASS_INCHURT);
DEFINE_SUBSTANCE(filter_Iceblade ,filter,CLASS_ICEBLADE);
DEFINE_SUBSTANCE(filter_Soilshield ,filter,CLASS_SOILSHIELD);
DEFINE_SUBSTANCE(filter_Activateskill ,filter,CLASS_ACTIVATESKILL);
DEFINE_SUBSTANCE(filter_Activatereboundskill ,filter,CLASS_ACTIVATEREBOUNDSKILL);
DEFINE_SUBSTANCE(filter_Tigerform ,filter,CLASS_TIGERFORM);
DEFINE_SUBSTANCE(filter_Cannonform ,filter,CLASS_CANNONFORM);
DEFINE_SUBSTANCE(filter_Frenetic ,filter,CLASS_FRENETIC); 
DEFINE_SUBSTANCE(filter_HighestLevel ,filter,CLASS_HIGHESTLEVEL); // Novo Atributo
DEFINE_SUBSTANCE(filter_Toxicblade ,filter,CLASS_TOXICBLADE);
DEFINE_SUBSTANCE(filter_Enhancegold ,filter,CLASS_ENHANCEGOLD);
DEFINE_SUBSTANCE(filter_Enhancewood ,filter,CLASS_ENHANCEWOOD);
DEFINE_SUBSTANCE(filter_Enhancewater ,filter,CLASS_ENHANCEWATER);
DEFINE_SUBSTANCE(filter_Enhancefire ,filter,CLASS_ENHANCEFIRE);
DEFINE_SUBSTANCE(filter_Enhancesoil ,filter,CLASS_ENHANCESOIL);
DEFINE_SUBSTANCE(filter_Reducegold ,filter,CLASS_REDUCEGOLD);
DEFINE_SUBSTANCE(filter_Reducewood ,filter,CLASS_REDUCEWOOD);
DEFINE_SUBSTANCE(filter_Reducewater ,filter,CLASS_REDUCEWATER);
DEFINE_SUBSTANCE(filter_Reducefire ,filter,CLASS_REDUCEFIRE);
DEFINE_SUBSTANCE(filter_Reducesoil ,filter,CLASS_REDUCESOIL);
DEFINE_SUBSTANCE(filter_Fireblade,filter,CLASS_FIREBLADE);
DEFINE_SUBSTANCE(filter_Fastpray,filter,CLASS_FASTPRAY);
DEFINE_SUBSTANCE(filter_Dechurt ,filter,CLASS_DECHURT);
DEFINE_SUBSTANCE(filter_Hpgen ,filter,CLASS_HPGEN);
DEFINE_SUBSTANCE(filter_Mpgen ,filter,CLASS_MPGEN);
DEFINE_SUBSTANCE(filter_Yijin ,filter,CLASS_YIJIN);
DEFINE_SUBSTANCE(filter_Xisui ,filter,CLASS_XISUI);
DEFINE_SUBSTANCE(filter_Fireshield ,filter,CLASS_FIRESHIELD);
DEFINE_SUBSTANCE(filter_Iceshield ,filter,CLASS_ICESHIELD);
DEFINE_SUBSTANCE(filter_Apgen ,filter,CLASS_APGEN);
DEFINE_SUBSTANCE(filter_Antiwater ,filter,CLASS_ANTIWATER);
DEFINE_SUBSTANCE(filter_Powerup ,filter,CLASS_POWERUP);
DEFINE_SUBSTANCE(filter_Stoneskin ,filter,CLASS_STONESKIN);
DEFINE_SUBSTANCE(filter_Decaccuracy ,filter,CLASS_DECACCURACY);
DEFINE_SUBSTANCE(filter_Incaccuracy ,filter,CLASS_INCACCURACY);
DEFINE_SUBSTANCE(filter_Ironshield ,filter,CLASS_IRONSHIELD);
DEFINE_SUBSTANCE(filter_Giant ,filter,CLASS_GIANT);
DEFINE_SUBSTANCE(filter_Devilstate ,filter,CLASS_DEVILSTATE);
DEFINE_SUBSTANCE(filter_Blessmagic ,filter,CLASS_BLESSMAGIC);
DEFINE_SUBSTANCE(filter_Wingshield ,filter,CLASS_WINGSHIELD);
DEFINE_SUBSTANCE(filter_Firearrow ,filter,CLASS_FIREARROW);
DEFINE_SUBSTANCE(filter_Eaglecurse ,filter,CLASS_EAGLECURSE);
DEFINE_SUBSTANCE(filter_Freemove ,filter,CLASS_FREEMOVE);
DEFINE_SUBSTANCE(filter_Frozen ,filter,CLASS_FROZEN);
DEFINE_SUBSTANCE(filter_Incsmite ,filter,CLASS_INCSMITE);
DEFINE_SUBSTANCE(filter_Canti ,filter,CLASS_CANTI);
DEFINE_SUBSTANCE(filter_Apleak ,filter,CLASS_APLEAK);
DEFINE_SUBSTANCE(filter_Noregain ,filter,CLASS_NOREGAIN);
DEFINE_SUBSTANCE(filter_Jingji ,filter,CLASS_JINGJI);
DEFINE_SUBSTANCE(filter_Icon ,filter,CLASS_ICON);
DEFINE_SUBSTANCE(filter_Foxform ,filter,CLASS_FOXFORM);
DEFINE_SUBSTANCE(filter_Swiftform ,filter,CLASS_SWIFTFORM);
DEFINE_SUBSTANCE(filter_Fastride ,filter,CLASS_FASTRIDE);
DEFINE_SUBSTANCE(filter_Sharpblade ,filter,CLASS_SHARPBLADE);
DEFINE_SUBSTANCE(filter_Addattackdegree ,filter,CLASS_ADDATTACKDEGREE);
DEFINE_SUBSTANCE(filter_Adddefencedegree ,filter,CLASS_ADDDEFENCEDEGREE);
DEFINE_SUBSTANCE(filter_Subattackdegree ,filter,CLASS_SUBATTACKDEGREE);
DEFINE_SUBSTANCE(filter_Subdefencedegree ,filter,CLASS_SUBDEFENCEDEGREE);
DEFINE_SUBSTANCE(filter_Immunesealed ,filter,CLASS_IMMUNESEALED);//lgc
DEFINE_SUBSTANCE(filter_Immunesleep ,filter,CLASS_IMMUNESLEEP);
DEFINE_SUBSTANCE(filter_Immuneslowdizzy ,filter,CLASS_IMMUNESLOWDIZZY);
DEFINE_SUBSTANCE(filter_Immunewound ,filter,CLASS_IMMUNEWOUND);
DEFINE_SUBSTANCE(filter_Immuneall ,filter,CLASS_IMMUNEALL);
DEFINE_SUBSTANCE(filter_Immunephysical ,filter,CLASS_IMMUNEPHYSICAL);
DEFINE_SUBSTANCE(filter_Immunefire ,filter,CLASS_IMMUNEFIRE);
DEFINE_SUBSTANCE(filter_Immunewater ,filter,CLASS_IMMUNEWATER);
DEFINE_SUBSTANCE(filter_Immunemetal ,filter,CLASS_IMMUNEMETAL);
DEFINE_SUBSTANCE(filter_Immunewood ,filter,CLASS_IMMUNEWOOD);
DEFINE_SUBSTANCE(filter_Immunesoil ,filter,CLASS_IMMUNESOIL);
DEFINE_SUBSTANCE(filter_Immunemagical ,filter,CLASS_IMMUNEMAGICAL);
DEFINE_SUBSTANCE(filter_Arrogant ,filter,CLASS_ARROGANT);
DEFINE_SUBSTANCE(filter_Slowswim ,filter,CLASS_SLOWSWIM);
DEFINE_SUBSTANCE(filter_Fastswim ,filter,CLASS_FASTSWIM);
DEFINE_SUBSTANCE(filter_Slowfly ,filter,CLASS_SLOWFLY);
DEFINE_SUBSTANCE(filter_Fastfly ,filter,CLASS_FASTFLY);
DEFINE_SUBSTANCE(filter_Slowride ,filter,CLASS_SLOWRIDE);
DEFINE_SUBSTANCE(filter_Apgencont ,filter,CLASS_APGENCONT);
DEFINE_SUBSTANCE(filter_Apleakcont ,filter,CLASS_APLEAKCONT);
DEFINE_SUBSTANCE(filter_Incelfstr ,filter,CLASS_INCELFSTR);
DEFINE_SUBSTANCE(filter_Incelfagi ,filter,CLASS_INCELFAGI);
DEFINE_SUBSTANCE(filter_Incdefence2 ,filter,CLASS_INCDEFENCE2);
DEFINE_SUBSTANCE(filter_Weakelement ,filter,CLASS_WEAKELEMENT);
DEFINE_SUBSTANCE(filter_Deeppoision ,filter,CLASS_DEEPPOISION);
DEFINE_SUBSTANCE(filter_Rooted ,filter,CLASS_ROOTED);
DEFINE_SUBSTANCE(filter_Earthguard ,filter,CLASS_EARTHGUARD);
DEFINE_SUBSTANCE(filter_Fury ,filter,CLASS_FURY);
DEFINE_SUBSTANCE(filter_Sandstorm ,filter,CLASS_SANDSTORM);
DEFINE_SUBSTANCE(filter_Homefeeling ,filter,CLASS_HOMEFEELING);
DEFINE_SUBSTANCE(filter_Reducewater2 ,filter,CLASS_REDUCEWATER2);
DEFINE_SUBSTANCE(filter_Incsmite2 ,filter,CLASS_INCSMITE2);
DEFINE_SUBSTANCE(filter_Decdefence2 ,filter,CLASS_DECDEFENCE2);
DEFINE_SUBSTANCE(filter_Reducefire2 ,filter,CLASS_REDUCEFIRE2);
DEFINE_SUBSTANCE(filter_Slowattackpray ,filter,CLASS_SLOWATTACKPRAY);
DEFINE_SUBSTANCE(filter_Burning2 ,filter,CLASS_BURNING2);
DEFINE_SUBSTANCE(filter_Burningfeet ,filter,CLASS_BURNINGFEET);
DEFINE_SUBSTANCE(filter_Hardenskin ,filter,CLASS_HARDENSKIN);
DEFINE_SUBSTANCE(filter_Reducegold2 ,filter,CLASS_REDUCEGOLD2);
DEFINE_SUBSTANCE(filter_Leafdance ,filter,CLASS_LEAFDANCE);
DEFINE_SUBSTANCE(filter_Charred ,filter,CLASS_CHARRED);
DEFINE_SUBSTANCE(filter_Vacuum ,filter,CLASS_VACUUM);
DEFINE_SUBSTANCE(filter_Immuneblooding ,filter,CLASS_IMMUNEBLOODING);
DEFINE_SUBSTANCE(filter_Absorbphysicdamage ,filter,CLASS_ABSORBPHYSICDAMAGE);
DEFINE_SUBSTANCE(filter_Absorbmagicdamage ,filter,CLASS_ABSORBMAGICDAMAGE);
DEFINE_SUBSTANCE(filter_Retortmagic ,filter,CLASS_RETORTMAGIC);
DEFINE_SUBSTANCE(filter_RetortNewPaladin ,filter,CLASS_SHIELDBUFFNEW3);
DEFINE_SUBSTANCE(filter_Windshield ,filter,CLASS_WINDSHIELD);
DEFINE_SUBSTANCE(filter_Airstreamlock ,filter,CLASS_AIRSTREAMLOCK);
DEFINE_SUBSTANCE(filter_Closed ,filter,CLASS_CLOSED);
DEFINE_SUBSTANCE(filter_Insertvstate ,filter,CLASS_INSERTVSTATE);
DEFINE_SUBSTANCE(filter_Immuneweak ,filter,CLASS_IMMUNEWEAK);
DEFINE_SUBSTANCE(filter_Befrozen ,filter,CLASS_BEFROZEN);
DEFINE_SUBSTANCE(filter_Fallen2 ,filter,CLASS_FALLEN2);
DEFINE_SUBSTANCE(filter_Sealed2 ,filter,CLASS_SEALED2);
DEFINE_SUBSTANCE(filter_Fix2 ,filter,CLASS_FIX2);
DEFINE_SUBSTANCE(filter_Dechurt2 ,filter,CLASS_DECHURT2);
DEFINE_SUBSTANCE(filter_Inchurt2 ,filter,CLASS_INCHURT2);
DEFINE_SUBSTANCE(filter_Inchp2 ,filter,CLASS_INCHP2);
DEFINE_SUBSTANCE(filter_Incattack2 ,filter,CLASS_INCATTACK2);
DEFINE_SUBSTANCE(filter_Incmagic2 ,filter,CLASS_INCMAGIC2);
DEFINE_SUBSTANCE(filter_Incmagic3 ,filter,CLASS_INCMAGIC3);
DEFINE_SUBSTANCE(filter_Fastpray2 ,filter,CLASS_FASTPRAY2);
DEFINE_SUBSTANCE(filter_Speedup2 ,filter,CLASS_SPEEDUP2);
DEFINE_SUBSTANCE(filter_Aurafireattack ,filter,CLASS_AURAFIREATTACK);
DEFINE_SUBSTANCE(filter_Aurabless,filter,CLASS_AURABLESS);
DEFINE_SUBSTANCE(filter_Auracurse,filter,CLASS_AURACURSE);
DEFINE_SUBSTANCE(filter_Incantiinvisibleactive,filter,CLASS_INCANTIINVISIBLEACTIVE);
DEFINE_SUBSTANCE(filter_Inchpsteal,filter,CLASS_INCHPSTEAL);
DEFINE_SUBSTANCE(filter_Inccritdamage,filter,CLASS_INCCRITDAMAGE);
DEFINE_SUBSTANCE(filter_Incdamagedodge,filter,CLASS_INCDAMAGEDODGE);
DEFINE_SUBSTANCE(filter_Incdebuffdodge,filter,CLASS_INCDEBUFFDODGE);
DEFINE_SUBSTANCE(filter_Rebirth,filter,CLASS_REBIRTH);
DEFINE_SUBSTANCE(filter_Deepenbless,filter,CLASS_DEEPENBLESS);
DEFINE_SUBSTANCE(filter_Weakenbless,filter,CLASS_WEAKENBLESS);
DEFINE_SUBSTANCE(filter_Hurtwhenuseskill,filter,CLASS_HURTWHENUSESKILL);
DEFINE_SUBSTANCE(filter_Interruptwhenuseskill,filter,CLASS_INTERRUPTWHENUSESKILL);
DEFINE_SUBSTANCE(filter_Soulretort,filter,CLASS_SOULRETORT);
DEFINE_SUBSTANCE(filter_Soulsealed,filter,CLASS_SOULSEALED);
DEFINE_SUBSTANCE(filter_Soulbeatback,filter,CLASS_SOULBEATBACK);
DEFINE_SUBSTANCE(filter_Soulstun,filter,CLASS_SOULSTUN);
DEFINE_SUBSTANCE(filter_Fishform,filter,CLASS_FISHFORM);
DEFINE_SUBSTANCE(filter_Deepicethrust,filter,CLASS_DEEPICETHRUST);
DEFINE_SUBSTANCE(filter_Adjustattackdefend,filter,CLASS_ADJUSTATTACKDEFEND);
DEFINE_SUBSTANCE(filter_Delayhurt,filter,CLASS_DELAYHURT);
DEFINE_SUBSTANCE(filter_Beastieform,filter,CLASS_BEASTIEFORM);
DEFINE_SUBSTANCE(filter_Inchurtphysicgold,filter,CLASS_INCHURTPHYSICGOLD);
DEFINE_SUBSTANCE(filter_Inchurtwoodwater,filter,CLASS_INCHURTWOODWATER);
DEFINE_SUBSTANCE(filter_Inchurtfireearth,filter,CLASS_INCHURTFIREEARTH);
DEFINE_SUBSTANCE(filter_Attackattachstate,filter,CLASS_ATTACKATTACHSTATE);
DEFINE_SUBSTANCE(filter_Beattackedattachstate,filter,CLASS_BEATTACKEDATTACHSTATE);
DEFINE_SUBSTANCE(filter_Poisionseed,filter,CLASS_POISIONSEED);
DEFINE_SUBSTANCE(filter_Hpgenseed,filter,CLASS_HPGENSEED);
DEFINE_SUBSTANCE(filter_Fastprayincmagic,filter,CLASS_FASTPRAYINCMAGIC);
DEFINE_SUBSTANCE(filter_Incwoodwaterdefense,filter,CLASS_INCWOODWATERDEFENSE);
DEFINE_SUBSTANCE(filter_Specialslow,filter,CLASS_SPECIALSLOW);
DEFINE_SUBSTANCE(filter_Incdefencesmite,filter,CLASS_INCDEFENCESMITE);
DEFINE_SUBSTANCE(filter_Incresistmagic,filter,CLASS_INCRESISTMAGIC);
DEFINE_SUBSTANCE(filter_Transportmptopet,filter,CLASS_TRANSPORTMPTOPET);
DEFINE_SUBSTANCE(filter_Transportdamagetopet,filter,CLASS_TRANSPORTDAMAGETOPET);
DEFINE_SUBSTANCE(filter_Absorbdamageincdefense,filter,CLASS_ABSORBDAMAGEINCDEFENSE);
DEFINE_SUBSTANCE(filter_Incrementalhpgen,filter,CLASS_INCREMENTALHPGEN);
DEFINE_SUBSTANCE(filter_Chanceofrebirth,filter,CLASS_CHANCEOFREBIRTH);
DEFINE_SUBSTANCE(filter_Specialphysichurttrigger,filter,CLASS_SPECIALPHYSICHURTTRIGGER);
DEFINE_SUBSTANCE(filter_Inccountedsmite,filter,CLASS_INCCOUNTEDSMITE);
DEFINE_SUBSTANCE(filter_Weapondisabled,filter,CLASS_WEAPONDISABLED);
DEFINE_SUBSTANCE(filter_Incaggroondamage,filter,CLASS_INCAGGROONDAMAGE);
DEFINE_SUBSTANCE(filter_Enhanceskilldamage,filter,CLASS_ENHANCESKILLDAMAGE);
DEFINE_SUBSTANCE(filter_Detectinvisible,filter,CLASS_DETECTINVISIBLE);
DEFINE_SUBSTANCE(filter_Decapperhit,filter,CLASS_DECAPPERHIT);
DEFINE_SUBSTANCE(filter_Fastmpgen2 ,filter,CLASS_FASTMPGEN2);
DEFINE_SUBSTANCE(filter_Positionrollback,filter,CLASS_POSITIONROLLBACK);
DEFINE_SUBSTANCE(filter_Positionrollback2,filter,CLASS_POSITIONROLLBACK2);
DEFINE_SUBSTANCE(filter_Hprollback,filter,CLASS_HPROLLBACK);
DEFINE_SUBSTANCE(filter_Nofly,filter,CLASS_NOFLY);
DEFINE_SUBSTANCE(filter_Nochangeselect,filter,CLASS_NOCHANGESELECT);
DEFINE_SUBSTANCE(filter_Healabsorb,filter,CLASS_HEALABSORB);
DEFINE_SUBSTANCE(filter_Repelonnormalattack,filter,CLASS_REPELONNORMALATTACK);
DEFINE_SUBSTANCE(filter_Inccritresistance,filter,CLASS_INCCRITRESISTANCE);
DEFINE_SUBSTANCE(filter_Deccritresistance,filter,CLASS_DECCRITRESISTANCE);
DEFINE_SUBSTANCE(filter_Transmitskillattack,filter,CLASS_TRANSMITSKILLATTACK);
DEFINE_SUBSTANCE(filter_Additionalheal,filter,CLASS_ADDITIONALHEAL);
DEFINE_SUBSTANCE(filter_Additionalattack,filter,CLASS_ADDITIONALATTACK);
DEFINE_SUBSTANCE(filter_Transportdamagetoleader,filter,CLASS_TRANSPORTDAMAGETOLEADER);
DEFINE_SUBSTANCE(filter_Forbidbeselected,filter,CLASS_FORBIDBESELECTED);
DEFINE_SUBSTANCE(filter_Enhanceskilldamage2,filter,CLASS_ENHANCESKILLDAMAGE2);
DEFINE_SUBSTANCE(filter_Delayearthhurt,filter,CLASS_DELAYEARTHHURT);
DEFINE_SUBSTANCE(filter_Dizzyinchurt,filter,CLASS_DIZZYINCHURT);
DEFINE_SUBSTANCE(filter_Soulretort2,filter,CLASS_SOULRETORT2);
DEFINE_SUBSTANCE(filter_Fixondamage,filter,CLASS_FIXONDAMAGE);
DEFINE_SUBSTANCE(filter_Apgen2,filter,CLASS_APGEN2);
DEFINE_SUBSTANCE(filter_Incattack3,filter,CLASS_INCATTACK3);
DEFINE_SUBSTANCE(filter_Incattackondamage,filter,CLASS_INCATTACKONDAMAGE);
DEFINE_SUBSTANCE(filter_Rebirth2,filter,CLASS_REBIRTH2);
DEFINE_SUBSTANCE(filter_Healsteal,filter,CLASS_HEALSTEAL);
DEFINE_SUBSTANCE(filter_Dropmoneyondeath,filter,CLASS_DROPMONEYONDEATH);
DEFINE_SUBSTANCE(filter_Incattackrange,filter,CLASS_INCATTACKRANGE);
DEFINE_SUBSTANCE(filter_Thunderform,filter,CLASS_THUNDERFORM);
DEFINE_SUBSTANCE(filter_Delaytransmit,filter,CLASS_DELAYTRANSMIT);
DEFINE_SUBSTANCE(filter_Decnormalattackhurt,filter,CLASS_DECNORMALATTACKHURT);
DEFINE_SUBSTANCE(filter_Freemoveapgen,filter,CLASS_FREEMOVEAPGEN);
DEFINE_SUBSTANCE(filter_Incatkdefhp,filter,CLASS_INCATKDEFHP);
DEFINE_SUBSTANCE(filter_Denyattackcmd,filter,CLASS_DENYATTACKCMD);
DEFINE_SUBSTANCE(filter_Hpmpgennotincombat,filter,CLASS_HPMPGENNOTINCOMBAT);
DEFINE_SUBSTANCE(filter_Inchpmp,filter,CLASS_INCHPMP);
DEFINE_SUBSTANCE(filter_Inchurt3,filter,CLASS_INCHURT3);
DEFINE_SUBSTANCE(filter_Incresist2,filter,CLASS_INCRESIST2);
DEFINE_SUBSTANCE(filter_Flager,filter,CLASS_FLAGER);
DEFINE_SUBSTANCE(filter_Subdefencedegree2,filter,CLASS_SUBDEFENCEDEGREE2);
DEFINE_SUBSTANCE(filter_Incatkdefhp2,filter,CLASS_INCATKDEFHP2);
DEFINE_SUBSTANCE(filter_Incsmite3 ,filter,CLASS_INCSMITE3);
DEFINE_SUBSTANCE(filter_Incpenres,filter,CLASS_INCPENRES);
DEFINE_SUBSTANCE(filter_Incmaxhpatkdfdlevel,filter,CLASS_INCMAXHPATKDFDLEVEL);
DEFINE_SUBSTANCE(filter_Dechurt3,filter,CLASS_DECHURT3);
DEFINE_SUBSTANCE(filter_Attachstatetoself,filter,CLASS_ATTACHSTATETOSELF);
DEFINE_SUBSTANCE(filter_Attachstatetotarget,filter,CLASS_ATTACHSTATETOTARGET);
DEFINE_SUBSTANCE(filter_Immunephysical2,filter,CLASS_IMMUNEPHYSICAL2);
DEFINE_SUBSTANCE(filter_Immunemetal2,filter,CLASS_IMMUNEMETAL2);
DEFINE_SUBSTANCE(filter_Immunewood2,filter,CLASS_IMMUNEWOOD2);
DEFINE_SUBSTANCE(filter_Immunewater2,filter,CLASS_IMMUNEWATER2);
DEFINE_SUBSTANCE(filter_Immunefire2,filter,CLASS_IMMUNEFIRE2);
DEFINE_SUBSTANCE(filter_Immunesoil2,filter,CLASS_IMMUNESOIL2);
DEFINE_SUBSTANCE(filter_Retort2,filter,CLASS_RETORT2);
DEFINE_SUBSTANCE(filter_Addattackdefenddegree,filter,CLASS_ADDATTACKDEFENDDEGREE);
DEFINE_SUBSTANCE(filter_Chariotform,filter,CLASS_CHARIOTFORM);
DEFINE_SUBSTANCE(filter_Palsy, filter, CLASS_PALSY);
DEFINE_SUBSTANCE(filter_Apgencont2 ,filter,CLASS_APGENCONT2);
DEFINE_SUBSTANCE(filter_Inchurtfromskill,filter,CLASS_INCHURTFROMSKILL);
DEFINE_SUBSTANCE(filter_Incbecritrate,filter,CLASS_INCBECRITRATE);
DEFINE_SUBSTANCE(filter_Modifyspecskillpray,filter,CLASS_MODIFYSPECSKILLPRAY);
DEFINE_SUBSTANCE(filter_Incspecskilldamage,filter,CLASS_INCSPECSKILLDAMAGE);
DEFINE_SUBSTANCE(filter_Fireshield2,filter,CLASS_FIRESHIELD2);
DEFINE_SUBSTANCE(filter_Iceshield2,filter,CLASS_ICESHIELD2);
DEFINE_SUBSTANCE(filter_Healshield,filter,CLASS_HEALSHIELD);
DEFINE_SUBSTANCE(filter_Incflyspeed, filter, CLASS_INCFLYSPEED);
DEFINE_SUBSTANCE(filter_Incvigour, filter, CLASS_INCVIGOUR);
DEFINE_SUBSTANCE(filter_Minecarprotect, filter, CLASS_MINECARPROTECT);
DEFINE_SUBSTANCE(filter_Incvigour2, filter, CLASS_INCVIGOUR2);
DEFINE_SUBSTANCE(filter_Shortjump, filter, CLASS_SHORTJUMP);
DEFINE_SUBSTANCE(filter_Shortjump2, filter, CLASS_SHORTJUMP2);
DEFINE_SUBSTANCE(filter_Movepunish, filter, CLASS_MOVEPUNISH);
DEFINE_SUBSTANCE(filter_Standpunish, filter, CLASS_STANDPUNISH);
DEFINE_SUBSTANCE(filter_Standpunish2, filter, CLASS_STANDPUNISH2);
DEFINE_SUBSTANCE(filter_Chantshield, filter, CLASS_CHANTSHIELD);
DEFINE_SUBSTANCE(filter_Intervalpalsy, filter, CLASS_INTERVALPALSY);
DEFINE_SUBSTANCE(filter_Internalinjury, filter, CLASS_INTERNALINJURY);
DEFINE_SUBSTANCE(filter_Atkdamagereduce, filter, CLASS_ATKDAMAGEREDUCE);
DEFINE_SUBSTANCE(filter_Deathresetcd, filter, CLASS_DEATHRESETCD);
DEFINE_SUBSTANCE(filter_Appendenchant, filter, CLASS_APPENDENCHANT);
DEFINE_SUBSTANCE(filter_Appenddamage, filter, CLASS_APPENDDAMAGE);
DEFINE_SUBSTANCE(filter_Cooldownaward, filter, CLASS_COOLDOWNAWARD);
DEFINE_SUBSTANCE(filter_Huntersoul, filter, CLASS_HUNTERSOUL);
DEFINE_SUBSTANCE(filter_Changeselfaggro, filter, CLASS_CHANGESELFAGGRO);
DEFINE_SUBSTANCE(filter_Neverdead, filter, CLASS_NEVERDEAD);
DEFINE_SUBSTANCE(filter_Changemodel, filter, CLASS_CHANGEMODEL);
DEFINE_SUBSTANCE(filter_Screeneffect, filter, CLASS_SCREENEFFECT);
DEFINE_SUBSTANCE(filter_Shadowform, filter, CLASS_SHADOWFORM);
DEFINE_SUBSTANCE(filter_Fairyform, filter, CLASS_FAIRYFORM);
DEFINE_SUBSTANCE(filter_Addfrosteffect, filter, CLASS_ADDFROSTEFFECT);
DEFINE_SUBSTANCE(filter_Incspecskillcrit, filter, CLASS_INCSPECSKILLCRIT);
DEFINE_SUBSTANCE(filter_Moongod, filter, CLASS_MOONGOD);
DEFINE_SUBSTANCE(filter_Delayskilleffect, filter, CLASS_DELAYSKILLEFFECT);
DEFINE_SUBSTANCE(filter_Enhanceskilldamage3, filter, CLASS_ENHANCESKILLDAMAGE3);
DEFINE_SUBSTANCE(filter_Critdamagereduce, filter, CLASS_CRITDAMAGEREDUCE);
DEFINE_SUBSTANCE(filter_Incphysicaldamage, filter, CLASS_INCPHYSICALDAMAGE);
DEFINE_SUBSTANCE(filter_Incmagicaldamage, filter, CLASS_INCMAGICALDAMAGE);
DEFINE_SUBSTANCE(filter_Cooldownpunish, filter, CLASS_COOLDOWNPUNISH);
DEFINE_SUBSTANCE(filter_Anticlearbuf, filter, CLASS_ANTICLEARBUF);
DEFINE_SUBSTANCE(filter_Incenchantrange, filter, CLASS_INCENCHANTRANGE);
DEFINE_SUBSTANCE(filter_Incphysicalmagicaldefense, filter, CLASS_INCPHYSICALMAGICALDEFENSE);
DEFINE_SUBSTANCE(filter_Reducegold3, filter, CLASS_REDUCEGOLD3);
DEFINE_SUBSTANCE(filter_Reducewater3, filter, CLASS_REDUCEWATER3);
DEFINE_SUBSTANCE(filter_Genhpap, filter, CLASS_GENHPAP);
DEFINE_SUBSTANCE(filter_Detaindart,filter,CLASS_DETAINDART);
DEFINE_SUBSTANCE(filter_Extraexpfactor, filter, CLASS_EXTRAEXPFACTOR);
DEFINE_SUBSTANCE(filter_Weakenbless2,filter,CLASS_WEAKENBLESS2);
DEFINE_SUBSTANCE(filter_solo_IncAttackAndMagic,filter,CLASS_SOLO_INCATTACKANDMAGIC);
DEFINE_SUBSTANCE(filter_solo_Incdefence, filter, CLASS_SOLO_INCDEFENCE);
DEFINE_SUBSTANCE(filter_solo_Enhanceresist, filter, CLASS_SOLO_ENHANCERESIST);
DEFINE_SUBSTANCE(filter_solo_IncMaxhp, filter, CLASS_SOLO_INCMAXHP);
DEFINE_SUBSTANCE(filter_solo_invincible,filter,CLASS_SOLO_INVINCIBLE);
DEFINE_SUBSTANCE(filter_solo_Hpgen, filter, CLASS_SOLO_HPGEN);
DEFINE_SUBSTANCE(filter_solo_Dechurt, filter, CLASS_SOLO_DECHURT);
DEFINE_SUBSTANCE(filter_solo_Addattackrange, filter, CLASS_SOLO_ADDATTACKRANGE);
DEFINE_SUBSTANCE(filter_Thunder3, filter, CLASS_THUNDER3);
DEFINE_SUBSTANCE(filter_Toxic3, filter, CLASS_TOXIC3);
DEFINE_SUBSTANCE(filter_Flood3, filter, CLASS_FLOOD3);
DEFINE_SUBSTANCE(filter_Burning3, filter, CLASS_BURNING3);
DEFINE_SUBSTANCE(filter_Fallen3, filter, CLASS_FALLEN3);
DEFINE_SUBSTANCE(filter_ReduceSpeeddebuff,filter,CLASS_REDUCESPEEDDDEBUFF); // Paladino
DEFINE_SUBSTANCE(filter_Shattereddream,filter,CLASS_NEWBUFFTELEPORT); // Paladino
DEFINE_SUBSTANCE(filter_ShieldNew1,filter,CLASS_SHIELDBUFFNEW1); // Paladino 1
DEFINE_SUBSTANCE(filter_ShieldNew2,filter,CLASS_SHIELDBUFFNEW2); // Paladino 2  
DEFINE_SUBSTANCE(filter_NewBuffSpeed,filter,CLASS_NEWBUFFSPEED); // Speed
DEFINE_SUBSTANCE(filter_IraAtiradora,filter,CLASS_IRAATIRADORA); // IRA
DEFINE_SUBSTANCE(filter_GeloAtiradora,filter,CLASS_GELOATIRADORA); // GELO
DEFINE_SUBSTANCE(filter_FeAtiradora,filter,CLASS_FEATIRADORA); // FE
DEFINE_SUBSTANCE(filter_SetRemoveNew,filter,CLASS_SETREMOVENEW); // NEW
DEFINE_SUBSTANCE(filter_AccumulateAttack ,filter,CLASS_ACCUMULATEATTACK); //UltWR 
DEFINE_SUBSTANCE(filter_AccumulateAttack2 ,filter,CLASS_ACCUMULATEATTACK2); //UltMG 
DEFINE_SUBSTANCE(filter_DecRegionDMG ,filter,CLASS_DECREGIONDMG); //CuraWF
DEFINE_SUBSTANCE(filter_IncAntiDefenseDegree,filter,CLASS_INCANTIDEFENSEDEGREE); //UltEA
DEFINE_SUBSTANCE(filter_IncPlusMaxHP,filter,CLASS_INCPLUSMAXHP); //UltEP
DEFINE_SUBSTANCE(filter_Auracurse4asn,filter,CLASS_AURACURSE4ASN); //UltMC
DEFINE_SUBSTANCE(filter_Incmagic4,filter,CLASS_INCMAGIC4); //UltESP
DEFINE_SUBSTANCE(filter_Decsoul,filter,CLASS_DECSOUL); //UltESP
DEFINE_SUBSTANCE(filter_Giantform,filter,CLASS_GIANTFORM); //UltSK
DEFINE_SUBSTANCE(filter_Transdmg2pet,filter,CLASS_TRANSDMG2PET); //UltMS
DEFINE_SUBSTANCE(filter_DecRegionDMG2 ,filter,CLASS_DECREGIONDMG2);
DEFINE_SUBSTANCE(filter_Loaddmg4master ,filter,CLASS_LOADDMG4MASTER);
DEFINE_SUBSTANCE(filter_Decfardmg ,filter,CLASS_DECFARDMG);
DEFINE_SUBSTANCE(filter_Decphysicalmagicaldefense ,filter,CLASS_DECPHYSICALMAGICALDEFENSE);
DEFINE_SUBSTANCE(filter_MagicFrenetic ,filter,CLASS_MAGICFRENETIC);
DEFINE_SUBSTANCE(filter_Decheal ,filter,CLASS_DECHEAL);

DEFINE_SUBSTANCE(filter_Decphysicalmagicaldefense2 ,filter,CLASS_DECPHYSICALMAGICALDEFENSE2);
DEFINE_SUBSTANCE(filter_Incsmitedamage ,filter,CLASS_INCSMITEDAMAGE);
DEFINE_SUBSTANCE(filter_Fastpray3,filter,CLASS_FASTPRAY3);
DEFINE_SUBSTANCE(filter_Incdebuffdodge2,filter,CLASS_INCDEBUFFDODGE2);
DEFINE_SUBSTANCE(filter_Incdamagedodge2,filter,CLASS_INCDAMAGEDODGE2);
DEFINE_SUBSTANCE(filter_Debithurt,filter,CLASS_DEBITHURT);
DEFINE_SUBSTANCE(filter_Healnurse,filter,CLASS_HEALNURSE);

DEFINE_SUBSTANCE(filter_Activateskill2 ,filter,CLASS_ACTIVATESKILL2);
// Nova Torre
DEFINE_SUBSTANCE(filter_solo_IncAttackLevel, filter, CLASS_SOLO_ADDATTACKDEGREE);
DEFINE_SUBSTANCE(filter_solo_IncDefenseLevel, filter, CLASS_SOLO_ADDDEFENCEDEGREE);

DEFINE_SUBSTANCE(filter_UltimatePaladin, filter, CLASS_ULTIMATEPALADIN);
DEFINE_SUBSTANCE(filter_AttackplusAtr, filter, CLASS_ATTACKPLUSATR);
DEFINE_SUBSTANCE(filter_AddPraga, filter, CLASS_ADDPRAGA);
DEFINE_SUBSTANCE(filter_skillplusAtr, filter, CLASS_SKILLPLUSATR);
DEFINE_SUBSTANCE(filter_Shattereddream2,filter,CLASS_NEWBUFFTELEPORT2); // Paladino

// Novos Versos Sombrios

DEFINE_SUBSTANCE(filter_SetVersoSombrio01 ,filter,CLASS_VERSOPALADIN01);
DEFINE_SUBSTANCE(filter_SetVersoSombrio02 ,filter,CLASS_VERSOPALADIN02);
DEFINE_SUBSTANCE(filter_SetVersoSombrio03 ,filter,CLASS_VERSOPALADIN03);
DEFINE_SUBSTANCE(filter_SetVersoSombrio04 ,filter,CLASS_VERSOPALADIN04);
DEFINE_SUBSTANCE(filter_SetVersoSombrio05 ,filter,CLASS_VERSOPALADIN05);
DEFINE_SUBSTANCE(filter_SetVersoSombrio06 ,filter,CLASS_VERSOPALADIN06);


DEFINE_SUBSTANCE(filter_Retort3,filter,CLASS_RETORT3);
DEFINE_SUBSTANCE(filter_Elflock ,filter,CLASS_ELFLOCK);
DEFINE_SUBSTANCE(filter_Sleep2 ,filter, CLASS_SLEEP2);

DEFINE_SUBSTANCE(filter_Othergold, filter, CLASS_OTHERGOLD);
DEFINE_SUBSTANCE(filter_Otherwood, filter, CLASS_OTHERWOOD);
DEFINE_SUBSTANCE(filter_Otherwater, filter, CLASS_OTHERWATER);
DEFINE_SUBSTANCE(filter_Otherfire, filter, CLASS_OTHERFIRE);
DEFINE_SUBSTANCE(filter_Othersoil, filter, CLASS_OTHERSOIL);
DEFINE_SUBSTANCE(filter_Otherrange, filter, CLASS_OTHERRANGE);
DEFINE_SUBSTANCE(filter_Otherdamage, filter, CLASS_OTHERDAMAGE);
DEFINE_SUBSTANCE(filter_Othercooldown, filter, CLASS_OTHERCOOLDOWN);
DEFINE_SUBSTANCE(filter_Otherprayspeed, filter, CLASS_OTHERPRAYSPEED);

//++++++++++++++172+++++++++++++++++++

DEFINE_SUBSTANCE(filter_FastswimPassive ,filter,CLASS_FASTSWIMPASSIVE);	 
DEFINE_SUBSTANCE(filter_AuracurseMonkey,filter,CLASS_AURACURSEMONKEY);

DEFINE_SUBSTANCE(filter_Monkeyform ,filter,CLASS_MONKEYFORM);
DEFINE_SUBSTANCE(filter_MonkeyformUltimate ,filter,CLASS_MONKEYFORMULTI);
DEFINE_SUBSTANCE(filter_Marcadovento,filter,CLASS_MARCADOVENTO); // Marca 01
DEFINE_SUBSTANCE(filter_Marcadafloresta,filter,CLASS_MARCADAFLORESTA); // Marca 02
DEFINE_SUBSTANCE(filter_Marcadofogo,filter,CLASS_MARCADOFOGO); // Marca 03
DEFINE_SUBSTANCE(filter_Marcadamontanha,filter,CLASS_MARCADAMONTANHA); // Marca 04

DEFINE_SUBSTANCE(filter_MarcaYin,filter,CLASS_MARCAYIN); // Marca Yin
DEFINE_SUBSTANCE(filter_MarcaYang,filter,CLASS_MARCAYANG); // Marca Yin

DEFINE_SUBSTANCE(filter_FreemoveMonkey ,filter,CLASS_FREEMOVEMONKEY);
DEFINE_SUBSTANCE(filter_MovimentodasMaos ,filter,CLASS_MOVIMENTODASMAOS);
DEFINE_SUBSTANCE(filter_ShattereddreamMonkey,filter,CLASS_SHATTEREDDREAMMONKEY); // Andarilho Pulo
DEFINE_SUBSTANCE(filter_FeMonkey,filter,CLASS_FEMONKEY); // FE
DEFINE_SUBSTANCE(filter_ComboMonkey,filter,CLASS_COMBOMONKEY); // Combo 01
DEFINE_SUBSTANCE(filter_ComboYinYang,filter,CLASS_COMBOYINYANG); // Combo 02
DEFINE_SUBSTANCE(filter_ComboYinYang2,filter,CLASS_COMBOYINYANG2); // Combo 03

DEFINE_SUBSTANCE(filter_ReduzDanoaDistancia,filter,CLASS_REDUZDANOADISTANCIA); // Reduz dano a distância
DEFINE_SUBSTANCE(filter_InvincibleMonkeyNew,filter,CLASS_INVICIBLEMONKEYNEW);
DEFINE_SUBSTANCE(filter_IncCritReduce2,filter,CLASS_INCCRITREDUCE2);

// Passiva 

DEFINE_SUBSTANCE(filter_IncsformmonkeyDefense ,filter,CLASS_MONKEYDEFENSE);

// New Atiradora 

DEFINE_SUBSTANCE(filter_ArmadilhaPvP,filter,CLASS_ARMADILHAPVP); 

// Novas Habilidades 1.6.6 >

DEFINE_SUBSTANCE(filter_IncAtkFToDefense ,filter,CLASS_INCATTACKTODEFMF);
DEFINE_SUBSTANCE(filter_IncNewShieldMage ,filter,CLASS_INCNEWSHIELDMAGE);
DEFINE_SUBSTANCE(filter_IncNewShieldMage2 ,filter,CLASS_INCNEWSHIELDMAGE2);
DEFINE_SUBSTANCE(filter_SetNewShieldMage ,filter,CLASS_SETNEWSHIELDMAGE);
DEFINE_SUBSTANCE(filter_SetBuffAtiradora ,filter,CLASS_NEWBUFFATIRADORA);
DEFINE_SUBSTANCE(filter_SetBuffPaladin ,filter,CLASS_NEWBUFFPALADIN);

DEFINE_SUBSTANCE(filter_ReduceDefensePassive ,filter,CLASS_REDUCEDEFENSEPASSIVE);



void filter_Tigerform::OnAttach()
{
	_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
	_parent.LockEquipment(true);
	_parent.EnhanceScaleMaxHP(_inchp);
	_parent.EnhanceSpeed(_incspeed);
	_parent.EnhanceScaleDamage(_decattack);
	_parent.UpdateSpeedData();
	_parent.UpdateAttackData();
	_parent.ChangeShape(_shape|(FORM_CLASS<<6));
	_parent.SendClientCurSpeed();
	_parent.InsertTeamVisibleState(HSTATE_TIGERFORM,-1);
}

void filter_Tigerform::OnRelease()
{
	_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
	_parent.LockEquipment(false);
	_parent.ImpairScaleMaxHP(_inchp);
	_parent.ImpairSpeed(_incspeed);
	_parent.ImpairScaleDamage(_decattack);
	_parent.UpdateSpeedData();
	_parent.UpdateAttackData();
	_parent.ChangeShape(0);
	_parent.SendClientCurSpeed();
	_parent.RemoveTeamVisibleState(HSTATE_TIGERFORM);
}

void filter_Foxform::OnAttach()
{
	_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
	_parent.LockEquipment(true);
	_parent.ImpairScaleMaxMP(_decmp);
	_parent.EnhanceScaleDefense(_incdefence);
	_parent.EnhanceScaleAttack(_incaccuracy);
	_parent.UpdateDefenseData();
	_parent.UpdateAttackData();
	_parent.ChangeShape(_shape|(FORM_CLASS<<6));
	_parent.InsertTeamVisibleState(HSTATE_FOXFORM,-1);
}

void filter_Foxform::OnRelease()
{
	_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
	_parent.LockEquipment(false);
	_parent.EnhanceScaleMaxMP(_decmp);
	_parent.ImpairScaleDefense(_incdefence);
	_parent.ImpairScaleAttack(_incaccuracy);
	_parent.UpdateDefenseData();
	_parent.UpdateAttackData();
	_parent.ChangeShape(0);
	_parent.RemoveTeamVisibleState(HSTATE_FOXFORM);
}

void filter_Swiftform::OnAttach()
{
	_parent.EnhanceSpeed(_incspeed);
	_parent.UpdateSpeedData();
	_parent.SendClientCurSpeed();
	_parent.InsertTeamVisibleState(HSTATE_SWIFTFORM,-1);
	_parent.IncVisibleState(VSTATE_FOXFORM);
}

void filter_Swiftform::OnRelease()
{
	_parent.ImpairSpeed(_incspeed);
	_parent.UpdateSpeedData();
	_parent.SendClientCurSpeed();
	_parent.RemoveTeamVisibleState(HSTATE_SWIFTFORM);
	_parent.DecVisibleState(VSTATE_FOXFORM);
}

void filter_Cannonform::OnAttach() // Atiradora
{
	_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
	_parent.LockEquipment(true);
	_parent.EnhanceScaleDamage(_decattack);
	_parent.EnhanceAttackRange(_range);
	_parent.UpdateSpeedData();
	_parent.UpdateAttackData();
	_parent.ChangeShape(_shape|(FORM_CLASS<<6));
	_parent.InsertTeamVisibleState(HSTATE_CANNONFORM,-1);

	_parent.SetNoFly(true);
	_parent.SetNoMount(true);
	_parent.SetNoLongJump(true);
	_parent.SetNoSpeedUp(true);
	_parent.SetNoInvisible(true);

	_parent.DenyPetCmd(); // No use pet
	_parent.DenyElfSkillCmd(); // No use daimon
	_parent.DenyUseItemCmd(); // No use itens
	_parent.DenyNormalAttackCmd(); // No use attack normal

	_parent.GetNoInvisible(); // No invisible
	// No Move
	_parent.IncIdleSealMode(MODE_INDEX_ROOT);

}

void filter_Cannonform::OnRelease() // Atiradora
{
	_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
	_parent.LockEquipment(false);
	_parent.ImpairScaleDamage(_decattack);
	_parent.ImpairAttackRange(_range);
	_parent.UpdateSpeedData();
	_parent.UpdateAttackData();
	_parent.ChangeShape(0);
	_parent.RemoveTeamVisibleState(HSTATE_CANNONFORM);

	_parent.SetNoFly(false);
	_parent.SetNoMount(false);
	_parent.SetNoLongJump(false);
	_parent.SetNoSpeedUp(false);
	_parent.SetNoInvisible(false);

	_parent.AllowPetCmd();
	_parent.AllowElfSkillCmd();
	_parent.AllowUseItemCmd();
	_parent.AllowNormalAttackCmd();

	// Move
	_parent.DecIdleSealMode(MODE_INDEX_ROOT);

}

void filter_Activateskill::TranslateSendAttack(const XID & target, attack_msg & msg)
{
	int sid = (_parent.GetSkillWrapper()).GetAsid(0);
	int level = (_parent.GetSkillWrapper()).GetAslevel(0);
	if(sid && msg.attached_skill.skill==0 && !(msg._attack_state&AT_STATE_AURA_AND_RETORT))	//����͹⻷�˺�������?
	{
		SkillKeeper skill = Skill::Create(sid);
		if(!skill)
			return;
		if(skill->GetRange().IsSelf())
		{
			PlayerWrapper   w_player(_parent,NULL,skill);
			skill->SetVictim(&w_player);
			skill->SetPerformerid(_parent.GetSelfID());
			skill->SetLevel( level );
			skill->StateAttack();
			if(w_player.GetProbability()>99)
				_parent.SendClientEnchantResult(_parent.GetSelfID(), sid, level, false, 0, msg.section);
		}
		else
		{
			bool send = true;
			if(skill->DoBless())
			{
				PlayerWrapper   w_player(_parent,NULL,skill);
				skill->SetVictim(&w_player);
				skill->SetLevel(level);
				skill->SetPerformerid(_parent.GetSelfID());
				skill->BlessMe();
				send = w_player.GetProbability() > 99;
			}
			if(send && skill->DoEnchant())
			{
				msg.attached_skill.skill = sid;
				msg.attached_skill.level = level;
			}
		}
	}
}

void filter_Activateskill2::TranslateSendAttack(const XID & target, attack_msg & msg)
{
	int sid = (_parent.GetSkillWrapper()).GetAsid(1);
	int level = (_parent.GetSkillWrapper()).GetAslevel(1);
	
	if(sid && !(msg._attack_state&AT_STATE_AURA_AND_RETORT))	//����͹⻷�˺������￿?
	{
		SkillKeeper skill = Skill::Create(sid);
		if(!skill)
			return;
		if(skill->GetRange().IsSelf())
		{
			PlayerWrapper   w_player(_parent,NULL,skill);
			skill->SetVictim(&w_player);
			skill->SetPerformerid(_parent.GetSelfID());
			skill->SetLevel( level );
			skill->StateAttack();
			if(w_player.GetProbability()>99)
				_parent.SendClientEnchantResult(_parent.GetSelfID(), sid, level, false, 0, msg.section);
		}
		else
		{
			bool send = true;
			if(skill->DoBless())
			{
				PlayerWrapper   w_player(_parent,NULL,skill);
				skill->SetVictim(&w_player);
				skill->SetLevel(level);
				skill->SetPerformerid(_parent.GetSelfID());
				skill->BlessMe();
				send = w_player.GetProbability() > 99;
			}
			if(send && skill->DoEnchant())
			{
				msg.infected_skill.skill = sid;
				msg.infected_skill.level = level;
			}
		}
	}
}

void filter_Activatereboundskill::AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
{
        #define ARS_XID 7050
		if(msg._attack_state & AT_STATE_AURA_AND_RETORT) return;          //���Է���⻷��?        
        if(rand()%100 >= _trigger_prob)	return;         //�жϸ���
		if(!_parent.TestCoolDown(ARS_XID)) return;

		//printf("filter_Activatereboundskill::AdjustDamage: attacker = %d , _period = %d , _lasttime = %d \n", attacker.id , _period , _lasttime );


		int now = _parent.GetSystime();
		if(!_period || _period + _lasttime <= now)
		{
			_lasttime = now;
			_parent.SetCoolDown(ARS_XID, _period * 1000 );
			int sid = _parent.GetSkillWrapper().GetAsid(2);
			int level = _parent.GetSkillWrapper().GetAslevel(2);
			SkillKeeper skill = Skill::Create(sid);
			if(!skill)
					return;
			if(skill->GetRange().IsSelf()) // баф на себя
			{
				PlayerWrapper   w_player(_parent,NULL,skill);
				skill->SetVictim(&w_player);
				skill->SetPerformerid(_parent.GetSelfID());
				skill->SetLevel( level );
				skill->StateAttack();
				if( !w_player.GetProbability() || rand()%100 < w_player.GetProbability())
				{
					_parent.SendClientEnchantResult(_parent.GetSelfID(), sid, level, false, 0, msg.section);
				}
				//printf("filter_Activatereboundskill::AdjustDamage: self_id=%d , skill_id=%d , level=%d , probality=%f \n", _parent.GetSelfID().id , sid, level, w_player.GetProbability());
			}
			else //баф на цель
			{
				enchant_msg	ret;
				memset(&ret,0,sizeof(ret));
				ret.attack_range  = msg.attack_range + 0.5f;
				ret.skill = sid;
				ret.skill_level = level;
				ret.helpful = 0;
				ret.force_attack = _parent.GetForceAttack();

				_parent.EnterCombatState();
				_parent.SetReboundState();
				_parent.Enchant(attacker, ret);	
			};
		}
};

void filter_RetortNewPaladin::AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
{
	//printf("filter_RetortNewPaladin::AdjustDamage: attacker = %d skill=%d \n", attacker.id, msg.attached_skill.skill);
	
	if (_ratio > 0)
	{
		if (msg.attached_skill.skill != 0 && attacker.IsPlayerClass()  && !(msg._attack_state & AT_STATE_ALL_RETORT)  )
		{
			enchant_msg	ret; //создаём параметр ответного удара
			memset(&ret,0,sizeof(ret));
			ret.attack_range  = msg.attack_range + 0.5;
			ret.skill = msg.attached_skill.skill;
			ret.skill_level = msg.attached_skill.level;
			ret.helpful = 0;
			ret.force_attack = _parent.GetForceAttack(); 

			_parent.EnterCombatState(); // наносим противнику ответный дебаф
			_parent.SetReboundState();
			_parent.DelayEnchant(attacker, ret, 10); 
			
			attack_msg * _amsg = (attack_msg *)&msg; //игнорируем атаку противника
			//_amsg->skill_id = 0;
			_amsg->attached_skill.skill = 0;
			_amsg->attached_skill.level = 0;
			
			--_ratio; // вычитаем количество отражений дебафов
		}
	}
	else
	{
		_is_deleted  = true;
	}
}

//++++++++++++++172+++++++++++++++++++

// New Monkey Skills

void filter_Monkeyform::OnAttach()
{
	_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
	_parent.LockEquipment(true);
	_parent.EnhanceSpeed(_incspeed);
	_parent.UpdateSpeedData();
	_parent.UpdateAttackData();
	_parent.ChangeShape(_shape|(FORM_CLASS<<6));
	_parent.SendClientCurSpeed();
	_parent.InsertTeamVisibleState(HSTATE_MONKEYFORM,-1);
}

void filter_Monkeyform::OnRelease()
{
	_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
	_parent.LockEquipment(false);
	_parent.ImpairSpeed(_incspeed);
	_parent.UpdateSpeedData();
	_parent.UpdateAttackData();
	_parent.ChangeShape(0);
	_parent.SendClientCurSpeed();
	_parent.RemoveTeamVisibleState(HSTATE_MONKEYFORM);
}

