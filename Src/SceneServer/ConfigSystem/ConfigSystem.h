
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

	// 初始化
	BOOL		Initialize( VOID );

	//// 定义消息回调
	//VOID		InitPacketHandles( );

	//// 回收处理
	//BOOL		Finalize( VOID );

	//// 心跳函数
	//VOID		HeartBeat( INT iSkip, FLOAT fTimePass);

	//// 连接
	//VOID		OnConnected( Stub* pStub );
	//// 断开
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
			//参数  目标buffer，目标buffer长度，从多少读取，读多少
			memcpy_s(cBuffer,dataLen,buffer + i *dataLen, dataLen);
			t[i] = (T*)cBuffer;
		}
	}
};