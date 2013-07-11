///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __UIBASE_H__
#define __UIBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainDialogBase
///////////////////////////////////////////////////////////////////////////////
class MainDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText111;
		wxTextCtrl* m_textCtrlApkTools;
		wxStaticText* m_staticTextApkPackaget;
		wxTextCtrl* m_textCtrlApkPacket;
		wxStaticText* m_staticTextOutputPath;
		wxTextCtrl* m_textCtrlDir;
		wxTextCtrl* m_textCtrlInfo;
		wxButton* m_btnLoad;
		wxButton* m_btnDo;
		wxButton* m_btnDirectory;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnApkLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnApkTool( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnApkDirectory( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxApkTool"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 788,479 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~MainDialogBase();
	
};

#endif //__UIBASE_H__
