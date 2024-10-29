//---------------------------------------------------------------------------
//  онстанты
//---------------------------------------------------------------------------
#ifndef _CONFIG_H_
#define _CONFIG_H_

namespace CONFIG
{
    enum CONFIG : size_t
    {
#ifdef _WIN64
        IMAGEBASE = 0x140000000,
        SECTION_TEXT_BEGIN = 0x0000000140001000,
        SECTION_TEXT_END = 0x000000014108DFFF,
        SECTION_TEXT_SIZE = (SECTION_TEXT_END - SECTION_TEXT_BEGIN),

        SECTION_RDATA_BEGIN = 0x000000014108FD28,
        SECTION_RDATA_END = 0x000000014161CFFF,
        SECTION_RDATA_SIZE = (SECTION_RDATA_END - SECTION_RDATA_BEGIN),

        SECTION_IDATA_BEGIN = 0x000000014108E000,
        SECTION_IDATA_END = 0x000000014108FD20,
        SECTION_IDATA_SIZE = (SECTION_RDATA_END - SECTION_RDATA_BEGIN),

        BASE_ADDRES = 0x0000000141715C18,
        NEW_TRANSPORT_TAG = 0x00000001416230A8,
        EC_HOSTPLAYER = 0x01411AD510,
        EC_ELSEPLAYER = 0x014116D280,

        PIMP_ROLEID = 0x890,
        PIMP_TARGET_ID = 0x0A1C,
        PIMP_NPC_TARGET_ID = 0x18B8,
        PIMP_INVENTORY = 0x1B20,
        PIMP_LEVEL = 0x89C,

        PIMP_CUR_HP = 0x8A4,
        PIMP_CUR_MP = 0x8A8,
        PIMP_MAX_HP = 0x8FC,
        PIMP_MAX_MP = 0x900,

#else
        IMAGEBASE = 0x00400000,
        SECTION_TEXT_BEGIN = 0x00401000,
        SECTION_TEXT_END = 0x0111CFFF,
        SECTION_TEXT_SIZE = (SECTION_TEXT_END - SECTION_TEXT_BEGIN),

        SECTION_RDATA_BEGIN = 0x0111DE44,
        SECTION_RDATA_END = 0x0133BFFF,
        SECTION_RDATA_SIZE = (SECTION_RDATA_END - SECTION_RDATA_BEGIN),

        SECTION_IDATA_BEGIN = 0x0111D000,
        SECTION_IDATA_END = 0x0111DE40,
        SECTION_IDATA_SIZE = (SECTION_RDATA_END - SECTION_RDATA_BEGIN),

        BASE_ADDRES = 0x013FF5C8,
        NEW_TRANSPORT_TAG = 0x0133FD98,
        EC_HOSTPLAYER = 0x0119DDD0,
        EC_ELSEPLAYER = 0x0117D99C,

        PIMP_ROLEID = 0x718,
        PIMP_TARGET_ID = 0x8A4,
        PIMP_NPC_TARGET_ID = 0x154C,
        PIMP_INVENTORY = 0x1768,
        PIMP_LEVEL = 0x724,

        PIMP_CUR_HP = 0x72C,
        PIMP_CUR_MP = 0x730,
        PIMP_MAX_HP = 0x784,
        PIMP_MAX_MP = 0x788,
        


#endif
        VAL_ADDRESS = 0x00400000,
        ENABLE_LOG = 0, //включить запись логов
        
        PROTOCOL_END = 5290,
        GTITTLE_LEN = 16,
        GUILD_NAME_LEN = 16,
        COLOR_NAME_XID = 80300,
        COLOR_NAME_COUNT = 100,
        COLOR_FORCE_COUNT = 5,
        AUTOSWAP_MAX_SIZE = 64,
        MULTIGENDER_MASK = 2,
        NEW_PROPERTY_COUNT = 6,
        QUEST_NEW = 20u,
        QUEST_ADD = 10u,
        QUEST_DEF = 40u,

        MAX_MONEY = 2000000000u,
        MAX_MONEY_AUCTION = 40000000u,
        ID_NPC_REMOTE = 80088,
        ID_NPCSHOP = 80080,
        REFRESH_INS_TIMER = 300,
        ANTICHEAT_ENABLE = 0,

        RACE_COUNT = 5,
        CLS_COUNT = 14,
        MAX_ROLES_CREATE = 16,
        CREATE_NEW_CLASSES = 1,
        WARRIOR = 0,
        MAG = 1,
        SHAM = 2,
        DRUID = 3,
        OBOR = 4,
        ASSASIN = 5,
        LUK = 6,
        PRIST = 7,
        STRAJ = 8,
        MIST = 9,
        GHOST = 10,
        JNEC = 11,
        SHOOTER = 12,
        PALADIN = 13,
        MONKY = 14,
    };

#define TRANSPORT_TAGS { /*локации дл€ телепорта*/  \
        1,                                          \
        161,                                        \
        137,                                        \
        121,                                        \
        122,                                        \
        163,                                        \
        178,                                        \
        131,                                        \
        0                                           \
} 

#define FREE_ITEMS { /*отключить проверку на количество итемов в клиенте*/  \
        12979,                                      \
        36092,                                      \
        27728,                                      \
        27729,                                      \
        48178,                                      \
        48179,                                      \
        0                                           \
}


};

#endif