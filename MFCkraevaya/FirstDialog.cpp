// FirstDialog.cpp: файл реализации
//

#include "pch.h"
#include "MFCkraevaya.h"
#include "afxdialogex.h"
#include "FirstDialog.h"


// Диалоговое окно FirstDialog

IMPLEMENT_DYNAMIC(FirstDialog, CDialog)

FirstDialog::FirstDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, SZ(19)
	, GR_TB(0)
	, bg_colour(0)
{

}

FirstDialog::~FirstDialog()
{
}

void FirstDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SZ, SZ);
	DDV_MinMaxInt(pDX, SZ, 1, 99);
	DDX_Radio(pDX, IDC_RADIO_Graf, GR_TB);
	DDX_Radio(pDX, IDC_RADIO_WHITE, bg_colour);
}


BEGIN_MESSAGE_MAP(FirstDialog, CDialog)
END_MESSAGE_MAP()


// Обработчики сообщений FirstDialog
