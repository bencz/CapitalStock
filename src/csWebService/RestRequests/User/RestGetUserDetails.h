#ifndef _GETUSERDETAILS_H
#define _GETUSERDETAILS_H

#include <Wt/WResource>
#include <Wt/Http/Response>

#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>

#include "../../ServiceSession.h"
#include "../../../common/StringHelper.h"

class RestGetUserDetails : public Wt::WResource
{
private:
	ServiceSession& _serviceSession;

public:
	RestGetUserDetails(ServiceSession& serviceSession)
		: _serviceSession(serviceSession)
	{
	}

	virtual ~RestGetUserDetails()
	{
		beingDeleted();
	}

protected:
	virtual void handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
	{
		// Get url parameters
		auto userParameter = request.getParameterValues("username");
		auto passParameter = request.getParameterValues("password");

		std::string user = "";
		std::string pass = "";

		// Check if every parameter exist
		if (!userParameter.empty())
			user = userParameter[0];
		if (!passParameter.empty())
			pass = passParameter[0];

		Wt::Json::Object obj;

		// Check if user exist
		auto userExist = _serviceSession.getUserDataAccess().userExist(user, pass);
		if (!userExist)
		{
			obj["success"] = false;
			obj["reason"] = Wt::Json::Value(Wt::WString("User not exist"));
		}
		else
		{
			UserDetails* userDetails = new UserDetails();
			_serviceSession.getUserDataAccess().getUserDetails(user, pass, userDetails);
			obj["age"] = Wt::Json::Value(userDetails->getAge());
			obj["city"] = Wt::Json::Value(Wt::WString(userDetails->getCity()));
			obj["country"] = Wt::Json::Value(Wt::WString(userDetails->getCountry()));
			obj["email"] = Wt::Json::Value(Wt::WString(userDetails->getEmail()));
			obj["lastname"] = Wt::Json::Value(Wt::WString(userDetails->getLastname()));
			obj["name"] = Wt::Json::Value(Wt::WString(userDetails->getName()));
			obj["success"] = true;
			delete userDetails;
		}

		// return serialized json
		response.out() << Wt::Json::serialize(obj);
	}
};

#endif
