// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <string>

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame: public wxFrame
{
	public:
		MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	private:
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnPlay(wxCommandEvent& event);
		
		void checkWin(const wxString&);
		void setWin(const wxString&);
		void reset();
		
		int xScore, oScore;
    
		wxButton *playBtns[3][3];
		wxButton *resetBtn;
    
		wxStaticText *staticScores;
    
		wxString currTurn;
		
		bool gameOver;
    
    
		wxDECLARE_EVENT_TABLE();
};

const int ID_B[][3]{
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8} };

enum
{
    ID_Br = 9
};


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_BUTTON(wxID_ANY, MyFrame::OnPlay) 
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
    MyFrame *frame = new MyFrame( "Tic Tac Toe", wxPoint(50, 50), wxSize(300, 425) );
    frame->SetIcon(wxIcon(wxT("tttIcon.xpm"), wxBITMAP_TYPE_ICO));
    frame->SetMinSize(wxSize(300, 425));
    frame->Show( true );
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    
    xScore = 0;
    oScore = 0;
    currTurn = "X";
    gameOver = false;
    
    SetStatusText( currTurn + " Turn");
    
    //place scores text
    staticScores = new wxStaticText(this, wxID_ANY,
		wxT("X  Score: 0\nO Score: 0"), wxPoint(40, 25), wxSize(75, 75), 0);
    
    
    //place play buttons
    playBtns[0][0] = new wxButton(this, ID_B[0][0], wxT(" "), wxPoint(0, 100), 
		wxSize(100, 100));
	
	playBtns[0][1] = new wxButton(this, ID_B[0][1], wxT(" "), wxPoint(100, 100), 
		wxSize(100, 100));
		
	playBtns[0][2] = new wxButton(this, ID_B[0][2], wxT(" "), wxPoint(200, 100), 
		wxSize(100, 100));
		
    playBtns[1][0] = new wxButton(this, ID_B[1][0], wxT(" "), wxPoint(0, 200), 
		wxSize(100, 100));
	
	playBtns[1][1] = new wxButton(this, ID_B[1][1], wxT(" "), wxPoint(100, 200), 
		wxSize(100, 100));
		
	playBtns[1][2] = new wxButton(this, ID_B[1][2], wxT(" "), wxPoint(200, 200), 
		wxSize(100, 100));
		
    playBtns[2][0] = new wxButton(this, ID_B[2][0], wxT(" "), wxPoint(0, 300), 
		wxSize(100, 100));
	
	playBtns[2][1] = new wxButton(this, ID_B[2][1], wxT(" "), wxPoint(100, 300), 
		wxSize(100, 100));
		
	playBtns[2][2] = new wxButton(this, ID_B[2][2], wxT(" "), wxPoint(200, 300), 
		wxSize(100, 100));
		
	//place reset btn
	resetBtn = new wxButton(this, ID_Br, wxT("Reset"), wxPoint(200, 25), 
		wxSize(100, 50));
		
    
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "Written by Hadibus, 2016\ngithub.com/hadibus",
                  "About Tic Tac Toe", wxOK | wxICON_INFORMATION );
}

void MyFrame::OnPlay(wxCommandEvent& event)
{
	auto id = event.GetId();
	
	if(!gameOver)
	for(int col = 0; col < 3; col++)
		for(int row = 0; row < 3; row++)
			if (id == ID_B[row][col] && playBtns[row][col]->GetLabel() == " ")
				playBtns[row][col]->SetLabel(currTurn);
				
	
	//if reset, clear board
	if (id == ID_Br)
		reset();
		
	checkWin(currTurn);
	if (!gameOver)
	{
		currTurn = currTurn == "X" ? "O" : "X";
		SetStatusText( currTurn + " Turn");
	}
}

void MyFrame::checkWin(const wxString & symbol)
{
	if(gameOver) return;
	//check rows
	for(int row = 0; row < 3; row++)
		if(playBtns[row][0]->GetLabel() == symbol 
			&& playBtns[row][1]->GetLabel() == symbol
			&& playBtns[row][2]->GetLabel() == symbol)
		{
			setWin(symbol);
			return;
		}
	
	//check cols
	for(int col = 0; col < 3; col++)
		if(playBtns[0][col]->GetLabel() == symbol
			&& playBtns[1][col]->GetLabel() == symbol
			&& playBtns[2][col]->GetLabel() == symbol)
		{
			setWin(symbol);
			return;
		}
	
	//check diagonals
	if(playBtns[0][0]->GetLabel() == symbol
		&& playBtns[1][1]->GetLabel() == symbol
		&& playBtns[2][2]->GetLabel() == symbol)
	{
		setWin(symbol);
			return;
	}
		
	if(playBtns[0][2]->GetLabel() == symbol
		&& playBtns[1][1]->GetLabel() == symbol
		&& playBtns[2][0]->GetLabel() == symbol)
	{
		setWin(symbol);
			return;
	}
	
	//check if board is not full
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if(playBtns[row][col]->GetLabel() == " ")
				return;
				
	SetStatusText( "No winner...");
	gameOver = true;
	
}

void MyFrame::setWin(const wxString & symbol)
{
		gameOver = true;
		SetStatusText( symbol + " wins!");
		//change text for winCount
		if(symbol == "X")
			xScore++;
		else if (symbol == "O")
			oScore++;
			
		wxString xScoreStr = wxString::Format(wxT("%i"), xScore);
		wxString oScoreStr = wxString::Format(wxT("%i"), oScore);
			
		staticScores->SetLabel("X  Score: " + xScoreStr
			+ "\nO Score: " + oScoreStr);;

}

void MyFrame::reset()
{
	for(int col = 0; col < 3; col++)
		for(int row = 0; row < 3; row++)
			playBtns[row][col]->SetLabel(" ");
	
	gameOver = false;
}
