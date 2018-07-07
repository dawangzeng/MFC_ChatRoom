#include "stdafx.h"
#include "ClientSocket.h"
#include "ChatClientDlg.h"

CClientSocket::CClientSocket(CChatClientDlg *p):m_pDlg(p)
{
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	TCHAR msg[1024] = {0};
	Receive(msg, 1024 * 2);

	//显示
	int length=m_pDlg->m_showText.GetWindowTextLength();
	m_pDlg->m_showText.SetSel(length, -1);
	m_pDlg->m_showText.ReplaceSel(msg);
	CSocket::OnReceive(nErrorCode);
}


//void CClientSocket::OnClose(int nErrorCode)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	CSocket::OnClose(nErrorCode);
//}
