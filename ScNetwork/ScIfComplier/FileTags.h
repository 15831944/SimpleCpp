#pragma once
#include <vector>
#include <list>
using namespace std;
//����һ���ļ���tags
 
class CTag;
typedef enum _eTagType eTagType;
class CFileTags
{
public:
	CFileTags(void);
	virtual ~CFileTags(void);

	//
	void AppendTopTag(CTag* pTag);
	//
	void AppendToken(CTag* pTag);
	//
	list<CTag*>&	GetTopTags(){return m_lstTopTag;}
	CTag*			GetTags(eTagType type);
	CTag*			GetIfTag();
	//CFileTags::m_pFileTags
	static CFileTags*	m_pFileTags;
protected:
	//
	list<CTag*>	m_lstTopTag;
	//���е�token
	list<CTag*> m_lstToken;
	string		m_strFileName;
};
