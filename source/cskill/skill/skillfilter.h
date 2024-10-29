#ifndef __SKILL_FILTER_H__
#define __SKILL_FILTER_H__

#include <climits>
#include <common/types.h>
#include <obj_interface.h>
#include <filter.h>
#include "sfilterdef.h"
#include "skillwrapper.h"
#include "statedef.h"

using namespace GNET;
//lgc
enum	//seal/idle mode ��_idle_seal_mode_counter�м���������
{
	MODE_INDEX_SLEEP	= 0,
	MODE_INDEX_STUN,	
	MODE_INDEX_ROOT,
	MODE_INDEX_SILENT,
};

#define IS_PHYSIC_ATTACK(attack_attr) ((attack_attr)==attack_msg::PHYSIC_ATTACK || (attack_attr)==attack_msg::PHYSIC_ATTACK_HIT_DEFINITE)

enum	//attack state��ϸ������actobject.h
{
	AT_STATE_ALL_RETORT 		= 0x6020,
	AT_STATE_AURA_AND_RETORT	= 0x7020,
};

class delayhurt_stub
{
protected:	
	XID _performer;
	attacker_info_t _pinfo;
	bool _invader;
	char _mode;

	virtual bool Save(archive & ar)
	{
		ar << _performer;
		ar.push_back(&_pinfo, sizeof(attacker_info_t));
		ar << _invader;
		ar << _mode;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		ar >> _performer;
		ar.pop_back(&_pinfo, sizeof(attacker_info_t));
		ar >> _invader;
		ar >> _mode;
		return true;
	}
public:	
	void SetUp(const XID& player, const attacker_info_t& info, char mode, bool invader)
	{
		_performer = player;
		_pinfo = info;
		_mode = mode;
		_invader = invader;
	}
};

class multicond_stub
{
protected:
	std::set<int> _conds;
	
	virtual bool Save(archive & ar)
	{
		int count = _conds.size();
		ar << count;	  
		for(std::set<int>::iterator iter = _conds.begin();
				iter != _conds.end(); ++iter)
		{
			ar << *iter;
		}
		return true;
	}
	virtual bool Load(archive & ar)
	{
		int count = 0;
		ar >> count;
		for(int n = 0; n < count; ++n)
		{
			int id = 0;
			ar >> id;
			_conds.insert(id);
		}
		return true;
	}
	void MergeCond(std::set<int>& cds)
	{
		_conds.insert(cds.begin(),cds.end()); 
	}

public:
	virtual ~multicond_stub() {}
	bool CheckCond(int id)
	{
		return _conds.find(id) != _conds.end();
	}
};

class filter_Incdefence : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incdefence(){}
public:
	DECLARE_SUBSTANCE(filter_Incdefence); 
	filter_Incdefence(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCDEFENCE;
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incdefence*>(f));
		filter_Incdefence* nf = (filter_Incdefence*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleDefense(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleDefense(_ratio);
			_parent.UpdateDefenseData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCDEFENCE);
			_parent.InsertTeamVisibleState(HSTATE_INCDEFENCE, _timeout);
		}
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCDEFENCE,_timeout);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		_parent.ImpairScaleDefense(_ratio);
		_parent.UpdateDefenseData();
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCDEFENCE);
	}

	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Incattack : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incattack(){}
public:
	DECLARE_SUBSTANCE(filter_Incattack); 
	filter_Incattack(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCATTACK;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incattack*>(f));
		filter_Incattack* nf = (filter_Incattack*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleDamage(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleDamage(_ratio);
			_parent.UpdateAttackData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCATTACK);
			_parent.InsertTeamVisibleState(HSTATE_INCATTACK, _timeout);
		}
		
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCATTACK,_timeout);
		_parent.EnhanceScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCATTACK);
		_parent.ImpairScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Incresist : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incresist(){}
public:
	DECLARE_SUBSTANCE(filter_Incresist); 
	filter_Incresist(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCRESIST;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCRESIST,_timeout);
		_parent.EnhanceScaleResistance(0, _ratio);
		_parent.EnhanceScaleResistance(1, _ratio);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.EnhanceScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCRESIST);
		_parent.ImpairScaleResistance(0, _ratio);
		_parent.ImpairScaleResistance(1, _ratio);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.ImpairScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}
};

class filter_Incmagic : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incmagic(){}
public:
	DECLARE_SUBSTANCE(filter_Incmagic); 
	filter_Incmagic(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCMAGIC;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incmagic*>(f));
		filter_Incmagic* nf = (filter_Incmagic*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleMagicDamage(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleMagicDamage(_ratio);
			_parent.UpdateMagicData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCMAGIC);
			_parent.InsertTeamVisibleState(HSTATE_INCMAGIC, _timeout);
		}
		
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCMAGIC,_timeout);
		_parent.EnhanceScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCMAGIC);
		_parent.ImpairScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Speedup : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Speedup(){}
public:
	DECLARE_SUBSTANCE(filter_Speedup); 
	filter_Speedup(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_SPEEDUP;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Speedup*>(f));
		filter_Speedup* nf = (filter_Speedup*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairSpeed(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceSpeed(_ratio);
			_parent.UpdateSpeedData();
			_parent.SendClientCurSpeed();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SPEEDUP);
			_parent.InsertTeamVisibleState(HSTATE_SPEEDUP, _timeout);
		}
		
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_SPEEDUP,_timeout);
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_SPEEDUP);
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Inchp : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Inchp(){}
public:
	DECLARE_SUBSTANCE(filter_Inchp); 
	filter_Inchp(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCHP;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCHP,_timeout);
		_parent.EnhanceScaleMaxHP(_ratio);
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Inchp*>(f));
		filter_Inchp* nf = (filter_Inchp*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleMaxHP(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleMaxHP(_ratio);
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCHP);
			_parent.InsertTeamVisibleState(HSTATE_INCHP, _timeout);
		}
		
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCHP);
		_parent.ImpairScaleMaxHP(_ratio);
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Incmp : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incmp(){}
public:
	DECLARE_SUBSTANCE(filter_Incmp); 
	filter_Incmp(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCMP;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCMP,_timeout);
		_parent.EnhanceScaleMaxMP(_ratio);
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incmp*>(f));
		filter_Incmp* nf = (filter_Incmp*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleMaxMP(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleMaxMP(_ratio);
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCMP);
			_parent.InsertTeamVisibleState(HSTATE_INCMP, _timeout);
		}
		
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCMP);
		_parent.ImpairScaleMaxMP(_ratio);
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Fastmpgen : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Fastmpgen(){}
public:
	DECLARE_SUBSTANCE(filter_Fastmpgen); 
	filter_Fastmpgen(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(r)
	{
		_filter_id = FILTER_FASTMPGEN;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_FASTMPGEN,_timeout);
		_parent.EnhanceMPGen(_point);
		_parent.UpdateHPMPGen();
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Fastmpgen*>(f));
		filter_Fastmpgen* nf = (filter_Fastmpgen*) f;
		_timeout = GetTimeOut(nf);
		if(_point!=nf->GetPoint())
		{
			_parent.ImpairMPGen(_point);
			_point = nf->GetPoint();
			_parent.EnhanceMPGen(_point);
			_parent.UpdateHPMPGen();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_FASTMPGEN);
			_parent.InsertTeamVisibleState(HSTATE_FASTMPGEN, _timeout);
		}
		
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_FASTMPGEN);
		_parent.ImpairMPGen(_point);
		_parent.UpdateHPMPGen();
	}
	int GetPoint()
	{
		return _point;
	}
};

class filter_Fasthpgen : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Fasthpgen(){}
public:
	DECLARE_SUBSTANCE(filter_Fasthpgen); 
	filter_Fasthpgen(object_interface  object,int inc,int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(inc)
	{
		_filter_id = FILTER_FASTHPGEN;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_FASTHPGEN,_timeout);
		_parent.EnhanceHPGen(_point);
		_parent.UpdateHPMPGen();
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Fasthpgen*>(f));
		filter_Fasthpgen* nf = (filter_Fasthpgen*) f;
		_timeout = GetTimeOut(nf);
		if(_point!=nf->GetPoint())
		{
			_parent.ImpairHPGen(_point);
			_point = nf->GetPoint();
			_parent.EnhanceHPGen(_point);
			_parent.UpdateHPMPGen();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_FASTHPGEN);
			_parent.InsertTeamVisibleState(HSTATE_FASTHPGEN, _timeout);
		}
		
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_FASTHPGEN);
		_parent.ImpairHPGen(_point);
		_parent.UpdateHPMPGen();
	}
	int GetPoint()
	{
		return _point;
	}
};

class filter_Incdodge : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incdodge(){}
public:
	DECLARE_SUBSTANCE(filter_Incdodge); 
	filter_Incdodge(object_interface  object,int inc,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(inc)
	{
		_filter_id = FILTER_INCDODGE;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCDODGE,_timeout);
		_parent.EnhanceScaleArmor(_ratio);
		_parent.UpdateDefenseData();
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incdodge*>(f));
		filter_Incdodge* nf = (filter_Incdodge*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleArmor(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleArmor(_ratio);
			_parent.UpdateDefenseData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCDODGE);
			_parent.InsertTeamVisibleState(HSTATE_INCDODGE, _timeout);
		}
		
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCDODGE);
		_parent.ImpairScaleArmor(_ratio);
		_parent.UpdateDefenseData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Decdefence : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Decdefence(){}
public:
	DECLARE_SUBSTANCE(filter_Decdefence); 
	filter_Decdefence(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_DECDEFENCE;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_CURSED);
		_parent.InsertTeamVisibleState(HSTATE_DECDEFENCE,_timeout);
		_parent.ImpairScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_CURSED);
		_parent.RemoveTeamVisibleState(HSTATE_DECDEFENCE);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Decattack : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Decattack(){}
public:
	DECLARE_SUBSTANCE(filter_Decattack); 
	filter_Decattack(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_DECATTACK;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_CURSED);
		_parent.InsertTeamVisibleState(HSTATE_DECATTACK,_timeout);
		_parent.ImpairScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_CURSED);
		_parent.RemoveTeamVisibleState(HSTATE_DECATTACK);
		_parent.EnhanceScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}
};

class filter_Decresist : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Decresist(){}
public:
	DECLARE_SUBSTANCE(filter_Decresist); 
	filter_Decresist(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_DECRESIST;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_CURSED);
		_parent.InsertTeamVisibleState(HSTATE_DECRESIST,_timeout);
		_parent.ImpairScaleResistance(0, _ratio);
		_parent.ImpairScaleResistance(1, _ratio);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.ImpairScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_CURSED);
		_parent.RemoveTeamVisibleState(HSTATE_DECRESIST);
		_parent.EnhanceScaleResistance(0, _ratio);
		_parent.EnhanceScaleResistance(1, _ratio);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.EnhanceScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}
};

class filter_Decmagic : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Decmagic(){}
public:
	DECLARE_SUBSTANCE(filter_Decmagic); 
	filter_Decmagic(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_DECMAGIC;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_CURSED);
		_parent.InsertTeamVisibleState(HSTATE_DECMAGIC,_timeout);
		_parent.ImpairScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_CURSED);
		_parent.RemoveTeamVisibleState(HSTATE_DECMAGIC);
		_parent.EnhanceScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}
};

class filter_Slow : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Slow(){}
public:
	DECLARE_SUBSTANCE(filter_Slow); 
	filter_Slow(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_SLOW;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_SLOW);
		_parent.InsertTeamVisibleState(HSTATE_SLOW,_timeout);
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_SLOW);
		_parent.RemoveTeamVisibleState(HSTATE_SLOW);
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Dechp : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Dechp(){}
public:
	DECLARE_SUBSTANCE(filter_Dechp); 
	filter_Dechp(object_interface  object,int r,int period,int mask=FILTER_MASK_DEBUFF|FILTER_MASK_TRANSFERABLE_DEBUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask),_ratio(r)
	{
		_filter_id = FILTER_DECHP;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_CURSED);
		_parent.InsertTeamVisibleState(HSTATE_DECHP,_timeout);
		_parent.ImpairScaleMaxHP(_ratio);
	}

	void OnRelease()
	{
		_parent.EnhanceScaleMaxHP(_ratio);
		_parent.DecVisibleState(VSTATE_CURSED);
		_parent.RemoveTeamVisibleState(HSTATE_DECHP);
	}
};

class filter_Decmp : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Decmp(){}
public:
	DECLARE_SUBSTANCE(filter_Decmp); 
	filter_Decmp(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_DECMP;
	}

	void OnAttach()
	{
		_parent.ImpairScaleMaxMP(_ratio);
	}

	void OnRelease()
	{
		_parent.EnhanceScaleMaxMP(_ratio);
	}
};

class filter_Decdodge : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	int _increment;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _increment;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _increment;
		return true;
	}
	filter_Decdodge(){}
public:
	DECLARE_SUBSTANCE(filter_Decdodge); 
	filter_Decdodge(object_interface  object,int inc,int period)
				        :timeout_filter(object,period,FILTER_MASK),_increment(inc)
	{
		_filter_id = FILTER_DECDODGE;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_CURSED);
		_parent.InsertTeamVisibleState(HSTATE_DECDODGE,_timeout);
		_parent.ImpairScaleArmor(_increment);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_CURSED);
		_parent.RemoveTeamVisibleState(HSTATE_DECDODGE);
		_parent.EnhanceScaleArmor(_increment);
		_parent.UpdateDefenseData();
	}
};

class filter_Sleep : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_DO_DAMAGE | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	filter_Sleep(){}
public:
	DECLARE_SUBSTANCE(filter_Sleep); 
	filter_Sleep(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SLEEP;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_SLEEP);
		_parent.IncVisibleState(VSTATE_SLEEP);
		_parent.InsertTeamVisibleState(HSTATE_SLEEP,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_SLEEP);
		_parent.DecVisibleState(VSTATE_SLEEP);
		_parent.RemoveTeamVisibleState(HSTATE_SLEEP);
	}

	void DoDamage(const damage_entry & dmg)
	{
		_is_deleted = true;
	}
};

class filter_Sealed : public timeout_filter   // �޷�����
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	filter_Sealed(){}
public:
	DECLARE_SUBSTANCE(filter_Sealed); 
	filter_Sealed(object_interface  object,int period, int mask=FILTER_MASK_DEBUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_SEALED;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_SILENT);
		_parent.IncVisibleState(VSTATE_SEALED);
		_parent.InsertTeamVisibleState(HSTATE_SEALED,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_SILENT);
		_parent.DecVisibleState(VSTATE_SEALED);
		_parent.RemoveTeamVisibleState(HSTATE_SEALED);
	}

};
class filter_Dizzy : public timeout_filter  // ����
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH
	};

	filter_Dizzy(){}
public:
	DECLARE_SUBSTANCE(filter_Dizzy); 
	filter_Dizzy(object_interface  object,int period,int mask = FILTER_MASK_DEBUFF|FILTER_MASK_TRANSFERABLE_DEBUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_DIZZY;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_STUN);
		_parent.IncVisibleState(VSTATE_DIZZY);
		_parent.InsertTeamVisibleState(HSTATE_DIZZY,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_STUN);
		_parent.DecVisibleState(VSTATE_DIZZY);
		_parent.RemoveTeamVisibleState(HSTATE_DIZZY);
	}
};

class filter_Fix : public timeout_filter // ����
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	filter_Fix(){}
public:
	DECLARE_SUBSTANCE(filter_Fix); 
	filter_Fix(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FIX;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_ROOT);
		_parent.IncVisibleState(VSTATE_FIX);
		_parent.InsertTeamVisibleState(HSTATE_FIX,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_ROOT);
		_parent.DecVisibleState(VSTATE_FIX);
		_parent.RemoveTeamVisibleState(HSTATE_FIX);
	}

};

class filter_Feathershield : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;
	float _cost;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _cost;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _cost;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		float dec = (int)(dmg.physic_damage * _ratio);
		int mp = _parent.GetBasicProp().mp;
		int cost = (int)(dec*_cost*damage_adjust);
		if(mp<=cost)
		{
			_is_deleted = true;
			cost = mp;
			dec = mp /_cost;
		}
		dmg.physic_damage -= dec;
		_parent.DrainMana(cost);
	}

	filter_Feathershield(){}
public:
	DECLARE_SUBSTANCE(filter_Feathershield); 
	filter_Feathershield(object_interface  object,float ratio, float cost, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FEATHERSHIELD;
		_ratio = ratio;
		_cost = cost;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_FEATHERSHIELD);
		_parent.InsertTeamVisibleState(HSTATE_FEATHERSHIELD,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_FEATHERSHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_FEATHERSHIELD);
	}

};

class filter_Slowpray : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Slowpray(){}
public:
	DECLARE_SUBSTANCE(filter_Slowpray); 
	filter_Slowpray(object_interface  object,int ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SLOWPRAY;
		_ratio = ratio;
	}

	void OnAttach()
	{
		(_parent.GetSkillWrapper()).IncPrayTime(_ratio);
		_parent.IncVisibleState(VSTATE_INFAUST);
		_parent.InsertTeamVisibleState(HSTATE_SLOWPRAY,_timeout);
	}

	void OnRelease()
	{
		(_parent.GetSkillWrapper()).DecPrayTime(_ratio);
		_parent.DecVisibleState(VSTATE_INFAUST);
		_parent.RemoveTeamVisibleState(HSTATE_SLOWPRAY);
	}
};

class filter_Retort : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Retort(){}
public:
	DECLARE_SUBSTANCE(filter_Retort); 
	filter_Retort(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_RETORT;
		_ratio = ratio;
	}

	void AdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg.physic_damage >= 1000000) return;//��ֹ���������boss��������
		int damage = (int)(msg.physic_damage * _ratio);
		if(msg.short_range>0 || !IS_PHYSIC_ATTACK(msg.attack_attr) || damage <= 1)	
			return;
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.physic_damage	= damage;
		ret.short_range = 0.1;
		ret.attack_rate	 = 1000;
		ret.force_attack = false;
		ret.attack_attr	= attack_msg::MAGIC_ATTACK;
		ret.attack_range = msg.attack_range + 0.5;
		ret.speed = msg.speed;
		_parent.SetRetortState();
		_parent.Attack( attacker, ret, 0);
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_RETORT);
		_parent.InsertTeamVisibleState(HSTATE_RETORT,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_RETORT);
		_parent.RemoveTeamVisibleState(HSTATE_RETORT);
	}
};

class filter_Blind : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}

	filter_Blind(){}
public:
	DECLARE_SUBSTANCE(filter_Blind); 
	filter_Blind(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_BLIND;
	}

	void OnAttach()
	{
		_parent.SetAggressive(false);
		_parent.IncVisibleState(VSTATE_BLIND);
		_parent.InsertTeamVisibleState(HSTATE_BLIND,_timeout);
	}

	void OnRelease()
	{
		_parent.SetAggressive(true);
		_parent.DecVisibleState(VSTATE_BLIND);
		_parent.RemoveTeamVisibleState(HSTATE_BLIND);
	}
};

class filter_Tardy : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Tardy(){}
public:
	DECLARE_SUBSTANCE(filter_Tardy); 
	filter_Tardy(object_interface  object,int ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_TARDY;
		_ratio = ratio;
	}

	void OnAttach()
	{
		_parent.ImpairScaleAttackSpeed(_ratio);
		_parent.UpdateAttackData();
		_parent.IncVisibleState(VSTATE_INFAUST);
		_parent.InsertTeamVisibleState(HSTATE_SLOWATTACK,_timeout);
	}

	void OnRelease()
	{
		_parent.EnhanceScaleAttackSpeed(_ratio);
		_parent.UpdateAttackData();
		_parent.DecVisibleState(VSTATE_INFAUST);
		_parent.RemoveTeamVisibleState(HSTATE_SLOWATTACK);
	}
};

class filter_Crazy : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Crazy(){}
public:
	DECLARE_SUBSTANCE(filter_Crazy); 
	filter_Crazy(object_interface  object,int ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_CRAZY;
		_ratio = ratio;
	}

	void OnAttach()
	{
		_parent.EnhanceScaleAttackSpeed(_ratio);
		_parent.UpdateAttackData();
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_FASTATTACK,_timeout);
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Crazy*>(f));
		filter_Crazy* nf = (filter_Crazy*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleAttackSpeed(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleAttackSpeed(_ratio);
			_parent.UpdateAttackData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_FASTATTACK);
			_parent.InsertTeamVisibleState(HSTATE_FASTATTACK, _timeout);
		}
		
	}

	void OnRelease()
	{
		_parent.ImpairScaleAttackSpeed(_ratio);
		_parent.UpdateAttackData();
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_FASTATTACK);
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Magicleak : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	int _damage;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damage;
		ar << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damage;
		ar >> _counter;
		return true;
	}
	filter_Magicleak(){}
public:
	DECLARE_SUBSTANCE(filter_Magicleak); 
	filter_Magicleak(object_interface  object,int damage, int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_MAGICLEAK;
		_counter = 0;
		_damage = damage/period;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_MAGICLEAK);
		_parent.InsertTeamVisibleState(HSTATE_MAGICLEAK,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_MAGICLEAK);
		_parent.RemoveTeamVisibleState(HSTATE_MAGICLEAK);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.DrainMana(_damage*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Decaccuracy : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Decaccuracy(){}
public:
	DECLARE_SUBSTANCE(filter_Decaccuracy); 
	filter_Decaccuracy(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_DECACCURACY;
	}

	void OnAttach()
	{
		_parent.ImpairScaleAttack(_ratio);
		_parent.UpdateAttackData();
		_parent.IncVisibleState(VSTATE_INFAUST);
		_parent.InsertTeamVisibleState(HSTATE_DECACCURACY,_timeout);
	}

	void OnRelease()
	{
		_parent.EnhanceScaleAttack(_ratio);
		_parent.UpdateAttackData();
		_parent.DecVisibleState(VSTATE_INFAUST);
		_parent.RemoveTeamVisibleState(HSTATE_DECACCURACY);
	}
};

class filter_Inchurt : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Inchurt(){}
public:
	DECLARE_SUBSTANCE(filter_Inchurt); 
	filter_Inchurt(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_INCHURT;
		_ratio = 1.0+ratio;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INFAUST);
		_parent.InsertTeamVisibleState(HSTATE_INCHURT,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INFAUST);
		_parent.RemoveTeamVisibleState(HSTATE_INCHURT);
	}
};

class filter_Iceblade : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Iceblade(){}
public:
	DECLARE_SUBSTANCE(filter_Iceblade); 
	filter_Iceblade(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_ICEBLADE;
		_ratio = ratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(IS_PHYSIC_ATTACK(msg.attack_attr))
		{
			const item_prop & weapon = _parent.GetCurWeapon();
			msg.magic_damage[2] += (int)(_ratio * 0.5 * (weapon.damage_low+weapon.damage_high));
		}
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_ICEBLADE);
		_parent.InsertTeamVisibleState(HSTATE_ICEBLADE,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_ICEBLADE);
		_parent.RemoveTeamVisibleState(HSTATE_ICEBLADE);
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Iceblade*>(f));
		filter_Iceblade* nf = (filter_Iceblade*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_ratio = nf->GetRatio();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_ICEBLADE);
			_parent.InsertTeamVisibleState(HSTATE_ICEBLADE, _timeout);
		}
		
	}
	float GetRatio()
	{
		return _ratio;
	}
};

class filter_Wounded : public timeout_filter
{
protected:
	int _damage;
	XID _performer;
	attacker_info_t _pinfo;
	char _counter;
	bool _invader;
	char _mode;
	short _icon;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damage;
		ar << _performer;
		ar << _counter;
		ar.push_back(&_pinfo, sizeof(attacker_info_t));
		ar << _invader;
		ar << _mode;
		ar << _icon;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damage;
		ar >> _performer;
		ar >> _counter;
		ar.pop_back(&_pinfo, sizeof(attacker_info_t));
		ar >> _invader;
		ar >> _mode;
		ar >> _icon;
		return true;
	}
	filter_Wounded(){}
public:
	filter_Wounded(object_interface  object,int period,int damage,int mask)
			:timeout_filter(object,period,mask)
	{
		_counter = 0;
		if(period == 0)
		{
			_damage  = 0;
			_timeout = 0;
		}
		else
		{
			_damage = damage/period;
			if(_damage<1)
				_damage = 1;
			_timeout = damage/_damage;
		}
	}

	void SetUp(const XID& player, const attacker_info_t& info, char mode, bool invader)
	{
		_performer = player;
		_pinfo = info;
		_mode = mode;
		_invader = invader;
	}

	void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.BeHurt(_performer, _pinfo, _damage*_counter, _invader, _mode);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Wounded*>(f));
		filter_Wounded* nf = (filter_Wounded*) f;

		int tmp = _damage * _timeout;
		_timeout = GetTimeOut(nf);
		tmp /= _timeout;
		_damage = nf->GetDamage() + (tmp?tmp:1);
		if(_damage < 1)
			_damage = 1;
		
		if (_timeout > 0 )
		{
			_parent.RemoveTeamVisibleState(_icon);
			_parent.InsertTeamVisibleState(_icon,_timeout);
		}
	}

	int GetDamage()
	{
		return _damage;
	}
};

class filter_Bleeding : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	filter_Bleeding(){}
public:
	DECLARE_SUBSTANCE(filter_Bleeding); 
	filter_Bleeding(object_interface  object,int period, int damage, int mask = 0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_BLEEDING_MERGE;
		else
			_filter_id = FILTER_BLEEDING;
		_icon = HSTATE_BLEEDING;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_BLEEDING);
		_parent.InsertTeamVisibleState(HSTATE_BLEEDING,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLEEDING);
		_parent.RemoveTeamVisibleState(HSTATE_BLEEDING);
	}
};

class filter_Frozen : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	filter_Frozen(){}
public:
	DECLARE_SUBSTANCE(filter_Frozen); 
	filter_Frozen(object_interface  object,int period, int damage, int mask = 0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_FROZEN_MERGE;
		else
			_filter_id = FILTER_FROZEN;
		_icon = HSTATE_FROZEN;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_FROZEN,_timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FROZEN);
	}
};

class filter_Fallen : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	filter_Fallen(){}
public:
	DECLARE_SUBSTANCE(filter_Fallen); 
	filter_Fallen(object_interface  object,int period, int damage, int mask=0)
			:filter_Wounded(object,period,damage, FILTER_MASK|mask)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_FALLEN_MERGE;
		else
			_filter_id = FILTER_FALLEN;
		_icon = HSTATE_FALLEN;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_FALLEN);
		_parent.InsertTeamVisibleState(HSTATE_FALLEN,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_FALLEN);
		_parent.RemoveTeamVisibleState(HSTATE_FALLEN);
	}
};


class filter_Toxic : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	filter_Toxic(){}
public:
	DECLARE_SUBSTANCE(filter_Toxic); 
	filter_Toxic(object_interface  object,int period,int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_TOXIC_MERGE;
		else
			_filter_id = FILTER_TOXIC;
		_icon = HSTATE_TOXIC;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_TOXIC);
		_parent.InsertTeamVisibleState(HSTATE_TOXIC,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_TOXIC);
		_parent.RemoveTeamVisibleState(HSTATE_TOXIC);
	}

	void  OnModify(int ctrlname,void * ctrlval,unsigned int ctrllen) 
	{ 
		if(ctrlname==FMID_ANTIDOTE)
			_damage /= 2;
		if(_damage<2) 
			_is_deleted = true;
	}
};

class filter_Thunder : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	filter_Thunder(){}
public:
	DECLARE_SUBSTANCE(filter_Thunder); 
	filter_Thunder(object_interface  object,int period, int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_THUNDER_MERGE;
		else
			_filter_id = FILTER_THUNDER;
		_icon = HSTATE_THUNDER;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_THUNDER);
		_parent.InsertTeamVisibleState(HSTATE_THUNDER,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_THUNDER);
		_parent.RemoveTeamVisibleState(HSTATE_THUNDER);
	}
};

class filter_Burning : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	filter_Burning(){}
public:
	DECLARE_SUBSTANCE(filter_Burning); 
	filter_Burning(object_interface  object,int period,int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_BURNING_MERGE;
		else
			_filter_id = FILTER_BURNING;
		_icon = HSTATE_BURNING;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_BURNING);
		_parent.InsertTeamVisibleState(HSTATE_BURNING,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BURNING);
		_parent.RemoveTeamVisibleState(HSTATE_BURNING);
	}
};


class filter_Activateskill : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_TRANSLATE_SEND_MSG  | FILTER_MASK_WEAK
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		return true;
	}
	filter_Activateskill(){}
public:
	DECLARE_SUBSTANCE(filter_Activateskill); 
	filter_Activateskill(object_interface  object)
			:filter(object,FILTER_MASK)
	{
		_filter_id = FILTER_ACTIVATESKILL;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg);

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}
};

class filter_Activateskill2 : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_TRANSLATE_SEND_MSG  | FILTER_MASK_WEAK
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		return true;
	}
	filter_Activateskill2(){}
public:
	DECLARE_SUBSTANCE(filter_Activateskill2); 
	filter_Activateskill2(object_interface  object)
			:filter(object,FILTER_MASK)
	{
		_filter_id = FILTER_ACTIVATESKILL2;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg);

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}
};

class filter_Activatereboundskill : public filter
{
        int _trigger_prob;
		int _period;
		int _lasttime;
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_ADJUST_DAMAGE  | FILTER_MASK_WEAK
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
                ar << _trigger_prob;
				ar << _period;
				ar << _lasttime;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
                ar >> _trigger_prob;
				ar >> _period;
				ar >> _lasttime;
		return true;
	}
	filter_Activatereboundskill(){}
public:
	DECLARE_SUBSTANCE(filter_Activatereboundskill); 
	filter_Activatereboundskill(object_interface  object, int trigger_prob, int period)
			:filter(object,FILTER_MASK), _trigger_prob(trigger_prob), _period(period)
	{
		_filter_id = FILTER_ACTIVATESKILL;
		_lasttime = 0;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust);
	void OnAttach()
	{
	}

	void OnRelease()
	{
	}
};

class filter_Frenetic : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_TRANSLATE_SEND_MSG  | FILTER_MASK_WEAK
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _ratio;
		ar << _probability;
		ar << _hurt;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _ratio;
		ar >> _probability;
		ar >> _hurt;
		return true;
	}

	float _probability;
	float _ratio;
	int _hurt;

	filter_Frenetic(){}
public:
	DECLARE_SUBSTANCE(filter_Frenetic); 
	filter_Frenetic(object_interface  object, float probability, float ratio, float hurt)
			:filter(object,FILTER_MASK), _probability(probability), _ratio(ratio)
	{
		_filter_id = FILTER_FRENETIC;
		_hurt = (int)(_parent.GetExtendProp().max_hp * hurt);
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(IS_PHYSIC_ATTACK(msg.attack_attr) && (rand()%100)<=_probability)
		{
			if(_parent.GetBasicProp().hp>_hurt)
			{
				_parent.DecHP(_hurt);
				msg.physic_damage = (int)(msg.physic_damage*_ratio);
				msg.magic_damage[0] = (int)(msg.magic_damage[0]*_ratio);
				msg.magic_damage[1] = (int)(msg.magic_damage[1]*_ratio);
				msg.magic_damage[2] = (int)(msg.magic_damage[2]*_ratio);
				msg.magic_damage[3] = (int)(msg.magic_damage[3]*_ratio);
				msg.magic_damage[4] = (int)(msg.magic_damage[4]*_ratio);
				_parent.SendClientEnchantResult(_parent.GetSelfID(), 146, 1, false, 0, 0);
			}
		}
	}

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}
};

class filter_Toxicblade : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Toxicblade(){}
public:
	DECLARE_SUBSTANCE(filter_Toxicblade); 
	filter_Toxicblade(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_TOXICBLADE;
		_ratio = ratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(IS_PHYSIC_ATTACK(msg.attack_attr))
		{
			const item_prop & weapon = _parent.GetCurWeapon();
			msg.magic_damage[1] += (int)(_ratio * 0.5 * (weapon.damage_low+weapon.damage_high));
		}
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_TOXICBLADE,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_TOXICBLADE);
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Toxicblade*>(f));
		filter_Toxicblade* nf = (filter_Toxicblade*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_ratio = nf->GetRatio();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_TOXICBLADE);
			_parent.InsertTeamVisibleState(HSTATE_TOXICBLADE, _timeout);
		}
		
	}
	float GetRatio()
	{
		return _ratio;
	}
};

class filter_Enhancegold : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Enhancegold(){}
public:
	DECLARE_SUBSTANCE(filter_Enhancegold); 
	filter_Enhancegold(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_ENHANCEGOLD;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ENHANCEGOLD,_timeout);
		_parent.EnhanceScaleResistance(0, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ENHANCEGOLD);
		_parent.ImpairScaleResistance(0, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Enhancesoil : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Enhancesoil(){}
public:
	DECLARE_SUBSTANCE(filter_Enhancesoil); 
	filter_Enhancesoil(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_ENHANCESOIL;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ENHANCESOIL,_timeout);
		_parent.EnhanceScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ENHANCESOIL);
		_parent.ImpairScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};
class filter_Enhancewood : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Enhancewood(){}
public:
	DECLARE_SUBSTANCE(filter_Enhancewood); 
	filter_Enhancewood(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_ENHANCEWOOD;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ENHANCEWOOD,_timeout);
		_parent.EnhanceScaleResistance(1, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ENHANCEWOOD);
		_parent.ImpairScaleResistance(1, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};
class filter_Enhancewater : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Enhancewater(){}
public:
	DECLARE_SUBSTANCE(filter_Enhancewater); 
	filter_Enhancewater(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_ENHANCEWATER;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ENHANCEWATER,_timeout);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ENHANCEWATER);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};
class filter_Enhancefire : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Enhancefire(){}
public:
	DECLARE_SUBSTANCE(filter_Enhancefire); 
	filter_Enhancefire(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_ENHANCEFIRE;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ENHANCEFIRE,_timeout);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.RemoveTeamVisibleState(HSTATE_ENHANCEFIRE);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Reducegold : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Reducegold(){}
public:
	DECLARE_SUBSTANCE(filter_Reducegold); 
	filter_Reducegold(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_REDUCEGOLD;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCEGOLD,_timeout);
		_parent.ImpairScaleResistance(0, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCEGOLD);
		_parent.EnhanceScaleResistance(0, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Reducewood : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Reducewood(){}
public:
	DECLARE_SUBSTANCE(filter_Reducewood); 
	filter_Reducewood(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_REDUCEWOOD;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCEWOOD,_timeout);
		_parent.ImpairScaleResistance(1, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCEWOOD);
		_parent.EnhanceScaleResistance(1, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};
class filter_Reducewater : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Reducewater(){}
public:
	DECLARE_SUBSTANCE(filter_Reducewater); 
	filter_Reducewater(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_REDUCEWATER;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCEWATER,_timeout);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCEWATER);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};
class filter_Reducefire : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Reducefire(){}
public:
	DECLARE_SUBSTANCE(filter_Reducefire); 
	filter_Reducefire(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_REDUCEFIRE;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCEFIRE,_timeout);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCEFIRE);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};
class filter_Reducesoil : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Reducesoil(){}
public:
	DECLARE_SUBSTANCE(filter_Reducesoil); 
	filter_Reducesoil(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_REDUCESOIL;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCESOIL,_timeout);
		_parent.ImpairScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCESOIL);
		_parent.EnhanceScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Incaccuracy : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incaccuracy(){}
public:
	DECLARE_SUBSTANCE(filter_Incaccuracy); 
	filter_Incaccuracy(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCACCURACY;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCACCURACY,_timeout);
		_parent.EnhanceScaleAttack(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCACCURACY);
		_parent.ImpairScaleAttack(_ratio);
		_parent.UpdateAttackData();
	}
};

class filter_Fireblade : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Fireblade(){}
public:
	DECLARE_SUBSTANCE(filter_Fireblade); 
	filter_Fireblade(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FIREBLADE;
		_ratio = ratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(IS_PHYSIC_ATTACK(msg.attack_attr))
		{
			const item_prop & weapon = _parent.GetCurWeapon();
			msg.magic_damage[3] += (int)(_ratio * 0.5 * (weapon.damage_low+weapon.damage_high));
		}
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FIREBLADE,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FIREBLADE);
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Fireblade*>(f));
		filter_Fireblade* nf = (filter_Fireblade*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_ratio = nf->GetRatio();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_FIREBLADE);
			_parent.InsertTeamVisibleState(HSTATE_FIREBLADE, _timeout);
		}
		
		
	}
	float GetRatio()
	{
		return _ratio;
	}
};

class filter_Fastpray : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Fastpray(){}
public:
	DECLARE_SUBSTANCE(filter_Fastpray); 
	filter_Fastpray(object_interface  object,int ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FASTPRAY;
		_ratio = ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FASTPRAY,_timeout);
		(_parent.GetSkillWrapper()).DecPrayTime(_ratio);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FASTPRAY);
		(_parent.GetSkillWrapper()).IncPrayTime(_ratio);
	}
};

class filter_Dechurt : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Dechurt(){}
public:
	DECLARE_SUBSTANCE(filter_Dechurt); 
	filter_Dechurt(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DECHURT;
		_ratio = 1.0-ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECHURT,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECHURT);
	}
};

class filter_Hpgen : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _health;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _health;
		ar << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _health;
		ar >> _counter;
		return true;
	}
	filter_Hpgen(){}
public:
	DECLARE_SUBSTANCE(filter_Hpgen); 
	filter_Hpgen(object_interface  object,int health, int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_HPGEN;
		_counter = 0;
		_health = health/period;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_HPGEN,_timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_HPGEN);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.HealBySkill(_health*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Mpgen : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _health;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _health;
		ar << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _health;
		ar >> _counter;
		return true;
	}
	filter_Mpgen(){}
public:
	DECLARE_SUBSTANCE(filter_Mpgen); 
	filter_Mpgen(object_interface  object,int health, int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_MPGEN;
		_counter = 0;
		_health = health/period;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_MPGEN,_timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_MPGEN);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.InjectMana(_health*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Yijin : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _inc;
	int _dec;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		ar << _dec;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		ar >> _dec;
		return true;
	}
	filter_Yijin(){}
public:
	DECLARE_SUBSTANCE(filter_Yijin); 
	filter_Yijin(object_interface  object,int inc,int dec,int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_YIJIN;
		_inc = inc; 
		_dec = dec; 
	}

	void OnAttach()
	{
		_parent.ImpairScaleDefense(_dec);
		_parent.EnhanceScaleResistance(0, _inc);
		_parent.EnhanceScaleResistance(1, _inc);
		_parent.EnhanceScaleResistance(2, _inc);
		_parent.EnhanceScaleResistance(3, _inc);
		_parent.EnhanceScaleResistance(4, _inc);

		_parent.UpdateMagicData();
		_parent.UpdateDefenseData();
		_parent.InsertTeamVisibleState(HSTATE_YIJIN,_timeout);
	}

	void OnRelease()
	{

		_parent.RemoveTeamVisibleState(HSTATE_YIJIN);
		_parent.EnhanceScaleDefense(_dec);
		_parent.ImpairScaleResistance(0, _inc);
		_parent.ImpairScaleResistance(1, _inc);
		_parent.ImpairScaleResistance(2, _inc);
		_parent.ImpairScaleResistance(3, _inc);
		_parent.ImpairScaleResistance(4, _inc);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
	}
};

class filter_Xisui : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _inc;
	int _dec;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		ar << _dec;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		ar >> _dec;
		return true;
	}
	filter_Xisui(){}
public:
	DECLARE_SUBSTANCE(filter_Xisui); 
	filter_Xisui(object_interface  object,int inc, int dec, int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_XISUI;
		_inc = inc; 
		_dec = dec; 
	}

	void OnAttach()
	{
		_parent.EnhanceScaleDefense(_inc);
		_parent.ImpairScaleResistance(0, _dec);
		_parent.ImpairScaleResistance(1, _dec);
		_parent.ImpairScaleResistance(2, _dec);
		_parent.ImpairScaleResistance(3, _dec);
		_parent.ImpairScaleResistance(4, _dec);

		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
		_parent.InsertTeamVisibleState(HSTATE_XISUI,_timeout);
	}

	void OnRelease()
	{
		_parent.ImpairScaleDefense(_inc);
		_parent.EnhanceScaleResistance(0, _dec);
		_parent.EnhanceScaleResistance(1, _dec);
		_parent.EnhanceScaleResistance(2, _dec);
		_parent.EnhanceScaleResistance(3, _dec);
		_parent.EnhanceScaleResistance(4, _dec);
		_parent.RemoveTeamVisibleState(HSTATE_XISUI);

		_parent.UpdateMagicData();
		_parent.UpdateDefenseData();
	}
};

class filter_Iceshield : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		return true;
	}
	filter_Iceshield(){}
public:
	DECLARE_SUBSTANCE(filter_Iceshield); 
	filter_Iceshield(object_interface  object,int r, int p, int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p)
	{
		_filter_id = FILTER_MAGICSHIELD;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_ICESHIELD);
		_parent.InsertTeamVisibleState(HSTATE_ICESHIELD,_timeout);
		_parent.EnhanceMPGen(_point);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
		_parent.UpdateHPMPGen();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_ICESHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_ICESHIELD);
		_parent.ImpairMPGen(_point);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
		_parent.UpdateHPMPGen();
	}
};
class filter_Fireshield : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		return true;
	}
	filter_Fireshield(){}
public:
	DECLARE_SUBSTANCE(filter_Fireshield); 
	filter_Fireshield(object_interface  object,int r, int p, int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p)
	{
		_filter_id = FILTER_MAGICSHIELD;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_FIRESHIELD);
		_parent.InsertTeamVisibleState(HSTATE_FIRESHIELD,_timeout);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.EnhanceHPGen(_point);
		_parent.UpdateMagicData();
		_parent.UpdateHPMPGen();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_FIRESHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_FIRESHIELD);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.ImpairHPGen(_point);
		_parent.UpdateMagicData();
		_parent.UpdateHPMPGen();
	}
};

class filter_Soilshield : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _sratio;
	int _pratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _sratio;
		ar << _pratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _sratio;
		ar >> _pratio;
		return true;
	}
	filter_Soilshield(){}
public:
	DECLARE_SUBSTANCE(filter_Soilshield); 
	filter_Soilshield(object_interface  object,int s, int p, int period)
				        :timeout_filter(object,period,FILTER_MASK),_sratio(s),_pratio(p)
	{
		_filter_id = FILTER_MAGICSHIELD;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_SOILSHIELD);
		_parent.InsertTeamVisibleState(HSTATE_SOILSHIELD,_timeout);
		_parent.EnhanceScaleResistance(4, _sratio);
		_parent.UpdateMagicData();
		_parent.EnhanceScaleDefense(_pratio);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_SOILSHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_SOILSHIELD);
		_parent.ImpairScaleResistance(4, _sratio);
		_parent.UpdateMagicData();
		_parent.ImpairScaleDefense(_pratio);
		_parent.UpdateDefenseData();
	}
};

class filter_Apgen : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_DO_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Apgen(){}
public:
	DECLARE_SUBSTANCE(filter_Apgen); 
	filter_Apgen(object_interface  object,int p, int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(p)
	{
		_filter_id = FILTER_APGEN;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_APGEN,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_APGEN);
	}

	void DoDamage(const damage_entry & dmg)
	{
		_parent.ModifyAP(_point);
	}
};


class filter_Tigerform : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK
	};

	int _shape;
	int _inchp;
	int _incspeed;
	int _decattack;

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _shape;
		ar << _inchp;
		ar << _incspeed;
		ar << _decattack;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _shape;
		ar >> _inchp;
		ar >> _incspeed;
		ar >> _decattack;
		return true;
	}
	filter_Tigerform(){}
public:
	DECLARE_SUBSTANCE(filter_Tigerform); 
	filter_Tigerform(object_interface  object, int shape, int inchp, int incspeed, int decattack)
			:filter(object,FILTER_MASK),_shape(shape), _inchp(inchp),_incspeed(incspeed),_decattack(decattack)
	{
		_filter_id = FILTER_TIGERFORM;
	}

	void OnAttach();

	void OnRelease();
};

class filter_Cannonform : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _shape;
	int _decattack;
	float _range;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _shape;	
		ar << _decattack;
		ar << _range;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _shape;
		ar >> _decattack;
		ar >> _range;
		return true;
	}
	filter_Cannonform(){}
public:
	DECLARE_SUBSTANCE(filter_Cannonform); 
	filter_Cannonform(object_interface  object,int shape, int decattack, float range, int period)
			:timeout_filter(object,period, FILTER_MASK),_shape(shape), _decattack(decattack), _range(range)
	{
		_filter_id = FILTER_CANNONFORM;
	}

	void OnAttach();

	void OnRelease();
};


class filter_Antiwater : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}
	filter_Antiwater(){}
public:
	DECLARE_SUBSTANCE(filter_Antiwater); 
	filter_Antiwater(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_ANTIWATER;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ANTIWATER,_timeout);
		_parent.EnableEndlessBreath(true);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ANTIWATER);
		_parent.EnableEndlessBreath(false);
	}
};

class filter_Powerup : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}
	filter_Powerup(){}
public:
	DECLARE_SUBSTANCE(filter_Powerup); 
	filter_Powerup(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_POWERUP;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_POWERUP);
		_parent.InsertTeamVisibleState(HSTATE_POWERUP,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_POWERUP);
		_parent.RemoveTeamVisibleState(HSTATE_POWERUP);
	}
};

class filter_Stoneskin : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Stoneskin(){}
public:
	DECLARE_SUBSTANCE(filter_Stoneskin); 
	filter_Stoneskin(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_STONESKIN;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_STONESKIN,_timeout);
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		_parent.ImpairScaleDefense(_ratio);
		_parent.UpdateDefenseData();
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_STONESKIN);
	}

};

class filter_Ironshield : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Ironshield(){}
public:
	DECLARE_SUBSTANCE(filter_Ironshield); 
	filter_Ironshield(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_IRONSHIELD;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_IRONSHIELD,_timeout);
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		_parent.ImpairScaleDefense(_ratio);
		_parent.UpdateDefenseData();
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_IRONSHIELD);
	}

};

class filter_Giant : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Giant(){}
public:
	DECLARE_SUBSTANCE(filter_Giant); 
	filter_Giant(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_GIANT;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_GIANT,_timeout);
		_parent.EnhanceScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_GIANT);
		_parent.ImpairScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}
};

class filter_Devilstate : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	int _hpdec;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _hpdec;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _hpdec;
		return true;
	}
	filter_Devilstate(){}
public:
	DECLARE_SUBSTANCE(filter_Devilstate); 
	filter_Devilstate(object_interface  object,int r,int d,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_hpdec(d)
	{
		_filter_id = FILTER_DEVILSTATE;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_DEVILSTATE,_timeout);
		_parent.ImpairScaleMaxHP(_hpdec);
		_parent.EnhanceScaleAttack(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_DEVILSTATE);
		_parent.EnhanceScaleMaxHP(_hpdec);
		_parent.ImpairScaleAttack(_ratio);
		_parent.UpdateAttackData();
	}
};

class filter_Blessmagic : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Blessmagic(){}
public:
	DECLARE_SUBSTANCE(filter_Blessmagic); 
	filter_Blessmagic(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_BLESSMAGIC;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_BLESSMAGIC,_timeout);
		_parent.EnhanceScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_BLESSMAGIC);
		_parent.ImpairScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}
};

class filter_Wingshield : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE|FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _amount;
	int _mpgen;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _amount;
		ar << _mpgen;
		ar << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _amount;
		ar >> _mpgen;
		ar >> _counter;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg &msg , float damage_adjust)
	{
		float damage = dmg.physic_damage+dmg.magic_damage[0]+dmg.magic_damage[1]+dmg.magic_damage[2]+dmg.magic_damage[3]
					+dmg.magic_damage[4];
		damage *= damage_adjust*0.2;

		if(damage<_amount)
		{
			dmg.physic_damage *= 0.2;
			dmg.magic_damage[0] *= 0.2;
			dmg.magic_damage[1] *= 0.2;
			dmg.magic_damage[2] *= 0.2;
			dmg.magic_damage[3] *= 0.2;
			dmg.magic_damage[4] *= 0.2;
			_amount -= damage*4;
		}else if(damage>1)
		{
			float r = 1.0 - _amount/damage;
			dmg.physic_damage *= r;
			dmg.magic_damage[0] *= r;
			dmg.magic_damage[1] *= r;
			dmg.magic_damage[2] *= r;
			dmg.magic_damage[3] *= r;
			dmg.magic_damage[4] *= r;
			_amount = 0;
		}
		if(_amount<6)
			_is_deleted = true;
	}

	filter_Wingshield(){}
public:
	DECLARE_SUBSTANCE(filter_Wingshield); 
	filter_Wingshield(object_interface  object,int amount, int mpgen, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_WINGSHIELD;
		_amount = amount;
		_mpgen = mpgen;
		_counter = 0;
	}

	void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.InjectMana(_mpgen);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_WINGSHIELD);
		_parent.InsertTeamVisibleState(HSTATE_WINGSHIELD,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_WINGSHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_WINGSHIELD);
	}
};

class filter_Firearrow : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSLATE_SEND_MSG|FILTER_MASK_TRANSFERABLE_BUFF 
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Firearrow(){}
public:
	DECLARE_SUBSTANCE(filter_Firearrow); 
	filter_Firearrow(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FIREARROW;
		_ratio = ratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(IS_PHYSIC_ATTACK(msg.attack_attr))
		{
			const item_prop & weapon = _parent.GetCurWeapon();
			msg.magic_damage[3] += (int)(_ratio * 0.5 * (weapon.damage_low+weapon.damage_high));
		}
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FIREARROW,_timeout);
		_parent.IncVisibleState(VSTATE_FIREARROW);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FIREARROW);
		_parent.DecVisibleState(VSTATE_FIREARROW);
	}
};

class filter_Eaglecurse : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;
	int _damage;
	XID _performer;
	attacker_info_t _pinfo;
	bool _invader;
	int _counter;
	char _mode;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _damage;
		ar << _performer;
		ar << _counter;
		ar.push_back(&_pinfo, sizeof(attacker_info_t));
		ar << _invader;
		ar << _mode;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _damage;
		ar >> _performer;
		ar >> _counter;
		ar.pop_back(&_pinfo, sizeof(attacker_info_t));
		ar >> _invader;
		ar >> _mode;
		return true;
	}
	filter_Eaglecurse(){}
public:
	DECLARE_SUBSTANCE(filter_Eaglecurse); 
	filter_Eaglecurse(object_interface  object,int r,int period, int damage, int mask = 0)
				        :timeout_filter(object,period,FILTER_MASK | mask),_ratio(r)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_EAGLECURSE_MERGE;
		else
			_filter_id = FILTER_EAGLECURSE;
		_counter = 0;
		_damage = damage / period;
	}

	void SetUp(const XID& player, const attacker_info_t& info, char mode, bool invader)
	{
		_performer = player;
		_pinfo = info;
		_invader = invader;
		_mode = mode;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_EAGLECURSE,_timeout);
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_EAGLECURSE);
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.BeHurt(_performer, _pinfo, _damage*_counter, _invader, _mode);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Eaglecurse*>(f));
		filter_Eaglecurse* nf = (filter_Eaglecurse*) f;

		int tmp = _damage * _timeout;
		_timeout = GetTimeOut(nf);
		_damage = nf->GetDamage() + tmp/_timeout;
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_EAGLECURSE);
			_parent.InsertTeamVisibleState(HSTATE_EAGLECURSE, _timeout);
		}
	}

	int GetDamage()
	{
		return _damage;
	}
};

class filter_Freemove : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}

	filter_Freemove(){}
public:
	DECLARE_SUBSTANCE(filter_Freemove); 
	filter_Freemove(object_interface object, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FREEMOVE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FREEMOVE,_timeout);
		_parent.IncImmuneMask(IMMUNESLOW);
		_parent.IncImmuneMask(IMMUNEFIX);
		_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.IncImmuneMask(IMMUNESLEEP);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FREEMOVE);
		_parent.DecImmuneMask(IMMUNESLOW);
		_parent.DecImmuneMask(IMMUNEFIX);
		_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.DecImmuneMask(IMMUNESLEEP);
	}
};

class filter_Incsmite : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Incsmite(){}
public:
	DECLARE_SUBSTANCE(filter_Incsmite); 
	filter_Incsmite(object_interface  object,int inc,int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(inc)
	{
		_filter_id = FILTER_INCSMITE;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCSMITE,_timeout);
		_parent.EnhanceCrit(_point);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCSMITE);
		_parent.ImpairCrit(_point);
	}
};

class filter_Canti : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Canti(){}
public:
	DECLARE_SUBSTANCE(filter_Canti); 
	filter_Canti(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SPIRITCURSE;
		_ratio = 1.0+ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_CANTI,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_CANTI);
	}
};

class filter_Apleak : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_DO_DAMAGE|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Apleak(){}
public:
	DECLARE_SUBSTANCE(filter_Apleak); 
	filter_Apleak(object_interface  object,int p, int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(-p)
	{
		_filter_id = FILTER_SPIRITCURSE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_APLEAK,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_APLEAK);
	}

	void DoDamage(const damage_entry & dmg)
	{
		_parent.ModifyAP(_point);
	}
};

class filter_Foxform : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK
	};

	int _decmp;
	int _incdefence;
	int _incaccuracy;
	int _shape;

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _decmp;
		ar << _incdefence;
		ar << _incaccuracy;
		ar << _shape;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _decmp;
		ar >> _incdefence;
		ar >> _incaccuracy;
		ar >> _shape;
		return true;
	}
	filter_Foxform(){}
public:
	DECLARE_SUBSTANCE(filter_Foxform); 
	filter_Foxform(object_interface  object, int decmp, int incdefence, int incaccuracy, int shape)
			:filter(object,FILTER_MASK),_decmp(decmp),_incdefence(incdefence),_incaccuracy(incaccuracy),_shape(shape)
	{
		_filter_id = FILTER_FOXFORM;
	}

	void OnAttach();

	void OnRelease();
};

class filter_Noregain : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}
	filter_Noregain(){}
public:
	DECLARE_SUBSTANCE(filter_Noregain); 
	filter_Noregain(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SPIRITCURSE;
	}

	void OnAttach()
	{
		_parent.ImpairScaleHPGen(2000);
		_parent.ImpairScaleMPGen(2000);
		_parent.IncVisibleState(VSTATE_NOREGAIN);
		_parent.InsertTeamVisibleState(HSTATE_NOREGAIN,_timeout);
		_parent.UpdateHPMPGen();
	}
	void OnRelease()
	{
		_parent.EnhanceScaleHPGen(2000);
		_parent.EnhanceScaleMPGen(2000);
		_parent.DecVisibleState(VSTATE_NOREGAIN);
		_parent.RemoveTeamVisibleState(HSTATE_NOREGAIN);
		_parent.UpdateHPMPGen();
	}
};

class filter_Jingji : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;
	float _reduce;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _reduce;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _reduce;
		return true;
	}

	filter_Jingji(){}
public:
	DECLARE_SUBSTANCE(filter_Jingji); 
	filter_Jingji(object_interface  object,float ratio, float dec, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_RETORT;
		_ratio = ratio;
		_reduce = 1.0-dec;
		if(_reduce<=0.01)
			_reduce = 0.01;
	}
	
	void Merge(filter* f)
	{
		ASSERT(dynamic_cast<filter_Jingji*>(f));	
		filter_Jingji* nf = (filter_Jingji*) f;
		if(nf->GetValue() == _ratio)
		{
			if(GetTimeOut(nf) > _timeout) _timeout = GetTimeOut(nf);		
		}
		else if(nf->GetValue() > _ratio)
		{
			_timeout = GetTimeOut(nf);
			_ratio = nf->GetValue();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_JINGJI);
			_parent.InsertTeamVisibleState(HSTATE_JINGJI, _timeout);
		}
		
	}

	void AdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		ent.physic_damage   *= _reduce;
		ent.magic_damage[0] *= _reduce;
		ent.magic_damage[1] *= _reduce;
		ent.magic_damage[2] *= _reduce;
		ent.magic_damage[3] *= _reduce;
		ent.magic_damage[4] *= _reduce;

		if(msg.physic_damage >= 1000000) return;//��ֹ���������boss��������
		int damage = (int)(msg.physic_damage * _ratio);

		if(msg.short_range>0 || !IS_PHYSIC_ATTACK(msg.attack_attr) || damage <= 1)	
			return;
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.physic_damage	= damage;
		ret.attack_rate	= 1000;
		ret.force_attack = _parent.GetForceAttack();
		ret.attack_attr = attack_msg::MAGIC_ATTACK;
		ret.attack_range = msg.attack_range + 0.5;
		ret.speed = msg.speed;
		ret.skill_id = 1146;
		_parent.SetRetortState();
		_parent.Attack( attacker, ret, 0);

	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_JINGJI);
		_parent.InsertTeamVisibleState(HSTATE_JINGJI,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_JINGJI);
		_parent.RemoveTeamVisibleState(HSTATE_JINGJI);
	}
	
	float GetValue()
	{
		return _ratio;	
	}
	
};

class filter_Icon : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	int _vstate;
	int _hstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _vstate;
		ar << _hstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _vstate;
		ar >> _hstate;
		return true;
	}
	filter_Icon(){}
public:
	DECLARE_SUBSTANCE(filter_Icon); 
	filter_Icon(object_interface  object,int period, int hstate, int vstate=0, int filterid=FILTER_ICON, int mask=0)
				        :timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = filterid;
		_vstate = vstate;
		_hstate = hstate;
	}

	void OnAttach()
	{
		if(_vstate)
			_parent.IncVisibleState(_vstate);
		if(_hstate)
			_parent.InsertTeamVisibleState(_hstate,_timeout);
	}

	void OnRelease()
	{
		if(_vstate)
			_parent.DecVisibleState(_vstate);
		if(_hstate)
			_parent.RemoveTeamVisibleState(_hstate);
	}
};

class filter_Swiftform : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _incspeed;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _incspeed;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _incspeed;
		return true;
	}
	filter_Swiftform(){}
public:
	DECLARE_SUBSTANCE(filter_Swiftform); 
	filter_Swiftform(object_interface  object, int time, int incspeed)
			:timeout_filter(object,time,FILTER_MASK),_incspeed(incspeed)
	{
		_filter_id = FILTER_SWIFTFORM;
	}

	void OnAttach();

	void OnRelease();
};

class filter_Fastride : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Fastride(){}
public:
	DECLARE_SUBSTANCE(filter_Fastride); 
	filter_Fastride(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_FASTRIDE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FASTRIDE,_timeout);
		_parent.EnhanceMountSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FASTRIDE);
		_parent.ImpairMountSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Sharpblade : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Sharpblade(){}
public:
	DECLARE_SUBSTANCE(filter_Sharpblade); 
	filter_Sharpblade(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_SHARPBLADE;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_SHARPBLADE,_timeout);
		_parent.EnhanceScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_SHARPBLADE);
		_parent.ImpairScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}
};
class filter_Addattackdegree : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _add;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _add << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _add >> _insertvstate;
		return true;
	}
	filter_Addattackdegree(){}
public:
	DECLARE_SUBSTANCE(filter_Addattackdegree); 
	filter_Addattackdegree(object_interface  object,int r,int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_add(r),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_ADDATTACKDEGREE;
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Addattackdegree*>(f));
		filter_Addattackdegree* nf = (filter_Addattackdegree*) f;
		_timeout = GetTimeOut(nf);
		if(_add!=nf->GetValue())
		{
			_parent.ImpairAttackDegree(_add);
			_add = nf->GetValue();
			_parent.EnhanceAttackDegree(_add);
			_parent.SendClientAttackData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_ADDATTACKDEGREE);
			_parent.InsertTeamVisibleState(HSTATE_ADDATTACKDEGREE, _timeout);
		}
		
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_ADDATTACKDEGREE);
		_parent.InsertTeamVisibleState(HSTATE_ADDATTACKDEGREE,_timeout);
		_parent.EnhanceAttackDegree(_add);
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_ADDATTACKDEGREE);
		_parent.RemoveTeamVisibleState(HSTATE_ADDATTACKDEGREE);
		_parent.ImpairAttackDegree(_add);
		_parent.SendClientAttackData();
	}

	int GetValue()
	{
		return _add;
	}
};

class filter_Subattackdegree : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}
	filter_Subattackdegree(){}
public:
	DECLARE_SUBSTANCE(filter_Subattackdegree); 
	filter_Subattackdegree(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_value(r)
	{
		_filter_id = FILTER_SUBATTACKDEGREE;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SUBATTACKDEGREE,_timeout);
		_parent.ImpairAttackDegree(_value);
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SUBATTACKDEGREE);
		_parent.EnhanceAttackDegree(_value);
		_parent.SendClientAttackData();
	}

	int GetValue()
	{
		return _value;
	}
};
class filter_Subdefencedegree : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}
	filter_Subdefencedegree(){}
public:
	DECLARE_SUBSTANCE(filter_Subdefencedegree); 
	filter_Subdefencedegree(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_value(r)
	{
		_filter_id = FILTER_SUBDEFENCEDEGREE;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SUBDEFENCEDEGREE,_timeout);
		_parent.ImpairDefendDegree(_value);
		_parent.SendClientDefenseData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SUBDEFENCEDEGREE);
		_parent.EnhanceDefendDegree(_value);
		_parent.SendClientDefenseData();
	}

	int GetValue()
	{
		return _value;
	}
};
class filter_Adddefencedegree : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _value;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value >> _insertvstate;
		return true;
	}
	filter_Adddefencedegree(){}
public:
	DECLARE_SUBSTANCE(filter_Adddefencedegree); 
	filter_Adddefencedegree(object_interface  object,int r,int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_value(r),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_ADDDEFENCEDEGREE;
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Adddefencedegree*>(f));
		filter_Adddefencedegree* nf = (filter_Adddefencedegree*) f;
		_timeout = GetTimeOut(nf);
		if(_value!=nf->GetValue())
		{
			_parent.ImpairDefendDegree(_value);
			_value = nf->GetValue();
			_parent.EnhanceDefendDegree(_value);
			_parent.SendClientDefenseData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_ADDDEFENCEDEGREE);
			_parent.InsertTeamVisibleState(HSTATE_ADDDEFENCEDEGREE, _timeout);
		}
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_ADDDEFENCEDEGREE);
		_parent.InsertTeamVisibleState(HSTATE_ADDDEFENCEDEGREE,_timeout);
		_parent.EnhanceDefendDegree(_value);
		_parent.SendClientDefenseData();
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_ADDDEFENCEDEGREE);
		_parent.RemoveTeamVisibleState(HSTATE_ADDDEFENCEDEGREE);
		_parent.ImpairDefendDegree(_value);
		_parent.SendClientDefenseData();
	}

	int GetValue()
	{
		return _value;
	}
};

//lgc
class filter_Baseimmune : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _immune_mask;
	int _vstate;
	int _hstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _immune_mask << _vstate << _hstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _immune_mask >> _vstate >> _hstate;
		return true;
	}

	filter_Baseimmune(){}
public:
	filter_Baseimmune(object_interface object, int period, int immune_mask, int vstate, int hstate, int mask = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_TRANSFERABLE_BUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask), _immune_mask(immune_mask), _vstate(vstate), _hstate(hstate){}

	void OnAttach()
	{
		if(_hstate >= 0)
			_parent.InsertTeamVisibleState(_hstate,_timeout);
		if(_vstate >= 0)
			_parent.IncVisibleState(_vstate);
		_parent.IncImmuneMask(_immune_mask);
	}

	void OnRelease()
	{
		if(_hstate >= 0)
			_parent.RemoveTeamVisibleState(_hstate);
		if(_vstate >= 0)
			_parent.DecVisibleState(_vstate);
		_parent.DecImmuneMask(_immune_mask);
	}
	
};

class filter_Immunesealed : public filter_Baseimmune
{
protected:
	filter_Immunesealed(){}
public:
	DECLARE_SUBSTANCE(filter_Immunesealed);
	filter_Immunesealed(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNECURSED,(insertvstate?VSTATE_IMMUNESEALED:-1),HSTATE_IMMUNESEALED)
	{
		_filter_id = FILTER_IMMUNESEALED;			
	}
	
};


class filter_Immunesleep : public filter_Baseimmune
{
protected:
	filter_Immunesleep(){}
public:
	DECLARE_SUBSTANCE(filter_Immunesleep);
	filter_Immunesleep(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNESLEEP,(insertvstate?VSTATE_IMMUNESLEEP:-1),HSTATE_IMMUNESLEEP)
	{
		_filter_id = FILTER_IMMUNESLEEP;			
	}
	
};

class filter_Immuneslowdizzy : public filter_Baseimmune
{
protected:
	filter_Immuneslowdizzy(){}
public:
	DECLARE_SUBSTANCE(filter_Immuneslowdizzy);
	filter_Immuneslowdizzy(object_interface object, int period)
						:filter_Baseimmune(object,period,IMMUNESLOW|IMMUNEDIZZY,-1,HSTATE_IMMUNESLOWDIZZY)
	{
		_filter_id = FILTER_IMMUNESLOWDIZZY;			
	}
	
};
class filter_Immunewound : public filter_Baseimmune
{
protected:
	filter_Immunewound(){}
public:
	DECLARE_SUBSTANCE(filter_Immunewound);
	filter_Immunewound(object_interface object, int period)
						:filter_Baseimmune(object,period,IMMUNEWOUND, -1,HSTATE_IMMUNEWOUND)
	{
		_filter_id = FILTER_IMMUNEWOUND;			
	}
	
};
class filter_Immuneall : public filter_Baseimmune	//�������и���״̬
{
protected:
	
	enum 
	{
		FILTER_MASK = FILTER_MASK_BUFF | FILTER_MASK_TRANSFERABLE_BUFF
	};

	filter_Immuneall(){}
public:
	DECLARE_SUBSTANCE(filter_Immuneall);
	filter_Immuneall(object_interface object, int period)
						:filter_Baseimmune(object,period,IMMUNEALL,-1,HSTATE_IMMUNEALL,FILTER_MASK)
	{
		_filter_id = FILTER_IMMUNEALL;			
	}
	
};
class filter_Immunephysical : public filter_Baseimmune
{
protected:
	filter_Immunephysical(){}
public:
	DECLARE_SUBSTANCE(filter_Immunephysical);
	filter_Immunephysical(object_interface object, int period)
						:filter_Baseimmune(object,period,IMMUNEPHYSICAL,-1,HSTATE_IMMUNEPHYSICAL)
	{
		_filter_id = FILTER_IMMUNEPHYSICAL;			
	}
	
};
class filter_Immunefire : public filter_Baseimmune
{
protected:
	filter_Immunefire(){}
public:
	DECLARE_SUBSTANCE(filter_Immunefire);
	filter_Immunefire(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNEFIRE,(insertvstate?VSTATE_IMMUNEFIRE:-1),HSTATE_IMMUNEFIRE)
	{
		_filter_id = FILTER_IMMUNEFIRE;			
	}
	
};
class filter_Immunewater : public filter_Baseimmune
{
protected:
	filter_Immunewater(){}
public:
	DECLARE_SUBSTANCE(filter_Immunewater);
	filter_Immunewater(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNEWATER,(insertvstate?VSTATE_IMMUNEWATER:-1),HSTATE_IMMUNEWATER)
	{
		_filter_id = FILTER_IMMUNEWATER;			
	}
	
};
class filter_Immunemetal : public filter_Baseimmune
{
protected:
	filter_Immunemetal(){}
public:
	DECLARE_SUBSTANCE(filter_Immunemetal);
	filter_Immunemetal(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNEMETAL,(insertvstate?VSTATE_IMMUNEMETAL:-1),HSTATE_IMMUNEMETAL)
	{
		_filter_id = FILTER_IMMUNEMETAL;			
	}
	
};
class filter_Immunewood : public filter_Baseimmune
{
protected:
	filter_Immunewood(){}
public:
	DECLARE_SUBSTANCE(filter_Immunewood);
	filter_Immunewood(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNEWOOD,(insertvstate?VSTATE_IMMUNEWOOD:-1),HSTATE_IMMUNEWOOD)
	{
		_filter_id = FILTER_IMMUNEWOOD;			
	}
	
};
class filter_Immunesoil : public filter_Baseimmune
{
protected:
	filter_Immunesoil(){}
public:
	DECLARE_SUBSTANCE(filter_Immunesoil);
	filter_Immunesoil(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNESOIL,(insertvstate?VSTATE_IMMUNESOIL:-1),HSTATE_IMMUNESOIL)
	{
		_filter_id = FILTER_IMMUNESOIL;			
	}
	
};
class filter_Immunemagical : public filter_Baseimmune
{
protected:
	filter_Immunemagical(){}
public:
	DECLARE_SUBSTANCE(filter_Immunemagical);
	filter_Immunemagical(object_interface object, int period, int fid, int mask)
						:filter_Baseimmune(object,period,IMMUNEMETAL|IMMUNEWOOD|IMMUNEWATER|IMMUNEFIRE|IMMUNESOIL,-1,HSTATE_IMMUNEMAGICAL,mask)
	{
		_filter_id = fid;			
	}
	
};
class filter_Arrogant : public timeout_filter		//����һ��״̬
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH 
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}

	filter_Arrogant(){}
public:
	DECLARE_SUBSTANCE(filter_Arrogant); 
	filter_Arrogant(object_interface object, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_ARROGANT;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ARROGANT,_timeout);
		SkillWrapper & _skill = _parent.GetSkillWrapper();
		_skill.IncImmuneBuffDebuff();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ARROGANT);
		SkillWrapper & _skill = _parent.GetSkillWrapper();
		_skill.DecImmuneBuffDebuff();
	}
};

class filter_Slowswim : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Slowswim(){}
public:
	DECLARE_SUBSTANCE(filter_Slowswim); 
	filter_Slowswim(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_SLOWSWIM;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SLOWSWIM,_timeout);
		_parent.ImpairSwimSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SLOWSWIM);
		_parent.EnhanceSwimSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Fastswim : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Fastswim(){}
public:
	DECLARE_SUBSTANCE(filter_Fastswim); 
	filter_Fastswim(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_FASTSWIM;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FASTSWIM,_timeout);
		_parent.EnhanceSwimSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FASTSWIM);
		_parent.ImpairSwimSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};


class filter_Slowfly : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Slowfly(){}
public:
	DECLARE_SUBSTANCE(filter_Slowfly); 
	filter_Slowfly(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_SLOWFLY;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SLOWFLY,_timeout);
		_parent.ImpairScaleFlySpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SLOWFLY);
		_parent.EnhanceScaleFlySpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Fastfly : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Fastfly(){}
public:
	DECLARE_SUBSTANCE(filter_Fastfly); 
	filter_Fastfly(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_FASTFLY;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FASTFLY,_timeout);
		_parent.EnhanceScaleFlySpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FASTFLY);
		_parent.ImpairScaleFlySpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Slowride : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Slowride(){}
public:
	DECLARE_SUBSTANCE(filter_Slowride); 
	filter_Slowride(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_SLOWRIDE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SLOWRIDE,_timeout);
		_parent.ImpairMountSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SLOWRIDE);
		_parent.EnhanceMountSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Apgencont : public timeout_filter//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _ap;
	char _counter;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ap;
		ar << _counter;
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ap;
		ar >> _counter;
		ar >> _insertvstate;
		return true;
	}
	filter_Apgencont(){}
public:
	DECLARE_SUBSTANCE(filter_Apgencont); 
	filter_Apgencont(object_interface  object,int ap, int period, bool insertvstate=true, int mask=FILTER_MASK_BUFF)
			:timeout_filter(object,period,FILTER_MASK|mask), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_APGENCONT;
		_counter = 0;
		_ap = period > 0 ? ap/period : ap;
	}

	void OnAttach() 
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_APGENCONT);
		_parent.InsertTeamVisibleState(HSTATE_APGENCONT,_timeout);
	}
	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_APGENCONT);
		_parent.RemoveTeamVisibleState(HSTATE_APGENCONT);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.ModifyAP(_ap*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Apgencont2 : public timeout_filter//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _ap;
	char _counter;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ap;
		ar << _counter;
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ap;
		ar >> _counter;
		ar >> _insertvstate;
		return true;
	}
	filter_Apgencont2(){}
public:
	DECLARE_SUBSTANCE(filter_Apgencont2); 
	filter_Apgencont2(object_interface  object,int ap, int period, bool insertvstate=true, int mask=FILTER_MASK_BUFF)
			:timeout_filter(object,period,FILTER_MASK|mask), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_APGENCONT2;
		_counter = 0;
		_ap = period > 0 ? ap/period : ap;
	}

	void OnAttach() 
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_APGENCONT);
		_parent.InsertTeamVisibleState(HSTATE_APGENCONT,_timeout);
	}
	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_APGENCONT);
		_parent.RemoveTeamVisibleState(HSTATE_APGENCONT);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.ModifyAP(_ap*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

};

class filter_Apleakcont : public timeout_filter//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	int _ap;
	char _counter;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ap;
		ar << _counter;
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ap;
		ar >> _counter;
		ar >> _insertvstate;
		return true;
	}
	filter_Apleakcont(){}
public:
	DECLARE_SUBSTANCE(filter_Apleakcont); 
	filter_Apleakcont(object_interface  object,int ap, int period, bool insertvstate=true, int mask=FILTER_MASK_DEBUFF)
			:timeout_filter(object,period,FILTER_MASK|mask), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_APLEAKCONT;
		_counter = 0;
		_ap = ap/period;
	}

	void OnAttach() 
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_APLEAKCONT);
		_parent.InsertTeamVisibleState(HSTATE_APLEAKCONT,_timeout);
	}
	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_APLEAKCONT);
		_parent.RemoveTeamVisibleState(HSTATE_APLEAKCONT);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.ModifyAP(- _ap*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Incelfstr : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Incelfstr(){}
public:
	DECLARE_SUBSTANCE(filter_Incelfstr); 
	filter_Incelfstr(object_interface  object,int point,int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(point)
	{
		_filter_id = FILTER_INCELFSTR;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCELFSTR,_timeout);
		_parent.EnhanceElfProp(_point, 0, 0, 0);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCELFSTR);
		_parent.ImpairElfProp(_point, 0, 0, 0);
	}
};

class filter_Incelfagi : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Incelfagi(){}
public:
	DECLARE_SUBSTANCE(filter_Incelfagi); 
	filter_Incelfagi(object_interface  object,int point,int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(point)
	{
		_filter_id = FILTER_INCELFAGI;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCELFAGI,_timeout);
		_parent.EnhanceElfProp(0, _point, 0, 0);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCELFAGI);
		_parent.ImpairElfProp(0, _point, 0, 0);
	}
};

class filter_Incdefence2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incdefence2(){}
public:
	DECLARE_SUBSTANCE(filter_Incdefence2); 
	filter_Incdefence2(object_interface  object,int ratio,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(ratio)
	{
		_filter_id = FILTER_INCDEFENCE2;
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incdefence2*>(f));
		filter_Incdefence2* nf = (filter_Incdefence2*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleDefense(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleDefense(_ratio);
			_parent.UpdateDefenseData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCDEFENCE2);
			_parent.InsertTeamVisibleState(HSTATE_INCDEFENCE2, _timeout);
		}
		
	}

	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCDEFENCE2,_timeout);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCDEFENCE2);
		_parent.ImpairScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}

	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Weakelement : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_DEBUFF |FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	int _ratio;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _insertvstate;
		return true;
	}
	filter_Weakelement(){}
public:
	DECLARE_SUBSTANCE(filter_Weakelement); 
	filter_Weakelement(object_interface  object,int ratio,int period, bool insertvstate=true)
			:timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_WEAKELEMENT;
		_ratio = ratio; 
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_WEAKELEMENT);
		_parent.InsertTeamVisibleState(HSTATE_WEAKELEMENT,_timeout);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.ImpairScaleResistance(0, _ratio);
		_parent.ImpairScaleResistance(1, _ratio);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.ImpairScaleResistance(4, _ratio);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_WEAKELEMENT);
		_parent.RemoveTeamVisibleState(HSTATE_WEAKELEMENT);
		_parent.ImpairScaleDefense(_ratio);
		_parent.EnhanceScaleResistance(0, _ratio);
		_parent.EnhanceScaleResistance(1, _ratio);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.EnhanceScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
		_parent.UpdateDefenseData();

	}
};

class filter_Deeppoision : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Deeppoision(){}
public:
	DECLARE_SUBSTANCE(filter_Deeppoision); 
	filter_Deeppoision(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DEEPPOISION;
		_ratio = 1.0f+ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DEEPPOISION,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DEEPPOISION);
	}
};

class filter_Rooted : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _reduce;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _reduce;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _reduce;
		return true;
	}

	filter_Rooted(){}
public:
	DECLARE_SUBSTANCE(filter_Rooted); 
	filter_Rooted(object_interface  object,float reduce,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_ROOTED;
		_reduce = 1.0f - reduce;
		if(_reduce<=0.01f)
			_reduce = 0.01f;
	}

	void AdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		ent.physic_damage   *= _reduce;
		ent.magic_damage[0] *= _reduce;
		ent.magic_damage[1] *= _reduce;
		ent.magic_damage[2] *= _reduce;
		ent.magic_damage[3] *= _reduce;
		ent.magic_damage[4] *= _reduce;

		if(msg.physic_damage >= 1000000) return;//��ֹ���������boss��������
		int damage = (int)(msg.physic_damage * (1 - _reduce) * 2);

		if(msg.short_range>0 || !IS_PHYSIC_ATTACK(msg.attack_attr) || damage <= 1)	
			return;
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.physic_damage	= damage;
		ret.short_range = 0.1;
		ret.attack_rate	 = 1000;
		ret.force_attack = false;
		ret.attack_attr	= attack_msg::MAGIC_ATTACK;
		ret.attack_range = msg.attack_range + 0.5;
		ret.speed = msg.speed;
		_parent.SetRetortState();
		_parent.Attack( attacker, ret, 0);
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ROOTED,_timeout);
		_parent.IncIdleSealMode(MODE_INDEX_ROOT);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ROOTED);
		_parent.DecIdleSealMode(MODE_INDEX_ROOT);
	}
};

class filter_Earthguard : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _reduce;
	int _hp;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _reduce << _hp << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _reduce >> _hp >> _counter;
		return true;
	}

	filter_Earthguard(){}
public:
	DECLARE_SUBSTANCE(filter_Earthguard); 
	filter_Earthguard(object_interface  object,int hp, float reduce, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_EARTHGUARD;
		_reduce = 1.0f - reduce;
		if(_reduce < 0.01f)
			_reduce = 0.01f;
		_hp = hp/period;
		_counter = 0;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		msg.physic_damage = int(msg.physic_damage * _reduce);
		msg.magic_damage[0] = int(msg.magic_damage[0] * _reduce);
		msg.magic_damage[1] = int(msg.magic_damage[1] * _reduce);
		msg.magic_damage[2] = int(msg.magic_damage[2] * _reduce);
		msg.magic_damage[3] = int(msg.magic_damage[3] * _reduce);
		msg.magic_damage[4] = int(msg.magic_damage[4] * _reduce);
	}

	void AdjustDamage(damage_entry & dmg, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= 0.5f;			//�˺�����ֵ�̶�����Ҫ���ȷ��??
		dmg.magic_damage[0] *= 0.5f;
		dmg.magic_damage[1] *= 0.5f;
		dmg.magic_damage[2] *= 0.5f;
		dmg.magic_damage[3] *= 0.5f;
		dmg.magic_damage[4] *= 0.5f;
	}
	
	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.HealBySkill(_hp*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_EARTHGUARD,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_EARTHGUARD);
	}
};

class filter_Fury : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_DEBUFF |FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Fury(){}
public:
	DECLARE_SUBSTANCE(filter_Fury); 
	filter_Fury(object_interface  object,int point,int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FURY;
		_point = point; 
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FURY,_timeout);
		_parent.ImpairScaleDefense(_point * 5);
		_parent.ImpairScaleResistance(0, _point * 5);
		_parent.ImpairScaleResistance(1, _point * 5);
		_parent.ImpairScaleResistance(2, _point * 5);
		_parent.ImpairScaleResistance(3, _point * 5);
		_parent.ImpairScaleResistance(4, _point * 5);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
		_parent.EnhanceAttackDegree(_point);
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FURY);
		_parent.EnhanceScaleDefense(_point * 5);
		_parent.EnhanceScaleResistance(0, _point * 5);
		_parent.EnhanceScaleResistance(1, _point * 5);
		_parent.EnhanceScaleResistance(2, _point * 5);
		_parent.EnhanceScaleResistance(3, _point * 5);
		_parent.EnhanceScaleResistance(4, _point * 5);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
		_parent.ImpairAttackDegree(_point);
		_parent.SendClientAttackData();

	}
};

class filter_Sandstorm : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _attackrate;
	int _praytime;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _attackrate << _praytime;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >>  _attackrate >> _praytime;
		return true;
	}

	filter_Sandstorm(){}
public:
	DECLARE_SUBSTANCE(filter_Sandstorm); 
	filter_Sandstorm(object_interface  object,int attackrate, int praytime, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SANDSTORM;
		_attackrate = attackrate;
		_praytime = praytime;
	}

	void OnAttach()
	{
		(_parent.GetSkillWrapper()).IncPrayTime(_praytime);
		_parent.ImpairScaleAttack(_attackrate);
		_parent.UpdateAttackData();
		_parent.InsertTeamVisibleState(HSTATE_SANDSTORM,_timeout);
	}

	void OnRelease()
	{
		(_parent.GetSkillWrapper()).DecPrayTime(_praytime);
		_parent.EnhanceScaleAttack(_attackrate);
		_parent.UpdateAttackData();
		_parent.RemoveTeamVisibleState(HSTATE_SANDSTORM);
	}
};

class filter_Homefeeling : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _hpmpgen;
	int _speed;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _hpmpgen << _speed;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _hpmpgen >> _speed;
		return true;
	}
	filter_Homefeeling(){}
public:
	DECLARE_SUBSTANCE(filter_Homefeeling); 
	filter_Homefeeling(object_interface  object,int hpmpgen,int speed, int period)
				        :timeout_filter(object,period,FILTER_MASK),_hpmpgen(hpmpgen), _speed(speed)
	{
		_filter_id = FILTER_HOMEFEELING;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_HOMEFEELING,_timeout);
		_parent.EnhanceSpeed(_speed);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		
		_parent.EnhanceHPGen(_hpmpgen);
		_parent.EnhanceMPGen(_hpmpgen);
		_parent.UpdateHPMPGen();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_HOMEFEELING);
		_parent.ImpairSpeed(_speed);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		
		_parent.ImpairHPGen(_hpmpgen);
		_parent.ImpairMPGen(_hpmpgen);
		_parent.UpdateHPMPGen();
	}
};


class filter_Reducewater2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Reducewater2(){}
public:
	DECLARE_SUBSTANCE(filter_Reducewater2); 
	filter_Reducewater2(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_REDUCEWATER2;
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCEWATER2,_timeout);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCEWATER2);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
	}
};

class filter_Incsmite2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Incsmite2(){}
public:
	DECLARE_SUBSTANCE(filter_Incsmite2); 
	filter_Incsmite2(object_interface  object,int inc,int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(inc)
	{
		_filter_id = FILTER_INCSMITE2;
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCSMITE2,_timeout);
		_parent.EnhanceCrit(_point);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCSMITE2);
		_parent.ImpairCrit(_point);
	}
};

class filter_Decdefence2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Decdefence2(){}
public:
	DECLARE_SUBSTANCE(filter_Decdefence2); 
	filter_Decdefence2(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_DECDEFENCE2;
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECDEFENCE2,_timeout);
		_parent.ImpairScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECDEFENCE2);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.UpdateDefenseData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Reducefire2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Reducefire2(){}
public:
	DECLARE_SUBSTANCE(filter_Reducefire2); 
	filter_Reducefire2(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_REDUCEFIRE2;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCEFIRE2,_timeout);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCEFIRE2);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Slowattackpray : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Slowattackpray(){}
public:
	DECLARE_SUBSTANCE(filter_Slowattackpray); 
	filter_Slowattackpray(object_interface  object,int ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SLOWATTACKPRAY;
		_ratio = ratio;
	}

	void OnAttach()
	{
		_parent.ImpairScaleAttackSpeed(_ratio);
		_parent.UpdateAttackData();
		(_parent.GetSkillWrapper()).IncPrayTime(_ratio);
		_parent.InsertTeamVisibleState(HSTATE_SLOWATTACKPRAY,_timeout);
	}

	void OnRelease()
	{
		_parent.EnhanceScaleAttackSpeed(_ratio);
		_parent.UpdateAttackData();
		(_parent.GetSkillWrapper()).DecPrayTime(_ratio);
		_parent.RemoveTeamVisibleState(HSTATE_SLOWATTACKPRAY);
	}
};

class filter_Burning2 : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	filter_Burning2(){}
public:
	DECLARE_SUBSTANCE(filter_Burning2); 
	filter_Burning2(object_interface  object,int period,int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_BURNING2_MERGE;
		else
			_filter_id = FILTER_BURNING2;
		_icon = HSTATE_BURNING2;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_BURNING2,_timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_BURNING2);
	}
};

class filter_Burningfeet : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _fire;
	int _speed;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _fire << _speed;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _fire >> _speed;
		return true;
	}
	filter_Burningfeet(){}
public:
	DECLARE_SUBSTANCE(filter_Burningfeet); 
	filter_Burningfeet(object_interface  object,int fire, int speed, int period)
				        :timeout_filter(object,period,FILTER_MASK),_fire(fire),_speed(speed)
	{
		_filter_id = FILTER_BURNINGFEET;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_BURNINGFEET,_timeout);
		_parent.ImpairSpeed(_speed);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.ImpairScaleResistance(3, _fire);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_BURNINGFEET);
		_parent.EnhanceSpeed(_speed);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.EnhanceScaleResistance(3, _fire);
		_parent.UpdateMagicData();
	}
};

class filter_Hardenskin : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;
	int _ratio2;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _ratio2;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _ratio2;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Hardenskin(){}
public:
	DECLARE_SUBSTANCE(filter_Hardenskin); 
	filter_Hardenskin(object_interface  object,float ratio, int ratio2, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_HARDENSKIN;
		_ratio = 1.0f-ratio;
		if(_ratio < 0.01f)
			_ratio = 0.01f;
		_ratio2 = ratio2;
	}

	void OnAttach()
	{
		_parent.ImpairSpeed(_ratio2);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.IncVisibleState(VSTATE_HARDENSKIN);
		_parent.InsertTeamVisibleState(HSTATE_HARDENSKIN,_timeout);
	}

	void OnRelease()
	{
		_parent.EnhanceSpeed(_ratio2);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.DecVisibleState(VSTATE_HARDENSKIN);
		_parent.RemoveTeamVisibleState(HSTATE_HARDENSKIN);
	}
};

class filter_Reducegold2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Reducegold2(){}
public:
	DECLARE_SUBSTANCE(filter_Reducegold2); 
	filter_Reducegold2(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_REDUCEGOLD2;
	}
	void Merge(filter *f)
	{
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCEGOLD2,_timeout);
		_parent.ImpairScaleResistance(0, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCEGOLD2);
		_parent.EnhanceScaleResistance(0, _ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Leafdance : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;
	int _damage;
	XID _performer;
	attacker_info_t _pinfo;
	bool _invader;
	int _counter;
	char _mode;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _damage;
		ar << _performer;
		ar << _counter;
		ar.push_back(&_pinfo, sizeof(attacker_info_t));
		ar << _invader;
		ar << _mode;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _damage;
		ar >> _performer;
		ar >> _counter;
		ar.pop_back(&_pinfo, sizeof(attacker_info_t));
		ar >> _invader;
		ar >> _mode;
		return true;
	}
	filter_Leafdance(){}
public:
	DECLARE_SUBSTANCE(filter_Leafdance); 
	filter_Leafdance(object_interface  object,int ratio,int period, int damage, int mask=0)
				        :timeout_filter(object,period,FILTER_MASK|mask),_ratio(ratio)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_LEAFDANCE_MERGE;
		else
			_filter_id = FILTER_LEAFDANCE;
		_counter = 0;
		_damage = damage / period;
	}

	void SetUp(const XID& player, const attacker_info_t& info, char mode, bool invader)
	{
		_performer = player;
		_pinfo = info;
		_invader = invader;
		_mode = mode;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_LEAFDANCE,_timeout);
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_LEAFDANCE);
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.BeHurt(_performer, _pinfo, _damage*_counter, _invader, _mode);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Leafdance*>(f));
		filter_Leafdance* nf = (filter_Leafdance*) f;
		
		int tmp = _damage * _timeout;
		_timeout = GetTimeOut(nf);
		_damage = nf->GetDamage() + tmp/_timeout;
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_LEAFDANCE);
			_parent.InsertTeamVisibleState(HSTATE_LEAFDANCE, _timeout);
		}
		
	}
	
	int GetDamage()
	{
		return _damage;
	}

};

class filter_Charred : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;
	int _ratio2;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _ratio2;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _ratio2;
		return true;
	}
	filter_Charred(){}
public:
	DECLARE_SUBSTANCE(filter_Charred); 
	filter_Charred(object_interface  object,int r,int r2, int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_ratio2(r2)
	{
		_filter_id = FILTER_CHARRED;
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_CHARRED,_timeout);
		_parent.ImpairScaleDefense(_ratio);
		_parent.UpdateDefenseData();
		_parent.ImpairScaleDamage(_ratio);
		_parent.ImpairScaleMagicDamage(_ratio);
		_parent.UpdateAttackData();
		_parent.UpdateMagicData();
		_parent.EnhanceSpeed(_ratio2);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_CHARRED);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.UpdateDefenseData();
		_parent.EnhanceScaleDamage(_ratio);
		_parent.EnhanceScaleMagicDamage(_ratio);
		_parent.UpdateAttackData();
		_parent.UpdateMagicData();
		_parent.ImpairSpeed(_ratio2);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Vacuum : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;
	float _ratio2;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _ratio2 << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _ratio2 >> _insertvstate;
		return true;
	}
	
	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio2;
		dmg.magic_damage[0] *= _ratio2;
		dmg.magic_damage[1] *= _ratio2;
		dmg.magic_damage[2] *= _ratio2;
		dmg.magic_damage[3] *= _ratio2;
		dmg.magic_damage[4] *= _ratio2;
	}
	
	filter_Vacuum(){}
public:
	DECLARE_SUBSTANCE(filter_Vacuum); 
	filter_Vacuum(object_interface  object,int r,float r2, int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_VACUUM;
		_ratio2 = 1.0f - r2;
		if(_ratio2 < 0.01f)
			_ratio2 = 0.01f;
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_VACUUM);
		_parent.InsertTeamVisibleState(HSTATE_VACUUM,_timeout);
		(_parent.GetSkillWrapper()).IncPrayTime(_ratio);
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_VACUUM);
		_parent.RemoveTeamVisibleState(HSTATE_VACUUM);
		(_parent.GetSkillWrapper()).DecPrayTime(_ratio);
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Immuneblooding : public filter_Baseimmune	//�������µ�immune,��Ҫ��playerwrapper.cpp����filterʱ�����ж�
{
protected:
	filter_Immuneblooding(){}
public:
	DECLARE_SUBSTANCE(filter_Immuneblooding);
	filter_Immuneblooding(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNEBLOODING,(insertvstate?VSTATE_IMMUNEBLOODING:-1),HSTATE_IMMUNEBLOODING)
	{
		_filter_id = FILTER_IMMUNEBLOODING;			
	}
	
};

class filter_Absorbphysicdamage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _point;
	bool _insertvstate;
	bool _immune_dizzy;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point << _insertvstate << _immune_dizzy;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point >> _insertvstate >> _immune_dizzy;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		float _physic_damage = dmg.physic_damage * damage_adjust * 0.99f;
		if((int)_physic_damage <= 1) return;
		
		if(_point <= (int)_physic_damage)
		{
			float r = 1.0f - _point*0.99/_physic_damage;
			dmg.physic_damage *= r;
			_point = 0;
			_is_deleted = true;
		}
		else
		{
			dmg.physic_damage *= 0.01f;	
			_point -= (int)_physic_damage;
		}
	}

	filter_Absorbphysicdamage(){}
public:
	DECLARE_SUBSTANCE(filter_Absorbphysicdamage); 
	filter_Absorbphysicdamage(object_interface  object, int point, int period, bool insertvstate=true, bool immune_dizzy = false)
				        :timeout_filter(object,period,FILTER_MASK),_point(point),_insertvstate(insertvstate),_immune_dizzy(immune_dizzy)
	{
		_filter_id = FILTER_ABSORBPHYSICDAMAGE;
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_ABSORBPHYSICDAMAGE);
		if(_immune_dizzy)
			_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.InsertTeamVisibleState(HSTATE_ABSORBPHYSICDAMAGE,_timeout);
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_ABSORBPHYSICDAMAGE);
		if(_immune_dizzy)
			_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.RemoveTeamVisibleState(HSTATE_ABSORBPHYSICDAMAGE);
	}
	
};

class filter_Absorbmagicdamage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE |FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _point;
	bool _insertvstate;
	bool _immune_dizzy;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point << _insertvstate << _immune_dizzy;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point >> _insertvstate >> _immune_dizzy;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		float _magic_damage = (dmg.magic_damage[0] + dmg.magic_damage[1] + dmg.magic_damage[2] + dmg.magic_damage[3] + dmg.magic_damage[4]) * damage_adjust * 0.99f; 
		if((int)_magic_damage <= 1) return;
		
		if(_point <= (int)_magic_damage)
		{
			float r = 1.0f - _point*0.99f/_magic_damage;
			dmg.magic_damage[0] *= r;
			dmg.magic_damage[1] *= r;
			dmg.magic_damage[2] *= r;
			dmg.magic_damage[3] *= r;
			dmg.magic_damage[4] *= r;
			_point = 0;
			_is_deleted = true;
		}
		else
		{
			dmg.magic_damage[0] *= 0.01f;
			dmg.magic_damage[1] *= 0.01f;
			dmg.magic_damage[2] *= 0.01f;
			dmg.magic_damage[3] *= 0.01f;
			dmg.magic_damage[4] *= 0.01f;
			_point -= (int)_magic_damage;
		}
	}

	filter_Absorbmagicdamage(){}
public:
	DECLARE_SUBSTANCE(filter_Absorbmagicdamage); 
	filter_Absorbmagicdamage(object_interface  object, int point, int period, bool insertvstate=true, bool immune_dizzy = false)
				        :timeout_filter(object,period,FILTER_MASK),_point(point),_insertvstate(insertvstate),_immune_dizzy(immune_dizzy)
	{
		_filter_id = FILTER_ABSORBMAGICDAMAGE;
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_ABSORBMAGICDAMAGE);
		if(_immune_dizzy)
			_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.InsertTeamVisibleState(HSTATE_ABSORBMAGICDAMAGE,_timeout);
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_ABSORBMAGICDAMAGE);
		if(_immune_dizzy)
			_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.RemoveTeamVisibleState(HSTATE_ABSORBMAGICDAMAGE);
	}
	
};

class filter_Retortmagic : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_ADJUST_DAMAGE |FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _point;
		return true;
	}

	filter_Retortmagic(){}
public:
	DECLARE_SUBSTANCE(filter_Retortmagic); 
	filter_Retortmagic(object_interface  object,float ratio, int point,int period)
				        :timeout_filter(object,period,FILTER_MASK), _ratio(ratio), _point(point)
	{
		_filter_id = FILTER_RETORTMAGIC;
	}

	void AdjustDamage(damage_entry & dmg, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		int _magic_damage = msg.magic_damage[0] + msg.magic_damage[1] + msg.magic_damage[2] + msg.magic_damage[3] + msg.magic_damage[4]; 
		int damage = int(_magic_damage * _ratio);
		if(IS_PHYSIC_ATTACK(msg.attack_attr) || damage <= 1 || msg._attack_state & AT_STATE_ALL_RETORT)return;	//�����˺������ٴη���
		
		if(_point <= damage)
		{
			damage = _point;
			_point = 0;
			_is_deleted = true;
		}
		else
			_point -= damage;	
		
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		float r = (float)damage/(float)_magic_damage;
		ret.magic_damage[0]	= int(msg.magic_damage[0] * r);
		ret.magic_damage[1]	= int(msg.magic_damage[1] * r);
		ret.magic_damage[2]	= int(msg.magic_damage[2] * r);
		ret.magic_damage[3]	= int(msg.magic_damage[3] * r);
		ret.magic_damage[4]	= int(msg.magic_damage[4] * r);
		ret.short_range = 0.1;
		ret.attack_rate	 = 1000;
		ret.force_attack = false;
		ret.attack_attr	= attack_msg::MAGIC_ATTACK;
		ret.attack_range = msg.attack_range + 0.5;
		ret.speed = msg.speed;
		_parent.SetRetortState();
		_parent.Attack( attacker, ret, 0);
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_RETORTMAGIC,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_RETORTMAGIC);
	}
	
};

class filter_Windshield : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _reduce;
	int _inc;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _reduce << _inc << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _reduce >> _inc >> _insertvstate;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _reduce;
		dmg.magic_damage[0] *= _reduce;
		dmg.magic_damage[1] *= _reduce;
		dmg.magic_damage[2] *= _reduce;
		dmg.magic_damage[3] *= _reduce;
		dmg.magic_damage[4] *= _reduce;
	}

	filter_Windshield(){}
public:
	DECLARE_SUBSTANCE(filter_Windshield); 
	filter_Windshield(object_interface  object,float reduce, int inc, int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _inc(inc), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_WINDSHIELD;
		_reduce = 1.0f-reduce;
		if(_reduce < 0.01f)
			_reduce = 0.01f;
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_WINDSHIELD);
		_parent.InsertTeamVisibleState(HSTATE_WINDSHIELD,_timeout);
		_parent.EnhanceScaleArmor(_inc);
		_parent.UpdateDefenseData();
		_parent.EnhanceScaleAttackSpeed(_inc);
		_parent.UpdateAttackData();
		
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_WINDSHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_WINDSHIELD);
		_parent.ImpairScaleArmor(_inc);
		_parent.UpdateDefenseData();
		_parent.ImpairScaleAttackSpeed(_inc);
		_parent.UpdateAttackData();
	}
};

class filter_Airstreamlock : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _roottimeout;
	int _sealtimeout;
	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _roottimeout << _sealtimeout << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _roottimeout >> _sealtimeout >> _insertvstate;
		return true;
	}

	filter_Airstreamlock(){}
public:
	DECLARE_SUBSTANCE(filter_Airstreamlock); 
	filter_Airstreamlock(object_interface  object,int rootperiod, float sealprob, int sealperiod, bool insertvstate=true)
				        :timeout_filter(object,rootperiod,FILTER_MASK), _insertvstate(insertvstate)
	{
		ASSERT(rootperiod > 0 && sealperiod > 0);
		_filter_id = FILTER_AIRSTREAMLOCK;
		//ȷ��timeout
		if((rand()%100) >= sealprob)
			sealperiod = 0;
		if(sealperiod > 0 && sealperiod > rootperiod)
			_timeout = sealperiod;
		//���㶨���ͷ�ӡʱ�䵽ʱ��timeoutֵ
		_roottimeout = _timeout - rootperiod;
		if(sealperiod <= 0)
			_sealtimeout = -1;
		else
			_sealtimeout = _timeout - sealperiod;
	}

	void OnAttach()
	{
		if(_roottimeout >= 0)
			_parent.IncIdleSealMode(MODE_INDEX_ROOT);
		if(_sealtimeout >= 0)
			_parent.IncIdleSealMode(MODE_INDEX_SILENT);
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_AIRSTREAMLOCK);
		_parent.InsertTeamVisibleState(HSTATE_AIRSTREAMLOCK,_timeout);
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_AIRSTREAMLOCK);
		_parent.RemoveTeamVisibleState(HSTATE_AIRSTREAMLOCK);
	}

	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_roottimeout >= 0 && _timeout <= _roottimeout)	
		{
			_roottimeout = -1;
			_parent.DecIdleSealMode(MODE_INDEX_ROOT);
		}	
		if(_sealtimeout >= 0 && _timeout <= _sealtimeout)
		{
			_sealtimeout = -1;
			_parent.DecIdleSealMode(MODE_INDEX_SILENT);
		}	
	}

};

class filter_Closed : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_BUFF
	};

	filter_Closed(){}
public:
	DECLARE_SUBSTANCE(filter_Closed); 
	filter_Closed(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_CLOSED;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_SILENT);
		_parent.IncImmuneMask(IMMUNEPHYSICAL);
		_parent.InsertTeamVisibleState(HSTATE_CLOSED,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_SILENT);
		_parent.DecImmuneMask(IMMUNEPHYSICAL);
		_parent.RemoveTeamVisibleState(HSTATE_CLOSED);
	}

};

class filter_Insertvstate : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};
	
	int _vstate;
	int _hstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _vstate << _hstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _vstate >> _hstate;
		return true;
	}

	filter_Insertvstate(){}
public:
	DECLARE_SUBSTANCE(filter_Insertvstate); 
	filter_Insertvstate(object_interface  object,int period, int vstate, int hstate=0, int mask=0)
				        :timeout_filter(object,period,FILTER_MASK|mask),_vstate(vstate),_hstate(hstate)
	{
		ASSERT(_vstate >= 0 && _vstate < VSTATE_MAX);
		_filter_id = FILTER_INSERTVSTATE;
	}

	void OnAttach()
	{
		if(_vstate)
			_parent.IncVisibleState(_vstate);
		if(_hstate)
			_parent.InsertTeamVisibleState(_hstate,_timeout);
	}

	void OnRelease()
	{
		if(_vstate)
			_parent.DecVisibleState(_vstate);
		if(_hstate)
			_parent.RemoveTeamVisibleState(_hstate);
	}

};

class filter_Immuneweak : public filter_Baseimmune	//�����˺�����
{
protected:
	filter_Immuneweak(){}
public:
	DECLARE_SUBSTANCE(filter_Immuneweak);
	filter_Immuneweak(object_interface object, int period, bool insertvstate=true)
						:filter_Baseimmune(object,period,IMMUNEWEAK,(insertvstate?VSTATE_IMMUNEWEAK:-1),HSTATE_IMMUNEWEAK)
	{
		_filter_id = FILTER_IMMUNEWEAK;			
	}
	
};

class filter_Befrozen : public timeout_filter   //ͬѣ��
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_Befrozen(){}
public:
	DECLARE_SUBSTANCE(filter_Befrozen); 
	filter_Befrozen(object_interface  object,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_BEFROZEN;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_STUN);
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_BEFROZEN);
		_parent.InsertTeamVisibleState(HSTATE_BEFROZEN,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_STUN);
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_BEFROZEN);
		_parent.RemoveTeamVisibleState(HSTATE_BEFROZEN);
	}

};

class filter_Fallen2 : public filter_Wounded	//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_TRANSFERABLE_DEBUFF 
	};
	
	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		filter_Wounded::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Wounded::Load(ar);
		ar >> _insertvstate;
		return true;
	}
	
	filter_Fallen2(){}
public:
	DECLARE_SUBSTANCE(filter_Fallen2); 
	filter_Fallen2(object_interface  object,int period,int damage,bool insertvstate=true,int mask=FILTER_MASK_DEBUFF)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask),_insertvstate(insertvstate)
	{
		if(mask & FILTER_MASK_MERGE)
			_filter_id = FILTER_FALLEN2_MERGE;
		else
			_filter_id = FILTER_FALLEN2;
		_icon = HSTATE_FALLEN2;
	}

	void OnAttach() 
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_FALLEN);
		_parent.InsertTeamVisibleState(HSTATE_FALLEN2,_timeout);
	}
	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_FALLEN);
		_parent.RemoveTeamVisibleState(HSTATE_FALLEN2);
	}
};

class filter_Sealed2 : public timeout_filter   // �޷�����//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	
	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_Sealed2(){}
public:
	DECLARE_SUBSTANCE(filter_Sealed2); 
	filter_Sealed2(object_interface  object,int period, bool insertvstate=true, int mask=FILTER_MASK_DEBUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_SEALED2;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_SILENT);
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_SEALED);
		_parent.InsertTeamVisibleState(HSTATE_SEALED2,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_SILENT);
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_SEALED);
		_parent.RemoveTeamVisibleState(HSTATE_SEALED2);
	}

};

class filter_Fix2 : public timeout_filter // ����//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};
	
	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_Fix2(){}
public:
	DECLARE_SUBSTANCE(filter_Fix2); 
	filter_Fix2(object_interface  object,int period, bool insertvstate=true,int mask =FILTER_MASK_DEBUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_FIX2;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_ROOT);
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_FIX);
		_parent.InsertTeamVisibleState(HSTATE_FIX2,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_ROOT);
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_FIX);
		_parent.RemoveTeamVisibleState(HSTATE_FIX2);
	}

};

class filter_Dechurt2 : public timeout_filter	//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Dechurt2(){}
public:
	DECLARE_SUBSTANCE(filter_Dechurt2); 
	filter_Dechurt2(object_interface  object,float ratio, int period, int mask=FILTER_MASK_BUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_DECHURT2;
		_ratio = 1.0-ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECHURT2,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECHURT2);
	}
};

class filter_Inchurt2 : public timeout_filter		//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	float _ratio;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _insertvstate;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Inchurt2(){}
public:
	DECLARE_SUBSTANCE(filter_Inchurt2); 
	filter_Inchurt2(object_interface  object,float ratio, int period, bool insertvstate=true,int mask=FILTER_MASK_DEBUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_INCHURT2;
		_ratio = 1.0+ratio;
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_INFAUST);
		_parent.InsertTeamVisibleState(HSTATE_INCHURT2,_timeout);
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_INFAUST);
		_parent.RemoveTeamVisibleState(HSTATE_INCHURT2);
	}
};

class filter_Inchp2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _insertvstate;
		return true;
	}
	filter_Inchp2(){}
public:
	DECLARE_SUBSTANCE(filter_Inchp2); 
	filter_Inchp2(object_interface  object,int r,int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_INCHP2;
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCHP2,_timeout);
		_parent.EnhanceScaleMaxHP(_ratio);
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Inchp2*>(f));
		filter_Inchp2* nf = (filter_Inchp2*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleMaxHP(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleMaxHP(_ratio);
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCHP2);
			_parent.InsertTeamVisibleState(HSTATE_INCHP2, _timeout);
		}
		
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCHP2);
		_parent.ImpairScaleMaxHP(_ratio);
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Incattack2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _insertvstate;
		return true;
	}
	filter_Incattack2(){}
public:
	DECLARE_SUBSTANCE(filter_Incattack2); 
	filter_Incattack2(object_interface  object,int r,int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_INCATTACK2;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incattack2*>(f));
		filter_Incattack2* nf = (filter_Incattack2*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleDamage(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleDamage(_ratio);
			_parent.UpdateAttackData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCATTACK2);
			_parent.InsertTeamVisibleState(HSTATE_INCATTACK2, _timeout);
		}
		
	}
	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCATTACK2,_timeout);
		_parent.EnhanceScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCATTACK2);
		_parent.ImpairScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Incmagic2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _insertvstate;
		return true;
	}
	filter_Incmagic2(){}
public:
	DECLARE_SUBSTANCE(filter_Incmagic2); 
	filter_Incmagic2(object_interface  object,int r,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_INCMAGIC2;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incmagic2*>(f));
		filter_Incmagic2* nf = (filter_Incmagic2*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleMagicDamage(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleMagicDamage(_ratio);
			_parent.UpdateMagicData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCMAGIC2);
			_parent.InsertTeamVisibleState(HSTATE_INCMAGIC2, _timeout);
		}
		
	}
	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCMAGIC2,_timeout);
		_parent.EnhanceScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCMAGIC2);
		_parent.ImpairScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Fastpray2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Fastpray2(){}
public:
	DECLARE_SUBSTANCE(filter_Fastpray2); 
	filter_Fastpray2(object_interface  object,int ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FASTPRAY2;
		_ratio = ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FASTPRAY2,_timeout);
		(_parent.GetSkillWrapper()).DecPrayTime(_ratio);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FASTPRAY2);
		(_parent.GetSkillWrapper()).IncPrayTime(_ratio);
	}
};

class filter_Speedup2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _insertvstate;
		return true;
	}
	filter_Speedup2(){}
public:
	DECLARE_SUBSTANCE(filter_Speedup2); 
	filter_Speedup2(object_interface  object,int r,int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_SPEEDUP2;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Speedup2*>(f));
		filter_Speedup2* nf = (filter_Speedup2*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairSpeed(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceSpeed(_ratio);
			_parent.UpdateSpeedData();
			_parent.SendClientCurSpeed();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SPEEDUP2);
			_parent.InsertTeamVisibleState(HSTATE_SPEEDUP2, _timeout);
		}
		
	}

	void OnAttach()
	{
		if(_insertvstate)
			_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_SPEEDUP2,_timeout);
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		if(_insertvstate)
			_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_SPEEDUP2);
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Aurabase : public timeout_filter //ÿ����������Χ���й������buff
{
protected:
	char _counter;
	int _t0,_t1,_t2;
	int _step;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _counter << _t0 << _t1 << _t2;
		return true;
	}
	
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _counter >> _t0 >> _t1 >> _t2;
		return true;
	}
	filter_Aurabase(){}
public:
	filter_Aurabase(object_interface object, int period, int mask, int step = 3)
			:timeout_filter(object, period, mask)
	{
		_counter = 0;
		_t0 = _t1 = _t2 = 0;
		_step = step > 0 ? step : 3;
	}

	void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter >= _step || tick >= _timeout)
		{
			DoAura();
			_counter -= _step;		
		}
		timeout_filter::Heartbeat(tick);
	}

	virtual void DoAura()
	{
		ASSERT(false);
	}

	void SetTalent(int t0, int t1, int t2){ _t0 = t0; _t1 = t1; _t2 = t2;}
};

class filter_Aurafireattack : public filter_Aurabase		//�⹥���⻷
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	int _damage;
	float _range;

	virtual bool Save(archive & ar)
	{
		filter_Aurabase::Save(ar);
		ar << _damage << _range;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Aurabase::Load(ar);
		ar >> _damage >> _range;
		return true;
	}
	
	filter_Aurafireattack(){}
public:
	DECLARE_SUBSTANCE(filter_Aurafireattack);
	filter_Aurafireattack(object_interface object, int period, int damage, float range)
			:filter_Aurabase(object, period, FILTER_MASK),_damage(damage),_range(range)
	{
		_filter_id = FILTER_AURAFIREATTACK;					
	}

	virtual void DoAura()
	{
		attack_msg	msg;
		memset(&msg,0,sizeof(msg));
		msg.attack_range  = _range;
		msg.physic_damage = 0;
		msg.attack_rate	= (int)(_parent.GetExtendProp().attack); 
		msg.magic_damage[3] = _damage;
		msg.attack_attr = attack_msg::MAGIC_ATTACK;
		msg.force_attack = _parent.GetForceAttack();
		msg.speed = 0;
		
		_parent.SetAuraAttackState();
		_parent.EnterCombatState();
		_parent.RegionAttack1(_parent.GetPos(), _range, msg, 0, XID(-1,-1));
	}
	
	void OnAttach()
	{
		
	}

	void OnRelease()
	{
		
	}	
};

class filter_Aurabless : public filter_Aurabase		//ף���⻷
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	float _range;
	int _skill;
	int _level;
	bool _except_self;
	
	virtual bool Save(archive & ar)
	{
		filter_Aurabase::Save(ar);
		ar << _range << _skill << _level << _except_self;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Aurabase::Load(ar);
		ar >> _range >> _skill >> _level >> _except_self;
		return true;
	}
	
	filter_Aurabless(){}
public:
	DECLARE_SUBSTANCE(filter_Aurabless);
	filter_Aurabless(object_interface object, int period, float range, int skill, int level, int step = 3,bool ex = false)
			:filter_Aurabase(object, period, FILTER_MASK, step),_range(range),_skill(skill),_level(level),_except_self(ex)
	{
		_filter_id = FILTER_AURABLESS;					
	}

	virtual void DoAura()
	{
		enchant_msg	msg;
		memset(&msg,0,sizeof(msg));
		msg.attack_range  = _range;
		msg.skill = _skill;
		msg.skill_level = _level;
		msg.helpful = 1;
		msg.skill_modify[0] = _t0;
		msg.skill_modify[1] = _t1;
		msg.skill_modify[2] = _t2;
		
		_parent.SetAuraAttackState();
		if(_parent.IsInTeam())
		{
			_parent.TeamEnchant(msg,_except_self);	
		}
		else if(!_except_self)
		{
			_parent.Enchant(_parent.GetSelfID(), msg);	
		}
	}
	
	void OnAttach()
	{
		
	}

	void OnRelease()
	{
		
	}	

};

class filter_Auracurse : public filter_Aurabase		//�����??
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	float _range;
	int _skill;
	int _level;
	
	virtual bool Save(archive & ar)
	{
		filter_Aurabase::Save(ar);
		ar << _range << _skill << _level;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Aurabase::Load(ar);
		ar >> _range >> _skill >> _level;
		return true;
	}
	
	filter_Auracurse(){}
public:
	DECLARE_SUBSTANCE(filter_Auracurse);
	filter_Auracurse(object_interface object, int period, float range, int skill, int level, int step = 3)
			:filter_Aurabase(object, period, FILTER_MASK, step),_range(range),_skill(skill),_level(level)
	{
		_filter_id = FILTER_AURACURSE;					
	}

	virtual void DoAura()
	{
		enchant_msg	msg;
		memset(&msg,0,sizeof(msg));
		msg.attack_range  = _range;
		msg.skill = _skill;
		msg.skill_level = _level;
		msg.helpful = 0;
		msg.force_attack = _parent.GetForceAttack();
		msg.skill_modify[0] = _t0;
		msg.skill_modify[1] = _t1;
		msg.skill_modify[2] = _t2;

		_parent.SetAuraAttackState();
		_parent.EnterCombatState();
		_parent.RegionEnchant1(_parent.GetPos(), _range, msg, XID(-1,-1));
	}
	
	void OnAttach()
	{
		
	}

	void OnRelease()
	{
		
	}	

};

class filter_Incantiinvisibleactive : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		return true;
	}

	filter_Incantiinvisibleactive(){}
public:
	DECLARE_SUBSTANCE(filter_Incantiinvisibleactive); 
	filter_Incantiinvisibleactive(object_interface  object,int period, int inc)
				        :timeout_filter(object,period,FILTER_MASK),_inc(inc)
	{
		_filter_id = FILTER_INCANTIINVISIBLEACTIVE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCANTIINVISIBLEACTIVE,_timeout);
		_parent.IncAntiInvisibleActive(_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCANTIINVISIBLEACTIVE);
		_parent.DecAntiInvisibleActive(_inc);
	}
};

class filter_Inchpsteal : public timeout_filter		//�⻷Ч����Ѫʹ�õ�״̬,������MERGE
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		return true;
	}

	filter_Inchpsteal(){}
public:
	DECLARE_SUBSTANCE(filter_Inchpsteal); 
	filter_Inchpsteal(object_interface  object,int period, int inc)
				        :timeout_filter(object,period,FILTER_MASK),_inc(inc)
	{
		_filter_id = FILTER_INCHPSTEAL;
	}
	
    void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Inchpsteal*>(f));
		filter_Inchpsteal* nf = (filter_Inchpsteal*)f;
		if(nf->GetInc() == _inc)
		{
			_timeout = GetTimeOut(nf);
		}
		else if(nf->GetInc() > _inc)
		{
			_parent.ImpairHpSteal(_inc);
			_inc = nf->GetInc();
			_parent.EnhanceHpSteal(_inc);
			_timeout = GetTimeOut(nf);
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCHPSTEAL);
			_parent.InsertTeamVisibleState(HSTATE_INCHPSTEAL, _timeout);
		}
		
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCHPSTEAL,_timeout);
		_parent.EnhanceHpSteal(_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCHPSTEAL);
		_parent.ImpairHpSteal(_inc);
	}

	int GetInc()
	{
		return _inc;	
	}
};

class filter_Inccritdamage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		return true;
	}

	filter_Inccritdamage(){}
public:
	DECLARE_SUBSTANCE(filter_Inccritdamage); 
	filter_Inccritdamage(object_interface  object,int period, int inc)
				        :timeout_filter(object,period,FILTER_MASK),_inc(inc)
	{
		_filter_id = FILTER_INCCRITDAMAGE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCCRITDAMAGE,_timeout);
		_parent.EnhanceCritDamage(_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCCRITDAMAGE);
		_parent.ImpairCritDamage(_inc);
	}
};

class filter_Incdamagedodge : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		return true;
	}

	filter_Incdamagedodge(){}
public:
	DECLARE_SUBSTANCE(filter_Incdamagedodge); 
	filter_Incdamagedodge(object_interface  object,int period, int inc)
				        :timeout_filter(object,period,FILTER_MASK),_inc(inc)
	{
		_filter_id = FILTER_INCDAMAGEDODGE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCDAMAGEDODGE,_timeout);
		_parent.IncVisibleState(VSTATE_INCDAMAGEDODGE);
		_parent.EnhanceDamageDodge(_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCDAMAGEDODGE);
		_parent.DecVisibleState(VSTATE_INCDAMAGEDODGE);
		_parent.ImpairDamageDodge(_inc);
	}
};

class filter_Incdebuffdodge : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		return true;
	}

	filter_Incdebuffdodge(){}
public:
	DECLARE_SUBSTANCE(filter_Incdebuffdodge); 
	filter_Incdebuffdodge(object_interface  object,int period, int inc)
				        :timeout_filter(object,period,FILTER_MASK),_inc(inc)
	{
		_filter_id = FILTER_INCDEBUFFDODGE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCDEBUFFDODGE,_timeout);
		_parent.IncVisibleState(VSTATE_INCDEBUFFDODGE);
		_parent.EnhanceDebuffDodge(_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCDEBUFFDODGE);
		_parent.DecVisibleState(VSTATE_INCDEBUFFDODGE);
		_parent.ImpairDebuffDodge(_inc);
	}
};

class filter_Rebirth : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_BEFORE_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _rebirth_prob;
	float _life_after_rebirth;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _rebirth_prob << _life_after_rebirth;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _rebirth_prob >> _life_after_rebirth;
		return true;
	}

	filter_Rebirth(){}
public:
	DECLARE_SUBSTANCE(filter_Rebirth);
	filter_Rebirth(object_interface parent, int period, int rebirth_prob, float life_after_rebirth)
		:timeout_filter(parent,period,FILTER_MASK),_rebirth_prob(rebirth_prob),_life_after_rebirth(life_after_rebirth)
	{   
		_filter_id = FILTER_REBIRTH;
		if(_life_after_rebirth > 1.0f) _life_after_rebirth = 1.0f;
		if(_life_after_rebirth < 0.01f) _life_after_rebirth = 0.01f;
	}

	virtual void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REBIRTH,_timeout);
	}
	
	virtual void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REBIRTH);
	}

	virtual void BeforeDeath(const XID & attacker, char attacker_mode)
	{
		if(rand()%100 >= _rebirth_prob) return;
		_parent.Heal(int(_parent.GetExtendProp().max_hp*_life_after_rebirth));
		_parent.SendClientEnchantResult(_parent.GetSelfID(), 1085, 1, false, 0, 0);
		_is_deleted = true;
	}
};

class filter_Soulbase : public timeout_filter //����һ�������״�?������ݻ������������ǹ���??
{
protected:
	int _trigger_prob;
	int _mp_cost_per_trigger;
	char _del_on_trigger;	//0:��Ч��״̬����ʧ 1:��Ч��״̬��ʧ 2:��������״̬����ʧ 
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _trigger_prob << _mp_cost_per_trigger << _del_on_trigger;
		return true;
	}
	
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _trigger_prob >> _mp_cost_per_trigger >> _del_on_trigger;
		return true;
	}
	filter_Soulbase(){}
public:
	filter_Soulbase(object_interface object, int period, int mask, int trigger_prob, int mp_cost_per_trigger, char del_on_trigger)
			:timeout_filter(object, period, mask),_trigger_prob(trigger_prob),_mp_cost_per_trigger(mp_cost_per_trigger),_del_on_trigger(del_on_trigger)
	{
		ASSERT(mask & (FILTER_MASK_MERGE|FILTER_MASK_ADJUST_DAMAGE));
	}

	void AdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(_del_on_trigger == 2) _is_deleted = true;
		if(rand()%100 >= _trigger_prob)	return;
		if(_mp_cost_per_trigger > 0 && _parent.GetBasicProp().mp < _mp_cost_per_trigger) return;
		if(!DoSoulAdjustDamage(ent,attacker,msg,damage_adjust)) return;
		if(_mp_cost_per_trigger > 0) _parent.DrainMana(_mp_cost_per_trigger);
		if(_del_on_trigger == 1) _is_deleted = true;
	}
	
	void Merge(filter *f)
	{
		ASSERT(false);	
	}

	virtual bool DoSoulAdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		ASSERT(false);	
		return false;
	}

};

class filter_Soulretort : public filter_Soulbase
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_SAVE_DB_DATA
	};
	
	int _retort_damage;	
	
	virtual bool Save(archive & ar)
	{
		//���filter�����ߺ󱣴棬����ʱ
		//����_timeout
		int tmp = _timeout;
		_timeout += time(NULL);
		
		filter_Soulbase::Save(ar);
		ar << _retort_damage;
		
		//�ָ�_timeout
		_timeout = tmp;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Soulbase::Load(ar);
		ar >> _retort_damage;

		//�ָ�_timeout
		_timeout -= time(NULL);
		if(_timeout <= 0) _timeout = 1;
		return true;
	}
	
	filter_Soulretort(){}
public:
	DECLARE_SUBSTANCE(filter_Soulretort);
	filter_Soulretort(object_interface object,int period,int retort_damage,int trigger_prob,int mp_cost,char del_on_trigger)
			:filter_Soulbase(object,period,FILTER_MASK,trigger_prob,mp_cost,del_on_trigger),_retort_damage(retort_damage)
	{
		_filter_id = FILTER_SOULRETORT;	
	}

	void Merge(filter* f)
	{
		ASSERT(dynamic_cast<filter_Soulretort*>(f));	
		filter_Soulretort* nf = (filter_Soulretort*) f;
		if(nf->GetValue() == _retort_damage)
		{
			if(GetTimeOut(nf) > _timeout) _timeout = GetTimeOut(nf);		
		}
		else if(nf->GetValue() > _retort_damage)
		{
			_timeout = GetTimeOut(nf);
			_retort_damage = nf->GetValue();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SOULRETORT);
			_parent.InsertTeamVisibleState(HSTATE_SOULRETORT, _timeout);
		}
	}

	bool DoSoulAdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg._attack_state & AT_STATE_ALL_RETORT || _retort_damage <= 1)	
			return false;
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.physic_damage	= _retort_damage;
		ret.attack_rate	= 1000;
		ret.force_attack = _parent.GetForceAttack();
		ret.attack_attr = attack_msg::MAGIC_ATTACK;
		ret.attack_range = msg.attack_range + 0.5;
		ret.speed = msg.speed;
		ret.skill_id = 1146;
		_parent.SetReboundState();
		_parent.Attack( attacker, ret, 0);
		return true;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_SOULRETORT);
		_parent.InsertTeamVisibleState(HSTATE_SOULRETORT,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_SOULRETORT);
		_parent.RemoveTeamVisibleState(HSTATE_SOULRETORT);
	}

	int GetValue()
	{
		return _retort_damage;	
	}
};

class filter_Soulsealed : public filter_Soulbase
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_SAVE_DB_DATA
	};

	int _level;
	
	virtual bool Save(archive & ar)
	{
		//���filter�����ߺ󱣴棬����ʱ
		//����_timeout
		int tmp = _timeout;
		//����filter���ڵľ���ʱ��
		_timeout += time(NULL);

		filter_Soulbase::Save(ar);
		ar << _level;
		
		//�ָ�_timeout
		_timeout = tmp;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Soulbase::Load(ar);
		ar >> _level;
		
		//�ָ�_timeout
		_timeout -= time(NULL);
		if(_timeout <= 0) _timeout = 1;
		return true;
	}
	
	filter_Soulsealed(){}
public:
	DECLARE_SUBSTANCE(filter_Soulsealed);
	filter_Soulsealed(object_interface  object,int period,int level,int trigger_prob,int mp_cost,char del_on_trigger)
			:filter_Soulbase(object,period,FILTER_MASK,trigger_prob,mp_cost,del_on_trigger),_level(level)
	{
		_filter_id = FILTER_SOULSEALED;	
		if(_level < 1) _level = 1;
		if(_level > 20) _level = 20;
	}
	
	void Merge(filter* f)
	{
		ASSERT(dynamic_cast<filter_Soulsealed*>(f));	
		filter_Soulsealed* nf = (filter_Soulsealed*) f;
		if(nf->GetValue() == _level)
		{
			if(GetTimeOut(nf) > _timeout) _timeout = GetTimeOut(nf);		
		}
		else if(nf->GetValue() > _level)
		{
			_timeout = GetTimeOut(nf);
			_level = nf->GetValue();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SOULSEALED);
			_parent.InsertTeamVisibleState(HSTATE_SOULSEALED, _timeout);
		}
	}
	
	bool DoSoulAdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg._attack_state & AT_STATE_ALL_RETORT) return false;
		enchant_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.attack_range  = msg.attack_range + 0.5;
		ret.skill = 1092;	//������ܵ�״�?������??100%��ӡ
		ret.skill_level = _level;
		ret.helpful = 0;
		ret.force_attack = _parent.GetForceAttack();

		_parent.EnterCombatState();
		_parent.SetReboundState();
		_parent.DelayEnchant(attacker, ret, 10);	//�ӳ�0.5��
		return true;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_SOULSEALED);
		_parent.InsertTeamVisibleState(HSTATE_SOULSEALED,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_SOULSEALED);
		_parent.RemoveTeamVisibleState(HSTATE_SOULSEALED);
	}

	int GetValue()
	{
		return _level;	
	}
};

class filter_Soulbeatback : public filter_Soulbase
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_ADJUST_DAMAGE
	};

	int _retort_damage;	//������ȥ�Ĺ��������Լ����ٵĹ���

	virtual bool Save(archive & ar)
	{
		filter_Soulbase::Save(ar);
		ar << _retort_damage;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Soulbase::Load(ar);
		ar >> _retort_damage;
		return true;
	}
	
	filter_Soulbeatback(){}
public:
	DECLARE_SUBSTANCE(filter_Soulbeatback);
	filter_Soulbeatback(object_interface  object,int period,int retort_damage,int trigger_prob,int mp_cost,bool del_on_trigger)
			:filter_Soulbase(object,period,FILTER_MASK,trigger_prob,mp_cost,del_on_trigger),_retort_damage(retort_damage)
	{
		_filter_id = FILTER_SOULBEATBACK;	
	}
	
	void Merge(filter* f)
	{
		ASSERT(dynamic_cast<filter_Soulbeatback*>(f));	
		filter_Soulbeatback* nf = (filter_Soulbeatback*) f;
		if(nf->GetValue() == _retort_damage)
		{
			if(GetTimeOut(nf) > _timeout) _timeout = GetTimeOut(nf);		
		}
		else if(nf->GetValue() > _retort_damage)
		{
			_timeout = GetTimeOut(nf);
			_retort_damage = nf->GetValue();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SOULBEATBACK);
			_parent.InsertTeamVisibleState(HSTATE_SOULBEATBACK, _timeout);
		}
		
	}
	
	bool DoSoulAdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg._attack_state & AT_STATE_ALL_RETORT) return false;
		
		int damage_all = msg.physic_damage + msg.magic_damage[0] + msg.magic_damage[1] + msg.magic_damage[2] + msg.magic_damage[3] + msg.magic_damage[4];
		float r = _retort_damage/(float)damage_all;
		(const_cast<attack_msg &>(msg))._attack_state |= 0x0800;	//״̬����
		float r2 = 1 - r;
		if(r2 < 0.01f) r2 = 0.01f;
		ent.physic_damage *= r2;									//�˺�����
		ent.magic_damage[0] *= r2;
		ent.magic_damage[1] *= r2;
		ent.magic_damage[2] *= r2;
		ent.magic_damage[3] *= r2;
		ent.magic_damage[4] *= r2;
	
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.physic_damage = int(msg.physic_damage * r);
		ret.magic_damage[0] = int(msg.magic_damage[0] * r);
		ret.magic_damage[1] = int(msg.magic_damage[1] * r);
		ret.magic_damage[2] = int(msg.magic_damage[2] * r);
		ret.magic_damage[3] = int(msg.magic_damage[3] * r);
		ret.magic_damage[4] = int(msg.magic_damage[4] * r);
		ret.attack_rate	 = msg.attack_rate;
		ret.force_attack = _parent.GetForceAttack(); 
		ret.attack_attr = msg.attack_attr;
		if(ret.attack_attr == attack_msg::PHYSIC_ATTACK) ret.attack_attr = attack_msg::PHYSIC_ATTACK_HIT_DEFINITE;
		ret.attack_range = msg.attack_range + 0.5f;
		ret.speed = msg.speed;
		ret.skill_id = msg.skill_id;
		ret.attached_skill.skill = msg.attached_skill.skill;
		ret.attached_skill.level = msg.attached_skill.level;
		
		_parent.SetBeatBackState();
		_parent.DelayAttack( attacker, ret, 0, 10);	//�ӳ�0.5��
		return true;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_SOULBEATBACK);
		_parent.InsertTeamVisibleState(HSTATE_SOULBEATBACK,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_SOULBEATBACK);
		_parent.RemoveTeamVisibleState(HSTATE_SOULBEATBACK);
	}

	int GetValue()
	{
		return _retort_damage;	
	}
};

class filter_Soulstun : public filter_Soulbase
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_ADJUST_DAMAGE
	};

	int _level;
	
	virtual bool Save(archive & ar)
	{
		filter_Soulbase::Save(ar);
		ar << _level;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Soulbase::Load(ar);
		ar >> _level;
		return true;
	}
	
	filter_Soulstun(){}
public:
	DECLARE_SUBSTANCE(filter_Soulstun);
	filter_Soulstun(object_interface  object,int period,int level,int trigger_prob,int mp_cost,bool del_on_trigger)
			:filter_Soulbase(object,period,FILTER_MASK,trigger_prob,mp_cost,del_on_trigger),_level(level)
	{
		_filter_id = FILTER_SOULSTUN;	
		if(_level < 1) _level = 1;
		if(_level > 20) _level = 20;
	}
	
	void Merge(filter* f)
	{
		ASSERT(dynamic_cast<filter_Soulstun*>(f));	
		filter_Soulstun* nf = (filter_Soulstun*) f;
		if(nf->GetValue() == _level)
		{
			if(GetTimeOut(nf) > _timeout) _timeout = GetTimeOut(nf);		
		}
		else if(nf->GetValue() > _level)
		{
			_timeout = GetTimeOut(nf);
			_level = nf->GetValue();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SOULSTUN);
			_parent.InsertTeamVisibleState(HSTATE_SOULSTUN, _timeout);
		}
	}
	
	bool DoSoulAdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg._attack_state & AT_STATE_ALL_RETORT) return false;
		enchant_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.attack_range  = msg.attack_range + 0.5;
		ret.skill = 1091;	//������ܵ�״�?������??100%����
		ret.skill_level = _level;
		ret.helpful = 0;
		ret.force_attack = _parent.GetForceAttack(); 

		_parent.EnterCombatState();
		_parent.SetReboundState();
		_parent.DelayEnchant(attacker, ret, 10);	//�ӳ�0.5��
		return true;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_SOULSTUN);
		_parent.InsertTeamVisibleState(HSTATE_SOULSTUN,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_SOULSTUN);
		_parent.RemoveTeamVisibleState(HSTATE_SOULSTUN);
	}

	int GetValue()
	{
		return _level;	
	}
};

class filter_Deepenbless : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_ADJUST_HEAL
	};

	float _inc_heal_by_skill;
	float _inc_heal_by_potion;
	int _dec_heal_cool_time;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc_heal_by_skill << _inc_heal_by_potion << _dec_heal_cool_time;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc_heal_by_skill >> _inc_heal_by_potion >> _dec_heal_cool_time;
		return true;
	}

	filter_Deepenbless(){}
public:
	DECLARE_SUBSTANCE(filter_Deepenbless); 
	filter_Deepenbless(object_interface  object,int period, float inc_heal_by_skill, float inc_heal_by_potion, int dec_heal_cool_time)
				        :timeout_filter(object,period,FILTER_MASK),_inc_heal_by_skill(inc_heal_by_skill),_inc_heal_by_potion(inc_heal_by_potion),_dec_heal_cool_time(dec_heal_cool_time)
	{
		_filter_id = FILTER_DEEPENBLESS;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DEEPENBLESS,_timeout);
		_parent.DecHealCoolTime(_dec_heal_cool_time);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DEEPENBLESS);
		_parent.IncHealCoolTime(_dec_heal_cool_time);
	}
	void AdjustHeal(int& heal,char heal_type)
	{
		if(heal_type == 0)
			heal = (int)(heal * (1.f + _inc_heal_by_potion));
		else if(heal_type == 1)
			heal = (int)(heal * (1.f + _inc_heal_by_skill));
	}
};

class filter_Weakenbless : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|  FILTER_MASK_ADJUST_HEAL
	};

	float _dec_heal_by_skill;
	float _dec_heal_by_potion;
	int _inc_heal_cool_time;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _dec_heal_by_skill << _dec_heal_by_potion << _inc_heal_cool_time;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _dec_heal_by_skill >> _dec_heal_by_potion >> _inc_heal_cool_time;
		return true;
	}

	filter_Weakenbless(){}
public:
	DECLARE_SUBSTANCE(filter_Weakenbless); 
	filter_Weakenbless(object_interface  object,int period, float dec_heal_by_skill, float dec_heal_by_potion, int inc_heal_cool_time)
				        :timeout_filter(object,period,FILTER_MASK),_dec_heal_by_skill(dec_heal_by_skill),_dec_heal_by_potion(dec_heal_by_potion),_inc_heal_cool_time(inc_heal_cool_time)
	{
		_filter_id = FILTER_WEAKENBLESS;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_WEAKENBLESS,_timeout);
		_parent.IncHealCoolTime(_inc_heal_cool_time);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_WEAKENBLESS);
		_parent.DecHealCoolTime(_inc_heal_cool_time);
	}
	void AdjustHeal(int& heal,char heal_type)
	{
		if(heal_type == 0)
			heal = (int)(heal * (1.f - _dec_heal_by_potion));
		else if(heal_type == 1)
			heal = (int)(heal * (1.f - _dec_heal_by_skill));
	}
};

class filter_Delayhurt : public filter	//�ӳ����ࣱ������˺�??
{			//player��npc���˹�������(filter_Hurtwhenuseskill)֮��,�ڽ��й���ʱ(_cur_session = attack/skill session)����ʹ�Լ���Ѫ��������
protected:	//�ڵ�Ѫ���������������??,���ֱ�ӵ���_parent.BeHurt(),���������е�ClearSession������ʹ_cur_sessionָ��ʧЧ,���д�ڴ����
	enum
	{
		FILTER_MASK = FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _damage;
	XID _performer;
	attacker_info_t _pinfo;
	bool _invader;
	char _mode;

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _damage;
		ar << _performer;
		ar.push_back(&_pinfo, sizeof(attacker_info_t));
		ar << _invader;
		ar << _mode;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _damage;
		ar >> _performer;
		ar.pop_back(&_pinfo, sizeof(attacker_info_t));
		ar >> _invader;
		ar >> _mode;
		return true;
	}
	filter_Delayhurt(){}
public:
	DECLARE_SUBSTANCE(filter_Delayhurt); 
	filter_Delayhurt(object_interface  object,int damage)
			:filter(object,FILTER_MASK),_damage(damage)
	{
		_filter_id = FILTER_DELAYHURT;
	}

	void SetUp(const XID& player, const attacker_info_t& info, char mode, bool invader)
	{
		_performer = player;
		_pinfo = info;
		_mode = mode;
		_invader = invader;
	}

	virtual void Heartbeat(int tick)
	{
		_parent.BeHurt(_performer, _pinfo, _damage, _invader, _mode);	
		_is_deleted = true;	
	}

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}
};

class filter_Hurtwhenuseskill : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSLATE_SEND_ENCHANT 
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _hurt_prob;
	int _damage;
	XID _performer;
	attacker_info_t _pinfo;
	bool _invader;
	char _mode;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _hurt_prob << _damage << _performer << _invader << _mode;
		ar.push_back(&_pinfo, sizeof(attacker_info_t));
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _hurt_prob >> _damage >> _performer >> _invader >> _mode;
		ar.pop_back(&_pinfo, sizeof(attacker_info_t));
		return true;
	}
	filter_Hurtwhenuseskill(){}
public:
	DECLARE_SUBSTANCE(filter_Hurtwhenuseskill); 
	filter_Hurtwhenuseskill(object_interface  object, int period,int prob, int damage)
			:timeout_filter(object,period,FILTER_MASK),_hurt_prob(prob),_damage(damage)
	{
		_filter_id = FILTER_HURTWHENUSESKILL;
	}

	void SetUp(const XID& player, const attacker_info_t& info, char mode, bool invader)
	{
		_performer = player;
		_pinfo = info;
		_invader = invader;
		_mode = mode;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(msg._attack_state & AT_STATE_AURA_AND_RETORT)return;
		if((rand()%100)<_hurt_prob)
		{
			if(_parent.GetBasicProp().hp > _damage)
			{
				_parent.BeHurt(_performer, _pinfo, _damage, _invader, _mode);
			}
			else
			{
				filter_Delayhurt * pfilter;
				pfilter = new filter_Delayhurt(_parent,_damage);
				pfilter->SetUp(_performer,_pinfo,_mode,_invader);
				_parent.AddFilter(pfilter);
			}
			_parent.SendClientEnchantResult(_parent.GetSelfID(), 1147, 1, false, 0, 0);
		}
	}
	
	void TranslateSendEnchant(const XID & target,enchant_msg & msg)
	{
		if(msg._attack_state & AT_STATE_AURA_AND_RETORT)return;
		if(msg.skill && (rand()%100)<_hurt_prob)
		{
			if(_parent.GetBasicProp().hp > _damage)
			{
				_parent.BeHurt(_performer, _pinfo, _damage, _invader, _mode);
			}
			else
			{
				filter_Delayhurt * pfilter;
				pfilter = new filter_Delayhurt(_parent,_damage);
				pfilter->SetUp(_performer,_pinfo,_mode,_invader);
				_parent.AddFilter(pfilter);
			}
			_parent.SendClientEnchantResult(_parent.GetSelfID(), 1147, 1, false, 0, 0);
		}
	}
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_HURTWHENUSESKILL);
		_parent.InsertTeamVisibleState(HSTATE_HURTWHENUSESKILL,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_HURTWHENUSESKILL);
		_parent.RemoveTeamVisibleState(HSTATE_HURTWHENUSESKILL);
	}
};

class filter_Interruptwhenuseskill : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH 
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _prob;

	virtual bool Save(archive& ar)
	{
		timeout_filter::Save(ar);
		ar << _prob;	
		return true;
	}
	
	virtual bool Load(archive& ar)
	{
		timeout_filter::Load(ar);
		ar >> _prob;	
		return true;
	}
	
	filter_Interruptwhenuseskill(){}
public:
	DECLARE_SUBSTANCE(filter_Interruptwhenuseskill); 
	filter_Interruptwhenuseskill(object_interface  object, int period,int prob)
			:timeout_filter(object,period,FILTER_MASK),_prob(prob)
	{
		_filter_id = FILTER_INTERRUPTWHENUSESKILL;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INTERRUPTWHENUSESKILL,_timeout);
		_parent.GetSkillWrapper().IncInterruptProb(_prob);		
		_parent.IncImmuneMask(IMMUNEBREAK);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INTERRUPTWHENUSESKILL);
		_parent.GetSkillWrapper().DecInterruptProb(_prob);
		_parent.DecImmuneMask(IMMUNEBREAK);
	}
	
};

class filter_Fishform : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT
	};

	int _counter;
	int _inc_swim_speed;
	int _inc_defend_degree;

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _counter;
		ar << _inc_swim_speed;
		ar << _inc_defend_degree;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _counter;
		ar >> _inc_swim_speed;
		ar >> _inc_defend_degree;
		return true;
	}
	filter_Fishform(){}
public:
	DECLARE_SUBSTANCE(filter_Fishform); 
	filter_Fishform(object_interface  object, int inc_swim_speed, int inc_defend_degree)
			:filter(object,FILTER_MASK),_counter(0),_inc_swim_speed(inc_swim_speed),_inc_defend_degree(inc_defend_degree)
	{
		_filter_id = FILTER_FISHFORM;
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3)
		{
			if(!_parent.IsInWater()) _is_deleted = true;
			_counter -= 3;
		}
	}

	void OnAttach()
	{
		_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
		_parent.LockEquipment(true);
		_parent.ChangeShape(1|(FORM_CLASS<<6));
		_parent.InsertTeamVisibleState(HSTATE_FISHFORM,-1);		
		_parent.EnhanceSwimSpeed(_inc_swim_speed);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.EnhanceDefendDegree(_inc_defend_degree);
		_parent.SendClientDefenseData();
	}

	void OnRelease()
	{
		_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
		_parent.LockEquipment(false);
		_parent.ChangeShape(0);
		_parent.RemoveTeamVisibleState(HSTATE_FISHFORM);	
		_parent.ImpairSwimSpeed(_inc_swim_speed);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.ImpairDefendDegree(_inc_defend_degree);
		_parent.SendClientDefenseData();
	}
};

class filter_Deepicethrust : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _point;	//�����ȼ�����
	int _ratio;	//�����ٶ��½�

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point >> _ratio;
		return true;
	}
	filter_Deepicethrust(){}
public:
	DECLARE_SUBSTANCE(filter_Deepicethrust); 
	filter_Deepicethrust(object_interface  object,int period, int point, int ratio)
				        :timeout_filter(object,period,FILTER_MASK),_point(point),_ratio(ratio)
	{
		_filter_id = FILTER_DEEPICETHRUST;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DEEPICETHRUST,_timeout);
		_parent.IncVisibleState(VSTATE_DEEPICETHRUST);
		_parent.EnhanceAttackDegree(_point);
		_parent.SendClientAttackData();
		_parent.ImpairScaleAttackSpeed(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DEEPICETHRUST);
		_parent.DecVisibleState(VSTATE_DEEPICETHRUST);
		_parent.ImpairAttackDegree(_point);
		_parent.SendClientAttackData();
		_parent.EnhanceScaleAttackSpeed(_ratio);
		_parent.UpdateAttackData();
	}
};

class filter_Adjustattackdefend : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _attack_adj;	//�����ȼ�����������
	int _defend_adj;	//�����ȼ�����������

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _attack_adj << _defend_adj;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _attack_adj >> _defend_adj;
		return true;
	}
	filter_Adjustattackdefend(){}
public:
	DECLARE_SUBSTANCE(filter_Adjustattackdefend); 
	filter_Adjustattackdefend(object_interface  object,int period, int attack_adj, int defend_adj)
				        :timeout_filter(object,period,FILTER_MASK),_attack_adj(attack_adj),_defend_adj(defend_adj)
	{
		_filter_id = FILTER_ADJUSTATTACKDEFEND;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ADJUSTATTACKDEFEND,_timeout);
		if(_attack_adj > 0)
			_parent.IncVisibleState(VSTATE_ADJUSTATTACKDEFEND1);
		else
			_parent.IncVisibleState(VSTATE_ADJUSTATTACKDEFEND2);
		_parent.EnhanceAttackDegree(_attack_adj);
		_parent.EnhanceDefendDegree(_defend_adj);
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ADJUSTATTACKDEFEND);
		if(_attack_adj > 0)
			_parent.DecVisibleState(VSTATE_ADJUSTATTACKDEFEND1);
		else
			_parent.DecVisibleState(VSTATE_ADJUSTATTACKDEFEND2);
		_parent.ImpairAttackDegree(_attack_adj);
		_parent.ImpairDefendDegree(_defend_adj);
		_parent.SendClientAttackData();
	}
};

class filter_Beastieform : public timeout_filter 
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE
	};

	int _shape;
	int _ratio;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _shape << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _shape >> _ratio;
		return true;
	}
	filter_Beastieform(){}
public:
	DECLARE_SUBSTANCE(filter_Beastieform); 
	filter_Beastieform(object_interface  object,int period,int shape,int ratio,int mask=0)
			:timeout_filter(object,period,(mask?mask:FILTER_MASK)),_shape(shape),_ratio(ratio)
	{
		_filter_id = FILTER_BEASTIEFORM;
	}

	void OnAttach()
	{
		_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_BEASTIE);
		_parent.LockEquipment(true);
		_parent.SetNoFly(true);
		_parent.SetNoMount(true);
		_parent.SetNoBind(true);
		_parent.ChangeShape(_shape&(~FROM_MASK_HIGH)|(FORM_BEASTIE<<6));
		
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
		_parent.LockEquipment(false);
		_parent.SetNoFly(false);
		_parent.SetNoMount(false);
		_parent.SetNoBind(false);
		_parent.ChangeShape(0);

		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Baseinchurtspecattack: public timeout_filter	//��ĳЩ���Լ��ܹ��������˺�
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
				| FILTER_MASK_TRANSLATE_RECV_MSG | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _attr_mask;		//����Щ���Եļ��ܹ�����Ч
	float _ratio;		//��Ч���˺��������??
	int _value;			//��Ч��ôι��������������?
	int _vstate;
	int _hstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _attr_mask << _ratio << _value << _vstate << _hstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _attr_mask >> _ratio >> _value >> _vstate >> _hstate;
		return true;
	}

	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
		if(msg.skill_id && (_attr_mask & (1<<msg.attack_attr)))	
		{
			const Skill * sk = Skill::GetStub(msg.skill_id);
			if(!sk || sk->IsElfSkill()) return;
			msg.crit_rate += _value;	
			if(msg.crit_rate > 100) msg.crit_rate = 100;
		}
	}
	
	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg.skill_id && (_attr_mask & (1<<msg.attack_attr)))	
		{
			const Skill * sk = Skill::GetStub(msg.skill_id);
			if(!sk || sk->IsElfSkill()) return;
			dmg.physic_damage *= _ratio;
			dmg.magic_damage[0] *= _ratio;
			dmg.magic_damage[1] *= _ratio;
			dmg.magic_damage[2] *= _ratio;
			dmg.magic_damage[3] *= _ratio;
			dmg.magic_damage[4] *= _ratio;
		}
	}

	filter_Baseinchurtspecattack(){}
public:
	filter_Baseinchurtspecattack(object_interface  object, int period, int attr_mask, float ratio, int value, int vstate, int hstate)
				        :timeout_filter(object,period,FILTER_MASK),_attr_mask(attr_mask),_ratio(1.f+ratio),_value(value),_vstate(vstate),_hstate(hstate){}

	void OnAttach()
	{
		if(_hstate >= 0)
			_parent.InsertTeamVisibleState(_hstate,_timeout);
		if(_vstate >= 0)
			_parent.IncVisibleState(_vstate);
	}

	void OnRelease()
	{
		if(_hstate >= 0)
			_parent.RemoveTeamVisibleState(_hstate);
		if(_vstate >= 0)
			_parent.DecVisibleState(_vstate);
	}
};

class filter_Inchurtphysicgold : public filter_Baseinchurtspecattack
{
protected:
	enum
	{
		ATTR_MASK = (1<<attack_msg::PHYSIC_ATTACK | 1<<attack_msg::PHYSIC_ATTACK_HIT_DEFINITE | 1<<attack_msg::MAGIC_ATTACK_GOLD)	
	};
	filter_Inchurtphysicgold(){}
public:
	DECLARE_SUBSTANCE(filter_Inchurtphysicgold);
	filter_Inchurtphysicgold(object_interface object, int period, float ratio, int value)
		: filter_Baseinchurtspecattack(object,period,ATTR_MASK,ratio,value,-1,HSTATE_INCHURTPHYSICGOLD)
	{
		_filter_id = FILTER_INCHURTPHYSICGOLD;	
	}
};

class filter_Inchurtwoodwater: public filter_Baseinchurtspecattack
{
protected:
	enum
	{
		ATTR_MASK = (1<<attack_msg::MAGIC_ATTACK_WOOD | 1<<attack_msg::MAGIC_ATTACK_WATER)	
	};
	filter_Inchurtwoodwater(){}
public:
	DECLARE_SUBSTANCE(filter_Inchurtwoodwater);
	filter_Inchurtwoodwater(object_interface object, int period, float ratio, int value)
		: filter_Baseinchurtspecattack(object,period,ATTR_MASK,ratio,value,-1,HSTATE_INCHURTWOODWATER)
	{
		_filter_id = FILTER_INCHURTWOODWATER;	
	}
};

class filter_Inchurtfireearth: public filter_Baseinchurtspecattack
{
protected:
	enum
	{
		ATTR_MASK = (1<<attack_msg::MAGIC_ATTACK_FIRE | 1<<attack_msg::MAGIC_ATTACK_EARTH)	
	};
	filter_Inchurtfireearth(){}
public:
	DECLARE_SUBSTANCE(filter_Inchurtfireearth);
	filter_Inchurtfireearth(object_interface object, int period, float ratio, int value)
		: filter_Baseinchurtspecattack(object,period,ATTR_MASK,ratio,value,-1,HSTATE_INCHURTFIREEARTH)
	{
		_filter_id = FILTER_INCHURTFIREEARTH;	
	}
};

class filter_Attackattachstate : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
				| FILTER_MASK_TRANSLATE_SEND_MSG 
	};

	float _probability;
	int _attacker_skill;
	int _skill;
	int _level;
	int _vstate;
	int _hstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _probability << _attacker_skill << _skill << _level << _vstate << _hstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _probability >> _attacker_skill >> _skill >> _level >> _vstate >> _hstate;
		return true;
	}
	filter_Attackattachstate(){}
public:
	DECLARE_SUBSTANCE(filter_Attackattachstate); 
	filter_Attackattachstate(object_interface  object, int period, float probability, int attacker_skill, int skill, int level, int vstate, int hstate)
			:timeout_filter(object,period,FILTER_MASK),_probability(probability),_attacker_skill(attacker_skill),_skill(skill),_level(level),_vstate(vstate),_hstate(hstate)
	{
		_filter_id = FILTER_ATTACKATTACHSTATE;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(msg.skill_id != _attacker_skill && !(msg._attack_state&AT_STATE_AURA_AND_RETORT) && rand()%100<_probability)	//�����˺�������
		{
			msg.attached_skill.skill = _skill;
			msg.attached_skill.level = _level;
		}
	}

	void OnAttach()
	{
		if(_vstate)
			_parent.IncVisibleState(_vstate);
		if(_hstate)
			_parent.InsertTeamVisibleState(_hstate,_timeout);
	}

	void OnRelease()
	{
		if(_vstate)
			_parent.DecVisibleState(_vstate);
		if(_hstate)
			_parent.RemoveTeamVisibleState(_hstate);
	}
};

class filter_Beattackedattachstate : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
				| FILTER_MASK_ADJUST_DAMAGE 
	};

	int _attacker_skill;
	int _skill;
	int _level;
	bool _del_on_trigger; 
	int _hstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _attacker_skill << _skill << _level << _del_on_trigger << _hstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _attacker_skill >> _skill >> _level >> _del_on_trigger >> _hstate;
		return true;
	}
	filter_Beattackedattachstate(){}
public:
	DECLARE_SUBSTANCE(filter_Beattackedattachstate); 
	filter_Beattackedattachstate(object_interface  object, int period, int attacker_skill, int skill, int level, bool del_on_trigger, int hstate, int filter_id)
			:timeout_filter(object,period,FILTER_MASK),_attacker_skill(attacker_skill),_skill(skill),_level(level),_del_on_trigger(del_on_trigger),_hstate(hstate)
	{
		_filter_id = filter_id;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg.skill_id == _attacker_skill)
		{
			(const_cast<attack_msg &>(msg)).attached_skill.skill = _skill;
			(const_cast<attack_msg &>(msg)).attached_skill.level = _level;
			if(_del_on_trigger) _is_deleted = true;
		}
	}
	
	void OnAttach()
	{
		if(_hstate)
			_parent.InsertTeamVisibleState(_hstate,_timeout);
		//_parent.IncVisibleState(_vstate);
	}

	void OnRelease()
	{
		if(_hstate)
			_parent.RemoveTeamVisibleState(_hstate);
		//_parent.DecVisibleState(_vstate);
	}
};

class filter_Poisionseed : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _damage;
	XID _performer;
	attacker_info_t _pinfo;
	char _counter;
	bool _invader;
	char _mode;
	int _damage_time;	//��Ѫ����ʱ��,��ʼ��Ѫ���ֵ���?0
	float _hp_ratio;	//hp�½������پͿ�ʼ��Ѫ

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damage;
		ar << _performer;
		ar << _counter;
		ar.push_back(&_pinfo, sizeof(attacker_info_t));
		ar << _invader;
		ar << _mode;
		ar << _damage_time;
		ar << _hp_ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damage;
		ar >> _performer;
		ar >> _counter;
		ar.pop_back(&_pinfo, sizeof(attacker_info_t));
		ar >> _invader;
		ar >> _mode;
		ar >> _damage_time;
		ar >> _hp_ratio;
		return true;
	}
	filter_Poisionseed(){}
public:
	DECLARE_SUBSTANCE(filter_Poisionseed);
	filter_Poisionseed(object_interface  object,int period, int damage, int damage_time, float hp_ratio)
			:timeout_filter(object,period,FILTER_MASK),_damage_time(damage_time),_hp_ratio(hp_ratio)
	{
		_counter = 0;
		_damage = damage/damage_time;
		if(_damage<1)
			_damage = 1;
		_filter_id = FILTER_POISIONSEED;
	}

	void SetUp(const XID& player, const attacker_info_t& info, char mode, bool invader)
	{
		_performer = player;
		_pinfo = info;
		_mode = mode;
		_invader = invader;
	}

	void Heartbeat(int tick)
	{
		if(_damage_time > 0)
		{
			//�ж��Ƿ�Ӧ�ÿ�ʼ��Ѫ	
			if(_parent.GetBasicProp().hp < _parent.GetExtendProp().max_hp * _hp_ratio)
			{
				_timeout = _damage_time + tick;
				_damage_time = 0;
			}		
		}
		else
		{
			_counter += tick;
			if(_counter>=3 || tick>=_timeout)
			{
				_parent.BeHurt(_performer, _pinfo, _damage*_counter, _invader, _mode);	
				_counter -= 3;
			}
		}
		timeout_filter::Heartbeat(tick);
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_POISIONSEED);
		_parent.InsertTeamVisibleState(HSTATE_POISIONSEED,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_POISIONSEED);
		_parent.RemoveTeamVisibleState(HSTATE_POISIONSEED);
	}
};

class filter_Hpgenseed : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_DO_DAMAGE
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _health;
	char _counter;
	int _hpgen_time;	//��Ѫ����ʱ�䣬��ʼ��Ѫ���ֵ���?0	
	int _damage;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _health;
		ar << _counter;
		ar << _hpgen_time;
		ar << _damage;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _health;
		ar >> _counter;
		ar >> _hpgen_time;
		ar >> _damage;
		return true;
	}
	filter_Hpgenseed(){}
public:
	DECLARE_SUBSTANCE(filter_Hpgenseed); 
	filter_Hpgenseed(object_interface  object,int period,int health,int hpgen_time,int damage)
			:timeout_filter(object,period,FILTER_MASK),_hpgen_time(hpgen_time),_damage(damage)
	{
		_filter_id = FILTER_HPGENSEED;
		_health = health/hpgen_time;
		_counter = 0;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_HPGENSEED);
		_parent.InsertTeamVisibleState(HSTATE_HPGENSEED,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_HPGENSEED);
		_parent.RemoveTeamVisibleState(HSTATE_HPGENSEED);
	}

	virtual void Heartbeat(int tick)
	{
		if(_hpgen_time == 0)
		{
			_counter += tick;
			if(_counter>=3 || tick>=_timeout)
			{
				_parent.HealBySkill(_health*_counter);	
				_counter -= 3;
			}
		}
		timeout_filter::Heartbeat(tick);
	}
	
	void DoDamage(const damage_entry & dmg)
	{
		if(_hpgen_time > 0 && dmg.physic_damage+dmg.magic_damage[0]+dmg.magic_damage[1]+dmg.magic_damage[2]+dmg.magic_damage[3]+dmg.magic_damage[4] >= _damage)
		{
			//��ʼ��Ѫ
			_timeout = _hpgen_time;
			_hpgen_time = 0;
		}
	}
};

class filter_Fastprayincmagic : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _inc_magic;
	int _dec_praytime;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc_magic << _dec_praytime;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc_magic >> _dec_praytime;
		return true;
	}

	filter_Fastprayincmagic(){}
public:
	DECLARE_SUBSTANCE(filter_Fastprayincmagic); 
	filter_Fastprayincmagic(object_interface  object,int period,int inc_magic, int dec_praytime)
				        :timeout_filter(object,period,FILTER_MASK),_inc_magic(inc_magic),_dec_praytime(dec_praytime)
	{
		_filter_id = FILTER_FASTPRAYINCMAGIC;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_FASTPRAYINCMAGIC);
		_parent.InsertTeamVisibleState(HSTATE_FASTPRAYINCMAGIC,_timeout);
		_parent.EnhanceScaleMagicDamage(_inc_magic);
		_parent.UpdateMagicData();
		(_parent.GetSkillWrapper()).DecPrayTime(_dec_praytime);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_FASTPRAYINCMAGIC);
		_parent.RemoveTeamVisibleState(HSTATE_FASTPRAYINCMAGIC);
		_parent.ImpairScaleMagicDamage(_inc_magic);
		_parent.UpdateMagicData();
		(_parent.GetSkillWrapper()).IncPrayTime(_dec_praytime);
	}
};

class filter_Incwoodwaterdefense : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _inc_wood;
	int _inc_water;
	int _inc_defense;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc_wood << _inc_water << _inc_defense;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc_wood >> _inc_water >> _inc_defense;
		return true;
	}

	filter_Incwoodwaterdefense(){}
public:
	DECLARE_SUBSTANCE(filter_Incwoodwaterdefense); 
	filter_Incwoodwaterdefense(object_interface  object,int period,int inc_wood, int inc_water, int inc_defense)
				        :timeout_filter(object,period,FILTER_MASK),_inc_wood(inc_wood),_inc_water(inc_water),_inc_defense(inc_defense)
	{
		_filter_id = FILTER_INCWOODWATERDEFENSE;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INCWOODWATERDEFENSE);
		_parent.InsertTeamVisibleState(HSTATE_INCWOODWATERDEFENSE,_timeout);
		_parent.EnhanceScaleDefense(_inc_defense);
		_parent.EnhanceScaleResistance(1,_inc_wood);
		_parent.EnhanceScaleResistance(2,_inc_water);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INCWOODWATERDEFENSE);
		_parent.RemoveTeamVisibleState(HSTATE_INCWOODWATERDEFENSE);
		_parent.ImpairScaleDefense(_inc_defense);
		_parent.ImpairScaleResistance(1,_inc_wood);
		_parent.ImpairScaleResistance(2,_inc_water);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
	}
};

class filter_Specialslow : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Specialslow(){}
public:
	DECLARE_SUBSTANCE(filter_Specialslow); 
	filter_Specialslow(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_SPECIALSLOW;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_SPECIALSLOW);
		_parent.InsertTeamVisibleState(HSTATE_SPECIALSLOW,_timeout);
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_SPECIALSLOW);
		_parent.RemoveTeamVisibleState(HSTATE_SPECIALSLOW);
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};

class filter_Incdefencesmite : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _inc_defence;
	int _inc_crit;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc_defence << _inc_crit;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc_defence >> _inc_crit;
		return true;
	}
	filter_Incdefencesmite(){}
public:
	DECLARE_SUBSTANCE(filter_Incdefencesmite); 
	filter_Incdefencesmite(object_interface  object,int period,int inc_defence, int inc_crit)
				        :timeout_filter(object,period,FILTER_MASK),_inc_defence(inc_defence),_inc_crit(inc_crit)
	{
		_filter_id = FILTER_INCDEFENCESMITE;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INCDEFENCESMITE);
		_parent.InsertTeamVisibleState(HSTATE_INCDEFENCESMITE,_timeout);
		_parent.EnhanceScaleDefense(_inc_defence);
		_parent.UpdateDefenseData();
		_parent.EnhanceCrit(_inc_crit);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INCDEFENCESMITE);
		_parent.RemoveTeamVisibleState(HSTATE_INCDEFENCESMITE);
		_parent.ImpairScaleDefense(_inc_defence);
		_parent.UpdateDefenseData();
		_parent.ImpairCrit(_inc_crit);
	}
};

class filter_Incresistmagic : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _inc_resist;
	int _inc_magic;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc_resist << _inc_magic;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc_resist >> _inc_magic;
		return true;
	}
	filter_Incresistmagic(){}
public:
	DECLARE_SUBSTANCE(filter_Incresistmagic); 
	filter_Incresistmagic(object_interface  object,int period,int inc_resist, int inc_magic)
				        :timeout_filter(object,period,FILTER_MASK),_inc_resist(inc_resist),_inc_magic(inc_magic)
	{
		_filter_id = FILTER_INCRESISTMAGIC;
	}
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INCRESISTMAGIC);
		_parent.InsertTeamVisibleState(HSTATE_INCRESISTMAGIC,_timeout);
		_parent.EnhanceScaleResistance(0, _inc_resist);
		_parent.EnhanceScaleResistance(1, _inc_resist);
		_parent.EnhanceScaleResistance(2, _inc_resist);
		_parent.EnhanceScaleResistance(3, _inc_resist);
		_parent.EnhanceScaleResistance(4, _inc_resist);
		_parent.EnhanceScaleMagicDamage(_inc_magic);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INCRESISTMAGIC);
		_parent.RemoveTeamVisibleState(HSTATE_INCRESISTMAGIC);
		_parent.ImpairScaleResistance(0, _inc_resist);
		_parent.ImpairScaleResistance(1, _inc_resist);
		_parent.ImpairScaleResistance(2, _inc_resist);
		_parent.ImpairScaleResistance(3, _inc_resist);
		_parent.ImpairScaleResistance(4, _inc_resist);
		_parent.ImpairScaleMagicDamage(_inc_magic);
		_parent.UpdateMagicData();
	}
};

class filter_Transportmptopet : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _mp_cost;
	int _mp_transport;
	float _transport_range;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _mp_cost << _mp_transport << _transport_range << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _mp_cost >> _mp_transport >> _transport_range >> _counter;
		return true;
	}
	filter_Transportmptopet(){}
public:
	DECLARE_SUBSTANCE(filter_Transportmptopet); 
	filter_Transportmptopet(object_interface  object,int period,int mp_cost, int mp_transport, float transport_range)
				        :timeout_filter(object,period,FILTER_MASK),_mp_cost(mp_cost/period),_mp_transport(mp_transport/period),_transport_range(transport_range*transport_range),_counter(0)
	{
		_filter_id = FILTER_TRANSPORTMPTOPET;
		if(_mp_cost < 1) _mp_cost = 1;
		if(_mp_transport < 1) _mp_transport = 1;
	}
	
	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			//������
			XID pet_id = _parent.GetPetID();
			A3DVECTOR pos;
			int hp,mp2;
			if(!pet_id.IsValid() || _parent.QueryObject(pet_id,pos,hp,mp2) != 1 || pos.squared_distance(_parent.GetPos()) > _transport_range)
			{
				_is_deleted = true;
				return;
			}
			
			int mp = _parent.GetBasicProp().mp;
			if(mp >= _mp_cost*_counter)
			{
				_parent.DrainMana(_mp_cost*_counter);
				_parent.InjectPetHPMP(0,_mp_transport*_counter);	
			}
			else if(mp > 0)
			{
				_parent.DrainMana(mp);
				_parent.InjectPetHPMP(0,mp*_mp_transport/_mp_cost);	
			}
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_TRANSPORTMPTOPET);
		_parent.InsertTeamVisibleState(HSTATE_TRANSPORTMPTOPET,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_TRANSPORTMPTOPET);
		_parent.RemoveTeamVisibleState(HSTATE_TRANSPORTMPTOPET);
	}
};

class filter_Transportdamagetopet : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_ADJUST_DAMAGE
	};

	float _damage_transport_ratio;
	XID _pet_id;
	float _mp_cost_per_damage;
	float _transport_range;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damage_transport_ratio << _pet_id << _mp_cost_per_damage << _transport_range;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damage_transport_ratio >> _pet_id >> _mp_cost_per_damage >> _transport_range;
		return true;
	}
	filter_Transportdamagetopet(){}
public:
	DECLARE_SUBSTANCE(filter_Transportdamagetopet); 
	filter_Transportdamagetopet(object_interface  object,int period,float damage_transport_ratio,const XID & pet_id,float mp_cost_per_damage,float transport_range)
				        :timeout_filter(object,period,FILTER_MASK),_damage_transport_ratio(damage_transport_ratio),_pet_id(pet_id),_mp_cost_per_damage(mp_cost_per_damage),_transport_range(transport_range*transport_range)
	{
		_filter_id = FILTER_TRANSPORTDAMAGETOPET;
	}
	
	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		A3DVECTOR pos;
		int hp,mp;
		if(_parent.QueryObject(_pet_id,pos,hp,mp) != 1 || pos.squared_distance(_parent.GetPos()) > _transport_range)
		{
			_is_deleted = true;
			return;
		}
		if(mp <= 0) return;
		
		float damage_transport = (dmg.physic_damage + dmg.magic_damage[0] + dmg.magic_damage[1] + dmg.magic_damage[2] + dmg.magic_damage[3] + dmg.magic_damage[4]) * damage_adjust * _damage_transport_ratio; 
		if((int)damage_transport <= 1) return;
		int mp_cost = (int)(damage_transport*_mp_cost_per_damage);

		if(mp > mp_cost)
		{
			float r = 1.0f - _damage_transport_ratio;
			dmg.physic_damage *= r;
			dmg.magic_damage[0] *= r;
			dmg.magic_damage[1] *= r;
			dmg.magic_damage[2] *= r;
			dmg.magic_damage[3] *= r;
			dmg.magic_damage[4] *= r;
		}
		else if(mp > 0)
		{
			float r = 1.0f - _damage_transport_ratio/mp_cost*mp;
			dmg.physic_damage *= r;
			dmg.magic_damage[0] *= r;
			dmg.magic_damage[1] *= r;
			dmg.magic_damage[2] *= r;
			dmg.magic_damage[3] *= r;
			dmg.magic_damage[4] *= r;
			damage_transport = damage_transport/mp_cost*mp;
			mp_cost = mp;
		}
		//���ٴ����˺���
		//_parent.DrainPetHPMP(_pet_id,(int)damage_transport,mp_cost);
		_parent.DrainPetHPMP(_pet_id,0,mp_cost);
	}
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_TRANSPORTDAMAGETOPET);
		_parent.InsertTeamVisibleState(HSTATE_TRANSPORTDAMAGETOPET,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_TRANSPORTDAMAGETOPET);
		_parent.RemoveTeamVisibleState(HSTATE_TRANSPORTDAMAGETOPET);
	}
};

class filter_Absorbdamageincdefense : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE |FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _absorb_amount;
	int _inc_defense;
	int _inc_resist;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _absorb_amount << _inc_defense << _inc_resist;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _absorb_amount >> _inc_defense >> _inc_resist;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		float damage = (dmg.physic_damage + dmg.magic_damage[0] + dmg.magic_damage[1] + dmg.magic_damage[2] + dmg.magic_damage[3] + dmg.magic_damage[4]) * damage_adjust * 0.99f; 
		if((int)damage <= 1) return;
		
		if(_absorb_amount <= (int)damage)
		{
			float r = 1.0f - _absorb_amount*0.99f/damage;
			dmg.physic_damage *= r;
			dmg.magic_damage[0] *= r;
			dmg.magic_damage[1] *= r;
			dmg.magic_damage[2] *= r;
			dmg.magic_damage[3] *= r;
			dmg.magic_damage[4] *= r;
			_absorb_amount = 0;
			_is_deleted = true;
		}
		else
		{
			dmg.physic_damage *= 0.01;
			dmg.magic_damage[0] *= 0.01f;
			dmg.magic_damage[1] *= 0.01f;
			dmg.magic_damage[2] *= 0.01f;
			dmg.magic_damage[3] *= 0.01f;
			dmg.magic_damage[4] *= 0.01f;
			_absorb_amount -= (int)damage;
		}
	}

	filter_Absorbdamageincdefense(){}
public:
	DECLARE_SUBSTANCE(filter_Absorbdamageincdefense); 
	filter_Absorbdamageincdefense(object_interface  object, int period, int absorb_amount, int inc_defense, int inc_resist)
				        :timeout_filter(object,period,FILTER_MASK),_absorb_amount(absorb_amount),_inc_defense(inc_defense),_inc_resist(inc_resist)
	{
		_filter_id = FILTER_ABSORBDAMAGEINCDEFENSE;
	}

	void OnAttach()
	{
		_parent.EnhanceScaleDefense(_inc_defense);
		_parent.UpdateDefenseData();
		_parent.EnhanceScaleResistance(0, _inc_resist);
		_parent.EnhanceScaleResistance(1, _inc_resist);
		_parent.EnhanceScaleResistance(2, _inc_resist);
		_parent.EnhanceScaleResistance(3, _inc_resist);
		_parent.EnhanceScaleResistance(4, _inc_resist);
		_parent.UpdateMagicData();
		_parent.IncVisibleState(VSTATE_ABSORBDAMAGEINCDEFENSE);
		_parent.InsertTeamVisibleState(HSTATE_ABSORBDAMAGEINCDEFENSE,_timeout);
	}

	void OnRelease()
	{
		_parent.ImpairScaleDefense(_inc_defense);
		_parent.UpdateDefenseData();
		_parent.ImpairScaleResistance(0, _inc_resist);
		_parent.ImpairScaleResistance(1, _inc_resist);
		_parent.ImpairScaleResistance(2, _inc_resist);
		_parent.ImpairScaleResistance(3, _inc_resist);
		_parent.ImpairScaleResistance(4, _inc_resist);
		_parent.UpdateMagicData();
		_parent.DecVisibleState(VSTATE_ABSORBDAMAGEINCDEFENSE);
		_parent.RemoveTeamVisibleState(HSTATE_ABSORBDAMAGEINCDEFENSE);
	}
	
};

class filter_Incrementalhpgen : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _health;
	int _inc_each;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _health << _inc_each << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _health >> _inc_each >> _counter;
		return true;
	}
	filter_Incrementalhpgen(){}
public:
	DECLARE_SUBSTANCE(filter_Incrementalhpgen); 
	filter_Incrementalhpgen(object_interface  object,int period,int health, int inc_each)
			:timeout_filter(object,period,FILTER_MASK),_health(health),_inc_each(inc_each),_counter(0)
	{
		_filter_id = FILTER_INCREMENTALHPGEN;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_INCREMENTALHPGEN,_timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCREMENTALHPGEN);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.HealBySkill(_health*_counter);	
			_health += _inc_each*_counter;
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Chanceofrebirth : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _exp_reduce;
	float _life_after_rebirth;
	float _mana_after_rebirth;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _exp_reduce << _life_after_rebirth << _mana_after_rebirth;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _exp_reduce >> _life_after_rebirth >> _mana_after_rebirth;
		return true;
	}
	filter_Chanceofrebirth(){}
public:
	DECLARE_SUBSTANCE(filter_Chanceofrebirth); 
	filter_Chanceofrebirth(object_interface  object,int period,float exp_reduce, float life_after_rebirth, float mana_after_rebirth)
			:timeout_filter(object,period,FILTER_MASK),_exp_reduce(exp_reduce),_life_after_rebirth(life_after_rebirth),_mana_after_rebirth(mana_after_rebirth)
	{
		_filter_id = FILTER_CHANCEOFREBIRTH;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_CHANCEOFREBIRTH);
		_parent.InsertTeamVisibleState(HSTATE_CHANCEOFREBIRTH,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_CHANCEOFREBIRTH);
		_parent.RemoveTeamVisibleState(HSTATE_CHANCEOFREBIRTH);
	}

	virtual void Heartbeat(int tick)
	{
		if(_parent.IsDead())
		{
			if(_parent.GetBasicProp().level <= 10) _exp_reduce = 0.f;
			_parent.Resurrect(_exp_reduce,_life_after_rebirth,_mana_after_rebirth);
			_is_deleted = true;	
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Specialphysichurttrigger : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	filter_Specialphysichurttrigger(){}
public:
	DECLARE_SUBSTANCE(filter_Specialphysichurttrigger); 
	filter_Specialphysichurttrigger(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SPECIALPHYSICHURTTRIGGER;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SPECIALPHYSICHURTTRIGGER,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SPECIALPHYSICHURTTRIGGER);
	}
};

class filter_Inccountedsmite : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSFERABLE_BUFF
	};
	
	int _crit;
	int _skill_id;
	int _count;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _crit << _skill_id << _count;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _crit >> _skill_id >> _count;
		return true;
	}
	filter_Inccountedsmite(){}
public:
	DECLARE_SUBSTANCE(filter_Inccountedsmite); 
	filter_Inccountedsmite(object_interface object, int period, int crit, int skill_id, int count)
				        :timeout_filter(object,period,FILTER_MASK),_crit(crit),_skill_id(skill_id),_count(count)
	{
		_filter_id = FILTER_INCCOUNTEDSMITE;
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(_skill_id == 0 || _skill_id == msg.skill_id)
		{
			msg.crit_rate += _crit;
			if(--_count <= 0) _is_deleted = true;
		}
	}
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INCCOUNTEDSMITE);
		_parent.InsertTeamVisibleState(HSTATE_INCCOUNTEDSMITE,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INCCOUNTEDSMITE);
		_parent.RemoveTeamVisibleState(HSTATE_INCCOUNTEDSMITE);
	}
};

class filter_Weapondisabled : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
			|FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	filter_Weapondisabled(){}
public:
	DECLARE_SUBSTANCE(filter_Weapondisabled); 
	filter_Weapondisabled(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_WEAPONDISABLED;
	}

	void OnAttach()
	{
	//	_parent.IncVisibleState(VSTATE_WEAPONDISABLED);
		_parent.InsertTeamVisibleState(HSTATE_WEAPONDISABLED,_timeout);
		_parent.WeaponDisabled(true);
	}

	void OnRelease()
	{
	//	_parent.DecVisibleState(VSTATE_WEAPONDISABLED);
		_parent.RemoveTeamVisibleState(HSTATE_WEAPONDISABLED);
		_parent.WeaponDisabled(false);
	}
};

class filter_Incaggroondamage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	XID _attacker;
	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _attacker << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _attacker >> _inc;
		return true;
	}

	filter_Incaggroondamage(){}
public:
	DECLARE_SUBSTANCE(filter_Incaggroondamage); 
	filter_Incaggroondamage(object_interface  object,int period,const XID& attacker,int inc)
				        :timeout_filter(object,period,FILTER_MASK),_attacker(attacker),_inc(inc)
	{
		_filter_id = FILTER_INCAGGROONDAMAGE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCAGGROONDAMAGE,_timeout);
		_parent.IncAggroOnDamage(_attacker,_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCAGGROONDAMAGE);
		_parent.DecAggroOnDamage(_attacker,_inc);
	}
};
class filter_Enhanceskilldamage : public timeout_filter//���Ӽ��ܶ�npc���˺�
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE 
	};

	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		return true;
	}

	filter_Enhanceskilldamage(){}
public:
	DECLARE_SUBSTANCE(filter_Enhanceskilldamage); 
	filter_Enhanceskilldamage(object_interface  object,int period,int inc)
				        :timeout_filter(object,period,FILTER_MASK),_inc(inc)
	{
		_filter_id = FILTER_ENHANCESKILLDAMAGE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ENHANCESKILLDAMAGE,_timeout);
		_parent.EnhanceSkillDamage(_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ENHANCESKILLDAMAGE);
		_parent.ImpairSkillDamage(_inc);
	}
};
class filter_Detectinvisible : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	float _range;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _range << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _range >> _counter;
		return true;
	}

	filter_Detectinvisible(){}
public:
	DECLARE_SUBSTANCE(filter_Detectinvisible); 
	filter_Detectinvisible(object_interface  object,int period,float range)
				        :timeout_filter(object,period,FILTER_MASK),_range(range),_counter(0)
	{
		_filter_id = FILTER_DETECTINVISIBLE;
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.DetectInvisible(_range);
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DETECTINVISIBLE, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DETECTINVISIBLE);
	}
};
class filter_Decapperhit : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _dec;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _dec;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _dec;
		return true;
	}

	filter_Decapperhit(){}
public:
	DECLARE_SUBSTANCE(filter_Decapperhit); 
	filter_Decapperhit(object_interface  object,int period,int dec)
				        :timeout_filter(object,period,FILTER_MASK),_dec(dec)
	{
		_filter_id = FILTER_DECAPPERHIT;
	}

	void OnAttach()
	{
		_parent.DecApPerHit(_dec);
	}

	void OnRelease()
	{
		_parent.IncApPerHit(_dec);
	}
};
class filter_Fastmpgen2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE
	};

	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}
	filter_Fastmpgen2(){}
public:
	DECLARE_SUBSTANCE(filter_Fastmpgen2); 
	filter_Fastmpgen2(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(r)
	{
		_filter_id = FILTER_FASTMPGEN2;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_FASTMPGEN2, _timeout);
		_parent.EnhanceMPGen(_point);
		_parent.UpdateHPMPGen();
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Fastmpgen2*>(f));
		filter_Fastmpgen2* nf = (filter_Fastmpgen2*) f;
		_timeout = GetTimeOut(nf);
		if(_point!=nf->GetPoint())
		{
			_parent.ImpairMPGen(_point);
			_point = nf->GetPoint();
			_parent.EnhanceMPGen(_point);
			_parent.UpdateHPMPGen();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_FASTMPGEN2);
			_parent.InsertTeamVisibleState(HSTATE_FASTMPGEN2, _timeout);
		}
		
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_FASTMPGEN2);
		_parent.ImpairMPGen(_point);
		_parent.UpdateHPMPGen();
	}
	int GetPoint()
	{
		return _point;
	}
};

class filter_Positionrollback : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE 
	};

	int _tag;
	A3DVECTOR _pos;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _tag << _pos;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _tag >> _pos;
		return true;
	}
	filter_Positionrollback(){}
public:
	DECLARE_SUBSTANCE(filter_Positionrollback); 
	filter_Positionrollback(object_interface  object,int period,int tag,const A3DVECTOR & pos)
			:timeout_filter(object,period,FILTER_MASK),_tag(tag),_pos(pos)
	{
		_filter_id = FILTER_POSITIONROLLBACK;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_POSITIONROLLBACK);
		_parent.InsertTeamVisibleState(HSTATE_POSITIONROLLBACK, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_POSITIONROLLBACK);
		_parent.RemoveTeamVisibleState(HSTATE_POSITIONROLLBACK);
	}

	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_timeout <= 0 && !_parent.IsDead())
		{
			_parent.LongJump(_pos,_tag);
		}
	}
};

class filter_Hprollback : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE 
	};

	int _hp;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _hp;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _hp;
		return true;
	}
	filter_Hprollback(){}
public:
	DECLARE_SUBSTANCE(filter_Hprollback); 
	filter_Hprollback(object_interface  object,int period,int hp)
			:timeout_filter(object,period,FILTER_MASK),_hp(hp)
	{
		_filter_id = FILTER_HPROLLBACK;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_HPROLLBACK);
		_parent.InsertTeamVisibleState(HSTATE_HPROLLBACK, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_HPROLLBACK);
		_parent.RemoveTeamVisibleState(HSTATE_HPROLLBACK);
	}

	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_timeout <= 0 && !_parent.IsDead())
		{
			int dec = (int)(_parent.GetBasicProp().hp - _hp);
			if(dec>0)
				_parent.DecHP(dec);
			else if(dec<0)
				_parent.Heal(-dec);
		}
	}
};

class filter_Nofly : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE 
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}
	filter_Nofly(){}
public:
	DECLARE_SUBSTANCE(filter_Nofly); 
	filter_Nofly(object_interface  object,int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_NOFLY;
	}

	void OnAttach() 
	{
		//_parent.IncVisibleState(VSTATE_);
		_parent.InsertTeamVisibleState(HSTATE_NOFLY, _timeout);
		_parent.SetNoFly(true);
	}
	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_);
		_parent.RemoveTeamVisibleState(HSTATE_NOFLY);
		_parent.SetNoFly(false);
	}
};

class filter_Nochangeselect : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE 
	};

	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _counter;
		return true;
	}
	filter_Nochangeselect(){}
public:
	DECLARE_SUBSTANCE(filter_Nochangeselect); 
	filter_Nochangeselect(object_interface  object,int period)
			:timeout_filter(object,period,FILTER_MASK),_counter(0)
	{
		_filter_id = FILTER_NOCHANGESELECT;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_NOCHANGESELECT);
		_parent.InsertTeamVisibleState(HSTATE_NOCHANGESELECT, _timeout);
		_parent.SetNoChangeSelect(true);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NOCHANGESELECT);
		_parent.RemoveTeamVisibleState(HSTATE_NOCHANGESELECT);
		_parent.SetNoChangeSelect(false);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3)
		{
			if(!_parent.GetCurTargetID().IsValid()) _is_deleted = true; 
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Healabsorb : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE 
			| FILTER_MASK_ADJUST_HEAL
	};

	int _point_max;
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point_max << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point_max >> _point;
		return true;
	}
	filter_Healabsorb(){}
public:
	DECLARE_SUBSTANCE(filter_Healabsorb); 
	filter_Healabsorb(object_interface  object,int period,int point,int point_max)
			:timeout_filter(object,period,FILTER_MASK),_point_max(point_max),_point(point)
	{
		_filter_id = FILTER_HEALABSORB;
		if(_point > _point_max) _point = _point_max;
	}

	int OnQuery(int index)
	{
		return index == FILTER_QUERY_LEVEL ?  _point : 0;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_HEALABSORB);
		_parent.InsertTeamVisibleState(HSTATE_HEALABSORB, _point, _point_max, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_HEALABSORB);
		_parent.RemoveTeamVisibleState(HSTATE_HEALABSORB);
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Healabsorb*>(f));
		filter_Healabsorb* nf = (filter_Healabsorb*) f;
		if(_point_max < nf->_point_max) _point_max = nf->_point_max;
		if(_point < _point_max)
		{
			_point += nf->_point;
			if(_point > _point_max) _point = _point_max;
		}
		if(_timeout < nf->_timeout) _timeout = nf->_timeout;
		_parent.ModifyTeamVisibleState(HSTATE_HEALABSORB, _point, _point_max, _timeout);
	}

	void AdjustHeal(int& heal,char heal_type)
	{
		if(heal >= _point)
		{
			heal -= _point;
			_point = 0;
			_is_deleted = true;
		}
		else if(heal > 0)
		{
			_point -= heal;
			heal = 0;
			_parent.ModifyTeamVisibleState(HSTATE_HEALABSORB, _point, _point_max, _timeout);
		}
	}
};

class filter_Repelonnormalattack : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE 
	};

	int _prob;			//ÿ���ܹ����������˵ĸ���
	float _distance;	//���˵ľ���
	int _repel_time;	//���˳���ʱ�� ms
	int _last_time;		//�ϴδ�����ʱ��
	int _cd_time;		//�������˵���ȴʱ��

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _prob << _distance << _repel_time << _last_time << _cd_time;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _prob >> _distance >> _repel_time >>  _last_time >> _cd_time;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(_last_time-_timeout >= _cd_time && msg.skill_id == 0 && msg.short_range <= 0.f && (rand()%100) < _prob)
		{
			_last_time = _timeout;	
			_parent.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			_parent.KnockBack(attacker, A3DVECTOR(0,0,0)/*��ұ�����ʱ�˲������?*/, _distance, _repel_time, 0);	
		}
	}

	filter_Repelonnormalattack(){}
public:
	DECLARE_SUBSTANCE(filter_Repelonnormalattack); 
	filter_Repelonnormalattack(object_interface  object, int period, int prob, float distance, int repel_time, int cd_time)
				        :timeout_filter(object,period,FILTER_MASK),_prob(prob),_distance(distance),_repel_time(repel_time),_last_time(INT_MAX),_cd_time(cd_time)
	{
		_filter_id = FILTER_REPELONNORMALATTACK;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_REPELONNORMALATTACK);
		_parent.InsertTeamVisibleState(HSTATE_REPELONNORMALATTACK, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_REPELONNORMALATTACK);
		_parent.RemoveTeamVisibleState(HSTATE_REPELONNORMALATTACK);
	}

};

class filter_Inccritresistance : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		return true;
	}

	filter_Inccritresistance(){}
public:
	DECLARE_SUBSTANCE(filter_Inccritresistance); 
	filter_Inccritresistance(object_interface  object,int period, int inc)
				        :timeout_filter(object,period,FILTER_MASK),_inc(inc)
	{
		_filter_id = FILTER_INCCRITRESISTANCE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCCRITRESISTANCE, _timeout);
		_parent.EnhanceCritResistance(_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCCRITRESISTANCE);
		_parent.ImpairCritResistance(_inc);
	}
};

class filter_Deccritresistance : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _dec;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _dec;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _dec;
		return true;
	}

	filter_Deccritresistance(){}
public:
	DECLARE_SUBSTANCE(filter_Deccritresistance); 
	filter_Deccritresistance(object_interface  object,int period, int dec)
				        :timeout_filter(object,period,FILTER_MASK),_dec(dec)
	{
		_filter_id = FILTER_DECCRITRESISTANCE;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_DECCRITRESISTANCE);
		_parent.InsertTeamVisibleState(HSTATE_DECCRITRESISTANCE, _timeout);
		_parent.ImpairCritResistance(_dec);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_DECCRITRESISTANCE);
		_parent.RemoveTeamVisibleState(HSTATE_DECCRITRESISTANCE);
		_parent.EnhanceCritResistance(_dec);
	}
};

class filter_Transmitskillattack : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	XID _target;
	float _squared_range;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _target << _squared_range << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _target >> _squared_range >> _counter;
		return true;
	}

	filter_Transmitskillattack(){}
public:
	DECLARE_SUBSTANCE(filter_Transmitskillattack); 
	filter_Transmitskillattack(object_interface  object,int period, const XID & target, float range)
				        :timeout_filter(object,period,FILTER_MASK),_target(target),_squared_range(range*range),_counter(0)
	{
		_filter_id = FILTER_TRANSMITSKILLATTACK;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_TRANSMITSKILLATTACK);
		_parent.InsertTeamVisibleState(HSTATE_TRANSMITSKILLATTACK, _timeout);
		_parent.SetSkillAttackTransmit(_target);
		_parent.AddMultiObjEffect(_target, MULTIOBJ_EFFECT_ATTACK);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_TRANSMITSKILLATTACK);
		_parent.RemoveTeamVisibleState(HSTATE_TRANSMITSKILLATTACK);
		_parent.SetSkillAttackTransmit(XID(-1,-1));
		_parent.RemoveMultiObjEffect(_target, MULTIOBJ_EFFECT_ATTACK);
	}
	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3)
		{
			A3DVECTOR pos;
			float body_size;
			if(_parent.QueryObject(_target, pos, body_size) != 1 || pos.squared_distance(_parent.GetPos()) > _squared_range) _is_deleted = true; 
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Additionalheal : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_ADJUST_HEAL
	};

	XID _target;
	float _ratio;
	float _squared_range;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _target << _ratio << _squared_range << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _target >> _ratio >> _squared_range >> _counter;
		return true;
	}
	filter_Additionalheal(){}
public:
	DECLARE_SUBSTANCE(filter_Additionalheal); 
	filter_Additionalheal(object_interface  object,int period,const XID & target, float ratio,float range)
			:timeout_filter(object,period,FILTER_MASK),_target(target),_ratio(ratio),_squared_range(range*range),_counter(0)
	{
		_filter_id = FILTER_ADDITIONALHEAL;
	}

	void OnAttach() 
	{
		//_parent.IncVisibleState(VSTATE_);
		_parent.InsertTeamVisibleState(HSTATE_ADDITIONALHEAL, _timeout);
	}
	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_);
		_parent.RemoveTeamVisibleState(HSTATE_ADDITIONALHEAL);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3)
		{
			A3DVECTOR pos;
			float body_size;
			if(_parent.QueryObject(_target, pos, body_size) != 1 || pos.squared_distance(_parent.GetPos()) > _squared_range) _is_deleted = true; 
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

	void AdjustHeal(int& heal,char heal_type)
	{
		int h = (int)(heal * _ratio);
		if(h > 0)
		{
			_parent.SendHealMsg(_target, h);
		}
	}
};

class filter_Additionalattack : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_ADJUST_DAMAGE 
	};

	XID _target;
	float _ratio;
	float _range;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _target << _ratio << _range << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _target >> _ratio >> _range >> _counter;
		return true;
	}
	filter_Additionalattack(){}
public:
	DECLARE_SUBSTANCE(filter_Additionalattack); 
	filter_Additionalattack(object_interface  object,int period,const XID & target, float ratio,float range)
			:timeout_filter(object,period,FILTER_MASK),_target(target),_ratio(ratio),_range(range),_counter(0)
	{
		_filter_id = FILTER_ADDITIONALATTACK;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_ADDITIONALATTACK);
		_parent.InsertTeamVisibleState(HSTATE_ADDITIONALATTACK, _timeout);
		_parent.AddMultiObjEffect(_target, MULTIOBJ_EFFECT_ATTACK2);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_ADDITIONALATTACK);
		_parent.RemoveTeamVisibleState(HSTATE_ADDITIONALATTACK);
		_parent.RemoveMultiObjEffect(_target, MULTIOBJ_EFFECT_ATTACK2);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3)
		{
			A3DVECTOR pos;
			float body_size;
			if(_parent.QueryObject(_target, pos, body_size) != 1 || pos.squared_distance(_parent.GetPos()) > _range*_range) _is_deleted = true; 
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

	void AdjustDamage(damage_entry & dmg, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg._attack_state & AT_STATE_AURA_AND_RETORT) return;
		if(attacker == _target) return;

		dmg.physic_damage *= 1.f-_ratio;
		dmg.magic_damage[0] *= 1.f-_ratio;
		dmg.magic_damage[1] *= 1.f-_ratio;
		dmg.magic_damage[2] *= 1.f-_ratio;
		dmg.magic_damage[3] *= 1.f-_ratio;
		dmg.magic_damage[4] *= 1.f-_ratio;

		attack_msg	newmsg;
		memset(&newmsg,0,sizeof(newmsg));
		newmsg.attack_range = _range;
		newmsg.physic_damage	= (int)(msg.physic_damage * _ratio);
		newmsg.attack_rate	= 1000; 
		newmsg.magic_damage[0]	= (int)(msg.magic_damage[0] * _ratio);
		newmsg.magic_damage[1]	= (int)(msg.magic_damage[1] * _ratio);
		newmsg.magic_damage[2]	= (int)(msg.magic_damage[2] * _ratio);
		newmsg.magic_damage[3]	= (int)(msg.magic_damage[3] * _ratio);
		newmsg.magic_damage[4]	= (int)(msg.magic_damage[4] * _ratio);
		newmsg.attack_attr	= attack_msg::MAGIC_ATTACK;
		newmsg.force_attack = _parent.GetForceAttack();
		newmsg.speed = msg.speed;

		_parent.SetAuraAttackState();
		_parent.Attack( _target, newmsg, 0);
	}
};

class filter_Transportdamagetoleader : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_ADJUST_DAMAGE
	};

	float _ratio;
	XID _leader_id;
	float _range;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _leader_id << _range;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _leader_id >> _range;
		return true;
	}
	filter_Transportdamagetoleader(){}
public:
	DECLARE_SUBSTANCE(filter_Transportdamagetoleader); 
	filter_Transportdamagetoleader(object_interface  object,int period,float ratio,const XID & leader_id,float range)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(ratio),_leader_id(leader_id),_range(range*range)
	{
		_filter_id = FILTER_TRANSPORTDAMAGETOLEADER;
	}
	
	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		A3DVECTOR pos;
		float body_size;
		if(_parent.QueryObject(_leader_id,pos,body_size) != 1 || pos.squared_distance(_parent.GetPos()) > _range)
		{
			return;
		}
		
		float damage = (dmg.physic_damage + dmg.magic_damage[0] + dmg.magic_damage[1] + dmg.magic_damage[2] + dmg.magic_damage[3] + dmg.magic_damage[4]) * damage_adjust * _ratio; 
		if((int)damage <= 1) return;

		_parent.DrainLeaderHPMP(attacker,(int)damage,0);
	}
	
	void OnAttach()
	{
		//_parent.InsertTeamVisibleState(HSTATE_TRANSPORTDAMAGETOLEADER);
	}

	void OnRelease()
	{
		//_parent.RemoveTeamVisibleState(HSTATE_TRANSPORTDAMAGETOLEADER);
	}
};
class filter_Forbidbeselected : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}
	filter_Forbidbeselected(){}
public:
	DECLARE_SUBSTANCE(filter_Forbidbeselected); 
	filter_Forbidbeselected(object_interface  object,int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FORBIDBESELECTED;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_FORBIDBESELECTED);
		_parent.InsertTeamVisibleState(HSTATE_FORBIDBESELECTED, _timeout);
		_parent.ForbidBeSelected(true);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_FORBIDBESELECTED);
		_parent.RemoveTeamVisibleState(HSTATE_FORBIDBESELECTED);
		_parent.ForbidBeSelected(false);
	}
};
class filter_Enhanceskilldamage2 : public timeout_filter//���Ӽ��ܶ�npc���˺�
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE 
	};

	int _inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc;
		return true;
	}

	filter_Enhanceskilldamage2(){}
public:
	DECLARE_SUBSTANCE(filter_Enhanceskilldamage2); 
	filter_Enhanceskilldamage2(object_interface  object,int period,int inc)
				        :timeout_filter(object,period,FILTER_MASK),_inc(inc)
	{
		_filter_id = FILTER_ENHANCESKILLDAMAGE2;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ENHANCESKILLDAMAGE2, _timeout);
		_parent.EnhanceSkillDamage(_inc);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ENHANCESKILLDAMAGE2);
		_parent.ImpairSkillDamage(_inc);
	}
};
class filter_Delayhurt2 : public timeout_filter 
{
protected:
	int _damage;
	XID _performer;
	attacker_info_t _pinfo;
	bool _invader;
	char _mode;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damage;
		ar << _performer;
		ar.push_back(&_pinfo, sizeof(attacker_info_t));
		ar << _invader;
		ar << _mode;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damage;
		ar >> _performer;
		ar.pop_back(&_pinfo, sizeof(attacker_info_t));
		ar >> _invader;
		ar >> _mode;
		return true;
	}
	filter_Delayhurt2(){}
public:
	filter_Delayhurt2(object_interface  object,int period,int damage,int mask)
			:timeout_filter(object,period,mask),_damage(damage)
	{
	}

	void SetUp(const XID& player, const attacker_info_t& info, char mode, bool invader)
	{
		_performer = player;
		_pinfo = info;
		_mode = mode;
		_invader = invader;
	}

	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_is_deleted) 
			_parent.BeHurt(_performer, _pinfo, _damage, _invader, _mode);	
	}

};

class filter_Delayearthhurt : public filter_Delayhurt2
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	filter_Delayearthhurt(){}
public:
	DECLARE_SUBSTANCE(filter_Delayearthhurt); 
	filter_Delayearthhurt(object_interface  object,int period,int damage)
		:filter_Delayhurt2(object,period,damage,FILTER_MASK)
	{
		_filter_id = FILTER_DELAYEARTHHURT;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_DELAYEARTHHURT);
		_parent.InsertTeamVisibleState(HSTATE_DELAYEARTHHURT, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_DELAYEARTHHURT);
		_parent.RemoveTeamVisibleState(HSTATE_DELAYEARTHHURT);
	}
};

class filter_Dizzyinchurt : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Dizzyinchurt(){}
public:
	DECLARE_SUBSTANCE(filter_Dizzyinchurt); 
	filter_Dizzyinchurt(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DIZZYINCHURT;
		_ratio = 1.0+ratio;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_STUN);
		_parent.IncVisibleState(VSTATE_DIZZYINCHURT);
		_parent.InsertTeamVisibleState(HSTATE_DIZZYINCHURT, _timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_STUN);
		_parent.DecVisibleState(VSTATE_DIZZYINCHURT);
		_parent.RemoveTeamVisibleState(HSTATE_DIZZYINCHURT);
	}
};
class filter_Soulretort2 : public filter_Soulbase
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_SAVE_DB_DATA
	};
	
	float _ratio;	
	
	virtual bool Save(archive & ar)
	{
		//���filter�����ߺ󱣴棬����ʱ
		//����_timeout
		int tmp = _timeout;
		_timeout += time(NULL);
		
		filter_Soulbase::Save(ar);
		ar << _ratio;
		
		//�ָ�_timeout
		_timeout = tmp;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Soulbase::Load(ar);
		ar >> _ratio;

		//�ָ�_timeout
		_timeout -= time(NULL);
		if(_timeout <= 0) _timeout = 1;
		return true;
	}
	
	filter_Soulretort2(){}
public:
	DECLARE_SUBSTANCE(filter_Soulretort2);
	filter_Soulretort2(object_interface object,int period,float ratio,int trigger_prob,int mp_cost,char del_on_trigger)
			:filter_Soulbase(object,period,FILTER_MASK,trigger_prob,mp_cost,del_on_trigger),_ratio(ratio)
	{
		_filter_id = FILTER_SOULRETORT2;	
	}

	void Merge(filter* f)
	{
		ASSERT(dynamic_cast<filter_Soulretort2*>(f));	
		filter_Soulretort2* nf = (filter_Soulretort2*) f;
		if(nf->GetValue() == _ratio)
		{
			if(GetTimeOut(nf) > _timeout) _timeout = GetTimeOut(nf);		
		}
		else if(nf->GetValue() > _ratio)
		{
			_timeout = GetTimeOut(nf);
			_ratio = nf->GetValue();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SOULRETORT2);
			_parent.InsertTeamVisibleState(HSTATE_SOULRETORT2, _timeout);
		}
		
	}

	bool DoSoulAdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg._attack_state & AT_STATE_ALL_RETORT) return false;
		int damage = (int)(msg.physic_damage * _ratio);
		if(damage <= 1) return false;
		
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.physic_damage	= damage;
		ret.attack_rate	= 1000;
		ret.force_attack = _parent.GetForceAttack();
		ret.attack_attr = attack_msg::MAGIC_ATTACK;
		ret.attack_range = msg.attack_range + 0.5;
		ret.speed = msg.speed;
		ret.skill_id = 1146;
		_parent.SetRetortState();
		_parent.Attack( attacker, ret, 0);
		return true;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_SOULRETORT2);
		_parent.InsertTeamVisibleState(HSTATE_SOULRETORT2, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_SOULRETORT2);
		_parent.RemoveTeamVisibleState(HSTATE_SOULRETORT2);
	}

	float GetValue()
	{
		return _ratio;	
	}
};

class filter_Fixondamage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_DO_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _rooted_time;
	int _last_time;		//�ϴδ�����ʱ��
	int _cd_time;		//�������˵���ȴʱ��

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _rooted_time << _last_time << _cd_time;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _rooted_time >>  _last_time >> _cd_time;
		return true;
	}

	filter_Fixondamage(){}
public:
	DECLARE_SUBSTANCE(filter_Fixondamage); 
	filter_Fixondamage(object_interface  object, int period, int rooted_time, int cd_time)
				        :timeout_filter(object,period,FILTER_MASK),_rooted_time(rooted_time),_last_time(INT_MAX),_cd_time(cd_time)
	{
		_filter_id = FILTER_FIXONDAMAGE;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_FIXONDAMAGE);
		_parent.InsertTeamVisibleState(HSTATE_FIXONDAMAGE, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_FIXONDAMAGE);
		_parent.RemoveTeamVisibleState(HSTATE_FIXONDAMAGE);
	}

	void DoDamage(const damage_entry & dmg)
	{
		if(_last_time-_timeout >= _cd_time)
		{
			_last_time = _timeout;	
			_parent.AddFilter(new filter_Fix(_parent,_rooted_time));
		}
	}
};

class filter_Apgen2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_DO_DAMAGE 
	};

	int _damage;
	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damage << _point;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damage >> _point;
		return true;
	}
	filter_Apgen2(){}
public:
	DECLARE_SUBSTANCE(filter_Apgen2); 
	filter_Apgen2(object_interface  object, int period, int damage, int point)
				        :timeout_filter(object,period,FILTER_MASK),_damage(damage),_point(point)
	{
		_filter_id = FILTER_APGEN2;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_APGEN2, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_APGEN2);
	}

	void DoDamage(const damage_entry & dmg)
	{
		if(dmg.physic_damage+dmg.magic_damage[0]+dmg.magic_damage[1]+dmg.magic_damage[2]+dmg.magic_damage[3]+dmg.magic_damage[4] >= _damage)
			_parent.ModifyAP(_point);
	}
};

class filter_Incattack3 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	int _cur_merge;
	int _merge_max;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _cur_merge << _merge_max;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _cur_merge >> _merge_max;
		return true;
	}
	filter_Incattack3(){}
public:
	DECLARE_SUBSTANCE(filter_Incattack3); 
	filter_Incattack3(object_interface  object,int period,int ratio,int merge_max)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(ratio),_cur_merge(1),_merge_max(merge_max)
	{
		_filter_id = FILTER_INCATTACK3;
	}
	void Merge(filter *f)
	{
		if(_cur_merge < _merge_max)
		{
			_cur_merge ++;
			ASSERT(dynamic_cast<filter_Incattack3*>(f));
			filter_Incattack3* nf = (filter_Incattack3*) f;
			_parent.ImpairScaleDamage(_ratio);
			_ratio += nf->GetRatio();
			_parent.EnhanceScaleDamage(_ratio);
			_parent.UpdateAttackData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCATTACK3);
			_parent.InsertTeamVisibleState(HSTATE_INCATTACK3, _timeout);
		}
		
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCATTACK3, _timeout);
		_parent.EnhanceScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCATTACK3);
		_parent.ImpairScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

class filter_Incattackondamage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_DO_DAMAGE 
	};

	int _damage;
	int _ia_time;
	int _ia_ratio;
	int _ia_merge_max;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damage << _ia_time << _ia_ratio << _ia_merge_max;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damage >> _ia_time >> _ia_ratio >> _ia_merge_max;
		return true;
	}
	filter_Incattackondamage(){}
public:
	DECLARE_SUBSTANCE(filter_Incattackondamage); 
	filter_Incattackondamage(object_interface  object, int period, int damage, int ia_time, int ia_ratio, int ia_merge_max)
				        :timeout_filter(object,period,FILTER_MASK),_damage(damage),_ia_time(ia_time),_ia_ratio(ia_ratio),_ia_merge_max(ia_merge_max)
	{
		_filter_id = FILTER_INCATTACKONDAMAGE;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INCATTACKONDAMAGE);
		_parent.InsertTeamVisibleState(HSTATE_INCATTACKONDAMAGE, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INCATTACKONDAMAGE);
		_parent.RemoveTeamVisibleState(HSTATE_INCATTACKONDAMAGE);
	}

	void DoDamage(const damage_entry & dmg)
	{
		if(dmg.physic_damage+dmg.magic_damage[0]+dmg.magic_damage[1]+dmg.magic_damage[2]+dmg.magic_damage[3]+dmg.magic_damage[4] >= _damage)
		{
			_parent.AddFilter(new filter_Incattack3(_parent,_ia_time,_ia_ratio,_ia_merge_max));
		}
	}
};
class filter_Rebirth2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_BEFORE_DEATH
	};

	float _hp_ratio;
	int _ap;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _hp_ratio << _ap;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _hp_ratio >> _ap;
		return true;
	}

	filter_Rebirth2(){}
public:
	DECLARE_SUBSTANCE(filter_Rebirth2);
	filter_Rebirth2(object_interface parent, int period, float hp_ratio, int ap)
		:timeout_filter(parent,period,FILTER_MASK),_hp_ratio(hp_ratio),_ap(ap)
	{   
		_filter_id = FILTER_REBIRTH2;
	}

	virtual void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_REBIRTH2);
		_parent.InsertTeamVisibleState(HSTATE_REBIRTH2, _timeout);
	}
	
	virtual void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_REBIRTH2);
		_parent.RemoveTeamVisibleState(HSTATE_REBIRTH2);
	}

	virtual void BeforeDeath(const XID & attacker, char attacker_mode)
	{
		_parent.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
		_parent.Heal((int)(_parent.GetExtendProp().max_hp*_hp_ratio));
		_parent.ModifyAP(_ap);
		//_parent.SendClientEnchantResult(_parent.GetSelfID(), 1085, 1, false, 0);
		_is_deleted = true;
	}
};

class filter_Healsteal : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_ADJUST_HEAL
	};

	XID _target;
	float _squared_range;
	float _ratio;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _target << _squared_range << _ratio << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _target >> _squared_range >> _ratio >> _counter;
		return true;
	}
	filter_Healsteal(){}
public:
	DECLARE_SUBSTANCE(filter_Healsteal); 
	filter_Healsteal(object_interface  object,int period,const XID& target, float range, float ratio)
			:timeout_filter(object,period,FILTER_MASK),_target(target),_squared_range(range*range),_ratio(ratio),_counter(0)
	{
		_filter_id = FILTER_HEALSTEAL;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_HEALSTEAL);
		_parent.InsertTeamVisibleState(HSTATE_HEALSTEAL, _timeout);
		_parent.AddMultiObjEffect(_target, MULTIOBJ_EFFECT_HEAL);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_HEALSTEAL);
		_parent.RemoveTeamVisibleState(HSTATE_HEALSTEAL);
		_parent.RemoveMultiObjEffect(_target, MULTIOBJ_EFFECT_HEAL);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3)
		{
			A3DVECTOR pos;
			float body_size;
			if(_parent.QueryObject(_target, pos, body_size) != 1 || pos.squared_distance(_parent.GetPos()) > _squared_range) _is_deleted = true; 
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
	void AdjustHeal(int& heal,char heal_type)
	{
		int h = (int)(heal * _ratio);
		if(h > 0)
		{
			_parent.SendHealMsg(_target, h);
			heal -= h;
		}
	}
};
class filter_Dropmoneyondeath : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_BEFORE_DEATH
	};

	int _money;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _money;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _money;
		return true;
	}

	filter_Dropmoneyondeath(){}
public:
	DECLARE_SUBSTANCE(filter_Dropmoneyondeath); 
	filter_Dropmoneyondeath(object_interface  object,int period,int money)
				        :timeout_filter(object,period,FILTER_MASK),_money(money)
	{
		_filter_id = FILTER_DROPMONEYONDEATH;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_DROPMONEYONDEATH);
		_parent.InsertTeamVisibleState(HSTATE_DROPMONEYONDEATH, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_DROPMONEYONDEATH);
		_parent.RemoveTeamVisibleState(HSTATE_DROPMONEYONDEATH);
	}

	virtual void BeforeDeath(const XID & attacker, char attacker_mode)
	{
		if(attacker_mode & attack_msg::PVP_DUEL) return;
		//if(_money > 0) _parent.DropMoney((size_t)_money,false);
		_parent.DropSpecItem(false, attacker);
		_is_deleted = true;
	}
};

class filter_Incattackrange : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _range;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _range;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _range;
		return true;
	}
	filter_Incattackrange(){}
public:
	DECLARE_SUBSTANCE(filter_Incattackrange); 
	filter_Incattackrange(object_interface  object,int period,float range)
				        :timeout_filter(object,period,FILTER_MASK),_range(range)
	{
		_filter_id = FILTER_INCATTACKRANGE;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incattackrange*>(f));
		filter_Incattackrange* nf = (filter_Incattackrange*) f;
		_timeout = GetTimeOut(nf);
		if(_range!=nf->GetValue())
		{
			_parent.ImpairAttackRange(_range);
			_range = nf->GetValue();
			_parent.EnhanceAttackRange(_range);
			_parent.UpdateAttackData();
			_parent.SendClientAttackData();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCATTACKRANGE);
			_parent.InsertTeamVisibleState(HSTATE_INCATTACKRANGE, _timeout);
		}
		
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INCATTACKRANGE);
		_parent.InsertTeamVisibleState(HSTATE_INCATTACKRANGE, _timeout);
		_parent.EnhanceAttackRange(_range);
		_parent.UpdateAttackData();
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INCATTACKRANGE);
		_parent.RemoveTeamVisibleState(HSTATE_INCATTACKRANGE);
		_parent.ImpairAttackRange(_range);
		_parent.UpdateAttackData();
		_parent.SendClientAttackData();
	}
	float GetValue()
	{
		return _range;
	}
};
class filter_Thunderform : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK
	};

	int _inc_hp;
	int _inc_magic;

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _inc_hp << _inc_magic;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _inc_hp >> _inc_magic;
		return true;
	}
	filter_Thunderform(){}
public:
	DECLARE_SUBSTANCE(filter_Thunderform); 
	filter_Thunderform(object_interface  object, int inc_hp, int inc_magic)
			:filter(object,FILTER_MASK),_inc_hp(inc_hp),_inc_magic(inc_magic)
	{
		_filter_id = FILTER_THUNDERFORM;
	}

	void OnAttach()
	{
		_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
		_parent.LockEquipment(true);
		_parent.ChangeShape(1|(FORM_CLASS<<6));
		_parent.IncVisibleState(VSTATE_THUNDERFORM);
		_parent.InsertTeamVisibleState(HSTATE_THUNDERFORM, -1);		
		_parent.EnhanceMaxHP(_inc_hp);
		_parent.EnhanceScaleMagicDamage(_inc_magic);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
		_parent.LockEquipment(false);
		_parent.ChangeShape(0);
		_parent.DecVisibleState(VSTATE_THUNDERFORM);
		_parent.RemoveTeamVisibleState(HSTATE_THUNDERFORM);	
		_parent.ImpairMaxHP(_inc_hp);
		_parent.ImpairScaleMagicDamage(_inc_magic);
		_parent.UpdateMagicData();
	}
};

class filter_Delaytransmit : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE 
	};

	int _tag;
	A3DVECTOR _pos;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _tag << _pos;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _tag >> _pos;
		return true;
	}
	filter_Delaytransmit(){}
public:
	DECLARE_SUBSTANCE(filter_Delaytransmit); 
	filter_Delaytransmit(object_interface  object,int period,int tag,const A3DVECTOR & pos)
			:timeout_filter(object,period,FILTER_MASK),_tag(tag),_pos(pos)
	{
		_filter_id = FILTER_DELAYTRANSMIT;
	}

	void OnAttach() 
	{
		//_parent.IncVisibleState(VSTATE_);
		_parent.InsertTeamVisibleState(HSTATE_DELAYTRANSMIT, _timeout);
	}
	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_);
		_parent.RemoveTeamVisibleState(HSTATE_DELAYTRANSMIT);
	}

	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_timeout <= 0 && !_parent.IsDead())
		{
			_parent.LongJump(_pos,_tag);
		}
	}
};

class filter_Decnormalattackhurt : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE 
	};

	bool _active;
	int _active_time;
	float _ratio;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _active << _active_time << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _active >> _active_time >> _ratio;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg.skill_id || msg.short_range > 1e-6) return;
		//��ս�չ���Ч
		if(_active)
		{
			dmg.physic_damage *= _ratio;
			dmg.magic_damage[0] *= _ratio;
			dmg.magic_damage[1] *= _ratio;
			dmg.magic_damage[2] *= _ratio;
			dmg.magic_damage[3] *= _ratio;
			dmg.magic_damage[4] *= _ratio;
		}
		else
		{
			_active = true;
			_timeout = _active_time;
		}
	}

	filter_Decnormalattackhurt(){}
public:
	DECLARE_SUBSTANCE(filter_Decnormalattackhurt); 
	filter_Decnormalattackhurt(object_interface  object,int period,int active_time,float ratio)
				        :timeout_filter(object,period,FILTER_MASK),_active(false),_active_time(active_time)
	{
		_filter_id = FILTER_DECNORMALATTACKHURT;
		_ratio = 1.0-ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECNORMALATTACKHURT, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECNORMALATTACKHURT);
	}
};

class filter_Freemoveapgen : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_NOSAVE | FILTER_MASK_ADJUST_DAMAGE
	};

	int _counter;
	int _ap;
	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _counter << _ap;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _counter >> _ap;
		return true;
	}

	filter_Freemoveapgen(){}
public:
	DECLARE_SUBSTANCE(filter_Freemoveapgen); 
	filter_Freemoveapgen(object_interface object, int period, float r, int ap)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FREEMOVEAPGEN;
		_counter = 0;
		_ap = ap/period;
		_ratio = 1.f - r;
	}

	void AdjustDamage(damage_entry & dmg, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	void OnAttach()
	{
	//	_parent.InsertTeamVisibleState(HSTATE_);
		_parent.IncImmuneMask(IMMUNESLOW);
		_parent.IncImmuneMask(IMMUNEFIX);
		_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.IncImmuneMask(IMMUNESLEEP);
	}

	void OnRelease()
	{
	//	_parent.RemoveTeamVisibleState(HSTATE_);
		_parent.DecImmuneMask(IMMUNESLOW);
		_parent.DecImmuneMask(IMMUNEFIX);
		_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.DecImmuneMask(IMMUNESLEEP);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.ModifyAP(_ap*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Incatkdefhp : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT
	};

	int _atk_ratio;
	int _def_ratio;
	int _hp_ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _atk_ratio << _def_ratio << _hp_ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _atk_ratio >> _def_ratio >> _hp_ratio;
		return true;
	}
	filter_Incatkdefhp(){}
public:
	DECLARE_SUBSTANCE(filter_Incatkdefhp); 
	filter_Incatkdefhp(object_interface  object,int period, int atk_ratio, int def_ratio, int hp_ratio)
				        :timeout_filter(object,period,FILTER_MASK),_atk_ratio(atk_ratio),_def_ratio(def_ratio),_hp_ratio(hp_ratio)
	{
		_filter_id = FILTER_INCATKDEFHP;
	}
	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCATKDEFHP, _timeout);
		_parent.EnhanceScaleDamage(_atk_ratio);
		_parent.UpdateAttackData();
		_parent.EnhanceScaleMagicDamage(_atk_ratio);
		_parent.EnhanceScaleDefense(_def_ratio);
		_parent.UpdateDefenseData();
		_parent.EnhanceScaleResistance(0, _def_ratio);
		_parent.EnhanceScaleResistance(1, _def_ratio);
		_parent.EnhanceScaleResistance(2, _def_ratio);
		_parent.EnhanceScaleResistance(3, _def_ratio);
		_parent.EnhanceScaleResistance(4, _def_ratio);
		_parent.UpdateMagicData();
		_parent.EnhanceScaleMaxHP(_hp_ratio);
	}

	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCATKDEFHP);
		_parent.ImpairScaleDamage(_atk_ratio);
		_parent.UpdateAttackData();
		_parent.ImpairScaleMagicDamage(_atk_ratio);
		_parent.ImpairScaleDefense(_def_ratio);
		_parent.UpdateDefenseData();
		_parent.ImpairScaleResistance(0, _def_ratio);
		_parent.ImpairScaleResistance(1, _def_ratio);
		_parent.ImpairScaleResistance(2, _def_ratio);
		_parent.ImpairScaleResistance(3, _def_ratio);
		_parent.ImpairScaleResistance(4, _def_ratio);
		_parent.UpdateMagicData();
		_parent.ImpairScaleMaxHP(_hp_ratio);
	}
};
class filter_Denyattackcmd : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}
	filter_Denyattackcmd(){}
public:
	DECLARE_SUBSTANCE(filter_Denyattackcmd); 
	filter_Denyattackcmd(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DENYATTACKCMD;
	}
	void OnAttach()
	{
		_parent.DenyAttackCmd();
	}

	void OnRelease()
	{
		_parent.AllowAttackCmd();
	}
};
class filter_Hpmpgennotincombat : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};
	int _hpgen;
	int _mpgen;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _hpgen << _mpgen << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _hpgen >> _mpgen >> _counter;
		return true;
	}
	filter_Hpmpgennotincombat(){}
public:
	DECLARE_SUBSTANCE(filter_Hpmpgennotincombat); 
	filter_Hpmpgennotincombat(object_interface  object, int period, int hpgen, int mpgen)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_HPMPGENNOTINCOMBAT;
		_counter = 0;
		_hpgen = hpgen/period;
		_mpgen = mpgen/period;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_HPMPGENNOTINCOMBAT, _timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_HPMPGENNOTINCOMBAT);
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			if(!_parent.IsCombatState())
			{
				_parent.HealBySkill(_hpgen*_counter);	
				_parent.InjectMana(_mpgen*_counter);
			}
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Inchpmp : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _hp;
	int _mp;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _hp << _mp;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _hp >> _mp;
		return true;
	}
	filter_Inchpmp(){}
public:
	DECLARE_SUBSTANCE(filter_Inchpmp); 
	filter_Inchpmp(object_interface  object,int period,int hp,int mp)
				        :timeout_filter(object,period,FILTER_MASK),_hp(hp),_mp(mp)
	{
		_filter_id = FILTER_INCHPMP;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCHPMP, _timeout);
		_parent.EnhanceMaxHP(_hp);
		_parent.EnhanceMaxMP(_mp);
	}

	void OnRelease()
	{
		_parent.ImpairMaxHP(_hp);
		_parent.ImpairMaxMP(_mp);
		_parent.RemoveTeamVisibleState(HSTATE_INCHPMP);
	}
};

class filter_Inchurt3 : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_MERGE,
	};

	float _ratio;    //�˺��������??
	int _pile_times; //��ǰ���Ӵ���
	int _pile_limit; //״̬��������

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _pile_times << _pile_limit;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _pile_times >> _pile_limit;
		return true;
	}

	void AdjustDamage(damage_entry & dmg, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Inchurt3(){}
public:
	DECLARE_SUBSTANCE(filter_Inchurt3); 
	filter_Inchurt3(object_interface & object, float ratio, int period, int pile_limit, int filter_mask)
				        :timeout_filter(object, period, FILTER_MASK|filter_mask)
	{
		_filter_id = FILTER_INCHURT3;
		_ratio = 1.0 + ratio;
		_pile_times = 1;
		_pile_limit = pile_limit;
	}

	int OnQuery(int index)
	{
		return index == FILTER_QUERY_LEVEL ? _pile_times : 0;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INFAUST);
		_parent.InsertTeamVisibleState(HSTATE_INCHURT3, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INFAUST);
		_parent.RemoveTeamVisibleState(HSTATE_INCHURT3);
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Inchurt3 *>(f));
		filter_Inchurt3 * filter = (filter_Inchurt3 *)f;
		if(_pile_times < filter->_pile_limit)
		{
			_pile_times++;
			_ratio += (filter->_ratio - 1.0f);
			_pile_limit = filter->_pile_limit;
		}
		_timeout = filter->_timeout;
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCHURT3);
			_parent.InsertTeamVisibleState(HSTATE_INCHURT3, _timeout);
		}
		
	}
};

class filter_Incresist2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_TRANSFERABLE_BUFF,
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incresist2(){}
public:
	DECLARE_SUBSTANCE(filter_Incresist2); 
	filter_Incresist2(object_interface object,int r,int period,int filter_mask)
				        :timeout_filter(object,period,FILTER_MASK|filter_mask),_ratio(r)
	{
		_filter_id = FILTER_INCRESIST2;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_BLESSED);
		_parent.InsertTeamVisibleState(HSTATE_INCRESIST2, _timeout);
		_parent.EnhanceScaleResistance(0, _ratio);
		_parent.EnhanceScaleResistance(1, _ratio);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.EnhanceScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_BLESSED);
		_parent.RemoveTeamVisibleState(HSTATE_INCRESIST2);
		_parent.ImpairScaleResistance(0, _ratio);
		_parent.ImpairScaleResistance(1, _ratio);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.ImpairScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}
};

/*
 * filter_FlagerΪ��ս����,��ս�е�����ӵ�д�״̬��
 * ״̬������:
 * 1) �˺�����;
 * 2) �ƶ��ٶȵ���;
 * 3) Ѫ�����޵���
 * ���ϵ������Ա�����ʽ����,���������ɸ�,��ֵ��������,��ֵ��������
 */
 
class filter_Flager : public filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE,
	};

	struct AdjustRatio
	{
		float hurt;		//����ս��ͨ����˺�����??
		float hurt2;	//��ս�չ����˺���������
		int speed;		//�ƶ��ٶȵ�������
		int max_hp;		//Ѫ�����޵�������
	} _ratio;

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _ratio.hurt << _ratio.hurt2 << _ratio.speed << _ratio.max_hp;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _ratio.hurt >> _ratio.hurt2 >> _ratio.speed >> _ratio.max_hp;
		return true;
	}

	filter_Flager() {}
public:
	DECLARE_SUBSTANCE(filter_Flager); 
	filter_Flager(object_interface & player, float hurt_ratio, float hurt_ratio2, float speed_adjust_ratio, float max_hp_adjust_ratio): filter(player, FILTER_MASK)
	{
		ASSERT(hurt_ratio >= -0.9f && hurt_ratio2 >= -0.9f && max_hp_adjust_ratio >= -0.9f);
		_filter_id = FILTER_FLAGER;
		_ratio.hurt = hurt_ratio + 1.0f;
		_ratio.hurt2 = hurt_ratio2 + 1.0f;
		_ratio.speed = (int)(speed_adjust_ratio * 100);
		_ratio.max_hp = (int)(max_hp_adjust_ratio * 100);
	}

	virtual void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg,float damage_adjust)
	{
		float ratio = 0;
		if(msg.skill_id || msg.short_range > 1e-6)
		{
			ratio = _ratio.hurt;
		}
		else
		{
			//��ս�չ�
			ratio = _ratio.hurt2;
		}


		dmg.physic_damage *= ratio;
		dmg.magic_damage[0] *= ratio;
		dmg.magic_damage[1] *= ratio;
		dmg.magic_damage[2] *= ratio;
		dmg.magic_damage[3] *= ratio;
		dmg.magic_damage[4] *= ratio;
	}

	virtual void OnAttach()
	{
		_parent.EnhanceSpeed(_ratio.speed);
		_parent.EnhanceScaleMaxHP(_ratio.max_hp);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.IncVisibleState(VSTATE_FLAGER);
		_parent.InsertTeamVisibleState(HSTATE_FLAGER, -1);
		_parent.SetNoFly(true);
		_parent.SetNoBind(true);
		_parent.SetNoMount(true);
		_parent.DenyElfSkillCmd();
	}

	virtual void OnRelease() 
	{
		_parent.ImpairSpeed(_ratio.speed);
		_parent.ImpairScaleMaxHP(_ratio.max_hp);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.DecVisibleState(VSTATE_FLAGER);
		_parent.RemoveTeamVisibleState(HSTATE_FLAGER);
		_parent.SetNoFly(false);
		_parent.SetNoBind(false);
		_parent.SetNoMount(false);
		_parent.AllowElfSkillCmd();
	}
};

/*
 *Ѻ�ڻ״̬��
 *״̬������
 *1. ���÷�����
 *2. ��������
 *3. ��ֹʹ�ûس��㡢�س���
 *4. ��ֹ���ܶ��飨 ���ɣ����������ʦ���ٻ�?? 
 *5. ��ֹ���ְٷֱȼ���Ч���������ƶ��ٶȹ̶�Ϊ �����ʼ�ٶ�??+װ���ӳ�
 *
 *EDIT BY LJJ
 */
class filter_Detaindart : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK=FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE | FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT,
	};
	
	bool _show_icon;//�Ƿ���ʾ״̬ͼ�� 0 ��ʾ 1 ����ʾ
	bool _show_lighting_effect;//�Ƿ���ʾ״̬��Ч 0 ��ʾ 1 ����ʾ
	//int _probability;//״̬�����и��ʣ�100��ʾ100%

	virtual bool Save(archive &ar)
	{
		timeout_filter::Save(ar);
		ar << _show_icon << _show_lighting_effect;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _show_icon >> _show_lighting_effect;
		return true;
	}
	filter_Detaindart(){}
public:
	DECLARE_SUBSTANCE(filter_Detaindart);
	filter_Detaindart(object_interface &object, int duration,bool show_icon,bool show_lighting_effect):timeout_filter(object,duration,FILTER_MASK),_show_icon(show_icon),_show_lighting_effect(show_lighting_effect)
	{
		_filter_id = FILTER_DETAINDART;
	}

	virtual void OnAttach()
	{
		if(_show_icon)
			_parent.InsertTeamVisibleState(HSTATE_DETAINDART, _timeout);
		if(_show_lighting_effect)
			_parent.IncVisibleState(VSTATE_DETAINDART);
		_parent.SetNoFly(true);
		_parent.SetNoMount(true);
		_parent.SetNoLongJump(true);
		_parent.SetNoSpeedUp(true);
		_parent.SetNoInvisible(true);
		_parent.SetNoBind(true);

        _parent.UpdateSpeedData();
        _parent.SendClientCurSpeed();
	}
	virtual void OnRelease()
	{
		if(_show_icon)
			_parent.RemoveTeamVisibleState(HSTATE_DETAINDART);
		if(_show_lighting_effect)
			_parent.DecVisibleState(VSTATE_DETAINDART);
		_parent.SetNoFly(false);
		_parent.SetNoMount(false);
		_parent.SetNoLongJump(false);
		_parent.SetNoSpeedUp(false);
		_parent.SetNoInvisible(false);
		_parent.SetNoBind(false);
	}
};


class filter_Subdefencedegree2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT |FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}
	filter_Subdefencedegree2(){}
public:
	DECLARE_SUBSTANCE(filter_Subdefencedegree2); 
	filter_Subdefencedegree2(object_interface object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_value(r)
	{
		_filter_id = FILTER_SUBDEFENCEDEGREE2;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SUBDEFENCEDEGREE2, _timeout);
		_parent.ImpairDefendDegree(_value);
		_parent.SendClientDefenseData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SUBDEFENCEDEGREE2);
		_parent.EnhanceDefendDegree(_value);
		_parent.SendClientDefenseData();
	}

	int GetValue()
	{
		return _value;
	}
};

class filter_Incatkdefhp2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_BUFF
	};

	int _atk_ratio;
	int _def_ratio;
	int _hp_ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _atk_ratio << _def_ratio << _hp_ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _atk_ratio >> _def_ratio >> _hp_ratio;
		return true;
	}
	filter_Incatkdefhp2(){}
public:
	DECLARE_SUBSTANCE(filter_Incatkdefhp2);
	filter_Incatkdefhp2(object_interface object,int period, int atk_ratio, int def_ratio, int hp_ratio)
				        :timeout_filter(object,period,FILTER_MASK),_atk_ratio(atk_ratio),_def_ratio(def_ratio),_hp_ratio(hp_ratio)
	{
		_filter_id = FILTER_INCATKDEFHP2;
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCATKDEFHP2, _timeout);
		_parent.EnhanceScaleDamage(_atk_ratio);
		_parent.UpdateAttackData();
		_parent.EnhanceScaleMagicDamage(_atk_ratio);
		_parent.EnhanceScaleDefense(_def_ratio);
		_parent.UpdateDefenseData();
		_parent.EnhanceScaleResistance(0, _def_ratio);
		_parent.EnhanceScaleResistance(1, _def_ratio);
		_parent.EnhanceScaleResistance(2, _def_ratio);
		_parent.EnhanceScaleResistance(3, _def_ratio);
		_parent.EnhanceScaleResistance(4, _def_ratio);
		_parent.UpdateMagicData();
		_parent.EnhanceScaleMaxHP(_hp_ratio);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCATKDEFHP2);
		_parent.ImpairScaleDamage(_atk_ratio);
		_parent.UpdateAttackData();
		_parent.ImpairScaleMagicDamage(_atk_ratio);
		_parent.ImpairScaleDefense(_def_ratio);
		_parent.UpdateDefenseData();
		_parent.ImpairScaleResistance(0, _def_ratio);
		_parent.ImpairScaleResistance(1, _def_ratio);
		_parent.ImpairScaleResistance(2, _def_ratio);
		_parent.ImpairScaleResistance(3, _def_ratio);
		_parent.ImpairScaleResistance(4, _def_ratio);
		_parent.UpdateMagicData();
		_parent.ImpairScaleMaxHP(_hp_ratio);
	}
};

class filter_Incsmite3 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _point;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point;
		return true;
	}

	filter_Incsmite3(){}
public:
	DECLARE_SUBSTANCE(filter_Incsmite3); 
	filter_Incsmite3(object_interface  object,int inc,int period)
				        :timeout_filter(object,period,FILTER_MASK),_point(inc)
	{
		_filter_id = FILTER_INCSMITE3;
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCSMITE3, _timeout);
		_parent.EnhanceCrit(_point);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCSMITE3);
		_parent.ImpairCrit(_point);
	}
};


class filter_Incpenres : public timeout_filter
{
	//���������ħ����ħ�ȼ�??
	//��ħ: gactive_imp::_penetration
	//��ħ: gactive_imp::_resilience

protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	int _point1;//��ħ��������
	int _point2;//��ħ��������

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point1 << _point2;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point1 >> _point2;
		return true;
	}

	filter_Incpenres(){}
public:
	DECLARE_SUBSTANCE(filter_Incpenres); 
	filter_Incpenres(object_interface object,int period,int p1,int p2)
				        :timeout_filter(object,period,FILTER_MASK),_point1(p1),_point2(p2)
	{
		_filter_id = FILTER_INCPENRES;
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCPENRES, _timeout);
		_parent.IncPenetration(_point1);
		_parent.IncResilience(_point2);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCPENRES);
		_parent.DecPenetration(_point1);
		_parent.DecResilience(_point2);
	}
};

//ͬʱ����HP����/�����ȼ�/�����ȼ�
class filter_Incmaxhpatkdfdlevel : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE
	};

	int _max_hp_inc;
	int _atk_lvl_inc;
	int _dfd_lvl_inc;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _max_hp_inc << _atk_lvl_inc << _dfd_lvl_inc;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _max_hp_inc >> _atk_lvl_inc >> _dfd_lvl_inc;
		return true;
	}

	filter_Incmaxhpatkdfdlevel() {}
public:
	DECLARE_SUBSTANCE(filter_Incmaxhpatkdfdlevel); 
	filter_Incmaxhpatkdfdlevel(object_interface object,int period,float maxhp_inc,int atklvl_inc,int dfdlvl_inc,int filter_mask)
		:timeout_filter(object,period,filter_mask|FILTER_MASK)
	{
		_filter_id = FILTER_INCMAXHPATKDFDLEVEL;
		_max_hp_inc = (int)(100*maxhp_inc);
		_atk_lvl_inc = atklvl_inc;
		_dfd_lvl_inc = dfdlvl_inc;
	}
	virtual void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCMAXHPATKDFDLEVEL, _timeout);
		_parent.EnhanceScaleMaxHP(_max_hp_inc);
		_parent.EnhanceAttackDegree(_atk_lvl_inc);
		_parent.EnhanceDefendDegree(_dfd_lvl_inc);
	}
	virtual void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCMAXHPATKDFDLEVEL);
		_parent.ImpairScaleMaxHP(_max_hp_inc);
		_parent.ImpairAttackDegree(_atk_lvl_inc);
		_parent.ImpairDefendDegree(_dfd_lvl_inc);
	}
};

/*
 * �˺�����3
 * ֻ����һ������ɵ��˺����?
 */
class filter_Dechurt3 : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	virtual void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(attacker.IsPlayerClass())
		{
			//����һ���﹥����Ч
			dmg.physic_damage *= _ratio;
			dmg.magic_damage[0] *= _ratio;
			dmg.magic_damage[1] *= _ratio;
			dmg.magic_damage[2] *= _ratio;
			dmg.magic_damage[3] *= _ratio;
			dmg.magic_damage[4] *= _ratio;
		}
	}

	filter_Dechurt3(){}
public:
	DECLARE_SUBSTANCE(filter_Dechurt3); 
	filter_Dechurt3(object_interface object,float ratio, int period, int mask):
		timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_DECHURT3;
		_ratio = 1.0-ratio;
	}

	virtual void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECHURT3, _timeout);
	}
	virtual void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECHURT3);
	}
};

//��ͨ����ʱ��һ�����ʶ��Լ�����״̬��
class filter_Attachstatetoself : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	int _skill_id;
	int _skill_lvl;
	int _trigger_prob;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _skill_id << _skill_lvl << _trigger_prob;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _skill_id >> _skill_lvl >> _trigger_prob;
		return true;
	}

	filter_Attachstatetoself() {}
public:
	DECLARE_SUBSTANCE(filter_Attachstatetoself); 
	filter_Attachstatetoself(object_interface object,int period,int skill_id,int skill_lvl,int probability,int mask):
		timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_ATTACHSTATETOSELF;
		_skill_id = skill_id;
		_skill_lvl = skill_lvl;
		_trigger_prob = probability;
	}

	virtual void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(msg.skill_id == 0 && !(msg._attack_state & AT_STATE_AURA_AND_RETORT) && rand()%100 < _trigger_prob)
		{
			SkillKeeper skill = Skill::Create(_skill_id);
			if(!skill) return;
			if(skill->GetRange().IsSelf())
			{
				PlayerWrapper w_player(_parent,NULL,skill);
				skill->SetVictim(&w_player);
				skill->SetPerformerid(_parent.GetSelfID());
				skill->SetLevel(_skill_lvl);
				skill->StateAttack();
				_parent.SendClientEnchantResult(_parent.GetSelfID(),_skill_id,_skill_lvl,false,0,0);
			}
		}
	}

	virtual void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ATTACHSTATETOSELF, _timeout);
	}
	virtual void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ATTACHSTATETOSELF);
	}
};

//��ͨ����ʱ��һ�����ʶ�Ŀ�긽��״̬��
class filter_Attachstatetotarget : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	int _skill_id;
	int _skill_lvl;
	int _trigger_prob;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _skill_id << _skill_lvl << _trigger_prob;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _skill_id >> _skill_lvl >> _trigger_prob;
		return true;
	}

	filter_Attachstatetotarget() {}
public:
	DECLARE_SUBSTANCE(filter_Attachstatetotarget); 
	filter_Attachstatetotarget(object_interface object,int period,int skill_id,int skill_lvl,int probability,int mask):
		timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_ATTACHSTATETOTARGET;
		_skill_id = skill_id;
		_skill_lvl = skill_lvl;
		_trigger_prob = probability;
	}

	virtual void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(msg.skill_id == 0 && !(msg._attack_state & AT_STATE_AURA_AND_RETORT) && rand()%100 < _trigger_prob)
		{
			SkillKeeper skill = Skill::Create(_skill_id);
			if(!skill) return;
			if(skill->DoEnchant())
			{
				//��Ŀ�긽��״̬��
				msg.attached_skill.skill = _skill_id;
				msg.attached_skill.level = _skill_lvl;
			}
		}
	}

	virtual void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ATTACHSTATETOTARGET, _timeout);
	}
	virtual void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ATTACHSTATETOTARGET);
	}
};

/*
 * ��filter_Baseimmune����: 
 * 1 �Ƿ�����?��������??,
 * 2 ��״̬�����Ը��Ǿ�״̬��
 */
class filter_Baseimmune2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _immune_mask;
	int _vstate;
	int _hstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _immune_mask << _vstate << _hstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _immune_mask >> _vstate >> _hstate;
		return true;
	}

	filter_Baseimmune2(){}
public:
	filter_Baseimmune2(object_interface object, int period, int immune_mask, int filter_mask, int vstate, int hstate)
		:timeout_filter(object,period,FILTER_MASK|filter_mask), _immune_mask(immune_mask), _vstate(vstate), _hstate(hstate){}

	void OnAttach()
	{
		if(_hstate >= 0)
			_parent.InsertTeamVisibleState(_hstate,_timeout);
		if(_vstate >= 0)
			_parent.IncVisibleState(_vstate);
		_parent.IncImmuneMask(_immune_mask);
	}

	void OnRelease()
	{
		if(_hstate >= 0)
			_parent.RemoveTeamVisibleState(_hstate);
		if(_vstate >= 0)
			_parent.DecVisibleState(_vstate);
		_parent.DecImmuneMask(_immune_mask);
	}
};

class filter_Immunephysical2 : public filter_Baseimmune2
{
protected:
	filter_Immunephysical2(){}
public:
	DECLARE_SUBSTANCE(filter_Immunephysical2);
	filter_Immunephysical2(object_interface object, int period, int mask)
		:filter_Baseimmune2(object,period,IMMUNEPHYSICAL,mask,-1,HSTATE_IMMUNEPHYSICAL2)
	{
		_filter_id = FILTER_IMMUNEPHYSICAL2;
	}
};
class filter_Immunefire2 : public filter_Baseimmune2
{
protected:
	filter_Immunefire2(){}
public:
	DECLARE_SUBSTANCE(filter_Immunefire2);
	filter_Immunefire2(object_interface object, int period, int mask, bool insertvstate=true)
		:filter_Baseimmune2(object,period,IMMUNEFIRE,mask,(insertvstate?VSTATE_IMMUNEFIRE:-1),HSTATE_IMMUNEFIRE2)
	{
		_filter_id = FILTER_IMMUNEFIRE2;
	}
};
class filter_Immunewater2 : public filter_Baseimmune2
{
protected:
	filter_Immunewater2(){}
public:
	DECLARE_SUBSTANCE(filter_Immunewater2);
	filter_Immunewater2(object_interface object, int period, int mask, bool insertvstate=true)
		:filter_Baseimmune2(object,period,IMMUNEWATER,mask,(insertvstate?VSTATE_IMMUNEWATER:-1),HSTATE_IMMUNEWATER2)
	{
		_filter_id = FILTER_IMMUNEWATER2;			
	}
};
class filter_Immunemetal2 : public filter_Baseimmune2
{
protected:
	filter_Immunemetal2(){}
public:
	DECLARE_SUBSTANCE(filter_Immunemetal2);
	filter_Immunemetal2(object_interface object, int period, int mask, bool insertvstate=true)
		:filter_Baseimmune2(object,period,IMMUNEMETAL,mask,(insertvstate?VSTATE_IMMUNEMETAL:-1),HSTATE_IMMUNEMETAL2)
	{
		_filter_id = FILTER_IMMUNEMETAL2;
	}
};
class filter_Immunewood2 : public filter_Baseimmune2
{
protected:
	filter_Immunewood2(){}
public:
	DECLARE_SUBSTANCE(filter_Immunewood2);
	filter_Immunewood2(object_interface object, int period, int mask, bool insertvstate=true)
		:filter_Baseimmune2(object,period,IMMUNEWOOD,mask,(insertvstate?VSTATE_IMMUNEWOOD:-1),HSTATE_IMMUNEWOOD2)
	{
		_filter_id = FILTER_IMMUNEWOOD2;
	}
};
class filter_Immunesoil2 : public filter_Baseimmune2
{
protected:
	filter_Immunesoil2(){}
public:
	DECLARE_SUBSTANCE(filter_Immunesoil2);
	filter_Immunesoil2(object_interface object, int period, int mask, bool insertvstate=true)
		:filter_Baseimmune2(object,period,IMMUNESOIL,mask,(insertvstate?VSTATE_IMMUNESOIL:-1),HSTATE_IMMUNESOIL2)
	{
		_filter_id = FILTER_IMMUNESOIL2;
	}
};
class filter_Retort2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;
	float _ratio_skill;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _ratio_skill;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _ratio_skill;
		return true;
	}

	filter_Retort2(){}
public:
	DECLARE_SUBSTANCE(filter_Retort2); 
	filter_Retort2(object_interface  object,float ratio, float ratio_skill, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_RETORT2;
		_ratio = ratio;
		_ratio_skill = ratio_skill;
	}
	
	void Merge(filter* f)
	{
		ASSERT(dynamic_cast<filter_Retort2*>(f));	
		filter_Retort2* nf = (filter_Retort2*) f;
		if(nf->GetValue() == _ratio)
		{
			if(GetTimeOut(nf) > _timeout) _timeout = GetTimeOut(nf);		
		}
		else if(nf->GetValue() > _ratio)
		{
			_timeout = GetTimeOut(nf);
			_ratio = nf->GetValue();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_RETORT2);
			_parent.InsertTeamVisibleState(HSTATE_RETORT2, _timeout);
		}
		
	}

	void AdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg.physic_damage >= 1000000) return;
		int damage = (int)(msg.physic_damage * (msg.skill_id ? _ratio_skill : _ratio));
		if(msg.short_range>0 || !IS_PHYSIC_ATTACK(msg.attack_attr) || damage <= 1)	
			return;
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.physic_damage	= damage;
		ret.short_range = 0.1;
		ret.attack_rate	 = 1000;
		ret.force_attack = false;
		ret.attack_attr	= attack_msg::MAGIC_ATTACK;
		ret.attack_range = msg.attack_range + 0.5;
		ret.speed = msg.speed;
					  
		_parent.SetRetortState();
		_parent.Attack( attacker, ret, 0);
			  
	}
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_RETORT);
		_parent.InsertTeamVisibleState(HSTATE_RETORT2, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_RETORT);
		_parent.RemoveTeamVisibleState(HSTATE_RETORT2);
	}
	
	float GetValue()
	{
		return _ratio;	
	}
	
};
class filter_Addattackdefenddegree : public timeout_filter	//��ս����buff
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE
	};

	int _attack_inc;	//�����ȼ�����
	int _defend_inc;	//�����ȼ�����

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _attack_inc << _defend_inc;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _attack_inc >> _defend_inc;
		return true;
	}
	filter_Addattackdefenddegree(){}
public:
	DECLARE_SUBSTANCE(filter_Addattackdefenddegree); 
	filter_Addattackdefenddegree(object_interface  object,int period, int attack_inc, int defend_inc)
				        :timeout_filter(object,period,FILTER_MASK),_attack_inc(attack_inc),_defend_inc(defend_inc)
	{
		_filter_id = FILTER_ADDATTACKDEFENDDEGREE;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_ADDATTACKDEFENDDEGREE, _timeout);
		_parent.EnhanceAttackDegree(_attack_inc);
		_parent.EnhanceDefendDegree(_defend_inc);
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_ADDATTACKDEFENDDEGREE);
		_parent.ImpairAttackDegree(_attack_inc);
		_parent.ImpairDefendDegree(_defend_inc);
		_parent.SendClientAttackData();
	}
};

class filter_Chariotform : public filter_Beastieform
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE
	};

	int _hp;
	int _defense;
	int _resistance[5];
	int _damage;
	int _magic_damage;
	float _speed;
	int _hp_ratio;
	int _skill[4];

	virtual bool Save(archive & ar)
	{
		filter_Beastieform::Save(ar);
		ar << _hp << _defense << _damage << _magic_damage << _speed << _hp_ratio;
		ar.push_back(_resistance, sizeof(_resistance));
		ar.push_back(_skill, sizeof(_skill));
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Beastieform::Load(ar);
		ar >> _hp >> _defense >> _damage >> _magic_damage >> _speed >> _hp_ratio;
		ar.pop_back(_resistance, sizeof(_resistance));
		ar.pop_back(_skill, sizeof(_skill));
		return true;
	}
	
	filter_Chariotform(){}
public:
	DECLARE_SUBSTANCE(filter_Chariotform);
	filter_Chariotform(object_interface object, int shape, int hp, int defense, int resistance[5], int damage, int magic_damage, float speed, int hp_ratio, int skill[4])
		: filter_Beastieform(object, -1, shape, 0, FILTER_MASK), _hp(hp), _defense(defense), _damage(damage), _magic_damage(magic_damage), _speed(speed), _hp_ratio(hp_ratio)
	{
		memcpy(_resistance, resistance, sizeof(_resistance));
		memcpy(_skill, skill, sizeof(_skill));
		//filter idΪFILTER_BEASTIEFORM
	}

	void OnAttach()
	{
		filter_Beastieform::OnAttach();
		_parent.EnhanceMaxHP(_hp);
		_parent.EnhanceScaleMaxHP(_hp_ratio);
		_parent.EnhanceDefense(_defense);
		_parent.EnhanceResistance(0,_resistance[0]);
		_parent.EnhanceResistance(1,_resistance[1]);
		_parent.EnhanceResistance(2,_resistance[2]);
		_parent.EnhanceResistance(3,_resistance[3]);
		_parent.EnhanceResistance(4,_resistance[4]);
		_parent.EnhanceDamage(_damage);
		_parent.EnhanceMagicDamage(_magic_damage);
		_parent.EnhanceSpeed0(_speed);
		if(_skill[0]) (_parent.GetSkillWrapper()).ActivateDynSkill(_skill[0],1);
		if(_skill[1]) (_parent.GetSkillWrapper()).ActivateDynSkill(_skill[1],1);
		if(_skill[2]) (_parent.GetSkillWrapper()).ActivateDynSkill(_skill[2],1);
		if(_skill[3]) (_parent.GetSkillWrapper()).ActivateDynSkill(_skill[3],1);
		_parent.DenyUseItemCmd();
		_parent.DenyNormalAttackCmd();
		_parent.DenyPetCmd();
		_parent.DenyElfSkillCmd();

		_parent.SetNoAmulet(true);

		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
		_parent.UpdateAttackData();
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		filter_Beastieform::OnRelease();	
		_parent.ImpairMaxHP(_hp);
		_parent.ImpairScaleMaxHP(_hp_ratio);
		_parent.ImpairDefense(_defense);
		_parent.ImpairResistance(0,_resistance[0]);
		_parent.ImpairResistance(1,_resistance[1]);
		_parent.ImpairResistance(2,_resistance[2]);
		_parent.ImpairResistance(3,_resistance[3]);
		_parent.ImpairResistance(4,_resistance[4]);
		_parent.ImpairDamage(_damage);
		_parent.ImpairMagicDamage(_magic_damage);
		_parent.ImpairSpeed0(_speed);
		if(_skill[0]) (_parent.GetSkillWrapper()).DeactivateDynSkill(_skill[0],1);
		if(_skill[1]) (_parent.GetSkillWrapper()).DeactivateDynSkill(_skill[1],1);
		if(_skill[2]) (_parent.GetSkillWrapper()).DeactivateDynSkill(_skill[2],1);
		if(_skill[3]) (_parent.GetSkillWrapper()).DeactivateDynSkill(_skill[3],1);
		_parent.AllowUseItemCmd();
		_parent.AllowNormalAttackCmd();
		_parent.AllowPetCmd();
		_parent.AllowElfSkillCmd();
		
		_parent.SetNoAmulet(false);

		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
		_parent.UpdateAttackData();
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void Heartbeat(int tick)
	{
		if(_timeout > 0)
		{
			_timeout -= tick;
			if(_timeout <=0) _is_deleted = true;
		}
	}
};

class filter_Palsy : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	filter_Palsy(){}
public:
	DECLARE_SUBSTANCE(filter_Palsy)
	filter_Palsy(object_interface object, int period, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_PALSY;
	}
	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_STUN);
		_parent.IncVisibleState(VSTATE_PALSY);
		_parent.InsertTeamVisibleState(HSTATE_PALSY, _timeout);
	}
	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_STUN);
		_parent.DecVisibleState(VSTATE_PALSY);
		_parent.RemoveTeamVisibleState(HSTATE_PALSY);
	}
};

class filter_Inchurtfromskill : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_MERGE,
	};

	float _ratio;    //�˺��������??
	int _pile_times; //��ǰ���Ӵ���
	int _pile_limit; //״̬��������
	int _vstate;
	int _hstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _pile_times << _pile_limit << _vstate << _hstate; 
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _pile_times >> _pile_limit >> _vstate >> _hstate;
		return true;
	}

	void AdjustDamage(damage_entry & dmg, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg.skill_id == 0)
			return;

		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_Inchurtfromskill(){}
public:
	DECLARE_SUBSTANCE(filter_Inchurtfromskill); 
	filter_Inchurtfromskill(object_interface & object, float ratio, int period, int pile_limit, int mask,
					int filterid, int vstate, int hstate)
				        :timeout_filter(object, period, FILTER_MASK|mask)
	{
		_filter_id = filterid;		
		_ratio = 1.0 + ratio;
		_pile_times = 1;
		_pile_limit = pile_limit;
		_vstate = vstate;
		_hstate = hstate;
	}

	int OnQuery(int index)
	{
		return index == FILTER_QUERY_LEVEL ? _pile_times : 0;
	}

	void OnAttach()
	{
		if(_vstate)	_parent.IncVisibleState(_vstate);
		if(_hstate) _parent.InsertTeamVisibleState(_hstate, _timeout);
	}

	void OnRelease()
	{
		if(_vstate) _parent.DecVisibleState(_vstate);
		if(_hstate) _parent.RemoveTeamVisibleState(_hstate);
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Inchurtfromskill *>(f));
		filter_Inchurtfromskill * filter = (filter_Inchurtfromskill *)f;
		if(_pile_times < filter->_pile_limit)
		{
			_pile_times++;
			_ratio += (filter->_ratio - 1.0f);
			_pile_limit = filter->_pile_limit;
		}
		_timeout = filter->_timeout;
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(_hstate);
			_parent.InsertTeamVisibleState(_hstate, _timeout);
		}
		
	}
};

class filter_Incbecritrate: public timeout_filter	//�Լ��ܹ��������
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
				| FILTER_MASK_TRANSLATE_RECV_MSG | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _value;			//��Ч��ôι��������������?
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value ;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}

	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
		if(msg.skill_id)	
		{
			msg.crit_rate += _value;	
			if(msg.crit_rate > 100) msg.crit_rate = 100;
		}
	}

	filter_Incbecritrate(){}
public:
	DECLARE_SUBSTANCE(filter_Incbecritrate); 
	filter_Incbecritrate(object_interface  object, int period, int value,int mask)
				        :timeout_filter(object,period,FILTER_MASK|mask),_value(value)
	{
		_filter_id = FILTER_INCBECRITRATE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCBECRITRATE, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCBECRITRATE);
	}
};

class filter_Modifyspecskillpray: public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH			
	};

	int _skillid;
	int _times;
	float _ratio;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _skillid << _times << _ratio;
		
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _skillid >> _times >> _ratio;

		return true;
	}

	filter_Modifyspecskillpray(){}
public:
	DECLARE_SUBSTANCE(filter_Modifyspecskillpray); 
	filter_Modifyspecskillpray(object_interface  object, int period, int times, int skillid, float ratio)
				        :timeout_filter(object,period,FILTER_MASK),_skillid(skillid),_times(times > 0 ? times : 1),_ratio(ratio > 0 ? ratio : 0)
	{
		_filter_id = FILTER_MODIFYSPECSKILLPRAY;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_MODIFYSPECSKILLPRAY, _timeout);
		_parent.IncVisibleState(VSTATE_MODIFYSPECSKILLPRAY);
		_parent.GetSkillWrapper().ModifyDynamicPray(_skillid,_ratio,_times);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_MODIFYSPECSKILLPRAY);
		_parent.DecVisibleState(VSTATE_MODIFYSPECSKILLPRAY);
		_parent.GetSkillWrapper().ModifyDynamicPray(_skillid,0,0);
	}
	
	void Heartbeat(int tick)
	{
		_is_deleted = _parent.GetSkillWrapper().GetDynamicPrayTimes(_skillid) == 0; // û�з���ֻ�ܲ�ѯ��
		timeout_filter::Heartbeat(tick);
	}

};

class filter_Incspecskilldamage: public timeout_filter, public multicond_stub
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH	| FILTER_MASK_TRANSLATE_SEND_MSG	
	};

	int _count;
	float _ratio;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		multicond_stub::Save(ar);
		ar << _count << _ratio;
		
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		multicond_stub::Load(ar);
		ar >> _count >> _ratio;

		return true;
	}

	filter_Incspecskilldamage(){}
public:
	DECLARE_SUBSTANCE(filter_Incspecskilldamage); 
	filter_Incspecskilldamage(object_interface  object, int period, int count, int skillid, float ratio)
				        :timeout_filter(object,period,FILTER_MASK),_count(count > 0 ? count : 1),_ratio(ratio+1.f)
	{
		_filter_id = FILTER_INCSPECSKILLDAMAGE;
		if(skillid) _conds.insert(skillid);
	}

    void Merge(filter *f) // �����¼������� for ��ħ����
	{
       	filter_Incspecskilldamage* nf = dynamic_cast<filter_Incspecskilldamage*>(f);
		ASSERT(nf);
		if(!_conds.empty() && !nf->_conds.empty())	MergeCond(nf->_conds);
		_timeout = nf->_timeout;
		_count = nf->_count;
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCSPECSKILLDAMAGE);
			_parent.InsertTeamVisibleState(HSTATE_INCSPECSKILLDAMAGE, _timeout);
		}
		
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCSPECSKILLDAMAGE, _timeout);
		_parent.IncVisibleState(VSTATE_INCSPECSKILLDAMAGE);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCSPECSKILLDAMAGE);
		_parent.DecVisibleState(VSTATE_INCSPECSKILLDAMAGE);
	}
	
	virtual void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
        if(_conds.empty() || CheckCond(msg.skill_id))
		{
			msg.physic_damage = int(msg.physic_damage*_ratio);
			msg.magic_damage[0] = int(msg.magic_damage[0]*_ratio);
			msg.magic_damage[1] = int(msg.magic_damage[1]*_ratio);
			msg.magic_damage[2] = int(msg.magic_damage[2]*_ratio);
			msg.magic_damage[3] = int(msg.magic_damage[3]*_ratio);
			msg.magic_damage[4] = int(msg.magic_damage[4]*_ratio);
			if(--_count <= 0) _is_deleted = true;
		}
	}

};

class filter_Iceshield2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	int _point;
	int _appoint;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		ar << _appoint;
		ar << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		ar >> _appoint;
		ar >> _counter;
		return true;
	}

	filter_Iceshield2(){}
public:
	DECLARE_SUBSTANCE(filter_Iceshield2); 
	filter_Iceshield2(object_interface  object,int period, int p, int ap, int r)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p), _appoint(ap),_counter(0)
	{
		_filter_id = FILTER_MAGICSHIELD;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_ICESHIELD);
		_parent.InsertTeamVisibleState(HSTATE_ICESHIELD2, _timeout);
		_parent.EnhanceMPGen(_point);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
		_parent.UpdateHPMPGen();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_ICESHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_ICESHIELD2);
		_parent.ImpairMPGen(_point);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.UpdateMagicData();
		_parent.UpdateHPMPGen();
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;

		if(tick>=_timeout)
		{
			_parent.ModifyAP(_appoint*_counter);
			_counter = 0;	
		}
		else if(_counter>=3)
		{
			_parent.ModifyAP(_appoint);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

};
class filter_Fireshield2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;
	int _point;
	int _appoint;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		ar << _appoint;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		ar >> _appoint;
		return true;
	}
	filter_Fireshield2(){}
public:
	DECLARE_SUBSTANCE(filter_Fireshield2); 
	filter_Fireshield2(object_interface  object,int period, int p, int ap, int r)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p), _appoint(ap)
	{
		_filter_id = FILTER_MAGICSHIELD;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_FIRESHIELD);
		_parent.InsertTeamVisibleState(HSTATE_FIRESHIELD2, _timeout);
		_parent.EnhanceCrit(_appoint);
		_parent.EnhanceHPGen(_point);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.UpdateMagicData();
		_parent.UpdateHPMPGen();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_FIRESHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_FIRESHIELD2);
		_parent.ImpairCrit(_appoint);
		_parent.ImpairHPGen(_point);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.UpdateMagicData();
		_parent.UpdateHPMPGen();
	}
};

class filter_Healshield : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE
	};

	float _amount;
	int  _hpgen;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _amount;
		ar << _hpgen;
		ar << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _amount;
		ar >> _hpgen;
		ar >> _counter;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg &msg , float damage_adjust)
	{
		float damage = dmg.physic_damage+dmg.magic_damage[0]+dmg.magic_damage[1]+dmg.magic_damage[2]+dmg.magic_damage[3]
					+dmg.magic_damage[4];
		damage *= damage_adjust*0.8;

		if(damage<_amount)
		{
			dmg.physic_damage *= 0.2;
			dmg.magic_damage[0] *= 0.2;
			dmg.magic_damage[1] *= 0.2;
			dmg.magic_damage[2] *= 0.2;
			dmg.magic_damage[3] *= 0.2;
			dmg.magic_damage[4] *= 0.2;
			_amount -= damage;
		}else if(damage>1)
		{
			float r = 1.0 - _amount/damage;
			dmg.physic_damage *= r;
			dmg.magic_damage[0] *= r;
			dmg.magic_damage[1] *= r;
			dmg.magic_damage[2] *= r;
			dmg.magic_damage[3] *= r;
			dmg.magic_damage[4] *= r;
			_amount = 0;
		}
		if(_amount<6)
			_is_deleted = true;
	}

	filter_Healshield(){}
public:
	DECLARE_SUBSTANCE(filter_Healshield); 
	filter_Healshield(object_interface  object,int period, int amount, int hpgen , int mask)
				        :timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_WINGSHIELD;
		_amount = amount;
		_hpgen = hpgen;
		_counter = 0;
	}

	void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.Heal(_hpgen);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_HEALSHIELD);
		_parent.InsertTeamVisibleState(HSTATE_HEALSHIELD, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_HEALSHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_HEALSHIELD);
	}
};

class filter_Incflyspeed : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _ratio;
	int _pile_times;
	int _pile_limit;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _pile_times;
		ar << _pile_limit;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _pile_times;
		ar >> _pile_limit;
		return true;
	}
	filter_Incflyspeed(){}
public:
	DECLARE_SUBSTANCE(filter_Incflyspeed)
	filter_Incflyspeed(object_interface object, int period, int mask, int ratio, int pile_limit)
			:timeout_filter(object,period,FILTER_MASK|mask), _ratio(ratio), _pile_times(1), _pile_limit(pile_limit)
	{
		_filter_id = FILTER_INCFLYSPEED;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INCFLYSPEED);
		_parent.InsertTeamVisibleState(HSTATE_INCFLYSPEED, _timeout);
		_parent.EnhanceScaleFlySpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
	void OnRelease()
	{
		_parent.ImpairScaleFlySpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		_parent.DecVisibleState(VSTATE_INCFLYSPEED);
		_parent.RemoveTeamVisibleState(HSTATE_INCFLYSPEED);
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incflyspeed*>(f));
		filter_Incflyspeed* nf = (filter_Incflyspeed*) f;
		if(_pile_times < nf->_pile_limit)
		{
			_pile_times++;
			_pile_limit = nf->_pile_limit;
			
			_parent.ImpairScaleFlySpeed(_ratio);
			_ratio += nf->_ratio;
			_parent.EnhanceScaleFlySpeed(_ratio);
			_parent.UpdateSpeedData();
			_parent.SendClientCurSpeed();
		}
		_timeout = nf->_timeout;
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_INCFLYSPEED);
			_parent.InsertTeamVisibleState(HSTATE_INCFLYSPEED, _timeout);
		}
		
	}
};

class filter_Incvigour : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT  | FILTER_MASK_REMOVE_ON_DEATH
	};
	
	int _vigour;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _vigour;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _vigour;
		return true;
	}


	filter_Incvigour(){}
public:
	DECLARE_SUBSTANCE(filter_Incvigour)
	filter_Incvigour(object_interface object, int period, int mask, int vigour)
			:timeout_filter(object,period,FILTER_MASK|mask),_vigour(vigour)
	{
		_filter_id = FILTER_INCVIGOUR;
	}
	void OnAttach()
	{
		_parent.IncVigour(_vigour);
		_parent.InsertTeamVisibleState(HSTATE_INCVIGOUR, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVigour(_vigour);
		_parent.RemoveTeamVisibleState(HSTATE_INCVIGOUR);
	}
};

class filter_Minecarprotect : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT  | FILTER_MASK_REMOVE_ON_DEATH
	};
	
	filter_Minecarprotect(){}
public:
	DECLARE_SUBSTANCE(filter_Minecarprotect)
	filter_Minecarprotect(object_interface object, int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_MINECARPROTECT;
	}
	void OnAttach()
	{
		_parent.IncImmuneMask(IMMUNEPHYSICAL|IMMUNEMETAL|IMMUNEWOOD|
				IMMUNEWATER|IMMUNEFIRE|IMMUNESOIL|IMMUNEALL);
		_parent.IncVisibleState(VSTATE_INVINCIBLE);
		_parent.InsertTeamVisibleState(HSTATE_INVINCIBLE, _timeout);
	}
	void OnRelease()
	{
		_parent.DecImmuneMask(IMMUNEPHYSICAL|IMMUNEMETAL|IMMUNEWOOD|
				IMMUNEWATER|IMMUNEFIRE|IMMUNESOIL|IMMUNEALL);
		_parent.DecVisibleState(VSTATE_INVINCIBLE);
		_parent.RemoveTeamVisibleState(HSTATE_INVINCIBLE);
	}
};

class filter_Incvigour2 : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT  | FILTER_MASK_SAVE_DB_DATA
	};
	
	int _vigour;
	int _crit_damage_reduce;

	virtual bool Save(archive & ar)
	{
		//���filter�����ߺ󱣴棬����ʱ
		//����_timeout
		int tmp = _timeout;
		_timeout += time(NULL);
		
		timeout_filter::Save(ar);
		ar << _vigour;
		ar << _crit_damage_reduce;
		
		//�ָ�_timeout
		_timeout = tmp;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _vigour;
		ar >> _crit_damage_reduce;

		//�ָ�_timeout
		_timeout -= time(NULL);
		if(_timeout <= 0) _timeout = 1;
		return true;
	}


	filter_Incvigour2(){}
public:
	DECLARE_SUBSTANCE(filter_Incvigour2)
	filter_Incvigour2(object_interface object, int period, int mask, int vigour, int cdr)
			:timeout_filter(object,period,FILTER_MASK|mask),_vigour(vigour),_crit_damage_reduce(cdr)
	{
		_filter_id = FILTER_INCVIGOUR2;
	}
	void OnAttach()
	{
		_parent.IncVigour(_vigour);
		_parent.EnhanceCritDamageReduce(_crit_damage_reduce);
		_parent.InsertTeamVisibleState(HSTATE_INCVIGOUR2, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVigour(_vigour);
		_parent.ImpairCritDamageReduce(_crit_damage_reduce);
		_parent.RemoveTeamVisibleState(HSTATE_INCVIGOUR2);
	}
};

class filter_Shortjump : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _radius;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _radius;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _radius;
		return true;
	}
	filter_Shortjump(){}
public:
	DECLARE_SUBSTANCE(filter_Shortjump)
	filter_Shortjump(object_interface object,int period, int radius, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _radius(radius)
	{
		_filter_id = FILTER_SHORTJUMP;
	}
	void OnAttach() {}
	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_timeout <= 0 && !_parent.IsDead())
		{
			_parent.ShortJump(_radius,true); 
		}
	}
};

class filter_Shortjump2 : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _distance;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _distance;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _distance;
		return true;
	}
	filter_Shortjump2(){}
public:
	DECLARE_SUBSTANCE(filter_Shortjump2)
	filter_Shortjump2(object_interface object,int period, int distance ,int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _distance(distance)
	{
		_filter_id = FILTER_SHORTJUMP2;
	}
	void OnAttach() {}
	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_timeout <= 0 && !_parent.IsDead())
		{
			_parent.ShortJump(_distance,false);
		}
	}
};

class filter_Movepunish : public timeout_filter, public delayhurt_stub
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _damage;
	A3DVECTOR _pos;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		delayhurt_stub::Save(ar);
		ar << _damage;
		ar << _pos;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		delayhurt_stub::Load(ar);
		ar >> _damage;
		ar >> _pos;
		return true;
	}
	filter_Movepunish(){}
public:
	DECLARE_SUBSTANCE(filter_Movepunish)
	filter_Movepunish(object_interface object,int period, int damage, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _damage(damage)
	{
		_filter_id = FILTER_MOVEPUNISH;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_MOVEPUNISH);
		_parent.InsertTeamVisibleState(HSTATE_MOVEPUNISH, _timeout);
		_pos = _parent.GetPos();
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_MOVEPUNISH);
		_parent.RemoveTeamVisibleState(HSTATE_MOVEPUNISH);
	}
	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
	 	float dis = sqrt(_pos.squared_distance(_parent.GetPos()));
		if(dis > 1.f && dis < 50.f)
		{
			if(dis > 15.f) dis = 15.f; // �߻�����15��Ϊ����˺����?
			_parent.BeHurt(_performer, _pinfo, int(_damage*dis+0.1f), _invader, _mode);	
			_pos = _parent.GetPos();
			_parent.SendClientGfxEffect(STIME_GFX_MOVEPUNISH,1);
		}
	}
};

class filter_Standpunish : public timeout_filter, public delayhurt_stub
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _distance;
	int _damage;
	A3DVECTOR _pos;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		delayhurt_stub::Save(ar);
		ar << _distance;
		ar << _damage;
		ar << _pos;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		delayhurt_stub::Load(ar);
		ar >> _distance;
		ar >> _damage;
		ar >> _pos;
		return true;
	}
	filter_Standpunish(){}
public:
	DECLARE_SUBSTANCE(filter_Standpunish)
	filter_Standpunish(object_interface object,int period, int distance, int damage, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _distance(distance*distance), _damage(damage)
	{
		_filter_id = FILTER_STANDPUNISH;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_STANDPUNISH);
		_parent.InsertTeamVisibleState(HSTATE_STANDPUNISH, _timeout);
		_pos = _parent.GetPos();
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_STANDPUNISH);
		_parent.RemoveTeamVisibleState(HSTATE_STANDPUNISH);
	}
	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_pos.squared_distance(_parent.GetPos()) < _distance)
		{
			_parent.BeHurt(_performer, _pinfo, _damage, _invader, _mode);	
		}
		else
		{
			_pos = _parent.GetPos();
		}
	}
};

class filter_Standpunish2 : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _distance;
	int _skillid;
	int _skilllevel;
	A3DVECTOR _pos;
	XID _executor;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _distance;
		ar << _skillid;
		ar << _skilllevel;
		ar << _pos;
		ar << _executor;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _distance;
		ar >> _skillid;
		ar >> _skilllevel;
		ar >> _pos;
		ar >> _executor;
		return true;
	}
	filter_Standpunish2(){}
public:
	DECLARE_SUBSTANCE(filter_Standpunish2)
	filter_Standpunish2(object_interface object,int period, int distance, int skillid, int skilllevel, XID executor)
			:timeout_filter(object,period,FILTER_MASK), _distance(distance*distance), _skillid(skillid), _skilllevel(skilllevel)
	{
		_executor = executor;
		_filter_id = FILTER_STANDPUNISH2;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_STANDPUNISH2);
		_parent.InsertTeamVisibleState(HSTATE_STANDPUNISH2, _timeout);
		_pos = _parent.GetPos();
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_STANDPUNISH2);
		_parent.RemoveTeamVisibleState(HSTATE_STANDPUNISH2);
	}
	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_timeout <= 0 && !_parent.IsDead())
		{
			if(_pos.squared_distance(_parent.GetPos()) < _distance)
			{
				_parent.RequestPunish(_executor,_skillid,_skilllevel);
			}
		}
	}
};

class filter_Chantshield : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _amount;
	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _amount;
		ar << _ratio;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _amount;
		ar >> _ratio;
		return true;
	}
	filter_Chantshield(){}
public:
	DECLARE_SUBSTANCE(filter_Chantshield)
	filter_Chantshield(object_interface object,int period, int amount, int ratio, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _amount(amount), _ratio(ratio*0.01f)
	{
		_filter_id = FILTER_CHANTSHIELD;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_CHANTSHIELD);
		_parent.InsertTeamVisibleState(HSTATE_CHANTSHIELD, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_CHANTSHIELD);
		_parent.RemoveTeamVisibleState(HSTATE_CHANTSHIELD);
	}
	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(_amount < 0) return;
		
		float ratio = 1.f - _ratio;
		
		if(_amount)
		{
			int total_reduce = int((dmg.physic_damage + dmg.magic_damage[0] + dmg.magic_damage[1] 
					+ dmg.magic_damage[2] + dmg.magic_damage[3] + dmg.magic_damage[4]) * damage_adjust * _ratio);
			
			if(_amount < total_reduce)
			{
				_amount = -1;
				_is_deleted = true;
				ratio = 1.f - _ratio*_amount/total_reduce;
			}
			else if(_amount == total_reduce)
			{
				_amount = -1;
				_is_deleted = true;
			}
			else
				_amount -= total_reduce;

		}
		
		dmg.physic_damage = int(dmg.physic_damage * ratio);
		dmg.magic_damage[0] = int(dmg.magic_damage[0] * ratio);
		dmg.magic_damage[1] = int(dmg.magic_damage[1] * ratio);
		dmg.magic_damage[2] = int(dmg.magic_damage[2] * ratio);
		dmg.magic_damage[3] = int(dmg.magic_damage[3] * ratio);
		dmg.magic_damage[4] = int(dmg.magic_damage[4] * ratio);
	}
};

class filter_Intervalpalsy : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _runtime;
	int _interval;
	int _palsytime;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _runtime;
		ar << _interval;
		ar << _palsytime;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _runtime;
		ar >> _interval;
		ar >> _palsytime;
		return true;
	}
	filter_Intervalpalsy(){}
public:
	DECLARE_SUBSTANCE(filter_Intervalpalsy)
	filter_Intervalpalsy(object_interface object, int period, int interval, int palsytime, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _runtime(0), _interval(interval?interval/1000:1), _palsytime(palsytime/1000)
	{
		_filter_id = FILTER_INTERVALPALSY;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INTERVALPALSY);
		_parent.InsertTeamVisibleState(HSTATE_INTERVALPALSY, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INTERVALPALSY);
		_parent.RemoveTeamVisibleState(HSTATE_INTERVALPALSY);
	}
	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(++_runtime % _interval == 0)
		{
			if(!_parent.IsPalsyImmune())
				_parent.AddFilter(new filter_Palsy(_parent, _palsytime, filter::FILTER_MASK_DEBUFF));	
		}
	}
};

class filter_Internalinjury : public timeout_filter, public delayhurt_stub
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	float _hplimit;
	int _punish;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		delayhurt_stub::Save(ar);
		ar << _hplimit;
		ar << _punish;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		delayhurt_stub::Load(ar);
		ar >> _hplimit;
		ar >> _punish;
		return true;
	}
	filter_Internalinjury(){}
public:
	DECLARE_SUBSTANCE(filter_Internalinjury)
	filter_Internalinjury(object_interface object,int period, float hplimit, int punish, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _hplimit(hplimit/100.f), _punish(punish)
	{
		_filter_id = FILTER_INTERNALINJURY;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INTERNALINJURY);
		_parent.InsertTeamVisibleState(HSTATE_INTERNALINJURY, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_INTERNALINJURY);
		_parent.RemoveTeamVisibleState(HSTATE_INTERNALINJURY);
	}
	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_parent.GetHpScale() < _hplimit)
		{
			_parent.BeHurt(_performer, _pinfo, _punish, _invader, _mode);
			_parent.SendClientGfxEffect(STIME_GFX_INTERNALINJURY,1);
			_is_deleted = true;
		}
	}
};

class filter_Atkdamagereduce : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_RECV_MSG
	};

	float _reduceradio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _reduceradio;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _reduceradio;
		return true;
	}
	filter_Atkdamagereduce(){}
public:
	DECLARE_SUBSTANCE(filter_Atkdamagereduce)
	filter_Atkdamagereduce(object_interface object, int period, float reduceradio, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _reduceradio(1.f-reduceradio/100.f)
	{
		_filter_id = FILTER_ATKDAMAGEREDUCE;
	}
	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_ATKDAMAGEREDUCE);
		_parent.InsertTeamVisibleState(HSTATE_ATKDAMAGEREDUCE, _timeout);
	}
	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_ATKDAMAGEREDUCE);
		_parent.RemoveTeamVisibleState(HSTATE_ATKDAMAGEREDUCE);
	}
	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
		if(!msg.skill_id)
		{
			msg.physic_damage = int(msg.physic_damage * _reduceradio);
			for(int n = 0 ; n < MAGIC_CLASS; ++n )
				msg.magic_damage[n] = int(msg.magic_damage[n] * _reduceradio);
		}
	}
};

class filter_Deathresetcd : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_BEFORE_DEATH
	};

	XID _performer;
	int _skillid;
	int _msec;
	int _distance;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _performer;
		ar << _skillid;
		ar << _msec;
		ar << _distance;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _performer;
		ar >> _skillid;
		ar >> _msec;
		ar >> _distance;
		return true;
	}
	filter_Deathresetcd(){}
public:
	DECLARE_SUBSTANCE(filter_Deathresetcd)
	filter_Deathresetcd(object_interface object,int period, const XID & performer, int skillid, int msec, int distance)
			:timeout_filter(object,period,FILTER_MASK),_performer(performer), _skillid(skillid), _msec(msec), _distance(distance*distance)
	{
		_filter_id = FILTER_DEATHRESETCD;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_DEATHRESETCD);
		_parent.InsertTeamVisibleState(HSTATE_DEATHRESETCD, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_DEATHRESETCD);
		_parent.RemoveTeamVisibleState(HSTATE_DEATHRESETCD);
	}
	void BeforeDeath(const XID & attacker, char attacker_mode)
	{
		A3DVECTOR pos;
		float body_size;
		if(_parent.QueryObject(_performer,pos,body_size) == 1 && pos.squared_distance(_parent.GetPos()) <= _distance )
			_parent.SendReduceCDMsg(_performer,_skillid+COOLINGID_BEGIN,_msec);
		_is_deleted = true;
	}
};

class filter_Appendenchant : public timeout_filter, public multicond_stub
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSLATE_SEND_ENCHANT
	};

	int _skillid;
	int _skilllevel;
	int _count;
	bool _activeflag;	
	XID	_target;
	float _range;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		multicond_stub::Save(ar);		

		ar << _skillid;
		ar << _skilllevel;
		ar << _count;
		ar << _activeflag;
		ar << _target;
		ar << _range;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		multicond_stub::Load(ar);

		ar >> _skillid;
		ar >> _skilllevel;
		ar >> _count;
		ar >> _activeflag;
		ar >> _target;
		ar >> _range;
		return true;
	}
	filter_Appendenchant(){}
public:
	DECLARE_SUBSTANCE(filter_Appendenchant)
	filter_Appendenchant(object_interface object,int period, int condskillid, int skillid, int skilllevel, int count)
			:timeout_filter(object,period,FILTER_MASK), _skillid(skillid), _skilllevel(skilllevel), _count(count), _activeflag(false), _target(-1,-1), _range(0.f)
	{
		_filter_id = FILTER_APPENDENCHANT;
		_conds.insert(condskillid);
	}
    void Merge(filter *f) // �����¼������� for ��ħ����
	{
       	filter_Appendenchant* nf = dynamic_cast<filter_Appendenchant*>(f);
		ASSERT(nf);
		MergeCond(nf->_conds);	
		_timeout = nf->_timeout;
		_count = nf->_count;
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_APPENDENCHANT);
			_parent.InsertTeamVisibleState(HSTATE_APPENDENCHANT, _timeout);
		}
		
	}
	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_APPENDENCHANT);
		_parent.InsertTeamVisibleState(HSTATE_APPENDENCHANT, _timeout);
	}
	void OnRelease()
	{
		OnActive();
		//_parent.DecVisibleState(VSTATE_APPENDENCHANT);
		_parent.RemoveTeamVisibleState(HSTATE_APPENDENCHANT);
	}
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(CheckCond(msg.skill_id))
		{
			_target = target;
			_range = msg.attack_range;
			_activeflag = true;	
		}
	}
	void TranslateSendEnchant(const XID & target,enchant_msg & msg)
	{
		if(CheckCond(msg.skill))
		{
			_target = target;
			_range = msg.attack_range;
			_activeflag = true;	
		}
	}
	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		OnActive();
	}
	void OnActive()
	{
		if(_activeflag)
		{
			enchant_msg	msg;
			memset(&msg,0,sizeof(msg));
			msg.skill = _skillid;
			msg.skill_level = _skilllevel;
			msg.attack_range = _range + 0.5; 
			_parent.Enchant(_target, msg);
			
			if(--_count <= 0) _is_deleted = true;	
		}
		_activeflag = false;
	}
};

class filter_Appenddamage : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	int _damage;
	int _dmgtype;
	int _count;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damage;
		ar << _dmgtype;
		ar << _count;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damage;
		ar >> _dmgtype;
		ar >> _count;
		return true;
	}
	filter_Appenddamage(){}
public:
	DECLARE_SUBSTANCE(filter_Appenddamage)
	filter_Appenddamage(object_interface object,int period, int damage, int dmgtype, int count)
			:timeout_filter(object,period,FILTER_MASK), _damage(damage), _dmgtype(dmgtype), _count(count)
	{
		_filter_id = FILTER_APPENDDAMAGE;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_APPENDDAMAGE);
		_parent.InsertTeamVisibleState(HSTATE_APPENDDAMAGE, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_APPENDDAMAGE);
		_parent.RemoveTeamVisibleState(HSTATE_APPENDDAMAGE);
	}
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(0 == msg.skill_id) // ��ͨ����
		{
			if(_dmgtype>0 && _dmgtype <= MAGIC_CLASS)
				msg.magic_damage[_dmgtype-1] += _damage;
			else
				msg.physic_damage += _damage;

			if(--_count <= 0) _is_deleted = true;	
		}
	}
};

class filter_Cooldownaward : public timeout_filter, public multicond_stub
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSLATE_SEND_ENCHANT
	};

	int _skillid;
	int _count;
	bool _activeflag;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		multicond_stub::Save(ar);
		ar << _skillid;
		ar << _count;
		ar << _activeflag;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		multicond_stub::Load(ar);
		ar >> _skillid;
		ar >> _count;
		ar >> _activeflag;
		return true;
	}
	filter_Cooldownaward(){}
public:
	DECLARE_SUBSTANCE(filter_Cooldownaward)
	filter_Cooldownaward(object_interface object,int period, int skillid, int count, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _skillid(0), _count(count?count:0xFFFF), _activeflag(false)
	{
		_filter_id = FILTER_COOLDOWNAWARD;
		_conds.insert(skillid);
	}
	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_COOLDOWNAWARD);
		_parent.InsertTeamVisibleState(HSTATE_COOLDOWNAWARD, _timeout);
	}
	void OnRelease()
	{
		OnActive();
		//_parent.DecVisibleState(VSTATE_COOLDOWNAWARD);
		_parent.RemoveTeamVisibleState(HSTATE_COOLDOWNAWARD);
	}
    void Merge(filter *f) // �����¼������� for ��ħ����
	{
       	filter_Cooldownaward* nf = dynamic_cast<filter_Cooldownaward*>(f);
		ASSERT(nf);
		MergeCond(nf->_conds);	
		_timeout = nf->_timeout;
		_count = nf->_count;
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_COOLDOWNAWARD);
			_parent.InsertTeamVisibleState(HSTATE_COOLDOWNAWARD, _timeout);
		}
	}
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(CheckCond(msg.skill_id))
		{
			_skillid = msg.skill_id;
			_activeflag = true;
		}
	}
	void TranslateSendEnchant(const XID & target,enchant_msg & msg)
	{
		if(CheckCond(msg.skill))
		{
			_skillid = msg.skill;
			_activeflag = true;
		}
	}
	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		OnActive();
	}
	void OnActive()
	{
		if(_activeflag)
		{
			_parent.ResetCoolDown(_skillid+COOLINGID_BEGIN);
			if(--_count <= 0) _is_deleted = true;	
		}
		_activeflag = false;
	}
};

class filter_Huntersoul : public timeout_filter, public delayhurt_stub
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG // | FILTER_MASK_TRANSLATE_SEND_ENCHANT
	};

	int _damage;
	int _dizzytime;
    XID _executor;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		delayhurt_stub::Save(ar);
		ar << _damage;
		ar << _dizzytime;
        ar << _executor;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		delayhurt_stub::Load(ar);
		ar >> _damage;
		ar >> _dizzytime;
		ar >> _executor;
		return true;
	}
	filter_Huntersoul(){}
public:
	DECLARE_SUBSTANCE(filter_Huntersoul)
	filter_Huntersoul(object_interface object,int period, int damage, int dizzytime, int mask, XID executor)
			:timeout_filter(object,period,FILTER_MASK|mask), _damage(damage), _dizzytime(dizzytime/1000)
	{
		_executor = executor;
		_filter_id = FILTER_HUNTERSOUL;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_HUNTERSOUL);
		_parent.InsertTeamVisibleState(HSTATE_HUNTERSOUL, _timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_HUNTERSOUL);
		_parent.RemoveTeamVisibleState(HSTATE_HUNTERSOUL);
	}
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(msg.skill_id)
		{
			const Skill * sk = Skill::GetStub(msg.skill_id);
			if(!sk || sk->IsElfSkill()) return;
		}
		
		if(target != _parent.GetSelfID() && 
		  (msg.physic_damage || msg.magic_damage[0] || msg.magic_damage[1] || msg.magic_damage[2] || msg.magic_damage[3] || msg.magic_damage[4]))
			_is_deleted = true;
	}
	void TranslateSendEnchant(const XID & target,enchant_msg & msg)
	{
//		if(target != _parent.GetSelfID())
//			_is_deleted = true;
	}
	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_timeout <= 0 && !_parent.IsDead())
		{
			if(!(_parent.GetImmuneMask()&(IMMUNEDIZZY|IMMUNEALL)))
			{
				_parent.AddFilter(new filter_Dizzy(_parent,_dizzytime,filter::FILTER_MASK_DEBUFF|filter::FILTER_MASK_TRANSFERABLE_DEBUFF));
			}
			
			_parent.BeHurt(_performer, _pinfo, _damage, _invader, _mode);	
			_parent.SendClientGfxEffect(STIME_GFX_HUNTERSOUL,1);
		}
	}
};

class filter_Changeselfaggro : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	XID _target;
	int _aggro;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _target;
		ar << _aggro;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _target;
		ar >> _aggro;
		return true;
	}
	filter_Changeselfaggro(){}
public:
	DECLARE_SUBSTANCE(filter_Changeselfaggro)
	filter_Changeselfaggro(object_interface object,int period,const XID& target, int aggro)
			:timeout_filter(object,period,FILTER_MASK), _target(target), _aggro(aggro)
	{
		_filter_id = FILTER_CHANGESELFAGGRO;
	}
	void OnAttach()
	{
		_parent.AddAggro(_target,_aggro);
	}
	void OnRelease()
	{
	    _parent.AddAggro(_target,-_aggro);
	}
};

class filter_Neverdead : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT  | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_BEFORE_DEATH
	};

	filter_Neverdead(){}
public:
	DECLARE_SUBSTANCE(filter_Neverdead);
	filter_Neverdead(object_interface parent, int period, int mask)
		:timeout_filter(parent,period > 0 ? period : 0x8FFFFFFF,FILTER_MASK|mask)	
	{   
		_filter_id = FILTER_NEVERDEAD;
	}

	virtual void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REBIRTH, _timeout);
	}
	
	virtual void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REBIRTH);
	}

	virtual void BeforeDeath(const XID & attacker, char attacker_mode)
	{
		_parent.Heal(1);
	}
};

class filter_Changemodel : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _vtid;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _vtid;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _vtid;
		return true;
	}
	filter_Changemodel(){}
public:
	DECLARE_SUBSTANCE(filter_Changemodel)
	filter_Changemodel(object_interface object,int period, int vtid)
			:timeout_filter(object,period,FILTER_MASK), _vtid(vtid)
	{
		_filter_id = FILTER_CHANGEMODEL;
	}
    void Merge(filter *f)
    {
        filter_Changemodel* nf = dynamic_cast<filter_Changemodel*>(f);
		ASSERT(nf);

		_parent.ChangeVisibleTypeId(nf->_vtid);
		_timeout = GetTimeOut(nf);
	}
	void OnAttach()
	{
		_vtid =	_parent.ChangeVisibleTypeId(_vtid);
		if(_vtid < 0) _is_deleted = true;			
	}
	void OnRelease()
	{
		if(_vtid > 0) _parent.ChangeVisibleTypeId(_vtid);
	}
};

class filter_Screeneffect : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _eid;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _eid;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _eid;
		return true;
	}
	filter_Screeneffect(){}
public:
	DECLARE_SUBSTANCE(filter_Screeneffect)
	filter_Screeneffect(object_interface object,int period, int eid, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _eid(eid)
	{
		_filter_id = FILTER_SCREENEFFECT;
	}
	void OnAttach()
	{
		_parent.SendClientScreenEffect(_eid,1);
	}
	void OnRelease()
	{
		_parent.SendClientScreenEffect(_eid,0);
	}
};

class filter_Shadowform : public timeout_filter
{
protected:
    enum 
    {
        FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE
    };

    int _attack_speed;
    float _ratio;

    virtual bool Save(archive & ar)
    {
        timeout_filter::Save(ar);
        ar << _attack_speed;
        ar << _ratio;
        return true;
    }

    virtual bool Load(archive & ar)
    {
        timeout_filter::Load(ar);
        ar >> _attack_speed;
        ar >> _ratio;
        return true;
    }
    filter_Shadowform(){}
public:
    DECLARE_SUBSTANCE(filter_Shadowform); 
    filter_Shadowform(object_interface object, int period, int attack_speed, float ratio)
        :timeout_filter(object, period, FILTER_MASK), _attack_speed(attack_speed), _ratio(1.f-ratio)
    {
        _filter_id = FILTER_SHADOWFORM;
    }
    
    void OnAttach()
    {
        _parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
        _parent.LockEquipment(true);
        _parent.ChangeShape(1|(FORM_CLASS<<6));
        _parent.InsertTeamVisibleState(HSTATE_SHADOWFORM, _timeout);		
        _parent.EnhanceScaleAttackSpeed(_attack_speed);
        _parent.UpdateAttackData();
        _parent.SendClientAttackData();
    }

    void OnRelease()
    {
        _parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
        _parent.LockEquipment(false);
        _parent.ChangeShape(0);
        _parent.RemoveTeamVisibleState(HSTATE_SHADOWFORM);	
        _parent.ImpairScaleAttackSpeed(_attack_speed);
        _parent.UpdateAttackData();
        _parent.SendClientAttackData();
    }
    
	void AdjustDamage(damage_entry& dmg,const XID& attacker, const attack_msg& msg, float damage_adjust)
    {
		if(IS_RANGE_WEAPON(msg.weapon_class) && _ratio > 0)
		{
			dmg.physic_damage *= _ratio;
			dmg.magic_damage[0] *= _ratio;
			dmg.magic_damage[1] *= _ratio;
			dmg.magic_damage[2] *= _ratio;
			dmg.magic_damage[3] *= _ratio;
			dmg.magic_damage[4] *= _ratio;
		}
	}
};

class filter_Fairyform : public timeout_filter
{
protected:
    enum 
    {
        FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT
    };

    int _speed;
    int _defense;

    virtual bool Save(archive & ar)
    {
        timeout_filter::Save(ar);
        ar << _speed;
        ar << _defense;
        return true;
    }

    virtual bool Load(archive & ar)
    {
        timeout_filter::Load(ar);
        ar >> _speed;
        ar >> _defense;
        return true;
    }
    filter_Fairyform(){}
public:
    DECLARE_SUBSTANCE(filter_Fairyform); 
    filter_Fairyform(object_interface object, int period, int speed, int defense)
        :timeout_filter(object, period, FILTER_MASK), _speed(speed), _defense(defense)
        {
            _filter_id = FILTER_FAIRYFORM;
        }

    void OnAttach()
    {
        _parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
        _parent.LockEquipment(true);
        _parent.ChangeShape(1|(FORM_CLASS<<6));
        _parent.InsertTeamVisibleState(HSTATE_FAIRYFORM, _timeout);
        _parent.EnhanceSpeed(_speed);
        _parent.UpdateSpeedData();
        _parent.SendClientCurSpeed();
        _parent.EnhanceScaleDefense(_defense);
        _parent.UpdateDefenseData();
        _parent.SendClientDefenseData();
    }

    void OnRelease()
    {
        _parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
        _parent.LockEquipment(false);
        _parent.ChangeShape(0);
        _parent.RemoveTeamVisibleState(HSTATE_FAIRYFORM);	
        _parent.ImpairSpeed(_speed);
        _parent.UpdateSpeedData();
        _parent.SendClientCurSpeed();
        _parent.ImpairScaleDefense(_defense);
        _parent.UpdateDefenseData();
        _parent.SendClientDefenseData();
    }
};

class filter_Addfrosteffect: public filter_Wounded
{
    enum
    {
        FILTER_MASK = FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
            | FILTER_MASK_TRANSFERABLE_DEBUFF | FILTER_MASK_MERGE,
        MAX_STACK = 5,
    };

    int _stacks;
    int _dmg_per_stack;

    virtual bool Save(archive & ar)
    {
        filter_Wounded::Save(ar);
        ar << _stacks;
        ar << _dmg_per_stack;
        return true;
    }

    virtual bool Load(archive & ar)
    {
        filter_Wounded::Load(ar);
        ar >> _stacks;
        ar >> _dmg_per_stack;
        return true;
    }

    filter_Addfrosteffect() {}
public:
    DECLARE_SUBSTANCE(filter_Addfrosteffect);
    filter_Addfrosteffect(object_interface object, int period, int mask, int damage)
        :filter_Wounded(object, period, damage, FILTER_MASK | mask), _stacks(1), _dmg_per_stack(damage)
        {
            _filter_id = FILTER_ADDFROSTEFFECT;	
			_icon = HSTATE_ADDFROSTEFFECT;
        }

    void Merge(filter *f)
    {
        ASSERT(dynamic_cast<filter_Addfrosteffect*>(f));
        filter_Addfrosteffect* nf = (filter_Addfrosteffect*)f;

		if(nf->_timeout)
		{
			++_stacks;
			if(_stacks > MAX_STACK) _stacks = MAX_STACK;

			int total_dmg = nf->_dmg_per_stack * _stacks;
			_timeout = GetTimeOut(nf);
			_damage = total_dmg / _timeout;
			if(_damage < 1) _damage = 1;

			_parent.ModifyTeamVisibleState(HSTATE_ADDFROSTEFFECT, _stacks, _timeout);
		}
    }

    int OnQuery(int index)
    {
        if (index == FILTER_QUERY_LEVEL) return _stacks;
        if (index == FILTER_QUERY_DAMAGE) return (_damage * _timeout);
        return 0;
    }

    void OnAttach()
    {
        _parent.InsertTeamVisibleState(HSTATE_ADDFROSTEFFECT, _stacks, _timeout);
    }

    void OnRelease()
    {
        _parent.RemoveTeamVisibleState(HSTATE_ADDFROSTEFFECT);
    }
};

class filter_Incspecskillcrit: public timeout_filter, public multicond_stub
{
protected:
    enum 
    {
        FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH	| FILTER_MASK_TRANSLATE_SEND_MSG	
            | FILTER_MASK_NOSAVE
    };

    int _count;
    int _ratio;

    virtual bool Save(archive & ar)
    {
        timeout_filter::Save(ar);
		multicond_stub::Save(ar);
        ar << _count << _ratio;

        return true;
    }

    virtual bool Load(archive & ar)
    {
        timeout_filter::Load(ar);
		multicond_stub::Load(ar);
        ar >> _count >> _ratio;

        return true;
    }

    filter_Incspecskillcrit(){}
public:
    DECLARE_SUBSTANCE(filter_Incspecskillcrit); 
    filter_Incspecskillcrit(object_interface  object, int period, int count, int skillid, int ratio)
        :timeout_filter(object,period,FILTER_MASK),_count(count > 0 ? count : 1),_ratio(ratio)
        {
            _filter_id = FILTER_INCSPECSKILLCRIT;
			if(skillid) _conds.insert(skillid);
        }

    void Merge(filter *f) // �����¼������� for ��ħ����
	{
       	filter_Incspecskillcrit* nf = dynamic_cast<filter_Incspecskillcrit*>(f);
		ASSERT(nf);
		if(!_conds.empty() && !nf->_conds.empty())	MergeCond(nf->_conds);
		_timeout = nf->_timeout;
		_count = nf->_count;
	}

    void OnAttach()
    {
        //_parent.InsertTeamVisibleState(HSTATE_INCSPECSKILLDAMAGE);
        //_parent.IncVisibleState(VSTATE_INCSPECSKILLDAMAGE);
    }

    void OnRelease()
    {
        //_parent.RemoveTeamVisibleState(HSTATE_INCSPECSKILLDAMAGE);
        //_parent.DecVisibleState(VSTATE_INCSPECSKILLDAMAGE);
    }

    virtual void TranslateSendAttack(const XID& target, attack_msg& msg)
    {
        if(_conds.empty() || CheckCond(msg.skill_id))
        {
			msg.crit_rate = msg.crit_rate + _ratio;
			if(msg.crit_rate > 100) msg.crit_rate = 100;
			if(--_count <= 0) _is_deleted = true;
        }
    }
};

class filter_Moongod: public timeout_filter
{
protected:
    enum 
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH |  FILTER_MASK_ADJUST_HEAL | FILTER_MASK_ADJUST_DAMAGE
            | FILTER_MASK_NOSAVE
    };

    float _dmg_ratio;
    float _hp_ratio;

    virtual bool Save(archive & ar)
    {
        timeout_filter::Save(ar);
        ar << _dmg_ratio << _hp_ratio;
        return true;
    }

    virtual bool Load(archive & ar)
    {
        timeout_filter::Load(ar);
        ar >> _dmg_ratio >> _hp_ratio;
        return true;
    }

    filter_Moongod(){}
public:
    DECLARE_SUBSTANCE(filter_Moongod); 
    filter_Moongod(object_interface object, int period, float dmg_ratio, float hp_ratio)
        :timeout_filter(object, period, FILTER_MASK), _dmg_ratio(1.0 - dmg_ratio), _hp_ratio(hp_ratio)
        {
            _filter_id = FILTER_MOONGOD;
        }

    void OnAttach()
    {
        _parent.InsertTeamVisibleState(HSTATE_MOONGOD, _timeout);
        _parent.Heal( (int)(_parent.GetExtendProp().max_hp * _hp_ratio) );
        _parent.IncImmuneMask(IMMUNEALL);
    }

    void OnRelease()
    {
        _parent.RemoveTeamVisibleState(HSTATE_MOONGOD);
        _parent.DecImmuneMask(IMMUNEALL);
    }

    void AdjustDamage(damage_entry& dmg,const XID& attacker, const attack_msg& msg, float damage_adjust)
    {
        dmg.physic_damage *= _dmg_ratio;
        dmg.magic_damage[0] *= _dmg_ratio;
        dmg.magic_damage[1] *= _dmg_ratio;
        dmg.magic_damage[2] *= _dmg_ratio;
        dmg.magic_damage[3] *= _dmg_ratio;
        dmg.magic_damage[4] *= _dmg_ratio;
    }

    void AdjustHeal(int& heal,char heal_type)
    {
        heal = 0;
    }
};

class filter_Delayskilleffect: public timeout_filter
{
protected:
    enum
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH
    };

    int _skillid;
    int _skilllevel;
    XID _executor;

    virtual bool Save(archive & ar)
    {
        timeout_filter::Save(ar);
        ar << _skillid;
        ar << _skilllevel;
        ar << _executor;
        return true;
    }
    virtual bool Load(archive & ar)
    {
        timeout_filter::Load(ar);
        ar >> _skillid;
        ar >> _skilllevel;
        ar >> _executor;
        return true;
    }

    filter_Delayskilleffect(){}
public:
    DECLARE_SUBSTANCE(filter_Delayskilleffect);
    filter_Delayskilleffect(object_interface object, int period, int filtermask, int skillid, int skilllevel, XID executor)
        :timeout_filter(object, period, FILTER_MASK | filtermask), _skillid(skillid), _skilllevel(skilllevel)
        {
            _executor = executor;
            _filter_id = FILTER_DELAYSKILLEFFECT;
        }
    void OnAttach()
    {
        //_parent.IncVisibleState(VSTATE_DELAYSKILLEFFECT);
        //_parent.InsertTeamVisibleState(HSTATE_DELAYSKILLEFFECT);
    }
    void OnRelease()
    {
        //_parent.DecVisibleState(VSTATE_DELAYSKILLEFFECT);
        //_parent.RemoveTeamVisibleState(HSTATE_DELAYSKILLEFFECT);
    }
    virtual void Heartbeat(int tick)
    {
        timeout_filter::Heartbeat(tick);
        if (_timeout <= 0 && !_parent.IsDead())
        {
            _parent.RequestPunish(_executor, _skillid, _skilllevel);
        }
    }
};


class filter_Enhanceskilldamage3: public timeout_filter//���Ӽ��ܶ�npc���˺�
{
protected:
    enum 
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE 
    };

    int _inc;

    virtual bool Save(archive & ar)
    {
        timeout_filter::Save(ar);
        ar << _inc;
        return true;
    }

    virtual bool Load(archive & ar)
    {
        timeout_filter::Load(ar);
        ar >> _inc;
        return true;
    }

    filter_Enhanceskilldamage3(){}
public:
    DECLARE_SUBSTANCE(filter_Enhanceskilldamage3); 
    filter_Enhanceskilldamage3(object_interface object, int period, int inc)
        :timeout_filter(object,period,FILTER_MASK), _inc(inc)
        {
            _filter_id = FILTER_ENHANCESKILLDAMAGE3;
        }

    void OnAttach()
    {
        _parent.InsertTeamVisibleState(HSTATE_ENHANCESKILLDAMAGE3, _timeout);
        _parent.EnhanceSkillDamage(_inc);
    }

    void OnRelease()
    {
        _parent.RemoveTeamVisibleState(HSTATE_ENHANCESKILLDAMAGE3);
        _parent.ImpairSkillDamage(_inc);
    }
};

class filter_Critdamagereduce: public timeout_filter//�����˺�����
{
protected:
    enum 
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE 
    };

    int _crit_damage_reduce;

    virtual bool Save(archive & ar)
    {
        timeout_filter::Save(ar);
        ar << _crit_damage_reduce;
        return true;
    }

    virtual bool Load(archive & ar)
    {
        timeout_filter::Load(ar);
        ar >> _crit_damage_reduce;
        return true;
    }

    filter_Critdamagereduce(){}
public:
    DECLARE_SUBSTANCE(filter_Critdamagereduce); 
    filter_Critdamagereduce(object_interface object, int period, int cdr)
        :timeout_filter(object,period,FILTER_MASK), _crit_damage_reduce(cdr)
        {
            _filter_id = FILTER_CRITDAMAGEREDUCE;
        }

    void OnAttach()
    {
        _parent.InsertTeamVisibleState(HSTATE_CRITDAMAGEREDUCE, _timeout);
		_parent.EnhanceCritDamageReduce(_crit_damage_reduce);
    }

    void OnRelease()
    {
        _parent.RemoveTeamVisibleState(HSTATE_CRITDAMAGEREDUCE);
		_parent.ImpairCritDamageReduce(_crit_damage_reduce);
    }
};


class filter_Incphysicaldamage : public timeout_filter
{
protected:
    enum
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
    };

    float _ratio;

    virtual bool Save(archive& ar)
    {
        timeout_filter::Save(ar);
        ar << _ratio;

        return true;
    }

    virtual bool Load(archive& ar)
    {
        timeout_filter::Load(ar);
        ar >> _ratio;

        return true;
    }

    filter_Incphysicaldamage() {}

public:
    DECLARE_SUBSTANCE(filter_Incphysicaldamage);
    filter_Incphysicaldamage(object_interface object, int period, float ratio, int mask) : timeout_filter(object, period, FILTER_MASK | mask)
    {
        _filter_id = FILTER_INCPHYSICALDAMAGE;
        _ratio = 1.0 + ratio / 100.0;
    }

    void TranslateSendAttack(const XID& target, attack_msg& msg)
    {
        if (IS_PHYSIC_ATTACK(msg.attack_attr))
        {
            msg.physic_damage = (int)(msg.physic_damage * _ratio);
        }
    }

    void OnAttach()
    {
        _parent.InsertTeamVisibleState(HSTATE_INCPHYSICALDAMAGE, _timeout);
    }

    void OnRelease()
    {
        _parent.RemoveTeamVisibleState(HSTATE_INCPHYSICALDAMAGE);
    }

};


class filter_Incmagicaldamage : public timeout_filter
{
protected:
    enum
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
    };

    float _ratio;

    virtual bool Save(archive& ar)
    {
        timeout_filter::Save(ar);
        ar << _ratio;

        return true;
    }

    virtual bool Load(archive& ar)
    {
        timeout_filter::Load(ar);
        ar >> _ratio;

        return true;
    }

    filter_Incmagicaldamage() {}

public:
    DECLARE_SUBSTANCE(filter_Incmagicaldamage);
    filter_Incmagicaldamage(object_interface object, int period, float ratio, int mask) : timeout_filter(object, period, FILTER_MASK | mask)
    {
        _filter_id = FILTER_INCMAGICALDAMAGE;
        _ratio = 1.0 + ratio / 100.0;
    }

    void TranslateSendAttack(const XID& target, attack_msg& msg)
    {
        if (!IS_PHYSIC_ATTACK(msg.attack_attr))
        {
            for (int i = 0; i < MAGIC_CLASS; ++i)
            {
                msg.magic_damage[i] = (int)(msg.magic_damage[i] * _ratio);
            }
        }
    }

    void OnAttach()
    {
        _parent.InsertTeamVisibleState(HSTATE_INCMAGICALDAMAGE, _timeout);
    }

    void OnRelease()
    {
        _parent.RemoveTeamVisibleState(HSTATE_INCMAGICALDAMAGE);
    }

};

class filter_Cooldownpunish : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _count;
	int _delay;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _count;
		ar << _delay;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _count;
		ar >> _delay;
		return true;
	}
	filter_Cooldownpunish(){}
public:
	DECLARE_SUBSTANCE(filter_Cooldownpunish)
	filter_Cooldownpunish(object_interface object, int period, int count, int delay ,int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _count(count), _delay(delay)
	{
		_filter_id = FILTER_COOLDOWNPUNISH;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_COOLDOWNPUNISH);
		_parent.InsertTeamVisibleState(HSTATE_COOLDOWNPUNISH, _timeout);
		(_parent.GetSkillWrapper()).IncCDAdjust(_delay);
		(_parent.GetSkillWrapper()).SetCDAdjustCount(_count);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_COOLDOWNPUNISH);
		_parent.RemoveTeamVisibleState(HSTATE_COOLDOWNPUNISH);
		(_parent.GetSkillWrapper()).DecCDAdjust(_delay);
	}
	void Heartbeat(int tick)
	{
		if((_parent.GetSkillWrapper()).GetCDAdjustCount() <= 0)
			_is_deleted = true;
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Anticlearbuf : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _count;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _count;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _count;
		return true;
	}
	filter_Anticlearbuf(){}
public:
	DECLARE_SUBSTANCE(filter_Anticlearbuf)
	filter_Anticlearbuf(object_interface object, int period, int count, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _count(count)
	{
		_filter_id = FILTER_ANTICLEARBUF;
	}
	void  OnModify(int ctrlname,void * ctrlval,unsigned int ctrllen) 
	{
		if(ctrlname==FMID_DEC_ANTICLEAR)
		{
			if(--_count <= 0) _is_deleted = true;
		}
	}
	void OnAttach()
	{
//		_parent.IncVisibleState(VSTATE_ANTICLEARBUF);
		_parent.InsertTeamVisibleState(HSTATE_ANTICLEARBUF, _timeout);
	}
	void OnRelease()
	{
//		_parent.DecVisibleState(VSTATE_ANTICLEARBUF);
		_parent.RemoveTeamVisibleState(HSTATE_ANTICLEARBUF);
	}
	void Heartbeat(int tick)
	{
		if(_count <= 0)
		{
			_is_deleted = true;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_Incenchantrange : public timeout_filter
{
protected:
	enum
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	float _range;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _range;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _range;
		return true;
	}
	filter_Incenchantrange(){}
public:
	DECLARE_SUBSTANCE(filter_Incenchantrange)
	filter_Incenchantrange(object_interface object, int period, float range, int mask)
			:timeout_filter(object,period,FILTER_MASK|mask), _range(range)
	{
		_filter_id = FILTER_INCENCHANTRANGE;
	}
	void OnAttach()
	{
//		_parent.IncVisibleState(VSTATE_INCENCHANTRANGE);
		_parent.InsertTeamVisibleState(HSTATE_INCENCHANTRANGE, _timeout);
		_parent.SendClientPrayDistanceChange(
			(_parent.GetSkillWrapper()).IncPrayDisAdjust(_range));
	}
	void OnRelease()
	{
//		_parent.DecVisibleState(VSTATE_INCENCHANTRANGE);
		_parent.RemoveTeamVisibleState(HSTATE_INCENCHANTRANGE);
		_parent.SendClientPrayDistanceChange(
			(_parent.GetSkillWrapper()).DecPrayDisAdjust(_range));
	}
};


class filter_Incphysicalmagicaldefense : public timeout_filter
{
protected:
    enum
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
    };

    int _physical_ratio;
    int _magical_ratio;

    virtual bool Save(archive& ar)
    {
        timeout_filter::Save(ar);
        ar << _physical_ratio;
        ar << _magical_ratio;

        return true;
    }

    virtual bool Load(archive& ar)
    {
        timeout_filter::Load(ar);
        ar >> _physical_ratio;
        ar >> _magical_ratio;

        return true;
    }

    filter_Incphysicalmagicaldefense() {}

public:
    DECLARE_SUBSTANCE(filter_Incphysicalmagicaldefense);
    filter_Incphysicalmagicaldefense(object_interface object, int period, float physical_ratio, float magical_ratio, int mask) : timeout_filter(object, period, FILTER_MASK | mask)
    {
        _filter_id = FILTER_INCPHYSICALMAGICALDEFENSE;
        _physical_ratio = (int)(physical_ratio * 100);
        _magical_ratio = (int)(magical_ratio * 100);
    }

    void OnAttach()
    {
//        _parent.IncVisibleState(VSTATE_INCPHYSICALMAGICALDEFENSE);
        _parent.InsertTeamVisibleState(HSTATE_INCPHYSICALMAGICALDEFENSE, _timeout);

        _parent.EnhanceScaleDefense(_physical_ratio);
        for (unsigned int i = 0; i < MAGIC_CLASS; ++i)
        {
            _parent.EnhanceScaleResistance(i, _magical_ratio);
        }
        _parent.UpdateDefenseData();
        _parent.UpdateMagicData();
    }

    void OnRelease()
    {
        _parent.ImpairScaleDefense(_physical_ratio);
        for (unsigned int i = 0; i < MAGIC_CLASS; ++i)
        {
            _parent.ImpairScaleResistance(i, _magical_ratio);
        }
        _parent.UpdateDefenseData();
        _parent.UpdateMagicData();

//        _parent.DecVisibleState(VSTATE_INCPHYSICALMAGICALDEFENSE);
        _parent.RemoveTeamVisibleState(HSTATE_INCPHYSICALMAGICALDEFENSE);
    }

};


class filter_Reducegold3 : public timeout_filter
{
protected:
    enum
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
    };

    int _gold_ratio;

    virtual bool Save(archive& ar)
    {
        timeout_filter::Save(ar);
        ar << _gold_ratio;

        return true;
    }

    virtual bool Load(archive& ar)
    {
        timeout_filter::Load(ar);
        ar >> _gold_ratio;

        return true;
    }

    filter_Reducegold3() {}

public:
    DECLARE_SUBSTANCE(filter_Reducegold3);
    filter_Reducegold3(object_interface object, int period, float gold_ratio, int mask) : timeout_filter(object, period, FILTER_MASK | mask)
    {
        _filter_id = FILTER_REDUCEGOLD3;
        _gold_ratio = (int)(gold_ratio * 100);
    }

    void OnAttach()
    {
//      _parent.IncVisibleState(VSTATE_REDUCEGOLD3);
        _parent.InsertTeamVisibleState(HSTATE_REDUCEGOLD3, _timeout);
        _parent.ImpairScaleResistance(0, _gold_ratio);
        _parent.UpdateMagicData();
    }

    void OnRelease()
    {
        _parent.EnhanceScaleResistance(0, _gold_ratio);
        _parent.UpdateMagicData();
//        _parent.DecVisibleState(VSTATE_REDUCEGOLD3);
        _parent.RemoveTeamVisibleState(HSTATE_REDUCEGOLD3);
    }

};


class filter_Reducewater3 : public timeout_filter
{
protected:
    enum
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
    };

    int _water_ratio;

    virtual bool Save(archive& ar)
    {
        timeout_filter::Save(ar);
        ar << _water_ratio;

        return true;
    }

    virtual bool Load(archive& ar)
    {
        timeout_filter::Load(ar);
        ar >> _water_ratio;

        return true;
    }

    filter_Reducewater3() {}

public:
    DECLARE_SUBSTANCE(filter_Reducewater3);
    filter_Reducewater3(object_interface object, int period, float water_ratio, int mask) : timeout_filter(object, period, FILTER_MASK | mask)
    {
        _filter_id = FILTER_REDUCEWATER3;
        _water_ratio = (int)(water_ratio * 100);
    }

    void OnAttach()
    {
//        _parent.IncVisibleState(VSTATE_REDUCEWATER3);
        _parent.InsertTeamVisibleState(HSTATE_REDUCEWATER3, _timeout);
        _parent.ImpairScaleResistance(2, _water_ratio);
        _parent.UpdateMagicData();
    }

    void OnRelease()
    {
        _parent.EnhanceScaleResistance(2, _water_ratio);
        _parent.UpdateMagicData();
//        _parent.DecVisibleState(VSTATE_REDUCEWATER3);
        _parent.RemoveTeamVisibleState(HSTATE_REDUCEWATER3);
    }

};


class filter_Genhpap : public timeout_filter
{
protected:
    enum
    {
        FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
    };

    int _hp_ratio;
    int _ap;

    virtual bool Save(archive& ar)
    {
        timeout_filter::Save(ar);
        ar << _hp_ratio;
        ar << _ap;

        return true;
    }

    virtual bool Load(archive& ar)
    {
        timeout_filter::Load(ar);
        ar >> _hp_ratio;
        ar >> _ap;

        return true;
    }

    filter_Genhpap() {}

public:
    DECLARE_SUBSTANCE(filter_Genhpap);
    filter_Genhpap(object_interface object, int period, float hp_ratio, int ap, int mask) : timeout_filter(object, period, FILTER_MASK | mask)
    {
        _filter_id = FILTER_GENHPAP;
        _hp_ratio = (int)(hp_ratio * 100);
        _ap = ap;
    }

    void TranslateSendAttack(const XID& target, attack_msg& msg)
    {
        msg._attack_state |= 0x8000; // AT_STATE_CRIT_FEEDBACK;
        msg.feedback_filter = FILTER_GENHPAP;
    }

    void  OnModify(int ctrlname, void* ctrlval, unsigned int ctrllen)
    {
        if (ctrlname == FMID_CRIT_FEEDBACK)
        {
            _parent.ModifyScaleHP(_hp_ratio);
            _parent.ModifyAP(_ap);
        }
    }

    void OnAttach()
    {
//        _parent.IncVisibleState(VSTATE_GENHPAP);
        _parent.InsertTeamVisibleState(HSTATE_GENHPAP, _timeout);
    }

    void OnRelease()
    {
//        _parent.DecVisibleState(VSTATE_GENHPAP);
        _parent.RemoveTeamVisibleState(HSTATE_GENHPAP);
    }

};


class filter_Extraexpfactor : public timeout_filter
{
protected:
    enum
    {
        FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_SAVE_DB_DATA
    };

    float _exp_sp_factor;
    float _realm_exp_factor;

    virtual bool Save(archive& ar)
    {
        int tmp = _timeout;
        _timeout += time(NULL);

        timeout_filter::Save(ar);
        ar << _exp_sp_factor << _realm_exp_factor;

        _timeout = tmp;
        return true;
    }

    virtual bool Load(archive& ar)
    {
        timeout_filter::Load(ar);
        ar >> _exp_sp_factor >> _realm_exp_factor;

        _timeout -= time(NULL);
        if (_timeout <= 0) _timeout = 1;

        return true;
    }

    filter_Extraexpfactor() {}

public:
    DECLARE_SUBSTANCE(filter_Extraexpfactor);
    filter_Extraexpfactor(object_interface object, int period, float exp_sp_factor, float realm_exp_factor) : timeout_filter(object, period, FILTER_MASK)
    {
        _filter_id = FILTER_EXTRAEXPFACTOR;
        _exp_sp_factor = exp_sp_factor;
        _realm_exp_factor = realm_exp_factor;
    }

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Extraexpfactor*>(f));
		filter_Extraexpfactor* nf = (filter_Extraexpfactor*) f;
		if(nf->_exp_sp_factor > _exp_sp_factor)
		{
			_parent.ImpairScaleExp(_exp_sp_factor, _realm_exp_factor);
			_exp_sp_factor = nf->_exp_sp_factor;
			_realm_exp_factor = nf->_realm_exp_factor;
			_parent.EnhanceScaleExp(_exp_sp_factor, _realm_exp_factor);
		}
		else if(_exp_sp_factor - nf->_exp_sp_factor < 1e-5)
		{
			_timeout = nf->_timeout;
		}
		
		if (_timeout > 0 )
		{
			_parent.RemoveTeamVisibleState(HSTATE_EXTRAEXPFACTOR);
			_parent.InsertTeamVisibleState(HSTATE_EXTRAEXPFACTOR, _timeout);
		}
		
	}

    void OnAttach()
    {
        _parent.IncVisibleState(VSTATE_EXTRAEXPFACTOR);
        _parent.InsertTeamVisibleState(HSTATE_EXTRAEXPFACTOR, _timeout);
        _parent.EnhanceScaleExp(_exp_sp_factor, _realm_exp_factor);
    }

    void OnRelease()
    {
        _parent.DecVisibleState(VSTATE_EXTRAEXPFACTOR);
        _parent.RemoveTeamVisibleState(HSTATE_EXTRAEXPFACTOR);
        _parent.ImpairScaleExp(_exp_sp_factor, _realm_exp_factor);
    }

};

class filter_Weakenbless2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _inc_heal_cool_time;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc_heal_cool_time;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc_heal_cool_time;
		return true;
	}

	filter_Weakenbless2(){}
public:
	DECLARE_SUBSTANCE(filter_Weakenbless2); 
	filter_Weakenbless2(object_interface  object,int period, int inc_heal_cool_time)
				        :timeout_filter(object,period,FILTER_MASK),_inc_heal_cool_time(inc_heal_cool_time)
	{
		_filter_id = FILTER_WEAKENBLESS2;
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Weakenbless2*>(f));
		filter_Weakenbless2* nf = (filter_Weakenbless2*) f;
		if(_inc_heal_cool_time < nf->_inc_heal_cool_time)
		{
			_parent.DecHealCoolTime(_inc_heal_cool_time);
			_inc_heal_cool_time = nf->_inc_heal_cool_time;
			_parent.IncHealCoolTime(_inc_heal_cool_time);
			_timeout = nf->_timeout;
		}
		else if(_inc_heal_cool_time == nf->_inc_heal_cool_time)
			_timeout = nf->_timeout;
		
		if (_timeout > 0 )
		{
			_parent.RemoveTeamVisibleState(HSTATE_WEAKENBLESS2);
			_parent.InsertTeamVisibleState(HSTATE_WEAKENBLESS2, _timeout);
		}
		
	}

	void OnAttach()
	{
//        _parent.IncVisibleState(VSTATE_WEAKENBLESS2);
		_parent.InsertTeamVisibleState(HSTATE_WEAKENBLESS2, _timeout);
		_parent.IncHealCoolTime(_inc_heal_cool_time);
	}

	void OnRelease()
	{
//		_parent.DecVisibleState(VSTATE_WEAKENBLESS2);
		_parent.RemoveTeamVisibleState(HSTATE_WEAKENBLESS2);
		_parent.DecHealCoolTime(_inc_heal_cool_time);
	}
};

///////////////////////////////////////////////////////////////////
//���˸���״̬��
//////////////////////////////////////////////////////////////////

class filter_solo_IncAttackAndMagic : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE,
		MAX_STACK = 20,
	};
	int _attack_point;
	int _magic_point;
	int _stacks;
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar); 
		ar << _attack_point << _magic_point << _stacks;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Save(ar); 
		ar >> _attack_point >> _magic_point >> _stacks;
		return true;
	}
	filter_solo_IncAttackAndMagic(){}
public:
	DECLARE_SUBSTANCE(filter_solo_IncAttackAndMagic);
	filter_solo_IncAttackAndMagic(object_interface object, int attack_point, int magic_point, int period):timeout_filter(object, period, FILTER_MASK),_attack_point(attack_point),_magic_point(magic_point),_stacks(1)
	{
		_filter_id = FILTER_SOLO_INCATTACKANDMAGIC; 
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_solo_IncAttackAndMagic*>(f));
		filter_solo_IncAttackAndMagic* nf = (filter_solo_IncAttackAndMagic*)f;

		if(nf->_timeout)
		{
			++_stacks;
			if(_stacks > MAX_STACK)
			  _stacks = MAX_STACK;
			_timeout = GetTimeOut(nf);
			_parent.ImpairPlusDamage(_attack_point);
			_parent.ImpairPlusMagicDamage(_magic_point);
			_attack_point += nf->GetAttackPoint();
			_magic_point  += nf->GetMagicPoint();
			_parent.EnhancePlusDamage(_attack_point);
			_parent.EnhancePlusMagicDamage(_magic_point);
			_parent.ModifyTeamVisibleState(HSTATE_SOLO_INCATTACKANDMAGIC, _stacks,_timeout);
			_parent.UpdateAttackData();
			_parent.UpdateMagicData();
			_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
		}
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SOLO_INCATTACKANDMAGIC, _stacks, _timeout);	
		_parent.EnhancePlusDamage(_attack_point);
		_parent.EnhancePlusMagicDamage(_magic_point);
		_parent.UpdateAttackData(); 
		_parent.UpdateMagicData();
		_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_INCATTACKANDMAGIC);
		_parent.ImpairPlusDamage(_attack_point);
		_parent.ImpairPlusMagicDamage(_magic_point);
		_parent.UpdateAttackData();
		_parent.UpdateMagicData();
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
	}
	int GetAttackPoint()
	{
		return _attack_point;
	}
	int GetMagicPoint()
	{
		return _magic_point;
	}
};

class filter_solo_Incdefence : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE,
		MAX_STACK = 20,
	};

	int _defence_point;
	int _stacks;
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _defence_point << _stacks;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _defence_point >> _stacks;
		return true;
	}
	filter_solo_Incdefence(){}
public:
	DECLARE_SUBSTANCE(filter_solo_Incdefence); 
	filter_solo_Incdefence(object_interface  object,int defence_point,int period):timeout_filter(object,period,FILTER_MASK),_defence_point(defence_point),_stacks(1)
	{
		_filter_id = FILTER_SOLO_INCDEFENCE;
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_solo_Incdefence*>(f));
		filter_solo_Incdefence* nf = (filter_solo_Incdefence*) f;
		if(nf->_timeout)
		{
			++_stacks;
			if(_stacks > MAX_STACK)
			  _stacks = MAX_STACK;
			_timeout = GetTimeOut(nf);
			_parent.ImpairPlusDefense(_defence_point);
			_defence_point += nf->GetDefencePoint();
			_parent.EnhancePlusDefense(_defence_point);
			_parent.ModifyTeamVisibleState(HSTATE_SOLO_INCDEFENCE, _stacks, _timeout);
			_parent.UpdateDefenseData();
			_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
		}
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SOLO_INCDEFENCE, _stacks, _timeout);
		_parent.EnhancePlusDefense(_defence_point);
		_parent.UpdateDefenseData();
		_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_INCDEFENCE);
		_parent.ImpairPlusDefense(_defence_point);
		_parent.UpdateDefenseData();
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
	}

	int GetDefencePoint()
	{
		return _defence_point;
	}
};

class filter_solo_Enhanceresist : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE,
		MAX_STACK = 20,
	};

	int _enhance_point;
	int _stacks;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _enhance_point << _stacks;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _enhance_point >> _stacks;
		return true;
	}
	filter_solo_Enhanceresist(){}
public:
	DECLARE_SUBSTANCE(filter_solo_Enhanceresist); 
	filter_solo_Enhanceresist(object_interface  object,int enhance_point,int period)
				        :timeout_filter(object,period,FILTER_MASK),_enhance_point(enhance_point),_stacks(1)
	{
		_filter_id = FILTER_SOLO_ENHANCERESIST;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_solo_Enhanceresist*>(f));
		filter_solo_Enhanceresist* nf = (filter_solo_Enhanceresist*) f;
		if(nf->_timeout)
		{
			if(++_stacks <= MAX_STACK)
			{
				_timeout = GetTimeOut(nf);
				_parent.ImpairPlusResistance(0, _enhance_point);
				_parent.ImpairPlusResistance(1, _enhance_point);
				_parent.ImpairPlusResistance(2, _enhance_point);
				_parent.ImpairPlusResistance(3, _enhance_point);
				_parent.ImpairPlusResistance(4, _enhance_point);
				_enhance_point += nf->GetResistEnhancePoint();
				_parent.EnhancePlusResistance(0, _enhance_point);
				_parent.EnhancePlusResistance(1, _enhance_point);
				_parent.EnhancePlusResistance(2, _enhance_point);
				_parent.EnhancePlusResistance(3, _enhance_point);
				_parent.EnhancePlusResistance(4, _enhance_point);
				_parent.ModifyTeamVisibleState(HSTATE_SOLO_ENHANCERESIST, _stacks, _timeout);
				_parent.UpdateMagicData();
				_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
			}
			else
			{
				this->_stacks = 20;
			}
		}
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SOLO_ENHANCERESIST, _stacks, _timeout);
		_parent.EnhancePlusResistance(0, _enhance_point);
		_parent.EnhancePlusResistance(1, _enhance_point);
		_parent.EnhancePlusResistance(2, _enhance_point);
		_parent.EnhancePlusResistance(3, _enhance_point);
		_parent.EnhancePlusResistance(4, _enhance_point);
		_parent.UpdateMagicData();
		_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_ENHANCERESIST);
		_parent.ImpairPlusResistance(0, _enhance_point);
		_parent.ImpairPlusResistance(1, _enhance_point);
		_parent.ImpairPlusResistance(2, _enhance_point);
		_parent.ImpairPlusResistance(3, _enhance_point);
		_parent.ImpairPlusResistance(4, _enhance_point);
		_parent.UpdateMagicData();
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
	}
	int GetResistEnhancePoint()
	{
		return _enhance_point;
	}
};

class filter_solo_IncMaxhp : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE,
		MAX_STACK = 20,
	};

	int _inc_maxhp_value;
	int _stacks;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _inc_maxhp_value << _stacks;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _inc_maxhp_value >> _stacks;
		return true;
	}
	filter_solo_IncMaxhp(){}
public:
	DECLARE_SUBSTANCE(filter_solo_IncMaxhp); 
	filter_solo_IncMaxhp(object_interface  object,int inc_maxhp_value,int period)
				        :timeout_filter(object,period,FILTER_MASK),_inc_maxhp_value(inc_maxhp_value),_stacks(1)
	{
		_filter_id = FILTER_SOLO_INCMAXHP;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_solo_IncMaxhp*>(f));
		filter_solo_IncMaxhp* nf = (filter_solo_IncMaxhp*) f;
		if(nf->_timeout)
		{
			++_stacks;
			if(_stacks > MAX_STACK)
			  _stacks = MAX_STACK;
			_timeout = GetTimeOut(nf);
			_parent.ImpairPlusMaxHP(_inc_maxhp_value);
			_inc_maxhp_value += nf->GetMaxHpValue();
			_parent.EnhancePlusMaxHP(_inc_maxhp_value);
			_parent.ModifyTeamVisibleState(HSTATE_SOLO_INCMAXHP, _stacks, _timeout);
			_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
		}
		
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SOLO_INCMAXHP, _stacks, _timeout);
		_parent.EnhancePlusMaxHP(_inc_maxhp_value);
		_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_INCMAXHP);
		_parent.ImpairPlusMaxHP(_inc_maxhp_value);
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
	}
	int GetMaxHpValue()
	{
		return _inc_maxhp_value;
	}
};

class filter_solo_invincible : public filter
{
protected:
	short _timeout;
	enum 
	{
		FILTER_MASK = FILTER_MASK_HEARTBEAT | FILTER_MASK_TRANSLATE_RECV_MSG | FILTER_MASK_TRANSLATE_ENCHANT
			| FILTER_MASK_UNIQUE | FILTER_MASK_NOSAVE 
	};
public:
	DECLARE_SUBSTANCE(filter_solo_invincible);
	filter_solo_invincible(object_interface  object,short timeout = -1)
		:filter(object, FILTER_MASK),_timeout(timeout)
	{
		_filter_id = FILTER_SOLO_INVINCIBLE;
	}

protected:
	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _timeout;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _timeout;
		return true;
	}
	
	filter_solo_invincible() {}

	void OnAttach()
	{
		_parent.SetSoloChallengeFilterData(_filter_id, 1);
		_parent.InsertTeamVisibleState(HSTATE_SOLO_INVINCIBLE, _timeout);
	}

	void OnRelease()
	{
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_INVINCIBLE);
	}

	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
		msg.target_faction = 0;
		msg._attack_state |= 0x0080;//gactive_imp::AT_STATE_IMMUNE;
	}       

	void TranslateEnchant(const XID & attacker,enchant_msg & msg)
	{
		if(!msg.helpful)
		{
			msg.target_faction = 0;
			msg._attack_state |= 0x0080;//gactive_imp::AT_STATE_IMMUNE;
		}
	}       

	void Heartbeat(int tick)
	{
		if(_timeout < 0) return;
		if(--_timeout <= 0) 
		{
			_is_deleted = true;
		}
	}
};

class filter_solo_Hpgen : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_NOSAVE,
	};
	int _health;
	char _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _health;
		ar << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _health;
		ar >> _counter;
		return true;
	}
	filter_solo_Hpgen(){}
public:
	DECLARE_SUBSTANCE(filter_solo_Hpgen); 
	filter_solo_Hpgen(object_interface  object,int health, int period)
			:timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SOLO_HPGEN;
		_counter = 0;
		_health = health/period;
	}
	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_SOLO_HPGEN, _timeout);
		_parent.SetSoloChallengeFilterData(_filter_id, 1);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_HPGEN);
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
	}
	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout)
		{
			_parent.HealBySkill(_health*_counter);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

class filter_solo_Dechurt : public timeout_filter	//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_NOSAVE | FILTER_MASK_BUFF, 
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_solo_Dechurt(){}
public:
	DECLARE_SUBSTANCE(filter_solo_Dechurt); 
	filter_solo_Dechurt(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SOLO_DECHURT;
		_ratio = 1.0-ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SOLO_DECHURT, _timeout);
		_parent.SetSoloChallengeFilterData(_filter_id, 1);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_DECHURT);
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
	}
};

class filter_solo_Addattackrange : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_BUFF, 
	};
	int _add_range;
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _add_range;
		return true;
	}
	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _add_range;
		return true;
	}
	filter_solo_Addattackrange(){}
public:
	DECLARE_SUBSTANCE(filter_solo_Addattackrange);
	filter_solo_Addattackrange(object_interface  object, int add_range, int period):timeout_filter(object,period,FILTER_MASK),_add_range(add_range)
	{
		_filter_id = FILTER_SOLO_ADDATTACKRANGE; 
	}
	void OnAttach()
	{
		_parent.EnhanceAttackRange(_add_range); 
		_parent.InsertTeamVisibleState(HSTATE_SOLO_ADDATTACKRANGE, _timeout);
		_parent.UpdateAttackData();
		_parent.SetSoloChallengeFilterData(_filter_id, 1);
		_parent.SendClientAttackData();
	}
	void OnRelease()
	{
		_parent.ImpairAttackRange(_add_range);
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_ADDATTACKRANGE);
		_parent.UpdateAttackData();
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
		_parent.SendClientAttackData();
	}
};
								
class filter_Thunder3 : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE 
	};
	filter_Thunder3(){}
public:
	DECLARE_SUBSTANCE(filter_Thunder3); 
	filter_Thunder3(object_interface  object,int period, int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		_filter_id = FILTER_THUNDER3;
		_icon = HSTATE_THUNDER3;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_THUNDER3, _timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_THUNDER3);
	}
};

class filter_Toxic3 : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE
	};
	filter_Toxic3(){}
public:
	DECLARE_SUBSTANCE(filter_Toxic3); 
	filter_Toxic3(object_interface  object,int period, int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		_filter_id = FILTER_TOXIC3;
		_icon = HSTATE_TOXIC3;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_TOXIC3, _timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_TOXIC3);
	}
};

class filter_Flood3 : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE
	};
	filter_Flood3(){}
public:
	DECLARE_SUBSTANCE(filter_Flood3); 
	filter_Flood3(object_interface  object,int period, int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		_filter_id = FILTER_FLOOD3;
		_icon = HSTATE_FLOOD3;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_FLOOD3, _timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FLOOD3);
	}
};
class filter_Burning3 : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE
	};
	filter_Burning3(){}
public:
	DECLARE_SUBSTANCE(filter_Burning3); 
	filter_Burning3(object_interface  object,int period, int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		_filter_id = FILTER_BURNING3;
		_icon = HSTATE_BURNING3;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_BURNING3, _timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_BURNING3);
	}
};

class filter_Fallen3 : public filter_Wounded
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE 
	};
	filter_Fallen3(){}
public:
	DECLARE_SUBSTANCE(filter_Fallen3); 
	filter_Fallen3(object_interface  object,int period, int damage,int mask=0)
			:filter_Wounded(object,period,damage,FILTER_MASK|mask)
	{
		_filter_id = FILTER_FALLEN3;
		_icon = HSTATE_FALLEN3;
	}

	void OnAttach() 
	{
		_parent.InsertTeamVisibleState(HSTATE_FALLEN3, _timeout);
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FALLEN3);
	}
};

// Buff mp reduzido + redução de defesa + aumento de velocidade Paladino 


class filter_ReduceSpeeddebuff : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_MANA_COST | FILTER_MASK_ADJUST_DAMAGE
	};

	int _ratio;
	int _amount;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _amount;		
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _amount;
		return true;
	}
	
	// Reduce
	
	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _amount;
		dmg.magic_damage[0] *= _amount;
		dmg.magic_damage[1] *= _amount;
		dmg.magic_damage[2] *= _amount;
		dmg.magic_damage[3] *= _amount;
		dmg.magic_damage[4] *= _amount;
	}
	
	
	filter_ReduceSpeeddebuff(){}
public:
	DECLARE_SUBSTANCE(filter_ReduceSpeeddebuff); 
	filter_ReduceSpeeddebuff(object_interface  object,int r,int amount, int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_amount(amount)
	{
		_filter_id = FILTER_REDUCESPEEDDDEBUFF;
		_amount = 1.0-amount;
	}		
	
					
	void Merge(filter *f) // Speed
	{
		
		ASSERT(dynamic_cast<filter_ReduceSpeeddebuff*>(f));
		filter_ReduceSpeeddebuff* nf = (filter_ReduceSpeeddebuff*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairSpeed(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceSpeed(_ratio);
			_parent.UpdateSpeedData();
			_parent.SendClientCurSpeed();
		}
		
		if (_timeout > 0 )
		{
			_parent.RemoveTeamVisibleState(HSTATE_REDUCESPEEDDDEBUFF);
			_parent.InsertTeamVisibleState(HSTATE_REDUCESPEEDDDEBUFF, _timeout);
		}
		
	}

	void OnAttach()
	{		
		// Icon
		_parent.InsertTeamVisibleState(HSTATE_REDUCESPEEDDDEBUFF, _timeout);

		// Speed 				
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		
		// Freemove
		_parent.IncImmuneMask(IMMUNESLOW);
		_parent.IncImmuneMask(IMMUNEFIX);
		_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.IncImmuneMask(IMMUNESLEEP);	
	}

	void OnRelease()
	{
		// Icon
		_parent.RemoveTeamVisibleState(HSTATE_REDUCESPEEDDDEBUFF);
	
		// Speed 		
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		
		// Free Move		
		_parent.DecImmuneMask(IMMUNESLOW);
		_parent.DecImmuneMask(IMMUNEFIX);
		_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.DecImmuneMask(IMMUNESLEEP);

	}
	int GetRatio()
	{
		return _ratio;
	}
	
	
};

// Buff Teleport

class filter_Shattereddream : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE | FILTER_MASK_TRANSLATE_SEND_MSG 
	};
	
	int _tag;
	A3DVECTOR _pos;
	XID _target;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _tag << _target << _pos;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _tag >> _target >> _pos;
		return true;
	}

	filter_Shattereddream(){}
public:
	DECLARE_SUBSTANCE(filter_Shattereddream); 
	filter_Shattereddream(object_interface object,int period,int tag, const XID & target, A3DVECTOR pos)
			:timeout_filter(object,period,FILTER_MASK),_tag(tag),_target(target),_pos(pos)
	{
		_filter_id = FILTER_SHATTEREDDREAM;
	}		

	virtual void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(IS_PHYSIC_ATTACK(msg.attack_attr) && !_parent.IsDead())
		{			
			_parent.LongJump(_pos,_tag);
		}	
	}

	void OnAttach()
	{
		// Icon
		_parent.IncVisibleState(VSTATE_NEWBUFF36);
		_parent.InsertTeamVisibleState(HSTATE_SHATTEREDDREAM, _timeout);	
	
		_parent.EnhanceAttackRange(30);
		_parent.UpdateAttackData();
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		// Icon
		_parent.DecVisibleState(VSTATE_NEWBUFF36);
		_parent.RemoveTeamVisibleState(HSTATE_SHATTEREDDREAM);
		
		_parent.ImpairAttackRange(30);
		_parent.UpdateAttackData();
		_parent.SendClientAttackData();
	}

};

class filter_Positionrollback2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE 
	};

	int _tag;
	A3DVECTOR _pos;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _tag << _pos;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _tag >> _pos;
		return true;
	}
	filter_Positionrollback2(){}
public:
	DECLARE_SUBSTANCE(filter_Positionrollback2); 
	filter_Positionrollback2(object_interface  object,int period,int tag,const A3DVECTOR & pos)
			:timeout_filter(object,period,FILTER_MASK),_tag(tag),_pos(pos)
	{
		_filter_id = FILTER_POSITIONROLLBACK2;
	}

	void OnAttach()
	{		
	}

	void OnRelease()
	{
	}

	virtual void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		if(_timeout <= 0 && !_parent.IsDead())
		{
			_parent.LongJump(_pos,_tag);
		}
	}
};

// New Shield Buff

class filter_ShieldNew1 : public timeout_filter // Novas Alterações
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}	

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if (_value > 0)
		{
			if (dmg.physic_damage)
			{
				if (dmg.physic_damage > _value)
				{
					dmg.physic_damage -= _value;
					_value = 0;
				}
				else
				{
					float new_f = (_value - dmg.physic_damage);
					dmg.physic_damage = 1;
					_value -= new_f;
				}
			}
			
			for (int i = 0; i < 5; i++)
			{
				if (dmg.magic_damage[i])
				{
					if (dmg.magic_damage[i] > _value)
					{
						dmg.magic_damage[i] -= _value;
						_value = 0;
					}
					else
					{
						float new_f = (_value - dmg.magic_damage[i]);
						dmg.magic_damage[i] = 1;
						_value -= new_f;
					}
				}
			}
		}
		else
		{
			_is_deleted  = true;
		}
	}

	filter_ShieldNew1(){}
public:
	DECLARE_SUBSTANCE(filter_ShieldNew1); 
	filter_ShieldNew1(object_interface  object,float value, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SHIELDBUFFNEW1;
		_value = value;
	}

void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF37);
		_parent.InsertTeamVisibleState(HSTATE_SHIELDBUFFNEW1, (int) _value, _timeout);
		_parent.IncImmuneMask ( IMMUNESLOW | IMMUNEFIX | IMMUNEDIZZY | IMMUNESLEEP | IMMUNEBREAK | IMMUNEPALSY | IMMUNECURSED );
	}

	void OnRelease()
	{

		_parent.DecVisibleState(VSTATE_NEWBUFF37);
		_parent.RemoveTeamVisibleState(HSTATE_SHIELDBUFFNEW1);
		_parent.DecImmuneMask ( IMMUNESLOW | IMMUNEFIX | IMMUNEDIZZY | IMMUNESLEEP | IMMUNEBREAK | IMMUNEPALSY | IMMUNECURSED );
	}


};

class filter_ShieldNew2 : public filter_Aurabase		//Skill Borrão Paladino
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	float _range;
	int _skill;
	int _level;
	
	virtual bool Save(archive & ar)
	{
		filter_Aurabase::Save(ar);
		ar << _range << _skill << _level;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Aurabase::Load(ar);
		ar >> _range >> _skill >> _level;
		return true;
	}
	
	filter_ShieldNew2(){}
public:
	DECLARE_SUBSTANCE(filter_ShieldNew2);
	filter_ShieldNew2(object_interface object, int period, float range, int skill, int level, int step = 3)
			:filter_Aurabase(object, period, FILTER_MASK, step),_range(range),_skill(skill),_level(level)
	{
		_filter_id = FILTER_SHIELDBUFFNEW2;					
	}

	virtual void DoAura()
	{
		enchant_msg	msg;
		memset(&msg,0,sizeof(msg));
		msg.attack_range  = _range;
		msg.skill = _skill;
		msg.skill_level = _level;
		msg.helpful = 0;
		msg.force_attack = _parent.GetForceAttack();
		msg.skill_modify[0] = _t0;
		msg.skill_modify[1] = _t1;
		msg.skill_modify[2] = _t2;

		_parent.SetAuraAttackState();
		_parent.EnterCombatState();
		_parent.RegionEnchant1(_parent.GetPos(), _range, msg, XID(-1,-1));
	}
	
	void OnAttach()
	{
		
	}

	void OnRelease()
	{
		
	}	

};

// New Buff


// New Buff


class filter_RetortNewPaladin : public timeout_filter // Nova Alteração
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH 
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF  
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_RetortNewPaladin(){}
public:
	DECLARE_SUBSTANCE(filter_RetortNewPaladin); 
	filter_RetortNewPaladin(object_interface  object,int ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK), _ratio(ratio)
	{
		_filter_id = FILTER_SHIELDBUFFNEW3;
	}

	// Corrigir escudo 
	
	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust);
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF39);
		_parent.InsertTeamVisibleState(HSTATE_SHIELDBUFFNEW3, _timeout);
		_parent.IncImmuneMask ( IMMUNESLOW | IMMUNEFIX | IMMUNEDIZZY | IMMUNESLEEP | IMMUNEBREAK | IMMUNEPALSY | IMMUNECURSED );
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF39);
		_parent.RemoveTeamVisibleState(HSTATE_SHIELDBUFFNEW3);
		_parent.DecImmuneMask ( IMMUNESLOW | IMMUNEFIX | IMMUNEDIZZY | IMMUNESLEEP | IMMUNEBREAK | IMMUNEPALSY | IMMUNECURSED );
	}

	
};


class filter_NewBuffSpeed : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_NewBuffSpeed(){}
public:
	DECLARE_SUBSTANCE(filter_NewBuffSpeed); 
	filter_NewBuffSpeed(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_NEWSPEEDBUFF;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_NewBuffSpeed*>(f));
		filter_NewBuffSpeed* nf = (filter_NewBuffSpeed*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairSpeed(_ratio);
			_parent.ImpairSwimSpeed(_ratio);
			_parent.ImpairFlySpeed(_ratio * 0.5f);
			_ratio = nf->GetRatio();
			_parent.EnhanceSpeed(_ratio);
			_parent.EnhanceSwimSpeed(_ratio);
			_parent.EnhanceFlySpeed(_ratio * 0.5f);
			_parent.UpdateSpeedData();
			_parent.SendClientCurSpeed();
		}
		
		if (_timeout > 0 )
		{
			_parent.RemoveTeamVisibleState(HSTATE_NEWBUFFSPEED);
			_parent.InsertTeamVisibleState(HSTATE_NEWBUFFSPEED, _timeout);
		}
		
		
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_NEWBUFFSPEED, _timeout);
		_parent.EnhanceSpeed(_ratio);
		_parent.EnhanceSwimSpeed(_ratio);
		_parent.EnhanceFlySpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_NEWBUFFSPEED);
		_parent.ImpairSpeed(_ratio);
		_parent.ImpairSwimSpeed(_ratio);
		_parent.ImpairFlySpeed(_ratio * 0.5f);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
	int GetRatio()
	{
		return _ratio;
	}
};



class filter_IraAtiradora : public timeout_filter		//mask������������BUFF/DEBUFF(�ɱ���ɢ)��/0(����)
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	float _ratio;
	bool _insertvstate;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _insertvstate;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _ratio;
		dmg.magic_damage[0] *= _ratio;
		dmg.magic_damage[1] *= _ratio;
		dmg.magic_damage[2] *= _ratio;
		dmg.magic_damage[3] *= _ratio;
		dmg.magic_damage[4] *= _ratio;
	}

	filter_IraAtiradora(){}
public:
	DECLARE_SUBSTANCE(filter_IraAtiradora); 
	filter_IraAtiradora(object_interface  object,float ratio, int period, bool insertvstate=true,int mask=FILTER_MASK_DEBUFF)
				        :timeout_filter(object,period,FILTER_MASK|mask),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_IRAATIRADORA;
		_ratio = 1.0+ratio;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_IRAATIRADORA, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_IRAATIRADORA);
	}
};

class filter_GeloAtiradora : public timeout_filter   //ͬѣ��
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_GeloAtiradora(){}
public:
	DECLARE_SUBSTANCE(filter_GeloAtiradora); 
	filter_GeloAtiradora(object_interface  object,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_GELOATIRADORA;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_STUN);
			_parent.IncVisibleState(VSTATE_NEWBUFF15);
		_parent.InsertTeamVisibleState(HSTATE_GELOATIRADORA, _timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_STUN);
			_parent.DecVisibleState(VSTATE_NEWBUFF15);
		_parent.RemoveTeamVisibleState(HSTATE_GELOATIRADORA);
	}

};


class filter_FeAtiradora : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}

	filter_FeAtiradora(){}
public:
	DECLARE_SUBSTANCE(filter_FeAtiradora); 
	filter_FeAtiradora(object_interface object, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FEATIRADORA;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FEATIRADORA, _timeout);
		_parent.IncImmuneMask(IMMUNESLOW);
		_parent.IncImmuneMask(IMMUNEFIX);
		_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.IncImmuneMask(IMMUNESLEEP);
		_parent.IncImmuneMask(IMMUNEBREAK); // New
		_parent.IncImmuneMask(IMMUNEPALSY); // New
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FEATIRADORA);
		_parent.DecImmuneMask(IMMUNESLOW);
		_parent.DecImmuneMask(IMMUNEFIX);
		_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.DecImmuneMask(IMMUNESLEEP);
		_parent.DecImmuneMask(IMMUNEBREAK); // New
		_parent.DecImmuneMask(IMMUNEPALSY); // New
	}
};


class filter_SetRemoveNew : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};


	filter_SetRemoveNew(){}
public:
	DECLARE_SUBSTANCE(filter_SetRemoveNew); 
	filter_SetRemoveNew(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_SETREMOVENEW;		
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		_parent.Die();
	}


	void OnAttach()
	{
	}

	void OnRelease()
	{
	}

		
};
//UltWR
class filter_AccumulateAttack : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =  FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};

	float _ratio = 0;
	float _ratio_add;
	float _ratio_max;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _ratio_add;
		ar << _ratio_max;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _ratio_add;
		ar >> _ratio_max;
		return true;
	}

	filter_AccumulateAttack(){}
public:
	DECLARE_SUBSTANCE(filter_AccumulateAttack); 
	filter_AccumulateAttack(object_interface object, int period,float ratio_add,float ratio_max,int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_ACCUMULATEATTACK;
		_ratio_add = ratio_add;
		_ratio_max = ratio_max;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if (msg.skill_id)
		{
		float cur_ratio;
				_ratio += _ratio_add;
				if (_ratio > _ratio_max)
				{
					_ratio = _ratio_max;
				}
				cur_ratio = _ratio + 1;
				msg.physic_damage = (int)(msg.physic_damage * cur_ratio);
				msg.magic_damage[0] = (int)(msg.magic_damage[0]*cur_ratio);
				msg.magic_damage[1] = (int)(msg.magic_damage[1]*cur_ratio);
				msg.magic_damage[2] = (int)(msg.magic_damage[2]*cur_ratio);
				msg.magic_damage[3] = (int)(msg.magic_damage[3]*cur_ratio);
				msg.magic_damage[4] = (int)(msg.magic_damage[4]*cur_ratio);
				//_parent.SendClientEnchantResult(_parent.GetSelfID(), 319, 1, false, 0, 0);
		}
	}

	virtual void Heartbeat(int tick)
	{
		//timeout_filter::Heartbeat(tick);
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_ACCUMULATEATTACK);
		_parent.InsertTeamVisibleState(HSTATE_ACCUMULATEATTACK, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_ACCUMULATEATTACK);
		_parent.RemoveTeamVisibleState(HSTATE_ACCUMULATEATTACK);
	}
};

//UltMG
class filter_AccumulateAttack2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =  FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSLATE_RECV_MSG | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio1;
	float _ratio2;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio1;
		ar << _ratio2;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio1;
		ar >> _ratio2;
		return true;
	}

	filter_AccumulateAttack2(){}
public:
	DECLARE_SUBSTANCE(filter_AccumulateAttack2); 
	filter_AccumulateAttack2(object_interface object, int period,float ratio1,float ratio2,int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_ACCUMULATEATTACK2;
		_ratio1 = ratio1 + 1;
		_ratio2 = ratio2 + 1;
	}
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if (msg.skill_id)
		{
				msg.physic_damage = (int)(msg.physic_damage * _ratio1);
				msg.magic_damage[0] = (int)(msg.magic_damage[0]*_ratio1);
				msg.magic_damage[1] = (int)(msg.magic_damage[1]*_ratio1);
				msg.magic_damage[2] = (int)(msg.magic_damage[2]*_ratio1);
				msg.magic_damage[3] = (int)(msg.magic_damage[3]*_ratio1);
				msg.magic_damage[4] = (int)(msg.magic_damage[4]*_ratio1);
				//_parent.SendClientEnchantResult(_parent.GetSelfID(), 319, 1, false, 0, 0);
		}
	}
	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
		if (msg.skill_id)
		{
				msg.physic_damage = (int)(msg.physic_damage * _ratio2);
				msg.magic_damage[0] = (int)(msg.magic_damage[0]*_ratio2);
				msg.magic_damage[1] = (int)(msg.magic_damage[1]*_ratio2);
				msg.magic_damage[2] = (int)(msg.magic_damage[2]*_ratio2);
				msg.magic_damage[3] = (int)(msg.magic_damage[3]*_ratio2);
				msg.magic_damage[4] = (int)(msg.magic_damage[4]*_ratio2);
				//_parent.SendClientEnchantResult(_parent.GetSelfID(), 319, 1, false, 0, 0);
		}
	}
	virtual void Heartbeat(int tick)
	{
		//timeout_filter::Heartbeat(tick);
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_ACCUMULATEATTACK2);
		_parent.InsertTeamVisibleState(HSTATE_ACCUMULATEATTACK2, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_ACCUMULATEATTACK2);
		_parent.RemoveTeamVisibleState(HSTATE_ACCUMULATEATTACK2);
	}
};
//CuraWF
class filter_DecRegionDMG : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =  FILTER_MASK_TRANSLATE_RECV_MSG | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_DecRegionDMG(){}
public:
	DECLARE_SUBSTANCE(filter_DecRegionDMG); 
	filter_DecRegionDMG(object_interface object, int period,float ratio,int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DECREGIONDMG;
		if ( ratio <= 1.0 )
		{
			_ratio = 1.0 - ratio;
		}	
  		else
		{
			_ratio = 0.1;
		}
    
	}
	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
		
  		if ( msg.attack_attr < 0 && !attacker.IsPlayerClass())
  		{
    		msg.physic_damage = (int)(msg.physic_damage * _ratio);
			msg.magic_damage[0] = (int)(msg.magic_damage[0]*_ratio);
			msg.magic_damage[1] = (int)(msg.magic_damage[1]*_ratio);
			msg.magic_damage[2] = (int)(msg.magic_damage[2]*_ratio);
			msg.magic_damage[3] = (int)(msg.magic_damage[3]*_ratio);
			msg.magic_damage[4] = (int)(msg.magic_damage[4]*_ratio);;
  		}
	}
	virtual void Heartbeat(int tick)
	{
		//timeout_filter::Heartbeat(tick);
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECREGIONDMG, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECREGIONDMG);
	}
};

//UltEA
class filter_IncAntiDefenseDegree : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			
	};
	int _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}

	filter_IncAntiDefenseDegree(){}
public:
	DECLARE_SUBSTANCE(filter_IncAntiDefenseDegree); 
	filter_IncAntiDefenseDegree(object_interface object, int value, int period, int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_INCANTIDEFENSEDEGREE;
		_value = value;
    
	}
	virtual void Heartbeat(int tick)
	{
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCANTIDEFENSEDEGREE, _timeout);
		_parent.IncAntiDefenseDegree(_value);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCANTIDEFENSEDEGREE);
		_parent.DecAntiDefenseDegree(_value);
	}
	
};

//UltEP
class filter_IncPlusMaxHP : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio1;
	float _ratio2;
	int _inc_maxhp;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio1;
		ar << _ratio2;
		ar << _inc_maxhp;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio1;
		ar >> _ratio2;
		ar >> _inc_maxhp;
		return true;
	}

	filter_IncPlusMaxHP(){}
public:
	DECLARE_SUBSTANCE(filter_IncPlusMaxHP); 
	filter_IncPlusMaxHP(object_interface object, int period,float ratio1 ,float ratio2,int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_INCPLUSMAXHP;
		_ratio1 = ratio1;
        _ratio2 = ratio2;
        _inc_maxhp = 0;
    
	}
	virtual void Heartbeat(int tick)
	{
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_INCPLUSMAXHP);
  		_parent.InsertTeamVisibleState(HSTATE_INCPLUSMAXHP, _timeout);
  		_inc_maxhp = (int)(_parent.GetExtendProp().max_hp * _ratio1);
  		_parent.EnhancePlusMaxHP(_inc_maxhp);
  		_parent.Heal((int)(_parent.GetExtendProp().max_hp * _ratio2));
	}

	void OnRelease()
	{
		_parent.ImpairPlusMaxHP(_inc_maxhp);
  		_parent.DecVisibleState(VSTATE_INCPLUSMAXHP);
		_parent.RemoveTeamVisibleState(HSTATE_INCPLUSMAXHP);
	}
};
//UltMC
class filter_Auracurse4asn : public filter_Aurabase		//�����??
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	float _range;
	int _skill;
	int _level;
	
	virtual bool Save(archive & ar)
	{
		filter_Aurabase::Save(ar);
		ar << _range << _skill << _level;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Aurabase::Load(ar);
		ar >> _range >> _skill >> _level;
		return true;
	}
	
	filter_Auracurse4asn(){}
public:
	DECLARE_SUBSTANCE(filter_Auracurse4asn);
	filter_Auracurse4asn(object_interface object, int period, float range, int skill, int level, int step)
			:filter_Aurabase(object, period, FILTER_MASK, step),_range(range),_skill(skill),_level(level)
	{
		_filter_id = FILTER_AURACURSE4ASN;
		_range = range;
		_skill = skill;
		_level = level;					
	}
	virtual void DoAura()
	{
		enchant_msg	msg;
		memset(&msg,0,sizeof(msg));
		msg.attack_range  = _range;
		msg.skill = _skill;
		msg.skill_level = _level;
		msg.helpful = 1;
		msg.skill_modify[0] = _t0;
		msg.skill_modify[1] = _t1;
		msg.skill_modify[2] = _t2;

		_parent.SetAuraAttackState();
		if ( _parent.IsInTeam())
  		{
    		_parent.TeamEnchant( msg, false);
  		}
  		else
  		{
    		_parent.Enchant( _parent.GetSelfID(), msg);
  		}
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_AURACURSE4ASN, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_AURACURSE4ASN);
	}	

};
//UltESP
class filter_Incmagic4 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio;
	int _add_magic;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _add_magic;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _add_magic;
		return true;
	}

	filter_Incmagic4(){}
public:
	DECLARE_SUBSTANCE(filter_Incmagic4); 
	filter_Incmagic4(object_interface object, int period,float ratio, int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_INCMAGIC4;
		_ratio = ratio;
        _add_magic = 0;
    
	}
	virtual void Heartbeat(int tick)
	{
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
  		_parent.InsertTeamVisibleState(HSTATE_INCMAGIC4, _timeout);
  		_add_magic = (int)(_parent.GetSoulPower() * _ratio);
  		_parent.EnhancePlusMagicDamage(_add_magic);
  		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCMAGIC4);
		_parent.ImpairPlusMagicDamage(_add_magic);
  		_parent.UpdateMagicData();	
	}
};
//UltESP
class filter_Decsoul : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio;
	int _dec_soul;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _dec_soul;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _dec_soul;
		return true;
	}

	filter_Decsoul(){}
public:
	DECLARE_SUBSTANCE(filter_Decsoul); 
	filter_Decsoul(object_interface object, int period,float ratio, int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DECSOUL;
		_ratio = ratio;
        _dec_soul = 0;
    
	}
	virtual void Heartbeat(int tick)
	{
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_DECSOUL);
  		_parent.InsertTeamVisibleState(HSTATE_DECSOUL,_timeout);
  		_dec_soul = (int)(_parent.GetSoulPower() * _ratio);
  		_parent.ImpairSoulPower(_dec_soul);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_DECSOUL);
		_parent.RemoveTeamVisibleState(HSTATE_DECSOUL);
		_parent.EnhanceSoulPower(_dec_soul);
	}
};
//UltSK
class filter_Giantform : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _body_ratio;
	int _speed_ratio;
	int _attack_ratio;
	int _free_move;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _body_ratio;
		ar << _speed_ratio;
		ar << _attack_ratio;
		ar << _free_move;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _body_ratio;
		ar >> _speed_ratio;
		ar >> _attack_ratio;
		ar >> _free_move;
		return true;
	}

	filter_Giantform(){}
public:
	DECLARE_SUBSTANCE(filter_Giantform); 
	filter_Giantform(object_interface object, int period,float body_ratio, int speed_ratio, int attack_ratio, int free_move)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_GIANTFORM;
		_body_ratio = body_ratio;
        _speed_ratio = speed_ratio;
		_attack_ratio = attack_ratio;
		_free_move = free_move;
	}
	virtual void Heartbeat(int tick)
	{
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
  		_parent.InsertTeamVisibleState(HSTATE_GIANTFORM, _timeout);
  		_parent.SetBodyScale(_body_ratio);
		_parent.EnhanceScaleDamage(_attack_ratio);
		_parent.EnhanceSpeed(_speed_ratio);
  		if(_free_move)
		  {
		  	_parent.IncImmuneMask(IMMUNESLOW);
		  	_parent.IncImmuneMask(IMMUNEFIX);
			_parent.IncImmuneMask(IMMUNEDIZZY);
			_parent.IncImmuneMask(IMMUNESLEEP);
		  }
		_parent.UpdateAttackData();
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_GIANTFORM);
		_parent.ImpairScaleDamage(_attack_ratio);
		_parent.ImpairSpeed(_speed_ratio);
  		if(_free_move)
		  {
		  	_parent.DecImmuneMask(IMMUNESLOW);
		  	_parent.DecImmuneMask(IMMUNEFIX);
			_parent.DecImmuneMask(IMMUNEDIZZY);
			_parent.DecImmuneMask(IMMUNESLEEP);
		  }
		_parent.SetBodyScale(1);
		_parent.UpdateAttackData();
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}
};
//UltMS
class filter_Transdmg2pet : public timeout_filter // Novas Alterações
{
protected:
	enum 
	{
		FILTER_MASK =  FILTER_MASK_TRANSLATE_RECV_MSG | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio;
	XID _petid;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _petid;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _petid;
		return true;
	}

	filter_Transdmg2pet(){}
public:
	DECLARE_SUBSTANCE(filter_Transdmg2pet); 
	filter_Transdmg2pet(object_interface object, int period,float ratio,int mask, XID petid)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_TRANSDMG2PET;
		if ( ratio <= 1.0 )
		{
			_ratio = ratio;
		}	
  		else
		{
			_ratio = 1.0;
		}
		_petid = petid;
    
	}
	
	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
		attack_msg pet_msg;
		int mp2;
		int hp;
		A3DVECTOR pos;
		
		if(_petid != _parent.GetPetID())
		{
			_is_deleted = true;
		}
		else
		{
			if(_petid.IsValid() && _parent.QueryObject(_petid, pos, hp, mp2) == 1)
			{
				memcpy(&pet_msg, &msg, sizeof(pet_msg));
				msg.physic_damage = (int)((1 - _ratio) * msg.physic_damage);
				msg.magic_damage[0] = (int)((1 - _ratio) * msg.magic_damage[0]);
				msg.magic_damage[1] = (int)((1 - _ratio) * msg.magic_damage[1]);
				msg.magic_damage[2] = (int)((1 - _ratio) * msg.magic_damage[2]);
				msg.magic_damage[3] = (int)((1 - _ratio) * msg.magic_damage[3]);
				msg.magic_damage[4] = (int)((1 - _ratio) * msg.magic_damage[4]);

				pet_msg.physic_damage = (int)(pet_msg.physic_damage * _ratio);
				pet_msg.magic_damage[0]  = (int)(pet_msg.magic_damage[0] * _ratio);
				pet_msg.magic_damage[1]  = (int)(pet_msg.magic_damage[1] * _ratio);
				pet_msg.magic_damage[2]  = (int)(pet_msg.magic_damage[2] * _ratio);
				pet_msg.magic_damage[3]  = (int)(pet_msg.magic_damage[3] * _ratio);
				pet_msg.magic_damage[4]  = (int)(pet_msg.magic_damage[4] * _ratio);
				pet_msg.attack_range = 100;
				_parent.SendAttack(_petid, pet_msg);
			}
			else
			{
				_is_deleted = true;
			}
		}
	}

	virtual void Heartbeat(int tick)
	{
		//timeout_filter::Heartbeat(tick);
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_TRANSDMG2PET, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_TRANSDMG2PET);
	}
};
class filter_DecRegionDMG2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =  FILTER_MASK_TRANSLATE_RECV_MSG | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_DecRegionDMG2(){}
public:
	DECLARE_SUBSTANCE(filter_DecRegionDMG2); 
	filter_DecRegionDMG2(object_interface object, int period,float ratio,int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DECREGIONDMG2;
		if ( ratio <= 1.0 )
		{
			_ratio = 1.0 - ratio;
		}	
  		else
		{
			_ratio = 0.1;
		}
    
	}
	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
		
  		if ( msg.attack_attr < 0 && !attacker.IsPlayerClass())
  		{
    		msg.physic_damage = (int)(msg.physic_damage * _ratio);
			msg.magic_damage[0] = (int)(msg.magic_damage[0]*_ratio);
			msg.magic_damage[1] = (int)(msg.magic_damage[1]*_ratio);
			msg.magic_damage[2] = (int)(msg.magic_damage[2]*_ratio);
			msg.magic_damage[3] = (int)(msg.magic_damage[3]*_ratio);
			msg.magic_damage[4] = (int)(msg.magic_damage[4]*_ratio);;
  		}
	}
	virtual void Heartbeat(int tick)
	{
		//timeout_filter::Heartbeat(tick);
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECREGIONDMG2, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECREGIONDMG2);
	}
};

class filter_Loaddmg4master : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =    FILTER_MASK_UNIQUE  | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_BEFORE_DEATH
					
	};

	float _ratio;
	int _damagemax;
	int _range;
	int _hurt;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _damagemax << _range << _hurt;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _damagemax >> _range >> _hurt;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(!(msg._attack_state & AT_STATE_AURA_AND_RETORT))
		{
			_hurt += (int)((dmg.physic_damage + dmg.magic_damage[0] + dmg.magic_damage[1] + dmg.magic_damage[2] + dmg.magic_damage[3] + dmg.magic_damage[4]) * damage_adjust);
		}
		
	}

	filter_Loaddmg4master(){}
public:
	DECLARE_SUBSTANCE(filter_Loaddmg4master); 
	filter_Loaddmg4master(object_interface  object, int period, float ratio, int damagemax, int range, int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_LOADDMG4MASTER;
		_ratio = ratio;
		_damagemax = damagemax;
		_range = range;
		_hurt = 0;
	}

	void BeforeDeath(const XID & attacker, char attacker_mode)
	{

		int damage = ((int)(_hurt * _ratio));
		if (damage > _damagemax)
		{
			damage = _damagemax;
		}
		damage /= 2;
		attack_msg	msg;
		memset(&msg,0,sizeof(msg));
		msg.attack_range  = _range;
		msg.physic_damage = damage;
		msg.attack_rate	= (int)(_parent.GetExtendProp().attack); 
		msg.magic_damage[1] = damage;
		msg.attack_attr = 0;
		msg.force_attack = -1;
		msg.speed = 0;
		
		_parent.SetAuraAttackState();
		_parent.EnterCombatState();
		_parent.RegionAttack1(_parent.GetPos(), _range, msg, 0, XID(-1,-1));
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_LOADDMG4MASTER, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_LOADDMG4MASTER);
	}
	
};
//ULTRT
class filter_Decfardmg : public timeout_filter // Nova Alteração
{
protected:
	enum 
	{
		FILTER_MASK =  FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio1;
	float _ratio2;
	float _ratiofinish;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio1 << _ratio2 << _ratiofinish;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio1 >> _ratio2 >> _ratiofinish;
		return true;
	}

	filter_Decfardmg(){}
public:
	DECLARE_SUBSTANCE(filter_Decfardmg); 
	filter_Decfardmg(object_interface object, int period, float ratio1, float ratio2, int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DECFARDMG;
		if ( ratio1 <= 1.0 )
		{
			_ratio1 = 1.0 - ratio1;
		}	
  		else
		{
			_ratio1 = 0.1;
		}
		if ( ratio2 <= 1.0 )
		{
			_ratio2 = 1.0 - ratio2;
		}	
  		else
		{
			_ratio2 = 0.1;
		}
   
	}

	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);

			A3DVECTOR pos2;
			float body_size;
					 
			const XID & target1 = _parent.GetCurTargetID();
			_parent.QueryObject(target1, pos2, body_size);
			
		float dis = sqrt(_parent.GetPos().squared_distance(pos2));

		if(dis > 7.f)
		{
			_ratiofinish = _ratio2;
		} else {
			_ratiofinish = 1;
		}
	}

	void AdjustDamage(damage_entry& dmg,const XID& attacker, const attack_msg& msg, float damage_adjust)
	{
		if (msg.skill_id)
		{
			dmg.physic_damage *= _ratiofinish;
			dmg.magic_damage[0] *= _ratiofinish;
			dmg.magic_damage[1] *= _ratiofinish;
			dmg.magic_damage[2] *= _ratiofinish;
			dmg.magic_damage[3] *= _ratiofinish;
			dmg.magic_damage[4] *= _ratiofinish;
		}			

	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECFARDMG, _timeout);
		_parent.IncVisibleState(VSTATE_DECFARDMG);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECFARDMG);
		_parent.DecVisibleState(VSTATE_DECFARDMG);
	}
};
//UltTM
class filter_Decphysicalmagicaldefense : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	float _ratio1;
	float _ratio2;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio1;
		ar << _ratio2;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio1;
		ar >> _ratio2;
		return true;
	}

	filter_Decphysicalmagicaldefense(){}
public:
	DECLARE_SUBSTANCE(filter_Decphysicalmagicaldefense); 
	filter_Decphysicalmagicaldefense(object_interface object, int period,float ratio1 ,float ratio2,int mask)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_DECPHYSICALMAGICALDEFENSE;
		_ratio1 = ratio1;
        _ratio2 = ratio2;
    
	}
	virtual void Heartbeat(int tick)
	{
		_timeout -= tick;
		if(_timeout <= 0)
		{
			_is_deleted = 1;
		}
	}
	void OnAttach()
	{
  		_parent.InsertTeamVisibleState(HSTATE_DECPHYSICALMAGICALDEFENSE, _timeout);
  		_parent.ImpairScaleDefense(_ratio1);
		_parent.ImpairAllScaleResistance(_ratio2);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECPHYSICALMAGICALDEFENSE);
  		_parent.EnhanceScaleDefense(_ratio1);
		_parent.EnhanceAllScaleResistance(_ratio2);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
	}
};
//G17
class filter_MagicFrenetic : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_TRANSLATE_SEND_MSG  | FILTER_MASK_WEAK
	};

	int _probability;
	float _ratio;
	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _ratio;
		ar << _probability;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _ratio;
		ar >> _probability;
		return true;
	}

	

	filter_MagicFrenetic(){}
public:
	DECLARE_SUBSTANCE(filter_MagicFrenetic); 
	filter_MagicFrenetic(object_interface  object, float ratio, int probability)
			:filter(object,FILTER_MASK), _probability(probability), _ratio(ratio + 1.0)
	{
		_filter_id = FILTER_MAGICFRENETIC;
		//_ratio = ratio + 1.0;
		//_probability = probability;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if (msg.skill_id)
		{
			if( rand() % 100 <= _probability)
			{
				msg.physic_damage = (int)(msg.physic_damage*_ratio);
				msg.magic_damage[0] = (int)(msg.magic_damage[0]*_ratio);
				msg.magic_damage[1] = (int)(msg.magic_damage[1]*_ratio);
				msg.magic_damage[2] = (int)(msg.magic_damage[2]*_ratio);
				msg.magic_damage[3] = (int)(msg.magic_damage[3]*_ratio);
				msg.magic_damage[4] = (int)(msg.magic_damage[4]*_ratio);
				_parent.SendClientEnchantResult(_parent.GetSelfID(), 146, 1, false, 0, 0);
			}
		}
	}

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}
};


class filter_Decheal : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			|  FILTER_MASK_ADJUST_HEAL
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Decheal(){}
public:
	DECLARE_SUBSTANCE(filter_Decheal); 
	filter_Decheal(object_interface  object,int period, float ratio, int mask)
				        :timeout_filter(object,period,FILTER_MASK), _ratio(ratio)
	{
		_filter_id = FILTER_DECHEAL;
		if (ratio <= 1.f)
		{
			_ratio = 1.f - ratio;
		}
		else
		{
			_ratio = 0.f;
		}
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DECHEAL, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECHEAL);
	}
	void AdjustHeal(int& heal,char heal_type)
	{
			heal = (int)(heal * _ratio);
	}
};

class filter_Incsmitedamage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	int _ratio1;
	int _ratio2;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio1;
		ar << _ratio2;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio1;
		ar >> _ratio2;
		return true;
	}

	filter_Incsmitedamage(){}
public:
	DECLARE_SUBSTANCE(filter_Incsmitedamage); 
	filter_Incsmitedamage(object_interface object, int period,int ratio1 ,int ratio2)
				        :timeout_filter(object,period,FILTER_MASK), _ratio1(ratio1), _ratio2(ratio2)
	{
		_filter_id = FILTER_INCSMITEDAMAGE;
    
	}
	void OnAttach()
	{
  		_parent.InsertTeamVisibleState(HSTATE_INCSMITEDAMAGE, _timeout);
  		_parent.EnhanceCritDamage(_ratio1);
		_parent.EnhanceCrit(_ratio2);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCSMITEDAMAGE);
  		_parent.ImpairCritDamage(_ratio1);
		_parent.ImpairCrit(_ratio2);
	}
};

class filter_Decphysicalmagicaldefense2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
			
	};
	int _ratio1;
	int _ratio2;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio1;
		ar << _ratio2;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio1;
		ar >> _ratio2;
		return true;
	}

	filter_Decphysicalmagicaldefense2(){}
public:
	DECLARE_SUBSTANCE(filter_Decphysicalmagicaldefense2); 
	filter_Decphysicalmagicaldefense2(object_interface object, int period,int ratio1 ,int ratio2,int mask)
				        :timeout_filter(object,period,FILTER_MASK), _ratio1(ratio1), _ratio2(ratio2)
	{
		_filter_id = FILTER_DECPHYSICALMAGICALDEFENSE2;
	}

	void OnAttach()
	{
  		_parent.InsertTeamVisibleState(HSTATE_DECPHYSICALMAGICALDEFENSE2, _timeout);
  		_parent.ImpairScaleDefense(_ratio1);
		_parent.ImpairAllScaleResistance(_ratio2);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DECPHYSICALMAGICALDEFENSE2);
  		_parent.EnhanceScaleDefense(_ratio1);
		_parent.EnhanceAllScaleResistance(_ratio2);
		_parent.UpdateDefenseData();
		_parent.UpdateMagicData();
	}
};

class filter_Fastpray3 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Fastpray3(){}
public:
	DECLARE_SUBSTANCE(filter_Fastpray3); 
	filter_Fastpray3(object_interface  object, int period, int ratio, int mask)
				        :timeout_filter(object,period,FILTER_MASK), _ratio(ratio)
	{
		_filter_id = FILTER_FASTPRAY3;
				 
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FASTPRAY3, _timeout);
		_parent.GetSkillWrapper().DecPrayTime(_ratio);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FASTPRAY3);
		_parent.GetSkillWrapper().IncPrayTime(_ratio);
	}
};

class filter_Incdebuffdodge2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Incdebuffdodge2(){}
public:
	DECLARE_SUBSTANCE(filter_Incdebuffdodge2); 
	filter_Incdebuffdodge2(object_interface  object,int period, int ratio, int mask)
				        :timeout_filter(object,period,FILTER_MASK), _ratio(ratio)
	{
		_filter_id = FILTER_INCDEBUFFDODGE2;
				 
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCDEBUFFDODGE2, _timeout);
		_parent.EnhanceDebuffDodge(_ratio);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCDEBUFFDODGE2);
		_parent.ImpairDebuffDodge(_ratio);
	}
};

class filter_Incdamagedodge2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK =   FILTER_MASK_HEARTBEAT | FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_Incdamagedodge2(){}
public:
	DECLARE_SUBSTANCE(filter_Incdamagedodge2); 
	filter_Incdamagedodge2(object_interface  object,int period, int ratio, int mask)
				        :timeout_filter(object,period,FILTER_MASK), _ratio(ratio)
	{
		_filter_id = FILTER_INCDAMAGEDODGE2;
				 
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCDAMAGEDODGE2, _timeout);
		_parent.EnhanceDamageDodge(_ratio);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_INCDAMAGEDODGE2);
		_parent.ImpairDamageDodge(_ratio);
	}
};



class filter_Debithurt : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_HEARTBEAT | FILTER_MASK_WEAK |FILTER_MASK_REMOVE_ON_DEATH |FILTER_MASK_ADJUST_DAMAGE
	};

	int _repay_period;
	int _state;
	int _total_hurt;
	int _per_repay;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _repay_period;
		ar << _state;
		ar << _total_hurt;
		ar << _per_repay;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _repay_period;
		ar >> _state;
		ar >> _total_hurt;
		ar >> _per_repay;
		return true;
	}

	filter_Debithurt(){}
public:
	DECLARE_SUBSTANCE(filter_Debithurt); 
	filter_Debithurt(object_interface  object,int period, int repay_period)
				        :timeout_filter(object,period,FILTER_MASK), _repay_period(repay_period)
	{
		_filter_id = FILTER_DEBITHURT;
		_state = 0;
		_total_hurt = 0;
		_per_repay = 0;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_DEBITHURT);
		if(_state)
		_parent.InsertTeamVisibleState(HSTATE_DEBITHURT2,_timeout);
		else
		_parent.InsertTeamVisibleState(HSTATE_DEBITHURT1,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_DEBITHURT);
		if(_state)
		_parent.RemoveTeamVisibleState(HSTATE_DEBITHURT2);
		else
		_parent.RemoveTeamVisibleState(HSTATE_DEBITHURT1);
	}

	virtual void Heartbeat(int tick)
	{
		int total_hurt;
		timeout_filter::Heartbeat(tick);
		if(!_state && _timeout <= _repay_period )
		{
			_parent.RemoveTeamVisibleState(HSTATE_DEBITHURT1);
			_parent.InsertTeamVisibleState(HSTATE_DEBITHURT2, _timeout);
			_state = 1;
			total_hurt = _total_hurt;
			if (_timeout > 0)
			{
				total_hurt /= _timeout;
				_per_repay = total_hurt;
				_total_hurt = 0;
			}
		}
		if (_state)
			{
				_parent.DecHP(_per_repay);
			}
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if (!_state)
		{
			_total_hurt += (int)((dmg.physic_damage + dmg.magic_damage[0] + dmg.magic_damage[1] +
			dmg.magic_damage[2] + dmg.magic_damage[3] + dmg.magic_damage[4]) * damage_adjust + 0.5);

		dmg.physic_damage = 0;
		dmg.magic_damage[0] = 0;
		dmg.magic_damage[1] = 0;
		dmg.magic_damage[2] = 0;
		dmg.magic_damage[3] = 0;
		dmg.magic_damage[4] = 0;
		}
	}
};

// Torre Solo novos Buffs


class filter_solo_IncAttackLevel : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE,
		MAX_STACK = 20,
	};

	int _attack_point;
	int _stacks;
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _attack_point << _stacks;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _attack_point >> _stacks;
		return true;
	}
	filter_solo_IncAttackLevel(){}
public:
	DECLARE_SUBSTANCE(filter_solo_IncAttackLevel); 
	filter_solo_IncAttackLevel(object_interface  object,int attack_point,int period):timeout_filter(object,period,FILTER_MASK),_attack_point(attack_point),_stacks(1)
	{
		_filter_id = FILTER_SOLO_ADDATTACKDEGREE;
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_solo_IncAttackLevel*>(f));
		filter_solo_IncAttackLevel* nf = (filter_solo_IncAttackLevel*) f;
		if(nf->_timeout)
		{
			++_stacks;
			if(_stacks > MAX_STACK)
			  _stacks = MAX_STACK;
			_timeout = GetTimeOut(nf);
			_parent.ImpairAttackDegree(_attack_point);
			_attack_point += nf->GetDefencePoint();
			_parent.EnhanceAttackDegree(_attack_point);
			_parent.ModifyTeamVisibleState(HSTATE_SOLO_ATTACKLEVEL, _stacks, _timeout);
			_parent.UpdateDefenseData();
			_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
		}
		
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SOLO_ATTACKLEVEL, _stacks, _timeout);
		_parent.EnhanceAttackDegree(_attack_point);
		_parent.UpdateDefenseData();
		_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_ATTACKLEVEL);
		_parent.ImpairAttackDegree(_attack_point);
		_parent.UpdateDefenseData();
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
	}

	int GetDefencePoint()
	{
		return _attack_point;
	}
};

class filter_solo_IncDefenseLevel : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE,
		MAX_STACK = 20,
	};

	int _defense_point;
	int _stacks;
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _defense_point << _stacks;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _defense_point >> _stacks;
		return true;
	}
	filter_solo_IncDefenseLevel(){}
public:
	DECLARE_SUBSTANCE(filter_solo_IncDefenseLevel); 
	filter_solo_IncDefenseLevel(object_interface  object,int defence_point,int period):timeout_filter(object,period,FILTER_MASK),_defense_point(defence_point),_stacks(1)
	{
		_filter_id = FILTER_SOLO_ADDDEFENCEDEGREE;
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_solo_IncDefenseLevel*>(f));
		filter_solo_IncDefenseLevel* nf = (filter_solo_IncDefenseLevel*) f;
		if(nf->_timeout)
		{
			++_stacks;
			if(_stacks > MAX_STACK)
			  _stacks = MAX_STACK;
			_timeout = GetTimeOut(nf);
			_parent.ImpairDefendDegree(_defense_point);
			_defense_point += nf->GetDefencePoint();
			_parent.EnhanceDefendDegree(_defense_point);
			_parent.ModifyTeamVisibleState(HSTATE_SOLO_DEFENSELEVEL, _stacks, _timeout);
			_parent.UpdateDefenseData();
			_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
		}
		
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_SOLO_DEFENSELEVEL, _stacks, _timeout);
		_parent.EnhanceDefendDegree(_defense_point);
		_parent.UpdateDefenseData();
		_parent.SetSoloChallengeFilterData(_filter_id, _stacks);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_SOLO_DEFENSELEVEL);
		_parent.ImpairDefendDegree(_defense_point);
		_parent.UpdateDefenseData();
		_parent.SetSoloChallengeFilterData(_filter_id, 0);
	}

	int GetDefencePoint()
	{
		return _defense_point;
	}
};

// Ultimate do Paladino
// Buff mp reduzido + redução de defesa + aumento de velocidade Paladino 


class filter_UltimatePaladin : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_MANA_COST | FILTER_MASK_ADJUST_DAMAGE
	};

	int _ratio;
	int _amount;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _amount;		
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _amount;
		return true;
	}
	
	// Reduce
	
	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _amount;
		dmg.magic_damage[0] *= _amount;
		dmg.magic_damage[1] *= _amount;
		dmg.magic_damage[2] *= _amount;
		dmg.magic_damage[3] *= _amount;
		dmg.magic_damage[4] *= _amount;
	}
	
	
	filter_UltimatePaladin(){}
public:
	DECLARE_SUBSTANCE(filter_UltimatePaladin); 
	filter_UltimatePaladin(object_interface  object,int r,int amount, int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r),_amount(amount)
	{
		_filter_id = FILTER_ULTIMATEPALADIN;
		_amount = 1.0-amount;
	}		
	
					
	void Merge(filter *f) // Speed
	{
		
		ASSERT(dynamic_cast<filter_UltimatePaladin*>(f));
		filter_UltimatePaladin* nf = (filter_UltimatePaladin*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairSpeed(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceSpeed(_ratio);
			_parent.UpdateSpeedData();
			_parent.SendClientCurSpeed();
		}
		
		if (_timeout > 0 )
		{
			_parent.RemoveTeamVisibleState(HSTATE_REDUCESPEEDDDEBUFF);
			_parent.InsertTeamVisibleState(HSTATE_REDUCESPEEDDDEBUFF,_timeout);
		}
		
	}

	void OnAttach()
	{		
		// Icon
		_parent.InsertTeamVisibleState(HSTATE_REDUCESPEEDDDEBUFF,_timeout);

		// Speed 				
		_parent.EnhanceSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		
		// Freemove
		_parent.IncImmuneMask(IMMUNESLOW);
		_parent.IncImmuneMask(IMMUNEFIX);
		_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.IncImmuneMask(IMMUNESLEEP);	
	}

	void OnRelease()
	{
		// Icon
		_parent.RemoveTeamVisibleState(HSTATE_REDUCESPEEDDDEBUFF);
	
		// Speed 		
		_parent.ImpairSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
		
		// Free Move		
		_parent.DecImmuneMask(IMMUNESLOW);
		_parent.DecImmuneMask(IMMUNEFIX);
		_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.DecImmuneMask(IMMUNESLEEP);

	}


	int GetRatio()
	{
		return _ratio;
	}
	
	
};


class filter_AttackplusAtr : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}
	filter_AttackplusAtr(){}
public:
	DECLARE_SUBSTANCE(filter_AttackplusAtr); 
	filter_AttackplusAtr(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_value(r)
	{
		_filter_id = FILTER_ATTACKPLUSATR;
	}
	
	void OnAttach()
	{
		//_parent.InsertTeamVisibleState(HSTATE_DISTANCEULTIMATE2);
		_parent.InsertTeamVisibleState(HSTATE_ADDATTACKDEGREE,_timeout);
		//_parent.IncVisibleState(VSTATE_NEWBUFF32); // Efeito Branco
		_parent.EnhanceAttackDegree(_value);
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		//_parent.RemoveTeamVisibleState(HSTATE_DISTANCEULTIMATE2);
		_parent.RemoveTeamVisibleState(HSTATE_ADDATTACKDEGREE);
		//_parent.DecVisibleState(VSTATE_NEWBUFF32); // Efeito Branco
		_parent.ImpairAttackDegree(_value);
		_parent.SendClientAttackData();
	}

	int GetValue()
	{
		return _value;
	}
};

class filter_AddPraga : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSLATE_RECV_MSG
	};

	XID _target;
	float _ratio;
	float _range;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _target << _ratio << _range << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _target >> _ratio >> _range >> _counter;
		return true;
	}
	filter_AddPraga(){}
public:
	DECLARE_SUBSTANCE(filter_AddPraga); 
	filter_AddPraga(object_interface  object,int period,const XID & target, float ratio,float range)
			:timeout_filter(object,period,FILTER_MASK),_target(target),_ratio(ratio),_range(range),_counter(0)
	{
		_filter_id = FILTER_ADDPRAGA;
	}

	void OnAttach() 
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF33);
		_parent.InsertTeamVisibleState(HSTATE_DISTANCEULTIMATE2,_timeout);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF33);
		_parent.RemoveTeamVisibleState(HSTATE_DISTANCEULTIMATE2);
	}
	
	void TranslateRecvAttack(const XID & attacker,attack_msg & msg)
	{
			A3DVECTOR pos;
			float body_size;
		
			attack_msg	newmsg;
			memset(&newmsg,0,sizeof(newmsg));

			newmsg.attack_range = _range;
			newmsg.physic_damage	= (int)(msg.physic_damage);
			newmsg.attack_rate	= 1000; 
			newmsg.magic_damage[0]	= (int)(msg.magic_damage[0]);
			newmsg.magic_damage[1]	= (int)(msg.magic_damage[1]);
			newmsg.magic_damage[2]	= (int)(msg.magic_damage[2]);
			newmsg.magic_damage[3]	= (int)(msg.magic_damage[3]);
			newmsg.magic_damage[4]	= (int)(msg.magic_damage[4]);
			newmsg.attack_attr	= attack_msg::MAGIC_ATTACK;
			newmsg.force_attack = _parent.GetForceAttack();
			newmsg.speed = msg.speed;

		
			_parent.SetAuraAttackState();
			_parent.EnterCombatState();

			_parent.RegionAttack2(_parent.GetPos(), _range, newmsg, 0);
			
	}

};


class filter_skillplusAtr : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_DEBUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}
	filter_skillplusAtr(){}
public:
	DECLARE_SUBSTANCE(filter_skillplusAtr); 
	filter_skillplusAtr(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_value(r)
	{
		_filter_id = FILTER_SKILLPLUSATR;
	}
	
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_DISTANCEULTIMATE1,_timeout);
		_parent.IncVisibleState(VSTATE_NEWBUFF32); // Efeito Branco
		_parent.EnhanceSkillDamage2(_value);
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_DISTANCEULTIMATE1);
		_parent.DecVisibleState(VSTATE_NEWBUFF32); // Efeito Branco
		_parent.ImpairSkillDamage2(_value);
		_parent.SendClientAttackData();
	}

	int GetValue()
	{
		return _value;
	}
};

class filter_Shattereddream2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH 
						| FILTER_MASK_NOSAVE | FILTER_MASK_TRANSLATE_SEND_MSG 
	};
	
	int _distance;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _distance;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _distance;
		return true;
	}

	filter_Shattereddream2(){}
public:
	DECLARE_SUBSTANCE(filter_Shattereddream2); 
	filter_Shattereddream2(object_interface object,int period, int distance)
			:timeout_filter(object,period,FILTER_MASK),_distance(distance)
	{
		_filter_id = FILTER_SHATTEREDDREAM;
	}		

	virtual void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		A3DVECTOR pos2;
		float body_size;
					
		const XID & target1 = _parent.GetCurTargetID();
		_parent.QueryObject(target1, pos2, body_size);
		_parent.ShortJump(pos2);	
	}

	void OnAttach()
	{
		// Icon
		_parent.IncVisibleState(VSTATE_NEWBUFF49);
		_parent.InsertTeamVisibleState(HSTATE_SHATTEREDDREAM, _timeout);	
	
		_parent.EnhanceAttackRange(_distance);
		_parent.UpdateAttackData();
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		// Icon
		_parent.DecVisibleState(VSTATE_NEWBUFF49);
		_parent.RemoveTeamVisibleState(HSTATE_SHATTEREDDREAM);
		
		_parent.ImpairAttackRange(_distance);
		_parent.UpdateAttackData();
		_parent.SendClientAttackData();
	}

};

class filter_Incmagic3 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_Incmagic3(){}
public:
	DECLARE_SUBSTANCE(filter_Incmagic3); 
	filter_Incmagic3(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCMAGIC3;
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_Incmagic3*>(f));
		filter_Incmagic3* nf = (filter_Incmagic3*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleMagicDamage(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleMagicDamage(_ratio);
			_parent.UpdateMagicData();
		}
	}
	void OnAttach()
	{
		_parent.EnhanceScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.ImpairScaleMagicDamage(_ratio);
		_parent.UpdateMagicData();
	}
	int GetRatio()
	{
		return _ratio;
	}
};

// Novo Atributo 

class filter_HighestLevel : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_TRANSLATE_SEND_MSG  | FILTER_MASK_WEAK
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _ratio;
		ar << _probability;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _ratio;
		ar >> _probability;
		return true;
	}

	float _probability;
	float _ratio;

	filter_HighestLevel(){}
public:
	DECLARE_SUBSTANCE(filter_HighestLevel); 
	filter_HighestLevel(object_interface  object, float probability, float ratio)
			:filter(object,FILTER_MASK), _probability(probability), _ratio(ratio)
	{
		_filter_id = FILTER_HIGHESTLEVEL;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if((rand()%100)<=_probability && msg.skill_id)
		{		
			msg.physic_damage = (int)(msg.physic_damage*_ratio);
			msg.magic_damage[0] = (int)(msg.magic_damage[0]*_ratio);
			msg.magic_damage[1] = (int)(msg.magic_damage[1]*_ratio);
			msg.magic_damage[2] = (int)(msg.magic_damage[2]*_ratio);
			msg.magic_damage[3] = (int)(msg.magic_damage[3]*_ratio);
			msg.magic_damage[4] = (int)(msg.magic_damage[4]*_ratio);
			//_parent.SendClientEnchantResult(_parent.GetSelfID(), 146, 1, false, 0, 0);
		}
	}

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}
};

class filter_SetVersoSombrio01 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	float _ratio;
	int _point;
	float _newratio;


	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		ar << _newratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		ar >> _newratio;
		return true;
	}
	filter_SetVersoSombrio01(){}
public:
	DECLARE_SUBSTANCE(filter_SetVersoSombrio01); 
	filter_SetVersoSombrio01(object_interface  object,int r, int p, int period, float newratio = 1)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p)
	{
		_filter_id = FILTER_VERSOPALADIN;
		_newratio = newratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
			if(IS_PHYSIC_ATTACK(msg.attack_attr))
			{
				msg.attack_attr = attack_msg::PHYSIC_ATTACK;
				const item_prop & weapon = _parent.GetCurWeapon();
				msg.physic_damage = (int)(msg.physic_damage + _newratio * (weapon.damage_low+weapon.damage_high));

				 for (int i = 0; i < MAGIC_CLASS; ++i){
               		 msg.magic_damage[i] = 0;
            	 }     		
			}
	}
	

	void OnAttach()
	{
		_parent.GetPaladinWeaponLight(1);
		_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF1,_timeout);
		_parent.EnhanceScaleDamage(_ratio);
		_parent.UpdateAttackData();	
	}

	void OnRelease()
	{
		_parent.GetPaladinWeaponLight(0);
		_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF1);
		_parent.ImpairScaleDamage(_ratio);
		_parent.UpdateAttackData();
	}
};


class filter_SetVersoSombrio02 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	float _ratio;
	int _point;
	float _newratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;		
		ar << _point;
		ar << _newratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		ar >> _newratio;
		return true;
	}
	filter_SetVersoSombrio02(){}
public:
	DECLARE_SUBSTANCE(filter_SetVersoSombrio02); 
	filter_SetVersoSombrio02(object_interface  object,int r, int p, int period, float newratio = 1)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p)
	{
		_filter_id = FILTER_VERSOPALADIN;
		_newratio = newratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
		{
			
			if(IS_PHYSIC_ATTACK(msg.attack_attr) || !IS_PHYSIC_ATTACK(msg.attack_attr))
			{
				msg.attack_attr = attack_msg::MAGIC_ATTACK_GOLD;
				const item_prop & weapon = _parent.GetCurWeapon();
				msg.magic_damage[0] += (int)(msg.physic_damage + _newratio * (weapon.damage_low+weapon.damage_high));
				msg.physic_damage = 0;

				_parent.ModifyAP(5);
			}
		}


	void OnAttach()
	{
		_parent.GetPaladinWeaponLight(2);
		_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF4,_timeout);
		//_parent.EnhanceScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.GetPaladinWeaponLight(0);
		_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF4);
		//_parent.ImpairScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_SetVersoSombrio02*>(f));
		filter_SetVersoSombrio02* nf = (filter_SetVersoSombrio02*) f;
		_timeout = GetTimeOut(nf);
		if(_newratio!=nf->GetRatio())
		{
			_newratio = nf->GetRatio();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF4);
			_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF4, _timeout);
		}
				
	}

	float GetRatio()
	{
		return _newratio;
	}

};

class filter_SetVersoSombrio03 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_MERGE
	};

	float _ratio;
	int _point;
	float _newratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		ar << _newratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		ar >> _newratio;
		return true;
	}
	filter_SetVersoSombrio03(){}
public:
	DECLARE_SUBSTANCE(filter_SetVersoSombrio03); 
	filter_SetVersoSombrio03(object_interface  object,int r, int p, int period, float newratio = 1)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p)
	{
		_filter_id = FILTER_VERSOPALADIN;
		_newratio = newratio;
	}

	// Recuperação de HP 
		
		void Merge(filter *f)
		{		
		ASSERT(dynamic_cast<filter_SetVersoSombrio03*>(f));
		filter_SetVersoSombrio03* nf = (filter_SetVersoSombrio03*)f;
		if(nf->GetInc() == _point)
		{
			_timeout = GetTimeOut(nf);
		}
		else if(nf->GetInc() > _point)
		{
			_parent.ImpairHpSteal(_point);
			_point = nf->GetInc();
			_parent.EnhanceHpSteal(_point);
			_timeout = GetTimeOut(nf);
		}

		if(_newratio!=nf->GetRatio())
		{
			_newratio = nf->GetRatio();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF4);
			_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF4, _timeout);
		}		
		}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
			if(IS_PHYSIC_ATTACK(msg.attack_attr))
			{
				msg.attack_attr = attack_msg::MAGIC_ATTACK_WOOD;
				const item_prop & weapon = _parent.GetCurWeapon();
				msg.magic_damage[1] += (int)(msg.physic_damage + _newratio * (weapon.damage_low+weapon.damage_high));
				msg.physic_damage = 0;
			}
	}


	void OnAttach()
	{
		_parent.GetPaladinWeaponLight(3);
		_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF2,_timeout);
		_parent.EnhanceHpSteal(_point);
		//_parent.EnhanceScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.GetPaladinWeaponLight(0); 
		_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF2);
		_parent.ImpairHpSteal(_point);
		//_parent.ImpairScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	float GetRatio()
	{
		return _newratio;
	}

	int GetInc()
	{
			return _point;	
	}
};

class filter_SetVersoSombrio04 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	float _ratio;
	int _point;
	int _prob;
	float _newratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		ar << _prob;
		ar << _newratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		ar >> _prob;
		ar >> _newratio;
		return true;
	}
	filter_SetVersoSombrio04(){}
public:
	DECLARE_SUBSTANCE(filter_SetVersoSombrio04); 
	filter_SetVersoSombrio04(object_interface  object,int r, int p, int period, float prob = 100, float newratio = 1)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p), _prob(prob)
	{
		_filter_id = FILTER_VERSOPALADIN;
		_newratio = newratio;
	}


	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
			if(IS_PHYSIC_ATTACK(msg.attack_attr) || !IS_PHYSIC_ATTACK(msg.attack_attr))
			{
				msg.attack_attr = attack_msg::MAGIC_ATTACK_WATER;
				const item_prop & weapon = _parent.GetCurWeapon();
				msg.magic_damage[2] += (int)(msg.physic_damage + _newratio * (weapon.damage_low+weapon.damage_high));
				msg.physic_damage = 0;
			}

			if((rand()%100)<5)
			{
				int skill_id = 18000;
				SkillKeeper skill = Skill::Create(skill_id);
				if ( skill )
				{
					if ( skill->DoEnchant() )
					{
						msg.attached_skill.skill = skill_id;
						msg.attached_skill.level = 1;
					}
					//skill->Destroy();
				}			
			}
	}

	void OnAttach()
	{
		_parent.GetPaladinWeaponLight(4); // 
		_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF3,_timeout);
		//_parent.EnhanceScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.GetPaladinWeaponLight(0); 
		_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF3);
		//_parent.ImpairScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_SetVersoSombrio04*>(f));
		filter_SetVersoSombrio04* nf = (filter_SetVersoSombrio04*) f;
		_timeout = GetTimeOut(nf);
		if(_newratio!=nf->GetRatio())
		{
			_newratio = nf->GetRatio();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF3);
			_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF3, _timeout);
		}
				
	}

	float GetRatio()
	{
		return _newratio;
	}

};

class filter_SetVersoSombrio05 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	float _ratio;
	int _point;
	int _prob;
	float _newratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		ar << _prob;
		ar << _newratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		ar >> _prob;
		ar >> _newratio;
		return true;
	}
	filter_SetVersoSombrio05(){}
public:
	DECLARE_SUBSTANCE(filter_SetVersoSombrio05); 
	filter_SetVersoSombrio05(object_interface  object,int r, int p, int period, float prob = 100, float newratio = 1)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p), _prob(prob)
	{
		_filter_id = FILTER_VERSOPALADIN;
		_newratio = newratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
			if(IS_PHYSIC_ATTACK(msg.attack_attr) || !IS_PHYSIC_ATTACK(msg.attack_attr))
			{
				msg.attack_attr = attack_msg::MAGIC_ATTACK_FIRE;
				const item_prop & weapon = _parent.GetCurWeapon();
				msg.magic_damage[3] += (int)(msg.physic_damage + _newratio * (weapon.damage_low+weapon.damage_high));
				msg.physic_damage = 0;
			}

			if((rand()%100)<50)
			{
				int skill_id = 18000;
				SkillKeeper skill = Skill::Create(skill_id);
				if ( skill )
				{
					if ( skill->DoEnchant() )
					{
						msg.attached_skill.skill = skill_id;
						msg.attached_skill.level = 3;
					}
					//skill->Destroy();
				}			
			}
	}

	void OnAttach()
	{
		_parent.GetPaladinWeaponLight(5);
		_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF5,_timeout);
		//_parent.EnhanceScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.GetPaladinWeaponLight(0); 
		_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF5);
		//_parent.ImpairScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_SetVersoSombrio05*>(f));
		filter_SetVersoSombrio05* nf = (filter_SetVersoSombrio05*) f;
		_timeout = GetTimeOut(nf);
		if(_newratio!=nf->GetRatio())
		{
			_newratio = nf->GetRatio();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF5);
			_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF5, _timeout);
		}
				
	}

	float GetRatio()
	{
		return _newratio;
	}

};


class filter_SetVersoSombrio06 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	float _ratio;
	int _point;
	int _prob;
	float _newratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		ar << _point;
		ar << _prob;
		ar << _newratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		ar >> _point;
		ar >> _prob;
		ar >> _newratio;
		return true;
	}
	filter_SetVersoSombrio06(){}
public:
	DECLARE_SUBSTANCE(filter_SetVersoSombrio06); 
	filter_SetVersoSombrio06(object_interface  object,int r, int p, int period, float prob = 100, float newratio = 1)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r), _point(p), _prob(prob)
	{
		_filter_id = FILTER_VERSOPALADIN;
		_newratio = newratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
			if(IS_PHYSIC_ATTACK(msg.attack_attr) || !IS_PHYSIC_ATTACK(msg.attack_attr))
			{				
				msg.attack_attr = attack_msg::MAGIC_ATTACK_EARTH;
				const item_prop & weapon = _parent.GetCurWeapon();
				msg.magic_damage[4] += (int)(msg.physic_damage + _newratio * (weapon.damage_low+weapon.damage_high));
				msg.physic_damage = 0;
			}

			if((rand()%100)<3)
			{
				int skill_id = 18000;
				SkillKeeper skill = Skill::Create(skill_id);
				if ( skill )
				{
					if ( skill->DoEnchant() )
					{
						msg.attached_skill.skill = skill_id;
						msg.attached_skill.level = 4;
					}
					//skill->Destroy();
				}			
			}
	}


	void OnAttach()
	{
		_parent.GetPaladinWeaponLight(6);
		_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF6,_timeout);
		//_parent.EnhanceScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.GetPaladinWeaponLight(0); 
		_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF6);
		//_parent.ImpairScaleMagicDamage(_ratio);
		//_parent.UpdateMagicData();
	}

		void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_SetVersoSombrio06*>(f));
		filter_SetVersoSombrio06* nf = (filter_SetVersoSombrio06*) f;
		_timeout = GetTimeOut(nf);
		if(_newratio!=nf->GetRatio())
		{
			_newratio = nf->GetRatio();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_SETICONBUFF6);
			_parent.InsertTeamVisibleState(HSTATE_SETICONBUFF6, _timeout);
		}
				
	}

	float GetRatio()
	{
		return _newratio;
	}

};

// skill 3261

class filter_Healnurse : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_ADJUST_DAMAGE
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _ratio1;
		ar << _ratio2;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _ratio1;
		ar >> _ratio2;
		return true;
	}

	float _ratio1; // сколько должно остаться жс, чтобы выполнить (0.4f)
	float _ratio2; // сколько жс нужно отхиллить 

	filter_Healnurse(){}
public:
	DECLARE_SUBSTANCE(filter_Healnurse); 
	filter_Healnurse(object_interface  object, float period, float ratio, float value, int mask)
			:timeout_filter(object,period,mask | FILTER_MASK) , _ratio1(ratio), _ratio2(value)
	{
		_filter_id = FILTER_HEALNURSE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_HEALNURSE, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_HEALNURSE);
	}
	
	void DoBless()
	{
		float hp = _parent.GetBasicProp().hp;
		if ( (_parent.GetExtendProp().max_hp * _ratio1) > hp  )
		{
			double heal_hp = _parent.GetExtendProp().max_hp * _ratio2;
			_parent.Heal(heal_hp);
			_parent.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			_is_deleted  = true;
		}
	}
	
	virtual void Heartbeat(int tick)
	{
		DoBless();
		timeout_filter::Heartbeat(tick);
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		DoBless();
	}

};

//skill 306 all instance retort filter


class filter_Retort3 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;
	float _ratio_skill;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio << _ratio_skill;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio >> _ratio_skill;
		return true;
	}

	filter_Retort3(){}
public:
	DECLARE_SUBSTANCE(filter_Retort3); 
	filter_Retort3(object_interface  object,float ratio, float ratio_skill, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_RETORT3;
		_ratio = ratio;
		_ratio_skill = ratio_skill;
	}
	
	void Merge(filter* f)
	{
		ASSERT(dynamic_cast<filter_Retort3*>(f));	
		filter_Retort3* nf = (filter_Retort3*) f;
		if(nf->GetValue() == _ratio)
		{
			if(GetTimeOut(nf) > _timeout) _timeout = GetTimeOut(nf);		
		}
		else if(nf->GetValue() > _ratio)
		{
			_timeout = GetTimeOut(nf);
			_ratio = nf->GetValue();
		}
		
		if (_timeout > 0)
		{
			_parent.RemoveTeamVisibleState(HSTATE_RETORT2);
			_parent.InsertTeamVisibleState(HSTATE_RETORT2, _timeout);
		}
		
	}

	void AdjustDamage(damage_entry & ent, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(msg.physic_damage >= 1000000) return;//��ֹ���������boss��������
		int damage = (int)(msg.physic_damage * (msg.skill_id ? _ratio_skill : _ratio));
		if(msg.short_range>0 || !IS_PHYSIC_ATTACK(msg.attack_attr) || damage <= 1)	
			return;
		attack_msg	ret;
		memset(&ret,0,sizeof(ret));
		ret.physic_damage	= damage;
		ret.attack_rate	= 1000;
		ret.force_attack = _parent.GetForceAttack();
		ret.attack_attr = attack_msg::MAGIC_ATTACK;
		ret.attack_range = msg.attack_range + 0.5;
		ret.speed = msg.speed;
		ret.skill_id = 1146;
		_parent.SetRetortState();
		_parent.Attack( attacker, ret, 0);
	}
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_RETORT);
		_parent.InsertTeamVisibleState(HSTATE_RETORT2, _timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_RETORT);
		_parent.RemoveTeamVisibleState(HSTATE_RETORT2);
	}
	
	float GetValue()
	{
		return _ratio;	
	}
	
};

// -------- elf lock --------------

class filter_Elflock : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	filter_Elflock(){}
public:
	DECLARE_SUBSTANCE(filter_Elflock); 
	filter_Elflock(object_interface  object,int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_ELFLOCK;
	}

	void OnAttach()
	{
		_parent.DenyElfSkillCmd();
		_parent.InsertTeamVisibleState(HSTATE_ELFLOCK,_timeout);
	}

	void OnRelease()
	{
		_parent.AllowElfSkillCmd();
		_parent.RemoveTeamVisibleState(HSTATE_ELFLOCK);
	}

};

//-- new sleep --

class filter_Sleep2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_NOSAVE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_DO_DAMAGE
	};

	filter_Sleep2(){}
public:
	DECLARE_SUBSTANCE(filter_Sleep2); 
	filter_Sleep2(object_interface  object,int period,int mask)
				        :timeout_filter(object,period,FILTER_MASK|mask)
	{
		_filter_id = FILTER_SLEEP2;
	}

	void OnAttach()
	{
		_parent.IncIdleSealMode(MODE_INDEX_SLEEP);
		_parent.IncVisibleState(VSTATE_SLEEP);
		_parent.InsertTeamVisibleState(HSTATE_SLEEP,_timeout);
	}

	void OnRelease()
	{
		_parent.DecIdleSealMode(MODE_INDEX_SLEEP);
		_parent.DecVisibleState(VSTATE_SLEEP);
		_parent.RemoveTeamVisibleState(HSTATE_SLEEP);
	}

	void DoDamage(const damage_entry & dmg)
	{
		_is_deleted = true;
	}
};

// -- glyph other skills --

// "Длительный урон стихией металла, активируется особым умением"
class filter_Othergold : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG 
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _plus;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _plus;
		return true;
	}

	float _skill_begin;
	float _skill_count;
	float _plus;

	filter_Othergold(){}
public:
	DECLARE_SUBSTANCE(filter_Othergold); 
	filter_Othergold(object_interface  object, float period, float ratio, float value, float amount )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _plus(amount)
	{
		_filter_id = FILTER_OTHERGOLD;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERGOLD, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERGOLD);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i <= _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				msg.magic_damage[0] += _plus;
				break;
			}
		}
	}
	
};

// "Длительный урон стихией дерева, активируется особым умением"
class filter_Otherwood : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _plus;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _plus;
		return true;
	}

	float _skill_begin;
	float _skill_count;
	float _plus;

	filter_Otherwood(){}
public:
	DECLARE_SUBSTANCE(filter_Otherwood); 
	filter_Otherwood(object_interface  object, float period, float ratio, float value, float amount )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _plus(amount)
	{
		_filter_id = FILTER_OTHERWOOD;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERWOOD, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERWOOD);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i <= _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				msg.magic_damage[1] += _plus;
				break;
			}
		}
	}
	
};

// "Длительный урон стихией воды, активируется особым умением"
class filter_Otherwater : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _plus;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _plus;
		return true;
	}

	float _skill_begin;
	float _skill_count;
	float _plus;

	filter_Otherwater(){}
public:
	DECLARE_SUBSTANCE(filter_Otherwater); 
	filter_Otherwater(object_interface  object, float period, float ratio, float value, float amount )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _plus(amount)
	{
		_filter_id = FILTER_OTHERWATER;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERWATER, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERWATER);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i <= _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				msg.magic_damage[2] += _plus;
				break;
			}
		}
	}
	
};

// "Длительный урон стихией огня, активируется особым умением"
class filter_Otherfire : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _plus;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _plus;
		return true;
	}

	float _skill_begin;
	float _skill_count;
	float _plus;

	filter_Otherfire(){}
public:
	DECLARE_SUBSTANCE(filter_Otherfire); 
	filter_Otherfire(object_interface  object, float period, float ratio, float value, float amount )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _plus(amount)
	{
		_filter_id = FILTER_OTHERFIRE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERFIRE, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERFIRE);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i <= _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				msg.magic_damage[3] += _plus;
				break;
			}
		}
	}
	
};

// "Длительный урон стихией земли, активируется особым умением"
class filter_Othersoil : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _plus;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _plus;
		return true;
	}

	float _skill_begin;
	float _skill_count;
	float _plus;

	filter_Othersoil(){}
public:
	DECLARE_SUBSTANCE(filter_Othersoil); 
	filter_Othersoil(object_interface  object, float period, float ratio, float value, float amount )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _plus(amount)
	{
		_filter_id = FILTER_OTHERSOIL;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERSOIL, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERSOIL);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i <= _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				msg.magic_damage[4] += _plus;
				break;
			}
		}
	}
	
};

// "Увеличение дальности действия особого умения"
class filter_Otherrange : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _plus;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _plus;
		return true;
	}

	float _skill_begin;
	float _skill_count;
	float _plus;

	filter_Otherrange(){}
public:
	DECLARE_SUBSTANCE(filter_Otherrange); 
	filter_Otherrange(object_interface  object, float period, float ratio, float value, float amount )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _plus(amount)
	{
		_filter_id = FILTER_OTHERRANGE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERRANGE, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERRANGE);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i <= _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				msg.attack_range += _plus;
				break;
			}
		}
	}
	
};

// "Увеличение урона от специальных умений"
class filter_Otherdamage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _plus;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _plus;
		return true;
	}

	float _skill_begin;
	float _skill_count;
	float _plus;

	filter_Otherdamage(){}
public:
	DECLARE_SUBSTANCE(filter_Otherdamage); 
	filter_Otherdamage(object_interface  object, float period, float ratio, float value, float amount )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _plus(amount)
	{
		_filter_id = FILTER_OTHERDAMAGE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERDAMAGE, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERDAMAGE);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i <= _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				msg.physic_damage += _plus;
				break;
			}
		}
	}
	
};

// "Мгновение Некоторые умения можно применять без восстановления"
class filter_Othercooldown : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSLATE_SEND_ENCHANT
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _activeflag;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _activeflag;
		return true;
	}

	float _skill_begin; // с какого скилла начинать откат
	float _skill_count; // сколько скиллов нужно откатить 
	bool _activeflag;

	filter_Othercooldown(){}
public:
	DECLARE_SUBSTANCE(filter_Othercooldown); 
	filter_Othercooldown(object_interface  object, float period, float ratio, float value )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _activeflag(false)
	{
		_filter_id = FILTER_OTHERCOOLDOWN;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERCOOLDOWN, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERCOOLDOWN);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i < _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				_activeflag = true;
			}
		}
	}
	
	void TranslateSendEnchant(const XID & target,enchant_msg & msg)
	{
		for (size_t i = 0; i < _skill_count; i++)
		{
			if ( msg.skill == (_skill_begin+i) )
			{
				_activeflag = true;
			}
		}
	}
	
	void Heartbeat(int tick)
	{
		timeout_filter::Heartbeat(tick);
		OnActive();
	}
	
	void OnActive()
	{
		if(_activeflag)
		{
			for (size_t i = 0; i < _skill_count; i++)
			{
				_parent.ResetCoolDown((_skill_begin+i)+COOLINGID_BEGIN);
			}
		}
		_activeflag = false;
	}

};


// "Сокращение подготовки особого умения"
class filter_Otherprayspeed : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSLATE_SEND_MSG
	};

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _skill_begin;
		ar << _skill_count;
		ar << _plus;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _skill_begin;
		ar >> _skill_count;
		ar >> _plus;
		return true;
	}

	float _skill_begin;
	float _skill_count;
	float _plus;

	filter_Otherprayspeed(){}
public:
	DECLARE_SUBSTANCE(filter_Otherprayspeed); 
	filter_Otherprayspeed(object_interface  object, float period, float ratio, float value, float amount )
			:timeout_filter(object, period, FILTER_MASK) , _skill_begin(ratio), _skill_count(value), _plus(amount)
	{
		_filter_id = FILTER_OTHERPRAYSPEED;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_OTHERPRAYSPEED, _timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_OTHERPRAYSPEED);
	}
	
	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		for (size_t i = 0; i <= _skill_count; i++)
		{
			if ( msg.skill_id == (_skill_begin+i) )
			{
				msg.speed -= _plus;
				if (msg.speed < 0)
				{
					msg.speed = 0;
				}
				break;
			}
		}
	}
	
};

//++++++++++++++++++++++++172++++++++++++++++++++++

class filter_AuracurseMonkey : public filter_Aurabase		//�����??
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT 
	};

	float _range;
	int _skill;
	int _level;
	
	virtual bool Save(archive & ar)
	{
		filter_Aurabase::Save(ar);
		ar << _range << _skill << _level;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter_Aurabase::Load(ar);
		ar >> _range >> _skill >> _level;
		return true;
	}
	
	filter_AuracurseMonkey(){}
public:
	DECLARE_SUBSTANCE(filter_AuracurseMonkey);
	filter_AuracurseMonkey(object_interface object, int period, float range, int skill, int level, int step = 1)
			:filter_Aurabase(object, period, FILTER_MASK, step),_range(range),_skill(skill),_level(level)
	{
		_filter_id = FILTER_AURACURSEMONKEY;					
	}

	virtual void DoAura()
	{
		enchant_msg	msg;
		memset(&msg,0,sizeof(msg));
		msg.attack_range  = _range;
		msg.skill = _skill;
		msg.skill_level = _level;
		msg.helpful = 0;
		msg.force_attack = _parent.GetForceAttack();
		msg.skill_modify[0] = _t0;
		//msg.skill_modify[1] = _t1;
		//msg.skill_modify[2] = _t2;

		_parent.SetAuraAttackState();
		_parent.EnterCombatState();
		_parent.RegionEnchant1(_parent.GetPos(), _range, msg, XID(-1,-1));
	}
	
	void OnAttach()
	{
		
	}

	void OnRelease()
	{
		
	}	

};

// New Monkey Skills

class filter_Monkeyform : public filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK
	};

	int _shape;
	int _inchp;
	int _incspeed;
	int _decattack;

	virtual bool Save(archive & ar)
	{
		filter::Save(ar);
		ar << _shape;
		ar << _inchp;
		ar << _incspeed;
		ar << _decattack;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		filter::Load(ar);
		ar >> _shape;
		ar >> _inchp;
		ar >> _incspeed;
		ar >> _decattack;
		return true;
	}
	filter_Monkeyform(){}
public:
	DECLARE_SUBSTANCE(filter_Monkeyform); 
	filter_Monkeyform(object_interface  object, int shape, int inchp, int incspeed, int decattack)
			:filter(object,FILTER_MASK),_shape(shape), _inchp(inchp),_incspeed(incspeed),_decattack(decattack)
	{
		_filter_id = FILTER_MONKEYFORM;
	}

	void OnAttach();

	void OnRelease();
};


class filter_MonkeyformUltimate : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _shape;
	int _inchp;
	int _incspeed;
	int _decattack;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _shape;
		ar << _inchp;
		ar << _incspeed;
		ar << _decattack;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _shape;
		ar >> _inchp;
		ar >> _incspeed;
		ar >> _decattack;
		return true;
	}
	filter_MonkeyformUltimate(){}
public:
	DECLARE_SUBSTANCE(filter_MonkeyformUltimate); 
	filter_MonkeyformUltimate(object_interface  object,int period, int shape, int inchp, int incspeed, int decattack)
			:timeout_filter(object,period,FILTER_MASK),_shape(shape), _inchp(inchp),_incspeed(incspeed),_decattack(decattack)
	{
		_filter_id = FILTER_MONKEYFORMULTI;
	}

	void OnAttach()
	{
		_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), FORM_CLASS);
		_parent.LockEquipment(true);
		_parent.EnhanceSpeed(_incspeed);
		_parent.UpdateSpeedData();
		_parent.UpdateAttackData();
		_parent.ChangeShape(_shape|(FORM_CLASS<<6));
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.GetSkillWrapper().EventChange(_parent, _parent.GetForm(), 0);
		_parent.LockEquipment(false);
		_parent.ImpairSpeed(_incspeed);
		_parent.UpdateSpeedData();
		_parent.UpdateAttackData();
		_parent.ChangeShape(0);
		_parent.SendClientCurSpeed();
	}
};

// Marca do Vento

class filter_Marcadovento : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_Marcadovento(){}
public:
	DECLARE_SUBSTANCE(filter_Marcadovento); 
	filter_Marcadovento(object_interface  object,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_MARCADOVENTO;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF101);
		_parent.InsertTeamVisibleState(HSTATE_MARCADOVENTO,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF101);
		_parent.RemoveTeamVisibleState(HSTATE_MARCADOVENTO);
	}

};

// Marca da Floresta 

class filter_Marcadafloresta : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_Marcadafloresta(){}
public:
	DECLARE_SUBSTANCE(filter_Marcadafloresta); 
	filter_Marcadafloresta(object_interface  object,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_MARCADAFLORESTA;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF102);
		_parent.InsertTeamVisibleState(HSTATE_MARCADAFLORESTA,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF102);
		_parent.RemoveTeamVisibleState(HSTATE_MARCADAFLORESTA);
	}

};

// Marca do Fogo 

class filter_Marcadofogo : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_Marcadofogo(){}
public:
	DECLARE_SUBSTANCE(filter_Marcadofogo); 
	filter_Marcadofogo(object_interface  object,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_MARCADOFOGO;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF103);
		_parent.InsertTeamVisibleState(HSTATE_MARCADOFOGO,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF103);
		_parent.RemoveTeamVisibleState(HSTATE_MARCADOFOGO);
	}

};

// Marca da Montanha 

class filter_Marcadamontanha : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_Marcadamontanha(){}
public:
	DECLARE_SUBSTANCE(filter_Marcadamontanha); 
	filter_Marcadamontanha(object_interface  object,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_MARCADAMONTANHA;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF104);
		_parent.InsertTeamVisibleState(HSTATE_MARCADAMONTANHA,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF104);
		_parent.RemoveTeamVisibleState(HSTATE_MARCADAMONTANHA);
	}

};


// Marca Yin 

class filter_MarcaYin : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_BUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_MarcaYin(){}
public:
	DECLARE_SUBSTANCE(filter_MarcaYin); 
	filter_MarcaYin(object_interface  object,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_MARCAYIN;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF105);
		_parent.InsertTeamVisibleState(HSTATE_MARCAYIN,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF105);
		_parent.RemoveTeamVisibleState(HSTATE_MARCAYIN);
	}

};

// Marca Yang 

class filter_MarcaYang : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_BUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_MarcaYang(){}
public:
	DECLARE_SUBSTANCE(filter_MarcaYang); 
	filter_MarcaYang(object_interface  object,int period,bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK), _insertvstate(insertvstate)
	{
		_filter_id = FILTER_MARCAYANG;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF106);
		_parent.InsertTeamVisibleState(HSTATE_MARCAYANG,_timeout);
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF106);
		_parent.RemoveTeamVisibleState(HSTATE_MARCAYANG);
	}

};

// Passiva de Defesa 

class filter_IncsformmonkeyDefense : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(attacker.IsPlayerClass())
		{
			dmg.physic_damage -= _value;
			dmg.magic_damage[0] -= _value;
			dmg.magic_damage[1] -= _value;
			dmg.magic_damage[2] -= _value;
			dmg.magic_damage[3] -= _value;
			dmg.magic_damage[4] -= _value;
		}
	}

	filter_IncsformmonkeyDefense(){}
public:
	DECLARE_SUBSTANCE(filter_IncsformmonkeyDefense); 
	filter_IncsformmonkeyDefense(object_interface  object,float value, int period = 9999999)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_MONKEYDEFENSE;
		_value = value;
	}

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}


};

// Todas as Habilidades

class filter_FreemoveMonkey : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}

	filter_FreemoveMonkey(){}
public:
	DECLARE_SUBSTANCE(filter_FreemoveMonkey); 
	filter_FreemoveMonkey(object_interface object, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FREEMOVEMONKEY;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF100);
		_parent.IncImmuneMask(IMMUNESLOW);
		_parent.IncImmuneMask(IMMUNEFIX);
		_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.IncImmuneMask(IMMUNESLEEP);
		_parent.IncImmuneMask(IMMUNEBREAK); // New
		_parent.IncImmuneMask(IMMUNEPALSY); // New
		_parent.IncImmuneMask(IMMUNECLEAR); // New
		_parent.IncImmuneMask(IMMUNEBLOODING); // New
		_parent.IncImmuneMask(IMMUNEDROP); // New
		_parent.IncImmuneMask(IMMUNEREPEL); // New
		_parent.IncImmuneMask(IMMUNECURSED); // New
		_parent.IncImmuneMask(IMMUNEWOUND); // New
		_parent.IncImmuneMask(IMMUNEWEAK); // New
		_parent.IncImmuneMask(IMMUNEALL); // New
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF100);
		_parent.DecImmuneMask(IMMUNESLOW);
		_parent.DecImmuneMask(IMMUNEFIX);
		_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.DecImmuneMask(IMMUNESLEEP);
		_parent.DecImmuneMask(IMMUNEBREAK); // New
		_parent.DecImmuneMask(IMMUNEPALSY); // New
		_parent.DecImmuneMask(IMMUNECLEAR); // New
		_parent.DecImmuneMask(IMMUNEBLOODING); // New
		_parent.DecImmuneMask(IMMUNEDROP); // New
		_parent.DecImmuneMask(IMMUNEREPEL); // New
		_parent.DecImmuneMask(IMMUNECURSED); // New
		_parent.DecImmuneMask(IMMUNEWOUND); // New
		_parent.DecImmuneMask(IMMUNEWEAK); // New
		_parent.DecImmuneMask(IMMUNEALL); // New
	}
};

class filter_FastswimPassive : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			|FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_FastswimPassive(){}
public:
	DECLARE_SUBSTANCE(filter_FastswimPassive);
	filter_FastswimPassive(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_FASTSWIMPASSIVE;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_FASTSWIM,_timeout);
		_parent.EnhanceSwimSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_FASTSWIM);
		_parent.ImpairSwimSpeed(_ratio);
		_parent.UpdateSpeedData();
		_parent.SendClientCurSpeed();
	}

};

// Buff 

class filter_MovimentodasMaos : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_ADJUST_DAMAGE
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_MovimentodasMaos(){}
public:
	DECLARE_SUBSTANCE(filter_MovimentodasMaos); 
	filter_MovimentodasMaos(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_MOVIMENTODASMAOS;
	}

	void AdjustDamage(damage_entry & dmg, const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		if(attacker.IsPlayerClass()) {
			dmg.physic_damage -= _ratio;
			dmg.magic_damage[0] -= _ratio;
			dmg.magic_damage[1] -= _ratio;
			dmg.magic_damage[2] -= _ratio;
			dmg.magic_damage[3] -= _ratio;
			dmg.magic_damage[4] -= _ratio;
		}	else {
			dmg.physic_damage -= _ratio / 4;
			dmg.magic_damage[0] -= _ratio / 4;
			dmg.magic_damage[1] -= _ratio / 4;
			dmg.magic_damage[2] -= _ratio / 4;
			dmg.magic_damage[3] -= _ratio / 4;
			dmg.magic_damage[4] -= _ratio / 4;
		}	
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_BLOQUEIADANOSDIRETOS,_timeout);
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_BLOQUEIADANOSDIRETOS);
	}
};

// Buff de Salto 

class filter_ShattereddreamMonkey : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_NOSAVE | FILTER_MASK_TRANSLATE_SEND_MSG 
	};
	
	int _tag;
	A3DVECTOR _pos;
	XID _target;
	int _distance;
	int _quantidade;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _tag << _target << _pos << _distance << _quantidade;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _tag >> _target >> _pos >> _distance >> _quantidade;
		return true;
	}

	filter_ShattereddreamMonkey(){}
public:
	DECLARE_SUBSTANCE(filter_ShattereddreamMonkey); 
	filter_ShattereddreamMonkey(object_interface object,int period, int distance, int quantidade, int tag, const XID & target, A3DVECTOR pos)
			:timeout_filter(object,period,FILTER_MASK),_tag(tag),_distance(distance),_quantidade(quantidade),_target(target),_pos(pos)
	{
		_filter_id = FILTER_SHATTEREDDREAMMONKEY;
	}		

	virtual void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(IS_PHYSIC_ATTACK(msg.attack_attr))
		{	

			A3DVECTOR pos2;
			float body_size;
			const XID target1 = _parent.GetCurTargetID();
			_parent.QueryObject(target1, pos2, body_size);
			_parent.ShortJump(pos2);

			_is_deleted = true;
		}	
		
	}

	void OnAttach()
	{
		// Icon
		
		_parent.InsertTeamVisibleState(HSTATE_SHATTEREDDREAMMONKEY,_timeout);	
	
		_parent.EnhanceAttackRange(_distance);
		_parent.UpdateAttackData();
		_parent.SendClientAttackData();
	}

	void OnRelease()
	{
		// Icon
		
		_parent.RemoveTeamVisibleState(HSTATE_SHATTEREDDREAMMONKEY);
		
		_parent.ImpairAttackRange(_distance);
		_parent.UpdateAttackData();
		_parent.SendClientAttackData();
	}

};

// Fé do Andarilho

class filter_FeMonkey : public timeout_filter // Nova Atualização
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		return true;
	}

	filter_FeMonkey(){}
public:
	DECLARE_SUBSTANCE(filter_FeMonkey); 
	filter_FeMonkey(object_interface object, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_FEMONKEY;
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_EVITAOPROXIMOEFEITO,_timeout);
		
		_parent.IncImmuneMask(IMMUNESLOW);
		_parent.IncImmuneMask(IMMUNEFIX);
		_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.IncImmuneMask(IMMUNESLEEP);
		_parent.IncImmuneMask(IMMUNEBREAK); // New
		_parent.IncImmuneMask(IMMUNEPALSY); // New
		_parent.IncImmuneMask(IMMUNECLEAR); // New
		_parent.IncImmuneMask(IMMUNEBLOODING); // New
		_parent.IncImmuneMask(IMMUNEDROP); // New
		_parent.IncImmuneMask(IMMUNEREPEL); // New
		_parent.IncImmuneMask(IMMUNECURSED); // New
		_parent.IncImmuneMask(IMMUNEWOUND); // New
		_parent.IncImmuneMask(IMMUNEWEAK); // New
		_parent.IncImmuneMask(IMMUNEALL); // New
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_EVITAOPROXIMOEFEITO);
		
		_parent.DecImmuneMask(IMMUNESLOW);
		_parent.DecImmuneMask(IMMUNEFIX);
		_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.DecImmuneMask(IMMUNESLEEP);
		_parent.DecImmuneMask(IMMUNEBREAK); // New
		_parent.DecImmuneMask(IMMUNEPALSY); // New
		_parent.DecImmuneMask(IMMUNECLEAR); // New
		_parent.DecImmuneMask(IMMUNEBLOODING); // New
		_parent.DecImmuneMask(IMMUNEDROP); // New
		_parent.DecImmuneMask(IMMUNEREPEL); // New
		_parent.DecImmuneMask(IMMUNECURSED); // New
		_parent.DecImmuneMask(IMMUNEWOUND); // New
		_parent.DecImmuneMask(IMMUNEWEAK); // New
		_parent.DecImmuneMask(IMMUNEALL); // New
	}

};

// Combo Monkey 

class filter_ComboMonkey : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	int _tag;
	A3DVECTOR _pos;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate << _tag << _pos;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate >> _tag >> _pos;
		return true;
	}

	filter_ComboMonkey(){}
public:
	DECLARE_SUBSTANCE(filter_ComboMonkey); 
	filter_ComboMonkey(object_interface  object,int period,int tagtest,const A3DVECTOR & positiontest, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_tag(tagtest),_pos(positiontest),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_COMBOMONKEY;

	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF99);		
		_parent.InsertTeamVisibleState(HSTATE_COMBOMARCAPINCEL,_timeout);

		_parent.SetNoLongJump(true);
		_parent.SetNoSpeedUp(true);
		
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF99);
		_parent.RemoveTeamVisibleState(HSTATE_COMBOMARCAPINCEL);

		_parent.SetNoLongJump(false);
		_parent.SetNoSpeedUp(false);
	}

	void Heartbeat(int tick)
	{
		XID targettest = _parent.GetCurTargetID();					

		timeout_filter::Heartbeat(tick);

	 	float dis = sqrt(_pos.squared_distance(_parent.GetPos()));

		if(dis > 4.5f) // Ocorre caso o jogador alcance 5 metros
		{			
			_parent.ShortJump(0.8f,false); // Causa roolback no personagem para trás
		}
	}

};


// Combo Yin e Yang 

class filter_ComboYinYang : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_ComboYinYang(){}
public:
	DECLARE_SUBSTANCE(filter_ComboYinYang); 
	filter_ComboYinYang(object_interface  object,int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_COMBOYINYANG;

	}

	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_NEWBUFF105);		
		_parent.InsertTeamVisibleState(HSTATE_BLOQUEIAVELOCIDADEVALORFIXO,_timeout);

		_parent.SetNoLongJump(true);
		_parent.SetNoSpeedUp(true);

		
	}

	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_NEWBUFF105);
		_parent.RemoveTeamVisibleState(HSTATE_BLOQUEIAVELOCIDADEVALORFIXO);

		_parent.SetNoLongJump(false);
		_parent.SetNoSpeedUp(false);

	}

};

// Combo Yin e Yang 2

class filter_ComboYinYang2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_DEBUFF | FILTER_MASK_HEARTBEAT 
						| FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	bool _insertvstate;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _insertvstate;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _insertvstate;
		return true;
	}

	filter_ComboYinYang2(){}
public:
	DECLARE_SUBSTANCE(filter_ComboYinYang2); 
	filter_ComboYinYang2(object_interface  object,int period, bool insertvstate=true)
				        :timeout_filter(object,period,FILTER_MASK),_insertvstate(insertvstate)
	{
		_filter_id = FILTER_COMBOYINYANG2;

	}

	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_NEWBUFF106);		
		_parent.InsertTeamVisibleState(HSTATE_BLOQUEIAVELOCIDADEVALORFIXO,_timeout);
		_parent.IncIdleSealMode(MODE_INDEX_SLEEP);
		_parent.SetNoLongJump(true);
		_parent.SetNoSpeedUp(true);

		
	}

	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_NEWBUFF106);
		_parent.RemoveTeamVisibleState(HSTATE_BLOQUEIAVELOCIDADEVALORFIXO);
		_parent.DecIdleSealMode(MODE_INDEX_SLEEP);
		_parent.SetNoLongJump(false);
		_parent.SetNoSpeedUp(false);

	}

};

class filter_ReduzDanoaDistancia : public timeout_filter
{
protected:
    enum 
    {
        FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_HEARTBEAT | FILTER_MASK_ADJUST_DAMAGE
    };

    float _ratio;
	A3DVECTOR _pos;

    virtual bool Save(archive & ar)
    {
        timeout_filter::Save(ar);
        ar << _ratio << _pos;
        return true;
    }

    virtual bool Load(archive & ar)
    {
        timeout_filter::Load(ar);
        ar >> _ratio >> _pos;
        return true;
    }
    filter_ReduzDanoaDistancia(){}
public:
    DECLARE_SUBSTANCE(filter_ReduzDanoaDistancia); 
    filter_ReduzDanoaDistancia(object_interface object, int period, float ratio, const A3DVECTOR & positiontest)
        :timeout_filter(object, period, FILTER_MASK), _ratio(1.f-ratio),_pos(positiontest)
    {
        _filter_id = FILTER_REDUZDANOADISTANCIA;
    }
      
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_REDUCEDISTANCEATK,_timeout);
		_parent.IncImmuneMask(IMMUNESLOW);
		_parent.IncImmuneMask(IMMUNEFIX);
		_parent.IncImmuneMask(IMMUNEDIZZY);
		_parent.IncImmuneMask(IMMUNESLEEP);
		_parent.IncImmuneMask(IMMUNEBREAK); // New
		_parent.IncImmuneMask(IMMUNEPALSY); // New
		_parent.IncImmuneMask(IMMUNECLEAR); // New
		_parent.IncImmuneMask(IMMUNEBLOODING); // New
		_parent.IncImmuneMask(IMMUNEDROP); // New
		_parent.IncImmuneMask(IMMUNEREPEL); // New
		_parent.IncImmuneMask(IMMUNECURSED); // New
		_parent.IncImmuneMask(IMMUNEWOUND); // New
		_parent.IncImmuneMask(IMMUNEWEAK); // New
		_parent.IncImmuneMask(IMMUNEALL); // New
	}

	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_REDUCEDISTANCEATK);
		_parent.DecImmuneMask(IMMUNESLOW);
		_parent.DecImmuneMask(IMMUNEFIX);
		_parent.DecImmuneMask(IMMUNEDIZZY);
		_parent.DecImmuneMask(IMMUNESLEEP);
		_parent.DecImmuneMask(IMMUNEBREAK); // New
		_parent.DecImmuneMask(IMMUNEPALSY); // New
		_parent.DecImmuneMask(IMMUNECLEAR); // New
		_parent.DecImmuneMask(IMMUNEBLOODING); // New
		_parent.DecImmuneMask(IMMUNEDROP); // New
		_parent.DecImmuneMask(IMMUNEREPEL); // New
		_parent.DecImmuneMask(IMMUNECURSED); // New
		_parent.DecImmuneMask(IMMUNEWOUND); // New
		_parent.DecImmuneMask(IMMUNEWEAK); // New
		_parent.DecImmuneMask(IMMUNEALL); // New
	}
    
	void AdjustDamage(damage_entry& dmg,const XID& attacker, const attack_msg& msg, float damage_adjust)
    {
		float dis = sqrt(_pos.squared_distance(_parent.GetPos()));

		if(dis < 8.f && _ratio > 0) // Ocorre caso o jogador alcance até 8 metros
		{			
			dmg.physic_damage *= _ratio;
			dmg.magic_damage[0] *= _ratio;
			dmg.magic_damage[1] *= _ratio;
			dmg.magic_damage[2] *= _ratio;
			dmg.magic_damage[3] *= _ratio;
			dmg.magic_damage[4] *= _ratio;
		}

	}
};

// 
class filter_InvincibleMonkeyNew : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};
	int _point;
	float _newpoint;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point << _newpoint;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point >> _newpoint;
		return true;
	}
	filter_InvincibleMonkeyNew(){}
public:
	DECLARE_SUBSTANCE(filter_InvincibleMonkeyNew); 
	filter_InvincibleMonkeyNew(object_interface  object,int inc,int period, float newpoint = 100)
				        :timeout_filter(object,period,FILTER_MASK),_point(inc),_newpoint(newpoint)
	{
		_filter_id = FILTER_INVICIBLEMONKEYNEW;
	}
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF108);
		_parent.InsertTeamVisibleState(HSTATE_MONTANHAVERDADEIRA,_timeout);
		_parent.IncImmuneMask(IMMUNEPHYSICAL|IMMUNEMETAL|IMMUNEWOOD|
				IMMUNEWATER|IMMUNEFIRE|IMMUNESOIL|IMMUNEALL);
				_parent.IncIdleSealMode(MODE_INDEX_ROOT);
	}
	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF108);
		_parent.RemoveTeamVisibleState(HSTATE_MONTANHAVERDADEIRA);
		_parent.DecImmuneMask(IMMUNEPHYSICAL|IMMUNEMETAL|IMMUNEWOOD|
				IMMUNEWATER|IMMUNEFIRE|IMMUNESOIL|IMMUNEALL);
				_parent.DecIdleSealMode(MODE_INDEX_ROOT);
	}
};

// Reduz Crítico

class filter_IncCritReduce2 : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};


	int _amount;
	
	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _amount;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _amount;
		return true;
	}

	filter_IncCritReduce2(){}
public:
	DECLARE_SUBSTANCE(filter_IncCritReduce2); 
	filter_IncCritReduce2(object_interface  object,int period, int amount)
				        :timeout_filter(object,period,FILTER_MASK),_amount(amount)
	{
		_filter_id = FILTER_INCCRITREDUCE2;
	}
	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_NEWBUFF15);
		_parent.InsertTeamVisibleState(HSTATE_MONTANHAVERDADEIRA,_timeout);
		_parent.EnhanceCritDamageReduce(_amount);
	}

	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_NEWBUFF15);
		_parent.RemoveTeamVisibleState(HSTATE_MONTANHAVERDADEIRA);
		_parent.ImpairCritDamageReduce(_amount);
	}
};


// Novas Habilidades 1.6.6 > 

class filter_IncAtkFToDefense : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_IncAtkFToDefense(){}
public:
	DECLARE_SUBSTANCE(filter_IncAtkFToDefense); 
	filter_IncAtkFToDefense(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCATTACKTODEFMF;
	}
	
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_IncAtkFToDefense*>(f));
		filter_IncAtkFToDefense* nf = (filter_IncAtkFToDefense*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleDefense(_ratio);
			_parent.EnhanceScaleDamage(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleDefense(_ratio);
			_parent.ImpairScaleDamage(_ratio);
			_parent.UpdateDefenseData();
			_parent.UpdateAttackData();
		}
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCATTACKTODEFMF,_timeout);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.ImpairScaleDamage(_ratio);
		_parent.UpdateDefenseData();
		_parent.UpdateAttackData();
	}

	void OnRelease()
	{
		_parent.ImpairScaleDefense(_ratio);
		_parent.EnhanceScaleDamage(_ratio);
		_parent.UpdateDefenseData();
		_parent.UpdateAttackData();
		_parent.RemoveTeamVisibleState(HSTATE_INCATTACKTODEFMF);
	}

	int GetRatio()
	{
		return _ratio;
	}
};


class filter_IncNewShieldMage : public timeout_filter // Imune
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}
	filter_IncNewShieldMage(){}
public:
	DECLARE_SUBSTANCE(filter_IncNewShieldMage); 
	filter_IncNewShieldMage(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCNEWSHIELDMAGE;
	}
	
	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF15);
		_parent.IncIdleSealMode(MODE_INDEX_ROOT);
		_parent.IncImmuneMask(IMMUNEPHYSICAL|IMMUNEMETAL|IMMUNEWOOD|
				IMMUNEWATER|IMMUNEFIRE|IMMUNESOIL|IMMUNEALL);

	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF15);
		_parent.DecIdleSealMode(MODE_INDEX_ROOT);
		_parent.DecImmuneMask(IMMUNEPHYSICAL|IMMUNEMETAL|IMMUNEWOOD|
				IMMUNEWATER|IMMUNEFIRE|IMMUNESOIL|IMMUNEALL);

	}


};

class filter_IncNewShieldMage2 : public timeout_filter // Escudo
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_DEBUFF | FILTER_MASK_TRANSFERABLE_DEBUFF
	};

	int _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}


	filter_IncNewShieldMage2(){}
public:
	DECLARE_SUBSTANCE(filter_IncNewShieldMage2); 
	filter_IncNewShieldMage2(object_interface  object,int r,int period)
				        :timeout_filter(object,period,FILTER_MASK),_ratio(r)
	{
		_filter_id = FILTER_INCNEWSHIELDMAGE2;
	}

	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_IncAtkFToDefense*>(f));
		filter_IncAtkFToDefense* nf = (filter_IncAtkFToDefense*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_parent.ImpairScaleDefense(_ratio);
			_ratio = nf->GetRatio();
			_parent.EnhanceScaleDefense(_ratio);
			_parent.UpdateDefenseData();

			_parent.EnhanceScaleResistance(0, _ratio);
			_parent.EnhanceScaleResistance(1, _ratio);
			_parent.EnhanceScaleResistance(2, _ratio);
			_parent.EnhanceScaleResistance(3, _ratio);
			_parent.EnhanceScaleResistance(4, _ratio);
			_parent.UpdateMagicData();
		}
	}

	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_INCNEWSHIELDMAGE,_timeout);
		_parent.EnhanceScaleDefense(_ratio);
		_parent.UpdateDefenseData();

		_parent.EnhanceScaleResistance(0, _ratio);
		_parent.EnhanceScaleResistance(1, _ratio);
		_parent.EnhanceScaleResistance(2, _ratio);
		_parent.EnhanceScaleResistance(3, _ratio);
		_parent.EnhanceScaleResistance(4, _ratio);
		_parent.UpdateMagicData();
	}

	void OnRelease()
	{
		_parent.ImpairScaleDefense(_ratio);
		_parent.UpdateDefenseData();

		_parent.ImpairScaleResistance(0, _ratio);
		_parent.ImpairScaleResistance(1, _ratio);
		_parent.ImpairScaleResistance(2, _ratio);
		_parent.ImpairScaleResistance(3, _ratio);
		_parent.ImpairScaleResistance(4, _ratio);
		_parent.UpdateMagicData();

		_parent.RemoveTeamVisibleState(HSTATE_INCNEWSHIELDMAGE);
	}

	int GetRatio()
	{
		return _ratio;
	}
	
};

// Escudo dos 4 Elementos 

class filter_SetNewShieldMage : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF
	};

	int _sratio;
	int _pratio;
	int _counter;
	int _appoint;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _sratio;
		ar << _pratio;
		ar << _counter;
		ar << _appoint;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _sratio;
		ar >> _pratio;
		ar >> _counter;
		ar >> _appoint;
		return true;
	}
	filter_SetNewShieldMage(){}
public:
	DECLARE_SUBSTANCE(filter_SetNewShieldMage); 
	filter_SetNewShieldMage(object_interface  object,int valueap, int s, int p, int period)
				        :timeout_filter(object,period,FILTER_MASK),_sratio(s),_pratio(p),_counter(0),_appoint(valueap)
	{
		_filter_id = FILTER_MAGICSHIELD;
	}

	void OnAttach()
	{
		_parent.IncVisibleState(VSTATE_NEWBUFF93);
		_parent.InsertTeamVisibleState(HSTATE_ARMORAPEX,_timeout);
		_parent.EnhanceScaleResistance(2, _sratio);
		_parent.EnhanceScaleResistance(3, _sratio);
		_parent.EnhanceScaleResistance(4, _sratio);
		_parent.EnhanceCrit(10);
		_parent.UpdateMagicData();
		_parent.EnhanceScaleDefense(_pratio);
		_parent.UpdateDefenseData();
	}

	void OnRelease()
	{
		_parent.DecVisibleState(VSTATE_NEWBUFF93);
		_parent.RemoveTeamVisibleState(HSTATE_ARMORAPEX);
		_parent.ImpairScaleResistance(2, _sratio);
		_parent.ImpairScaleResistance(3, _sratio);
		_parent.ImpairScaleResistance(4, _sratio);
		_parent.ImpairCrit(10);
		_parent.UpdateMagicData();
		_parent.ImpairScaleDefense(_pratio);
		_parent.UpdateDefenseData();
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;

		if(tick>=_timeout)
		{
			_parent.ModifyAP(_appoint*_counter);
			_counter = 0;	
		}
		else if(_counter>=3)
		{
			_parent.ModifyAP(_appoint);	
			_counter -= 3;
		}
		timeout_filter::Heartbeat(tick);
	}
};

// Buff da atiradora

class filter_SetBuffAtiradora : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_MERGE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
			| FILTER_MASK_TRANSLATE_SEND_MSG | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _ratio;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _ratio;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _ratio;
		return true;
	}

	filter_SetBuffAtiradora(){}
public:
	DECLARE_SUBSTANCE(filter_SetBuffAtiradora); 
	filter_SetBuffAtiradora(object_interface  object,float ratio, int period)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_NEWBUFFATIRADORA;
		_ratio = ratio;
	}

	void TranslateSendAttack(const XID & target, attack_msg & msg)
	{
		if(IS_PHYSIC_ATTACK(msg.attack_attr))
		{
			const item_prop & weapon = _parent.GetCurWeapon();
			msg.magic_damage[3] += (int)(_ratio * 0.5 * (weapon.damage_low+weapon.damage_high));
		}
	}

	void OnAttach()
	{
		//_parent.IncVisibleState(VSTATE_FIREBLADE);
		_parent.InsertTeamVisibleState(HSTATE_NEWBUFFATIRADORA,_timeout);
	}

	void OnRelease()
	{
		//_parent.DecVisibleState(VSTATE_FIREBLADE);
		_parent.RemoveTeamVisibleState(HSTATE_NEWBUFFATIRADORA);
	}
	void Merge(filter *f)
	{
		ASSERT(dynamic_cast<filter_SetBuffAtiradora*>(f));
		filter_SetBuffAtiradora* nf = (filter_SetBuffAtiradora*) f;
		_timeout = GetTimeOut(nf);
		if(_ratio!=nf->GetRatio())
		{
			_ratio = nf->GetRatio();
		}
	}
	float GetRatio()
	{
		return _ratio;
	}
};

// Buff do Paladino

class filter_SetBuffPaladin : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_WEAK | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
			| FILTER_MASK_TRANSFERABLE_BUFF | FILTER_MASK_NOSAVE
	};
	int _point;
	float _newpoint;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _point << _newpoint;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _point >> _newpoint;
		return true;
	}
	filter_SetBuffPaladin(){}
public:
	DECLARE_SUBSTANCE(filter_SetBuffPaladin); 
	filter_SetBuffPaladin(object_interface  object,int inc,int period, float newpoint = 100)
				        :timeout_filter(object,period,FILTER_MASK),_point(inc),_newpoint(newpoint)
	{
		_filter_id = FILTER_NEWBUFFPALADIN;
	}
	void OnAttach()
	{
		_parent.InsertTeamVisibleState(HSTATE_NEWBUFFPALADIN,_timeout);
		_parent.EnhanceCrit(_point);
		
		_parent.EnhanceScaleAttack(_newpoint);
		_parent.UpdateAttackData();
	}
	void OnRelease()
	{
		_parent.RemoveTeamVisibleState(HSTATE_NEWBUFFPALADIN);
		_parent.ImpairCrit(_point);

		_parent.ImpairScaleAttack(_newpoint);
		_parent.UpdateAttackData();
	}
};

// Nova Passiva de Defesa 

class filter_ReduceDefensePassive : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_HEARTBEAT | FILTER_MASK_REMOVE_ON_DEATH
					| FILTER_MASK_ADJUST_DAMAGE | FILTER_MASK_TRANSFERABLE_BUFF
	};

	float _value;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _value;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _value;
		return true;
	}

	void AdjustDamage(damage_entry & dmg,const XID & attacker, const attack_msg & msg, float damage_adjust)
	{
		dmg.physic_damage *= _value;
		dmg.magic_damage[0] *= _value;
		dmg.magic_damage[1] *= _value;
		dmg.magic_damage[2] *= _value;
		dmg.magic_damage[3] *= _value;
		dmg.magic_damage[4] *= _value;
	}

	filter_ReduceDefensePassive(){}
public:
	DECLARE_SUBSTANCE(filter_ReduceDefensePassive); 
	filter_ReduceDefensePassive(object_interface  object,float value, int period = 9999999)
				        :timeout_filter(object,period,FILTER_MASK)
	{
		_filter_id = FILTER_REDUCEDEFENSEPASSIVE;
		_value = 1.0-value;
	}

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}


};

class filter_ArmadilhaPvP : public timeout_filter
{
protected:
	enum 
	{
		FILTER_MASK = FILTER_MASK_UNIQUE | FILTER_MASK_BUFF | FILTER_MASK_REMOVE_ON_DEATH | FILTER_MASK_HEARTBEAT
	};

	float _range;
	int _counter;

	virtual bool Save(archive & ar)
	{
		timeout_filter::Save(ar);
		ar << _range << _counter;
		return true;
	}

	virtual bool Load(archive & ar)
	{
		timeout_filter::Load(ar);
		ar >> _range >> _counter;
		return true;
	}

	filter_ArmadilhaPvP(){}
public:
	DECLARE_SUBSTANCE(filter_ArmadilhaPvP); 
	filter_ArmadilhaPvP(object_interface  object,int period,float range)
				        :timeout_filter(object,period,FILTER_MASK),_range(range),_counter(0)
	{
		_filter_id = FILTER_ARMADILHAPVP;
	}

	virtual void Heartbeat(int tick)
	{
		_counter += tick;
		if(_counter>=3 || tick>=_timeout && _range < 12.f)
		{
			_parent.DetectInvisible(_range);

			attack_msg	msg;
			memset(&msg,0,sizeof(msg));
			msg.attack_range  = _range;
			msg.physic_damage = 0;
			msg.attack_rate	= (int)(_parent.GetExtendProp().attack); 
			msg.attack_attr = attack_msg::PVP_ENABLE;
			msg.force_attack = _parent.GetForceAttack();
			msg.speed = 0;		
			_parent.EnterCombatState();
			_parent.RegionAttack1(_parent.GetPos(), _range, msg, 0, XID(-1,-1));

			_counter -= 3;
		}

		timeout_filter::Heartbeat(tick);
	}

	void OnAttach()
	{
	}

	void OnRelease()
	{
	}
};


#undef IS_PHYSIC_ATTACK
#endif
