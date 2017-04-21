#pragma once
#ifndef LOGIN_FRAME_WND_H
#define LOGIN_FRAME_WND_H

#include "stdafx.h"

class CLoginFrameWnd : public DuiLib::WindowImplBase
{
public:
	explicit CLoginFrameWnd(LPCTSTR pszXMLName);
	virtual ~CLoginFrameWnd();
public:
	DUI_DECLARE_MESSAGE_MAP()
	virtual void InitWindow();
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
	virtual void Notify(TNotifyUI & msg);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);	
	virtual void OnClick(TNotifyUI& msg);
	virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
private:
	CDuiString		m_strXMLName;
};

#endif