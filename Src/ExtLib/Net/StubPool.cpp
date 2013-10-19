#include "StubPool.h"
#include "Stub.h"
#include "PacketFactoryManager.h"

StubPool::StubPool( )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

StubPool::~StubPool()
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}


BOOL StubPool::Init( UINT nMaxSize )
{
__ENTER_FUNCTION

	m_nClientStubCount = 0;
	m_nServerStubCount = 0;

	return m_ObjPool.Init( nMaxSize );

__LEAVE_FUNCTION

	return FALSE;
}

// 从空闲池中分配一网络节点
Stub* StubPool::NewStub( BOOL bIsServer /*= FALSE*/ )
{
__ENTER_FUNCTION

	Stub* pStub = m_ObjPool.NewObj();
	if( pStub )
	{
		pStub->Init( bIsServer );
	}

	if( bIsServer )
	{
		++m_nServerStubCount;
	}
	else
	{
		++m_nClientStubCount;
	}

	return pStub;

__LEAVE_FUNCTION

	return NULL;
}

// 将节点返回池中
VOID StubPool::DelStub( Stub* pStub )
{
__ENTER_FUNCTION

	if( pStub->IsServerStub() )
	{
		--m_nServerStubCount;
	}
	else
	{
		--m_nClientStubCount;
	}

	m_ObjPool.DeleteObj( pStub );

__LEAVE_FUNCTION
}