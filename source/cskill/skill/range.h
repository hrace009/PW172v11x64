#ifndef __SKILL_RANGE_H
#define __SKILL_RANGE_H

#include <string>

namespace GNET
{

class Skill;

#ifdef INTEPRETED_EXPR 
class Range : public Marshal
#else
class Range
#endif
{
public:
	enum Type{
		POINT = 0,
		LINE = 1,
		SELFBALL = 2,
		TARGETBALL = 3,
		SECTOR = 4,
		SELF = 5,
		
		RECTANGLE = 6, // Прямоугольная атака
		SELFSPHERE = 7, // Круг вокруг себя
		TARGETSPHERE = 8, // Круг вокруг цели
		
		UNC_9 = 9, // skill 3334
		UNC_10 = 10, //Сметание дракона / Хвост дракона Элмсли
		UNC_11 = 11, //Удар молнии молитвы о Священной молнии
		
	};
	char	type;	// 0点 1线 2自身球 3目标球 4圆锥形 5自身
public:
	Range(char t=1) : type(t) { }

#ifdef INTEPRETED_EXPR 
	std::string		radius_exp;				// 圆柱半径,或者球半径
	std::string		attackdistance_exp;		// 杀伤距离
	std::string		angle_exp;				// 半张角
	std::string		praydistance_exp;		// 吟唱距离
	std::string		effectdistance_exp;		// 最大有效距离
public:
	Range(const Range &rhs) : type(rhs.type),
			radius_exp(rhs.radius_exp), attackdistance_exp(rhs.attackdistance_exp),
			angle_exp(rhs.angle_exp), praydistance_exp(rhs.praydistance_exp),
			effectdistance_exp(rhs.effectdistance_exp) { }
	Range& operator = (const Range& rhs)
	{
		type = rhs.type;
		radius_exp = rhs.radius_exp;
		attackdistance_exp = rhs.attackdistance_exp;
		angle_exp = rhs.angle_exp;
		praydistance_exp = rhs.praydistance_exp;
		effectdistance_exp = rhs.effectdistance_exp;
		return *this;
	}
	OctetsStream& marshal(OctetsStream &os)	const
	{
		return os << type << radius_exp << attackdistance_exp << angle_exp
				<< praydistance_exp << effectdistance_exp;
	}
	const OctetsStream& unmarshal(const OctetsStream &os)
	{
		return os >> type >> radius_exp >> attackdistance_exp >> angle_exp
				>> praydistance_exp >> effectdistance_exp;
	}
#else
public:
	Range(const Range &rhs) : type(rhs.type){} 
#endif

	bool IsPoint() const { return 0 == type; }
	bool IsLine() const { return 1 == type || 6 == type ; }
	bool IsSelfBall() const { return 2 == type || 7 == type ; }
	bool IsTargetBall() const { return 3 == type || 8 == type; }
	bool IsSector() const { return 4 == type; }
	bool IsSelf() const { return 5 == type; }
	bool NoTarget() const { return 5 == type || 2 == type; }
	
};

}

#endif

