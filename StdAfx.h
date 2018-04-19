// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F68874FD_B266_4426_B2B0_F0041F7AA182__INCLUDED_)
#define AFX_STDAFX_H__F68874FD_B266_4426_B2B0_F0041F7AA182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <mmsystem.h>
#include "..\public\Structs.h"
#include <math.h>

#include <afxtempl.h>		// MFC template classes
#include <locale.h>			// MFC local

#include <afxmt.h>

typedef char	STDEUID[8+1];
typedef char STTELNUM[20+1];

/////////////////////////////////////////////////
//
typedef struct _STCARDEUID{

	STDEUID		m_nDEUID;
	STTELNUM    m_nCarLicense;
}STCARDEUID,*PSTCARDEUID;

//////////////////////////////////////////////////////////////////////////
//
typedef struct  _STDEUIDTIME 
{
	unsigned char	m_nNumber;
	STDEUID			m_nDEUID;
	STTELNUM		m_nCarLicense;
	CTime			m_oTime;
}STDEUIDTIME,*PSTDEUIDTIME;


#define     _NEED_CLPROTOCOL

/////////////////////////////////////
//
enum{
	WM_SOCKET_CLOSE  = WM_USER+100,
	WM_SOCKET_SEND_ERROR,
	WM_SOCKET_CONNECT,
	TIMER_SETUP_IP
};


// 可拷贝数组模板定义
template <class TYPE, class ARG_TYPE>
class CArrayExt : public CArray<TYPE, ARG_TYPE>
{
public:
	CArrayExt()		// 缺省构造函数
	{
		m_pData = NULL;
		m_nSize = m_nMaxSize = m_nGrowBy = 0;
	}
	CArrayExt(CArrayExt<TYPE, ARG_TYPE>& a)		// 拷贝构造函数
	{
		SetSize(a.GetSize());
		for (int i=0; i<a.GetSize(); i++)
			ElementAt(i) = a[i];
	}
	const CArrayExt<TYPE, ARG_TYPE>& operator=(const CArrayExt<TYPE, ARG_TYPE>& a)	//重载赋值运算符
	{
		if (m_pData!=a.m_pData)
		{
			SetSize(a.GetSize());
			for (int i=0; i<a.GetSize(); i++)
				ElementAt(i) = a[i];
		}
		return *this;
	}
	int AddMany(TYPE* pAddElements, int size)
	{
		int nOldSize = m_nSize;
		SetSize(m_nSize + size);
		CopyElements<TYPE>(m_pData + nOldSize, pAddElements, size);
		return nOldSize;
	}
};

typedef CArrayExt<BYTE, BYTE>		CAByte;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F68874FD_B266_4426_B2B0_F0041F7AA182__INCLUDED_)
