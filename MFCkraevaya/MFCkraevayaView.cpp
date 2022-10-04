
// MFCkraevayaView.cpp: реализация класса CMFCkraevayaView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFCkraevaya.h"
#endif

#include "MFCkraevayaDoc.h"
#include "MFCkraevayaView.h"
#include "FirstDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "plot_funcsions.h"

// CMFCkraevayaView

//consts: 
const int N = 100;
double a = 0; // Начало отрезка. 
double b = 1; // Конец отрезка.
double Y0 = 2; // Значение в начале.
double Yn = 2 * sqrt(2); // Значение на конце.
double q = -2; // Значение q(x) - константы.
double f = -1.5; // Значение f(x) - константы.
//
void Thomas(double[][N], double[], double[], int);
void zeroing(double[][N]);
void Input_rights(double[], int, double, double[], double, double, double, int);
void Input_matrix_coeff(double[][N], double, double, double[], int);
void Input_x_p(double, double[N + 1], double[N + 1], double, int);
//

IMPLEMENT_DYNCREATE(CMFCkraevayaView, CView)

BEGIN_MESSAGE_MAP(CMFCkraevayaView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(ID_SOMETHINGNEW_SETTINGS, &CMFCkraevayaView::OnSomethingnewSettings)
END_MESSAGE_MAP()

// Создание или уничтожение CMFCkraevayaView

CMFCkraevayaView::CMFCkraevayaView() noexcept
{
	// TODO: добавьте код создания

}

CMFCkraevayaView::~CMFCkraevayaView()
{
}

BOOL CMFCkraevayaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CMFCkraevayaView

void CMFCkraevayaView::OnDraw(CDC* pDC)
{
	CMFCkraevayaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
    // Фон
    CRect clientrect;
    GetClientRect(clientrect);
    if (bg_colour == 0) 
        pDC->FillSolidRect(clientrect, RGB(255, 255, 255));
    else if (bg_colour == 1) 
        pDC->FillSolidRect(clientrect, RGB(169, 169, 169));
    //
    int Xmax = ::GetSystemMetrics(SM_CXSCREEN);
    int Ymax = ::GetSystemMetrics(SM_CYSCREEN);
    //
    XUmax = Xmax / 2, YUmax = Ymax / 2;
    //
    int sz = SZ;
	double h = (b - a) / (sz+1);
	double x[N] = { NAN }, p[N] = { NAN }, y[N] = { NAN };
	Input_x_p(a, x, p, h, sz);
	double A[N][N];
	zeroing(A);
	Input_matrix_coeff(A, q, h, p, sz);
	double rights[N] = { NAN };
	Input_rights(rights, N, h, p, f, Y0, Yn, sz);
	Thomas(A, rights, y, sz);
    //
    if (GR_TB == 0)
    {
        int sx = Xmax / 8;
        int sy = Ymax / 30; 
        pDC->SetViewportOrg(sx, sy); 
        xmin = x[1]; xmax = x[sz];
        ymax = y[0], ymin = y[0];
        for (int i = 0; i < sz; ++i)
        {
            ymax = max(ymax, y[i]);
            ymin = min(ymin, y[i]);
        }
        hf = XUmax / (xmax - xmin), vf = YUmax / (ymax - ymin);
        //
        CPen GreenPen(PS_SOLID, 12, RGB(0, 255, 0));
        //DrawAxis(pDC, GreenPen);
        //
        CPen BlackPen(PS_SOLID, 4, RGB(0, 0, 0));
        DrawlGrid(pDC, 10, 10, BlackPen);
        //
        CPen BluePen(PS_SOLID, 6, RGB(0, 255, 255));
        PlotGraph(pDC, sz, x, y, BluePen);
        //
        PlotLabels(pDC, sz, sz, x, y);
        //
        CString text("My solution Graf:");
        CString FName("graph");
        SetText(pDC, 15, 25, 15, FName, text);
        //
    }
    else if (GR_TB == 1)
    {
        int sx = Xmax / 20;
        int sy = Ymax / 50; 
        pDC->SetViewportOrg(sx, sy); 
        CString text("Coeff matrix:");
        pDC->TextOut(0, -1, text);
        CString txt;
        for (int i = 0; i <= sz-1; ++i)
        {
            for (int j = 0; j <= sz-1; ++j)
            {
                txt.Format(_T(" %.1f"), A[i][j]);
                pDC->TextOut(60 * j, 20 + 30 * i, txt);
            }
        }
        //
        CString text1("Solutions at X-points:");
        pDC->TextOut(0, 32*sz, text1);
        //
        for (int i = 1; i < sz + 1; i++)
        {
            txt.Format(_T(" %.2f"), x[i]);
            pDC->TextOut(60 * (i-1), 34 * sz, txt);
        }
        //
        for (int i = 0; i < sz; i++)
        {
            txt.Format(_T(" %.3f"), y[i]);
            pDC->TextOut(60 * i, 36 * sz, txt);
        }
        //
    }
}


// Печать CMFCkraevayaView

BOOL CMFCkraevayaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CMFCkraevayaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CMFCkraevayaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CMFCkraevayaView

#ifdef _DEBUG
void CMFCkraevayaView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCkraevayaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCkraevayaDoc* CMFCkraevayaView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCkraevayaDoc)));
	return (CMFCkraevayaDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMFCkraevayaView

void Thomas(double C[][N], double f[], double y[], int sz)
{
    double S[N] = { NAN };
    double K[N] = { NAN };

    S[1] = -C[0][1] / C[0][0];
    K[1] = f[0] / C[0][0];

    for (int i = 1; i < sz - 1; i++)
    {
        S[i + 1] = -C[i][i + 1] / ((C[i][i - 1] * S[i]) + C[i][i]);
        K[i + 1] = (f[i] - (C[i][i - 1] * K[i])) / ((C[i][i - 1] * S[i]) + C[i][i]);
    }
    y[sz - 1] = ((-C[sz - 1][sz - 2] * K[sz - 1]) - f[sz - 1]) / ((C[sz - 1][sz - 2] * S[sz - 1]) + C[sz - 1][sz - 1]);
    for (int j = sz - 2; j >= 0; j--)
    {
        y[j] = (S[j + 1] * y[j + 1]) + K[j + 1];
    }
}
void zeroing(double Matrix[][N])
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++) Matrix[i][j] = 0;
    }
}
void Input_rights(double rights[N], int N, double h, double p[], double f, double y0, double yn, int sz)
{
    for (int i = 0; i < sz; i++)
    {
        if (i == 0)
        {
            rights[i] = f - y0 * (1 / (h * h) - p[i + 1] / (2 * h));
        }
        else if (i == sz - 1)
        {
            rights[i] = -(f - yn * (1 / (h * h) + p[i + 1] / (2 * h)));
        }
        else
        {
            rights[i] = f;
        }
    }
}
void Input_matrix_coeff(double A[][N], double q, double h, double p[], int sz)
{
    for (int i = 0; i < sz; i++)
    {
        if (i == 0)
        {
            A[i][i] = (-2 / (h * h) + q);
            A[i][i + 1] = (1 / (h * h) + p[i + 1] / (2 * h));
        }
        else if (i == sz - 1)
        {
            A[i][i - 1] = (1 / (h * h) - p[i + 1] / (2 * h));
            A[i][i] = (-2 / (h * h) + q);
        }
        else
        {
            A[i][i - 1] = (1 / (h * h) - p[i + 1] / (2 * h));
            A[i][i] = (-2 / (h * h) + q);
            A[i][i + 1] = (1 / (h * h) + p[i + 1] / (h * 2));
        }
    }
}
void Input_x_p(double a, double x[N], double p[N], double h, int sz)
{
    for (int i = 0; i < sz + 1; i++)
    {
        x[i] = a;
        p[i] = x[i];
        a = a + h;
    }
}

void CMFCkraevayaView::OnSomethingnewSettings()
{
    FirstDialog dlg;

    dlg.SZ = SZ;
    dlg.GR_TB = GR_TB;
    dlg.bg_colour = bg_colour;

    if (dlg.DoModal() == IDOK)
    {
        SZ = dlg.SZ;
        GR_TB = dlg.GR_TB;
        bg_colour = dlg.bg_colour;
    }
    Invalidate();
    UpdateWindow();
}
