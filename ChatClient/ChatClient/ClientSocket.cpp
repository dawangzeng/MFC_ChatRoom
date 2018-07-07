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
	// TODO: �ڴ����ר�ô����/����û���
	TCHAR msg[1024] = {0};
	Receive(msg, 1024 * 2);

	//��ʾ
	int length=m_pDlg->m_showText.GetWindowTextLength();
	m_pDlg->m_showText.SetSel(length, -1);
	m_pDlg->m_showText.ReplaceSel(msg);
	CSocket::OnReceive(nErrorCode);
}


//void CClientSocket::OnClose(int nErrorCode)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//	CSocket::OnClose(nErrorCode);
//}
