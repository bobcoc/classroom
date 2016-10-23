#include "stdafx.h"
#include "comFuns.h"
#include <shlwapi.h>

// CStringA to CStringW

CString		QaGetAppPath( void )
{
	TCHAR	tszBuf[MAX_PATH] = { '\0 '};
	GetModuleFileName( NULL, tszBuf, MAX_PATH );

	CString	tmpDir = tszBuf;
	//CString	strDir = tmpDir.Left( tmpDir.ReverseFind('\\') );

	return tmpDir;
}

ULONGLONG	QaGetFileSize( CString szFileName )
{
	CFileStatus	fStatus;

	if( CFile::GetStatus( szFileName, fStatus ) )
		return fStatus.m_size;

	return 0;
}

CString		QaFilterPamaters( CString szPamater )
{
	CString	szTmp = szPamater;

	szTmp.Replace( _T("%"), _T("%25") );
	szTmp.Replace( _T("+"), _T("%2B") );
	szTmp.Replace( _T(" "), _T("+") );
	szTmp.Replace( _T("\r\n"), _T("%0D%0A") );
	szTmp.Replace( _T("&"), _T("%26") );
	szTmp.Replace( _T("\r\n"), _T("<br>") );

	return szTmp;
}
void InitobjReq(CHttpClient& objHttpReq) {
	objHttpReq.SetInternet(_T("My date 1.0"));
	objHttpReq.SetUseUtf8(TRUE);
	objHttpReq.SetAnsiCodePage(949);
	objHttpReq.AddHeader(_T("Ryeol-Magic"), _T("My Magic Header"));
	objHttpReq.AddHeader(_T("User-Magic"), _T("User's Magic Header"));

}
CString		QaHttpPost(CHttpClient& objHttpReq )
{
	CHttpResponse *     pobjHttpRes = NULL;

	try {

		const DWORD     cbProceed = 1024;  // 1K
		int i = 0;
		do {
			i++;
		} while (!(pobjHttpRes = objHttpReq.Proceed(cbProceed)));
	}
	catch (httpclientexception & e) {
	}

	BOOL        bIsText = FALSE;
	LPCTSTR szHeader;

	// Reads the length of the stream
	DWORD       dwContSize;
	// If the length is not specified
	if (!pobjHttpRes->GetContentLength(dwContSize))
		dwContSize = 0;

	const DWORD     cbBuff = 1024 * 20000;
	BYTE *byBuff = new BYTE [cbBuff+1];
	const DWORD cbBuffsum = cbBuff * 40;
	BYTE *byBuffsum = new BYTE [cbBuffsum];
	memset(byBuffsum, 0, cbBuffsum);
	DWORD           dwRead;
	size_t          cbTotal = 0, newlen = 0;
	CString szret;
	CString strResult = _T("");
	// Reads the data stream returned by the HTTP server.
	memset(byBuff, 0, cbBuff+1);
	while (dwRead = pobjHttpRes->ReadContent(byBuff, cbBuff)) {
		byBuff[dwRead-1] = '\0';
		strncat_s((char*)byBuffsum, cbTotal, (char*)byBuff, _TRUNCATE);
		cbTotal += dwRead;
		memset(byBuff, 0, cbBuff + 1);
	}
	delete[]byBuff;
	DWORD dwFlags = 0;
	LPWSTR lpWideCharStr;

	if (!bIsText) {
		newlen = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)byBuffsum, cbTotal, NULL, 0);
		lpWideCharStr = new wchar_t[newlen + 10];
		MultiByteToWideChar(CP_UTF8, dwFlags, (LPCCH)byBuffsum, cbTotal, lpWideCharStr, newlen);
		szret = lpWideCharStr;
		strResult = szret;
	}
	else {
		strResult = byBuffsum;
	}

	delete[]byBuffsum;	
	return strResult;
}
CString GetDirectoryPath()
{
	CString strPath =_T("");
	BROWSEINFO bInfo;
	ZeroMemory(&bInfo, sizeof(bInfo));
	bInfo.hwndOwner =NULL;
	bInfo.lpszTitle = _T("请选择路径: ");
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS;   

	LPITEMIDLIST lpDlist; //用来保存返回信息的IDList
	lpDlist = SHBrowseForFolder(&bInfo) ; //显示选择对话框
	if(lpDlist != NULL)  //用户按了确定按钮
	{
		TCHAR chPath[255]; //用来存储路径的字符串
		SHGetPathFromIDList(lpDlist, chPath);//把项目标识列表转化成字符串
		strPath = chPath; //将TCHAR类型的字符串转换为CString类型的字符串
	}
	return strPath;
}
void ExecuteCmd(CString lpFilename,CString szParams)
{
	SHELLEXECUTEINFO exeInfo;
	ZeroMemory(&exeInfo, sizeof(SHELLEXECUTEINFO));
	exeInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	exeInfo.fMask = (SEE_MASK_DOENVSUBST|SEE_MASK_FLAG_DDEWAIT|0x04000000|SEE_MASK_NOCLOSEPROCESS|SEE_MASK_NO_CONSOLE);
	exeInfo.hwnd = NULL;
	exeInfo.lpVerb = _T("open");
	exeInfo.lpFile =lpFilename;
	exeInfo.lpParameters = szParams;
	exeInfo.lpDirectory = NULL;
	exeInfo.nShow = SW_HIDE;
	exeInfo.hInstApp = NULL;
	exeInfo.lpIDList = NULL;
	exeInfo.lpClass = NULL;
	exeInfo.hkeyClass = NULL;
	exeInfo.dwHotKey = NULL;
	exeInfo.hMonitor = NULL;
	exeInfo.hIcon = NULL;
	exeInfo.hProcess = NULL;

	::ShellExecuteEx(&exeInfo);

	if( exeInfo.hProcess )
	{
		::WaitForSingleObject( exeInfo.hProcess, INFINITE );
		::CloseHandle( exeInfo.hProcess );
	}
}