#ifndef __ONLINEGAME_COMMON_CHAT_DATA_H__
#define __ONLINEGAME_COMMON_CHAT_DATA_H__


#pragma pack(1)

namespace CHAT_S2C
{
	enum 
	{
		CHAT_EQUIP_ITEM,
		CHAT_GENERALCARD_COLLECTION,
		CHAT_AIPOLICY_VALUE,
        CHAT_PROPERTY_SCORE,
	};

	struct chat_equip_item
	{
		short cmd_id;
		int type;
		int expire_date;
		int proc_type;
		unsigned short content_length;
		char content[];
	};

	struct chat_generalcard_collection
	{
		short cmd_id;
		int card_id;
	};

	struct chat_aipolicy_value
	{
		short cmd_id;
		int mask;
		char val[];
	};

    struct chat_property_score
    {
        short cmd_id;
        char name[40];
        int cls;
        short level;
        int fighting_score;
        int viability_score;

        size_t state_num;
        unsigned short* state;
    };


}

namespace CHAT_C2S
{

	enum		//CHAT_CMD
	{
		CHAT_EQUIP_ITEM,
		CHAT_GENERALCARD_COLLECTION,
        CHAT_AIPOLICY_VALUE,
        CHAT_PROPERTY_SCORE,
	};

	struct chat_equip_item
	{
		short cmd_id;
		char where;
		short index;
	};

	struct chat_generalcard_collection
	{
		short cmd_id;
		int card_id;
	};

    struct chat_property_score
    {
        short cmd_id;
    };


}

#pragma pack()
#endif

