#ifndef _GETTOTALCASH_H
#define _GETTOTALCASH_H

#include <Wt/WResource>
#include <Wt/Http/Response>

#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>

#include "../../ServiceSession.h"
#include "../../../common/StringHelper.h"

class RestGetTotalCash : public Wt::WResource
{
private:
	ServiceSession& _serviceSession;

public:
	RestGetTotalCash(ServiceSession& serviceSession)
		: _serviceSession(serviceSession)
	{
	}

	virtual ~RestGetTotalCash()
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
			auto totalMoney = _serviceSession.getUserDataAccess().getTotalCash(user, pass);
			obj["value"] = Wt::Json::Value(totalMoney);
			obj["success"] = true;
		}

		// return serialized json
		response.out() << Wt::Json::serialize(obj);
	}
};

#endif
