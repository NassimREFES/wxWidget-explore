#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/font.h>
#include <wx/msgdlg.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/utils.h>

class setting_font_frame : public wxDialog
{
  wxStaticText* pointsize;
  wxSpinCtrl*   sz;
  wxStaticText* family;
  wxChoice*     choice_family;
  wxRadioBox* rb_style;
  wxRadioBox* rb_weight;
  wxCheckBox* cb_ul;
  wxButton* validate;

  wxFontFamily string_to_font_family(wxString ss)
  {
    if (ss == ft[0]) return wxFONTFAMILY_DEFAULT;
    else if (ss == ft[1]) return wxFONTFAMILY_DECORATIVE;
    else if (ss == ft[2]) return wxFONTFAMILY_ROMAN;
    else if (ss == ft[3]) return wxFONTFAMILY_SCRIPT;
    else if (ss == ft[4]) return wxFONTFAMILY_SWISS;
    else if (ss == ft[5]) return wxFONTFAMILY_MODERN;
    else if (ss == ft[6]) return wxFONTFAMILY_TELETYPE;
    return wxFONTFAMILY_UNKNOWN;
  }

  wxFontStyle string_to_font_style(wxString ss)
  {
    if (ss == st[0]) return wxFONTSTYLE_NORMAL;
    else if (ss == st[1]) return wxFONTSTYLE_ITALIC;
    else if (ss == st[2]) return wxFONTSTYLE_SLANT;
    else if (ss == st[3]) return wxFONTSTYLE_MAX;
  }

  wxFontWeight string_to_font_weight(wxString ss)
  {
    if (ss == wt[0]) return wxFONTWEIGHT_NORMAL;
    else if (ss == wt[1]) return wxFONTWEIGHT_LIGHT;
    else if (ss == wt[2]) return wxFONTWEIGHT_BOLD;
    else if (ss == wt[3]) return wxFONTWEIGHT_MAX;
  }

  struct Info {
    int ps;
    wxFontFamily ff;
    wxFontStyle fs;
    wxFontWeight fw;
    bool underline;

    Info()
    {
      ps = wxNORMAL_FONT->GetPointSize();
      ff = wxNORMAL_FONT->GetFamily();
      fs = wxNORMAL_FONT->GetStyle();
      fw = wxNORMAL_FONT->GetWeight();
      underline = wxNORMAL_FONT->GetUnderlined();
    }
  }information;
public :
  wxString ft[7] = { "Default", "Decorative", "Roman", "Script", 
		     "Swiss", "Modern", "Teletype" };
  wxString st[4] = { "Normal", "Italic", "Slant", "Max" };
  wxString wt[4] = { "Normal", "Light", "Bold", "Max" };

  int validate_value;

  setting_font_frame(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, wxT("Font Setting"), wxDefaultPosition, wxSize(430, 310))
  {
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    
    pointsize = new wxStaticText(this, wxID_ANY, wxT("pointsize: "));
    sz = new wxSpinCtrl(this, wxID_ANY, wxT("8"));
    sz->SetRange(8, 32);
    
    family = new wxStaticText(this, wxID_ANY, wxT("Family : "));
    choice_family = new wxChoice(this, wxID_ANY, wxDefaultPosition,
				 wxDefaultSize, 7, ft);
    
    rb_style = new wxRadioBox(this, wxID_ANY, wxT("Style"), wxDefaultPosition,
			      wxDefaultSize, 4, st);
    rb_style->SetSelection(0);
    rb_weight = new wxRadioBox(this, wxID_ANY, wxT("Weight"), wxDefaultPosition,
			       wxDefaultSize, 4, wt);
    cb_ul = new wxCheckBox(this, wxID_ANY, wxT("underLine"));
    validate = new wxButton(this, wxID_OK, wxT("Validate"));

    hbox1->Add(pointsize, 1, wxALL, 2);
    hbox1->Add(sz, 1, wxALL | wxEXPAND, 10);
    hbox1->Add(family, 1, wxALL, 2);
    hbox1->Add(choice_family, 1, wxALL | wxEXPAND, 10);
    vbox->Add(hbox1, 1, wxEXPAND, 10);
    vbox->Add(rb_style, 1, wxALL | wxEXPAND, 10);
    vbox->Add(rb_weight, 1, wxALL | wxEXPAND, 10);
    vbox->Add(cb_ul, 1, wxALL | wxEXPAND, 10);
    vbox->Add(validate, 1, wxALL | wxEXPAND, 10);

    Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
	    wxCommandEventHandler(setting_font_frame::OnValide));
    
    SetSizer(vbox);
    SetMinSize(wxSize(430, 310));
    Centre();
    validate_value = ShowModal();
  }

  void OnValide(wxCommandEvent& event)
  {
    information.ps = sz->GetValue();
    if (choice_family->GetSelection() != wxNOT_FOUND)
      information.ff = string_to_font_family( ft[choice_family->GetSelection()] );
    if (rb_style->GetSelection() != wxNOT_FOUND)
      information.fs = string_to_font_style( st[rb_style->GetSelection()] );
    if (rb_weight->GetSelection() != wxNOT_FOUND)
      information.fw = string_to_font_weight( wt[rb_weight->GetSelection()] );
    
    information.underline = cb_ul->IsChecked();
    validate_value = true;
    EndModal(validate_value);
  }

  Info get_setting() const { return information; }
}; 

class font_frame : public wxFrame
{
public :
  font_frame(const wxString& title);

  void OnQuit(wxCommandEvent&);
  void OnSave(wxCommandEvent&);
  void OnNew(wxCommandEvent&);
  void OnOption(wxCommandEvent&);
private :
  wxMenu* file;
  wxMenuBar* menubar;
  wxTextCtrl* text;
  
   wxStaticText* pointSize_txt;
   wxStaticText* ff_txt;
   wxStaticText* fs_txt;
   wxStaticText* fw_txt;
   wxStaticText* ul_txt;

  void setInfo(int pointsize, wxFontFamily ff, wxFontStyle fs, 
	       wxFontWeight fw, bool underline);
  void set_font_family(wxFontFamily ff);
  void set_font_style(wxFontStyle fs);
  void set_font_weight(wxFontWeight fw);
  void set_font_underline(bool ul);
  
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(font_frame, wxFrame)
  EVT_MENU(wxID_NEW, font_frame::OnNew)
  EVT_MENU(wxID_SAVE, font_frame::OnSave)
  EVT_MENU(wxID_EXIT, font_frame::OnQuit)
  EVT_MENU(wxID_EDIT, font_frame::OnOption)
END_EVENT_TABLE()

font_frame::font_frame(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 420))
{
  wxPanel* global = new wxPanel(this, wxID_ANY);
  wxPanel* panel1 = new wxPanel(global, wxID_ANY); 
  wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
  
  text = new wxTextCtrl(global, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  vbox->Add(text, 1, wxALL | wxEXPAND, 10);

  menubar = new wxMenuBar;
  file = new wxMenu;
  file->Append(wxID_NEW, wxT("&New"));
  file->Append(wxID_SAVE, wxT("&Save"));
  file->AppendSeparator();
  file->Append(wxID_EDIT, wxT("&Option"));
  file->AppendSeparator();
  file->Append(wxID_EXIT, wxT("&Quit"));
  menubar->Append(file, wxT("&File"));
  SetMenuBar(menubar);

  //--------------------------------------------

    wxBoxSizer* vbox1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox11 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox21 = new wxBoxSizer(wxHORIZONTAL);
    pointSize_txt = new wxStaticText(panel1, wxID_ANY, wxT(""));
    ff_txt        = new wxStaticText(panel1, wxID_ANY, wxT(""));
    fs_txt        = new wxStaticText(panel1, wxID_ANY, wxT(""));
    fw_txt        = new wxStaticText(panel1, wxID_ANY, wxT(""));
    ul_txt        = new wxStaticText(panel1, wxID_ANY, wxT(""));
    
    hbox11->Add(pointSize_txt, 1, wxALL | wxEXPAND, 5);
    hbox11->Add(ff_txt, 1, wxALL | wxEXPAND, 5);
    hbox11->Add(fs_txt, 1, wxALL | wxEXPAND, 5);
    vbox1->Add(hbox11, 1, wxALL | wxEXPAND, 5);
    
    hbox21->Add(fw_txt, 1, wxALL | wxEXPAND, 5);
    hbox21->Add(ul_txt, 1, wxALL | wxEXPAND, 5);
    vbox1->Add(hbox21, 1, wxALL | wxEXPAND, 5);

    panel1->SetSizer(vbox1);
    
  //--------------------------------------------

  vbox->Add(panel1, 1, wxALL | wxEXPAND, 10);

  global->SetSizer(vbox);
  Centre();
}

void font_frame::set_font_family(wxFontFamily ff)
{
  wxString s2;
  s2 << "font family : ";
  enum wxFontFamily ffo;
  switch (ff) {
    case wxFONTFAMILY_DEFAULT : s2 << "DEFAULT"; break;
    case wxFONTFAMILY_DECORATIVE : s2 << "DECORATIVE"; break;
    case wxFONTFAMILY_ROMAN : s2 << "ROMAN"; break;
    case wxFONTFAMILY_SCRIPT : s2 << "SCRIPT"; break;
    case wxFONTFAMILY_SWISS : s2 << "SWISS"; break;
    case wxFONTFAMILY_MODERN : s2 << "MODERN"; break;
    case wxFONTFAMILY_TELETYPE : s2 << "TELETYPE"; break;
    case wxFONTFAMILY_UNKNOWN : s2 << "UNKNOWN"; break;
  }
  ff_txt->SetLabel(s2);
}

void font_frame::set_font_style(wxFontStyle fs)
{
  wxString s3;
  s3 << "font style : ";
  {
  enum wxFontStyle fso;
  switch (fs) {
    case wxFONTSTYLE_NORMAL : s3 << "NORMAL"; break;
    case wxFONTSTYLE_ITALIC : s3 << "ITALIC"; break;
    case wxFONTSTYLE_SLANT  : s3 << "SLANT"; break;
    case wxFONTSTYLE_MAX    : s3 << "MAX"; break;
  }
  }
  fs_txt->SetLabel(s3);
}

void font_frame::set_font_weight(wxFontWeight fw)
{
  wxString s4;
  s4 << "font weight : ";
  enum wxFontWeight fwo;
  switch (fw) {
  case wxFONTWEIGHT_NORMAL : s4 << "NORMAL"; break;
  case wxFONTWEIGHT_LIGHT : s4 << "LIGHT"; break;
  case wxFONTWEIGHT_BOLD : s4 << "BOLD"; break;
  case wxFONTWEIGHT_MAX : s4 << "MAX"; break;
  }
  fw_txt->SetLabel(s4);
}

void font_frame::set_font_underline(bool ul)
{
  wxString s5;
  s5 << "underline : " << (ul ? "true" : "false");
  ul_txt->SetLabel(s5);
}

void font_frame::setInfo(int pointsize, wxFontFamily ff, wxFontStyle fs, 
	       wxFontWeight fw, bool underline)
{
  wxString s1;
  s1 << "point size : " << pointsize;
  pointSize_txt->SetLabel(s1);

  set_font_family(ff);
  set_font_style(fs);
  set_font_weight(fw);
  set_font_underline(underline);

  text->SetFont(wxFont(pointsize, ff, fs, fw, underline));
}

void font_frame::OnNew(wxCommandEvent& event)
{
  wxMessageDialog* msgd = new wxMessageDialog(NULL, wxT("Are u sure u want to clear text ?"), wxT("NEW"),
					      wxYES_NO | wxCENTRE | wxICON_QUESTION | wxNO_DEFAULT);
  int res = msgd->ShowModal();
  msgd->Destroy();
  if (res == wxID_YES)
    text->SetValue("");
}

void font_frame::OnSave(wxCommandEvent& event)
{
  text->SaveFile(wxT("save_txt.txt"));
  wxMessageBox("Saved !");
}

void font_frame::OnOption(wxCommandEvent& event)
{
  setting_font_frame* frame = new setting_font_frame(this);
  setInfo(frame->get_setting().ps, frame->get_setting().ff,
	  frame->get_setting().fs, frame->get_setting().fw,
	  frame->get_setting().underline);
}

void font_frame::OnQuit(wxCommandEvent& event)
{
  Close();
}

class myapp : public wxApp
{
public :
  virtual bool OnInit();
};

IMPLEMENT_APP(myapp)

bool myapp::OnInit()
{
  font_frame* frame = new font_frame(wxT("FONT TEST"));
  frame->Show(true);
  return true;
}
