#include "stdafx.h"
#include "ListenSocket.h"
#include  "ChatserverDlg.h"
CListenSocket::CListenSocket(CChatserverDlg * m_pdlg):m_dlg(m_pdlg)
{
}


CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_dlg->OnAccept();
	CSocket::OnAccept(nErrorCode);
}
