#include<windows.h>
#include<Wininet.h>
#include<iostream>
#include<fstream>
#include<string>
#pragma comment(lib,"WinInet.lib")
using namespace std;
int main()
{
	HINTERNET hINet, hHttpFile;               
	char szSizeBuffer[32];
	DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);

	hINet = InternetOpen("IE6.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );    //InternetOpen��ʼ��WININET.DLL
	cout<<"������url,��Ҫ����http://,��"<<endl;

	string url;
	cin>>url;
	if ( !hINet )
	{
		cout << "InternetOpen fail" << endl;
		return 1;
	}
	hHttpFile = InternetOpenUrl(hINet, url.c_str(), NULL, 0, 0, 0);  //����������ӵ�һ������������ϲ�����ӷ������϶�ȡ����
	if(!hHttpFile)
	{
		cout << "error open url" << endl;
		return 1;
	}
	BOOL bQuery = HttpQueryInfo(hHttpFile,
		HTTP_QUERY_CONTENT_LENGTH,
		szSizeBuffer,
		&dwLengthSizeBuffer, NULL); //�õ������ļ�����Ϣ
	if(bQuery ==false)
	{
		InternetCloseHandle(hINet); 
		cout << "error query info" << endl;
		return 3;
	}
	int FileSize=atol(szSizeBuffer);    //atol�������ַ���ת���ɳ�������
	string revData;
	revData.resize(FileSize);

	DWORD dwBytesRead;
	BOOL bRead = InternetReadFile(hHttpFile, &revData[0], FileSize, &dwBytesRead);     //web���������InternetReadFile��ѭ�� ����ͣ�ش�Internet�϶������ݿ顣

	if(!bRead)
	{
		cout << "error to read file" << endl;
		return 4;
	}
	ofstream   out_file("WebCapture.txt");   
	out_file << revData;              //������ļ�
	InternetCloseHandle(hHttpFile);   //�رվ��
	InternetCloseHandle(hINet);

	cout << "ץȡ�ɹ�!/n" << endl;
	return 0;
}