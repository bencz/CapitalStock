#ifndef _WEBAPIACCESS_H
#define _WEBAPIACCESS_H

#include <string>

class WebApiAccess
{
public:
	WebApiAccess(const std::string& baseWebApiUrl);

protected:
	enum ErrorLevel
	{
		REQUEST_SUCCESS,
		REQUEST_ERROR
	};
	
	// Make the resquest to WebApi server
	// std::string url = url to be concated with webapi url
	// - example:
	// makeRequest("/auth?user=Alex&pass=MyScretePass");
	ErrorLevel makeRequest(std::string url);

	// Return the response value from webapi request
	std::string getResponseValue();

	// Return error level of "handleMe" method
	ErrorLevel getErrorLevel() const;

	// Set the errorLevel
	void setErrorLevel(ErrorLevel errorlevel);

// Private methods
private:
	static int writer(char *data, unsigned int size, unsigned int nmemb, std::string *buffer_in, void* p);
	int writer_impl(char *data, unsigned int size, unsigned int nmemb, std::string *buffer_in);
	
	void setResponseValue(const std::string& value);

// Private variables
private:
	std::string _baseWebApiUrl;
	std::string _responseValue;
	ErrorLevel _errorLevel;
};

#endif