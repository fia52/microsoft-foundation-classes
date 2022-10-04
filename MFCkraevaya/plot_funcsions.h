inline int CMFCkraevayaView::cx(double x)
{
	return (int)((x - xmin) * hf + 0.5);
}
inline int CMFCkraevayaView::cy(double y)
{
	return YUmax - (int)((y - ymin) * vf + 0.5);
}
//
void CMFCkraevayaView::DrawlGrid(CDC* pDC, const int gridx, const int gridy, CPen &Pen)
{
	CPen OldPen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(&Pen);
	double hx = (xmax - xmin) / (gridx - 1), hy = (ymax - ymin) / (gridy - 1);
	for (int i = 0; i < gridy; ++i)
	{
		pDC->MoveTo(cx(xmin), cy(ymin + hy*i));
		pDC->LineTo(cx(xmax), cy(ymin + hy*i));
	}
	for (int i = 0; i < gridx; ++i)
	{
		pDC->MoveTo(cx(xmin + hx*i), cy(ymin));
		pDC->LineTo(cx(xmin + hx*i), cy(ymax));
	}

	pDC->SelectObject(&OldPen);
}
//
void CMFCkraevayaView::DrawAxis(CDC* pDC, CPen &Pen)
{
	CPen OldPen(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(&Pen);
	if (xmin <= 0.0 && ymin <= 0.0)
	{
		// Y axis
		pDC->MoveTo(cx(0.0), cy(ymin));
		pDC->LineTo(cx(0.0), cy(ymax));
		// X axis
		pDC->MoveTo(cx(xmin), cy(0.0));
		pDC->LineTo(cx(xmax), cy(0.0));
	}
	else if (ymin <= 0.0)
	{
		// Y axis not needed

	    pDC->MoveTo(cx(xmin), cy(0.0));
		pDC->LineTo(cx(xmax), cy(0.0));
	}
	else
	{
		pDC->MoveTo(cx(0.0), cy(ymin));
		pDC->LineTo(cx(0.0), cy(ymax));
	}
	// X axis not needed

	pDC->SelectObject(&OldPen);
}
//
void CMFCkraevayaView::PlotGraph(CDC* PDC, int sz, double X[], double Y[], CPen& Pen)
{
	CPen OldPen(PS_SOLID, 1, RGB(0, 0, 0));
	PDC->SelectObject(&Pen);
	for (int i = 0; i < sz - 1; ++i)
	{
		PDC->MoveTo(cx(X[i+1]), cy(Y[i]));
		PDC->LineTo(cx(X[i + 1+1]), cy(Y[i + 1]));
	}
	PDC->SelectObject(&OldPen);
}
//
void CMFCkraevayaView::PlotLabels(CDC* pDC, const int gridx, const int gridy, double LX[], double LY[])
{
	CString Out;
	UINT SZ = 10;
	char Outch[10];
	int fntsz = 4;
	CString fname("Helvetica");
	double stepx = (xmax - xmin) / (gridx - 1); 	// xmax, xmin - is public
	double stepy = (ymax - ymin) / (gridy - 1);
	int i, dx = XUmax / (gridx - 1), dy = YUmax / (gridy - 1);
	// inits labels of coordinates
	for (i = 0; i < gridx; ++i)
		LX[i] = i * dx;
	for (i = 0; i < gridy; ++i)
		LY[i] = (i * dy);
	for (i = 0; i < gridx; i += 2)
	{
		sprintf_s(Outch, "%1.3f", xmin + i * stepx); Out = CString(Outch);
		Out.ReleaseBuffer();
		SetText(pDC, LX[i] - 15, YUmax + 5, fntsz, fname, Out);
	}
	for (i = 0; i < gridy; i += 2)
	{
		sprintf_s(Outch, "%2.4f", ymin + i * stepy); Out = CString(Outch);
		Out.ReleaseBuffer();
		SetText(pDC, -60, YUmax - LY[i] - 15, fntsz, fname, Out);
	}
}
//
void CMFCkraevayaView::SetText(CDC* pDC, int xPos, int yPos, int nPoints, CString FName, CString& text)
{
	CFont CurrentFont;
	CurrentFont.CreateFont(nPoints * 4, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, FName);
	CFont * pOldFont = (CFont*) pDC->SelectObject(&CurrentFont);
	pDC->TextOut(xPos, yPos, text);
	pDC->SelectObject(pOldFont);
}
		
			