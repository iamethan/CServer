#pragma once

class CTransformPack_REQ_Handle
{
public:
	static PACKET_EXE Execute(CBasePack* pPacket, Player* pPlayer);
};

class CTransformEndPack_REQ_Handle
{
public:
	static PACKET_EXE Execute(CBasePack* pPacket, Player* pPlayer);
};