#include <wx/wx.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/dcps.h>
#include <wx/utils.h>

class Window : public wxFrame
{
public :
  Window(const wxString& title);
  void OnMotion(wxMouseEvent& event);
  //void OnErase(wxEraseEvent& event);
  void OnPaint(wxPaintEvent&);
private :
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(Window, wxFrame)
   EVT_MOTION(Window::OnMotion)
// EVT_ERASE_BACKGROUND(Window::OnErase)
   EVT_PAINT(Window::OnPaint)
END_EVENT_TABLE()

Window::Window(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400), wxFULL_REPAINT_ON_RESIZE | wxDEFAULT_FRAME_STYLE )
{
  wxExecute(wxT("java appTest"));
  
  Centre();
}

void Window::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  
  wxPen pen(*wxRED, 6);
  dc.SetPen(pen);
  dc.SetBrush(*wxRED_BRUSH);

  wxSize sz = GetClientSize();
  
  wxCoord w = 100, h = 50;
  int x = wxMax(0, (sz.x - w)/2);
  int y = wxMax(0, (sz.y - h)/2);

  wxRect rectToDraw(x, y, w, h);
  
  /* if (IsExposed(rectToDraw))
     dc.DrawRectangle(rectToDraw);*/
}

void Window::OnMotion(wxMouseEvent& event)
{
  if (event.Dragging()) {
    wxClientDC dc(this);
    wxPen pen(*wxRED, 10);
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);
    dc.DrawLine(event.GetPosition(), event.GetPosition());
    dc.SetPen(wxNullPen);
  }
}

/*void Window::OnErase(wxEraseEvent& event)
{
  wxClientDC* clientDC = NULL;
  if (!event.GetDC()) 
    clientDC = new wxClientDC(this);

  wxDC* dc = clientDC ? clientDC : event.GetDC();

  wxSize sz = GetClientSize();
  wxEffects effects;
  effects.TIleBitmap(wxRect(0, 0, sz.x, sz.y), *dc, m_bitmap);
  if (clientDC)
    delete clientDC;
}*/

class MyCustomCtrl : public wxScrolledWindow
{
public :
  MyCustomCtrl(wxWindow*);
  
  void OnPaint(wxPaintEvent&);
  void OnEraseBackground(wxEraseEvent&);
  void PaintBackground(wxDC&);
  wxBitmap CreateRedOutlineBitmap();
  wxBitmap GetScreenShot();
private :
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyCustomCtrl, wxScrolledWindow)
  EVT_PAINT(MyCustomCtrl::OnPaint)
  EVT_ERASE_BACKGROUND(MyCustomCtrl::OnEraseBackground)
END_EVENT_TABLE()

MyCustomCtrl::MyCustomCtrl(wxWindow* parent)
: wxScrolledWindow(parent)
{
  wxBitmap bt = GetScreenShot();
  if ( bt.SaveFile(wxT("test"), wxBITMAP_TYPE_PNG) )
    wxMessageBox("File saved!");
  Centre();
}

wxBitmap MyCustomCtrl::CreateRedOutlineBitmap()
{
  wxMemoryDC memDC;
  wxBitmap bitmap(200, 200);
  memDC.SelectObject(bitmap);
  memDC.SetBackground(*wxWHITE_BRUSH);
  memDC.Clear();
  memDC.SetPen(*wxRED_PEN);
  memDC.SetBrush(*wxTRANSPARENT_BRUSH);
  memDC.DrawRectangle(wxRect(10, 10, 100, 100));
  memDC.SelectObject(wxNullBitmap);
  return bitmap;
}

wxBitmap MyCustomCtrl::GetScreenShot()
{
  wxSize screenSize = wxGetDisplaySize();
  wxBitmap bitmap(screenSize.x, screenSize.y);
  wxScreenDC dc;
  wxMemoryDC memDC;
  memDC.SelectObject(bitmap);
  memDC.Blit(0, 0, screenSize.x, screenSize.y, &dc, 0, 0);
  memDC.SelectObject(wxNullBitmap);
  return bitmap;
}

void MyCustomCtrl::PaintBackground(wxDC& dc)
{
  wxColour backgroundColour = GetBackgroundColour();
  if (!backgroundColour.IsOk())
    backgroundColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
  dc.SetBrush(wxBrush(backgroundColour));
  dc.SetPen(wxPen(backgroundColour, 1));
  wxRect windowRect(wxPoint(0, 0), GetClientSize());
  CalcUnscrolledPosition(windowRect.x, windowRect.y,
			 &windowRect.x, &windowRect.y);
  dc.DrawRectangle(windowRect);
}

void MyCustomCtrl::OnPaint(wxPaintEvent& event)
{
  wxBufferedPaintDC dc(this);
  PrepareDC(dc);
  PaintBackground(dc);
  dc.SetPen(*wxBLACK_PEN);
  dc.DrawRectangle(50, 50, 100, 100);
  dc.SetPen(wxNullPen);
}

void MyCustomCtrl::OnEraseBackground(wxEraseEvent& event)
{
}

class app : public wxApp
{
public :
  virtual bool OnInit();
};

DECLARE_APP(app)
IMPLEMENT_APP(app)

bool app::OnInit()
{
  /*wxFrame* f = new wxFrame(NULL, wxID_ANY, wxT("simple test"),
			   wxDefaultPosition, wxSize(400, 400));
			   
  MyCustomCtrl* win = new MyCustomCtrl(f);*/
  Window* win = new Window(wxT("test"));
  win->Show(true);
  //f->Show(true);
  return true;
}

