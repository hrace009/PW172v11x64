
#include "common/types.h"
#include "obj_interface.h"

#include "filter.h"
#include "playerwrapper.h"
#include "skillwrapper.h"
#include "skill.h"
#include "skillfilter.h"

namespace GNET
{

	bool IS_PVP(object_interface &obj, Skill *sk)
	{
		return (obj.IsPlayerClass() || obj.IsPet()) && (sk->GetPerformerid().IsPlayerClass() || sk->GetPerformerid().IsPet());
	}

	int CALC_PHYSIC_DMG(object_interface &object, Skill *skill, int pdmg, int ndmg)
	{
		int damage = 0;
		if (object.IsPlayerClass())
		{
			damage = object.CalcPhysicDamage(pdmg, skill->GetPlayerlevel());
			if (skill->GetPerformerid().IsPlayerClass())
				damage = damage >> 2;
		}
		else
		{
			damage = object.CalcPhysicDamage(ndmg, skill->GetPlayerlevel());
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}
		return damage;
	}

	template <int mt>
	int CALC_MAGIC_DMG(object_interface &object, Skill *skill, int pdmg, int ndmg)
	{
		int damage = 0;
		if (object.IsPlayerClass())
		{
			damage = object.CalcMagicDamage(mt, pdmg, skill->GetPlayerlevel());
			if (skill->GetPerformerid().IsPlayerClass())
				damage = damage >> 2;
		}
		else
		{
			damage = object.CalcMagicDamage(mt, ndmg, skill->GetPlayerlevel());
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}
		return damage;
	}

	float PlayerWrapper::GetIncgold() { return skillwrapper->GetSkillInc(0); }
	float PlayerWrapper::GetIncwood() { return skillwrapper->GetSkillInc(1); }
	float PlayerWrapper::GetIncwater() { return skillwrapper->GetSkillInc(2); }
	float PlayerWrapper::GetIncfire() { return skillwrapper->GetSkillInc(3); }
	float PlayerWrapper::GetIncearth() { return skillwrapper->GetSkillInc(4); }

	bool PlayerWrapper::SetIncgold(float inc) { return (skillwrapper && skillwrapper->SetSkillInc(0, inc)); }
	bool PlayerWrapper::SetIncwater(float inc) { return (skillwrapper && skillwrapper->SetSkillInc(2, inc)); }
	bool PlayerWrapper::SetIncwood(float inc) { return (skillwrapper && skillwrapper->SetSkillInc(1, inc)); }
	bool PlayerWrapper::SetIncfire(float inc) { return (skillwrapper && skillwrapper->SetSkillInc(3, inc)); }
	bool PlayerWrapper::SetIncearth(float inc) { return (skillwrapper && skillwrapper->SetSkillInc(4, inc)); }

	int PlayerWrapper::GetSkilllevel(SID id)
	{
		if (skillwrapper)
			return skillwrapper->GetSkillLevel(id);
		return 0;
	}

	int PlayerWrapper::GetProduceSkill()
	{
		if (skillwrapper)
			return skillwrapper->GetProduceSkill();
		return 0;
	}

	int PlayerWrapper::GetDynskillcounter()
	{
		if (skillwrapper && skill)
			return skillwrapper->GetDynSkillCounter(skill->GetId());
		else
			return 0;
	}

	int PlayerWrapper::GetLvalue()
	{
		if (skill)
			return skill->GetLvalue();
		return 0;
	}

	float PlayerWrapper::GetPrayrangeplus()
	{
		if (skillwrapper)
			return skillwrapper->GetPrayDisAdjust();
		return 0;
	}

	int PlayerWrapper::GetBalls()
	{
		return skillwrapper ? skillwrapper->GetBlackWhiteBalls() : 0;
	}

	void PlayerWrapper::SetAddball(int type)
	{
		int newvstate = 0, oldvstate = 0, hstate = 0;
		if (skillwrapper &&
			skillwrapper->AddBlackWhiteBalls(type, newvstate, oldvstate, hstate))
		{
			if (oldvstate)
				object.DecVisibleState(oldvstate);
			if (newvstate)
				object.IncVisibleState(newvstate);

			if (!oldvstate) // only one ball
			{
				object.InsertTeamVisibleState(HSTATE_BLACKWHITE, hstate, -1); // HSTATE_BLACKWHITE
			}
			else
			{
				object.ModifyTeamVisibleState(HSTATE_BLACKWHITE, hstate, -1); // HSTATE_BLACKWHITE
			}
		}
	}

	void PlayerWrapper::SetFilpball(int)
	{
		int newvstate = 0, oldvstate = 0, hstate = 0;
		if (skillwrapper &&
			skillwrapper->FlipBlackWhiteBalls(newvstate, oldvstate, hstate))
		{
			if (oldvstate)
				object.DecVisibleState(oldvstate);
			if (newvstate)
				object.IncVisibleState(newvstate);

			if (!oldvstate) // only one ball
			{
				object.InsertTeamVisibleState(HSTATE_BLACKWHITE, hstate, -1); // HSTATE_BLACKWHITE
			}
			else
			{
				object.ModifyTeamVisibleState(HSTATE_BLACKWHITE, hstate, -1); // HSTATE_BLACKWHITE
			}
		}
	}

	void PlayerWrapper::SetComboid(int id)
	{
		if (skillwrapper)
			skillwrapper->SetComboState(id);
	}

	bool PlayerWrapper::SetPerform(int inform)
	{
		if (!skill)
			return false;
		success = true;
		bool blessmesucc = false;
		if (inform == 2)
		{
			object.SendClientMsgSkillPerform();
			SetMultiCoolDown();
			//object.SetCoolDown(skill->GetId() + COOLINGID_BEGIN, skill->GetCoolingtime() * 1000 + skillwrapper->GetCDAdjust());
			SetCommonCoolDown(skill->GetCommonCoolDown(), skill->GetCommonCoolDownTime());
			if (skill->GetStub()->cls != 258)
			{
				int ap = skill->GetApgain() - skill->GetApcost();
				if (ap)
					object.ModifyAP(ap);
			}

			if ( skill->GetStub()->cls == USER_CLASS_ASN && skill->GetStub()->rank >= 40 )
			{
				int cm = skill->GetChargeMerc();
				//printf("PlayerWrapper::GainChargeMerc: val = %d \n", cm);
				if (cm)
				{
					GainChargeMerc(cm);
				}
			}
			if (!skill->IsElfSkill())
				skillwrapper->OnSkillPerform(skill->GetId(), skill->GetComboPreSkill(), object);
			return true;
		}

		if (!skill->CanAttack())
			success = false;

		if (skill->GetRange().IsSelf())
		{
			if (skill->GetType() == TYPE_JUMP || success)
			{

				enchant_msg msg;
				memset(&msg, 0, sizeof(msg));

				msg.skill = skill->GetId();
				msg.skill_level = skill->GetLevel();
				msg.force_attack = skill->GetForceattack();
				msg.skill_reserved1 = (int)object.GenerateMagicDamage();
				msg.attack_degree = skill->GetDegree();
				msg.section = skill->GetSection();
				if (skill->GetType() == TYPE_NEUTRALBLESS)
					msg.helpful = 2;
				else if (skill->GetType() == TYPE_NEUTRALBLESS2)
					msg.helpful = 3;
				else
					msg.helpful = 1;
				msg.attack_range = object.GetExtendProp().attack_range;
				SetTalentData(msg.skill_modify);
				object.Enchant(object.GetSelfID(), msg);
				if (inform && success)
				{
					object.SendClientMsgSkillPerform();
					SetMultiCoolDown();
					//object.SetCoolDown(skill->GetId() + COOLINGID_BEGIN, skill->GetCoolingtime() * 1000 + skillwrapper->GetCDAdjust());
					SetCommonCoolDown(skill->GetCommonCoolDown(), skill->GetCommonCoolDownTime());
					if (skill->GetStub()->cls != 258)
					{
						int ap = skill->GetApgain() - skill->GetApcost();
						if (ap)
							object.ModifyAP(ap);
					}

					if ( skill->GetStub()->cls == USER_CLASS_ASN && skill->GetStub()->rank >= 40 )
					{
						int cm = skill->GetChargeMerc();
						//printf("PlayerWrapper::GainChargeMerc: val = %d \n", cm);
						if (cm)
						{
							GainChargeMerc(cm);
						}
					}
				
					if (!skill->IsElfSkill())
						skillwrapper->OnSkillPerform(skill->GetId(), skill->GetComboPreSkill(), object);
				}
			}
			return true;
		}
		else if (skill->GetStub()->DoBless())
		{
			bool is136bug = BugSkillRelease(skill->GetId(), this->GetCls());
			if ( is136bug || success )
			{
				if (!is136bug)
					blessmesucc = true;
				skill->SetVictim(this);
				skill->SetPerformerid(XID(-1, -1));
				skill->SetPlayerlevel(this->GetLevel());
				skill->SetMagicDamage(GetMagicattack());
				skill->BlessMe();
			}
		}

		if (skill->GetStub()->GetType() == TYPE_ATTACK)
		{
			int arrowcost = skill->GetStub()->arrowcost;
			attack_msg msg;
			memset(&msg, 0, sizeof(msg));
			msg.physic_damage = skill->GetDamage();
			msg.speed = skill->GetAttackspeed();
			memcpy(msg.magic_damage, skill->GetFivedamage(), sizeof(msg.magic_damage));
			msg.attack_rate = (int)(object.GetExtendProp().attack * skill->GetHitrate());
			msg.force_attack = skill->GetForceattack();
			msg.skill_id = skill->GetId();
			msg.attack_degree = skill->GetDegree();
			msg.attack_attr = skill->GetStub()->GetAttr();
			msg.section = skill->GetSection();
			int rangeadjust = skill->RangeAdjust();
			if (rangeadjust)
			{
				msg.short_range = 6.0f;
				if (rangeadjust == 1)
					msg.short_range_adjust_factor = 0.5;
				else
					msg.short_range_adjust_factor = 2.0;
			}
			else
				msg.short_range_adjust_factor = 1.0;
			msg.target_layer_adjust_mask = skill->PositionAdjust();
			if (msg.target_layer_adjust_mask)
				msg.target_layer_adjust_factor = 3.0;
			SetTalentData(msg.skill_modify);

			if (skill->GetStub()->DoEnchant())
			{
				msg.attached_skill.skill = skill->GetId();
				msg.attached_skill.level = skill->GetLevel();
			}
			msg.skill_enhance = object.GetSkillEnhance();
			msg.skill_enhance2 = object.GetSkillEnhance2();

			object.EnterCombatState();
			if (tsize && target[0].type == GM_TYPE_NPC && !target[0].IsPet())
			{
				object.SetAttackMonster();
			}

			switch (skill->GetRange().type)
			{
			case Range::POINT:
				if (success)
				{
					float correction;
					if (target && GetInrange(skill->GetEffectdistance(), correction))
					{
						msg.attack_range = skill->GetEffectdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += correction;
						object.Attack(*target, msg, arrowcost);
					}
					else
						success = false;
				}
				break;

			case Range::LINE:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					if (!target || 1 != object.QueryObject(*target, tpos, tbody) || object.GetPos().squared_distance(tpos) < 1e-6)
					{
						success = false;
					}
					else
					{
						msg.attack_range = skill->GetAttackdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += tbody + object.GetBodySize();
						object.RegionAttack2(tpos, skill->GetRadius(), msg, arrowcost);
					}
				}
				break;

			case Range::SELFBALL:
				if (success)
				{
					msg.attack_range = skill->GetRadius();
					if (msg.attack_range <= 0)
						msg.attack_range = object.GetExtendProp().attack_range;
					object.RegionAttack1(object.GetPos(), msg.attack_range, msg, arrowcost, (target ? *target : XID(-1, -1)));
				}
				break;

			case Range::TARGETBALL:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					float correction;
					if (target && 1 == object.QueryObject(*target, tpos, tbody) && GetInrange(tpos, tbody, skill->GetEffectdistance(), correction))
					{
						msg.attack_range = skill->GetEffectdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += correction;
						object.RegionAttack1(tpos, skill->GetRadius(), msg, arrowcost, *target);
					}
					else
						success = false;
				}
				break;

			case Range::SECTOR:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					if (target && 1 == object.QueryObject(*target, tpos, tbody) && object.GetPos().squared_distance(tpos) > 1e-6)
					{
						msg.attack_range = skill->GetRadius();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += tbody + object.GetBodySize();
						object.RegionAttack3(tpos, skill->GetAngle(), msg, arrowcost);
					}
					else
						success = false;
				}
				break;
			
			
			// new range
			
			case Range::RECTANGLE:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					if (!target || 1 != object.QueryObject(*target, tpos, tbody) || object.GetPos().squared_distance(tpos) < 1e-6)
					{
						success = false;
					}
					else
					{
						msg.attack_range = skill->GetAttackdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += tbody + object.GetBodySize();
						object.RegionAttack2(tpos, skill->GetRadius(), msg, arrowcost);
					}
				}
				break;

			case Range::SELFSPHERE:
				if (success)
				{
					msg.attack_range = skill->GetRadius();
					if (msg.attack_range <= 0)
						msg.attack_range = object.GetExtendProp().attack_range;
					object.RegionAttack1(object.GetPos(), msg.attack_range, msg, arrowcost, (target ? *target : XID(-1, -1)));
				}
				break;

			case Range::TARGETSPHERE:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					float correction;
					if (target && 1 == object.QueryObject(*target, tpos, tbody) && GetInrange(tpos, tbody, skill->GetEffectdistance(), correction))
					{
						msg.attack_range = skill->GetEffectdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += correction;
						object.RegionAttack1(tpos, skill->GetRadius(), msg, arrowcost, *target);
					}
					else
						success = false;
				}
				break;
			
			// new range
			};
		}
		else if (skill->GetStub()->DoEnchant())
		{
			enchant_msg msg;
			memset(&msg, 0, sizeof(msg));

			msg.skill = skill->GetId();
			msg.skill_level = skill->GetLevel();
			msg.force_attack = skill->GetForceattack();
			msg.skill_reserved1 = (int)object.GenerateMagicDamageWithoutRune();
			msg.attack_degree = skill->GetDegree();
			msg.section = skill->GetSection();
			int stype = skill->GetStub()->GetType();
			if (stype == TYPE_BLESS || stype == TYPE_BLESSPET)
				msg.helpful = 1;
			else if (stype == TYPE_NEUTRALBLESS)
				msg.helpful = 2;
			else if (stype == TYPE_NEUTRALBLESS2)
				msg.helpful = 3;
			else if (stype == TYPE_CURSE)
			{
				object.EnterCombatState();
				if (tsize && target[0].type == GM_TYPE_NPC && !target[0].IsPet())
				{
					object.SetAttackMonster();
				}
			}
			SetTalentData(msg.skill_modify);

			switch (skill->GetRange().type)
			{
			case Range::POINT:
				if (success)
				{
					float correction;
					if (target && GetInrange(skill->GetEffectdistance(), correction, skill->GetRestrictCorpse()))
					{
						msg.attack_range = skill->GetEffectdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += correction;
						if (skill->GetRestrictCorpse() == 1)
							object.EnchantZombie(*target, msg);
						else
							object.Enchant(*target, msg);
					}
					else
						success = false;
				}
				break;

			case Range::LINE:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					if (target && 1 == object.QueryObject(*target, tpos, tbody) && object.GetPos().squared_distance(tpos) > 1e-6)
					{
						msg.attack_range = skill->GetAttackdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += tbody + object.GetBodySize();
						object.RegionEnchant2(tpos, skill->GetRadius(), msg);
					}
					else
						success = false;
				}
				break;

			case Range::SELFBALL:
				if (!success)
					break;
				if (stype == TYPE_BLESS || stype == TYPE_NEUTRALBLESS || stype == TYPE_NEUTRALBLESS2)
				{
					if (object.IsPet())
					{
						if (GetInteam())
						{
							msg.attack_range = skill->GetRadius();
							if (msg.attack_range <= 0)
								msg.attack_range = object.GetExtendProp().attack_range;
							object.TeamEnchant(msg, false);
						}
						else
						{
							msg.attack_range = skill->GetRadius();
							if (msg.attack_range <= 0)
								msg.attack_range = object.GetExtendProp().attack_range;
							unsigned int index = 1;
							XID list[2] = {object.GetSelfID()};
							A3DVECTOR tpos;
							float tbody;
							if (object.QueryObject(object.GetLeaderID(), tpos, tbody) == 1 && tpos.squared_distance(object.GetPos()) < msg.attack_range * msg.attack_range)
							{
								list[index++] = object.GetLeaderID();
							}
							object.MultiEnchant(list, index, msg);
						}
					}
					else
					{
						if (GetInteam())
						{
							msg.attack_range = skill->GetRadius();
							if (msg.attack_range <= 0)
								msg.attack_range = object.GetExtendProp().attack_range;
							object.TeamEnchant(msg, false);
						}
						else
						{
							/*skill->SetVictim(this);
						skill->SetPerformerid(XID(-1,-1));
						skill->SetPlayerlevel( this->GetLevel() );
						skill->SetMagicDamage(GetMagicattack());
						skill->StateAttack();
						object.SendClientEnchantResult(object.GetSelfID(), skill->GetId(), skill->GetLevel(), false, 0);*/
							msg.attack_range = skill->GetRadius();
							if (msg.attack_range <= 0)
								msg.attack_range = object.GetExtendProp().attack_range;
							object.Enchant(object.GetSelfID(), msg);
						}
					}
				}
				else
				{
					msg.attack_range = skill->GetRadius();
					if (msg.attack_range <= 0)
						msg.attack_range = object.GetExtendProp().attack_range;
					object.RegionEnchant1(object.GetPos(), msg.attack_range, msg, (target ? *target : XID(-1, -1)));
				}
				break;

			case Range::TARGETBALL:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					float correction;
					if (target && 1 == object.QueryObject(*target, tpos, tbody) && GetInrange(tpos, tbody, skill->GetEffectdistance(), correction))
					{
						msg.attack_range = skill->GetEffectdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += correction;
						object.RegionEnchant1(tpos, skill->GetRadius(), msg, *target);
					}
					else
						success = false;
				}
				break;

			case Range::SECTOR:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					if (target && 1 == object.QueryObject(*target, tpos, tbody) && object.GetPos().squared_distance(tpos) > 1e-6)
					{
						msg.attack_range = skill->GetRadius();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += tbody + object.GetBodySize();
						object.RegionEnchant3(tpos, skill->GetAngle(), msg);
					}
					else
						success = false;
				}
				break;
				
			// new range 
			case Range::RECTANGLE:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					if (target && 1 == object.QueryObject(*target, tpos, tbody) && object.GetPos().squared_distance(tpos) > 1e-6)
					{
						msg.attack_range = skill->GetAttackdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += tbody + object.GetBodySize();
						object.RegionEnchant2(tpos, skill->GetRadius(), msg);
					}
					else
						success = false;
				}
				break;

			case Range::SELFSPHERE:
				if (!success)
					break;
				if (stype == TYPE_BLESS || stype == TYPE_NEUTRALBLESS || stype == TYPE_NEUTRALBLESS2)
				{
					if (object.IsPet())
					{
						if (GetInteam())
						{
							msg.attack_range = skill->GetRadius();
							if (msg.attack_range <= 0)
								msg.attack_range = object.GetExtendProp().attack_range;
							object.TeamEnchant(msg, false);
						}
						else
						{
							msg.attack_range = skill->GetRadius();
							if (msg.attack_range <= 0)
								msg.attack_range = object.GetExtendProp().attack_range;
							unsigned int index = 1;
							XID list[2] = {object.GetSelfID()};
							A3DVECTOR tpos;
							float tbody;
							if (object.QueryObject(object.GetLeaderID(), tpos, tbody) == 1 && tpos.squared_distance(object.GetPos()) < msg.attack_range * msg.attack_range)
							{
								list[index++] = object.GetLeaderID();
							}
							object.MultiEnchant(list, index, msg);
						}
					}
					else
					{
						if (GetInteam())
						{
							msg.attack_range = skill->GetRadius();
							if (msg.attack_range <= 0)
								msg.attack_range = object.GetExtendProp().attack_range;
							object.TeamEnchant(msg, false);
						}
						else
						{
							/*skill->SetVictim(this);
						skill->SetPerformerid(XID(-1,-1));
						skill->SetPlayerlevel( this->GetLevel() );
						skill->SetMagicDamage(GetMagicattack());
						skill->StateAttack();
						object.SendClientEnchantResult(object.GetSelfID(), skill->GetId(), skill->GetLevel(), false, 0);*/
							msg.attack_range = skill->GetRadius();
							if (msg.attack_range <= 0)
								msg.attack_range = object.GetExtendProp().attack_range;
							object.Enchant(object.GetSelfID(), msg);
						}
					}
				}
				else
				{
					msg.attack_range = skill->GetRadius();
					if (msg.attack_range <= 0)
						msg.attack_range = object.GetExtendProp().attack_range;
					object.RegionEnchant1(object.GetPos(), msg.attack_range, msg, (target ? *target : XID(-1, -1)));
				}
				break;

			case Range::TARGETSPHERE:
				if (success)
				{
					A3DVECTOR tpos;
					float tbody;
					float correction;
					if (target && 1 == object.QueryObject(*target, tpos, tbody) && GetInrange(tpos, tbody, skill->GetEffectdistance(), correction))
					{
						msg.attack_range = skill->GetEffectdistance();
						if (msg.attack_range <= 0)
							msg.attack_range = object.GetExtendProp().attack_range;
						msg.attack_range += correction;
						object.RegionEnchant1(tpos, skill->GetRadius(), msg, *target);
					}
					else
						success = false;
				}
				break;				
				// new range end
			}
		}
		if (inform && (success || blessmesucc))
		{
			object.SendClientMsgSkillPerform();
			SetMultiCoolDown();
			//object.SetCoolDown(skill->GetId() + COOLINGID_BEGIN, skill->GetCoolingtime() * 1000 + skillwrapper->GetCDAdjust());
			SetCommonCoolDown(skill->GetCommonCoolDown(), skill->GetCommonCoolDownTime());
			if (skill->GetStub()->cls != 258)
			{
				int ap = skill->GetApgain() - skill->GetApcost();
				if (ap)
					object.ModifyAP(ap);
			}
		
			if ( skill->GetStub()->cls == USER_CLASS_ASN && skill->GetStub()->rank >= 40 )
			{
				int cm = skill->GetChargeMerc();
				//printf("PlayerWrapper::GainChargeMerc: val = %d \n", cm);
				if (cm)
				{
					GainChargeMerc(cm);
				}
			}

			if (!skill->IsElfSkill())
				skillwrapper->OnSkillPerform(skill->GetId(), skill->GetComboPreSkill(), object);
		}
		return false;
	}

	float PlayerWrapper::GetRangetotarget()
	{
		if (!target)
			return 0.f;
		A3DVECTOR tpos;
		float tbody;
		int ret = object.QueryObject(*target, tpos, tbody);
		if (!ret)
			return 0.f;
		return sqrt(object.GetPos().squared_distance(tpos));
	}

	bool PlayerWrapper::GetInrange(float range, float &correction, char type)
	{
		A3DVECTOR tpos;
		float tbody;
		if (!target || !tsize)
			return false;
		int ret = object.QueryObject(*target, tpos, tbody);
		if (!ret)
			return false;
		if (type == 1 && ret != 2)
			return false;

		const A3DVECTOR pos = object.GetPos();
		float body = object.GetBodySize();
		correction = body + tbody;
		return pos.squared_distance(tpos) < (body + range + tbody) * (body + range + tbody);
	}

	bool PlayerWrapper::GetInrange(A3DVECTOR &tpos, float tbody, float range, float &correction)
	{
		const A3DVECTOR pos = object.GetPos();
		float body = object.GetBodySize();
		correction = body + tbody;
		return pos.squared_distance(tpos) < (body + range + tbody) * (body + range + tbody);
	}

	int PlayerWrapper::GetTargetregionplayernum()
	{
		A3DVECTOR tpos;
		float tbody;
		int ret = object.QueryObject(*target, tpos, tbody);
		if (ret == 0)
			return 1;
		float radius = skill->GetRadius();
		int num = object.GetSpherePlayerListSize(tpos, radius);
		return num > 0 ? num : 1;
	}

	unsigned int PlayerWrapper::GetCharging()
	{
		return skill ? skill->GetCharging() : 0;
	}

	bool PlayerWrapper::SetSpeedup(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Speedup(object, (int)(ratio * 100), time));
#endif
		return true;
	}
	bool PlayerWrapper::SetIncdefence(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Incdefence(object, (int)(ratio * 100), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetDecdefence(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEPHYSICAL | IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Decdefence(object, (int)(ratio * 100), time));
		}
#endif
		return true;
	}


	bool PlayerWrapper::SetInchp(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Inchp(object, (int)(ratio * 100 + 0.00001f), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetDechp(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWOUND | IMMUNEALL))
				immune |= 0x80;
			else
			{
				if (skill->GetAttackState() & 0x4000 && !object.IsPlayerClass())
					return false;
				object.AddFilter(new filter_Dechp(object, (int)(ratio * 100), time, filter::FILTER_MASK_DEBUFF));
			}
		}
		return true;
	}

	bool PlayerWrapper::SetIncmp(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Incmp(object, (int)(ratio * 100), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetHeal(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
		{
			if (skill->GetPerformerid() == object.GetSelfID())
				object.HealBySkill((int)value);
			else
				object.HealBySkill(skill->GetPerformerid(), (int)value);
		}
#endif
		return true;
	}

	bool PlayerWrapper::SetDirecthurt(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEDIRECT | IMMUNEALL))
			immune |= 0x80;
		else
		{
			if (skill->GetAttackState() & 0x4000 && !object.IsPlayerClass())
				return false;
			object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), (int)value, invader,
						  skill->GetAttackerMode());
		}
		return true;
	}

	bool PlayerWrapper::SetEnmity(int n)
	{
#ifndef _SKILL_TEST
		char type = skill->GetStub()->GetType();
		if (type == TYPE_BLESS || type == TYPE_NEUTRALBLESS || type == TYPE_BLESSPET || type == TYPE_NEUTRALBLESS2)
			object.AddAggroToEnemy(skill->GetPerformerid(), n);
		else
			object.AddAggro(skill->GetPerformerid(), n);
#endif
		return true;
	}

	bool PlayerWrapper::SetResurrect(bool)
	{
#ifndef _SKILL_TEST
		if (GetLevel() <= 10)
			ratio = 0;

		if (object.IsDead())
			object.Resurrect(ratio, value, amount);
#endif
		return true;
	}

	bool PlayerWrapper::SetIncsword(float inc)
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_SWORD)
				return false;
		}
		else if (intarg != WEAPONCLASS_SWORD)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				//ѧϰ���ܺ���Ҫ���¼��㹥����
				object.UpdateAttackData();
			}
			return true;
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
			return true;
		}
#endif
		return false;
	}

	bool PlayerWrapper::SetIncspear(float inc)
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_SPEAR)
				return false;
		}
		else if (intarg != WEAPONCLASS_SPEAR)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				//ѧϰ���ܺ���Ҫ���¼��㹥����
				object.UpdateAttackData();
			}
		}
		else
			object.ImpairScaleDamage((int)(inc * 100));
#endif
		return true;
	}

	bool PlayerWrapper::SetInchammer(float inc)
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_AXE)
				return false;
		}
		else if (intarg != WEAPONCLASS_AXE)
			return false;

		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				//ѧϰ���ܺ���Ҫ���¼��㹥����
				object.UpdateAttackData();
			}
			return true;
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
			return true;
		}
#endif
		return false;
	}

	bool PlayerWrapper::SetIncboxing(float inc)
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_BOXING)
				return false;
		}
		else if (intarg != WEAPONCLASS_BOXING)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				//ѧϰ���ܺ���Ҫ���¼��㹥����
				object.UpdateAttackData();
			}
			return true;
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
			return true;
		}
#endif
		return false;
	}

	bool PlayerWrapper::SetIncdagger(float inc)
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_DAGGER)
				return false;
		}
		else if (intarg != WEAPONCLASS_DAGGER)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				//ѧϰ���ܺ���Ҫ���¼��㹥����
				object.UpdateAttackData();
			}
			return true;
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
			return true;
		}
#endif
		return false;
	}

	bool PlayerWrapper::SetInctalisman(float inc)
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_TALISMAN)
				return false;
		}
		else if (intarg != WEAPONCLASS_TALISMAN)
			return false;
		if (enable)
		{
			object.EnhanceScaleMagicDamage((int)(inc * 100));
			if (intarg == -1)
			{
				//ѧϰ���ܺ���Ҫ���¼��㹥����
				object.UpdateMagicData();
			}
			return true;
		}
		else
		{
			object.ImpairScaleMagicDamage((int)(inc * 100));
			return true;
		}
#endif
		return false;
	}

	bool PlayerWrapper::SetIncscimitar(float inc)
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_SCIMITAR)
				return false;
		}
		else if (intarg != WEAPONCLASS_SCIMITAR)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				//ѧϰ���ܺ���Ҫ���¼��㹥����
				object.UpdateAttackData();
			}
			return true;
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
			return true;
		}
#endif
		return false;
	}

	bool PlayerWrapper::SetRepel(bool b)
	{
		// ����,���Թ�����Ч
		if (object.IsPlayerClass())
			return false;
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL))
				immune |= 0x80;
			else
				object.KnockBack(skill->GetPerformerid(), skill->GetPerformerpos(), GetValue());
		}
		return true;
	}

	bool PlayerWrapper::SetRepel2(bool b)
	{
		// ���ˣ�����������?
		if (!object.IsPlayerClass())
			return false;
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL))
				immune |= 0x80;
			else
				object.KnockBack(skill->GetPerformerid(), skill->GetPerformerpos(), value, (int)amount, time);
		}
		return true;
	}

	bool PlayerWrapper::SetKnockup(bool b)
	{
		//���ɣ�����������?
		if (!object.IsPlayerClass())
			return false;
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL))
				immune |= 0x80;
			else
				object.KnockUp(value, (int)amount);
		}
		return true;
	}

	bool PlayerWrapper::SetSleep(bool b)
	{
		// ˯��
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNESLEEP | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Sleep(object, time));
		}
		return true;
	}

	bool PlayerWrapper::SetFix(bool b)
	{
		// ����
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEFIX | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Fix(object, time));
		}
		return true;
	}

	bool PlayerWrapper::SetSealed(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Sealed(object, time));
		}
		return true;
	}

	bool PlayerWrapper::SetMagicleak(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Magicleak(object, (int)(amount), time));
		}
#endif
		return true;
	}

	bool PlayerWrapper::SetFlood(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEWATER | IMMUNEALL)) //lgc
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(2, damage, skill->GetPlayerlevel());
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);

		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

		if (damage > 3)
		{
			filter_Frozen *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Frozen(object, time, damage);
				}
				else
					pfilter = new filter_Frozen(object, time, damage, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Frozen(object, time, damage);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetThunder(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEMETAL | IMMUNEALL)) //lgc
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(0, damage, skill->GetPlayerlevel());
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

		if (damage > 3)
		{
			filter_Thunder *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Thunder(object, time, damage);
				}
				else
					pfilter = new filter_Thunder(object, time, damage, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Thunder(object, time, damage);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetToxic(bool)
	{
#ifndef _SKILL_TEST
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEWOOD | IMMUNEALL)) //lgc
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(1, damage, skill->GetPlayerlevel());
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 3)
		{
			filter_Toxic *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Toxic(object, time, damage);
				}
				else
					pfilter = new filter_Toxic(object, time, damage, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Toxic(object, time, damage);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
#endif
		return true;
	}

	bool PlayerWrapper::SetBurning(bool)
	{
#ifndef _SKILL_TEST
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEFIRE | IMMUNEALL)) //lgc
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(3, damage, skill->GetPlayerlevel());
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 3)
		{
			filter_Burning *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Burning(object, time, damage);
				}
				else
					pfilter = new filter_Burning(object, time, damage, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Burning(object, time, damage);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
#endif
		return true;
	}
	bool PlayerWrapper::SetFallen(bool)
	{
#ifndef _SKILL_TEST
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNESOIL | IMMUNEALL)) //lgc
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(4, damage, skill->GetPlayerlevel());
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 3)
		{
			filter_Fallen *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Fallen(object, time, damage);
				}
				else
					pfilter = new filter_Fallen(object, time, damage, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Fallen(object, time, damage);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
#endif
		return true;
	}

	bool PlayerWrapper::SetBleeding(bool)
	{
#ifndef _SKILL_TEST
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEBLOODING | IMMUNEALL)) //lgc
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcPhysicDamage(damage, skill->GetPlayerlevel());
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 3)
		{
			filter_Bleeding *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Bleeding(object, time, damage);
				}
				else
					pfilter = new filter_Bleeding(object, time, damage, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Bleeding(object, time, damage);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
#endif
		return true;
	}

	bool PlayerWrapper::SetFeathershield(bool b)
	{
#ifndef _SKILL_TEST
		object.AddFilter(new filter_Feathershield(object, ratio, value, time));
#endif
		return true;
	}

	bool PlayerWrapper::SetSlow(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNESLOW | IMMUNEWATER | IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Slow(object, (int)(ratio * 100), time));
		}
		return true;
	}

	bool PlayerWrapper::SetSlowpray(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNESLOW | IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Slowpray(object, (int)(ratio * 100), time));
		}
#endif
		return true;
	}

	bool PlayerWrapper::SetIncmpgen(float inc)
	{
#ifndef _SKILL_TEST
		if (enable)
			object.EnhanceMPGen((int)inc); // ÿ�����??
		else
			object.ImpairMPGen((int)inc); // ÿ�����??
#endif
		return true;
	}

	bool PlayerWrapper::SetInccrit(int point)
	{
#ifndef _SKILL_TEST
		if (enable)
			object.EnhanceCrit(point);
		else
			object.ImpairCrit(point);
#endif
		return true;
	}

	bool PlayerWrapper::SetInchitrate(float _ratio)
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_BOW)
				return false;
		}
		else if (intarg != WEAPONCLASS_BOW)
			return false;
		if (enable)
		{
			object.EnhanceScaleAttack((int)(100 * _ratio));
			if (intarg == -1)
				object.UpdateAttackData();
		}
		else
			object.ImpairScaleAttack((int)(100 * _ratio));
#endif
		return true;
	}

	bool PlayerWrapper::SetIncantiinvisiblepassive(int inc)
	{
		if (enable)
		{
			object.IncAntiInvisiblePassive(inc);
		}
		else
		{
			object.DecAntiInvisiblePassive(inc);
		}
		return true;
	}

	bool PlayerWrapper::SetIncinvisiblepassive(int inc)
	{
		if (enable)
		{
			object.IncInvisiblePassive(inc);
		}
		else
		{
			object.DecInvisiblePassive(inc);
		}
		return true;
	}

	bool PlayerWrapper::SetIncpethp(float inc)
	{
		if (enable)
			object.IncPetHp((int)(inc * 100));
		else
			object.IncPetHp(-(int)(inc * 100));
		return true;
	}

	bool PlayerWrapper::SetIncpetmp(float inc)
	{
		if (enable)
			object.IncPetMp((int)(inc * 100));
		else
			object.IncPetMp(-(int)(inc * 100));
		return true;
	}

	bool PlayerWrapper::SetIncpetdamage(float inc)
	{
		if (enable)
			object.IncPetDamage((int)(inc * 100));
		else
			object.IncPetDamage(-(int)(inc * 100));
		return true;
	}

	bool PlayerWrapper::SetIncpetmagicdamage(float inc)
	{
		if (enable)
			object.IncPetMagicDamage((int)(inc * 100));
		else
			object.IncPetMagicDamage(-(int)(inc * 100));
		return true;
	}

	bool PlayerWrapper::SetIncpetdefense(float inc)
	{
		if (enable)
			object.IncPetDefense((int)(inc * 100));
		else
			object.IncPetDefense(-(int)(inc * 100));
		return true;
	}

	bool PlayerWrapper::SetIncpetmagicdefense(float inc)
	{
		if (enable)
			object.IncPetMagicDefense((int)(inc * 100));
		else
			object.IncPetMagicDefense(-(int)(inc * 100));
		return true;
	}

	bool PlayerWrapper::SetIncpetattackdegree(float inc)
	{
		if (enable)
			object.IncPetAttackDegree((int)(inc * 100));
		else
			object.IncPetAttackDegree(-(int)(inc * 100));
		return true;
	}

	bool PlayerWrapper::SetIncpetdefenddegree(float inc)
	{
		if (enable)
			object.IncPetDefendDegree((int)(inc * 100));
		else
			object.IncPetDefendDegree(-(int)(inc * 100));
		return true;
	}

	bool PlayerWrapper::SetReduceresurrectexplost(int reduce)
	{
		if (enable)
			object.ReduceResurrectExpLost(reduce);
		else
			object.IncreaseResurrectExpLost(reduce);
		return true;
	}

	bool PlayerWrapper::SetImmunedrop(int)
	{
		if (enable)
			object.IncImmuneMask(IMMUNEDROP);
		else
			object.DecImmuneMask(IMMUNEDROP);
		return true;
	}

	bool PlayerWrapper::SetInchpgen(float inc)
	{
#ifndef _SKILL_TEST
		if (enable)
			object.EnhanceHPGen((int)inc); // ÿ�����??
		else
			object.ImpairHPGen((int)inc); // ÿ�����??
#endif
		return true;
	}

	bool PlayerWrapper::SetIncsmite(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Incsmite(object, (int)(value), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetIncattack(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Incattack(object, (int)(ratio * 100), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetIncmagic(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Incmagic(object, (int)(ratio * 100), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetDizzy(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Dizzy(object, time, filter::FILTER_MASK_DEBUFF | filter::FILTER_MASK_TRANSFERABLE_DEBUFF));
		}
		return false;
	}

	bool PlayerWrapper::SetRetort(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Retort(object, ratio, time));
		return false;
	}

	bool PlayerWrapper::SetJingji(bool)
	{
		object.AddFilter(new filter_Jingji(object, ratio, value, time));
		return true;
	}
	

	bool PlayerWrapper::SetBlind(bool b)
	{
#ifndef _SKILL_TEST
		if (!object.IsAggressive())
			return false;
		if (ThrowDice())
			object.AddFilter(new filter_Blind(object, time));
#endif
		return true;
	}

	bool PlayerWrapper::SetFastmpgen(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Fastmpgen(object, (int)(value), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetFasthpgen(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Fasthpgen(object, (int)(value), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetIncdodge(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_Incdodge(object, (int)(ratio * 100), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetDecdodge(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Decdodge(object, (int)(ratio * 100), time));
		}
#endif
		return true;
	}

	bool PlayerWrapper::SetAbsorbhp(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.SendHealMsg(skill->GetPerformerid(), (int)(ratio * object.GetExtendProp().max_hp));
#endif
		return true;
	}

	bool PlayerWrapper::SetSlowattack(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Tardy(object, (int)(ratio * 100), time));
		}
#endif
		return true;
	}

	bool PlayerWrapper::SetFastattack(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Crazy(object, (int)(ratio * 100 + 0.00001f), time)); //�������㾫������
		return true;
	}

	bool PlayerWrapper::SetDecaccuracy(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Decaccuracy(object, (int)(ratio * 100), time));
		}
		return true;
	}

	bool PlayerWrapper::SetInchurt(bool)
	{
		if (ThrowDice() && ratio > 0)
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Inchurt(object, ratio, time));
		}
		return true;
	}

	bool PlayerWrapper::SetIceblade(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Iceblade(object, ratio, time));
		return true;
	}

	bool PlayerWrapper::SetFireblade(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fireblade(object, ratio, time));
		return true;
	}

	bool PlayerWrapper::SetToxicblade(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Toxicblade(object, ratio, time));
		return true;
	}

	bool PlayerWrapper::SetSoilshield(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Soilshield(object, (int)(ratio * 100), (int)(100 * amount), time));
		return true;
	}

	bool PlayerWrapper::SetIncresist(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incresist(object, (int)(ratio * 100), time));
		return true;
	}

	bool PlayerWrapper::SetIncresist2(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incresist2(object, (int)(ratio * 100), time, (value > 0.5f) ? filter::FILTER_MASK_BUFF : 0));
		return true;
	}

	bool PlayerWrapper::SetDecresist(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Decresist(object, (int)(ratio * 100), time));
		}
		return true;
	}

	bool PlayerWrapper::SetFrighten(bool b)
	{
		return true;
	}
	bool PlayerWrapper::SetAssault(bool b)
	{
		if (ThrowDice())
			object.BeTaunted(skill->GetPerformerid(), (int)value);
		return true;
	}

	bool PlayerWrapper::SetCleardebuff(bool m)
	{
		if (ThrowDice())
			object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
		return true;
	}

	bool PlayerWrapper::SetCleardebuff2(bool m)
	{
		if (ThrowDice())
			object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
		return true;
	}

	bool PlayerWrapper::SetStartcallup(int)
	{
		if (skill)
		{
			return true;
		}
		return false;
	}

	bool PlayerWrapper::CheckTarget(float range, char type)
	{
		A3DVECTOR tpos;
		float tbody;
		char stype = skill->GetStub()->GetType();
		if (!target || !tsize)
			return false;
		if (*target == object.GetSelfID())
		{
			if (stype != TYPE_BLESS && stype != TYPE_NEUTRALBLESS && stype != TYPE_NEUTRALBLESS2)
				return false;
		}
		else if (*target != object.GetCurTargetID() && stype != TYPE_BLESSPET) //ֻ��ѡ�в��ܴ����??
			return false;
		int ret = object.QueryObject(*target, tpos, tbody);
		if (ret == 0)
			return false;
		if (type == 1 && ret != 2)
			return false;
		if (type != 1 && ret == 2)
			return false;
		if (type == 2 && object.IsInventoryFull())
			return false;

		const A3DVECTOR pos = object.GetPos();
		float body = object.GetBodySize();
		return pos.squared_distance(tpos) < (body + range + tbody) * (body + range + tbody);
	}

	bool PlayerWrapper::CheckComboState(unsigned int sid, int interval)
	{
		return skillwrapper && skillwrapper->CheckComboState(sid, interval, object.GetSystime());
	}

	bool PlayerWrapper::SetTigerform(bool b)
	{
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.RemoveFilter(FILTER_TIGERFORM);
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;

		object.AddFilter(new filter_Tigerform(object, GetRatioInt(), (int)(100 * probability), (int)(100 * amount), (int)(100 * value)));
		return true;
	}

	bool PlayerWrapper::SetFrenetic(bool b)
	{
		if (enable)
			object.AddFilter(new filter_Frenetic(object, probability, ratio + 1.0, value));
		else
			object.RemoveFilter(FILTER_FRENETIC);
		return true;
	}

	bool PlayerWrapper::SetAdddefence(float m)
	{
		if (enable)
			object.EnhanceScaleDefense((int)(m * 100));
		else
			object.ImpairScaleDefense((int)(m * 100));
		object.UpdateDefenseData();
		return true;
	}

	bool PlayerWrapper::SetAddresistance(float inc)
	{
		if (enable)
		{
			for (int n = 0; n < MAGIC_CLASS; ++n)
				object.EnhanceScaleResistance(n, (int)(inc * 100));
		}
		else
		{
			for (int n = 0; n < MAGIC_CLASS; ++n)
				object.ImpairScaleResistance(n, (int)(inc * 100));
		}
		object.UpdateMagicData();
		return true;
	}

	bool PlayerWrapper::SetAddskilldamage(float inc)
	{
		if (enable)
			object.EnhanceSkillDamage2((int)(inc * 100));
		else
			object.ImpairSkillDamage2((int)(inc * 100));

		return true;
	}

	bool PlayerWrapper::SetIncnearnormaldmgreduce(float inc)
	{
		if (enable)
			object.EnhanceNearNormalDmgReduce(inc);
		else
			object.ImpairNearNormalDmgReduce(inc);
		return true;
	}

	bool PlayerWrapper::SetIncnearskilldmgreduce(float inc)
	{
		if (enable)
			object.EnhanceNearSkillDmgReduce(inc);
		else
			object.ImpairNearSkillDmgReduce(inc);
		return true;
	}

	bool PlayerWrapper::SetIncfarnormaldmgreduce(float inc)
	{
		if (enable)
			object.EnhanceFarNormalDmgReduce(inc);
		else
			object.ImpairFarNormalDmgReduce(inc);
		return true;
	}

	bool PlayerWrapper::SetIncfarskilldmgreduce(float inc)
	{
		if (enable)
			object.EnhanceFarSkillDmgReduce(inc);
		else
			object.ImpairFarSkillDmgReduce(inc);
		return true;
	}

	bool PlayerWrapper::SetAddmaxhp(float inc)
	{
		if (enable)
			object.EnhanceScaleMaxHP((int)(inc * 100 + 0.00001f), intarg == -1);
		else
			object.ImpairScaleMaxHP((int)(inc * 100 + 0.00001f), intarg == -1);

		return true;
	}

	bool PlayerWrapper::SetDisturbrecover(int val)
	{
		const int DISTURBRECOVER_SKILL_ID = 2932;
		if (enable)
			object.SetInfectSkill(DISTURBRECOVER_SKILL_ID, val);
		else
			object.ClrInfectSkill(DISTURBRECOVER_SKILL_ID);

		return true;
	}

	bool PlayerWrapper::SetIncswimspeed(float inc)
	{
		if (inc == 0)
			return false;
		if (enable)
			object.EnhanceSwimSpeed((int)(inc * 100 + 0.00001f));
		else
			object.ImpairSwimSpeed((int)(inc * 100 + 0.00001f));

		object.UpdateSpeedData();
		object.SendClientCurSpeed();
		return true;
	}

	bool PlayerWrapper::SetReturntown(bool m)
	{
		success = false;
		if (object.CanReturnToTown())
		{
			//ע��:����ʹ����target����,�ͻ�����Ҫ���⴦��
			if (target && target->id != 0)
			{
				int city;
				int fid = object.GetMafiaID();
				if (fid && object.CheckWaypoint(target->id, city) && fid == object.GetCityOwner(city))
				{
					object.ReturnWaypoint(target->id);
					success = true;
				}
			}
			else
			{
				object.ReturnToTown();
				success = true;
			}
		}
		return success;
	}

	bool PlayerWrapper::SetEnhancegold(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Enhancegold(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetEnhancewood(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Enhancewood(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetEnhancewater(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Enhancewater(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetEnhancefire(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Enhancefire(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetEnhancesoil(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Enhancesoil(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetReducegold(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEMETAL | IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Reducegold(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetReducewood(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWOOD | IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Reducewood(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetReducewater(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWATER | IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Reducewater(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetReducefire(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEFIRE | IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Reducefire(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetReducesoil(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNESOIL | IMMUNEALL)) //lgc
				immune |= 0x80;
			else
				object.AddFilter(new filter_Reducesoil(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetDecmagic(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Decmagic(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetDecattack(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Decattack(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetIncaccuracy(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incaccuracy(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetIceshield(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Iceshield(object, (int)(ratio * 100), (int)amount, time));
		return true;
	}
	bool PlayerWrapper::SetFireshield(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fireshield(object, (int)(ratio * 100), (int)amount, time));
		return true;
	}
	bool PlayerWrapper::SetInvincible(bool)
	{
		if (ThrowDice())
		{
			object.SetInvincibleFilter(true, time, true);
			if (showicon)
				object.AddFilter(new filter_Icon(object, time, HSTATE_INVINCIBLE));
		}
		return true;
	}
	bool PlayerWrapper::SetInvincible2(bool) //����debuff
	{
		if (ThrowDice())
		{
			object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			object.SetInvincibleFilter(true, time, true);
			if (showicon)
				object.AddFilter(new filter_Icon(object, time, HSTATE_INVINCIBLE));
		}
		return true;
	}
	bool PlayerWrapper::SetInvincible3(bool) //����debuff����Ѫ
	{
		if (ThrowDice())
		{
			object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			object.Heal((int)(GetMaxhp() * ratio));
			object.SetInvincibleFilter(true, time, true);
			if (showicon)
				object.AddFilter(new filter_Icon(object, time, HSTATE_INVINCIBLE));
		}
		return true;
	}
	bool PlayerWrapper::SetInvincible4(bool) //����debuff,��ֹ�չ�����?��??
	{
		if (ThrowDice())
		{
			object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			object.SetInvincibleFilter(true, time, true);
			if (showicon)
				object.AddFilter(new filter_Icon(object, time, HSTATE_INVINCIBLE));
			object.AddFilter(new filter_Decapperhit(object, (int)(value / 1000), 100));
		}
		return true;
	}
	bool PlayerWrapper::SetInvincible5(bool) //����debuff,������Ѫ������
	{
		if (ThrowDice())
		{
			object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			object.SetInvincibleFilter(true, time, true);
			if (showicon)
				object.AddFilter(new filter_Icon(object, time, HSTATE_INVINCIBLE5, VSTATE_INVINCIBLE5));
			object.AddFilter(new filter_Dizzy(object, time, 0));
			object.AddFilter(new filter_Hpgen(object, (int)(value), time));
			object.TurretOutOfControl();
		}
		return true;
	}

	bool PlayerWrapper::SetInvincible6(bool) //���޵У��Ǵ���ʱ������
	{
		if (ThrowDice())
		{
			object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			if (!object.IsFilterExist(FILTER_MINECARPROTECT))
				object.GiveMafiaPvPAward(skill->GetPerformerid(), 5);
			object.AddFilter(new filter_Minecarprotect(object, time));
		}
		return true;
	}

	bool PlayerWrapper::SetInvincible7(bool)
	{
		if (ThrowDice())
		{
			object.SetInvincibleFilter2(true, time, true);
			if (showicon)
				object.AddFilter(new filter_Icon(object, time, HSTATE_INVINCIBLE));
		}
		return true;
	}

	bool PlayerWrapper::SetInvincible8(bool) //���˸���ר��
	{
		if (ThrowDice())
		{
			//printf("SetInvincible8: time = %f 2 \n", GetTime());
			object.AddFilter(new filter_solo_invincible(object, GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetAntiwater(bool)
	{
		object.AddFilter(new filter_Antiwater(object, time));
		return true;
	}

	bool PlayerWrapper::SetPanruo(bool)
	{
		return true;
	}

	bool PlayerWrapper::SetFastpray(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fastpray(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetBreak(bool)
	{
		if (object.GetImmuneMask() & (IMMUNEBREAK | IMMUNEALL))
			immune |= 0x80;
		else if (ThrowDice())
			object.BreakCurAction();
		return true;
	}
	bool PlayerWrapper::SetScaleinchp(bool)
	{
		if (ThrowDice())
		{
			object.Heal((int)(GetMaxhp() * ratio));
		}
		return true;
	}
	bool PlayerWrapper::SetScaleincmp(bool)
	{
		if (ThrowDice())
		{
			object.InjectMana((int)(GetMaxmp() * ratio));
		}
		return true;
	}
	bool PlayerWrapper::SetScaledechp(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWOUND | IMMUNEALL))
				immune |= 0x80;
			else
			{
				if (skill->GetAttackState() & 0x4000 && !object.IsPlayerClass())
					return false;
				struct attacker_info_t info = {XID(-1, -1), 0, 0, 0, 0, 0, 0, 0};
				object.BeHurt(XID(-1, -1), info, (int)(GetMaxhp() * ratio), false, 0);
				//object.DecHP((int)(GetMaxhp() * ratio));
			}
		}
		return true;
	}
	bool PlayerWrapper::SetScaledecmp(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.DrainMana((int)(GetMaxmp() * ratio));
		}
		return true;
	}
	bool PlayerWrapper::SetDechurt(bool)
	{
		if (ThrowDice() && ratio > 0.001 && ratio < 0.99)
			object.AddFilter(new filter_Dechurt(object, ratio, time));
		return true;
	}
	bool PlayerWrapper::SetHpgen(float)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Hpgen(object, (int)(value), time));
		return true;
	}
	bool PlayerWrapper::SetMpgen(float)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Mpgen(object, (int)(value), time));
		return true;
	}
	bool PlayerWrapper::SetYijin(bool)
	{
		object.AddFilter(new filter_Yijin(object, (int)(ratio * 100), (int)(amount * 100), time));
		return true;
	}
	bool PlayerWrapper::SetXisui(bool)
	{
		object.AddFilter(new filter_Xisui(object, (int)(ratio * 100), (int)(amount * 100), time));
		return true;
	}
	bool PlayerWrapper::SetApgen(bool)
	{
		object.AddFilter(new filter_Apgen(object, (int)(value), time));
		return true;
	}



	bool PlayerWrapper::SetMnfactionDecresist(bool)
	{
		if (object.GetImmuneMask() & IMMUNEALL)
		{
			immune |= 0x80;
			return false;
		}
		//object.AddFilter(new filter_MnfactionDecresist(object,(int)(ratio*100),time));
		return true;
	}

	bool PlayerWrapper::SetPowerup(bool)
	{
		object.AddFilter(new filter_Powerup(object, time));
		return true;
	}

	bool PlayerWrapper::SetIncswim(float inc)
	{
		if (enable)
		{
			object.EnhanceSwimSpeed((int)(100 * inc));
			object.AdjustBreathDecPoint(-1);
			object.UpdateSpeedData();
		}
		else
		{
			object.ImpairSwimSpeed((int)(100 * inc));
			object.AdjustBreathDecPoint(1);
			object.UpdateSpeedData();
		}
		return true;
	}

	bool PlayerWrapper::SetIncfeather(float inc)
	{
		if (intarg == -1)
		{
			if (!object.IsEquipWing())
				return false;
		}
		else if (intarg != WEAPONCLASS_FEATHER)
			return false;
		if (enable)
		{
			object.EnhanceFlySpeed(inc);
			if (intarg == -1)
			{
				object.UpdateSpeedData();
			}
			return true;
		}
		else
		{
			object.ImpairFlySpeed(inc);
			return true;
		}
		return false;
	}

	bool PlayerWrapper::SetStoneskin(bool)
	{
		object.AddFilter(new filter_Stoneskin(object, (int)(ratio * 100), time));
		return true;
	}

	bool PlayerWrapper::SetIronshield(bool)
	{
		object.AddFilter(new filter_Ironshield(object, (int)(ratio * 100), time));
		return true;
	}

	bool PlayerWrapper::SetWingshield(bool)
	{
		object.AddFilter(new filter_Wingshield(object, (int)(amount), (int)value, time));
		return true;
	}

	bool PlayerWrapper::SetFirearrow(bool)
	{
		object.AddFilter(new filter_Firearrow(object, ratio, time));
		return true;
	}

	bool PlayerWrapper::SetGiant(bool)
	{
		object.AddFilter(new filter_Giant(object, (int)(ratio * 100), time));
		return true;
	}

	bool PlayerWrapper::SetBlessmagic(bool)
	{
		object.AddFilter(new filter_Blessmagic(object, (int)(ratio * 100), time));
		return true;
	}

	bool PlayerWrapper::SetAp(bool b)
	{
		if (!ThrowDice())
			return false;
		object.ModifyAP((int)value);
		return true;
	}

	bool PlayerWrapper::SetEaglecurse(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEMETAL | IMMUNEALL)) //lgc
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(0, damage, skill->GetPlayerlevel());
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 1)
		{
			filter_Eaglecurse *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Eaglecurse(object, (int)(ratio * 100), time, damage);
				}
				else
					pfilter = new filter_Eaglecurse(object, (int)(ratio * 100), time, damage, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Eaglecurse(object, (int)(ratio * 100), time, damage);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetDevilstate(bool)
	{
		object.AddFilter(new filter_Devilstate(object, (int)(amount * 100 + 0.00001), (int)(ratio * 100 + 0.00001), time));
		return true;
	}

	bool PlayerWrapper::SetFreemove(bool)
	{
		object.AddFilter(new filter_Freemove(object, time));
		return true;
	}

	bool PlayerWrapper::SetIncrange(float r)
	{
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_BOW)
				return false;
		}
		else if (intarg != WEAPONCLASS_BOW)
			return false;
		if (enable)
		{
			object.EnhanceAttackRange(r);
			if (intarg == -1)
			{
				object.UpdateAttackData();
				object.SendClientAttackData();
			}
		}
		else
		{
			object.ImpairAttackRange(r);
		}
		return true;
	}

	bool PlayerWrapper::SetIncbow(float inc)
	{
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_BOW)
				return false;
		}
		else if (intarg != WEAPONCLASS_BOW)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				object.UpdateAttackData();
			}
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
		}
		return true;
	}

	bool PlayerWrapper::SetEntrap(bool b)
	{
		int eggid = object.GetPetEggID();
		if (eggid <= 0 || skill->GetPlayerlevel() < GetLevel())
			immune |= 0x80;
		else
		{
			float prob = ((float)GetMaxhp() - (float)GetHp()) / (float)GetMaxhp();
			prob *= prob * 100 * (1.35 - GetLevel() / 100 + skill->GetLevel() * 0.05);
			if ((rand() % 100) < prob)
			{
				object.TransferPetEgg(skill->GetPerformerid(), eggid);
				object.Disappear();
				immune |= 0x0200;
			}
			else
				immune |= 0x0100;
		}
		return true;
	}

	bool PlayerWrapper::SetSummon(bool b)
	{
		if (ThrowDice())
			object.ResurrectPet();
		return true;
	}

	bool PlayerWrapper::SetClearbuff(bool b)
	{
		if (object.GetImmuneMask() & (IMMUNECLEAR | IMMUNEALL))
			immune |= 0x80;
		else if (object.ModifyFilter(FILTER_ANTICLEARBUF, FMID_DEC_ANTICLEAR, 0, 0))
			immune |= 0x80;
		else if (ThrowDice())
			object.ClearSpecFilter(filter::FILTER_MASK_BUFF);
		return true;
	}

	bool PlayerWrapper::SetApleak(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Apleak(object, (int)(value), time));
		}
		return true;
	}

	bool PlayerWrapper::SetCanti(bool b)
	{
		if (ThrowDice() && ratio > 0)
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Canti(object, ratio, time));
		}
		return true;
	}

	bool PlayerWrapper::SetNoregain(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Noregain(object, time));
		}
		return true;
	}

	bool PlayerWrapper::SetFoxform(bool b)
	{
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.RemoveFilter(FILTER_FOXFORM);
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;
		object.AddFilter(new filter_Foxform(object, (int)(100 * ratio), (int)(100 * amount), (int)(100 * probability), GetValueInt()));
		return true;
	}

	bool PlayerWrapper::SetSwiftform(bool b)
	{
		object.AddFilter(new filter_Swiftform(object, time, (int)(100 * amount)));
		return true;
	}

	bool PlayerWrapper::SetIncfight(float inc)
	{
		if (enable)
			object.EnhanceScaleDamage((int)(inc * 100));
		else
			object.ImpairScaleDamage((int)(inc * 100));
		object.UpdateAttackData();
		return false;
	}

	bool PlayerWrapper::SetFlower1(bool)
	{
		object.AddFilter(new filter_Icon(object, time, 0, VSTATE_FLOWER1, FILTER_FLOWER, filter::FILTER_MASK_UNIQUE));
		return true;
	}
	bool PlayerWrapper::SetFlower2(bool)
	{
		object.AddFilter(new filter_Icon(object, time, 0, VSTATE_FLOWER2, FILTER_FLOWER, filter::FILTER_MASK_UNIQUE));
		return true;
	}
	bool PlayerWrapper::SetFlower3(bool)
	{
		object.AddFilter(new filter_Icon(object, time, 0, VSTATE_FLOWER3, FILTER_FLOWER, filter::FILTER_MASK_UNIQUE));
		return true;
	}
	bool PlayerWrapper::SetFlower4(bool)
	{
		object.AddFilter(new filter_Icon(object, time, 0, VSTATE_FLOWER4, FILTER_FLOWER, filter::FILTER_MASK_UNIQUE));
		return true;
	}

	bool PlayerWrapper::SetFastride(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fastride(object, (int)(ratio * 100), time));
		return true;
	}

	bool PlayerWrapper::SetDisappear(bool b)
	{
		object.Die();
		return true;
	}

	bool PlayerWrapper::SetHp2mp(bool b)
	{
		if (!object.IsPlayerClass())
			return false;
		if (ThrowDice())
		{
			float mper = (float)GetMp() / GetMaxmp();
			float hper = (float)GetHp() / GetMaxhp();
			int hp = (int)(GetMaxhp() * mper);
			int mp = (int)(GetMaxmp() * hper);
			SetHp(hp ? hp : 1);
			SetMp(mp);
		}
		return true;
	}
	bool PlayerWrapper::SetSharpblade(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Sharpblade(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetAddattackdegree(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Addattackdegree(object, (int)value, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetSubattackdegree(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Subattackdegree(object, (int)value, time));
		}
		return true;
	}
	bool PlayerWrapper::SetAdddefencedegree(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Adddefencedegree(object, (int)value, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetSubdefencedegree(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Subdefencedegree(object, (int)value, time));
		}
		return true;
	}
	void PlayerWrapper::SetTalentData(int *list)
	{
		if (!skill)
			return;
		list[0] = skill->GetT0();
		list[1] = skill->GetT1();
		list[2] = skill->GetT2();
	}
	int PlayerWrapper::GetElfstr()
	{
		short level, str = 0, agi = 0, vit = 0, eng = 0;
		object.GetElfProp(level, str, agi, vit, eng);
		return int(str * ELFSTR_ADJ_IN_SKILL_ATTACK);
	}
	int PlayerWrapper::GetElfagi()
	{
		short level, str = 0, agi = 0, vit = 0, eng = 0;
		object.GetElfProp(level, str, agi, vit, eng);
		return int(agi * ELFAGI_ADJ_IN_SKILL_ATTACK);
	}
	int PlayerWrapper::GetElfvit()
	{
		short level, str = 0, agi = 0, vit = 0, eng = 0;
		object.GetElfProp(level, str, agi, vit, eng);
		return vit;
	}
	int PlayerWrapper::GetElfeng()
	{
		short level, str = 0, agi = 0, vit = 0, eng = 0;
		object.GetElfProp(level, str, agi, vit, eng);
		return eng;
	}
	int PlayerWrapper::GetElflevel()
	{
		short level = 0, str = 0, agi = 0, vit = 0, eng = 0;
		object.GetElfProp(level, str, agi, vit, eng);
		return level;
	}
	//lgc
	//����filter�в���showicon��ʾ�Ƿ����gfx��Ч
	bool PlayerWrapper::SetImmunesealed(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunesealed(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetImmunesleep(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunesleep(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetImmuneslowdizzy(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immuneslowdizzy(object, time));
		return true;
	}
	bool PlayerWrapper::SetImmunewound(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunewound(object, time));
		return true;
	}
	bool PlayerWrapper::SetImmuneall(bool b)
	{
		if (ThrowDice())
		{
			object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			object.AddFilter(new filter_Immuneall(object, time));
		}
		return true;
	}
	bool PlayerWrapper::SetImmunephysical(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunephysical(object, time));
		return true;
	}
	bool PlayerWrapper::SetImmunefire(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunefire(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetImmunewater(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunewater(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetImmunemetal(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunemetal(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetImmunewood(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunewood(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetImmunesoil(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunesoil(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetImmunemagical(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immunemagical(object, time, FILTER_IMMUNEMAGICAL,
													  filter::FILTER_MASK_WEAK | filter::FILTER_MASK_BUFF | filter::FILTER_MASK_TRANSFERABLE_BUFF));
		return true;
	}
	bool PlayerWrapper::SetArrogant(bool b)
	{
		if (ThrowDice())
		{
			object.ClearSpecFilter(filter::FILTER_MASK_BUFF | filter::FILTER_MASK_DEBUFF);
			object.AddFilter(new filter_Arrogant(object, time));
		}
		return true;
	}
	bool PlayerWrapper::SetSlowswim(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNESLOW | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Slowswim(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetFastswim(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fastswim(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetSlowfly(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNESLOW | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Slowfly(object, (int)(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetFastfly(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fastfly(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetSlowride(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Slowride(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetApgencont(bool b)
	{
		if (ThrowDice())
		{
			int mask_buff = (value > 0.5f ? filter::FILTER_MASK_BUFF : 0);
			object.AddFilter(new filter_Apgencont(object, (int)amount, time, showicon, mask_buff));
		}
		return true;
	}
	bool PlayerWrapper::SetApgencont2(bool b)
	{
		if (ThrowDice())
		{
			int mask_buff = (value > 0.5f ? filter::FILTER_MASK_BUFF : 0);
			object.AddFilter(new filter_Apgencont2(object, (int)amount, time, showicon, mask_buff));
		}
		return true;
	}
	bool PlayerWrapper::SetApleakcont(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			int mask_buff = (value > 0.5f ? filter::FILTER_MASK_DEBUFF : 0);
			object.AddFilter(new filter_Apleakcont(object, (int)amount, time, showicon, mask_buff));
		}
		return true;
	}
	bool PlayerWrapper::SetIncelfstr(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incelfstr(object, (int)value, time));
		return true;
	}
	bool PlayerWrapper::SetIncelfagi(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incelfagi(object, (int)value, time));
		return true;
	}
	bool PlayerWrapper::SetIncdefence2(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incdefence2(object, int(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetWeakelement(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Weakelement(object, int(ratio * 100), time, showicon));
		return true;
	}
	bool PlayerWrapper::SetDeeppoision(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWOOD | IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Deeppoision(object, ratio, time));
		}
		return true;
	}
	bool PlayerWrapper::SetRooted(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Rooted(object, ratio, time));
		return true;
	}
	bool PlayerWrapper::SetEarthguard(bool b)
	{
		object.AddFilter(new filter_Earthguard(object, (int)amount, ratio, time));
		return true;
	}
	bool PlayerWrapper::SetFury(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fury(object, (int)value, time));
		return true;
	}
	bool PlayerWrapper::SetSandstorm(bool b)
	{
		object.AddFilter(new filter_Sandstorm(object, int(ratio * 100), int(value * 100), time));
		return true;
	}
	bool PlayerWrapper::SetHomefeeling(bool b)
	{
		object.AddFilter(new filter_Homefeeling(object, int(value), int(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetReducewater2(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWATER | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Reducewater2(object, int(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetIncsmite2(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incsmite2(object, int(value), time));
		return true;
	}
	bool PlayerWrapper::SetDecdefence2(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEPHYSICAL | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Decdefence2(object, int(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetReducefire2(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEFIRE | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Reducefire2(object, int(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetSlowattackpray(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Slowattackpray(object, int(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetBurning2(bool b)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEFIRE | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(3, damage, skill->GetPlayerlevel());
		damage = int(damage * (1 + (skill->GetAttackerDegree() - object.GetDefendDegree()) * 0.01f));
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 3)
		{
			filter_Burning2 *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Burning2(object, time, damage);
				}
				else
					pfilter = new filter_Burning2(object, time, damage, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Burning2(object, time, damage);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}
	bool PlayerWrapper::SetBurningfeet(bool b)
	{
		if (object.GetImmuneMask() & (IMMUNEFIRE | IMMUNESLOW | IMMUNEALL))
			immune |= 0x80;
		else
			object.AddFilter(new filter_Burningfeet(object, int(ratio * 100), int(value * 100), time));
		return true;
	}
	bool PlayerWrapper::SetHardenskin(bool b)
	{
		object.AddFilter(new filter_Hardenskin(object, ratio, int(value * 100), time));
		return true;
	}
	bool PlayerWrapper::SetReducegold2(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEMETAL | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Reducegold2(object, int(ratio * 100), time));
		}
		return true;
	}
	bool PlayerWrapper::SetLeafdance(bool b)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEBLOODING | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcPhysicDamage(damage, skill->GetPlayerlevel());
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 3)
		{
			filter_Leafdance *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Leafdance(object, int(ratio * 100), time, (int)amount);
				}
				else
					pfilter = new filter_Leafdance(object, int(ratio * 100), time, (int)amount, filter::FILTER_MASK_MERGE);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Leafdance(object, int(ratio * 100), time, (int)amount);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}
	bool PlayerWrapper::SetCharred(bool b)
	{
		if (object.GetImmuneMask() & (IMMUNEPHYSICAL | IMMUNEALL))
			immune |= 0x80;
		else
			object.AddFilter(new filter_Charred(object, int(ratio * 100), int(value * 100), time));
		return true;
	}
	bool PlayerWrapper::SetVacuum(bool b)
	{
		object.AddFilter(new filter_Vacuum(object, int(ratio * 100), value, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetImmuneblooding(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immuneblooding(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetAbsorbphysicdamage(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Absorbphysicdamage(object, (int)amount, time, showicon, value > 0.5f));
		return true;
	}
	bool PlayerWrapper::SetAbsorbmagicdamage(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Absorbmagicdamage(object, (int)amount, time, showicon, value > 0.5f));
		return true;
	}
	bool PlayerWrapper::SetRetortmagic(bool b)
	{
		object.AddFilter(new filter_Retortmagic(object, ratio, (int)amount, time));
		return true;
	}

	bool PlayerWrapper::SetRetortNewPaladin(bool b) // Novas Alterações
	{
		object.AddFilter(new filter_RetortNewPaladin(object, ratio, time));
		return true;
	}
	bool PlayerWrapper::SetWindshield(bool b)
	{
		object.AddFilter(new filter_Windshield(object, ratio, int(value * 100), time, showicon));
		return true;
	}
	bool PlayerWrapper::SetAirstreamlock(bool b)
	{
		object.AddFilter(new filter_Airstreamlock(object, time, probability, int(value / 1000), showicon));
		return true;
	}
	bool PlayerWrapper::SetClosed(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Closed(object, time));
		return true;
	}
	bool PlayerWrapper::SetInsertvstate(bool b)
	{
		int _vstate = (int)amount;
		int _hstate = (int)ratio;
		int _mask = (value > 1.0f ? 0 : (value > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		if (_vstate >= 0 && _vstate < VSTATE_MAX && _hstate >= 0)
			object.AddFilter(new filter_Insertvstate(object, time, _vstate, _hstate, _mask));
		return true;
	}
	bool PlayerWrapper::SetImmuneweak(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Immuneweak(object, time, showicon));
		return true;
	}
	bool PlayerWrapper::SetBefrozen(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Befrozen(object, time, showicon));
		}
		return true;
	}
	bool PlayerWrapper::SetClearsealed(bool b)
	{
		if (ThrowDice())
		{
			object.RemoveFilter(FILTER_SEALED);
			object.RemoveFilter(FILTER_AIRSTREAMLOCK);
			object.RemoveFilter(FILTER_CLOSED);
		}
		return true;
	}
	bool PlayerWrapper::SetClearrooted(bool b)
	{
		if (ThrowDice())
		{
			object.RemoveFilter(FILTER_FIX);
			object.RemoveFilter(FILTER_ROOTED);
			object.RemoveFilter(FILTER_AIRSTREAMLOCK);
		}
		return true;
	}
	bool PlayerWrapper::SetClearbleeding(bool b)
	{
		if (ThrowDice())
		{
			object.RemoveFilter(FILTER_BLEEDING);
			object.RemoveFilter(FILTER_BLEEDING_MERGE);
			object.RemoveFilter(FILTER_LEAFDANCE);
			object.RemoveFilter(FILTER_LEAFDANCE_MERGE);
		}
		return true;
	}
	bool PlayerWrapper::SetCleardizzy(bool b)
	{
		if (ThrowDice())
		{
			object.RemoveFilter(FILTER_DIZZY);
			object.RemoveFilter(FILTER_BEFROZEN);
		}
		return true;
	}
	bool PlayerWrapper::SetSelfburning(bool)
	{
#ifndef _SKILL_TEST
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEFIRE | IMMUNEALL)) //lgc
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(3, damage, GetLevel());
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 3)
		{
			filter_Burning *pfilter = new filter_Burning(object, time, (int)(0.25f * damage), filter::FILTER_MASK_MERGE);
			struct attacker_info_t info = {XID(-1, -1), 0, 0, 0, 0, 0, 0, 0};
			struct XID id(-1, -1);
			pfilter->SetUp(id, info, 0, false);
			object.AddFilter(pfilter);
		}

#endif
		return true;
	}
	bool PlayerWrapper::SetFallen2(bool b)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNESOIL | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)GetAmount();
		damage = object.CalcMagicDamage(4, damage, skill->GetPlayerlevel());
		damage = int(damage * (1 + (skill->GetAttackerDegree() - object.GetDefendDegree()) * 0.01f));
		if (!object.IsPlayerClass())
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), damage);

		if (damage > 3)
		{
			int mask_buff = (value > 0.5f ? filter::FILTER_MASK_DEBUFF : 0);
			filter_Fallen2 *pfilter;
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
				{
					damage = (int)(0.25 * damage);
					pfilter = new filter_Fallen2(object, time, damage, showicon, mask_buff);
				}
				else
					pfilter = new filter_Fallen2(object, time, damage, showicon, filter::FILTER_MASK_MERGE | mask_buff);
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				pfilter = new filter_Fallen2(object, time, damage, showicon, mask_buff);
			}
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}
	bool PlayerWrapper::SetSealed2(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
			{
				int mask_buff = (value > 0.5f ? filter::FILTER_MASK_DEBUFF : 0);
				object.AddFilter(new filter_Sealed2(object, time, showicon, mask_buff));
			}
		}
		return true;
	}
	bool PlayerWrapper::SetFix2(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEFIX | IMMUNEALL))
				immune |= 0x80;
			else
			{
				int mask_buff = (value > 0.5f ? filter::FILTER_MASK_DEBUFF : 0);
				object.AddFilter(new filter_Fix2(object, time, showicon, mask_buff));
			}
		}
		return true;
	}
	bool PlayerWrapper::SetDechurt2(bool)
	{
		if (ThrowDice() && ratio > 0.001 && ratio < 0.99)
		{
			int mask_buff = (value > 0.5f ? filter::FILTER_MASK_BUFF : 0);
			object.AddFilter(new filter_Dechurt2(object, ratio, time, mask_buff));
		}
		return true;
	}
	bool PlayerWrapper::SetDechurt3(bool)
	{
		if (ThrowDice() && ratio > 0.001 && ratio < 0.99)
		{
			int mask_buff = (value > 0.5f ? filter::FILTER_MASK_BUFF : 0);
			object.AddFilter(new filter_Dechurt3(object, ratio, time, mask_buff));
		}
		return true;
	}
	bool PlayerWrapper::SetInchurt2(bool)
	{
		if (ThrowDice() && ratio > 0)
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
			{
				int mask_buff = (value > 0.5f ? filter::FILTER_MASK_DEBUFF : 0);
				object.AddFilter(new filter_Inchurt2(object, ratio, time, showicon, mask_buff));
			}
		}
		return true;
	}
	bool PlayerWrapper::SetInchurt3(bool)
	{
		if (ratio > 0)
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
			{
				immune |= 0x80;
			}
			else
			{
				int filter_mask = 0;
				int pile_limit = GetAmountInt(); //״̬��������
				if (value > 0.5f)				 //�Ƿ��������??
					filter_mask |= filter::FILTER_MASK_DEBUFF;

				object.AddFilter(new filter_Inchurt3(object, ratio, time, pile_limit, filter_mask));
			}
		}

		return true;
	}
	bool PlayerWrapper::SetInchurt4(bool)
	{
		if (ratio > 0 && ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
			{
				immune |= 0x80;
			}
			else
			{
				int filter_mask = (value > 1.0f ? 0 : (value > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

				object.AddFilter(new filter_Inchurtfromskill(object, ratio, time, GetAmountInt(),
															 filter_mask, FILTER_INCHURT4, VSTATE_INFAUST, HSTATE_INCHURT4));
			}
		}

		return true;
	}
	bool PlayerWrapper::SetInchurt5(bool)
	{
		if (ratio > 0 && ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
			{
				immune |= 0x80;
			}
			else
			{
				int filter_mask = (value > 1.0f ? 0 : (value > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

				object.AddFilter(new filter_Inchurtfromskill(object, ratio, time, GetAmountInt(),
															 filter_mask, FILTER_INCHURT5, 0, HSTATE_INCHURT5));
			}
		}

		return true;
	}
	bool PlayerWrapper::SetInchp2(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Inchp2(object, (int)(ratio * 100 + 0.00001f), time, showicon));
		return true;
	}
	bool PlayerWrapper::SetIncattack2(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incattack2(object, (int)(ratio * 100), time, showicon));
		return true;
	}
	bool PlayerWrapper::SetIncmagic2(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incmagic2(object, (int)(ratio * 100), time, showicon));
		return true;
	}
	bool PlayerWrapper::SetIncmagic3(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incmagic3(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetFastpray2(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fastpray2(object, (int)(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetSpeedup2(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Speedup2(object, (int)(ratio * 100), time, showicon));
		return true;
	}
	bool PlayerWrapper::SetSkillcooldown(bool)
	{
		if (ThrowDice())
		{
			if (value > 0)
				object.SetCoolDown(GetValueInt() + COOLINGID_BEGIN, GetAmountInt());
			if (ratio > 0)
				object.SetCoolDown(GetRatioInt() + COOLINGID_BEGIN, GetAmountInt());
		}
		return true;
	}
	bool PlayerWrapper::SetCommoncooldown(bool)
	{
		if (ThrowDice())
			object.SetCommonCoolDown((int)value - 1, GetAmountInt());
		return true;
	}
	void PlayerWrapper::SetCommonCoolDown(int cd_mask, int ms)
	{
		int i = 0;
		while (cd_mask)
		{
			if (cd_mask & 1)
			{
				object.SetCommonCoolDown(i, ms);
			}
			i++;
			cd_mask >>= 1;
		}
		return;
	}
	bool PlayerWrapper::SetAurafireattack(bool)
	{
		if (ThrowDice())
		{
			//	���Ǽ�ǿ����
			//		value = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), GetValueInt());

			filter_Aurafireattack *pfilter = new filter_Aurafireattack(object, time, (int)value, ratio);
			pfilter->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetAurabless(bool)
	{
		if (ThrowDice())
		{
			filter_Aurabless *pfilter = new filter_Aurabless(object, time, ratio, GetValueInt(), GetAmountInt());
			pfilter->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetAuracurse(bool)
	{
		if (ThrowDice())
		{
			filter_Auracurse *pfilter = new filter_Auracurse(object, time, ratio, GetValueInt(), GetAmountInt());
			pfilter->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetAurabless2(bool)
	{
		filter_Aurabless *pfilter = new filter_Aurabless(object, time, ratio, GetValueInt(), GetAmountInt(), (int)(probability + 0.1f));
		pfilter->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
		object.AddFilter(pfilter);

		return true;
	}

	bool PlayerWrapper::SetAurabless3(bool)
	{
		filter_Aurabless *pfilter = new filter_Aurabless(object, time, ratio, GetValueInt(), GetAmountInt(), (int)(probability + 0.1f), true);
		pfilter->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
		object.AddFilter(pfilter);

		return true;
	}

	bool PlayerWrapper::SetAuracurse2(bool)
	{
		filter_Auracurse *pfilter = new filter_Auracurse(object, time, ratio, GetValueInt(), GetAmountInt(), (int)(probability + 0.1f));
		pfilter->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
		object.AddFilter(pfilter);

		return true;
	}

	bool PlayerWrapper::SetInvisible(bool)
	{
		if (object.GetNoInvisible())
			return true;

		if (object.IsInvisible())
		{
			object.RemoveFilter(FILTER_AURAFIREATTACK);
			object.RemoveFilter(FILTER_AURACURSE);
			object.SetInvisibleFilter(false, time, (int)amount, (int)value, (int)(ratio * 100));
			return true;
		}
		if (ThrowDice())
		{
			object.SetInvisibleFilter(true, time, (int)amount, (int)value, (int)(ratio * 100));
		}
		return true;
	}

	bool PlayerWrapper::SetIncantiinvisibleactive(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Incantiinvisibleactive(object, time, (int)value));
		}
		return true;
	}
	bool PlayerWrapper::SetInchpsteal(bool)
	{
		//ְҵ����,��ʦ��ʦ������â�������������޷�ʹ��
		int cls = GetCls();
		if (cls >= 0 && ((1 << cls) & 0xACE))
			return false;
		if (ThrowDice())
		{
			object.AddFilter(new filter_Inchpsteal(object, time, (int)(ratio * 100.f + 0.00001f)));
		}
		return true;
	}

	bool PlayerWrapper::SetInccritdamage(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Inccritdamage(object, time, (int)(ratio * 100)));
		}
		return true;
	}

	bool PlayerWrapper::SetIncdamagedodge(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Incdamagedodge(object, time, (int)(ratio * 100)));
		}
		return true;
	}

	bool PlayerWrapper::SetIncdebuffdodge(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Incdebuffdodge(object, time, (int)(ratio * 100)));
		}
		return true;
	}

	bool PlayerWrapper::SetRebirth(bool)
	{
		object.AddFilter(new filter_Rebirth(object, time, (int)(probability), ratio));
		return true;
	}

	bool PlayerWrapper::SetDeepenbless(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Deepenbless(object, time, ratio, amount, int(value)));
		}
		return true;
	}

	bool PlayerWrapper::SetWeakenbless(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
				immune |= 0x80;
			else
				object.AddFilter(new filter_Weakenbless(object, time, ratio, amount, int(value)));
		}
		return true;
	}

	bool PlayerWrapper::SetWeakenbless2(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
				immune |= 0x80;
			else
				object.AddFilter(new filter_Weakenbless2(object, time, GetValueInt()));
		}
		return true;
	}

	bool PlayerWrapper::SetHurtwhenuseskill(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
				immune |= 0x80;
			else
			{
				int damage = (int)value;
				damage = object.CalcPhysicDamage(damage, skill->GetPlayerlevel());
				if (object.IsPlayerClass())
				{
					if (skill->GetPerformerid().IsPlayerClass())
						damage = damage >> 2;
				}
				else
				{
					damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
					damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
				}

				//	���Ǽ�ǿ����
				//			damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

				if (damage > 0)
				{
					filter_Hurtwhenuseskill *pfilter;
					pfilter = new filter_Hurtwhenuseskill(object, time, (int)amount, damage);
					pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
					object.AddFilter(pfilter);
				}
			}
		}
		return true;
	}

	bool PlayerWrapper::SetInterruptwhenuseskill(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
				immune |= 0x80;
			else
				object.AddFilter(new filter_Interruptwhenuseskill(object, time, int(amount * 100)));
		}
		return true;
	}

	bool PlayerWrapper::SetSoulretort(bool)
	{
		char delete_type = 0;
		if (amount > 1.5f)
			delete_type = 2;
		else if (amount > 0.5f)
			delete_type = 1;

		//	���Ǽ�ǿ����
		//	value = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), GetValueInt());

		object.AddFilter(new filter_Soulretort(object, time, (int)value, (int)probability, (int)ratio, delete_type));
		return true;
	}

	bool PlayerWrapper::SetSoulsealed(bool)
	{
		char delete_type = 0;
		if (amount > 1.5f)
			delete_type = 2;
		else if (amount > 0.5f)
			delete_type = 1;
		object.AddFilter(new filter_Soulsealed(object, time, (int)value, (int)probability, (int)ratio, delete_type));
		return true;
	}

	bool PlayerWrapper::SetSoulbeatback(bool)
	{
		char delete_type = 0;
		if (amount > 1.5f)
			delete_type = 2;
		else if (amount > 0.5f)
			delete_type = 1;
		object.RemoveFilter(FILTER_SOULSTUN);

		//	���Ǽ�ǿ����
		//	value = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill), GetValueInt());

		object.AddFilter(new filter_Soulbeatback(object, time, (int)value, (int)probability, (int)ratio, delete_type));
		return true;
	}

	bool PlayerWrapper::SetSoulstun(bool)
	{
		char delete_type = 0;
		if (amount > 1.5f)
			delete_type = 2;
		else if (amount > 0.5f)
			delete_type = 1;
		object.RemoveFilter(FILTER_SOULBEATBACK);
		object.AddFilter(new filter_Soulstun(object, time, (int)value, (int)probability, (int)ratio, delete_type));
		return true;
	}

	bool PlayerWrapper::SetFishform(bool)
	{
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.RemoveFilter(FILTER_FISHFORM);
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;
		object.AddFilter(new filter_Fishform(object, (int)(100 * ratio), (int)value));
		return true;
	}

	bool PlayerWrapper::SetEntrap2(bool b)
	{
		int eggid = object.GetPetEggID();
		if (eggid <= 0 || skill->GetPlayerlevel() < GetLevel())
			immune |= 0x80;
		else
		{
			if ((rand() % 100) < probability)
			{
				object.TransferPetEgg(skill->GetPerformerid(), eggid);
				object.Disappear();
				immune |= 0x0200;
			}
			else
				immune |= 0x0100;
		}
		return true;
	}

	bool PlayerWrapper::SetDeepicethrust(bool b)
	{
		if (object.IsFilterExist(FILTER_DEEPICETHRUST))
		{
			object.RemoveFilter(FILTER_DEEPICETHRUST);
			return true;
		}
		if (ThrowDice())
		{
			object.AddFilter(new filter_Deepicethrust(object, time, (int)value, (int)(ratio * 100)));
		}
		return true;
	}

	bool PlayerWrapper::SetAdjustattackdefend(bool b)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Adjustattackdefend(object, time, (int)value, (int)amount));
		return true;
	}

	bool PlayerWrapper::SetClearinvisible(bool b)
	{
		if (object.IsInvisible())
			object.SetInvisibleFilter(false, 0, 0, 0, 0);
		return true;
	}

	bool PlayerWrapper::SetBeastieform(bool b)
	{
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.RemoveFilter(FILTER_TIGERFORM);
			object.RemoveFilter(FILTER_FOXFORM);
			object.RemoveFilter(FILTER_FISHFORM);
			object.RemoveFilter(FILTER_THUNDERFORM);
			object.RemoveFilter(FILTER_SHADOWFORM);
			object.RemoveFilter(FILTER_FAIRYFORM);
			object.RemoveFilter(FILTER_CANNONFORM);
			object.RemoveFilter(FILTER_MONKEYFORM);
		}

		if (GetValueInt() >= 0)
		{
			object.AddFilter(new filter_Beastieform(object, time, GetValueInt(), (int)(ratio * 100)));
		}
		else
		{
			object.RemoveFilter(FILTER_BEASTIEFORM);
		}
		return true;
	}

	bool PlayerWrapper::SetGminvisible(bool)
	{
		if (object.IsGMInvisible())
		{
			object.SetGMInvisibleFilter(false, time, 0);
			return true;
		}
		if (ThrowDice())
		{
			int mask = (value > 0.5f) ? (filter::FILTER_MASK_NOSAVE | filter::FILTER_MASK_SAVE_DB_DATA) : 0;
			object.SetGMInvisibleFilter(true, time, mask);
		}
		return true;
	}
	bool PlayerWrapper::SetActivatesharpener(bool)
	{
		if (ThrowDice())
		{
			object.ActivateSharpener(GetValueInt(), GetAmountInt());
		}
		return true;
	}
	bool PlayerWrapper::SetInchurtphysicgold(bool)
	{
		if (object.IsPlayerClass())
			return false;
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Inchurtphysicgold(object, time, ratio, GetValueInt()));
		}
		return true;
	}
	bool PlayerWrapper::SetInchurtwoodwater(bool)
	{
		if (object.IsPlayerClass())
			return false;
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Inchurtwoodwater(object, time, ratio, GetValueInt()));
		}
		return true;
	}
	bool PlayerWrapper::SetInchurtfireearth(bool)
	{
		if (object.IsPlayerClass())
			return false;
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Inchurtfireearth(object, time, ratio, GetValueInt()));
		}
		return true;
	}
	bool PlayerWrapper::SetAttackattachstate1(bool)
	{
		object.AddFilter(new filter_Attackattachstate(object, time, probability, GetRatioInt(), GetValueInt(), GetAmountInt(), VSTATE_ATTACKATTACHSTATE1, HSTATE_ATTACKATTACHSTATE1));
		return true;
	}
	bool PlayerWrapper::SetAttackattachstate2(bool)
	{
		object.AddFilter(new filter_Attackattachstate(object, time, probability, GetRatioInt(), GetValueInt(), GetAmountInt(), VSTATE_ATTACKATTACHSTATE2, HSTATE_ATTACKATTACHSTATE2));
		return true;
	}
	bool PlayerWrapper::SetAttackattachstate3(bool)
	{
		object.AddFilter(new filter_Attackattachstate(object, time, probability, GetRatioInt(), GetValueInt(), GetAmountInt(), VSTATE_ATTACKATTACHSTATE3, HSTATE_ATTACKATTACHSTATE3));
		return true;
	}
	bool PlayerWrapper::SetAttackattachstate4(bool)
	{
		object.AddFilter(new filter_Attackattachstate(object, time, probability, GetRatioInt(), GetValueInt(), GetAmountInt(), VSTATE_ATTACKATTACHSTATE4, HSTATE_ATTACKATTACHSTATE4));
		return true;
	}
	bool PlayerWrapper::SetBeattackattachstate1(bool)
	{
		object.AddFilter(new filter_Beattackedattachstate(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), showicon, HSTATE_BEATTACKEDATTACHSTATE1, FILTER_BEATTACKEDATTACHSTATE1));
		return true;
	}
	bool PlayerWrapper::SetBeattackattachstate2(bool)
	{
		object.AddFilter(new filter_Beattackedattachstate(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), showicon, HSTATE_BEATTACKEDATTACHSTATE2, FILTER_BEATTACKEDATTACHSTATE2));
		return true;
	}
	bool PlayerWrapper::SetBeattackattachstate3(bool)
	{
		object.AddFilter(new filter_Beattackedattachstate(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), showicon, HSTATE_BEATTACKEDATTACHSTATE3, FILTER_BEATTACKEDATTACHSTATE3));
		return true;
	}
	bool PlayerWrapper::SetBeattackattachstate4(bool)
	{
		object.AddFilter(new filter_Beattackedattachstate(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), showicon, HSTATE_BEATTACKEDATTACHSTATE4, FILTER_BEATTACKEDATTACHSTATE4));
		return true;
	}
	bool PlayerWrapper::SetBeattackattachstate5(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Beattackedattachstate(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), true, HSTATE_BEATTACKEDATTACHSTATE1, FILTER_BEATTACKEDATTACHSTATE1));
		}
		return true;
	}
	bool PlayerWrapper::SetBeattackattachstate6(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Beattackedattachstate(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), true, HSTATE_BEATTACKEDATTACHSTATE2, FILTER_BEATTACKEDATTACHSTATE2));
		}
		return true;
	}
	bool PlayerWrapper::SetBeattackattachstate7(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Beattackedattachstate(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), true, HSTATE_BEATTACKEDATTACHSTATE3, FILTER_BEATTACKEDATTACHSTATE3));
		}
		return true;
	}
	bool PlayerWrapper::SetBeattackattachstate8(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Beattackedattachstate(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), true, HSTATE_BEATTACKEDATTACHSTATE4, FILTER_BEATTACKEDATTACHSTATE4));
		}
		return true;
	}
	bool PlayerWrapper::SetTransferbuff(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.TransferSpecFilters(filter::FILTER_MASK_TRANSFERABLE_BUFF, skill->GetPerformerid(), GetValueInt());
		}
		return true;
	}
	bool PlayerWrapper::SetTransferdebuff(bool)
	{
		if (ThrowDice())
			object.TransferSpecFilters(filter::FILTER_MASK_TRANSFERABLE_DEBUFF, skill->GetPerformerid(), GetValueInt());
		return true;
	}
	bool PlayerWrapper::SetAbsorbbuff(bool)
	{
		if (ThrowDice())
			object.AbsorbSpecFilters(filter::FILTER_MASK_TRANSFERABLE_BUFF, skill->GetPerformerid(), GetValueInt());
		return true;
	}
	bool PlayerWrapper::SetAbsorbdebuff(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AbsorbSpecFilters(filter::FILTER_MASK_TRANSFERABLE_DEBUFF, skill->GetPerformerid(), GetValueInt());
		}
		return true;
	}
	bool PlayerWrapper::SetSummonpet2(bool)
	{
		object.SummonPet2(GetValueInt(), GetRatioInt(), time, (target ? *target : XID(-1, -1)), skill->GetForceattack()); //value��pet_egg_id
		return true;
	}
	bool PlayerWrapper::SetSummonplantpet(bool)
	{
		for (int i = 0; i < GetAmountInt(); i++)
			object.SummonPlantPet(GetValueInt(), GetRatioInt(), time, (target ? *target : XID(-1, -1)), skill->GetForceattack()); //value��pet_egg_id
		return true;
	}
	bool PlayerWrapper::SetPetsacrifice(bool)
	{
		object.PetSacrifice();
		return true;
	}
	bool PlayerWrapper::SetPlantsuicide(bool)
	{
		object.PlantSuicide(value, (target ? *target : XID(-1, -1)), skill->GetForceattack()); //���һ���ٻ��Ŀɱ�ըֲ�������˵ľ���С��value�ſ��Ա�ը
		return true;
	}
	bool PlayerWrapper::SetPoisionseed(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEWOOD | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int damage = (int)value;
		damage = object.CalcMagicDamage(1, damage, skill->GetPlayerlevel());
		if (object.IsPlayerClass())
		{
			if (skill->GetPerformerid().IsPlayerClass())
				damage = damage >> 2;
		}
		else
		{
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}

		//	���Ǽ�ǿ����
		//	damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

		if (damage > 0)
		{
			filter_Poisionseed *pfilter = new filter_Poisionseed(object, time, damage, GetAmountInt() / 1000, ratio);
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}
	bool PlayerWrapper::SetHpgenseed(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Hpgenseed(object, time, GetValueInt(), GetAmountInt() / 1000, (int)ratio));
		}
		return true;
	}
	bool PlayerWrapper::SetPhysichurt(bool)
	{
		if (object.GetImmuneMask() & (IMMUNEPHYSICAL | IMMUNEALL))
			immune |= 0x80;
		else
		{
			int damage = (int)value;
			damage = object.CalcPhysicDamage(damage, skill->GetPlayerlevel());
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
					damage = damage >> 2;
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
			}

			//	���Ǽ�ǿ����
			//		damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

			if (damage > 0)
			{
				object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), damage, invader,
							  skill->GetAttackerMode());
			}
		}
		return true;
	}
	bool PlayerWrapper::SetGoldhurt(bool)
	{
		if (object.GetImmuneMask() & (IMMUNEMETAL | IMMUNEALL))
			immune |= 0x80;
		else
		{
			int damage = (int)value;
			damage = object.CalcMagicDamage(0, damage, skill->GetPlayerlevel());
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
					damage = damage >> 2;
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
			}

			//	���Ǽ�ǿ����
			//		damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

			if (damage > 0)
			{
				object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), damage, invader,
							  skill->GetAttackerMode());
			}
		}
		return true;
	}
	bool PlayerWrapper::SetWoodhurt(bool)
	{
		if (object.GetImmuneMask() & (IMMUNEWOOD | IMMUNEALL))
			immune |= 0x80;
		else
		{
			int damage = (int)value;
			damage = object.CalcMagicDamage(1, damage, skill->GetPlayerlevel());
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
					damage = damage >> 2;
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
			}

			//	���Ǽ�ǿ����
			//		damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

			if (damage > 0)
			{
				object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), damage, invader,
							  skill->GetAttackerMode());
			}
		}
		return true;
	}
	bool PlayerWrapper::SetWaterhurt(bool)
	{
		if (object.GetImmuneMask() & (IMMUNEWATER | IMMUNEALL))
			immune |= 0x80;
		else
		{
			int damage = (int)value;
			damage = object.CalcMagicDamage(2, damage, skill->GetPlayerlevel());
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
					damage = damage >> 2;
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
			}

			//	���Ǽ�ǿ����
			//		damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

			if (damage > 0)
			{
				object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), damage, invader,
							  skill->GetAttackerMode());
			}
		}
		return true;
	}
	bool PlayerWrapper::SetFirehurt(bool)
	{
		if (object.GetImmuneMask() & (IMMUNEFIRE | IMMUNEALL))
			immune |= 0x80;
		else
		{
			int damage = (int)value;
			damage = object.CalcMagicDamage(3, damage, skill->GetPlayerlevel());
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
					damage = damage >> 2;
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
			}

			//	���Ǽ�ǿ����
			//		damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

			if (damage > 0)
			{
				object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), damage, invader,
							  skill->GetAttackerMode());
			}
		}
		return true;
	}
	bool PlayerWrapper::SetEarthhurt(bool)
	{
		if (object.GetImmuneMask() & (IMMUNESOIL | IMMUNEALL))
			immune |= 0x80;
		else
		{
			int damage = (int)value;
			damage = object.CalcMagicDamage(4, damage, skill->GetPlayerlevel());
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
					damage = damage >> 2;
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
			}

			//	���Ǽ�ǿ����
			//		damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

			if (damage > 0)
			{
				object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), damage, invader,
							  skill->GetAttackerMode());
			}
		}
		return true;
	}
	bool PlayerWrapper::SetFastprayincmagic(bool)
	{
		object.AddFilter(new filter_Fastprayincmagic(object, time, int(ratio * 100), int(value * 100)));
		return true;
	}
	bool PlayerWrapper::SetIncwoodwaterdefense(bool)
	{
		object.AddFilter(new filter_Incwoodwaterdefense(object, time, int(ratio * 100), int(value * 100), int(amount * 100)));
		return true;
	}
	bool PlayerWrapper::SetSpecialslow(bool) //���ڽ��м���Ч���ˣ��൱��slow2
	{
		if (object.GetImmuneMask() & (IMMUNESLOW | IMMUNEALL))
			immune |= 0x80;
		else
			object.AddFilter(new filter_Specialslow(object, int(ratio * 100), time));
		return true;
	}
	bool PlayerWrapper::SetSpecialphysichurt(bool)
	{
		if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
		{
			immune |= 0x80;
			return true;
		}
		int damage;
		if (object.IsPlayerClass())
		{
			damage = object.CalcPhysicDamage((int)value, skill->GetPlayerlevel());
			if (skill->GetPerformerid().IsPlayerClass())
				damage = damage >> 2;
		}
		else
		{
			damage = object.CalcPhysicDamage((int)amount, skill->GetPlayerlevel());
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}

		if (object.IsFilterExist(FILTER_SPECIALPHYSICHURTTRIGGER))
			damage = (int)(damage * (1.f + ratio));
		if (damage > 0)
		{
			object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), damage, invader,
						  skill->GetAttackerMode());
		}
		return true;
	}
	bool PlayerWrapper::SetIncdefencesmite(bool)
	{
		object.AddFilter(new filter_Incdefencesmite(object, time, int(ratio * 100), int(value * 100)));
		return true;
	}
	bool PlayerWrapper::SetIncresistmagic(bool)
	{
		object.AddFilter(new filter_Incresistmagic(object, time, int(ratio * 100), int(value * 100)));
		return true;
	}
	bool PlayerWrapper::SetTransportmptopet(bool)
	{
		if (object.IsFilterExist(FILTER_TRANSPORTMPTOPET))
		{
			object.RemoveFilter(FILTER_TRANSPORTMPTOPET);
			return true;
		}
		object.AddFilter(new filter_Transportmptopet(object, time, (int)value, (int)amount, ratio));
		return true;
	}
	bool PlayerWrapper::SetTransportdamagetopet(bool)
	{
		if (object.GetSelfID() == skill->GetPerformerid())
			return false;
		object.AddFilter(new filter_Transportdamagetopet(object, time, value, skill->GetPerformerid(), amount, ratio));
		return true;
	}
	bool PlayerWrapper::SetAbsorbdamageincdefense(bool)
	{
		object.AddFilter(new filter_Absorbdamageincdefense(object, time, (int)amount, (int)(ratio * 100), (int)(value * 100)));
		return true;
	}
	bool PlayerWrapper::SetIncrementalhpgen(bool)
	{
		object.AddFilter(new filter_Incrementalhpgen(object, time, (int)value, (int)ratio));
		return true;
	}
	bool PlayerWrapper::SetChanceofrebirth(bool)
	{
		object.AddFilter(new filter_Chanceofrebirth(object, time, ratio, value, amount));
		return true;
	}
	bool PlayerWrapper::SetSpecialphysichurttrigger(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Specialphysichurttrigger(object, time));
		}
		return true;
	}
	bool PlayerWrapper::SetLongjumptospouse(bool)
	{
		object.LongJumpToSpouse();
		return true;
	}
	bool PlayerWrapper::SetInccountedsmite(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Inccountedsmite(object, time, GetValueInt(), GetRatioInt(), GetAmountInt()));
		}
		return true;
	}
	bool PlayerWrapper::SetWeapondisabled(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Weapondisabled(object, time));
		}
		return true;
	}
	bool PlayerWrapper::SetIncaggroondamage(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Incaggroondamage(object, time, skill->GetPerformerid(), int(ratio * 100)));
		}
		return true;
	}
	bool PlayerWrapper::SetEnhanceskilldamage(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Enhanceskilldamage(object, time, int(ratio * 100)));
		}
		return true;
	}
	bool PlayerWrapper::SetDetectinvisible(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Detectinvisible(object, time, value));
		}
		return true;
	}
	bool PlayerWrapper::SetDetectinvisible2(bool)
	{
		if (ThrowDice())
			object.DetectInvisible(value);
		return true;
	}
	bool PlayerWrapper::SetFastmpgen2(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Fastmpgen2(object, (int)(value), time));
		return true;
	}
	bool PlayerWrapper::SetClearinvisible2(bool)
	{
		if (object.IsInvisible())
			object.SetInvisibleFilter(false, 0, 0, 0, 0);
		object.Heal((int)(GetMaxhp() * ratio));
		return true;
	}

	bool PlayerWrapper::SetPositionrollback(bool)
	{
		if (ThrowDice())
		{
			if (object.GetWorldTag() == 1)
				if (!object.IsInSanctuary(object.GetPos()))
					object.AddFilter(new filter_Positionrollback(object, time, object.GetWorldTag(), object.GetPos()));
		}
		return true;
	}

	bool PlayerWrapper::SetPositionrollback2(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Positionrollback2(object, time, object.GetWorldTag(), object.GetPos()));
		}
		return true;
	}

	bool PlayerWrapper::SetHprollback(bool)
	{
		if (ThrowDice())
		{
			if (object.IsPlayerClass())
				object.AddFilter(new filter_Hprollback(object, time, object.GetBasicProp().hp));
		}
		return true;
	}

	bool PlayerWrapper::SetNofly(bool)
	{
		if (ThrowDice())
		{
			if (object.IsPlayerClass())
				object.AddFilter(new filter_Nofly(object, time));
		}
		return true;
	}

	bool PlayerWrapper::SetForceselecttarget(bool)
	{
		if (ThrowDice())
		{
			if (object.IsPlayerClass())
			{
				object.ForceSelectTarget(skill->GetPerformerid());
				object.AddFilter(new filter_Nochangeselect(object, time));
			}
		}
		return true;
	}

	bool PlayerWrapper::SetHealabsorb(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Healabsorb(object, time, (int)value, GetAmountInt()));
		}
		return true;
	}
	bool PlayerWrapper::SetRepelonnormalattack(bool)
	{
		//ֻ�ܼ����������??
		if (object.IsPlayerClass())
		{
			//���ڷ�ʦ��˵��BUFF
			object.AddFilter(new filter_Repelonnormalattack(object, time, (int)probability, value, (int)amount, (int)ratio / 1000));
		}
		return true;
	}
	bool PlayerWrapper::SetInccritresistance(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Inccritresistance(object, time, (int)value));
		}
		return true;
	}
	bool PlayerWrapper::SetDeccritresistance(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Deccritresistance(object, time, (int)value));
		}
		return true;
	}
	bool PlayerWrapper::SetExchangeposition(bool)
	{
		if (ThrowDice())
		{
			object.ExchangePosition(skill->GetPerformerid());
		}
		return true;
	}
	bool PlayerWrapper::SetPullover(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL))
				immune |= 0x80;
			else
				object.PullOver(skill->GetPerformerid(), skill->GetPerformerpos(), value, (int)amount);
		}
		return true;
	}
	bool PlayerWrapper::SetTransmitskillattack(bool)
	{
		if (ThrowDice())
		{
			if (object.IsPlayerClass() && skill->GetPerformerid() != object.GetSelfID())
				object.AddFilter(new filter_Transmitskillattack(object, time, skill->GetPerformerid(), value));
		}
		return true;
	}
	bool PlayerWrapper::SetAdditionalheal(bool)
	{
		if (object.IsPlayerClass())
		{
			const XID &cur_target = object.GetCurTargetID();
			if (cur_target.IsActive() && cur_target != object.GetSelfID())
				object.AddFilter(new filter_Additionalheal(object, time, cur_target, ratio, value));
		}
		return true;
	}
	bool PlayerWrapper::SetAdditionalattack(bool)
	{
		if (object.IsPlayerClass())
		{
			const XID &cur_target = object.GetCurTargetID();
			if (cur_target.IsActive() && cur_target != object.GetSelfID())
				object.AddFilter(new filter_Additionalattack(object, time, cur_target, ratio, value));
		}
		return true;
	}
	bool PlayerWrapper::SetTransportdamagetoleader(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Transportdamagetoleader(object, time, ratio, object.GetLeaderID(), value));
		}
		return true;
	}
	bool PlayerWrapper::SetForbidbeselected(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Forbidbeselected(object, time));
		return true;
	}
	bool PlayerWrapper::SetEnhanceskilldamage2(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Enhanceskilldamage2(object, time, int(ratio * 100)));
		}
		return true;
	}
	bool PlayerWrapper::SetCallupteammember(bool)
	{
		//ע��:����Ͱ��ɻس�һ��ʹ����target����,�ͻ�����Ҫ���⴦��
		if (target)
			object.CallUpTeamMember(*target);
		return true;
	}
	bool PlayerWrapper::SetDelayearthhurt(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNESOIL | IMMUNEALL))
				immune |= 0x80;
			else
			{
				int damage = (int)value;
				damage = object.CalcMagicDamage(4, damage, skill->GetPlayerlevel());
				if (object.IsPlayerClass())
				{
					if (skill->GetPerformerid().IsPlayerClass())
						damage = damage >> 2;
				}
				else
				{
					damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
					damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
				}
				// ���Ǽ�����?
				//			damage = object.CalcVigourEnhanceDamage(skill->GetVigour(),	object.GetVigour(),	IS_PVP(object,skill),damage);

				if (damage > 0)
				{
					filter_Delayearthhurt *pfilter = new filter_Delayearthhurt(object, time, damage);
					pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
					object.AddFilter(pfilter);
				}
			}
		}
		return true;
	}
	bool PlayerWrapper::SetDizzyinchurt(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Dizzyinchurt(object, ratio, time));
		}
		return true;
	}
	bool PlayerWrapper::SetSoulretort2(bool)
	{
		char delete_type = 0;
		if (amount > 1.5f)
			delete_type = 2;
		else if (amount > 0.5f)
			delete_type = 1;
		object.AddFilter(new filter_Soulretort2(object, time, value, (int)probability, (int)ratio, delete_type));
		return true;
	}
	bool PlayerWrapper::SetFixondamage(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEFIX | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Fixondamage(object, time, (int)value / 1000, (int)ratio / 1000));
		}
		return true;
	}
	bool PlayerWrapper::SetApgen2(bool)
	{
		object.AddFilter(new filter_Apgen2(object, time, (int)ratio, (int)value));
		return true;
	}
	bool PlayerWrapper::SetIncattackondamage(bool)
	{
		object.AddFilter(new filter_Incattackondamage(object, time, (int)value, (int)probability / 1000, (int)(ratio * 100), (int)amount));
		return true;
	}
	bool PlayerWrapper::SetRebirth2(bool)
	{
		object.AddFilter(new filter_Rebirth2(object, time, ratio, (int)value));
		return true;
	}
	bool PlayerWrapper::SetHealsteal(bool)
	{
		object.AddFilter(new filter_Healsteal(object, time, skill->GetPerformerid(), value, ratio));
		return true;
	}
	bool PlayerWrapper::SetDropmoneyondeath(bool)
	{
		if (object.GetImmuneMask() & (IMMUNEDROP | IMMUNEALL))
			immune |= 0x80;
		else
			object.AddFilter(new filter_Dropmoneyondeath(object, time, (int)value));
		return true;
	}
	bool PlayerWrapper::SetIncattackrange(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Incattackrange(object, time, value));
		}
		return true;
	}
	bool PlayerWrapper::SetQueryotherinventory(bool)
	{
		if (object.IsPlayerClass())
		{
			const XID &cur_target = object.GetCurTargetID();
			if (cur_target.IsPlayerClass() && cur_target != object.GetSelfID())
				object.QueryOtherInventory(cur_target);
		}
		return true;
	}
	bool PlayerWrapper::SetThunderform(bool)
	{
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.RemoveFilter(FILTER_THUNDERFORM);
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;
		object.AddFilter(new filter_Thunderform(object, (int)ratio, (int)(100 * value)));
		return true;
	}

	bool PlayerWrapper::SetDelaytransmit(bool)
	{
		int tag = (int)(probability + 0.00001f);
		A3DVECTOR pos(ratio, amount, value);
		if (tag != object.GetWorldTag() || !object.IsInSanctuary(pos))
			object.AddFilter(new filter_Delaytransmit(object, time, tag, pos));
		return true;
	}
	bool PlayerWrapper::SetDecnormalattackhurt(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Decnormalattackhurt(object, time, (int)(value + 0.00001f) / 1000, ratio));
		}
		return true;
	}
	bool PlayerWrapper::SetFreemoveapgen(bool)
	{
		object.AddFilter(new filter_Freemoveapgen(object, time, ratio, (int)amount));
		return true;
	}

	bool PlayerWrapper::SetIncatkdefhp(bool)
	{
		object.AddFilter(new filter_Incatkdefhp(object, time, (int)(value * 100), (int)(ratio * 100), (int)(amount * 100)));
		return true;
	}
	bool PlayerWrapper::SetDenyattackcmd(bool)
	{
		object.AddFilter(new filter_Denyattackcmd(object, time));
		return true;
	}
	bool PlayerWrapper::SetHpmpgennotincombat(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Hpmpgennotincombat(object, time, (int)value, (int)amount));
		}
		return true;
	}

	bool PlayerWrapper::SetInchpmp(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Inchpmp(object, time, (int)value, (int)amount));
		}
		return true;
	}
	bool PlayerWrapper::SetEnternonpenaltypvp(bool)
	{
		object.SetNonpenaltyPVPFilter(true, time);
		return true;
	}
	bool PlayerWrapper::SetLeavenonpenaltypvp(bool)
	{
		object.SetNonpenaltyPVPFilter(false, 0);
		return true;
	}
	bool PlayerWrapper::SetIncmaxhpatkdfdlevel(bool)
	{
		object.AddFilter(new filter_Incmaxhpatkdfdlevel(object, time, ratio, (int)amount, (int)value, showicon ? filter::FILTER_MASK_BUFF : 0));
		return true;
	}
	bool PlayerWrapper::SetSubdefencedegree2(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & IMMUNEALL)
			{
				immune |= 0x80;
				return false;
			}
			object.AddFilter(new filter_Subdefencedegree2(object, (int)value, time));
		}
		return true;
	}
	bool PlayerWrapper::SetIncatkdefhp2(bool)
	{
		object.AddFilter(new filter_Incatkdefhp2(object, time, (int)(value * 100), (int)(ratio * 100), (int)(amount * 100)));
		return true;
	}
	bool PlayerWrapper::SetIncsmite3(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Incsmite3(object, (int)(value), time));
		return true;
	}
	bool PlayerWrapper::SetIncpenres(bool)
	{
		object.AddFilter(new filter_Incpenres(object, time, GetAmountInt(), GetValueInt()));
		return true;
	}
	bool PlayerWrapper::SetAttachstatetoself(bool)
	{
		int skill_id = GetAmountInt();
		int skill_lvl = GetValueInt();
		int mask_filter = showicon ? filter::FILTER_MASK_BUFF : 0;
		object.AddFilter(new filter_Attachstatetoself(object, time, skill_id, skill_lvl, int(probability), mask_filter));
		return true;
	}
	bool PlayerWrapper::SetAttachstatetotarget(bool)
	{
		int skill_id = GetAmountInt();
		int skill_lvl = GetValueInt();
		int mask_filter = showicon ? filter::FILTER_MASK_BUFF : 0;
		object.AddFilter(new filter_Attachstatetotarget(object, time, skill_id, skill_lvl, int(probability), mask_filter));
		return true;
	}

	bool PlayerWrapper::SetImmunephysical2(bool b)
	{
		if (ThrowDice())
		{
			int mask_filter = (value > 0.5) ? filter::FILTER_MASK_BUFF : 0;
			object.AddFilter(new filter_Immunephysical2(object, time, mask_filter));
		}
		return true;
	}
	bool PlayerWrapper::SetImmunefire2(bool b)
	{
		if (ThrowDice())
		{
			int mask_filter = (value > 0.5) ? filter::FILTER_MASK_BUFF : 0;
			object.AddFilter(new filter_Immunefire2(object, time, mask_filter, showicon));
		}
		return true;
	}
	bool PlayerWrapper::SetImmunewater2(bool b)
	{
		if (ThrowDice())
		{
			int mask_filter = (value > 0.5) ? filter::FILTER_MASK_BUFF : 0;
			object.AddFilter(new filter_Immunewater2(object, time, mask_filter, showicon));
		}
		return true;
	}
	bool PlayerWrapper::SetImmunemetal2(bool b)
	{
		if (ThrowDice())
		{
			int mask_filter = (value > 0.5) ? filter::FILTER_MASK_BUFF : 0;
			object.AddFilter(new filter_Immunemetal2(object, time, mask_filter, showicon));
		}
		return true;
	}
	bool PlayerWrapper::SetImmunewood2(bool b)
	{
		if (ThrowDice())
		{
			int mask_filter = (value > 0.5) ? filter::FILTER_MASK_BUFF : 0;
			object.AddFilter(new filter_Immunewood2(object, time, mask_filter, showicon));
		}
		return true;
	}
	bool PlayerWrapper::SetImmunesoil2(bool b)
	{
		if (ThrowDice())
		{
			int mask_filter = (value > 0.5) ? filter::FILTER_MASK_BUFF : 0;
			object.AddFilter(new filter_Immunesoil2(object, time, mask_filter, showicon));
		}
		return true;
	}
	bool PlayerWrapper::SetRetort2(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Retort2(object, ratio, value, time));
		return true;
	}

	bool PlayerWrapper::SetPalsy(bool b)
	{
		if (ThrowDice())
		{
			if (object.IsPalsyImmune())
				immune |= 0x80;
			else
			{
				int mask = (value > 1.0f ? 0 : (value > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
				object.AddFilter(new filter_Palsy(object, time, mask));
			}
		}
		return true;
	}

	bool PlayerWrapper::SetIncbecritrate(bool b)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
			{
				int mask = (value > 1.0f ? 0 : (value > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
				object.AddFilter(new filter_Incbecritrate(object, time, GetAmountInt(), mask));
			}
		}

		return true;
	}

	bool PlayerWrapper::SetModifyspecskillpray(bool b)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Modifyspecskillpray(object, time, GetAmountInt(), GetValueInt(), ratio));
		}

		return true;
	}

	bool PlayerWrapper::SetIncspecskilldamage(bool b)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Incspecskilldamage(object, time, GetAmountInt(), GetValueInt(), ratio));
		}

		return true;
	}

	bool PlayerWrapper::SetFireshield2(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Fireshield2(object, time, GetAmountInt(), GetValueInt(), (int)(GetRatio() * 100)));
		}

		return true;
	}

	bool PlayerWrapper::SetIceshield2(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Iceshield2(object, time, GetAmountInt(), GetValueInt(), (int)(GetRatio() * 100)));
		}

		return true;
	}

	bool PlayerWrapper::SetHealshield(bool)
	{
		if (ThrowDice())
		{
			int mask = (ratio > 1.0f ? 0 : (ratio > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Healshield(object, time, GetAmountInt(), GetValueInt(), mask));
		}

		return true;
	}

	bool PlayerWrapper::SetIncflyspeed(bool)
	{
		if (ThrowDice())
		{
			int mask = (value > 1.0f ? 0 : (value > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Incflyspeed(object, time, mask, (int)(ratio * 100), GetAmountInt()));
		}

		return true;
	}

	bool PlayerWrapper::SetIncvigour(bool)
	{
		if (ThrowDice())
		{
			int mask = (ratio > 0.5f ? filter::FILTER_MASK_BUFF : 0);
			object.AddFilter(new filter_Incvigour(object, time, mask, GetAmountInt()));
		}

		return true;
	}

	bool PlayerWrapper::SetIncvigour2(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Incvigour2(object, time, mask, GetValueInt(), GetRatioInt()));
		}

		return true;
	}

	bool PlayerWrapper::SetShortjump(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Shortjump(object, time, GetValueInt(), mask));
		}
		return true;
	}

	bool PlayerWrapper::SetShortjump2(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Shortjump2(object, time, GetValueInt(), mask));
		}
		return true;
	}

	bool PlayerWrapper::SetMovepunish(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEALL | IMMUNEMETAL))
			{
				immune |= 0x80;
				return true;
			}
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			int damage = CALC_MAGIC_DMG<0>(object, skill, GetValueInt(), GetValueInt());
			filter_Movepunish *pfilter = new filter_Movepunish(object, time, damage, mask);
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetStandpunish(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEALL))
			{
				immune |= 0x80;
				return true;
			}
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			filter_Standpunish *pfilter = new filter_Standpunish(object, time, GetRatioInt(), GetValueInt(), mask);
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetStandpunish2(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEALL))
			{
				immune |= 0x80;
				return true;
			}
			object.AddFilter(new filter_Standpunish2(object, time, GetRatioInt(), GetValueInt(), GetAmountInt(), skill->GetPerformerid()));
		}
		return true;
	}

	bool PlayerWrapper::SetChantshield(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Chantshield(object, time, GetValueInt(), GetRatioInt(), mask));
		}
		return true;
	}

	bool PlayerWrapper::SetChangeselfaggro(bool)
	{
		if (target && ThrowDice())
		{
			if (time)
				object.AddFilter(new filter_Changeselfaggro(object, time, *target, GetValueInt()));
			else
				object.AddAggro(*target, GetValueInt());
		}
		return true;
	}

	bool PlayerWrapper::SetSummonmobs(bool)
	{
		if (ThrowDice())
		{
			object_interface::minor_param param;
			memset(&param, 0, sizeof(param));
			param.mob_id = GetValueInt();
			param.remain_time = time;
			param.die_with_who = GetRatioInt();

			if (GetRatioInt() == 1) //���ٻ�������������
			{
				param.parent_is_leader = false;
				param.spec_leader_id = skill->GetPerformerid();
			}
			else if (GetRatioInt() == 2) //��Ŀ������������
			{
				param.target_id = object.GetSelfID();
			}
			else if (GetRatioInt() == 3) //���ٻ��ߺ�Ŀ��֮һ����������
			{
				param.parent_is_leader = false;
				param.spec_leader_id = skill->GetPerformerid();
				param.target_id = object.GetSelfID();
			}
			for (int n = 0; n < GetAmountInt(); ++n)
			{
				object.CreateMinors(param, 5.f);
			}
		}
		return true;
	}

	bool PlayerWrapper::SetIntervalpalsy(bool)
	{
		if (ThrowDice())
		{
			if (object.IsPalsyImmune())
			{
				immune |= 0x80;
				return true;
			}
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Intervalpalsy(object, time, GetValueInt(), GetRatioInt(), mask));
		}
		return true;
	}

	bool PlayerWrapper::SetInternalinjury(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEALL | IMMUNEMETAL))
			{
				immune |= 0x80;
				return true;
			}
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			int damage = CALC_MAGIC_DMG<0>(object, skill, GetValueInt(), GetValueInt());
			filter_Internalinjury *pfilter = new filter_Internalinjury(object, time, GetRatioInt(), damage, mask);
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetAtkdamagereduce(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Atkdamagereduce(object, time, GetRatioInt(), mask));
		}
		return true;
	}

	bool PlayerWrapper::SetDeathresetcd(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Deathresetcd(object, time, skill->GetPerformerid(), GetValueInt(), GetAmountInt(), GetRatioInt()));
		}
		return true;
	}

	bool PlayerWrapper::SetAppendenchant(bool)
	{
		object.AddFilter(new filter_Appendenchant(object, time, GetProbabilityInt(), GetValueInt(), GetRatioInt(), GetAmountInt()));
		return true;
	}

	bool PlayerWrapper::SetAppenddamage(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Appenddamage(object, time, GetValueInt(), GetRatioInt(), GetAmountInt()));
		}
		return true;
	}

	bool PlayerWrapper::SetCooldownaward(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Cooldownaward(object, time, GetValueInt(), GetRatioInt(), mask));
		}
		return true;
	}

	bool PlayerWrapper::SetHuntersoul(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEALL))
			{
				immune |= 0x80;
				return true;
			}
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			int damage = GetValueInt();
			damage = object.CalcPhysicDamage(damage, skill->GetPlayerlevel());
			if (object.IsPlayerClass())
			{
				if (skill->GetPerformerid().IsPlayerClass())
					damage = damage >> 2;
			}
			else
			{
				damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
				damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
			}

			filter_Huntersoul *pfilter = new filter_Huntersoul(object, time, damage, GetRatioInt(), mask, skill->GetPerformerid());
			pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetNeverdead(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			filter_Neverdead *pfilter = new filter_Neverdead(object, time, mask);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetChangemodel(bool)
	{
		if (ThrowDice())
		{
			if (time > 0) // temp
			{
				filter_Changemodel *pfilter = new filter_Changemodel(object, time, GetValueInt());
				object.AddFilter(pfilter);
			}
			else // forever
				object.ChangeVisibleTypeId(GetValueInt());
		}

		return true;
	}

	bool PlayerWrapper::SetScreeneffect(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			filter_Screeneffect *pfilter = new filter_Screeneffect(object, time, GetValueInt(), mask);
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetShadowform(bool b)
	{
		int form = object.GetForm();
		if (form != FORM_NORMAL)
		{
			return false;
		}

		object.AddFilter(new filter_Shadowform(object, time, (int)(100 * ratio + 0.00001f), value));
		return true;
	}

	bool PlayerWrapper::SetFairyform(bool b)
	{
		int form = object.GetForm();
		if (form != FORM_NORMAL)
		{
			return false;
		}

		object.AddFilter(new filter_Fairyform(object, time, (int)(100 * ratio + 0.00001f), (int)(100 * value + 0.00001f)));
		return true;
	}

	bool PlayerWrapper::SetAddfrosteffect(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & IMMUNEALL)
		{
			immune |= 0x80;
			return false;
		}

		int metal_dmg = GetValueInt();
		int water_dmg = GetAmountInt();
		metal_dmg = object.CalcMagicDamage(0, metal_dmg, skill->GetPlayerlevel());
		water_dmg = object.CalcMagicDamage(2, water_dmg, skill->GetPlayerlevel());

		if (!object.IsPlayerClass())
		{
			metal_dmg = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), metal_dmg);
			water_dmg = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), water_dmg);
		}

		if (object.GetImmuneMask() & IMMUNEMETAL)
			metal_dmg = 0;
		if (object.GetImmuneMask() & IMMUNEWATER)
			water_dmg = 0;

		if (object.IsPlayerClass())
		{
			if (skill->GetPerformerid().IsPlayerClass())
			{
				metal_dmg = (int)(0.25 * metal_dmg);
				water_dmg = (int)(0.25 * water_dmg);
			}
		}
		else
		{
			metal_dmg = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * metal_dmg);
			water_dmg = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * water_dmg);
		}

		int mask = (ratio > 1.0f ? 0 : (ratio > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		int damage = metal_dmg + water_dmg;

		filter_Addfrosteffect *pfilter = new filter_Addfrosteffect(object, time, mask, damage);
		pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
		object.AddFilter(pfilter);
		return true;
	}

	bool PlayerWrapper::SetActivefrosteffect(bool)
	{
		if (!ThrowDice())
			return false;
		if (!object.IsFilterExist(FILTER_ADDFROSTEFFECT))
			return false;

		int total_damage = (int)(object.QueryFilter(FILTER_ADDFROSTEFFECT, filter::FILTER_QUERY_DAMAGE) * ratio);
		object.BeHurt(skill->GetPerformerid(), skill->GetPerformerinfo(), total_damage, invader, skill->GetAttackerMode());
		object.RemoveFilter(FILTER_ADDFROSTEFFECT);
		return true;
	}

	bool PlayerWrapper::SetIncspecskillcrit(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Incspecskillcrit(object, time, GetAmountInt(), GetValueInt(), GetRatioInt()));
		}
		return true;
	}

	bool PlayerWrapper::SetClearfilterbyid(bool)
	{
		if (ThrowDice())
		{
			int filter_id = GetValueInt();
			object.RemoveFilter(filter_id);
		}
		return true;
	}

	bool PlayerWrapper::SetMoongod(bool)
	{
		object.AddFilter(new filter_Moongod(object, time, ratio, value));
		return true;
	}

	bool PlayerWrapper::SetDelayskilleffect(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			filter_Delayskilleffect *pfilter = new filter_Delayskilleffect(object, time, mask, GetValueInt(), GetRatioInt(), skill->GetPerformerid());
			object.AddFilter(pfilter);
		}
		return true;
	}

	bool PlayerWrapper::SetEnhanceskilldamage3(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Enhanceskilldamage3(object, time, int(ratio * 100))); //object.AddFilter(new filter_Enhanceskilldamage3(object, time, int(ratio * 100 + 0.00001f)));
		}
		return true;
	}

	bool PlayerWrapper::SetCritdamagereduce(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Critdamagereduce(object, time, GetRatioInt()));
		}
		return true;
	}

	bool PlayerWrapper::SetImmunemagical2(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Immunemagical(object, time, FILTER_IMMUNEMAGICAL2, filter::FILTER_MASK_UNIQUE | mask));
		}
		return true;
	}

	bool PlayerWrapper::SetPullover2(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL))
				immune |= 0x80;
			else
			{
				A3DVECTOR pos1, pos2;
				float body1, body2, dist;
				if (1 == object.QueryObject(skill->GetPerformerid(), pos1, body1))
				{
					body2 = object.GetBodySize();
					pos2 = object.GetPos();
					dist = sqrtf(pos2.squared_distance(pos1));
					if (dist < body1 + body2)
						value = 0;
					else if (dist < body1 + body2 + value)
						value = dist - body1 - body2;
					else
						value = dist - body1 - body2 - value;

					object.PullOver(skill->GetPerformerid(), skill->GetPerformerpos(), value, (int)amount);
				}
			}
		}
		return true;
	}

	bool PlayerWrapper::SetIncphysicaldamage(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Incphysicaldamage(object, time, ratio, mask));
		}

		return true;
	}

	bool PlayerWrapper::SetIncmagicaldamage(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Incmagicaldamage(object, time, ratio, mask));
		}

		return true;
	}

	bool PlayerWrapper::SetRemoveaggro(bool)
	{
		if (ThrowDice())
		{
			attacker_info_t attacker_info = skill->GetPerformerinfo();

			object.RemoveAggro(skill->GetPerformerid(), (GetValueInt() == 1 ? attacker_info.attacker : skill->GetPerformerid()), GetRatio());
		}

		return true;
	}

	bool PlayerWrapper::SetCooldownpunish(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Cooldownpunish(object, time, GetRatioInt(), GetValueInt(), mask));
		}

		return true;
	}

	bool PlayerWrapper::SetAnticlearbuf(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Anticlearbuf(object, time, GetValueInt(), mask));
		}

		return true;
	}

	bool PlayerWrapper::SetIncenchantrange(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Incenchantrange(object, time, value, mask));
		}

		return true;
	}

	bool PlayerWrapper::SetIncphysicalmagicaldefense(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Incphysicalmagicaldefense(object, time, ratio, value, mask));
		}

		return true;
	}

	bool PlayerWrapper::SetReducegold3(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Reducegold3(object, time, ratio, mask));
		}

		return true;
	}

	bool PlayerWrapper::SetReducewater3(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Reducewater3(object, time, ratio, mask));
		}

		return true;
	}

	bool PlayerWrapper::SetGenhpap(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));

			object.AddFilter(new filter_Genhpap(object, time, ratio, GetValueInt(), mask));
		}

		return true;
	}

	bool PlayerWrapper::SetDetaindart(bool)
	{
		if (ThrowDice())
		{
			bool is_lighting_effect = false;
			if (GetValueInt() != 0)
				is_lighting_effect = true;

			object.AddFilter(new filter_Detaindart(object, time, showicon, is_lighting_effect));
		}
		return true;
	}

	bool PlayerWrapper::SetExtraexpfactor(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_Extraexpfactor(object, time, GetValue(), GetRatio()));
		}

		return true;
	}

	bool PlayerWrapper::SetSoloIncAttackAndMagic(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_IncAttackAndMagic(object, GetAmountInt(), GetValueInt(), GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetSoloIncDefence(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_Incdefence(object, GetAmountInt(), GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetSoloEnhanceResist(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_Enhanceresist(object, GetAmountInt(), GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetSoloIncMaxHP(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_IncMaxhp(object, GetAmountInt(), GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetSoloHpGen(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_Hpgen(object, GetAmountInt(), GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetSoloDecHurt(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_Dechurt(object, GetRatioInt(), GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetSoloAddAttackRange(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_Addattackrange(object, GetAmountInt(), GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetThunder3(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEMETAL | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int thunder_damage = GetAmountInt();
		int physic_damage = GetValueInt();
		thunder_damage = object.CalcMagicDamage(0, thunder_damage, skill->GetPlayerlevel());
		physic_damage = object.CalcPhysicDamage(physic_damage, skill->GetPlayerlevel());
		int damage = thunder_damage + physic_damage;
		if (!object.IsPlayerClass())
		{
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}

		//if(damage>3)
		//{
		filter_Thunder3 *pfilter;
		int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		if (object.IsPlayerClass())
		{
			if (skill->GetPerformerid().IsPlayerClass())
			{
				damage = (int)(0.25 * damage);
				if (damage == 0)
					damage = 1;
			}
			pfilter = new filter_Thunder3(object, time, damage, mask);
		}
		else
		{
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			pfilter = new filter_Thunder3(object, time, damage, mask);
		}
		pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
		object.AddFilter(pfilter);
		//}
		return true;
	}

	bool PlayerWrapper::SetToxic3(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEWOOD | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int thunder_damage = GetAmountInt();
		int physic_damage = GetValueInt();
		thunder_damage = object.CalcMagicDamage(1, thunder_damage, skill->GetPlayerlevel());
		physic_damage = object.CalcPhysicDamage(physic_damage, skill->GetPlayerlevel());
		int damage = thunder_damage + physic_damage;
		if (!object.IsPlayerClass())
		{
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}

		//if(damage>3)
		//{
		filter_Toxic3 *pfilter;
		int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		if (object.IsPlayerClass())
		{
			if (skill->GetPerformerid().IsPlayerClass())
			{
				damage = (int)(0.25 * damage);
				if (damage == 0)
					damage = 1;
			}
			pfilter = new filter_Toxic3(object, time, damage, mask);
		}
		else
		{
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			pfilter = new filter_Toxic3(object, time, damage, mask);
		}
		pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
		object.AddFilter(pfilter);
		//}
		return true;
	}

	bool PlayerWrapper::SetFlood3(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEWATER | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int thunder_damage = GetAmountInt();
		int physic_damage = GetValueInt();
		thunder_damage = object.CalcMagicDamage(2, thunder_damage, skill->GetPlayerlevel());
		physic_damage = object.CalcPhysicDamage(physic_damage, skill->GetPlayerlevel());
		int damage = thunder_damage + physic_damage;
		if (!object.IsPlayerClass())
		{
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}

		//if(damage>3)
		//{
		filter_Flood3 *pfilter;
		int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		if (object.IsPlayerClass())
		{
			if (skill->GetPerformerid().IsPlayerClass())
			{
				damage = (int)(0.25 * damage);
				if (damage == 0)
					damage = 1;
			}
			pfilter = new filter_Flood3(object, time, damage, mask);
		}
		else
		{
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			pfilter = new filter_Flood3(object, time, damage, mask);
		}
		pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
		object.AddFilter(pfilter);
		//}
		return true;
	}

	bool PlayerWrapper::SetBurning3(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNEFIRE | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int thunder_damage = GetAmountInt();
		int physic_damage = GetValueInt();
		thunder_damage = object.CalcMagicDamage(3, thunder_damage, skill->GetPlayerlevel());
		physic_damage = object.CalcPhysicDamage(physic_damage, skill->GetPlayerlevel());
		int damage = thunder_damage + physic_damage;
		if (!object.IsPlayerClass())
		{
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}

		//if(damage>3)
		//{
		filter_Burning3 *pfilter;
		int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		if (object.IsPlayerClass())
		{
			if (skill->GetPerformerid().IsPlayerClass())
			{
				damage = (int)(0.25 * damage);
				if (damage == 0)
					damage = 1;
			}
			pfilter = new filter_Burning3(object, time, damage, mask);
		}
		else
		{
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			pfilter = new filter_Burning3(object, time, damage, mask);
		}
		pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
		object.AddFilter(pfilter);
		//}
		return true;
	}
	bool PlayerWrapper::SetFallen3(bool)
	{
		if (!ThrowDice())
			return false;
		if (object.GetImmuneMask() & (IMMUNESOIL | IMMUNEALL))
		{
			immune |= 0x80;
			return false;
		}
		int thunder_damage = GetAmountInt();
		int physic_damage = GetValueInt();
		thunder_damage = object.CalcMagicDamage(4, thunder_damage, skill->GetPlayerlevel());
		physic_damage = object.CalcPhysicDamage(physic_damage, skill->GetPlayerlevel());
		int damage = thunder_damage + physic_damage;
		if (!object.IsPlayerClass())
		{
			damage = object.CalcPenetrationEnhanceDamage(skill->GetPenetration(), damage);
		}

		//if(damage>3)
		//{
		filter_Fallen3 *pfilter;
		int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		if (object.IsPlayerClass())
		{
			if (skill->GetPerformerid().IsPlayerClass())
			{
				damage = (int)(0.25 * damage);
				if (damage == 0)
					damage = 1;
			}
			pfilter = new filter_Fallen3(object, time, damage, mask);
		}
		else
		{
			damage = (int)(object.CalcLevelDamagePunish(skill->GetPlayerlevel(), object.GetBasicProp().level) * damage);
			pfilter = new filter_Fallen3(object, time, damage, mask);
		}
		pfilter->SetUp(skill->GetPerformerid(), skill->GetPerformerinfo(), skill->GetAttackerMode(), invader);
		object.AddFilter(pfilter);
		//}
		return true;
	}

	bool PlayerWrapper::SetIncdefenselevel(float inc) // New passive Defense
	{
		if (enable)
		{
			object.EnhanceDefendDegree((int)(1 * inc));
			object.SendClientDefenseData();
		}
		else
		{
			object.ImpairDefendDegree((int)(1 * inc));
			object.SendClientDefenseData();
		}
		return true;
	}

	bool PlayerWrapper::SetIncCritReduce(float inc) // New passive Critical
	{
		if (enable)
		{
			object.EnhanceCritDamageReduce((int)(1 * inc));
		}
		else
		{
			object.ImpairCritDamageReduce((int)(1 * inc));
		}
		return true;
	}

	// Passiva Atr Arma

	bool PlayerWrapper::SetIncfirearm(float inc)
	{
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_FIREARM)
				return false;
		}
		else if (intarg != WEAPONCLASS_FIREARM)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				object.UpdateAttackData();
			}
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
		}
		return true;
	}

	// Passiva Palad Arma

	bool PlayerWrapper::SetIncswordshield(float inc)
	{
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_SWORDSHIELD)
				return false;
		}
		else if (intarg != WEAPONCLASS_SWORDSHIELD)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				object.UpdateAttackData();
			}
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
		}
		return true;
	}

	// Passiva Crítico

	bool PlayerWrapper::SetInccritshield(float inc)
	{		
		if (enable)
		{
			object.EnhanceCrit((int)(inc * 100));
			if (intarg == -1)
			{
				object.UpdateAttackData();
			}
		}
		else
		{
			object.ImpairCrit((int)(inc * 100));
		}
		return true;
	}

	// Passiva Atiradora Range

	bool PlayerWrapper::SetIncrangeatr(float r)
	{
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_FIREARM)
				return false;
		}
		else if (intarg != WEAPONCLASS_FIREARM)
			return false;
		if (enable)
		{
			object.EnhanceAttackRange(r);
			if (intarg == -1)
			{
				object.UpdateAttackData();
				object.SendClientAttackData();
			}
		}
		else
		{
			object.ImpairAttackRange(r);
		}
		return true;
	}

	bool PlayerWrapper::SetIncacertatr(float r) // Evil
	{
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_FIREARM)
				return false;
		}
		else if (intarg != WEAPONCLASS_FIREARM)
			return false;
		if (enable)
		{
			object.EnhanceScaleAttack(r);
			if (intarg == -1)
			{
				object.UpdateAttackData();
				object.SendClientAttackData();
			}
		}
		else
		{
			object.ImpairAttackRange(r);
		}
		return true;
	}

	// Cannon

	bool PlayerWrapper::SetCannonform(bool b)
	{
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.RemoveFilter(FILTER_CANNONFORM);
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;

		object.AddFilter(new filter_Cannonform(object, GetRatioInt(), (int)(amount * 100), (float)(value), time));
		return true;
	}

	
	bool PlayerWrapper::SetShattereddream(bool b) // Novas Alteração
	{	
		if (ThrowDice())
		{
			if (!object.IsInSanctuary(object.GetPos()))
				object.AddFilter(new filter_Shattereddream2(object, time, (int)amount));
		}
		return true;
	}


	bool PlayerWrapper::SetShattereddreammob(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL))
				immune |= 0x80;
			else
				object.PullOver(skill->GetPerformerid(), skill->GetPerformerpos(), value, (int)amount);
		}
		return true;
	}


	bool PlayerWrapper::SetRepelAtr(bool b)
	{
		if (!object.IsPlayerClass() && !object.IsInTeam()) {

			return false;
		}
			
		else  {

			if (ThrowDice())
			{
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL))
				immune |= 0x80;
			else
				object.KnockBack(skill->GetPerformerid(), skill->GetPerformerpos(), value, (int)amount, time);
			}
			
			return true;

		}
		
	}

	// Buff Speed + Reduce

	bool PlayerWrapper::SetReduceSpeeddebuff(bool)
	{

		if (ThrowDice())
	
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL))
				immune |= 0x80;
			else
			object.AddFilter(new filter_ReduceSpeeddebuff(object, (int)(ratio * 100), amount, time));


		return true;
	}

	// Novos escudos 

	bool PlayerWrapper::SetShieldNew1(bool)
	{
		if (ThrowDice())
		{
			//object.ClearSpecFilter(filter::FILTER_MASK_DEBUFF);
			object.AddFilter(new filter_ShieldNew1(object, value, time));
		}
		return true;
	}

	// Escudo dano em area 

	bool PlayerWrapper::SetShieldNew2(bool)
	{
		if (ThrowDice())
		{
			filter_ShieldNew2 *pfilter = new filter_ShieldNew2(object, time, ratio, GetValueInt(), GetAmountInt());
			pfilter->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
			object.AddFilter(pfilter);
		}
		return true;
	}
	
	// Speed
	
	bool PlayerWrapper::SetNewSpeedBuff(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_NewBuffSpeed(object, (int)(ratio * 100), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetIraAtiradora(bool)
	{
		if (ThrowDice() && ratio > 0)
		{
			if (object.GetImmuneMask() & (IMMUNEWEAK | IMMUNEALL))
				immune |= 0x80;
			else
			{
				int mask_buff = (value > 0.5f ? filter::FILTER_MASK_DEBUFF : 0);
				object.AddFilter(new filter_IraAtiradora(object, ratio, time, showicon, mask_buff));
			}
		}
		return true;
	}

	bool PlayerWrapper::SetGeloAtiradora(bool b) // Gelo
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_GeloAtiradora(object, time, showicon));
		}
		return true;
	}

	bool PlayerWrapper::SetFeAtiradora(bool) // Fe
	{
		object.AddFilter(new filter_FeAtiradora(object, time));
		return true;
	}

	bool PlayerWrapper::SetNewRemove(bool)
	{
		if(amount < 1) {
			return false;
		}	else {
			
			object.Die();
		}
		
		return true;

	}
	//UltWR
	bool PlayerWrapper::SetAccumulateAttack(bool b) 
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_AccumulateAttack(object, time, ratio, value, mask ));
		}
		return true;
	}
	//UltMG
	bool PlayerWrapper::SetAccumulateAttack2(bool b)
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_AccumulateAttack2(object, time, ratio, value, mask ));
		}
		return true;
	}
	//CuraWF
	bool PlayerWrapper::SetDecRegionDMG(bool b) // UltMG
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_DecRegionDMG(object, time, ratio, mask ));
		}
		return true;
	}
	//UltEA
	bool PlayerWrapper::SetIncAntiDefenseDegree(bool) 
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_IncAntiDefenseDegree(object, GetValueInt(), time, mask ));
		}
		return true;
	}
	//UltEP
	bool PlayerWrapper::SetIncPlusMaxHP(bool) 
	{
  		if (ThrowDice())
		{
		int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		object.AddFilter(new filter_IncPlusMaxHP(object, time, ratio, value, mask));
		}
		return true;
	}
	//UltMC
	bool PlayerWrapper::SetInvisible2(bool)
	{
	if (!object.GetNoInvisible() && ThrowDice())
	{ 
		object.SetInvisibleFilter(true,time,(int)amount,(int)value,(int)(ratio*100)); 
	}
		return true; 
	}
	//UltMC
	bool PlayerWrapper::SetAuracurse4ASN(bool) 
	{
		filter_Auracurse4asn *pfilter = new filter_Auracurse4asn(object, time, ratio, GetValueInt(), GetAmountInt(), GetProbabilityInt());
		pfilter ->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
		object.AddFilter(pfilter);
		return true;
	}
	//UltESP
	bool PlayerWrapper::SetIncmagic4(bool) 
	{
  		if (ThrowDice())
		{
		int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		object.AddFilter(new filter_Incmagic4(object, time, ratio, mask));
		}
		return true;
	}
	//UltESP
	bool PlayerWrapper::SetDecsoul(bool) 
	{
  		if (ThrowDice())
		{
		int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
		object.AddFilter(new filter_Decsoul(object, time, ratio, mask));
		}
		return true;
	}
	//UltSK
	bool PlayerWrapper::SetGiantform(bool) 
	{
		object.AddFilter(new filter_Giantform(object, time, ratio, int(value * 100), int(amount * 100), GetProbabilityInt()));
		return true;
	}
	//UltMS
	bool PlayerWrapper::SetTransdmg2pet(bool) 
	{
		if (ThrowDice())
		{
			char level;
			XID petid = object.GetPetID();
			A3DVECTOR pos;
			int hp;
			int mp2;
			if (petid.IsValid() && object.QueryObject(petid, pos, hp, mp2) == 1)
			{
				int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
				object.AddFilter(new filter_Transdmg2pet(object, time, ratio, mask, petid));
				if(GetValueInt())
				{
					enchant_msg msg;
					memset(&msg, 0, sizeof(msg));
					msg.skill = GetValueInt();
					if(skill)
					{
						level = skill->GetLevel();
					}
					else
					{
						level = 1;
					}
					msg.skill_level = level;
					msg.helpful = 2;
					msg.attack_range = 10;
					SetTalentData(msg.skill_modify);
					object.Enchant(petid, msg);
				}
			}
		}
		return true;
	}
	bool PlayerWrapper::SetDecRegionDMG2(bool b)
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_DecRegionDMG2(object, time, ratio, mask ));
		}
		return true;
	}
	bool PlayerWrapper::SetLoaddmg4master(bool b)
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Loaddmg4master(object, time, ratio, GetProbabilityInt(), GetValueInt(), mask ));
		}
		return true;
	}
	//ULTRT
	bool PlayerWrapper::SetDecfardmg(bool b)
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			
			object.AddFilter(new filter_Decfardmg(object, time, ratio, value, mask));
		}
		return true;
	}
		bool PlayerWrapper::SetSkillcooldown2(bool)
	{
		if (ThrowDice())
		{
			if (value > 0)

			for (int i = 2545; i < 2925; i++)  // i= 0
			{ 
				object.SetCoolDown(i + COOLINGID_BEGIN, GetAmountInt());
			}			
			
		}
		return true;
	}
	
	//ULTTM
	bool PlayerWrapper::SetDecphysicalmagicaldefense(bool)
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Decphysicalmagicaldefense(object, time, (int)(ratio * 100), (int)(value * 100), mask ));
		}
		return true;
	}
	//G17
	bool PlayerWrapper::SetMagicFrenetic(bool b) // G17
	{
		if(enable)
		{
		object.AddFilter(new filter_MagicFrenetic(object, ratio, GetProbabilityInt()));
		}
		else
		{
		object.RemoveFilter(FILTER_MAGICFRENETIC);
		}
		return true;
	}

	bool PlayerWrapper::SetDecheal(bool	b)
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Decheal(object, time, ratio, mask ));
		}
		return false;
	}
	bool PlayerWrapper::SetIncsmitedamage(bool)
	{
  		if (ThrowDice())
		{
			object.AddFilter(new filter_Incsmitedamage(object, time, (int)(ratio * 100), (int)(value * 100)));
		}
		return true;
	}
	bool PlayerWrapper::SetDecphysicalmagicaldefense2(bool)
	{
  		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Decphysicalmagicaldefense2(object, time, (int)(ratio * 100), (int)(value * 100), mask ));
		}
		return true;
	}
	bool PlayerWrapper::SetFastpray3(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Fastpray3(object, time, (int)(ratio * 100), mask));
		}
		return true;
	}
	bool PlayerWrapper::SetIncdebuffdodge2(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Incdebuffdodge2(object, time, (int)(ratio * 100), mask));
		}
		return true;
	}
	bool PlayerWrapper::SetIncdamagedodge2(bool)
	{
		if (ThrowDice())
		{
			int mask = (amount > 1.0f ? 0 : (amount > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
			object.AddFilter(new filter_Incdamagedodge2(object, time, (int)(ratio * 100), mask));
		}
		return true;
	}
	bool PlayerWrapper::SetDebithurt(bool)
	{
		object.AddFilter(new filter_Debithurt(object, time, GetValueInt()));
		return true;
	}	

		
	// Nova Torre 

	bool PlayerWrapper::SetSoloAddAttackLevel(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_IncAttackLevel(object, GetAmountInt(), GetTime()));
		}
		return true;
	}

	bool PlayerWrapper::SetSoloAddDefendLevel(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_solo_IncDefenseLevel(object, GetAmountInt(), GetTime()));
		}
		return true;
	}


	// Ultimate do Paladino

	bool PlayerWrapper::SetUltimatePaladin(bool)
	{

		if (ThrowDice())
		{
			object.AddFilter(new filter_UltimatePaladin(object, (int)(ratio * 100), amount, time));
		}

		return true;
	}

	// Ultimate Atiradora 

	bool PlayerWrapper::SetAttackplusAtr(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_AttackplusAtr(object, (int)value, time));
		}
		return true;
	}


	bool PlayerWrapper::SetAddPraga(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEREPEL | IMMUNEALL)) {
				immune |= 0x80;
			} else {

				const XID &cur_target = object.GetCurTargetID();

				object.AddFilter(new filter_AddPraga(object, time, cur_target, ratio, value));
			}
			
			
		}
		return true;
	}

	bool PlayerWrapper::SetSummonplantpet2(bool)
	{
		//skill->GetPerformerid()
		for (int i = 0; i < GetAmountInt(); i++)
			object.SummonPlantPet(GetValueInt(), GetRatioInt(), time, skill->GetPerformerid(), skill->GetForceattack()); //value��pet_egg_id
		return true;
	}

	bool PlayerWrapper::SetskillplusAtr(bool)
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_skillplusAtr(object, (int)value, time));
		}
		return true;
	}

	// Novo Atributo 

	bool PlayerWrapper::SetHighestLevel(bool b)
	{
		if (enable)
			object.AddFilter(new filter_HighestLevel(object, probability, (int)(ratio * 100)));
		else
			object.RemoveFilter(FILTER_HIGHESTLEVEL);
		return true;
	}

	// Patente 

	bool PlayerWrapper::SetIncdefencePatente(float inc)
	{
		if (enable)
		{
			object.EnhanceDefense((int)(inc * 100));
			for (int n = 0; n < MAGIC_CLASS; ++n)
				object.EnhanceResistance(n, (int)(inc * 100));
			
		}
		else
		{
			object.ImpairDefense((int)(inc * 100));
			for (int n = 0; n < MAGIC_CLASS; ++n)
				object.ImpairResistance(n, (int)(inc * 100));
			
		}
		object.UpdateMagicData();
		object.UpdateDefenseData();

		return true;
	}
	
	
	bool PlayerWrapper::UseSheild(float cost)
	{
		return object.UseSheild(cost);
	}

	bool PlayerWrapper::SetNewSheildMax(float inc)
	{
		if (enable)
		{
			object.EnhanceShieldEnergyMax(inc);
		}
		else
		{
			object.ImpairShieldEnergyMax(inc);
		}
		return true;
	}

	bool PlayerWrapper::SetNewSheildGen(float inc)
	{
		if (enable)
		{
			object.EnhanceShieldGen(inc);
		}
		else
		{
			object.ImpairShieldGen(inc);
		}
		return true;
	}
	
	
	// Versos Sombrios Novos

	bool PlayerWrapper::SetVersoSombrio01(bool) // Mesmo Filtro 
	{
		if (ThrowDice())
			object.AddFilter(new filter_SetVersoSombrio01(object, (int)(ratio * 100), (int)(amount * 100.f + 0.00001f), time));
		return true;
	}

	bool PlayerWrapper::SetVersoSombrio02(bool) // Mesmo Filtro 
	{
		if (ThrowDice())
			object.AddFilter(new filter_SetVersoSombrio02(object, (int)(ratio * 100), (int)(amount * 100.f + 0.00001f), time));
		return true;
	}

	bool PlayerWrapper::SetVersoSombrio03(bool) // Mesmo Filtro 
	{
		if (ThrowDice())
			object.AddFilter(new filter_SetVersoSombrio03(object, (int)(ratio * 100), (int)(amount * 100.f + 0.00001f), time));
		return true;
	}

	bool PlayerWrapper::SetVersoSombrio04(bool) // Mesmo Filtro 
	{
		if (ThrowDice())
			object.AddFilter(new filter_SetVersoSombrio04(object, (int)(ratio * 100), (int)(amount * 100.f + 0.00001f), time));
		return true;
	}

	bool PlayerWrapper::SetVersoSombrio05(bool) // Mesmo Filtro 
	{
		if (ThrowDice())
			object.AddFilter(new filter_SetVersoSombrio05(object, (int)(ratio * 100), (int)(amount * 100.f + 0.00001f), time));
		return true;
	}

	bool PlayerWrapper::SetVersoSombrio06(bool) // Mesmo Filtro 
	{
		if (ThrowDice())
			object.AddFilter(new filter_SetVersoSombrio06(object, (int)(ratio * 100), (int)(amount * 100.f + 0.00001f), time));
		return true;
	}
	
	bool PlayerWrapper::SetHealnurse(bool)
	{
		int mask;
		if (ThrowDice())
		{
			if ( amount <= 1.0 )
			{
				if ( amount <= 0.5 )
				{
					mask = 4096;
				}
				else
				{
					mask = 0x2000;
				}
			}
			else
			{
				mask = 0;
			}
			object.AddFilter( new filter_Healnurse(object, time, ratio, value, mask) );
		}
		return true;
	}
	
	bool PlayerWrapper::SetRetort3(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_Retort3(object, ratio, value, time));
		return true;
	}

	bool PlayerWrapper::SetElfLock(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Elflock(object, time));
		}
		return true;
	}

	// skill coldown limit
	
	bool PlayerWrapper::CooldownManager(char type, int idx, unsigned int time)
	{
		return object.CooldownManager(type, idx, time);
	}

	bool PlayerWrapper::CooldownManagerMassive(char type, unsigned int * table)
	{
		return object.CooldownManagerMassive(type, table);
	}
	
	void PlayerWrapper::SetMultiCoolDown()
	{
		if (!skill)
			return;
		
		if ( skill->GetCoolDownLimit() > 0 )
		{
			object.GetUseSkillCD( skill->GetId() + COOLINGID_BEGIN, skill->GetCoolDownLimit(), skill->GetCoolingtime() * 1000 + skillwrapper->GetCDAdjust() );
		}
		else
		{
			object.SetCoolDown( skill->GetId() + COOLINGID_BEGIN, skill->GetCoolingtime() * 1000 + skillwrapper->GetCDAdjust() );
		}
	}
	
	// asn combo skill
	int PlayerWrapper::GetChargeMerc()
	{
		return object.GetCountChargeMerc();
	}
	
	void PlayerWrapper::GainChargeMerc( int val )
	{
		//printf("PlayerWrapper::GainChargeMerc: val = %d \n", val);
		object.EnhanceChargeMerc( val );
	}
	
	void PlayerWrapper::SpendChargeMerc( int val )
	{
		object.ImpairChargeMerc( val );
	}
	// asn combo skill end
	
	bool PlayerWrapper::SetSleep2(bool b)
	{
		if (ThrowDice())
		{
			if (object.IsPalsyImmune())
				immune |= 0x80;
			else
			{
				int mask = (value > 1.0f ? 0 : (value > 0.5f ? filter::FILTER_MASK_BUFF : filter::FILTER_MASK_DEBUFF));
				object.AddFilter(new filter_Sleep2(object, time, mask));
			}
		}
		return true;
	}
	
	int PlayerWrapper::GetTargetClass()
	{
		return object.GetTargetClass( *target );
	}
	
	int PlayerWrapper::GetTargetHp()
	{
		return object.GetTargetHp( *target );
	}
	
	int PlayerWrapper::GetTargetMp()
	{
		return object.GetTargetMp( *target );
	}
	int PlayerWrapper::GetTargetMaxhp()
	{
		return object.GetTargetMaxhp( *target );
	}
	int PlayerWrapper::GetTargetLevel()
	{
		return object.GetTargetLevel( *target );
	}
	
	
	bool PlayerWrapper::SetOtherGold(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Othergold(object, time, ratio, value, amount));
		}
		return true;
	}
	
	bool PlayerWrapper::SetOtherWood(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Otherwood(object, time, ratio, value, amount));
		}
		return true;
	}
	
	bool PlayerWrapper::SetOtherWater(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Otherwater(object, time, ratio, value, amount));
		}
		return true;
	}
	
	bool PlayerWrapper::SetOtherFire(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Otherfire(object, time, ratio, value, amount));
		}
		return true;
	}
	
	bool PlayerWrapper::SetOtherSoil(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Othersoil(object, time, ratio, value, amount));
		}
		return true;
	}
	
	bool PlayerWrapper::SetOtherRange(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Otherrange(object, time, ratio, value, amount));
		}
		return true;
	}
	
	bool PlayerWrapper::SetOtherDamage(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Otherdamage(object, time, ratio, value, amount));
		}
		return true;
	}
	
	bool PlayerWrapper::SetOtherCooldown(bool)
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Othercooldown(object, time, ratio, value));
		}
		return true;
	}
	
	bool PlayerWrapper::SetOtherPraySpeed(bool)	
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNECURSED | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Otherprayspeed(object, time, ratio, value, amount));
		}
		return true;
	}
	
	



//++++++++++++172++++++++++++++//

	// Monkey New Skills

	bool PlayerWrapper::SetMonkeyform(bool b)
	{
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.RemoveFilter(FILTER_MONKEYFORM);
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;

		object.AddFilter(new filter_Monkeyform(object, GetRatioInt(), (int)(100 * probability), (int)(100 * amount), (int)(100 * value)));		
		return true;
	}

	bool PlayerWrapper::SetMonkeyformUltimate(bool b)
	{
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.RemoveFilter(FILTER_MONKEYFORM);
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;

		object.AddFilter(new filter_MonkeyformUltimate(object, time, GetRatioInt(), (int)(100 * probability), (int)(100 * amount), (int)(100 * value)));		
		return true;
	}

	bool PlayerWrapper::SetMonkeyinvisible(bool)
	{
		if (!object.GetNoInvisible() && ThrowDice())
		{ 
			object.SetInvisibleFilter(true, time, value, 130, 100);
		} else {
			object.SetInvisibleFilter(false, 0, 0, 0, 0);
		}

		return true;

	}
	
	bool PlayerWrapper::SetAuracurseMonkey(bool)
	{
		if (ThrowDice())
		{
			filter_AuracurseMonkey *pfilter = new filter_AuracurseMonkey(object, time, ratio, GetValueInt(), GetAmountInt());
			pfilter->SetTalent(skill->GetT0(), skill->GetT1(), skill->GetT2());
			object.AddFilter(pfilter);
		}
		return true;
	}

	// Marcas 

	bool PlayerWrapper::SetMarcadoVento(bool b) // Vento
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Marcadovento(object, time, showicon));
		}
		return true;
	}

	bool PlayerWrapper::SetMarcadaFloresta(bool b) // Floresta
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Marcadafloresta(object, time, showicon));
		}
		return true;
	}

	bool PlayerWrapper::SetMarcadofogo(bool b) // Fogo
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Marcadofogo(object, time, showicon));
		}
		return true;
	}

	bool PlayerWrapper::SetMarcadamontanha(bool b) // Montanha
	{
		if (ThrowDice())
		{
			if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
				immune |= 0x80;
			else
				object.AddFilter(new filter_Marcadamontanha(object, time, showicon));
		}
		return true;
	}

	bool PlayerWrapper::SetMarcaYin(bool b) // Yin
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_MarcaYin(object, time, showicon));
		}
		return true;
	}

	bool PlayerWrapper::SetMarcaYang(bool b) // Yin
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_MarcaYang(object, time, showicon));
		}
		return true;
	}

	// Passivas 

	bool PlayerWrapper::SetIncsbastao(float inc) // Bastão
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_CUDGEL)
				return false;
		}
		else if (intarg != WEAPONCLASS_CUDGEL)
			return false;
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			if (intarg == -1)
			{
				object.UpdateAttackData();
			}
			return true;
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
			return true;
		}
#endif
		return false;
	}

	bool PlayerWrapper::SetIncsbastaoCritico(float inc) // Bastão Critico
	{
#ifndef _SKILL_TEST
		if (intarg == -1)
		{
			if (GetCurWeapon() != WEAPONCLASS_CUDGEL)
				return false;
		}
		else if (intarg != WEAPONCLASS_CUDGEL)
			return false;
		if (enable)
		{
			object.EnhanceCrit((int)(inc * 100));
			return true;
		}
		else
		{
			object.ImpairCrit((int)(inc * 100));
			return true;
		}
#endif
		return false;
	}

	bool PlayerWrapper::SetIncsformmonkey(float inc) // Forma de Macaco
	{
#ifndef _SKILL_TEST
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.ImpairScaleDamage((int)(inc * 100));
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;
		
		if (enable)
		{
			object.EnhanceScaleDamage((int)(inc * 100));
			return true;
		}
		else
		{
			object.ImpairScaleDamage((int)(inc * 100));
			return false;
		}
		
		return true;
#endif
		return false;
	}

	bool PlayerWrapper::SetIncsformmonkeyCritico(float inc) // Forma de Macaco
	{
#ifndef _SKILL_TEST
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{
			object.ImpairCrit((int)(inc * 100));
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;
		
		if (enable)
		{
			object.EnhanceCrit((int)(inc * 100));
			return true;
		}
		else
		{
			object.ImpairCrit((int)(inc * 100));
			return false;
		}
		
		return true;
#endif
		return false;
	}

	bool PlayerWrapper::SetIncsformmonkeyDefense(float inc) // Redução de Defesa na Forma de Macaco
	{
#ifndef _SKILL_TEST
		int form = object.GetForm();
		if (form == FORM_CLASS)
		{			

			object.RemoveFilter(FILTER_MONKEYDEFENSE);
			return false;
		}
		else if (form == FORM_BEASTIE)
			return false;
		
		if (enable)
		{
			object.AddFilter(new filter_IncsformmonkeyDefense(object, inc));
			return true;
		}
		else
		{
			object.RemoveFilter(FILTER_MONKEYDEFENSE);
			return false;
		}
		
		return true;
#endif
		return false;
	}

	// Todas as Habilidades Transformado (fica imune a danos negativos)

	bool PlayerWrapper::SetFreemoveMonkey(bool) // Fe
	{
		int form = object.GetForm();
		int newtime = 2;

		if (form == FORM_CLASS)
		{
			object.AddFilter(new filter_FreemoveMonkey(object, newtime));
			return true;
		}
		else if (form == FORM_BEASTIE)
			return false;

		return true;
	}

	// Buff do Andarilho 

	bool PlayerWrapper::SetMovimentodasMaos(bool)
	{
		if (ThrowDice())
			object.AddFilter(new filter_MovimentodasMaos(object, GetAmountInt(), time));
		return true;
	}	

	// Buff de Salto

	bool PlayerWrapper::SetShattereddreamMonkey(bool b)
	{	
		if (ThrowDice())
		{
			const XID &cur_target = object.GetCurTargetID();
			object.AddFilter(new filter_ShattereddreamMonkey(object, time, (int)amount, (int)value, object.GetWorldTag(), cur_target, object.GetPos()));
		}
		return true;
	}

	// Fé do Andarilho

	bool PlayerWrapper::SetFeMonkey(bool) // Fe
	{
		object.AddFilter(new filter_FeMonkey(object, time));
		return true;
	}

	// Combo das Marcas 

	bool PlayerWrapper::SetComboMonkey(bool b) // Combo Geral
	{

		if (object.IsFilterExist(FILTER_MARCADOVENTO) && 
				object.IsFilterExist(FILTER_MARCADOFOGO) && 
					object.IsFilterExist(FILTER_MARCADAMONTANHA) && 
							object.IsFilterExist(FILTER_MARCADAFLORESTA))
		{
			if (ThrowDice())
			{
				if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
					immune |= 0x80;
				else

					object.RemoveFilter(FILTER_MARCADOVENTO);
						object.RemoveFilter(FILTER_MARCADOFOGO);
							object.RemoveFilter(FILTER_MARCADAMONTANHA);
								object.RemoveFilter(FILTER_MARCADAFLORESTA);

				object.AddFilter(new filter_ComboMonkey(object, time, object.GetWorldTag(), object.GetPos(), showicon));
			}

		} else {

			return false;
		}

		
		return true;
	}

	// Combo das Yin e Yang 

	bool PlayerWrapper::SetComboYinYang(bool b) // Combo Geral
	{		
			if (ThrowDice())
			{
				if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
					immune |= 0x80;
				else

				object.AddFilter(new filter_ComboYinYang(object, time, showicon));
			}
	
		return true;
	}

	// Combo das Yin e Yang  2

	bool PlayerWrapper::SetComboYinYang2(bool b) // Combo Geral 2
	{		
			if (ThrowDice())
			{
				if (object.GetImmuneMask() & (IMMUNEDIZZY | IMMUNEALL))
					immune |= 0x80;
				else

				object.AddFilter(new filter_ComboYinYang2(object, time, showicon));
			}
	
		return true;
	}

	// Remove os filtros Yin e Yang 

	bool PlayerWrapper::SetRemoveFilterMonkey(bool) // Combo Geral
	{

		if (object.IsFilterExist(FILTER_MARCAYIN) && 
				object.IsFilterExist(FILTER_MARCAYANG))
		{
			object.RemoveFilter(FILTER_MARCAYIN);
				object.RemoveFilter(FILTER_MARCAYANG);
		}

		 else {

			return false;
		}		
		return true;
	}

	// Reduz dano em até 8 metros

	bool PlayerWrapper::SetReduzDanoaDistancia(bool b) // Reduz o dano
	{
		if (ThrowDice())
		{
			object.AddFilter(new filter_ReduzDanoaDistancia(object, time, (int)(100 * ratio + 0.00001f), object.GetPos()));
		}
		return true;
	}

	bool PlayerWrapper::SetInvincibleMonkey(int b) // Novo
	{
		if (ThrowDice())
		{
			object.SetInvincibleFilter(true, b, true);
		}
		return true;
	}

	bool PlayerWrapper::SetInvincibleMonkeyNew(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_InvincibleMonkeyNew(object, (int)(value), time));
#endif
		
		return true;
	}

	bool PlayerWrapper::SetRemoveFilterMonkey2(bool)
	{

		if (object.IsFilterExist(FILTER_INVICIBLEMONKEYNEW))
		{
			object.RemoveFilter(FILTER_INVICIBLEMONKEYNEW);
		}
		else {
			return false;
		}		
		return true;
	}

	// Reduz Critico recebido 

	bool PlayerWrapper::SetIncCritReduce2(bool b) // Combo Geral
	{
		if (ThrowDice())
		{
		object.AddFilter(new filter_IncCritReduce2(object, time, amount));
		}
		return true;
	}



	// Novas Habilidades 1.6.6 > 

	bool PlayerWrapper::SetIncAtkFToDefense(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_IncAtkFToDefense(object, (int)(ratio * 100), time));
#endif
		return true;
	}


	bool PlayerWrapper::SetIncNewShieldMage(bool) // Invencível
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_IncNewShieldMage(object, (int)(ratio * 100), time));
#endif
		return true;
	}

	bool PlayerWrapper::SetIncNewShieldMage2(bool) // Escudo com mecânica
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_IncNewShieldMage2(object, GetRatioInt(), time));
#endif
		return true;
	}



	bool PlayerWrapper::SetNewShieldMage(bool) // 4 Elementos de resistência
	{
		if (ThrowDice())
			object.AddFilter(new filter_SetNewShieldMage(object, GetValueInt(), (int)(ratio * 100), (int)(100 * amount), time));
		return true;
	}

	// Buff da Atiradora

	bool PlayerWrapper::SetBuffAtiradora(bool b)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_SetBuffAtiradora(object, ratio, time));
#endif
		
		return true;
	}	

	// Buff do Paladino

	bool PlayerWrapper::SetBuffPaladin(bool)
	{
#ifndef _SKILL_TEST
		if (ThrowDice())
			object.AddFilter(new filter_SetBuffPaladin(object, (int)(value), time));
#endif
		
		return true;
	}

	// Novas Passivas 1.6.6 > 

	bool PlayerWrapper::SetAddskilldamage2(float inc)
	{
		if (enable)
			object.EnhanceSkillDamage2((int)(inc * 100));
		else
			object.ImpairSkillDamage2((int)(inc * 100));

		return true;
	}

	bool PlayerWrapper::SetAttackMPasive(int inc)
	{
		if (enable)
			object.EnhanceMagicDamage((int) inc);
		else
			object.ImpairMagicDamage((int) inc);

		return true;
	}

	bool PlayerWrapper::SetAttackFPasive(int inc)
	{
		if (enable)
			object.EnhanceDamage((int) inc);
		else
			object.ImpairDamage((int) inc);

		return true;
	}

	bool PlayerWrapper::SetIncPercDefenseMagicFisic(float inc)
	{
		if (enable)
		{
			object.EnhanceDefense((int)(inc * 100));
			for (int n = 0; n < MAGIC_CLASS; ++n)
				object.EnhanceResistance(n, (int)(inc * 100));
			
		}
		else
		{
			object.ImpairDefense((int)(inc * 100));
			for (int n = 0; n < MAGIC_CLASS; ++n)
				object.ImpairResistance(n, (int)(inc * 100));
			
		}
		object.UpdateMagicData();
		object.UpdateDefenseData();

		return true;
	}


	bool PlayerWrapper::SetReduceDefensePassive(float inc) // Redução de Defesa passiva nova
	{
#ifndef _SKILL_TEST

			
		if (enable)
		{
			if(object.IsCombatState())
			object.AddFilter(new filter_ReduceDefensePassive(object, inc));
			
			return true;
		}
		else
		{
			object.RemoveFilter(FILTER_REDUCEDEFENSEPASSIVE);
			return false;
		}
		
		return true;
#endif
		return false;
	}

	// New Atiradora

	bool PlayerWrapper::SetArmadilhaPvP(bool)
	{
		const XID &targetid = object.GetCurTargetID();

		if(!object.IsCombatState()) {
			object.EnterCombatState();
		}

			object.AddAggro(targetid, 999999);
			object.AddFilter(new filter_ArmadilhaPvP(object, time = 999999, 30));
		return true;
	}

	bool PlayerWrapper::SetIncfeather2(float inc)
	{
		if (enable)
		{
			object.EnhanceFlySpeed(inc);
			object.UpdateSpeedData();
			return true;
		}
		else
		{
			object.ImpairFlySpeed(inc);
			return true;
		}
		
		return false;
	}
	
	bool PlayerWrapper::SetClearbuffRandom(int inc)
	{
		if (ThrowDice())
		{
			for (int i = 0; i < inc; i++)
			{
				object.ClearSpecFilterRandom(filter::FILTER_MASK_BUFF);
			}
		}
		return true;
	}

	
	// Arena Guan Yu 

	bool PlayerWrapper::SetRedTeamIcon(bool b) // Bandeira Vermelha
	{
		object.AddFilter(new filter_Icon(object, time, 0, VSTATE_ARENARED, FILTER_ARENAGUANYU, filter::FILTER_MASK_UNIQUE));
		return true;
	}
	
	bool PlayerWrapper::SetBlueTeamIcon(bool b) // Bandeira Vermelha
	{
		object.AddFilter(new filter_Icon(object, time, 0, VSTATE_ARENABLUE, FILTER_ARENAGUANYU, filter::FILTER_MASK_UNIQUE));
		return true;
	}
	
};

