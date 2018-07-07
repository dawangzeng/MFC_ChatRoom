
// ChatserverDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ListenSocket.h"
#include "resource.h"
#include "ClientSocket.h"
#include <list>
// CChatserverDlg �Ի���
class CChatserverDlg : public CDialogEx
{
// ����
public:
	CChatserverDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
private:
	CListCtrl m_list;
public:
	afx_msg void OnBnClickedButton1();
	CListenSocket *m_pListenSocket;
	afx_msg void OnBnClickedButStop();
	void OnAccept();
	
	
};
