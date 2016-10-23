#ifndef __QaFuns_H__
#define __QaFuns_H__
#include "httpclient\RyeolHttpClient.h"
using namespace Ryeol;
CString			QaMakeMd5( CString strSrc );

CString			QaGetAppPath( void );
ULONGLONG		QaGetFileSize( CString FileName );
CString			QaFilterPamaters( CString szPamater );
void InitobjReq(CHttpClient& objHttpReq);
CString			QaHttpPost(CHttpClient& objHttpReq);
CString GetDirectoryPath();
void ExecuteCmd(CString lpFilename,CString szParams);
CString GetKemuStr(int SoftChannelID);//根据softchannelID取得科目名称
CString GetKemuStr(CString strSoftChannelID);//根据softchannelID取得科目名称

#endif//__QaFuns_H__
