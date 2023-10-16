//
// Name :         ImageGenerateDoc.cpp
// Description :  Implementation of the document class for the 
//                ImageProcess application.
//

// Notice:  Do not add any headers before stdafx.h
#include "pch.h"

#include "ImageProcess.h"
#include "graphics/GrImage.h"
#include <cmath>

#include <fstream>

#include "ImageGenerateDoc.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CImageGenerateDoc

IMPLEMENT_DYNCREATE(CImageGenerateDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageGenerateDoc, CDocument)
    //{{AFX_MSG_MAP(CImageGenerateDoc)
    ON_COMMAND(ID_MOUSE_DRAW, OnMouseDraw)
    //}}AFX_MSG_MAP
    ON_COMMAND(ID_GENERATE_FILLWHITE, &CImageGenerateDoc::OnGenerateFillwhite)
    ON_COMMAND(ID_GENERATE_FILLGREEN, &CImageGenerateDoc::OnGenerateFillgreen)
    ON_COMMAND(ID_GENERATE_FILLFIREBRICK, &CImageGenerateDoc::OnGenerateFillfirebrick)
    ON_COMMAND(ID_GENERATE_FILLHORIZANTALGRADIENT, &CImageGenerateDoc::OnGenerateFillhorizantalgradient)
    ON_COMMAND(ID_GENERATE_FILLVERTICALGREENGRADIENT, &CImageGenerateDoc::OnGenerateFillverticalgreengradient)
    ON_COMMAND(ID_GENERATE_FILLDIAGONALGRADIENT, &CImageGenerateDoc::OnGenerateFilldiagonalgradient)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageGenerateDoc construction/destruction

CImageGenerateDoc::CImageGenerateDoc()
{
    m_mousemode = 0;     // No mouse mode
    m_clickcnt = 0;
}

CImageGenerateDoc::~CImageGenerateDoc()
{
}

BOOL CImageGenerateDoc::OnNewDocument()
{
    m_image.SetSize(640, 480);
    m_image.Fill(0, 0, 0);
    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImageGenerateDoc diagnostics

#ifdef _DEBUG
void CImageGenerateDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CImageGenerateDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageGenerateDoc commands

BOOL CImageGenerateDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    return FALSE;
}

//
//  Name :         CImageGenerateDoc::OnSaveDocument()
//  Description :  Write the image to a BMP file.
//

BOOL CImageGenerateDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
    BeginWaitCursor();
    DeleteContents();

    bool r = m_image.SaveFile(lpszPathName, CGrImage::BMP);
    EndWaitCursor();

    if(!r)
    {
        // Error message on return
        AfxMessageBox(m_image.GetError(), NULL, MB_ICONINFORMATION | MB_OK);
        return FALSE;
    }

    SetModifiedFlag(FALSE);     // start off with unmodified
    return TRUE;
}




//
// Menu option handlers
//


//
// Name :         CImageGenerateDoc::OnGenerateFillwhite()
// Description :  Fill the image with white.
//
void CImageGenerateDoc::OnGenerateFillwhite()
{
    for(int r=0;  r<m_image.GetHeight();  r++)
    {
        // Looping over the columns of the array
        for(int c=0;  c<m_image.GetWidth() * 3;  c++)
        {
            m_image[r][c] = 255;
        }
    }

    UpdateAllViews(NULL);
}



//
// Name :         CImageGenerateDoc::OnMouseDraw() 
// Description :  Set the mouse draw mode.
//

void CImageGenerateDoc::OnMouseDraw() 
{
    m_mousemode = ID_MOUSE_DRAW;
}






/////////////////////////////////////////////////////////////////////
//
// Mouse Handlers
//
/////////////////////////////////////////////////////////////////////


//
// Name :         CImageGenerateDoc::MousePress()
// Description :  This function is called when the mouse is pressed over
//                m_image2.  The x,y coordinate is in the image.
//

void CImageGenerateDoc::MousePress(int x, int y)
{
    // We count the mouse clicks
    m_clickcnt++;

    BeginWaitCursor();

    switch(m_mousemode)
    {
    case ID_MOUSE_DRAW:
        m_image[y][x * 3] = 0;
        m_image[y][x * 3 + 1] = 255;
        m_image[y][x * 3 + 2] = 0;
        break;

    }

    UpdateAllViews(NULL);
    EndWaitCursor();
}


//
// Name :         CImageGenerateDoc::MouseMove()
// Description :  This function is called when the mouse is moved over
//                m_image.  The x,y coordinate is in the image.
//

void CImageGenerateDoc::MouseMove(int x, int y)
{
    BeginWaitCursor();

    switch(m_mousemode)
    {
    case ID_MOUSE_DRAW:
        m_image[y][x * 3] = 0;          // Blue
        m_image[y][x * 3 + 1] = 255;    // Green
        m_image[y][x * 3 + 2] = 255;    // Red
        break;
    }   

    UpdateAllViews(NULL);
    EndWaitCursor();
}


void CImageGenerateDoc::OnGenerateFillgreen()
{
    for (int r = 0; r < m_image.GetHeight(); r++)
    {
        // Looping over the columns of the image
        for (int c = 0; c < m_image.GetWidth(); c++)
        {
            m_image[r][c * 3 + 0] = 0;
            m_image[r][c * 3 + 1] = 255;
            m_image[r][c * 3 + 2] = 0;
        }
    }

    UpdateAllViews(NULL);// TODO: Add your command handler code here
}


void CImageGenerateDoc::OnGenerateFillfirebrick()
{
    for (int r = 0; r < m_image.GetHeight(); r++)
    {
        // Looping over the columns of the image
        for (int c = 0; c < m_image.GetWidth(); c++)
        {
            m_image[r][c * 3 + 0] = 34;  // Blue component
            m_image[r][c * 3 + 1] = 34;  // Green component
            m_image[r][c * 3 + 2] = 178; // Red component
        }
    }

    UpdateAllViews(NULL);
}


void CImageGenerateDoc::OnGenerateFillhorizantalgradient()
{
    for (int r = 0; r < m_image.GetHeight(); r++)
    {
        for (int c = 0; c < m_image.GetWidth(); c++)
        {
            BYTE intensity = BYTE(float(c) / float(m_image.GetWidth() - 1) * 255);
            m_image[r][c * 3 + 0] = intensity; // Blue component
            m_image[r][c * 3 + 1] = intensity; // Green component
            m_image[r][c * 3 + 2] = intensity; // Red component
        }
    }

    UpdateAllViews(NULL);// TODO: Add your command handler code here
}


void CImageGenerateDoc::OnGenerateFillverticalgreengradient()
{
    for (int r = 0; r < m_image.GetHeight(); r++)
    {
        BYTE blue = BYTE((m_image.GetHeight() - 1 - float(r)) / float(m_image.GetHeight() - 1) * 128);
        BYTE green = BYTE((m_image.GetHeight() - 1 - float(r)) / float(m_image.GetHeight() - 1) * 255);
        BYTE red = BYTE((m_image.GetHeight() - 1 - float(r)) / float(m_image.GetHeight() - 1) * 200);

        for (int c = 0; c < m_image.GetWidth(); c++)
        {
            m_image[r][c * 3 + 0] = blue;   // Blue component
            m_image[r][c * 3 + 1] = green;  // Green component
            m_image[r][c * 3 + 2] = red;    // Red component
        }
    }

    UpdateAllViews(NULL);// TODO: Add your command handler code here
}


void CImageGenerateDoc::OnGenerateFilldiagonalgradient()
{
    for (int r = 0; r < m_image.GetHeight(); r++)
    {
        for (int c = 0; c < m_image.GetWidth(); c++)
        {
            float diag_ratio = float(r + c) / (m_image.GetHeight() + m_image.GetWidth() - 2);

            BYTE blue = BYTE((1 - diag_ratio) * 0 + diag_ratio * 128); // Green to Purple
            BYTE green = BYTE((1 - diag_ratio) * 255 + diag_ratio * 0); // Green to Purple
            BYTE red = BYTE((1 - diag_ratio) * 0 + diag_ratio * 128); // Green to Purple

            m_image[r][c * 3 + 0] = blue;   // Blue component
            m_image[r][c * 3 + 1] = green;  // Green component
            m_image[r][c * 3 + 2] = red;    // Red component
        }
    }

    UpdateAllViews(NULL);// TODO: Add your command handler code here
}
