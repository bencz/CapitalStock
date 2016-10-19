#include "WebApiAccess.h"
#include "../../common/StringHelper.h"

#include <cstdlib>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>

WebApiAccess::WebApiAccess(const std::string& baseWebApiUrl)
	: _baseWebApiUrl(baseWebApiUrl)
{
	// Check if webapi url ends with '/'
	if (endsWith(_baseWebApiUrl, std::string("/")))
		_baseWebApiUrl = std::string(_baseWebApiUrl, 0, _baseWebApiUrl.size() - 1); // Remove the last "/" from webApiUrl
}

WebApiAccess::ErrorLevel WebApiAccess::makeRequest(std::string url)
{
	// create the URL with the request
	std::string urlString = _baseWebApiUrl + url;

	// temporary variable than hold the returned json
	std::string temp;

	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL; 
	curl_slist_append(headers, "Accept: application/json");
	curl_slist_append(headers, "Content-Type: application/json");
	curl_slist_append(headers, "charsets: utf-8");
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, urlString.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &temp);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebApiAccess::writer);
		res = curl_easy_perform(curl);

		if (CURLE_OK == res)
		{
			char *ct;
			res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
			setResponseValue(temp);
			setErrorLevel(ErrorLevel::REQUEST_SUCCESS);
		}
		else
			setErrorLevel(ErrorLevel::REQUEST_ERROR);
	}
	else
		setErrorLevel(ErrorLevel::REQUEST_ERROR);
	return getErrorLevel();
}


std::string WebApiAccess::getResponseValue()
{
	return _responseValue;
}

void WebApiAccess::setResponseValue(const std::string& value)
{
	_responseValue = value;
}

WebApiAccess::ErrorLevel WebApiAccess::getErrorLevel() const
{
	return _errorLevel;
}

void WebApiAccess::setErrorLevel(WebApiAccess::ErrorLevel errorlevel)
{
	_errorLevel = errorlevel;
}

int WebApiAccess::writer(char *data, unsigned int size, unsigned int nmemb, std::string* buffer_in, void* p)
{
	return static_cast<WebApiAccess*>(p)->writer_impl(data, size, nmemb, buffer_in);
}

int WebApiAccess::writer_impl(char *data, unsigned int size, unsigned int nmemb, std::string* buffer_in)
{
	if (buffer_in != NULL)
	{
		buffer_in->append(data, size * nmemb);
		return size * nmemb;
	}
	return 0;
}