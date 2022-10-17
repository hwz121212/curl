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

	hINet = InternetOpen("IE6.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );    //InternetOpen初始化WININET.DLL
	cout<<"请输入url,不要忘记http://,亲"<<endl;

	string url;
	cin>>url;
	if ( !hINet )
	{
		cout << "InternetOpen fail" << endl;
		return 1;
	}
	hHttpFile = InternetOpenUrl(hINet, url.c_str(), NULL, 0, 0, 0);  //这个函数连接到一个网络服务器上并且最被从服务器上读取数据
	if(!hHttpFile)
	{
		cout << "error open url" << endl;
		return 1;
	}
	BOOL bQuery = HttpQueryInfo(hHttpFile,
		HTTP_QUERY_CONTENT_LENGTH,
		szSizeBuffer,
		&dwLengthSizeBuffer, NULL); //得到关于文件的信息
	if(bQuery ==false)
	{
		InternetCloseHandle(hINet); 
		cout << "error query info" << endl;
		return 3;
	}
	int FileSize=atol(szSizeBuffer);    //atol函数把字符串转换成长整型数
	string revData;
	revData.resize(FileSize);

	DWORD dwBytesRead;
	BOOL bRead = InternetReadFile(hHttpFile, &revData[0], FileSize, &dwBytesRead);     //web浏览器将在InternetReadFile上循环 ，不停地从Internet上读入数据块。

	if(!bRead)
	{
		cout << "error to read file" << endl;
		return 4;
	}
	ofstream   out_file("WebCapture.txt");   
	out_file << revData;              //输出到文件
	InternetCloseHandle(hHttpFile);   //关闭句柄
	InternetCloseHandle(hINet);

	cout << "抓取成功!/n" << endl;
	return 0;
}