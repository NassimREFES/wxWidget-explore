#include <wx/wx.h>
#include <wx/dcclient.h>

using namespace std;

class move : public wxPanel;
{
public:
    move(wxWindow* parent);
    void start(int ms);
protected:
    void OnPaint(wxPaintEvent&);
    void OnTimer(wxCommandEvent&);

private:
    wxTimer* timer;
    vector<int> map;
    int from, to;
};

move::move(wxWindow* parent)
: wxPanel(parent, wxID_ANY, wxDefaultPosition,
        wxDefaultSize, wxBORDER_NONE), map(10000, 0),
        from(0), to(30)
{
    timer = new timer(this, 1);

    Connect(wxEVT_PAINT, wxPaintEventHandler(move::OnPaint));
    Connect(wxEVT_TIMER, wxCommandEvent(move::OnTimer));
}

void move::start(int ms)
{
    timer->Start(ms);
}

void move::OnTimer(wxCommandEvent& event)
{
    if (to != map.size()-1) {
        from += 1;
        to += 1;
    }
}

void move::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.SetPen(*wxBLACK);
    dc.SetBrush(*wxWHITE);
    wxSize sz = GetClientSize();
    int steps = sz.GetWidth()/(to-from);
    for (int i = 0; i < to-from-1; ++i) {
        wxPoint p1((to-from)*i, sz.GetHeight()-50);
        wxPoint p2((to-from)*(i+1), sz.GetHeight()-50);

        if (map[i+from] == 1|| map[i+from+1] == 1)
            p1.y = p2.y = sz.GetHeight()-100;

        dc.DrawLine(p1, p2);
    }
}

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        wxFrame* win = new wxFrame(NULL, wxID_ANY, wxT("move"), wxDefaultPosition,
                                wxSize(600, 300));
        move* m = new move(win);
        m->Start(100);
        m->Centre();
        m->Show(true);
    }
};
