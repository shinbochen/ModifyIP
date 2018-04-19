
#ifndef  DBDATA_H
#define  DBDATA_H

#include "..\public\ADODB.h"
#include <list>

class  CDBData{

public:
	CDBData();
	virtual ~CDBData();
public:	
	BOOL     CDBData::IsConnect( ){ return m_bConnect; }

	BOOL	 CDBData::Connect( CString strIP, CString strDB, CString strUser, CString strPsd );
	BOOL     CDBData::DisConnect( );
public:
	BOOL     CDBData::GetAllDEUIDData(  CPtrArray &outData );
	BOOL     CDBData::GetTrackData( CPtrArray  &outData );
	BOOL     CDBData::ModifyUserPsd( void );

protected:
	CADODatabase	m_oADODB;
	BOOL			m_bConnect;	
};

#endif   //DBDATA_H