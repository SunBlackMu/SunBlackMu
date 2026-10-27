// CommandManager.cpp: implementation of the CCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommandManager.h"
#include "QueryManager.h"
#include "SocketManager.h"

CCommandManager gCommandManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommandManager::CCommandManager() // OK
{

}

CCommandManager::~CCommandManager() // OK
{

}

void CCommandManager::GDCommandResetRecv(SDHP_COMMAND_RESET_RECV* lpMsg,int index) // OK
{
	SDHP_COMMAND_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x00,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

	gQueryManager.ExecQuery("EXEC WZ_GetResetInfo '%s','%s'",lpMsg->account,lpMsg->name);

	gQueryManager.Fetch();

	pMsg.ResetDay = gQueryManager.GetAsInteger("ResetDay");

	pMsg.ResetWek = gQueryManager.GetAsInteger("ResetWek");

	pMsg.ResetMon = gQueryManager.GetAsInteger("ResetMon");

	gQueryManager.Close();

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandMasterResetRecv(SDHP_COMMAND_MASTER_RESET_RECV* lpMsg,int index) // OK
{
	SDHP_COMMAND_MASTER_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x01,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

	gQueryManager.ExecQuery("EXEC WZ_GetMasterResetInfo '%s','%s'",lpMsg->account,lpMsg->name);

	gQueryManager.Fetch();

	pMsg.MasterResetDay = gQueryManager.GetAsInteger("MasterResetDay");

	pMsg.MasterResetWek = gQueryManager.GetAsInteger("MasterResetWek");

	pMsg.MasterResetMon = gQueryManager.GetAsInteger("MasterResetMon");

	gQueryManager.Close();

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandMarryRecv(SDHP_COMMAND_MARRY_RECV* lpMsg,int index) // OK
{
    SDHP_COMMAND_MARRY_SEND pMsg;
    pMsg.header.set(0x0F,0x02,sizeof(pMsg));
    pMsg.index = lpMsg->index;
    memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));
    memcpy(pMsg.marryname,lpMsg->marryname,sizeof(pMsg.marryname));
    memcpy(pMsg.mode,lpMsg->mode,sizeof(pMsg.mode));
    gQueryManager.ExecQuery("EXEC WZ_GetMarryInfo '%s','%s'",lpMsg->name,lpMsg->marryname);
    gQueryManager.Fetch();
    pMsg.countyou = gQueryManager.GetAsInteger("CountYou");
    pMsg.counthim = gQueryManager.GetAsInteger("CountHim");
    pMsg.marriedon = gQueryManager.GetAsInteger("MarriedOn");
    gQueryManager.GetAsString("NameGet1",pMsg.NameGet1,sizeof(pMsg.NameGet1));
    gQueryManager.GetAsString("NameGet2",pMsg.NameGet2,sizeof(pMsg.NameGet2));
    gQueryManager.Close();
    gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}