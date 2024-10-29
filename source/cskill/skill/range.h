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
		
		RECTANGLE = 6, // �����ާ��ԧ�ݧ�ߧѧ� �ѧ�ѧܧ�
		SELFSPHERE = 7, // ������ �ӧ�ܧ��� ��֧ҧ�
		TARGETSPHERE = 8, // ������ �ӧ�ܧ��� ��֧ݧ�
		
		UNC_9 = 9, // skill 3334
		UNC_10 = 10, //���ާ֧�ѧߧڧ� �է�ѧܧ�ߧ� / ���ӧ��� �է�ѧܧ�ߧ� ���ݧާ�ݧ�
		UNC_11 = 11, //���էѧ� �ާ�ݧߧڧ� �ާ�ݧڧ�ӧ� �� ���ӧ��֧ߧߧ�� �ާ�ݧߧڧ�
		
	};
	char	type;	// 0�� 1�� 2������ 3Ŀ���� 4Բ׶�� 5����
public:
	Range(char t=1) : type(t) { }

#ifdef INTEPRETED_EXPR 
	std::string		radius_exp;				// Բ���뾶,������뾶
	std::string		attackdistance_exp;		// ɱ�˾���
	std::string		angle_exp;				// ���Ž�
	std::string		praydistance_exp;		// ��������
	std::string		effectdistance_exp;		// �����Ч����
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

