#include <wx/wx.h>
#include <wx/dc.h>

class ShapedFrame : public wxFrame
{
  wxBitmap* m_bmp;
  bool m_hasShape;
public :
  ShapedFrame();
  void OnWindowCreate(wxWindowCreateEvent& event);
  void SetWindowShape();
  void OnMouseMove(wxMouseEvent& event);
  void OnPaint(wxPaintEvent& event);
private :
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(ShapedFrame, wxFrame)
  EVT_MOTION(ShapedFrame::OnMouseMove)
  EVT_PAINT(ShapedFrame::OnPaint)
#ifdef __WXGTK__
  EVT_WINDOW_CREATE(ShapedFrame::OnWindowCreate)
#endif
END_EVENT_TABLE()

ShapedFrame::ShapedFrame()
: wxFrame(NULL, wxID_ANY, wxEmptyString, 
	  wxDefaultPosition, wxSize(250, 300),
	  wxFRAME_SHAPED | wxSIMPLE_BORDER |
	  wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP)
{
  m_hasShape = false;
  m_bmp = new wxBitmap(wxT("test.png"), wxBITMAP_TYPE_PNG);
  SetSize(m_bmp->GetWidth(), m_bmp->GetHeight());
#ifndef __WXGTK__
  SetWindowShape();
#endif
}

void ShapedFrame::OnWindowCreate(wxWindowCreateEvent& WXUNUSED(event))
{
  SetWindowShape();
}

void ShapedFrame::SetWindowShape()
{
  wxRegion region(m_bmp, *wxWHITE);
  m_hasShape = SetShape(region);
}

void ShapedFrame::OnMouseMove(wxMouseEvent& event)
{
  wxPoint pt = event.GetPosition();
  if (event.Dragging() && event.LeftIsDown())
  {
    wxPoint pos = ClientToScreen(pt);
    Move(pos);
  }
}

void ShapedFrame::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  dc.DrawBitmap(m_bmp, 0, 0, true);
}

class MyApp : public wxApp
{
public :
  virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  /* wxFrame* frame = new wxFrame(NULL, wxID_ANY, wxT("test frame"));
  frame->CreateStatusBar(2, wxST_SIZEGRIP);
  int widths[3] = { 100, 100, -1 };
  // frame->SetStatusWidths(3, widths);
  frame->SetStatusText(wxT("Ready"), 0);
  frame->SetStatusText(wxT("Test1"), 1);
  frame->Show(true);*/

  ShapedFrame* f = new ShapedFrame();
  f->Show(true);
  return true;
}
