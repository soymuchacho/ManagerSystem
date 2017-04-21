#ifndef CONTROL_EX_H
#define CONTROL_EX_H
#include "stdafx.h"

//class ComputerExamineUI : public CContainerUI
//{
//public:
//ComputerExamineUI()
//{
//	CDialogBuilder builder;
//	CContainerUI* pComputerExamine = static_cast<CContainerUI*>(builder.Create(_T("ComputerExamine.xml"), (UINT)0));
//	if (pComputerExamine) {
//		this->Add(pComputerExamine);
//	}
//	else {
//		this->RemoveAll();
//		return;
//	}
//}
//};
//
//class CDialogBuilderCallbackEx : public IDialogBuilderCallback
//{
//public:
//CControlUI* CreateControl(LPCTSTR pstrClass)
//{
//	if (_tcscmp(pstrClass, _T("ComputerExamine")) == 0) return new ComputerExamineUI;
//	return NULL;
//}
//};

class TreeNodeEx : public DuiLib::TreeNode
{

};

#endif