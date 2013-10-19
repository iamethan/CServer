#ifndef __STUB_POOL_H__
#define __STUB_POOL_H__

#include "Utility.h"

#define DEFAULT_STUB_POOL_SIZE	2048

class Stub;
class PacketFactoryManager;

class StubPool
{
public:
	StubPool( );
	virtual ~StubPool();

	BOOL	Init( UINT nMaxSize );

	// �ӿ��г��з���һ����ڵ�
	Stub*	NewStub( BOOL bIsServer = FALSE );

	// ���ڵ㷵�س���
	VOID	DelStub( Stub* pStub );

private:
	ObjPool<Stub>	m_ObjPool;

	UINT			m_nClientStubCount;
	UINT			m_nServerStubCount;
};

#endif // __STUB_POOL_H__