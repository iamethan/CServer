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

	// 从空闲池中分配一网络节点
	Stub*	NewStub( BOOL bIsServer = FALSE );

	// 将节点返回池中
	VOID	DelStub( Stub* pStub );

private:
	ObjPool<Stub>	m_ObjPool;

	UINT			m_nClientStubCount;
	UINT			m_nServerStubCount;
};

#endif // __STUB_POOL_H__