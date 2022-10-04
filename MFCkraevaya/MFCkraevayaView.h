
// MFCkraevayaView.h: интерфейс класса CMFCkraevayaView
//

#pragma once


class CMFCkraevayaView : public CView
{
protected: // создать только из сериализации
	CMFCkraevayaView() noexcept;
	DECLARE_DYNCREATE(CMFCkraevayaView)
private:
	int XUmax, YUmax;
	double hf, vf, xmin, xmax, ymin, ymax;
	inline int cx(double);
	inline int cy(double);
	int SZ{19};
	int GR_TB{1};
	int bg_colour{0};

// Атрибуты
public:
	CMFCkraevayaDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void DrawlGrid(CDC* pDC, const int gridx, const int gridy, CPen& Pen);
	void DrawAxis(CDC* pDC, CPen& Pen);
	void PlotGraph(CDC* PDC, int sz, double X[], double Y[], CPen& Pen);
	void PlotLabels(CDC* pDC, const int gridx, const int gridy, double LX[], double LY[]);
	void SetText(CDC* pc, int xPos, int ypos, int nPoints, CString FName, CString& text);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CMFCkraevayaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSomethingnewSettings();
};

#ifndef _DEBUG  // версия отладки в MFCkraevayaView.cpp
inline CMFCkraevayaDoc* CMFCkraevayaView::GetDocument() const
   { return reinterpret_cast<CMFCkraevayaDoc*>(m_pDocument); }
#endif

