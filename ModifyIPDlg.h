// ModifyIPDlg.h : header file
//

#if !defined(AFX_MODIFYIPDLG_H__459B7714_0A09_4411_B636_7441899AF34A__INCLUDED_)
#define AFX_MODIFYIPDLG_H__459B7714_0A09_4411_B636_7441899AF34A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <list>
#include "resource.h"

#define	  MODIFY_IP					0
#define	  MODIFY_CBMODE				1


#define  SERVER_GPS_OLD_211		    1
#define  SERVER_GPS_LAO_14		    0
#define  SERVER_GPS_NEW_CLIENT      0
#define  SERVER_GPS_SUKE			0

//////////////////////////////////////////////////////////////////////////
//
#if( SERVER_GPS_OLD_211 )
	#define    TEXT_SERVER_NAME		"211.154.139.226"
	#define    TEXT_DATABASE_NAME   "MapTrack_DB"
	#define    TEXT_USER_NAME		"sa"
	// @track-earth3130
    // track-earth1012
	#define    TEXT_USER_PSD		"@track-earth3130"

	#define    REMOTE_IP			"211.154.139.226"
#endif 
//////////////////////////////////////////////////////////////////////////
//
#if( SERVER_GPS_LAO_14 )
	#define    TEXT_SERVER_NAME		"14.17.77.103"
	#define    TEXT_DATABASE_NAME   "MapTrack_DB"
	#define    TEXT_USER_NAME		"sa"
	#define    TEXT_USER_PSD		"gpslao.com-31301"

	#define    REMOTE_IP			"14.17.77.103"
#endif
//////////////////////////////////////////////////////////////////////////
//
#if( SERVER_GPS_NEW_CLIENT )
	#define    TEXT_SERVER_NAME		"62.61.172.71"
	#define    TEXT_DATABASE_NAME   "MapTrack_DB"
	#define    TEXT_USER_NAME		"sa"
	#define    TEXT_USER_PSD		"gpslao.com-31301"

	#define    REMOTE_IP			"62.61.172.71"
#endif 
//////////////////////////////////////////////////////////////////////////
//
#if ( SERVER_GPS_SUKE )
	#define    TEXT_SERVER_NAME		"121.37.61.67"
	#define    TEXT_DATABASE_NAME   "MapTrack_DB"
	#define    TEXT_USER_NAME		"sa"
	#define    TEXT_USER_PSD		"ZHouFe8512Samuel"

	#define    REMOTE_IP			"121.37.61.67"
#endif 

#define    MT_CONFIG_IP				18
	
#include   "DBData.h"



/////////////////////////////////////////////////////////////////////////////
// CModifyIPDlg dialog

class CModifyIPDlg : public CDialog
{
// Construction
public:
	CModifyIPDlg(CWnd* pParent = NULL);	// standard constructor
public:
	int							  m_nCurPos;
	CDBData						  m_oDBData;
	CPtrArray		   		      m_oPtrCarDEUID;
	CMapStringToOb				  m_omapDEUIDObj;	
	CStringArray				  m_strDEUIDArray;
	int							  m_nDEUIDPos;
	double						  m_nSendOK;
	double						  m_nSendFailed;
	CString						  m_strServerName;
	
	static  CCriticalSection	  m_oCS;
	
public:
	void						 SaveConfigOK( CString  strDEUID,  CTime   oTime );
	void						 ComparisonTrackData();
	void						 GetServerTrackData();
	CString						 CModifyIPDlg::GetDEUID( );
	
	void						 AddHelpInfo( CString strInfo ){ m_strInfo = strInfo;}

public:
	BOOL						 ConnectDatabase();
	unsigned char				 PL_CountVerifySum(unsigned char *lpDataBuf, int nDataLen);
	unsigned char 				 PL_ComposeHSData( unsigned char	*pDest );


	
	
	void	IncSendOK(){ m_nSendOK++;}
	void	IncSendFailed(){ m_nSendFailed++;};

// Dialog Data
	//{{AFX_DATA(CModifyIPDlg)
	enum { IDD = IDD_MODIFYIP_DIALOG };
	int		m_nType;
	CString	m_strInfo;
	DWORD	m_nNGCnt;
	DWORD	m_nOKCnt;
	CString	m_strUIDSUM;
	int		m_nThread;
	CString	m_strServerInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyIPDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CModifyIPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonModifyServer();
	afx_msg void OnSaveData();
	afx_msg void OnButtonModify();
	afx_msg void OnButtonFileMode();
	afx_msg void OnRadio_211();
	afx_msg void OnStart();
	afx_msg void OnScan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYIPDLG_H__459B7714_0A09_4411_B636_7441899AF34A__INCLUDED_)
