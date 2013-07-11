#include <wx/wx.h>
#include <wx/process.h>
#include <wx/utils.h>
#include <wx/msw/registry.h>
#include <wx/dnd.h>
#include "UIBase.h"
/////////////////////////////////////////////////////////
// event
/////////////////////////////////////////////////////////

enum CustomEventId
{
	ENUM_CUSTOMEVENT_ID_Id1=7000,
	ENUM_CUSTOMEVENT_ID_Id2,
	ENUM_CUSTOMEVENT_ID_Id3
};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_LOCAL_EVENT_TYPE(ENUM_CUSTOMEVENT_INFO, ENUM_CUSTOMEVENT_ID_Id1)
DECLARE_LOCAL_EVENT_TYPE(ENUM_CUSTOMEVENT_EXIT, ENUM_CUSTOMEVENT_ID_Id2)
DECLARE_LOCAL_EVENT_TYPE(ENUM_CUSTOMEVENT_DROPFILE, ENUM_CUSTOMEVENT_ID_Id2)
END_DECLARE_EVENT_TYPES()

DEFINE_LOCAL_EVENT_TYPE(ENUM_CUSTOMEVENT_INFO)
DEFINE_LOCAL_EVENT_TYPE(ENUM_CUSTOMEVENT_EXIT)
DEFINE_LOCAL_EVENT_TYPE(ENUM_CUSTOMEVENT_DROPFILE)

/////////////////////////////////////////////////////////
// thread 
/////////////////////////////////////////////////////////
class CApkProcess:public wxProcess
{
public:
	CApkProcess(wxWindow *pWindow)
	{
		Redirect();
		m_pWindow = pWindow;
	}

	virtual void OnTerminate (int pid, int status)
	{
		if (m_pWindow) 
		{
			wxCommandEvent evt(ENUM_CUSTOMEVENT_INFO);
			evt.SetString("* Progress EXIT!\n");
			wxPostEvent(m_pWindow->GetEventHandler(), evt);
		}
	}
public:
	wxWindow *m_pWindow;
};

class CApkWorkThread:public wxThread
{
public:
	CApkWorkThread(wxWindow *pWindow, wxString apktoolPath, wxString apkPacketPath, wxString apkDir)
		:wxThread(wxTHREAD_JOINABLE)
	{
		Create();
		m_pWindow = pWindow;
		m_pProcessApk = new CApkProcess(m_pWindow);
		m_strCmds.Printf(wxT("%s d -f %s %s"), apktoolPath, apkPacketPath, apkDir);
		wxFileName f(apktoolPath);
		wxSetWorkingDirectory(f.GetPath());

		m_nPid =  wxExecute(m_strCmds, wxEXEC_ASYNC|wxEXEC_HIDE_CONSOLE, m_pProcessApk, NULL);
	}

	virtual void * Entry() 
	{
		if (m_nPid<=0) {
			SendInfo("Can't Create Process!\nCMDS:" + m_strCmds + "\n");
			return NULL;
		}
		SendInfo("* " + m_strCmds + "\n");

		wxInputStream *pErrorInput = m_pProcessApk->GetErrorStream();
		wxInputStream *pStandInput = m_pProcessApk->GetInputStream();
		// check process output
		while(!TestDestroy()) {


			if (m_pProcessApk->IsErrorAvailable()) {
				wxCharBuffer buffer(4096);
				size_t offset = 0;
				while(pErrorInput->CanRead())
				{
					pErrorInput->Read(buffer.data()+offset, 1);
					offset++;
				}
				buffer.shrink(offset);
				SendInfo(buffer);
			}

			if (m_pProcessApk->IsInputAvailable()) {
				wxCharBuffer buffer(4096);
				size_t offset = 0;
				while(pStandInput->CanRead())
				{
					pStandInput->Read(buffer.data()+offset, 1);
					offset++;
				}
				buffer.shrink(offset);

				SendInfo(buffer);
			}

			if (!m_pProcessApk->Exists(m_nPid))
				break;
			Sleep(100);
		}

		if (m_pProcessApk->Exists(m_nPid))
			m_pProcessApk->Kill(m_nPid, wxSIGKILL);

		delete m_pProcessApk;
		return NULL;
	}


	void OnExit()
	{
		SendInfo("* Thread exit\n");
		wxCommandEvent evt(ENUM_CUSTOMEVENT_EXIT);
		wxPostEvent(m_pWindow->GetEventHandler(), evt);
	}

	void SendInfo( wxString str )
	{
		wxCommandEvent evt(ENUM_CUSTOMEVENT_INFO);
		evt.SetString(str);
		wxPostEvent(m_pWindow->GetEventHandler(), evt);
	}


private:
	wxWindow *m_pWindow;
	long m_nPid;
	wxString m_strCmds;
	CApkProcess *m_pProcessApk;
};

/////////////////////////////////////////////////////////
// ui 
/////////////////////////////////////////////////////////
class MainDialogFileDrog: public wxFileDropTarget
{
public:
	MainDialogFileDrog (wxWindow *pWindow)
		:m_pWindow(pWindow)
	{

	}
public:
	bool OnDropFiles( wxCoord x, wxCoord y, const wxArrayString& filenames ) 
	{
		wxCommandEvent evt(ENUM_CUSTOMEVENT_DROPFILE);
		evt.SetString(filenames.Item(0));
		wxPostEvent(m_pWindow->GetEventHandler(), evt);
		return true;
	}
private:
	wxWindow *m_pWindow;

};
class MainDialog : public MainDialogBase
{
public:
	MainDialog(wxWindow* parent):
	  MainDialogBase(parent),
		  m_droptarget(this)
	  {
		 m_textCtrlApkTools->SetValue(wxT("d:\\work\\android\\android.apk.tools\\apktool\\apktool.bat"));
		 m_pThread = NULL;
		 SetDropTarget(&m_droptarget);
	  }

	  virtual void OnApkLoad( wxCommandEvent& event ) 
	  {
		  wxString filename = wxFileSelector(wxT("ÇëÑ¡Ôñ APKÂ·¾¶"), wxEmptyString, wxEmptyString, wxEmptyString, wxT("APK files (*.apk)|*.apk"));
		  if (!filename.IsEmpty())
		  {
			  SetApkFile(filename);
		  }
	  }

	  virtual void OnApkTool( wxCommandEvent& event ) 
	  {
		  if (m_pThread)
			  return ;
		  m_pThread = new CApkWorkThread(this, m_textCtrlApkTools->GetValue(),
			  m_textCtrlApkPacket->GetValue(), m_textCtrlDir->GetValue());
		  m_pThread->Run();
	  }

	  virtual void OnApkDirectory( wxCommandEvent& event ) 
	  {
		  wxString path;
		  path = "explorer " + m_textCtrlDir->GetValue();
		  wxExecute(path);
	  }

	  void OnShowInfo(wxCommandEvent& event) 
	  {
		  m_textCtrlInfo->AppendText(event.GetString());
	  }


	  void OnThreadExit(wxCommandEvent& event) 
	  {
		  if (m_pThread)
		  {
			  m_pThread->Delete();
			  delete m_pThread;
			  m_pThread = NULL;
		  }
	  }

	  void OnDropFile(wxCommandEvent &event)
	  {
		  SetApkFile(event.GetString());
	  }

	  void SetApkFile(wxString& filename)
	  {
		  m_textCtrlApkPacket->SetValue(filename);
		  wxFileName fn(filename);
		  m_textCtrlDir->SetValue(fn.GetPath()+ "\\" + fn.GetName() + "\\");
	  }

private:
	DECLARE_EVENT_TABLE()
	CApkWorkThread *m_pThread;
	MainDialogFileDrog m_droptarget;
};

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};
wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
	//CMyFrame *frame = new CMyFrame(NULL);
	//frame->Show( true );
	MainDialog dlg(NULL);
	dlg.ShowModal();
	return false;
}

BEGIN_EVENT_TABLE(MainDialog, wxDialog)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_INFO, MainDialog::OnShowInfo)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_EXIT, MainDialog::OnThreadExit)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_DROPFILE, MainDialog::OnDropFile)
END_EVENT_TABLE()