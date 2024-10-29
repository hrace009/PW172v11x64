#ifndef __ONLINEGAME_GS_SUBSTANCE_H__
#define __ONLINEGAME_GS_SUBSTANCE_H__

#include <common/base_wrapper.h>
#include <ASSERT.h>
#include <amemobj.h>

#define DECLARE_SUBSTANCE(classname)	\
		static ClassInfo m_class##classname;\
		static classname *  CreateObject();\
		static ClassInfo *  GetClass() { return &classname::m_class##classname;} \
		virtual ClassInfo * GetRunTimeClass(); \
		static unsigned int 	GetSubstanceSize(); 
		

#define DEFINE_SUBSTANCE(classname,base,guid)	\
		ClassInfo classname::m_class##classname(#classname,guid,&base::m_class##base,(substance *(*)())classname::CreateObject,classname::GetSubstanceSize());\
		ClassInfo * classname::GetRunTimeClass() { return &classname::m_class##classname;} \
		classname *  classname::CreateObject() { return new classname;}\
		unsigned int 	classname::GetSubstanceSize() { return sizeof(classname);}\

#define DEFINE_SUBSTANCE_ABSTRACT(classname,base,guid)	\
		ClassInfo classname::m_class##classname(#classname,guid,&base::m_class##base,(substance *(*)())classname::CreateObject, classname::GetSubstanceSize());\
		ClassInfo * classname::GetRunTimeClass() { return &classname::m_class##classname;} \
		classname *  classname::CreateObject() { return NULL;}\
		unsigned int 	classname::GetSubstanceSize() { return sizeof(classname);}\

#define CLASSINFO(name) (name::GetClass())
		
class substance;
class ClassInfo
{
	ClassInfo * _next;
	ClassInfo * _prev;
	const char * _name;
	unsigned int  _guid;
	substance * (*_pfCreate)();
	ClassInfo * _base;
public:
	ClassInfo (const char * name, unsigned int guid,ClassInfo * pBase,substance *(*)(),unsigned int size);
	~ClassInfo ();
	inline const char * GetName() { return _name;}
	inline unsigned int GetGUID() { return _guid;}
	inline ClassInfo * GetBaseClass() { return _base;}
	bool IsDerivedFrom(const ClassInfo * base);
	static ClassInfo * GetRunTimeClass(const char *name);
	static ClassInfo * GetRunTimeClass(unsigned int guid);
	substance * CreateObject() 
	{
		return _pfCreate();
	}
	
};

class substance : public abase::ASmallObject
{
public:
DECLARE_SUBSTANCE(substance);
	virtual ~substance(){}
public:
	/*
	 * �������ݵ�archive��
	 * ע�����ﲻҪ����guid,�����Ҫʹ�ñ���guid�ķ���,
	 * ʹ�ú���SaveInstance������
	 */
	virtual bool Save(archive & ar)
	{ 
		ASSERT(false);
		return false;
	}

	/*
	 * �������Save�ķ�����,
	 * �����Ҫ��һ��������guid��archive�лָ��Ļ�
	 * ֱ��ʹ�þ�̬����LoadInstance
	 */
	virtual bool Load(archive & ar)
	{ 
		ASSERT(false);
		return false;
	}

	virtual substance * Clone() const
	{
		ASSERT(false);
		return NULL;
	}
public:
	/*
	 *	��һ��guid����һ�����ʵ��
	 */
	inline static substance * CreateInstance(unsigned int guid)
	{
		ClassInfo * pInfo = ClassInfo::GetRunTimeClass(guid);
		if(pInfo) 
			return pInfo->CreateObject();
		else
			return NULL;
	}


	template <typename CC> 	//CC ChildClass
	static inline CC * DynamicCast(substance * obj)
	{
	//	typedef CHILDCLASS:: childclass;
		if(obj == NULL) return NULL;
		if(obj->GetRunTimeClass()->IsDerivedFrom(CLASSINFO(CC)))
		{
			return (CC*)obj;
		}
		return NULL;
	}

	/*
	 *	��archive�����ɲ���װ��һ����
	 */
	static substance * LoadInstance(archive & ar)
	{
		unsigned int guid;
	 	ar >> guid;
		substance * pObj = CreateInstance(guid);
		if(pObj)
		{
			bool bRst = pObj->Load(ar);
			if(bRst) return pObj;
			delete pObj;
			return NULL;
		}
		else
		{
			ASSERT(false);
			return NULL;
		}
	}

	static substance * LoadInstance(unsigned int guid, archive & ar)
	{
		substance * pObj = CreateInstance(guid);
		if(pObj)
		{
			bool bRst = pObj->Load(ar);
			if(bRst) return pObj;
			delete pObj;
			return NULL;
		}
		else
		{
			ASSERT(false);
			return NULL;
		}
	}

	template <typename TT >
	static TT * LoadSpecInstance(unsigned int guid, archive & ar)
	{
		substance * pSub = CreateInstance(guid);
		TT * pObj = NULL;
		if(!pSub || (pObj = DynamicCast<TT>(pSub)) == NULL)
		{
			ASSERT(false);
			delete pObj;
			return NULL;
		}
		bool bRst = pObj->Load(ar);
		if(bRst) return pObj;
		ASSERT(false);
		delete pObj;
		return NULL;
	}


	/*
	 *	����һ�����guid���౾�������
	 */
	bool SaveInstance(archive & ar)
	{
		ar << GetGUID();
		return Save(ar);
	}

	/*
	 *	ȡ��һ�����GUID
	 */
	unsigned int GetGUID() 
	{
		return GetRunTimeClass()->GetGUID();
	}
};

template <typename BASE>
inline BASE * CreateDerivedInstance(unsigned int guid)
{
	ClassInfo * pInfo = ClassInfo::GetRunTimeClass(guid);
	if(!pInfo || !pInfo->IsDerivedFrom(CLASSINFO(BASE))) 
	{
		ASSERT(false && "���Ͳ�ƥ��");
		return NULL;
	}
	BASE * pIns = (BASE*)pInfo->CreateObject();
	return pIns;
}

#endif
