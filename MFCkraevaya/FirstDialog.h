#pragma once
#include "afxdialogex.h"


// Диалоговое окно FirstDialog

class FirstDialog : public CDialog
{
	DECLARE_DYNAMIC(FirstDialog)

public:
	FirstDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~FirstDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int SZ;
	int GR_TB;
	int bg_colour;
};
