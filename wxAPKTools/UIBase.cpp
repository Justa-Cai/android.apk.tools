///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "UIBase.h"

///////////////////////////////////////////////////////////////////////////

MainDialogBase::MainDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText111 = new wxStaticText( this, wxID_ANY, wxT("APK TOOLS:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText111->Wrap( -1 );
	bSizer111->Add( m_staticText111, 0, wxALL, 5 );
	
	m_textCtrlApkTools = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_textCtrlApkTools, 1, wxALL, 5 );
	
	
	bSizer5->Add( bSizer111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextApkPackaget = new wxStaticText( this, wxID_ANY, wxT("APK Path:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticTextApkPackaget->Wrap( -1 );
	bSizer11->Add( m_staticTextApkPackaget, 0, wxALL, 5 );
	
	m_textCtrlApkPacket = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_textCtrlApkPacket, 1, wxALL, 5 );
	
	
	bSizer5->Add( bSizer11, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer112;
	bSizer112 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextOutputPath = new wxStaticText( this, wxID_ANY, wxT("OUTPUT Path:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticTextOutputPath->Wrap( -1 );
	bSizer112->Add( m_staticTextOutputPath, 0, wxALL, 5 );
	
	m_textCtrlDir = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer112->Add( m_textCtrlDir, 1, wxALL, 5 );
	
	
	bSizer5->Add( bSizer112, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer151;
	bSizer151 = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	bSizer151->Add( m_textCtrlInfo, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer5->Add( bSizer151, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnLoad = new wxButton( this, wxID_ANY, wxT("Apk Load"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_btnLoad, 0, wxALL, 5 );
	
	m_btnDo = new wxButton( this, wxID_ANY, wxT("APKTOOL"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_btnDo, 0, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5 );
	
	m_btnDirectory = new wxButton( this, wxID_ANY, wxT("Directory"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_btnDirectory, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	bSizer15->Add( bSizer19, 0, wxEXPAND|wxALIGN_BOTTOM, 5 );
	
	
	bSizer5->Add( bSizer15, 0, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_btnLoad->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::OnApkLoad ), NULL, this );
	m_btnDo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::OnApkTool ), NULL, this );
	m_btnDirectory->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::OnApkDirectory ), NULL, this );
}

MainDialogBase::~MainDialogBase()
{
	// Disconnect Events
	m_btnLoad->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::OnApkLoad ), NULL, this );
	m_btnDo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::OnApkTool ), NULL, this );
	m_btnDirectory->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::OnApkDirectory ), NULL, this );
	
}
