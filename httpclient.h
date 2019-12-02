#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
#include <iostream>
#include <string>
using namespace std;

class CHttpClient
{
public:
    CHttpClient();
    int Put(
        const std::string &strUrl,
        const std::string &strPost,
        std::string &strResponse,
        int timeout );
};

#endif // HTTPCLIENT_H
