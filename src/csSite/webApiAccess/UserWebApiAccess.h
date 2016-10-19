#ifndef _USERWEBAPIACCESS_H
#define _USERWEBAPIACCESS_H

#include "WebApiAccess.h"
#include "../../common/WebApiUrl.h"
#include "../../common/StringHelper.h"
//#include "../../common/model/User.h"
//#include "../../common/model/UserDetails.h"
#include "../../common/model/Models.h"

#include <Wt/Utils>

class UserWebApiAccess : public WebApiAccess
{
public:
	UserWebApiAccess(const std::string& baseWebApiUrl)
		: WebApiAccess(baseWebApiUrl)
	{
	}

protected:
	// validate a username and password
	void validadeUser(std::string userName, std::string passWord)
	{
		// Create the URL to make the web request
		std::string urlUserValidation = URL_AUTHENTICATE;
		urlUserValidation += "?username=" + userName;
		urlUserValidation += "&password=" + passWord;

		makeRequest(urlUserValidation);
	}

	// Create the URL for rest api and make the request
	void createNewUser(const std::string username, const std::string password, UserDetails& userDetails)
	{
		// Create the URL to make the web request
		std::string urlUserValidation = URL_CREATEUSER;
		urlUserValidation += "?username=" + username;
		urlUserValidation += "&password=" + password;
		urlUserValidation += "&name=" + Wt::Utils::urlEncode(userDetails.getName());
		urlUserValidation += "&lastname=" + Wt::Utils::urlEncode(userDetails.getLastname());
		urlUserValidation += "&age=" + std::to_string(userDetails.getAge());
		urlUserValidation += "&email=" + Wt::Utils::urlEncode(userDetails.getEmail());
		urlUserValidation += "&country=" + Wt::Utils::urlEncode(userDetails.getCountry());
		urlUserValidation += "&city=" + Wt::Utils::urlEncode(userDetails.getCity());
		makeRequest(urlUserValidation);
	}

	// Get total of cash of user
	void getTotalCashOfUser(const std::string username, const std::string password)
	{
		std::string urlUserCash = URL_GETCASH;
		urlUserCash += "?username=" + username;
		urlUserCash += "&password=" + password;
		makeRequest(urlUserCash);
	}

	// Set user last access as now
	void setLastAccesAsNow(const std::string username, const std::string password)
	{
		std::string urlSetLastAccess = URL_SETLASTACCESS;
		urlSetLastAccess += "?username=" + username;
		urlSetLastAccess += "&password=" + password;
		makeRequest(urlSetLastAccess);
	}

	// Get the details of user
	void requestUserDetails(const std::string username, const std::string password)
	{
		std::string urlUserDetails = URL_GETUSERDETAILS;
		urlUserDetails += "?username=" + username;
		urlUserDetails += "&password=" + password;
		makeRequest(urlUserDetails);
	}
};

#endif