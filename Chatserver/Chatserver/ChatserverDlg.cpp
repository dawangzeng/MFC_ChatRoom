
// ChatserverDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CChatserverDlg 对话框



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


// CChatserverDlg 消息处理程序

BOOL CChatserverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_list.InsertColumn(0, L"IP地址", LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, L"端口号", LVCFMT_LEFT, 200);
	GetDlgItem(IDC_BUT_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_STOP)->EnableWindow(FALSE);
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatserverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatserverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatserverDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pListenSocket = new CListenSocket(this);
	//创建套接字
	if (FALSE == m_pListenSocket->Create(6666, SOCK_STREAM))
	{
		CString str;
		str.Format(L"创建网络套接字失败!,错误码:%d", GetLastError());
		MessageBox(str, L"温馨提示", MB_OK | MB_ICONERROR);
		delete m_pListenSocket;
		m_pListenSocket = nullptr;
		return ;
	}
	if (FALSE == m_pListenSocket->Listen(8))
	{
		CString str;
		str.Format(L"监听套接字失败!,错误码:%d", GetLastError());
		MessageBox(str, L"温馨提示", MB_OK | MB_ICONERROR);
		delete m_pListenSocket;
		m_pListenSocket = nullptr;
		return;
	}
	//修改服务器
	GetDlgItem(IDC_BUT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_STOP)->EnableWindow(TRUE);

}


void CChatserverDlg::OnBnClickedButStop()
{
	// TODO: 在此添加控件通知处理程序代码
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
