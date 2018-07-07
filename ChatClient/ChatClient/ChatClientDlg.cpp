
// ChatClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatClientDlg �Ի���



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHATCLIENT_DIALOG, pParent)
	, m_uPort(6666)
	, m_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pClientSocket = nullptr;
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Text(pDX, IDC_EDIT3, m_uPort);
	DDX_Text(pDX, IDC_EDIT2, m_text);
	DDX_Control(pDX, IDC_EDIT1, m_showText);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_CONNECT, &CChatClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUT_SEND, &CChatClientDlg::OnBnClickedButSend)
	ON_BN_CLICKED(IDC_BUT_CLOSE, &CChatClientDlg::OnBnClickedButClose)
END_MESSAGE_MAP()


// CChatClientDlg ��Ϣ�������

BOOL CChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_BUT_CONNECT)->EnableWindow(true);
	m_ip.SetWindowTextW(L"127.0.0.1");
	UpdateData(false);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString str;
	m_ip.GetWindowText(str);
	if (str.IsEmpty() || str == L"0.0.0.0")
	{
		MessageBox(L"��������ЧIP��ַ!", L"TIPS!", MB_OK | MB_ICONERROR);
		return;
	}
	m_pClientSocket = new CClientSocket(this);
	if (FALSE == m_pClientSocket->Create())
	{
		CString str;
		str.Format(L"���������׽���ʧ��!,������:%d", GetLastError());
		MessageBox(str, L"��ܰ��ʾ", MB_OK | MB_ICONERROR);
		delete m_pClientSocket;
		m_pClientSocket = nullptr;
		return;
	}
	//�����׽���
	
	if (FALSE == m_pClientSocket->Connect(str, m_uPort))
	{
		MessageBox(L"����ʧ�ܣ�");
		delete m_pClientSocket;
		m_pClientSocket = nullptr;
		return;
	}
	GetDlgItem(IDC_BUT_CONNECT)->EnableWindow(false);

}


void CChatClientDlg::OnBnClickedButSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_pClientSocket == nullptr)
	{
		MessageBox(L"�������ӷ�����!");
		return;
	}
	if (m_text.IsEmpty())
	{
		MessageBox(L"���Ͳ���Ϊ��!");
		return;
	}
	if (m_text.GetLength()>1024)
	{
		MessageBox(L"������Ϣ̫�࣬����һ�㣡");
		return;
	}

	if (0 > m_pClientSocket->Send(m_text, m_text.GetLength() * 2))
	{
		MessageBox(L"����ʧ�ܣ�");
		return;
	}
	m_text.Empty();
	UpdateData(false);

}


void CChatClientDlg::OnBnClickedButClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
