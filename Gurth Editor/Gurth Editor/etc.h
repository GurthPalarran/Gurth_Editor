#pragma once

// Classes
class UserOperation
{
public:
	CString FilePath;
	CString CSArgv;

public:
	BOOL getuseroperation(CString cmdline);

};

// Functions
BOOL TranscodingRead(CString *Content, CString FileName);
BOOL TranscodingWrite(CString Content, CString FileName);

BOOL DirectRead(CString* Content, CString FileName);

BOOL WriteGpConfig(CString gpconfigPath);
BOOL ReadGpConfig(CString gpconfigPath);

UINT TreadFunFind(LPVOID pParam);
UINT TreadFunReplace(LPVOID pParam);
UINT TreadFunPreferance(LPVOID pParam);