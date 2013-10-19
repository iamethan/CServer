
#include "Utility.h"
#include "Net.h"
#include "Framework.h"
#include "Define/SystemDefine.h"
#include "Helper/FileHelper.h"

class ConfigSystem : public GSystem
{
public: 
	ConfigSystem();
	virtual ~ConfigSystem();

	const CHAR*	SystemName( VOID )	{ return "ConfigSystem";	}
	const INT	SystemID( VOID )	{ return SYSTEM_ID_CONFIG_SYSTEM;	}

	// ��ʼ��
	BOOL		Initialize( VOID );

	//// ������Ϣ�ص�
	//VOID		InitPacketHandles( );

	//// ���մ���
	//BOOL		Finalize( VOID );

	//// ��������
	//VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	//// ����
	//VOID		OnConnected( Stub* pStub );
	//// �Ͽ�
	//VOID		OnDisconnected( Stub* pStub );
	

private:
	void LoadData();
	void ReadFile();

	template<typename T>
	void PerstrainFile(T**& t , char* filePath)
	{
		FileHelper fileHelper;
		char path[128] ={0};
		strcpy(path,filePath);
		//strcat(path,"playerproperty.bin");

		unsigned short dataLen =0 ;
		unsigned short dataCount =0;

		char* buffer  = fileHelper.PrestrainFileHelper(path,dataLen,dataCount);
		t = new T*[dataCount];

		for(int i = 0; i < dataCount; i++)
		{
			char* cBuffer =new char[dataLen];
			//����  Ŀ��buffer��Ŀ��buffer���ȣ��Ӷ��ٶ�ȡ��������
			memcpy_s(cBuffer,dataLen,buffer + i *dataLen, dataLen);
			t[i] = (T*)cBuffer;
		}
	}
};