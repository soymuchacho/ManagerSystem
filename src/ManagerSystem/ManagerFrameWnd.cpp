#include "ManagerFrameWnd.h"

CManagerFrameWnd::CManagerFrameWnd(LPCTSTR pszXMLName)
	: m_strXMLName(pszXMLName),
	m_bFullScreenMode(FALSE)
{

}

CManagerFrameWnd::~CManagerFrameWnd()
{

}

DUI_BEGIN_MESSAGE_MAP(CManagerFrameWnd, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_END_MESSAGE_MAP()

void CManagerFrameWnd::InitWindow()
{
	// 根据分辨率自动调节窗口大小
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
	AdaptWindowSize(oMonitor.rcMonitor.right - oMonitor.rcMonitor.left);
	::GetWindowPlacement(*this, &m_OldWndPlacement);
}

CControlUI* CManagerFrameWnd::CreateControl(LPCTSTR pstrClassName)
{
	CDuiString     strXML;
	CDialogBuilder builder;

	if (_tcsicmp(pstrClassName, _T("MenuList")) == 0)
	{
		strXML = _T("MenuList.xml");
	}
	else if (_tcsicmp(pstrClassName, _T("EmployeeSearchInterface")) == 0)
	{
		strXML = _T("EmployeeSearchInterface.xml");
	}
	else if (_tcsicmp(pstrClassName, _T("OrderSearchInterface")) == 0)
	{
		strXML = _T("OrderSearchInterface.xml");
	}

	if (!strXML.IsEmpty())
	{
		CControlUI* pUI = builder.Create(strXML.GetData(), NULL, NULL, &m_PaintManager, NULL); // 这里必须传入m_PaintManager，不然子XML不能使用默认滚动条等信息。
		return pUI;
	}
	return NULL;
}

void CManagerFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabMenulist")));
		if (name == _T("Employee"))
		{
			// 人力资源
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("EmployeeSearchInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("Customer"))
		{
			// 客户管理
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("CustomerSearchInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("Order"))
		{
			// 订单管理
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("OrderSearchInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("Finance"))
		{
			// 财务管理
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("FinanceSearchInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("EmployeeSearch"))
		{
			// 员工查询
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("EmployeeSearchInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("EmployeeHired"))
		{
			// 员工入职新增
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("EmployeeHiredInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("EmployeeTurnover"))
		{
			// 员工离职
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("EmployeeTurnoverInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("CustomerSearch"))
		{
			// 客户查询
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("CustomerSearchInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("CustomerAdd"))
		{
			// 客户新增
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("CustomerAddInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("OrderSearch"))
		{
			// 订单查询
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("OrderSearchInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("OrderRepair"))
		{
			// 订单录入
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("OrderEntryInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("FinanceSearch"))
		{
			// 财务查询
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("FinanceSearchInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("FinanceReport"))
		{
			// 财务报表
			CControlUI * pInterface = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("FinanceReportInterface")));
			pControl->SelectItem(pInterface);
		}
		else if (name == _T("btnEmployeeSearch"))
		{
			// 员工搜索
			OnSearchEmployee();
		}
		else if (name == _T("btnOrderSearch"))
		{
			// 销售订单搜索
			OnSearchOrder();
		}
	}
	return __super::Notify(msg);
}

LRESULT CManagerFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = __super::HandleMessage(uMsg, wParam, lParam);
	return lRes;
}

void CManagerFrameWnd::OnClick(TNotifyUI& msg)
{
	return __super::OnClick(msg);
}

LRESULT CManagerFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

	//return __super::OnNcHitTest(uMsg, wParam, lParam, bHandled);
}

LRESULT CManagerFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return false;
}

LPCTSTR CManagerFrameWnd::GetWindowClassName() const
{
	return _T("UIManagerFrame");
}

CDuiString CManagerFrameWnd::GetSkinFile()
{
	return m_strXMLName;
}

CDuiString CManagerFrameWnd::GetSkinFolder()
{
	return CDuiString(CPaintManagerUI::GetInstancePath());
}

void CManagerFrameWnd::FullScreen(bool bFull)
{
	CControlUI* pbtnFull = m_PaintManager.FindControl(_T("btnScreenFull"));
	CControlUI* pbtnNormal = m_PaintManager.FindControl(_T("btnScreenNormal"));
	CControlUI* pUICaption = m_PaintManager.FindControl(_T("ctnCaption"));
	int iBorderX = GetSystemMetrics(SM_CXFIXEDFRAME) + GetSystemMetrics(SM_CXBORDER);
	int iBorderY = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYBORDER);

	if (pbtnFull && pbtnNormal && pUICaption)
	{
		m_bFullScreenMode = bFull;

		if (bFull)
		{
			::GetWindowPlacement(*this, &m_OldWndPlacement);

			if (::IsZoomed(*this))
			{
				::ShowWindow(*this, SW_SHOWDEFAULT);
			}

			::SetWindowPos(*this, HWND_TOPMOST, -iBorderX, -iBorderY, GetSystemMetrics(SM_CXSCREEN) + 2 * iBorderX, GetSystemMetrics(SM_CYSCREEN) + 2 * iBorderY, 0);
			ShowPlaylist(false);
		}
		else
		{
			::SetWindowPlacement(*this, &m_OldWndPlacement);
			::SetWindowPos(*this, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}

		pbtnNormal->SetVisible(bFull);
		pUICaption->SetVisible(!bFull);
		pbtnFull->SetVisible(!bFull);
	}
}

void CManagerFrameWnd::AdaptWindowSize(UINT cxScreen)
{
	int iX = 968, iY = 600;
	int iWidthList = 225, iWidthSearchEdit = 193;
	SIZE szFixSearchBtn = { 201, 0 };

	if (cxScreen <= 1024)      // 800*600  1024*768  
	{
		iX = 775;
		iY = 470;
	}
	else if (cxScreen <= 1280) // 1152*864  1280*800  1280*960  1280*1024
	{
		iX = 968;
		iY = 600;
	}
	else if (cxScreen <= 1366) // 1360*768 1366*768
	{
		iX = 1058;
		iY = 656;
		iWidthList += 21;
		iWidthSearchEdit += 21;
		szFixSearchBtn.cx += 21;
	}
	else                      // 1440*900
	{
		iX = 1224;
		iY = 760;
		iWidthList += 66;
		iWidthSearchEdit += 66;
		szFixSearchBtn.cx += 66;
	}

	CControlUI *pctnPlaylist = m_PaintManager.FindControl(_T("ctnPlaylist"));
	CControlUI *peditSearch = m_PaintManager.FindControl(_T("editSearch"));
	CControlUI *pbtnSearch = m_PaintManager.FindControl(_T("btnSearch"));
	if (pctnPlaylist && peditSearch && pbtnSearch)
	{
		pctnPlaylist->SetFixedWidth(iWidthList);
		peditSearch->SetFixedWidth(iWidthSearchEdit);
		pbtnSearch->SetFixedXY(szFixSearchBtn);
	}

	::SetWindowPos(m_PaintManager.GetPaintWindow(), NULL, 0, 0, iX, iY, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOACTIVATE);
	CenterWindow();
}

void CManagerFrameWnd::ShowPlaylist(bool bShow)
{
	CControlUI *pctnPlaylist = m_PaintManager.FindControl(_T("ctnPlaylist"));
	CControlUI *pbtnHide = m_PaintManager.FindControl(_T("btnPlaylistHide"));
	CControlUI *pbtnShow = m_PaintManager.FindControl(_T("btnPlaylistShow"));

	if (pctnPlaylist && pbtnHide && pbtnShow)
	{
		pctnPlaylist->SetVisible(bShow);
		pbtnHide->SetVisible(bShow);
		pbtnShow->SetVisible(!bShow);
	}
}

void CManagerFrameWnd::OnSearchEmployee()							// 员工搜索
{
	CListUI * plistEmployee = static_cast<CListUI*>(m_PaintManager.FindControl(_T("employeelist")));
	CDialogBuilder builder;
	CListContainerElementUIEx *plist_element = static_cast<CListContainerElementUIEx*>(builder.Create(_T("listEmployeeElement.xml"), 0, NULL, &m_PaintManager, NULL));
	if (plistEmployee && plist_element)
	{
		plist_element->SetSubControlText(_T("employee_number"), _T("0911122110"));
		plist_element->SetSubControlText(_T("employee_name"), _T("小明"));
		CComboUI * pComboSex = static_cast<CComboUI*>(plist_element->FindSubControl(_T("employee_sex")));
		if (pComboSex)
		{
			pComboSex->SelectItem(1);
		}
		plist_element->SetSubControlText(_T("employee_age"), _T("28"));
		CDateTimeUI * pDatetime = static_cast<CDateTimeUI*>(plist_element->FindSubControl(_T("employee_date")));
		if (pDatetime)
		{
			SYSTEMTIME systime;
			memset(&systime, 0, sizeof(SYSTEMTIME));
			systime.wYear = 2017;
			systime.wMonth = 2;
			systime.wDay = 22;
			pDatetime->SetTime(&systime);
			pDatetime->SetText(_T("2017-02-22"));
		}

		CComboUI * pCombopos = static_cast<CComboUI*>(plist_element->FindSubControl(_T("employee_position")));
		if (pCombopos)
		{
			pCombopos->SelectItem(2);
		}
		plist_element->SetSubControlText(_T("employee_permissions"), _T("一级"));
		plistEmployee->Add(plist_element);
	}
}

void CManagerFrameWnd::OnSearchOrder()
{

}