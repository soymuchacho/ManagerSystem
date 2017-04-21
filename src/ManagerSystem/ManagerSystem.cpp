#include "stdafx.h"
#include "LoginFrameWnd.h"
// ³ÌÐòÈë¿Ú
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	//HRESULT Hr = ::CoInitialize(NULL);
	//if (FAILED(Hr)) return 0;

	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("./skin"));

	CLoginFrameWnd* pFrame = new CLoginFrameWnd(_T("login.xml"));
	if (pFrame == NULL) return 0;
	
	pFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
	pFrame->CenterWindow();
	pFrame->ShowModal();

	delete pFrame;
	//::CoUninitialize();
	return 0;
}

