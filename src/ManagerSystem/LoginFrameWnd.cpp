#include "LoginFrameWnd.h"
#include "ManagerFrameWnd.h"

CLoginFrameWnd::CLoginFrameWnd(LPCTSTR pszXMLName)
	: m_strXMLName(pszXMLName)
{

}

CLoginFrameWnd::~CLoginFrameWnd()
{

}

DUI_BEGIN_MESSAGE_MAP(CLoginFrameWnd, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_END_MESSAGE_MAP()

void CLoginFrameWnd::InitWindow()
{
	SetIcon(IDI_ICON);
	
	CComboUI* pAccountCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("accountcombo")));
	CEditUI* pAccountEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("accountedit")));

	/*CListLabelElementUI* pListElementUI1 = new CListLabelElementUI;
	pListElementUI1->SetText(_T("张三"));
	pAccountCombo->Add(pListElementUI1);

	CListLabelElementUI* pListElementUI2 = new CListLabelElementUI;
	pListElementUI2->SetText(_T("李四"));
	pAccountCombo->Add(pListElementUI2);*/

	//pAccountCombo->SelectItem(0);

	if (pAccountCombo && pAccountEdit) pAccountEdit->SetText(pAccountCombo->GetText());
	pAccountEdit->SetFocus();
}

CControlUI* CLoginFrameWnd::CreateControl(LPCTSTR pstrClassName)
{
	CDuiString strXML;
	strXML = pstrClassName;

	if (strXML.IsEmpty())
		return NULL;

	CDialogBuilder builder;

	// 这里必须传入m_PaintManager，不然子XML不能使用默认滚动条等信息。
	CControlUI* pRoot = builder.Create(pstrClassName, (UINT)0, NULL, &m_PaintManager, NULL);
	return pRoot;

}

void CLoginFrameWnd::Notify(TNotifyUI & msg)
{
	CDuiString name = msg.pSender->GetName();
	if (name == _T("accountcombo"))
	{
		if (msg.sType == _T("itemselect"))
		{
			CComboUI* pAccountCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("accountcombo")));
			CEditUI* pAccountEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("accountedit")));

			if (pAccountCombo && pAccountEdit) pAccountEdit->SetText(pAccountCombo->GetText());
			pAccountEdit->SetFocus();
		}
	}
	__super::Notify(msg);
}

LRESULT CLoginFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = __super::HandleMessage(uMsg, wParam, lParam);
	return lRes;
}

void CLoginFrameWnd::OnClick(TNotifyUI& msg)
{
	if (msg.pSender->GetName() == _T("closebtn"))
	{
		PostQuitMessage(0);
	}
	else if (msg.pSender->GetName() == _T("loginbtn"))
	{
		this->Close();
		//MessageBox(m_hWnd, _T("账号密码错误，请重新登录！"), _T("错误"), MB_OK);
		CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("./skin"));
		CManagerFrameWnd * mgrFrame = new CManagerFrameWnd(_T("ManagerFrame.xml"));
		if (mgrFrame == NULL)
			return;
		mgrFrame->Create(NULL, _T("管理系统"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
		mgrFrame->CenterWindow();
		mgrFrame->ShowModal();
		delete mgrFrame;
	}
	__super::OnClick(msg);
}

LRESULT CLoginFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if (!::IsZoomed(*this))
	{
		RECT rcSizeBox = m_PaintManager.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top)
		{
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom)
		{
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}

		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_PaintManager.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
		if (pControl && _tcsicmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcsicmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcsicmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}
	return HTCLIENT;
}

LRESULT CLoginFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (uMsg == WM_KEYDOWN) {
		if (wParam == VK_RETURN) {
			CEditUI* pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("accountedit")));
			if (pEdit->GetText().IsEmpty()) pEdit->SetFocus();
			else {
				pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("pwdedit")));
				if (pEdit->GetText().IsEmpty()) pEdit->SetFocus();
				else Close();
			}
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}

	}
	return false;
}


LPCTSTR CLoginFrameWnd::GetWindowClassName() const
{
	return _T("UILoginFrame");
}

CDuiString CLoginFrameWnd::GetSkinFile()
{
	return m_strXMLName;
}

CDuiString CLoginFrameWnd::GetSkinFolder()
{
	return CDuiString(CPaintManagerUI::GetInstancePath());
}