#ifndef __SKILL_CALLUP_H
#define __SKILL_CALLUP_H

#include <string>

namespace GNET
{

class Callup
{
public:
	int		id;						// 召唤物ID
	int		count;					// 个数

	int		livetime;				// 存活时间
	int		hp;						// 血值
	int		attack_mode;			// 攻击方式 1点攻击 2面攻击
	bool	restrict_target;		// 是否需要目标
	float	rect_length;			// 面攻击矩形边长

	int		attack;					// 攻击力
	int		poison;					// 毒攻击
	int		attack_water;			// 水系攻击力
	float	wood_factor;			// 降低木系防御系数
	float	wood_prob;				// 降低木系防御系数概率
	float	fix_prob;				// 定身概率
	int		defence;				// 防御力
	float	velocity;				// 移动速度
	float	interval;				// 攻击间隔
	float	view;					// 视野
	float	search_distance;		// 自动寻找距离
	float	attack_distance;		// 攻击距离

	Callup(int i=0, int c=0) : id(i), count(c) { }
	Callup(const Callup &rhs) : id(rhs.id), count(rhs.count),
			livetime(rhs.livetime), hp(rhs.hp), attack_mode(rhs.attack_mode),
			restrict_target(rhs.restrict_target), rect_length(rhs.rect_length), attack(rhs.attack),
			poison(rhs.poison), attack_water(rhs.attack_water), wood_factor(rhs.wood_factor),
			wood_prob(rhs.wood_prob), fix_prob(rhs.fix_prob), defence(rhs.defence),
			velocity(rhs.velocity), interval(rhs.interval), view(rhs.view),
			search_distance(rhs.search_distance), attack_distance(rhs.attack_distance) { }
	virtual ~Callup() { }
	Callup& operator = (const Callup& rhs)
	{
		id = rhs.id;
		count = rhs.count;

		livetime = rhs.livetime;
		hp = rhs.hp;
		attack_mode = rhs.attack_mode;
		restrict_target = rhs.restrict_target;
		rect_length = rhs.rect_length;
    
		attack = rhs.attack;
		poison = rhs.poison;
		attack_water = rhs.attack_water;
		wood_factor = rhs.wood_factor;
		wood_prob = rhs.wood_prob;
		fix_prob = rhs.fix_prob;
		defence = rhs.defence;
		velocity = rhs.velocity;
		interval = rhs.interval;
		view = rhs.view;
		search_distance = rhs.search_distance;
		attack_distance = rhs.attack_distance;
		return *this;
	}

	void SetId(int i) { id = i; }
	int GetId() const { return id; }

	void SetCount(int c) { count = c; }
	int GetCount() const { return count; }

	void SetLivetime(int l) { livetime = l; }
	int GetLivetime() const { return livetime; }

	void SetHp(int h) { hp = h; }
	int GetHp() const { return hp; }

	void SetAttackmode(int a) { attack_mode = a; }
	int GetAttackmode() const { return attack_mode; }

	void SetRestricttarget(bool r) { restrict_target = r; }
	bool GetRestricttarget() const { return restrict_target; }

	void SetRectlength(float r) { rect_length = r; }
	float GetRectlength() const { return rect_length; }

	void SetAttack(int a) { attack = a; }
	int GetAttack() const { return attack; }

	void SetPoison(int p) { poison = p; }
	int GetPoison() const { return poison; }

	void SetAttackwater(int a) { attack_water = a; }
	int GetAttackwater() const { return attack_water; }

	void SetWoodfactor(float w) { wood_factor = w; }
	float GetWoodfactor() const { return wood_factor; }

	void SetWoodprob(float w) { wood_prob = w; }
	float GetWoodprob() const { return wood_prob; }

	void SetFixprob(float f) { fix_prob = f; }
	float GetFixprob() const { return fix_prob; }

	void SetDefence(int d) { defence = d; }
	int GetDefence() const { return defence; }

	void SetVelocity(float v) { velocity = v; }
	float GetVelocity() const { return velocity; }

	void SetInterval(float i) { interval = i; }
	float GetInterval() const { return interval; }

	void SetView(float v) { view = v; }
	float GetView() const { return view; }

	void SetSearchdistance(float s) { search_distance = s; }
	float GetSearchdistance() const { return search_distance; }

	void SetAttackdistance(float a) { attack_distance = a; }
	float GetAttackdistance() const { return attack_distance; }

};

}

#endif

