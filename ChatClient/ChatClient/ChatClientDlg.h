
// ChatClientDlg.h : ͷ�ļ�
//

#pragma once
#include "ClientSocket.h"
#include "afxcmn.h"
#include "afxwin.h"

// CChatClientDlg �Ի���
class CChatClientDlg : public CDialogEx
{
// ����
public:
	CChatClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CClientSocket *m_pClientSocket;
	CIPAddressCtrl m_ip;
private:
	UINT m_uPort;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButSend();
	CString m_text;
	CEdit m_showText;
	afx_msg void OnBnClickedButClose();
};