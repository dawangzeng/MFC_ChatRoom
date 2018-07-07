
// ChatserverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chatserver.h"
#include "ChatserverDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ClientSocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::list<CClientSocket*> m_listSocket;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatserverDlg �Ի���



CChatserverDlg::CChatserverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pListenSocket = nullptr;
}

void CChatserverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CChatserverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_START, &CChatserverDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUT_STOP, &CChatserverDlg::OnBnClickedButStop)
END_MESSAGE_MAP()


// CChatserverDlg ��Ϣ�������

BOOL CChatserverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	m_list.InsertColumn(0, L"IP��ַ", LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, L"�˿ں�", LVCFMT_LEFT, 200);
	GetDlgItem(IDC_BUT_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_STOP)->EnableWindow(FALSE);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChatserverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatserverDlg::OnPaint()
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
HCURSOR CChatserverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatserverDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pListenSocket = new CListenSocket(this);
	//�����׽���
	if (FALSE == m_pListenSocket->Create(6666, SOCK_STREAM))
	{
		CString str;
		str.Format(L"���������׽���ʧ��!,������:%d", GetLastError());
		MessageBox(str, L"��ܰ��ʾ", MB_OK | MB_ICONERROR);
		delete m_pListenSocket;
		m_pListenSocket = nullptr;
		return ;
	}
	if (FALSE == m_pListenSocket->Listen(8))
	{
		CString str;
		str.Format(L"�����׽���ʧ��!,������:%d", GetLastError());
		MessageBox(str, L"��ܰ��ʾ", MB_OK | MB_ICONERROR);
		delete m_pListenSocket;
		m_pListenSocket = nullptr;
		return;
	}
	//�޸ķ�����
	GetDlgItem(IDC_BUT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_STOP)->EnableWindow(TRUE);

}


void CChatserverDlg::OnBnClickedButStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (nullptr == m_pListenSocket)
	{
		return;
	}
	else
	{
		m_pListenSocket->Close();
		delete m_pListenSocket;
		m_pListenSocket = nullptr;
	}
	GetDlgItem(IDC_BUT_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_STOP)->EnableWindow(FALSE);
}

void CChatserverDlg::OnAccept()
{
	CClientSocket *m_client = new CClientSocket;
	m_pListenSocket->Accept(*m_client);

	CString str;
	UINT port;

	m_client->GetPeerName(str, port);

	m_list.InsertItem(0, str);
	CString portstr;
	portstr.Format(L"%d", port);
	m_list.SetItemText(0, 1, portstr);
	m_listSocket.push_back(m_client);


}
