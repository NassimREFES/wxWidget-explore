#include <wx/wx.h>

class SubMenu : public wxFrame {
public :
  SubMenu(const wxString& title);

  void OnQuit(wxCommandEvent& event);

  wxMenuBar* menubar;
  wxMenu* file;
  wxMenu* imp;
  wxMenuItem* quit;
};

SubMenu::SubMenu(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 190))
{
  menubar = new wxMenuBar;
  file = new wxMenu;

  file->Append(wxID_ANY, wxT("&New"));
  file->Append(wxID_ANY, wxT("&Open"));
  file->Append(wxID_ANY, wxT("&Save"));
  file->AppendSeparator();
  
  imp = new wxMenu;
  imp->Append(wxID_ANY, wxT("Import newsfeed list..."));
  imp->Append(wxID_ANY, wxT("Import bookmarks..."));
  imp->Append(wxID_ANY, wxT("Import mail..."));
  
  file->AppendSubMenu(imp, wxT("I&mport"));

  quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl + W"));
  file->Append(quit);

  menubar->Append(file, wxT("&File"));
  SetMenuBar(menubar);

  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
	  wxCommandEventHandler(SubMenu::OnQuit));

  Centre();
}

void SubMenu::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

class toolBar : public wxFrame
{
public :
  toolBar(const wxString& title);
  void OnQuit(wxCommandEvent& event);
};

toolBar::toolBar(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 180))
{
  wxImage::AddHandler(new wxPNGHandler);

  wxBitmap exit(wxT("exit.png"), wxBITMAP_TYPE_PNG);
  wxToolBar* toolbar = CreateToolBar(wxTB_VERTICAL);
  toolbar->AddTool(wxID_EXIT, exit, wxT("Exit application"));
  toolbar->AddTool(wxID_ANY, wxT("khra"), wxBitmap(wxT("open.png"), wxBITMAP_TYPE_PNG), wxT("Open application"), wxITEM_CHECK);
  toolbar->Realize();

  Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED,
	  wxCommandEventHandler(toolBar::OnQuit));
  Centre();
}

void toolBar::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

class Align : public wxFrame
{
public :
  Align(const wxString& title);
};

Align::Align(const wxString& title)
  : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(300, 200))
{
  wxPanel* panel = new wxPanel(this, -1);

  wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);

  wxButton* ok = new wxButton(panel, -1, wxT("OK"));
  wxButton* cancel = new wxButton(panel, -1, wxT("Cancel"));
  
  hbox1->Add(new wxPanel(panel, -1));
  vbox->Add(hbox1, 1, wxEXPAND);
  
  hbox2->Add(ok);
  hbox2->Add(cancel);

  vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
  panel->SetSizer(vbox);

  Centre();
}

class MyApp : public wxApp 
{
public :
  virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  Align* m = new Align(wxT("Align panel and button"));
  m->Show(true);
  return true;
}
