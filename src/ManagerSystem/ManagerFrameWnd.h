#pragma once
#ifndef MANAGER_FRAME_WND_H
#define MANAGER_FRAME_WND_H

#include "stdafx.h"

class CManagerFrameWnd : public DuiLib::WindowImplBase
{
public:
	explicit CManagerFrameWnd(LPCTSTR pszXMLName);
	virtual ~CManagerFrameWnd();
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
public:
	void FullScreen(bool bFull);							// 全屏
	void AdaptWindowSize(UINT cxScreen);					// 根据分辨率自动调整窗口大小
	void ShowPlaylist(bool bShow);                          // 显示播放列表
public:
	void OnSearchEmployee();								// 员工搜索
	void OnSearchOrder();									// 销售订单搜索
private:
	CDuiString			m_strXMLName;
private:
	WINDOWPLACEMENT		m_OldWndPlacement;					// 保存窗口原来的位置
	BOOL				m_bFullScreenMode;					// 是不是全屏模式
};

#endif