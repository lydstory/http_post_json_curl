#include "httpclient.h"
#include <curl/curl.h>
#define m_bDebug  0
CHttpClient::CHttpClient()
{

}

static size_t OnWriteData(void *buffer, size_t size, size_t nmemb, void *lpVoid)
{
    std::string *str = dynamic_cast<std::string *>((std::string *)lpVoid);
    if (NULL == str || NULL == buffer)
    {
        return -1;
    }

    char *pData = (char *)buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}

int CHttpClient::Put(
    const std::string &strUrl,
    const std::string &strPost,
    std::string &strResponse,
    int timeout )
{

#ifdef ENCRYPT_URL_POST
//	string encryptedPost = encrypt_postdata(strPost);
#endif
    string encryptedPost = strPost;// by nf 180507
    CURLcode res;
    std::string useragent = "g_useragent";
    CURL *curl = curl_easy_init();
    if (NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if (m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
     //   curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
    }

    curl_easy_setopt(curl, CURLOPT_USERAGENT, useragent.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, encryptedPost.c_str());
    //curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookiefile);
    //curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookiefile);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    //返回数据
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

    //curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout);//连接等待时间
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);//传输时间

    //ca
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
//		LOG("curl_easy_perform 没有返回CURLE_OK");
//		LOG2("错误信息", curl_easy_strerror(res));
        strResponse.clear();
        curl_easy_cleanup(curl);
        return -1;

    }
    else
    {//res:CURLE_OK

        long responseCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
//		LOG2("返回响应状态",responseCode);
        if (responseCode < 200 || responseCode >= 300)
        {
            strResponse.clear();
            curl_easy_cleanup(curl);
            return responseCode;// by nf 180525 -1;
        }
        //成功的
        curl_easy_cleanup(curl);
        if (strResponse.size()==0)
        {
//			LOG("返回数据为空，请检查代码");
        }
        else
        {
        //解密
    #ifdef ENCRYPT_URL_POST
    //		decrypt_response(strResponse);
    #endif
//			LOG2("返回数据", strResponse);
        }

    }

    return res;
}
