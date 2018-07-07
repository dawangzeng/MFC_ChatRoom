#include "stdafx.h"
#include "ClientSocket.h"
#include<list>
extern std::list<CClientSocket*> m_listSocket;
CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	TCHAR meg[1024] = { 0 };
	Receive(meg, sizeof(meg));

	CString str;
	UINT port;
	GetPeerName(str, port);
	CString allmsg;
	allmsg.Format(L"%s:%d>>%s\r\n", str, port, meg);
	

	std::list<CClientSocket*>::iterator it;
	for (it = m_listSocket.begin(); it != m_listSocket.end(); ++it)
	{
		CClientSocket *client = *it;
		client->Send(allmsg, allmsg.GetLength()*2);
	}
	CSocket::OnReceive(nErrorCode);
}
