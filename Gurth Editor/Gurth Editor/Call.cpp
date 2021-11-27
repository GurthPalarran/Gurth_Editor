#include "pch.h"
#include "DlgMain.h"

BOOL __stdcall Call(CString cmdline, CString key)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	DlgMain Dlg;
	Dlg.List.Cmdline = cmdline;
	Dlg.DoModal();
	return TRUE;
}