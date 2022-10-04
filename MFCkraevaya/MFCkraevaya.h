
// MFCkraevaya.h: основной файл заголовка для приложения MFCkraevaya
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMFCkraevayaApp:
// Сведения о реализации этого класса: MFCkraevaya.cpp
//

class CMFCkraevayaApp : public CWinApp
{
public:
	CMFCkraevayaApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCkraevayaApp theApp;
