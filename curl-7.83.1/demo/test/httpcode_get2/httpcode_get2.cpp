
#include <afxinet.h>
#include <afxwin.h>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

#define  MAX_LEN 1024


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
		return nRetCode;
	}



	ifstream fin("url.txt");
	CString m_html;
	CString m_url;

	std::cout << "open url.txt" << std::endl;
	char outfile[_MAX_PATH];
	char *sUrl = new char[MAX_LEN];
	int i = 0;
	while (!fin.eof())
	{
		fin.getline(sUrl, MAX_LEN);
		if (strlen(sUrl) <  3)
		{
			std::cout << "invalid url" << std::endl;
			break;
		}

		i++;
		std::cout << "Open URL "  << i << ": ";
		std::cout << sUrl << std::endl;
		m_url.Format("%s", sUrl);

		//以下是获取网页内容
		CInternetSession httpSession;
		CInternetFile* htmlFile = (CInternetFile*)httpSession.OpenURL(m_url);
		if (htmlFile == NULL)
		{
			std::cout << "open url failed" << std::endl;
			break;
		}
		CString content;

		std::cout << "ReadString" << std::endl;
		sprintf(outfile, "%d.txt", i);
		ofstream fout(outfile);
		while (htmlFile->ReadString(content))
		{	
			fout << content << '\n';	
		}
		fout.close();
		htmlFile->Close();
		httpSession.Close();
	}


	std::cout << "finish! ";
	

	return nRetCode;
}



