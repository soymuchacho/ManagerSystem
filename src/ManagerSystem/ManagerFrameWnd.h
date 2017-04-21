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
	void FullScreen(bool bFull);							// ȫ��
	void AdaptWindowSize(UINT cxScreen);					// ���ݷֱ����Զ��������ڴ�С
	void ShowPlaylist(bool bShow);                          // ��ʾ�����б�
public:
	void OnSearchEmployee();								// Ա������
	void OnSearchOrder();									// ���۶�������
private:
	CDuiString			m_strXMLName;
private:
	WINDOWPLACEMENT		m_OldWndPlacement;					// ���洰��ԭ����λ��
	BOOL				m_bFullScreenMode;					// �ǲ���ȫ��ģʽ
};

#endif