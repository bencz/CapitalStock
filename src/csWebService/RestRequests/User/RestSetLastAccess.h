#ifndef _RESTGETSTOCKLIST_H
#define _RESTGETSTOCKLIST_H

#include <Wt/WResource>
#include <Wt/Http/Response>

#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>

#include "../../ServiceSession.h"
#include "../../../common/StringHelper.h"

class RestSetLastAccess : public Wt::WResource
{
private:
	ServiceSession& _serviceSession;

public:
	RestSetLastAccess(ServiceSession& serviceSession)
		: _serviceSession(serviceSession)
	{
	}

	virtual ~RestSetLastAccess()
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
			auto totalMoney = _serviceSession.getUserDataAccess().setLastAccess(user, pass);
			obj["success"] = true;
		}

		// return serialized json
		response.out() << Wt::Json::serialize(obj);
	}
};

#endif
