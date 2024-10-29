
#include <unistd.h>
#include <mcheck.h>

#include <iostream>

#include "conf.h"
#include "skill.h"
#include "playerwrapper.h"
#include "targetwrapper.h"
#include "skillwrapper.h"
#include "expr.h"

using std::cout;
using std::endl;
using namespace GNET;

class SkillRun : public IntervalTimer::Observer
{
	SkillWrapper * skillwrapper;
	SkillWrapper::Data * skilldata;

	object_interface player;
	const XID target;
	int next_interval;
public:
	SkillRun()
	{
		skillwrapper = new SkillWrapper();
		skilldata = new SkillWrapper::Data(1);
	}
	~SkillRun() { delete skillwrapper; delete skilldata; }

	void Start()
	{
		int ret = skillwrapper->StartSkill( *skilldata, player, &target, 1, next_interval );
		printf( "StartSkill ret = %d next_interval = %d\n", ret, next_interval );
		if( ret > 0 )
			IntervalTimer::Attach( this, ret*1000/IntervalTimer::Resolution() );
		else
			delete this;
	}

	void Run()
	{
		int ret = skillwrapper->Run( *skilldata, player, &target, 1, next_interval );
		printf( "StartSkill ret = %d next_interval = %d\n", ret, next_interval );
		if( ret > 0 )
			IntervalTimer::Attach( this, next_interval*1000/IntervalTimer::Resolution() );
		else
			delete this;
	}

	bool Update()
	{
		Run();
		return false;
	}
};

int main(int argc, char ** argv)
{
	setenv("MALLOC_TRACE", "./m.log", 1);
	mtrace();

	srand(time(NULL));
	Conf::GetInstance("io.conf");
	Log::setprogname( "skilltest" );

	IntervalTimer::StartTimer(50000);
	Expr::GetInstance("skill.og");

#ifdef INTEPRETED_EXPR 
	SkillStub::Store( "skill.dat" );
	for( int i=0; i<1; i++ )
		SkillStub::Load( "skill.dat" );

	SkillStub::Store( "skill2.dat" );
#endif
/*
	SkillKeeper skill = Skill::Create(5);
	static TargetWrapper target(NULL);
	static SkillWrapper wrapper;
	static PlayerWrapper player(NULL,NULL,NULL,skill);
	if( skill )
	{
		skill->AutoRun(&player, &target, &wrapper);
	}
	else
	{
		printf( "Skill::Create return NULL.\n" );
	}
*/
//	SkillRun * run = new SkillRun();
//	run->Start();

//	Thread::Pool::Run( );

	muntrace();
	return EXIT_SUCCESS;
}


