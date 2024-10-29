#ifndef __SKILL_SKILLLEVEL_H
#define __SKILL_SKILLLEVEL_H

namespace GNET
{

class SkillWrapper;
class SkillLevel
{
	SkillWrapper * skillwrapper;
	int cls;
public:
	SkillLevel(SkillWrapper * s=NULL,int cl = 0) : skillwrapper(s),cls(cl) { }

	int GetValue(int index);
	void SetValue(int index, int value);
};

class BuffLevel
{
	object_interface  object;
public:	
	BuffLevel() {}
	BuffLevel(object_interface  o) : object(o) { }
	
	int GetValue(int index);
	void SetValue(int index, int value){}
};

class ComboArg
{
	SkillWrapper * skillwrapper;
public:
	ComboArg(SkillWrapper * s=NULL) : skillwrapper(s) { }
	int GetValue(int index);
	void SetValue(int index, int value);
};

}

#endif

