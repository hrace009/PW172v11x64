#ifndef __SKILL_TARGETWRAPPER_H
#define __SKILL_TARGETWRAPPER_H

#include "common/types.h"
#include "obj_interface.h"

namespace GNET
{

class TargetWrapper
{
public:
	object_interface* player;
	const XID	* xid;
	const A3DVECTOR * pos;

	int	size;
	TargetWrapper(object_interface* p = NULL, const XID * _xid=NULL, int _size=0)
		: player(p), xid(_xid), size(_size)
	{ }

	XID GetFocus()
	{
		if( xid && size > 0 )
			return *xid;
		return XID(-1,-1);
	}
public:
	bool SetValid(bool) { return false; }
	bool GetValid() { return NULL != xid && size > 0; }
	int  GetCls() { return player&&xid ? player->GetTargetClass(xid[0]) : -1 ;} 
	int  GetHp() { return player&&xid ? player->GetTargetHp(xid[0]) : -1 ;}
	int  GetMp() { return player&&xid ? player->GetTargetMp(xid[0]) : -1 ;}
	int  GetMaxhp() { return player&&xid ? player->GetTargetMaxhp(xid[0]) : -1 ;} 
	int  GetLevel() { return player&&xid ? player->GetTargetLevel(xid[0]) : -1 ;}
	int  GetId() { return player&&xid ? xid[0].id : -1; }
	A3DVECTOR GetPos() { return player&&xid ? player->GetTargetPos(xid[0]) : A3DVECTOR(0,0,0); }
};

}

#endif

