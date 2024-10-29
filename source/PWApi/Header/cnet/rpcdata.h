//-----------------------------------------------------------------------------------------
//--C++ PWAPI (C) DEADRAKY 2022
//-----------------------------------------------------------------------------------------
#ifndef _RPCDATA_H_
#define _RPCDATA_H_

namespace GNET
{
#pragma pack(push, 1)
	class Protocol
	{
	public:
		size_t offt;
		size_t type;
	};

	struct A3DVECTOR
	{
		float x, y, z;
	};

	struct Octets
	{
		size_t offt;
		void* begin;
		void* end;
		size_t size;
		size_t len() { return (int)end - (int)begin; }
	};

	struct GRoleInventory
	{
		size_t offt;
		void* begin;
		void* end;
		void* end2;
	};

	struct RoleInfo
	{
		size_t offt;
		int roleid;
		char gender;
		char race;
		char occupation;
		char a1;
		int level1;
		int level2;
		Octets name;
		Octets custom_data;
		GRoleInventory equipment;
		int status;
		int delete_time;
		int create_time;
		int lastlogin_time;
		A3DVECTOR pos;
		int tag;
		Octets custom_status;
		Octets charactermode;
		int referrer_role;
		int cash_add;
		Octets reincarnation_data;
		Octets realm_data;
		Octets reserve1;
		Octets reserve2;
	};


	struct FactionOPRequest : public Protocol
	{
		size_t optype;
		size_t roleid;
		Octets params;
	};

	struct Response : public Protocol
	{
		Octets identity;
		Octets response;
		size_t use_token;
		Octets cli_fingerprint;
	};

	struct GamedataSend : public Protocol
	{
		Octets data;
	};


	struct CREARE_ROLE : public Protocol
	{
		size_t roleid;
		size_t localsid;
		RoleInfo roleinfo;
		Octets referid;
	};








#pragma pack(pop)
}
#endif