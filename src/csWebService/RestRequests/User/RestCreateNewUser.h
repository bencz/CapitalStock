#ifndef _RESTCREATENEWUSER_H
#define _RESTCREATENEWUSER_H

#include <string>
#include <Wt/WResource>
#include <Wt/Http/Response>

#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>

#include "../../ServiceSession.h"
#include "../../../common/StringHelper.h"

class RestCreateNewUser : public Wt::WResource
{
private:
	ServiceSession& _serviceSession;

public:
	RestCreateNewUser(ServiceSession& serviceSession)
		: _serviceSession(serviceSession)
	{
	}

	virtual ~RestCreateNewUser()
	{
		beingDeleted();
	}

protected:
	virtual void handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
	{
		// Get url parameters
		auto userParameter = request.getParameterValues("username");
		auto passParameter = request.getParameterValues("password");
		auto nameParameter = request.getParameterValues("name");
		auto lastNameParammeter = request.getParameterValues("lastname");
		auto ageParammeter = request.getParameterValues("age");
		auto emailParameter = request.getParameterValues("email");
		auto countryParameter = request.getParameterValues("country");
		auto cityParameter = request.getParameterValues("city");

		std::string username = "";
		std::string password = "";
		std::string name = "";
		std::string lastName = "";
		std::string email = "";
		std::string country = "";
		std::string city = "";
		int age = 0;

		// Check if every parameter exist
		// Check username parameter
		if (!userParameter.empty())
			username = userParameter[0];

		// check password parameter
		if (!passParameter.empty())
			password = passParameter[0];

		// check name parameter
		if (!nameParameter.empty())
			name = nameParameter[0];

		// check lastname parameter
		if (!lastNameParammeter.empty())
			lastName = lastNameParammeter[0];

		// check email parameter
		if (!emailParameter.empty())
			email = emailParameter[0];

		// check email parameter
		if (!countryParameter.empty())
			country = countryParameter[0];

		// check email parameter
		if (!cityParameter.empty())
			city = cityParameter[0];

		// check age parameter
		if (!ageParammeter.empty())
			age = toInt(ageParammeter[0]);

		// Create the new user
		auto retCode = _serviceSession.getUserDataAccess().createNewUser(username, password, User::AccessLevel::NormalUser);
		if (retCode != UserDataAccess::NewUserErrorLevel::SUCCESS)
		{
			// return the error code
			Wt::Json::Object obj;
			obj["reasonCode"] = (int)retCode;
			obj["reasonText"] = Wt::Json::Value(_serviceSession.getUserDataAccess().getNewUserErrorLevelText(retCode));
			obj["success"] = false;
			response.out() << Wt::Json::serialize(obj);
			return;
		}

		// User created with success, now, we will create the user details
		auto usrDetRetCode = _serviceSession.getUserDataAccess().createUserDetails(username, password, name, lastName, email, country, city, age);
		if (usrDetRetCode != UserDataAccess::NewUserErrorLevel::SUCCESS)
		{
			// return the error code
			Wt::Json::Object obj;
			obj["reasonCode"] = (int)usrDetRetCode;
			obj["reasonText"] = Wt::Json::Value(_serviceSession.getUserDataAccess().getNewUserErrorLevelText(usrDetRetCode));
			obj["success"] = false;
			response.out() << Wt::Json::serialize(obj);
			return;
		}

		// Everything is fine here! :)
		Wt::Json::Object obj;
		obj["reasonCode"] = (int)usrDetRetCode;
		obj["reasonText"] = Wt::Json::Value(_serviceSession.getUserDataAccess().getNewUserErrorLevelText(UserDataAccess::NewUserErrorLevel::SUCCESS));
		obj["success"] = true;

		// return serialized json
		response.out() << Wt::Json::serialize(obj);
	}
};

#endif
