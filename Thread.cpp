//////////////////////////////////////////////////////////////////////////
// gpslao.com
//
//
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Thread.h"

#include "ModifyIPDlg.h"
#include "..\public\ProtocolData.h"

///////////////////////////////////////////////////////
//
UINT	StartSocketThread( LPVOID lParam ){

	int				 nTmpCur = 0;
	CSocket          oSocket;
	PSTCARDEUID      pStTmp = NULL;
	CCLProtocolData  oProtocol;
	CData			 oData;
	CString			 strData;
	byte			 IP1,IP2,IP3,IP4;
	int              nPort;
	CModifyIPDlg	 *pDlg = (CModifyIPDlg*)AfxGetApp()->m_pMainWnd;
	
	CString			 strKey;
	POSITION		 pos;	
	PSTDEUIDTIME	 pTmp = NULL;

	while( 1 ){

		try{
			if( pDlg->m_omapDEUIDObj.GetCount() > 0 ){
					
				oSocket.Create();
				//9990
				if( oSocket.Connect( pDlg->m_strServerName/*REMOTE_IP*/, 9990  ) ){				
				
					pos = pDlg->m_omapDEUIDObj.GetStartPosition();
					while ( pos ){
						
						pDlg->m_omapDEUIDObj.GetNextAssoc( pos, strKey, (CObject*&)pTmp );					
	// 					if( memcmp( pTmp->m_nDEUID, "10901000", 8)== 0 ){
	// 						TRACE("DEUID相同\r\n");
	// 						continue;
	// 					}
	// 					else{
	// 						TRACE("SN: %s  Car:%s \r\n", pTmp->m_nDEUID, pTmp->m_oTime.Format("%Y-%m-%d %H:%M:%S") );	
	// 					}
					#if( MODIFY_IP )
						IP1 =rand()%250+1;
						IP2 =rand()%250+1;
						IP3 =rand()%250+1;
						IP4 =rand()%250+1;
						nPort = rand()%10000+1;
						strData.Format("%03d.%03d.%03d.%03d", IP1,IP2,IP3,IP4 );
						oProtocol.ComposeCtrlTESetupServer( 1, pTmp->m_nDEUID, 1, strData, nPort );
					#else
						oProtocol.ComposeCtrlTESetupCallback( 1, 
															  pTmp->m_nDEUID, 
															  1,
															  5,
															  6000 );
					#endif 
						while ( oProtocol.GetTLSendData( &oData ) ){				
							oSocket.Send( oData.GetDataBuf(),	oData.GetDataLen() );
						}
						Sleep(200);
					}	
				}
				else{
					//9900
					if( oSocket.Connect( pDlg->m_strServerName/*REMOTE_IP*/, 9900  ) ){				
						
						pos = pDlg->m_omapDEUIDObj.GetStartPosition();
						while ( pos ){
							
							pDlg->m_omapDEUIDObj.GetNextAssoc( pos, strKey, (CObject*&)pTmp );					
	// 						if( memcmp( pTmp->m_nDEUID, "10901000", 8) == 0 ){
	// 							TRACE("DEUID相同\r\n");
	// 							continue;
	// 						}
	// 						else{
	// 							TRACE("SN: %s  Car:%s \r\n", pTmp->m_nDEUID, pTmp->m_oTime.Format("%Y-%m-%d %H:%M:%S") );	
	// 						}
						#if( MODIFY_IP )
							IP1 =rand()%250+1;
							IP2 =rand()%250+1;
							IP3 =rand()%250+1;
							IP4 =rand()%250+1;
							nPort = rand()%10000+1;
							strData.Format("%03d.%03d.%03d.%03d", IP1,IP2,IP3,IP4 );
							oProtocol.ComposeCtrlTESetupServer( 1, pTmp->m_nDEUID, 1, strData, nPort );
						#else
							oProtocol.ComposeCtrlTESetupCallback( 1, 
																  pTmp->m_nDEUID, 
																  1,
																  5,
																  2400 );

							oProtocol.ComposeCtrlTESetFenceAlarm(1,pTmp->m_nDEUID,1,1,1,-143.085938,9.4490619,-157.851563,-0.351559);


						#endif 
							while ( oProtocol.GetTLSendData( &oData ) ){				
								oSocket.Send( oData.GetDataBuf(),	oData.GetDataLen() );
							}
							Sleep(200);
						}
					}
					else{
						TRACE("Socket Error!\r\n");
					}
				}
				oSocket.Close();			
			}
		}
		catch(...){
			Sleep(1000);
		}
	}
	return  0;
}
//////////////////////////////////////////////////////////////////////////
//  修改配置文件
UINT   ModifyConfigThread( LPVOID lParam ){


	int				 nTmpCur = 0;
	CSocket          oSocket;
	PSTCARDEUID      pStTmp = NULL;
	CCLProtocolData  oProtocol;
	CData			 oData;
	CString			 strData;
	byte			 IP1,IP2,IP3,IP4;
	int              nPort;
	CModifyIPDlg	 *pDlg = (CModifyIPDlg*)AfxGetApp()->m_pMainWnd;
	unsigned char    nMode = 0;

	CString			 strKey;
	POSITION		 pos;	
	PSTDEUIDTIME	 pTmp = NULL;
	
	while( 1 ){
		try{
			if( pDlg->m_omapDEUIDObj.GetCount() > 0 ){
				
				oSocket.Create();
				//9990
				if( oSocket.Connect( pDlg->m_strServerName/*REMOTE_IP*/, 9990  ) ){				
								
					pos = pDlg->m_omapDEUIDObj.GetStartPosition();
					while ( pos ){
						
						pDlg->m_omapDEUIDObj.GetNextAssoc( pos, strKey, (CObject*&)pTmp );	
						//nMode = rand()%7;
	// 					if( memcmp( pTmp->m_nDEUID, "10901000", 8) == 0 ){
	// 						TRACE("DEUID相同\r\n");
	// 						continue;
	// 					}
						for( int nMode = 7; nMode < 8; nMode++ ){
							TRACE("SN: %s  Car:%s mode:%d\r\n", pTmp->m_nDEUID, pTmp->m_oTime.Format("%Y-%m-%d %H:%M:%S"),nMode );	
							switch( nMode ){
							case 0: // 停车报警
								oProtocol.ComposeCtrlTEParkingAlarm( 1, pTmp->m_nDEUID, 1, 1 );
								break;
							case 1:// 设置围栏						
								oProtocol.ComposeCtrlTESetFenceAlarm(1,pTmp->m_nDEUID,1,1,1,-143.085938,9.4490619,-157.851563,-0.351559);
								break;
							case 2:// 设置超速报警							
								oProtocol.ComposeCtrlTEAlarmEnable( 1, pTmp->m_nDEUID, 1, 0xFFFFFF );
								break;
							case 3:// 设置超速报警							
								oProtocol.ComposeCtrlTEOverSpeedAlarm(1, pTmp->m_nDEUID, 1, 22 );
								break;
							case 4:// 设置非法开门							
								oProtocol.ComposeCtrlTEIllOpenDoorAlarm(1, pTmp->m_nDEUID, 1, 2 );
								break;
							case 5: // 疲劳驾驶设置							
								oProtocol.ComposeCtrlTETiredDriveAlarm(1, pTmp->m_nDEUID, 1, 2 );
								break;
							case 6: 	// 设置工作模式
								oProtocol.ComposeCtrlTESetupCallback( 1, pTmp->m_nDEUID, 1, 5, 2400 );
								break;
							case 7:	// IP地址
								IP1 =rand()%250+1;
								IP2 =rand()%250+1;
								IP3 =rand()%250+1;
								IP4 =rand()%250+1;
								nPort = rand()%10000+1;
								strData.Format("%03d.%03d.%03d.%03d", IP1,IP2,IP3,IP4 );
								oProtocol.ComposeCtrlTESetupServer( 1, pTmp->m_nDEUID, 1, strData, nPort );
								break;
							}

							while ( oProtocol.GetTLSendData( &oData ) ){				
								oSocket.Send( oData.GetDataBuf(),	oData.GetDataLen() );
							}
							Sleep(200);
						}
					}	
				}
				else{
					//9900
					if( oSocket.Connect( pDlg->m_strServerName/*REMOTE_IP*/, 9900  ) ){				
					
						pos = pDlg->m_omapDEUIDObj.GetStartPosition();
						while ( pos ){
							
							pDlg->m_omapDEUIDObj.GetNextAssoc( pos, strKey, (CObject*&)pTmp );					
	// 						if( memcmp( pTmp->m_nDEUID, "10901000", 8) == 0 ){
	// 							TRACE("DEUID相同\r\n");
	// 							continue;
	// 						}
							
							for( int nMode = 7; nMode < 8; nMode++ ){
								TRACE("SN: %s  Car:%s mode:%d\r\n", pTmp->m_nDEUID, pTmp->m_oTime.Format("%Y-%m-%d %H:%M:%S"),nMode );	
								switch( nMode ){
								case 0: // 停车报警
									oProtocol.ComposeCtrlTEParkingAlarm( 1, pTmp->m_nDEUID, 1, 1 );
									break;
								case 1:// 设置围栏						
									oProtocol.ComposeCtrlTESetFenceAlarm(1,pTmp->m_nDEUID,1,1,1,-143.085938,9.4490619,-157.851563,-0.351559);
									break;
								case 2:// 设置超速报警							
									oProtocol.ComposeCtrlTEAlarmEnable( 1, pTmp->m_nDEUID, 1, 0xFFFFFF );
									break;
								case 3:// 设置超速报警							
									oProtocol.ComposeCtrlTEOverSpeedAlarm(1, pTmp->m_nDEUID, 1, 22 );
									break;
								case 4:// 设置非法开门							
									oProtocol.ComposeCtrlTEIllOpenDoorAlarm(1, pTmp->m_nDEUID, 1, 2 );
									break;
								case 5: // 疲劳驾驶设置							
									oProtocol.ComposeCtrlTETiredDriveAlarm(1, pTmp->m_nDEUID, 1, 2 );
									break;
								case 6: 	// 设置工作模式
									oProtocol.ComposeCtrlTESetupCallback( 1, pTmp->m_nDEUID, 1, 5, 2400 );
									break;
								case 7:	// IP地址
									IP1 =rand()%250+1;
									IP2 =rand()%250+1;
									IP3 =rand()%250+1;
									IP4 =rand()%250+1;
									nPort = rand()%10000+1;
									strData.Format("%03d.%03d.%03d.%03d", IP1,IP2,IP3,IP4 );
									oProtocol.ComposeCtrlTESetupServer( 1, pTmp->m_nDEUID, 1, strData, nPort );
									break;
								}
								
								while ( oProtocol.GetTLSendData( &oData ) ){				
									oSocket.Send( oData.GetDataBuf(),	oData.GetDataLen() );
								}
								Sleep(200);
							}
						}
					}
					else{
						TRACE("Socket Error!\r\n");
					}
				}
				oSocket.Close();			
			}
		}
		catch(...){
			Sleep(1000);
		}
		Sleep(1000);
	}
	return  0;
}
//////////////////////////////////////////////////////////////////////////
//  修改配置文件
UINT   ModifyFileConfigThread( LPVOID lParam ){

	CSocket          oSocket;
	CCLProtocolData  oProtocol;
	CData			 oData;
	CModifyIPDlg	 *pDlg = (CModifyIPDlg*)AfxGetApp()->m_pMainWnd;
	unsigned char    nMode = 0;

	CString			 strDEUID;
	CString			 strData;
	int				 nNumber = 0;
	int				 nPos = 0;
	int				 nRecordPos = 0;
	int				 nCurPos = 0;	
	byte			 IP1,IP2,IP3,IP4;
	int              nPort;
	int				 nSend = 0;
	BOOL			 bSend = TRUE;
	BOOL			 bConnect;

	
	
	nCurPos = pDlg->m_nCurPos++;

	
	Sleep( 1000 );
	while( 1 ){	
		try{
			oSocket.Create();
			bConnect = FALSE;

			
		//	if( oSocket.Connect( "203.86.9.28", 1232  ) ){
		//		bConnect = TRUE;
		///	}


			if( oSocket.Connect( pDlg->m_strServerName, 9900  ) ){
				bConnect = TRUE;
			}
			else if( oSocket.Connect( pDlg->m_strServerName, 9990  ) ){
				bConnect = TRUE;
			}
		//	else if( oSocket.Connect( pDlg->m_strServerName, 9090  ) ){
		//		bConnect = TRUE;
		//	}
			if( bConnect == TRUE ){
				bSend = TRUE;
				while( bSend){
					strDEUID = pDlg->GetDEUID( );
					// 一次最好只发一条指令.终端有可能不能识别多项指令
					//for( int nMode = 7; nMode < 8; nMode++ ){
					nMode = 7;
						TRACE("SN: %s \t mode:%d Thread:%d\r\n", strDEUID, nMode, nCurPos );	
						switch( nMode ){
						case 0:// 停车报警		
							oProtocol.ComposeCtrlTEParkingAlarm( 1, strDEUID, 1, 1 );
							break;
						case 1:// 设置围栏						
							oProtocol.ComposeCtrlTESetFenceAlarm(1,strDEUID,1,1,1,-143.085938,9.4490619,-157.851563,-0.351559);
							break;
						case 2:// 设置报警开关							
							oProtocol.ComposeCtrlTEAlarmEnable( 1, strDEUID, 1, 0xFFFFFF );
							break;
						case 3:// 设置超速报警							
							oProtocol.ComposeCtrlTEOverSpeedAlarm(1, strDEUID, 1, 30 );
							break;
						case 4:// 设置非法开门							
							oProtocol.ComposeCtrlTEIllOpenDoorAlarm(1, strDEUID, 1, 2 );
							break;
						case 5: // 疲劳驾驶设置							
							oProtocol.ComposeCtrlTETiredDriveAlarm(1, strDEUID, 1, 2 );
							break;
						case 6: // 设置工作模式
							oProtocol.ComposeCtrlTESetupCallback( 1, strDEUID, 1, 5, 2400 );
							break;
						case 7:	// IP地址
							IP1 =rand()%250+1;
							IP2 =rand()%250+1;
							IP3 =rand()%250+1;
							IP4 =rand()%250+1;
							nPort = rand()%10000+1;
							strData.Format("%03d.%03d.%03d.%03d", IP1,IP2,IP3,IP4 );
							oProtocol.ComposeCtrlTESetupServer( 1, strDEUID, 1, strData, nPort );
							break;
						}
					//}
					while ( oProtocol.GetTLSendData( &oData ) && bSend ){
						nSend = oSocket.Send( oData.GetDataBuf(),	oData.GetDataLen() );
						if( nSend == SOCKET_ERROR ){
							bSend = FALSE;
						}
					}
					if( bSend ){
						pDlg->IncSendOK();
						strData.Format("线程%d:%s Send OK", nCurPos, strDEUID );
					}
					else{
						pDlg->IncSendFailed();
						strData.Format("线程%d:%s Send Fail", nCurPos, strDEUID );
					}
					pDlg->AddHelpInfo( strData );
					Sleep(1000);
				}
			}	
			else{
				strData="Connect Failed";
				pDlg->AddHelpInfo( strData );
			}
		}
		catch(...){
		}
		try{
			oSocket.Close();
		}
		catch(...){

		}
		Sleep(1000);
	}
	return  0;
}
//////////////////////////////////////////////////////////////////
//
UINT   ConfigSocketThread( LPVOID lParam ){

	unsigned char    nBuf[80];
	unsigned char    nLen = 0;
	CSocket          oSocket;
	CModifyIPDlg	 *pDlg = (CModifyIPDlg*)AfxGetApp()->m_pMainWnd;

	memset( nBuf, 0x00, 80 );
	oSocket.Create();
	if( oSocket.Connect( REMOTE_IP, 8868  ) ){
		
		nLen = pDlg->PL_ComposeHSData( nBuf );
		oSocket.Send( nBuf,	nLen );
	}
	oSocket.Close();

	return 0;
}