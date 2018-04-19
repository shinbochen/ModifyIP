
#include "StdAfx.h"
#include "DBData.h"
#include <stdlib.h>
#include "..\public\Data.h"
#include "..\public\Encrypt.h"



//////////////////////////////////////////////////////////////////////////
//
CDBData::CDBData(){

	m_bConnect = FALSE;	
}
//////////////////////////////////////////////////////////////////////////
//
CDBData::~CDBData(){
	
}
//////////////////////////////////////////////////////////////////////////
//
BOOL	CDBData::Connect( CString strIP, CString strDB, CString strUser, CString strPsd ){
	
	m_bConnect = m_oADODB.OpenDatabase( strUser,  strPsd, strDB, strIP );
	
	return m_bConnect;
}
//////////////////////////////////////////////////////////////////////////
//
BOOL	CDBData::DisConnect(){

	
	BOOL		bResult = TRUE;

	m_oADODB.CloseDatabase();

	return bResult;
}
//////////////////////////////////////////////////////////////////////////
// 修改自动
BOOL   CDBData::ModifyUserPsd( void ){

	BOOL			bResult = FALSE;
	unsigned char   nCh;
	CString			strSQL;
	_RecordsetPtr   oRecordset = NULL;
	STUSER			stUser;
	CString			strPsd;
	int				nLen = 0;
	int             nPos = 0;
	CString			strEncrypt,strDecrypt;
	try{

		strSQL.Format("select * from table_user");
		oRecordset = m_oADODB.ExecuteSQL( strSQL );
		if( oRecordset != NULL ){
			while( !oRecordset->adoEOF ){
				
				memset( stUser, 0x00, sizeof(STUSER) );
				m_oADODB.GetValueByFiledName( oRecordset, "ur_vchr_user", stUser , sizeof(STUSER)-1 );
				m_oADODB.GetValueByFiledName( oRecordset, "ur_vchr_psd",  strEncrypt ); 
				// 解密
				strDecrypt = DecryptPassword( strEncrypt );
				TRACE("User:%s\tpsd:%s", stUser, strDecrypt );
				nCh = rand()%55+1;
				if( (nCh >= 0 ) && (nCh < 10) ){
					 
					nCh += 0x30;
				}
				else if( (nCh >= 10 ) && (nCh <= 36) ){
						
					nCh = nCh-9+65;
				}
				else if( (nCh >= 37 ) && (nCh <= 58) ){
					nCh = nCh-36+97;
				}
				nLen = strDecrypt.GetLength();
				if( nLen <= 0 ){
					strDecrypt.Format("%s", stUser );
					nLen = strDecrypt.GetLength();
				}
				nPos = rand()%nLen;
				strDecrypt.Insert( nPos, nCh );
				strEncrypt = EncryptPassword( strDecrypt );

				strSQL.Format("update table_user  set ur_vchr_psd ='%s' where ur_vchr_user = '%s' ", strEncrypt, stUser  );

				m_oADODB.ExecuteSQL( strSQL );

				bResult =TRUE;
				oRecordset->MoveNext();
			}
		}
	}
	catch (...){
		TRACE("Modify User Psd Error.\r\n");
	}	
	if ( (oRecordset != NULL) &&
		(oRecordset->GetState() != adStateClosed) ){
		oRecordset->Close();
	}
	return  bResult;
}
//////////////////////////////////////////////////////////////////////////
//	获取最敌的GPS数据
BOOL   CDBData::GetTrackData( CPtrArray  &outData ){

	BOOL			bResult = FALSE;
	CString			strSQL;
	_RecordsetPtr   oRecordset = NULL;
	PSTDEUIDTIME     pTmp = NULL;

	try{
		strSQL.Format( "select top 50 * from table_track order by tk_int_utc DESC" );
		oRecordset = m_oADODB.ExecuteSQL( strSQL );
		if( oRecordset != NULL ){
			while( !oRecordset->adoEOF ){

				pTmp = new STDEUIDTIME();					
				memset( pTmp, 0x00, sizeof(STDEUIDTIME));				
				m_oADODB.GetValueByFiledName( oRecordset, "tk_vchr_deuid", pTmp->m_nDEUID, sizeof(STDEUID)-1 );
				m_oADODB.GetValueByFiledName( oRecordset, "tk_int_utc", (int*)&pTmp->m_oTime );

				outData.Add( pTmp );
				bResult =TRUE;
				oRecordset->MoveNext();
			}
		}
	}
	catch (...){
		TRACE("GetTrackData\n");
	}
	
	if ( (oRecordset != NULL) &&
		(oRecordset->GetState() != adStateClosed) ){
		oRecordset->Close();
	}
	return  bResult;
}
//////////////////////////////////////////////////////////////////////////
//
BOOL   CDBData::GetAllDEUIDData( CPtrArray &outData ){	
	
	BOOL			bResult = FALSE;
	CString			strSQL;
	PSTCARDEUID     pTmp = NULL;
	_RecordsetPtr   oRecordset = NULL;
	
	try{

		strSQL.Format("select * from table_device_data");
		oRecordset = m_oADODB.ExecuteSQL( strSQL );
		if ( oRecordset != NULL ){
			while ( !oRecordset->adoEOF ){
				
				pTmp = new STCARDEUID();					
				memset( pTmp, 0x00, sizeof(STCARDEUID));
				m_oADODB.GetValueByFiledName( oRecordset,  "cr_vchr_teuid"/*"CR_VCHR_DEUID"*/,   pTmp->m_nDEUID, sizeof(STDEUID)-1 );	
				m_oADODB.GetValueByFiledName( oRecordset, "CR_VCHR_LICENSE",   pTmp->m_nCarLicense, sizeof(STTELNUM)-1 );

				outData.Add(pTmp );
				bResult =TRUE;
				oRecordset->MoveNext();
			}
		}
	}
	catch (...){
		TRACE("GetAllDEUIDData\n");
	}
	if ( (oRecordset != NULL) &&
		(oRecordset->GetState() != adStateClosed) ){
		oRecordset->Close();
	}
	return  bResult;
}