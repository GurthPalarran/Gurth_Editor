#include "stdafx.h"
#include "RegistKey.h"
#include "Check.h"
#include <mysql.h>
#include <cstring>
#include <string>
#include "ExtraLib/cppmd5/md5.h"

using namespace std;

string Key_md5("d958aabb7153faa5172ed01f10aa13b6");

BOOL CheckTheKey()
{
	DWORD dwNameLen;
	char pcName[MAX_PATH] = {0};
	char userName[MAX_PATH] = {0};
	dwNameLen = MAX_PATH;

	if (!GetComputerNameA(pcName, &dwNameLen))
	{
		AfxMessageBox(L"Cannot get pc name.");
		return FALSE;
	}
	if (!GetUserNameA(userName, &dwNameLen))
	{
		AfxMessageBox(L"Cannot get user name.");
	}

	MD5 pcmd5(pcName);
	string md5tmp = pcmd5.md5();
	const char* epcname = md5tmp.c_str();

	MYSQL* conn;

	conn = mysql_init(0);

	if (!mysql_real_connect(conn, "localhost", "palarran", "l1111111", "db_editor", 3306, NULL, 0))
	{
		
		const char* err = mysql_error(conn);
		CString Tips(err);
		AfxMessageBox(L"Failed to connect to the database.\nBescuse:\n" + Tips);
		return FALSE;
	}
	else
	{
		AfxMessageBox(L"Successfully connect to the database.");
		int res = mysql_query(conn, "select name,name_md5 from user_info");
		if (!res)
		{
			MYSQL_RES* result;
			MYSQL_ROW sql_row;
			result = mysql_store_result(conn);
			if (result)
			{
				while (1)
				{
					sql_row = mysql_fetch_row(result);
					if (sql_row == NULL) break;
					if (StrCmpCA(sql_row[0], userName) == 0 &&
						StrCmpCA(sql_row[1], epcname) == 0)
						return TRUE;
				}
			}
		}
		else
		{
			AfxMessageBox(L"query sql failed!");
			mysql_close(conn);
			return FALSE;
		}
	}

	if (!PreCheck())
	{
		RegistKey Dlg;
		int nSelect = Dlg.DoModal();
		if (nSelect == IDOK)
		{
			USES_CONVERSION;
			CString CStmp = Dlg.Key_read;
			MD5 keymd5(T2A(Dlg.Key_read));
			string stmp = keymd5.md5();
			if (stmp == Key_md5)
			{
				char query_buff[200] = { 0 };
				sprintf_s(query_buff, 200, "insert into user_info (name,  name_md5, submission_time) values(\"%s\", \"%s\", NOW());", userName, epcname);
				int rt = mysql_real_query(conn, query_buff, strlen(query_buff));
				if (rt)
				{
					CString CStmp_err(mysql_error(conn));
					AfxMessageBox(CStmp_err);
					mysql_close(conn);
					return FALSE;
				}

				mysql_close(conn);
				return TRUE;
			}
		}
	}
/*		
#ifdef DEBUG
		//CString Result = MD5_Transcode(Dlg.Key_read);
#endif // DEBUG

		if (nSelect == IDOK && 
#ifdef DEBUG
			Result
#endif // DEBUG
#ifndef DEBUG
			MD5_Transcode(Dlg.Key_read)
#endif // !DEBUG			
			== Key_md5)
		{
			return TRUE;
		}
	}
#ifdef DEBUG
	return TRUE;
#endif // DEBUG
*/
	return FALSE;
}

BOOL PreCheck()
{
	return FALSE;
}
