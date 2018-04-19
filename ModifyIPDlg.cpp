// ModifyIPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModifyIP.h"
#include "ModifyIPDlg.h"
#include "Thread.h"
#include "../public/public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CCriticalSection CModifyIPDlg::m_oCS;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyIPDlg dialog

CModifyIPDlg::CModifyIPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyIPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyIPDlg)
	m_nType = -1;
	m_strInfo = _T("");
	m_nNGCnt = 0;
	m_nOKCnt = 0;
	m_strUIDSUM = _T("");
	m_nThread = 0;
	m_strServerInfo = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCurPos = 0;
	m_oPtrCarDEUID.RemoveAll();

	m_omapDEUIDObj.RemoveAll();
	m_strServerName = "211.154.139.226";
}

void CModifyIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyIPDlg)
	DDX_Radio(pDX, IDC_RADIO_211, m_nType);
	DDX_Text(pDX, IDC_INFOTEXT, m_strInfo);
	DDX_Text(pDX, IDC_NGCNT, m_nNGCnt);
	DDX_Text(pDX, IDC_OKCNT, m_nOKCnt);
	DDX_Text(pDX, IDC_UIDSUM, m_strUIDSUM);
	DDX_Text(pDX, IDC_THREAD, m_nThread);
	DDX_Text(pDX, IDC_SERVERNAME, m_strServerInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CModifyIPDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyIPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_SERVER, OnButtonModifyServer)
	ON_BN_CLICKED(IDC_SAVE_DATA, OnSaveData)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_FILE_MODE, OnButtonFileMode)
	ON_BN_CLICKED(IDC_RADIO_211, OnRadio_211)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_RADIO_14, OnRadio_211)
	ON_BN_CLICKED(IDC_RADIO_121, OnRadio_211)
	ON_BN_CLICKED(IDC_SCAN, OnScan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyIPDlg message handlers

BOOL CModifyIPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CModifyIPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CModifyIPDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CModifyIPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/////////////////////////////////////////////////////////////
//  连接数据库
void CModifyIPDlg::OnButtonConnect(){	

	if( ConnectDatabase() ){
		m_nCurPos = 0;
		SetTimer( TIMER_SETUP_IP, 20000, NULL );
	}
	else{
		m_nCurPos = 0;
		KillTimer(TIMER_SETUP_IP);	
	}
}
////////////////////////////////////////////////////////////////
//
BOOL   CModifyIPDlg::ConnectDatabase(){
	
	static   BOOL   bFlag = FALSE;
	BOOL			bResult = FALSE;
    
	if( bFlag == FALSE ){
		if( m_oDBData.Connect( TEXT_SERVER_NAME, TEXT_DATABASE_NAME, TEXT_USER_NAME, TEXT_USER_PSD ) ){

			bFlag = TRUE;
			bResult = TRUE;
			m_oDBData.GetAllDEUIDData( m_oPtrCarDEUID );	
			TRACE("车辆数:%d\r\n", m_oPtrCarDEUID.GetSize() );
			GetDlgItem( IDC_BUTTON_CONNECT )->SetWindowText("停止运行");
			//获取GPS数据
			GetServerTrackData();
		//	AfxBeginThread( StartSocketThread, NULL );
			AfxBeginThread( ModifyConfigThread, NULL );
		}
	}
	else{
		bFlag = FALSE;
		m_oDBData.DisConnect();
		GetDlgItem( IDC_BUTTON_CONNECT )->SetWindowText("开始运行");
		m_oPtrCarDEUID.RemoveAll();
	}
	return bResult;
}
//////////////////////////////////////////////////////////////
//   定时器
void CModifyIPDlg::OnTimer(UINT nIDEvent) 
{	
	if( nIDEvent == TIMER_SETUP_IP ){

		GetServerTrackData();
	}
	if( nIDEvent == IDC_TIME ){
				
		m_nNGCnt =  m_nSendFailed;
		m_nOKCnt =  m_nSendOK;
		
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}
//////////////////////////////////////////////////////////////
//   
BOOL CModifyIPDlg::DestroyWindow() 
{
	KillTimer(TIMER_SETUP_IP);	
	return CDialog::DestroyWindow();
}
/////////////////////////////////////////////////////////////////////////////
//  增加表头
void  PL_AddHead( unsigned char	*pBuf ){
	
	*pBuf++ = 0xE6;
	*pBuf = 0xE6;	
}
/////////////////////////////////////////////////////////////////////////////
//  增加序列号  取后8位
unsigned char  PL_AddTEUID( unsigned char	 *pBuf ){
	
	unsigned char 	nLen = 0;
	unsigned char	nPos = 0;
	unsigned char   nDEUID[9];
	
	strcpy( (char*)nDEUID, "88888888" );
	nLen = 8;
	pBuf[0] = nLen;
	memcpy( &pBuf[1], &nDEUID[0], nLen);
	return nLen + 1; 
}
/////////////////////////////////////////////////////////////////////////////
//
unsigned char  CModifyIPDlg::PL_CountVerifySum(unsigned char *lpDataBuf, int nDataLen){
	
	unsigned char nSumCheck = 0;
	unsigned char nCnt = 0;
	
	for ( nCnt = 0; nCnt < nDataLen; nCnt++){
		
		nSumCheck -= lpDataBuf[nCnt];
	}
	return nSumCheck;
}

/////////////////////////////////////////////////////////////////////////////
// 织织握手信息
unsigned char 	 CModifyIPDlg::PL_ComposeHSData( unsigned char	*pDest ){
	
	unsigned  char	nResultLen = 0;
	unsigned  char  nIPLen = 0;
	CString   str = "211.154.139.22";
	
	//  表头(2)
	PL_AddHead( pDest );
	//  消息类型(1)
	pDest[2] = MT_CONFIG_IP;	
	//  总长度(1)
	pDest[3] = 10;
	//  序号包数(1)
	pDest[4] = 6;	
	//  DEUID长度(1)+DEUID内容(n)
	PL_AddTEUID( &pDest[5] );
	//  数据类型(1)
	nIPLen = strlen(str/*TEXT_SERVER_NAME*/);
	pDest[14] = nIPLen;
	memcpy( &pDest[15], str/*TEXT_SERVER_NAME*/, nIPLen );
	//  校验和
	pDest[15+nIPLen] = PL_CountVerifySum(pDest, 15+nIPLen );	
	nResultLen = 16+nIPLen;
	
	return nResultLen;
}
//////////////////////////////////////////////////////////////////////////
//  修改服务器数据
void CModifyIPDlg::OnButtonModifyServer() 
{
	AfxBeginThread( ConfigSocketThread, NULL );
}
//////////////////////////////////////////////////////////////////////////
//	 获取数据
void  CModifyIPDlg::GetServerTrackData(){

	CPtrArray			outData;
	PSTDEUIDTIME		pTmp = NULL;
	PSTDEUIDTIME		pStDEUIDTime = NULL;
	
	outData.RemoveAll();
	if( m_oDBData.GetTrackData( outData ) ){
		
		for( int nCnt =0; nCnt < outData.GetSize(); nCnt++ ){

			pTmp  = (PSTDEUIDTIME)outData.GetAt( nCnt );
			if( m_omapDEUIDObj.Lookup( pTmp->m_nDEUID, (CObject*&)pStDEUIDTime) ){
					
				pStDEUIDTime->m_nNumber += 1;
				pStDEUIDTime->m_oTime = pTmp->m_oTime;
			}
			else{
				pStDEUIDTime = new STDEUIDTIME;
				memcpy( pStDEUIDTime, pTmp, sizeof(STDEUIDTIME) );
				m_omapDEUIDObj.SetAt( pTmp->m_nDEUID, (CObject*)pStDEUIDTime );
			}
			delete pTmp;
			pTmp = NULL;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//	比较数据
void	CModifyIPDlg::ComparisonTrackData(){

	CPtrArray			outData;
	PSTDEUIDTIME		pTmp = NULL;
	PSTDEUIDTIME		pStDEUIDTime = NULL;
	
	outData.RemoveAll();
	if( m_oDBData.GetTrackData( outData ) ){
		
		for( int nCnt =0; nCnt < outData.GetSize(); nCnt++ ){
			
			pTmp  = (PSTDEUIDTIME)outData.GetAt( nCnt );
			if( !m_omapDEUIDObj.Lookup( pTmp->m_nDEUID, (CObject*&)pStDEUIDTime) ){

				SaveConfigOK( pStDEUIDTime->m_nDEUID, pStDEUIDTime->m_oTime );
				delete pStDEUIDTime;
				pStDEUIDTime = NULL;
				m_omapDEUIDObj.RemoveKey( pTmp->m_nDEUID );
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//
void   CModifyIPDlg::SaveConfigOK( CString  strDEUID,  CTime   oTime ){

	CString		strData;
	CString		strFile;
	CFile		hFile;
	CString		strName;

	
	CTime  oTime2 = CTime::GetCurrentTime();
	strData.Format( "SN:%s\t 时间:%s\r\n", strDEUID, oTime.Format("%Y-%m-%d %H:%M:%S") ); 
	strName.Format("%s.txt", oTime2.Format("%H%M%S") ); 
	strFile = GetModulePath()+"\\"+strName;

	if ( hFile.Open(strFile, CFile::modeCreate|CFile::modeReadWrite, NULL) ){

		hFile.Write( strData, strData.GetLength() );
		hFile.Close();
	}
	else{
		// 创建目录
		if( CreateMultiFolder( GetModulePath() ) ){
			// 保存图像
			if( hFile.Open( strFile, CFile::modeCreate|CFile::modeReadWrite, NULL) ){
				hFile.Write( strData, strData.GetLength() );
				hFile.Close();
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//
void CModifyIPDlg::OnSaveData(){
		
	ComparisonTrackData();
}
//////////////////////////////////////////////////////////////////////////
//
void CModifyIPDlg::OnButtonModify() 
{	
	PSTDEUIDTIME	 pTmp = NULL;

	pTmp = new STDEUIDTIME;
	memcpy( pTmp->m_nDEUID, "01181380", sizeof(STDEUID ) );
	memcpy( pTmp->m_nCarLicense, "01181380", sizeof(STTELNUM ) );
	pTmp->m_oTime = 12312434;
	m_omapDEUIDObj.SetAt( "01181380", (CObject*)pTmp );

	pTmp = new STDEUIDTIME;
	memcpy( pTmp->m_nDEUID, "01508749", sizeof(STDEUID ) );
	memcpy( pTmp->m_nCarLicense, "01508749", sizeof(STTELNUM ) );
	pTmp->m_oTime = 12312434;
	m_omapDEUIDObj.SetAt( "01508749", (CObject*)pTmp );

	pTmp = new STDEUIDTIME;
	memcpy( pTmp->m_nDEUID, "10901000", sizeof(STDEUID ) );
	memcpy( pTmp->m_nCarLicense, "10901000", sizeof(STTELNUM ) );
	pTmp->m_oTime = 12312434;
	m_omapDEUIDObj.SetAt( "10901000", (CObject*)pTmp );
	
	AfxBeginThread( ModifyConfigThread, NULL );

	m_oDBData.ModifyUserPsd();	
}
//////////////////////////////////////////////////////////////////////////
//
void CModifyIPDlg::OnButtonFileMode() 
{
	CString			strPath;
	CString			strData;
	char			*pch = NULL;

	CString strFilter = "TXT Files(*.txt)|*.txt|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, 0, strFilter);
	if(dlg.DoModal() == IDOK){
		UpdateData( TRUE );		
		strPath= dlg.GetPathName();
		LoadDataFromFile( &m_strDEUIDArray, strPath );
		m_strUIDSUM.Format("%d", m_strDEUIDArray.GetSize() );
		UpdateData( FALSE );		
		m_nDEUIDPos = 0;
		m_nSendOK = 0;
		m_nSendFailed = 0;
	}
}

void CModifyIPDlg::OnStart() {

	UpdateData( TRUE );
	
	if( m_nThread > 0 ){
		SetTimer( IDC_TIME, 1000, NULL );
		for( int nCnt = 0; nCnt < m_nThread; nCnt++ ){
			AfxBeginThread( ModifyFileConfigThread, NULL );
		}
	}
	else{

		AfxMessageBox("请指定线程数");
	}
	// TODO: Add your control notification handler code here
	
}

//////////////////////////////////////////////////////////////////////////
//
void CModifyIPDlg::OnRadio_211(){
	
	UpdateData(TRUE);
	switch( m_nType ){
	case 0:		//	211.154.139.226
		m_strServerName = "211.154.139.226";
		break;
	case 1:	    //	14.17.77.103
		m_strServerName = "14.17.77.103";
		break;
	case 2:     //	121.37.61.67
		m_strServerName = "121.37.61.67";
		break;
	}
	m_strServerInfo = m_strServerName;
	UpdateData(FALSE);

	TRACE("IP:%s\r\n", m_strServerName );
}


CString CModifyIPDlg::GetDEUID( ){

	CString strUID;

	
	m_oCS.Lock();
	strUID = m_strDEUIDArray.GetAt( m_nDEUIDPos++ );
	m_oCS.Unlock();
	if( m_nDEUIDPos >= m_strDEUIDArray.GetSize() ){
		m_nDEUIDPos = 0;
	}
	
	return strUID;
}


void CModifyIPDlg::OnScan() 
{
	// TODO: Add your control notification handler code here
	
}
