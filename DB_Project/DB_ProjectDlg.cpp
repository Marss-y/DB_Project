
// DB_ProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DB_Project.h"
#include "DB_ProjectDlg.h"
#include "afxdialogex.h"

#include "odbcinst.h"
#include "afxdb.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CDBProjectDlg dialog



CDBProjectDlg::CDBProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DB_PROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, m_listview);
}

BEGIN_MESSAGE_MAP(CDBProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDBProjectDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST3, &CDBProjectDlg::OnLbnSelchangeList3)
END_MESSAGE_MAP()


// CDBProjectDlg message handlers

BOOL CDBProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//---------------------------------------
	//server=localhost;user id=FavLincsUserPass; persistsecurityinfo=True;database=apt
	CDatabase cDb;



	
	TRY
	{
	 bool flag = cDb.Open(_T("FavLincsConection"), FALSE, FALSE, _T("ODBC;UID = FavLincsUser; PWD = FavLincsUserPass"));
	// cDb.ExecuteSQL(_T("Select * from myusers")); - не връща резултат

 CRecordset myr( &cDb);
	// myr.Open(CRecordset::dynaset, "{CALL GetUsers()}");
	 myr.Open(CRecordset::snapshot, _T("SELECT Id, IdType, URL, Note, DateAdd, IdLanguage, IdStatus FROM address"));

	 //db.ExecuteSQL(_T("EXEC get_author_titles '998-72-3567'"));
	// bool flag = cDb.OpenEx(_T("DSN = MySQL_Connection; UID = Karakondjul; PWD = Karakondjul"));Get
//	cDb.OpenEx(_T("Driver={MySQL ODBC 5.1 Driver};Serverlocalhost;Database=apt;User=Karakondjul; Password=Karakondjul;Option=3;"), CDatabase::noOdbcDialog);
	 CString val;
	 CString IdType;
	 CString Id;
	 

	 


	 m_listview.InsertColumn(0, "Id", LVCFMT_LEFT, 30);
	 m_listview.InsertColumn(1, "IdType", LVCFMT_LEFT, 30);
	 m_listview.InsertColumn(2, "URL", LVCFMT_LEFT, 200);
	 m_listview.InsertColumn(3, "Note", LVCFMT_CENTER, 200); //98
	 m_listview.InsertColumn(4, "DateAdd", LVCFMT_LEFT, 50);
	 m_listview.InsertColumn(5, "IdLanguage", LVCFMT_RIGHT, 30);
	 m_listview.InsertColumn(6, "IdStatus", LVCFMT_RIGHT, 30);

	 int count = myr.GetRecordCount();

	 while (!myr.IsEOF())
	 {
		 myr.GetFieldValue(_T("URL"), val);
		 myr.GetFieldValue(_T("Id"), Id);
		 myr.GetFieldValue(_T("IdType"), IdType);

		 int nItem;

		 nItem = m_listview.InsertItem(0, Id);
		 m_listview.SetItemText(nItem, 1, IdType);
		 m_listview.SetItemText(nItem, 2, val);
		 m_listview.SetItemText(nItem, 3, IdType);
		 m_listview.SetItemText(nItem, 4, IdType);
		 m_listview.SetItemText(nItem, 5, IdType);
		 m_listview.SetItemText(nItem, 6, IdType);

		 myr.MoveNext();

	 }

	 myr.Close();
	 cDb.Close();
	}
		CATCH(CDBException, e)
	{
		AfxMessageBox(e->m_strError);
	}
	END_CATCH;
	//-----------------------------------------

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDBProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDBProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDBProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDBProjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CDBProjectDlg::OnLbnSelchangeList3()
{
	// TODO: Add your control notification handler code here
}
