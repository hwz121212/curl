#include <curl/curl.h>
#include <stdio.h>  
//#include <iostream>  
#include <Windows.h>   




#pragma comment(lib, "libcurl.lib")  
#pragma comment(lib, "wldap32.lib") 
#pragma comment(lib, "ws2_32.lib") 
#pragma comment(lib, "winmm.lib")     

using namespace std;  

size_t write_data(char *buffer,size_t size, size_t nitems,void *outstream)  
{  
	int written = fwrite(buffer, size, nitems, (FILE*)outstream);  
	return written;  
}  



void  anaylize_data()
{
}


 int main(void)  
 {
	CURL *pCurl;    
	FILE* pFile = fopen( "myxml.xml", "wb" );  
	pCurl = curl_easy_init(); 
	curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)pFile); 
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(pCurl, CURLOPT_URL, "https://www.baidu.com/?tn=80035161_1_dg");  
	curl_easy_perform(pCurl);  
	fclose(pFile);  
	curl_easy_cleanup( pCurl );  

	CURL *curl;
	CURLcode res;    
	curl = curl_easy_init();    

	if(curl)  
	{  
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com/?tn=80035161_1_dg");    
		res = curl_easy_perform(curl);    
		curl_easy_cleanup(curl);    
		curl_global_init(CURL_GLOBAL_ALL);   
	}  
	system("pause");
	anaylize_data();

	return 0;

}