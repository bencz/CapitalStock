#ifndef _RESTAUTHENTICATEUSER_H
#define _RESTAUTHENTICATEUSER_H

#include <Wt/WResource>
#include <Wt/Http/Response>

#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>

#include "../../ServiceSession.h"
#include "../../../common/StringHelper.h"

class RestAuthenticateUser : public Wt::WResource
{
private:
	ServiceSession& _serviceSession;

public:
	RestAuthenticateUser(ServiceSession& serviceSession)
		: _serviceSession(serviceSession)
	{
	}

	virtual ~RestAuthenticateUser()
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
		
		// Check if user exist
		auto retCode = _serviceSession.getUserDataAccess().userExist(user, pass);
		
		// Create the Json response 
		Wt::Json::Object obj;
		obj["success"] = retCode;// == _serviceSession.getUserDataAccess().SUCCESS;

		// return serialized json
		response.out() << Wt::Json::serialize(obj);
	}
};

#endif
