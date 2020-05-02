#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/bmpbuttn.h>
#include <iostream>
/*
class MyButton : public wxFrame
{
public :
  MyButton(const wxString& title);
  void OnQuit(wxCommandEvent& event);
private :
  DECLARE_EVENT_TABLE()
};

MyButton::MyButton(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, 
	    wxSize(270, 150))
{
  wxPanel* panel = new wxPanel(this, wxID_ANY);
  wxButton* button = new wxButton(panel, wxID_EXIT,
				  wxT("Quit"), wxPoint(20, 20));
  Centre();
}

void MyButton::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

BEGIN_EVENT_TABLE(MyButton, wxFrame)
  EVT_BUTTON(wxID_EXIT, MyButton::OnQuit)
END_EVENT_TABLE()*/

/*class Button : public wxButton
{
public :
   wxPoint pos;
   Button(wxWindow *parent, wxWindowID id, const wxString& title, const wxPoint &pos, 
	   const wxSize &size)
	  : wxButton(parent, id, title, pos, size)
  {
  }
};

class Move : public wxFrame
{
public :
  Move(const wxString& title);

  void OnMove(wxMoveEvent& event);
  void OnMotion(wxMouseEvent& event);
private :
  wxStaticText* str1, *str2;
  Button* button;
};

Move::Move(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
{
  wxPanel* panel = new wxPanel(this, -1);
  str1 = new wxStaticText(panel, -1, wxT(""), wxPoint(10, 10));
  str2 = new wxStaticText(panel, -1, wxT(""), wxPoint(10, 30));
  button = new Button(panel, -1, wxT("B"), wxPoint(50, 50), wxSize(50, 50));

  Connect(wxEVT_MOVE, wxMoveEventHandler(Move::OnMove));
  Connect(wxEVT_MOTION, wxMouseEventHandler(Move::OnMotion));
  Centre();
}

void Move::OnMotion(wxMouseEvent& event)
{
    button->SetPosition(event.GetPosition());
}

void Move::OnMove(wxMoveEvent& event)
{
  wxPoint pos = event.GetPosition();
  str1->SetLabel(wxString::Format(wxT("x : %d"), pos.x));
  str2->SetLabel(wxString::Format(wxT("y : %d"), pos.y));
}*/

class Propagate : public wxFrame
{
public :
  Propagate(const wxString& title);

  void OnClick(wxCommandEvent& event);
};

class MyPanel : public wxPanel
{
public :
  MyPanel(wxFrame* frame, int id);
  void OnClick(wxCommandEvent& event);
};

class MyButton : public wxButton
{
public :
  MyButton(MyPanel* panel, int id, const wxString& label);
  void OnClick(wxCommandEvent& event);
};

const int ID_BUTTON = 1;

Propagate::Propagate(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
{
  MyPanel* panel = new MyPanel(this, -1);
  new MyButton(panel, ID_BUTTON, wxT("Ok"));
  Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, 
	  wxCommandEventHandler(Propagate::OnClick));
  Centre();
}

void Propagate::OnClick(wxCommandEvent& event)
{
  std::cout << "event reached frame class\n";
  event.Skip();
}

MyPanel::MyPanel(wxFrame* frame, int id)
  : wxPanel(frame, id)
{
  Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, 
	  wxCommandEventHandler(MyPanel::OnClick));
}

void MyPanel::OnClick(wxCommandEvent& event)
{
  std::cout << "event reached panel class\n";
  event.Skip();
}

MyButton::MyButton(MyPanel* panel, int id, const wxString& label)
  : wxButton(panel, id, label, wxPoint(15, 15))
{
  Connect(ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED,
	  wxCommandEventHandler(MyButton::OnClick));
}

void MyButton::OnClick(wxCommandEvent& event)
{
  std::cout << "event reached button class\n";
  event.Skip();
}

class Veto : public wxFrame
{
public :
  Veto(const wxString& title);
  void OnClose(wxCloseEvent& event);
};

Veto::Veto(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
{
  Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(Veto::OnClose));
  Centre();
}

void Veto::OnClose(wxCloseEvent& event)
{
  wxMessageDialog* dial = new wxMessageDialog(NULL,
					      wxT("Are you sure to quit?"),
					      wxT("Question"),
					      wxYES_NO | wxNO_DEFAULT | 
					      wxICON_QUESTION);
  int ret = dial->ShowModal();
  dial->Destroy();
  if ( ret == wxID_YES )
    Destroy();
  else
    event.Veto();
}

class Ident : public wxFrame
{
public :
  Ident(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
  {
    wxPanel* panel = new wxPanel(this, -1);
    wxGridSizer* grid = new wxGridSizer(2, 3, 5, 5);

    grid->Add(new wxButton(panel, wxID_CANCEL), 0, wxTOP | wxLEFT, 9);
    grid->Add(new wxButton(panel, wxID_DELETE), 0, wxTOP, 9);
    grid->Add(new wxButton(panel, wxID_SAVE), 0, wxLEFT, 9);
    grid->Add(new wxButton(panel, wxID_EXIT));
    grid->Add(new wxButton(panel, wxID_STOP), 0, wxLEFT, 9);
    grid->Add(new wxButton(panel, wxID_NEW));
    wxBitmapButton* button = new wxBitmapButton(panel, wxID_ANY, wxBitmap(wxT("folder_cyan_open.png")), wxPoint(50, 50));
    //panel->SetSizer(grid);
    Centre();
  }
};




class MyApp : public wxApp
{
public :
  virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  //Veto* move = new Veto(wxT("veto"));
  Ident* ident = new Ident(wxT("Identifiers"));
  ident->Show(true);
  return true;
}
