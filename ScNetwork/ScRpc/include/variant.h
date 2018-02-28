
#ifndef VARIANT_H
#define VARIANT_H
#define CVARIANT_TYPE

#include "Types.h"
#include <string>
#include <vector>
#include "ScpDefine.h"

using namespace std;

class CBuffer;
namespace Scp{
	typedef enum _eVariantType{
		eVariantType_invalid=-1,
		eVariantType_int8=0,
		eVariantType_uint8, 
		eVariantType_int16,
		eVariantType_uint16,
		eVariantType_int32,
		eVariantType_uint32,
		eVariantType_int64,
		eVariantType_uint64,
		eVariantType_float,
		eVariantType_double,
		eVariantType_bool,
		eVariantType_voidPtr,
		eVariantType_metaType,

		eVariantType_object=20,
		eVariantType_string,
		eVariantType_vector,
		eVariantType_list,
		eVariantType_buffer, //�ڴ淽ʽ
		eVariantType_objectEnd,
		//�ṹ�壬 �����Զ�Ƕ�׵Ľṹ�壬����ͨ�ṹ�壬��ͨ�ṹ�嶼���ö���
		eVariantType_struct,
		eVariantType_class,
	}eVariantType;


	union _uVariantData ;
	//typedef struct _sVariantSturct sVariantSturct;
	//֧�ֻ������ͣ� string ����֧����������
class SCP_API CVariant{
	typedef struct _sVariantStruct{
	public:
		_sVariantStruct();
		~_sVariantStruct();

		vector<CVariant*>	m_arrMembers;
	}sVariantStruct;

	typedef union _uVariantData{
		char			m_i8;
		unsigned char	m_u8;
		short			m_i16;
		unsigned short	m_u16;
		int				m_i32;
		unsigned int	m_u32;
		long long		m_i64;
		unsigned long long m_u64;
		float			m_float;
		double			m_double;
		void*			m_ptr;
		void*			m_pObject;		
		sVariantStruct*	m_pStruct;

		//vector<uVariantData*>*	m_arrValue;
		//vector<char>*			m_arrBuffer;
	}uVariantData;
public:
	CVariant();
	CVariant(const CVariant &other);
	~CVariant();
	
	CVariant(int8);
	CVariant(uint8);
	CVariant(int16);
	CVariant(uint16);
	CVariant(int32);
	CVariant(uint32);
	CVariant(int64);
	CVariant(uint64);
	CVariant(float);
	CVariant(double);
	CVariant(void*);
	//�� string ��Ч
	CVariant(char*);
	//
	CVariant(string&);
	//����һ��vector������
	//CVariant(eVariantType_vector);
	//
	CVariant(eVariantType type);
	//�����ṹ�塣variant�Ľṹ�塣�� c++.��׼�ṹ�� �࣬�����ö���
	void	StructAppendMember(CVariant *varMember);
	//int		StructGetMemberCount(){return m_value.m_pStruct->m_arrMembers.size();};
	//�����ʱ��ʹ��
// 	vector<CVariant*>& GetVector(){
// 		return m_arrValue;
// 	}
	//
	template <class T>
		T Value(){ 
			
			if (m_nType == eVariantType_string)
			{
				char *pText(NULL);
				string* pStr = reinterpret_cast<string*>(m_value.m_pObject);
				pText = (char*)pStr->c_str();
				return (T)pText;
			}
			else{
				return *reinterpret_cast<T*>(&m_value);
			}
		}
// 	template <class T>
// 	void SetValue(T val){
// 		*reinterpret_cast<T*>(&m_value) = val;
// 	}
	char* Value(){
		char *pText(NULL);
		if (m_nType == eVariantType_string)
		{
			string* pStr = reinterpret_cast<string*>(m_value.m_pObject);
			pText = (char*)pStr->c_str();
		}
		return pText;
	};
	void SetValue(char* pSzText);
	void SetValue(string& strText);
	void SetValue(int8);
	void SetValue(uint8);
	void SetValue(int16);
	void SetValue(uint16);
	void SetValue(int32);
	void SetValue(uint32);
	void SetValue(int64);
	void SetValue(uint64);
	void SetValue(float);
	void SetValue(double);
	void SetValue(void*);
	//����
	template <class T>
	T& RefValue(){return *reinterpret_cast<T*>(&m_value);}
	//
	virtual void	CopyFrom(CVariant *pVar);
	//
	virtual void	Clear();
	//
	virtual int		WriteTo(CBuffer *pBuffer);
	virtual int		ReadFrom(CBuffer *pBuffer);

	CVariant& operator =(const CVariant &other);
protected:
	int				m_nType;

	//����
	uVariantData	m_value;
	//���������buffer ��

	//
	static int		m_mapTypeSize[255];
	//
};

}

#endif

