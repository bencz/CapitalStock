#ifndef _RESTGETSTOCKSTABLE_H
#define _RESTGETSTOCKSTABLE_H

#include <Wt/WResource>
#include <Wt/Http/Response>

#include <Wt/Json/Array>
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>

#include "../../ServiceSession.h"
#include "../../../common/StringHelper.h"

class RestGetStocksTable : public Wt::WResource
{
private:
	ServiceSession& _serviceSession;

public:
	RestGetStocksTable(ServiceSession& serviceSession)
		: _serviceSession(serviceSession)
	{
	}

	virtual ~RestGetStocksTable()
	{
		beingDeleted();
	}

protected:
	virtual void handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
	{
		// Get url parameters
		auto listLimitParameter = request.getParameterValues("limit");

		int limit = 0;

		// Check if every parameter exist
		if (!listLimitParameter.empty())
			limit = toInt(listLimitParameter[0]);
		

		// Create the Json response 
		Wt::Json::Object obj;
		Wt::Json::Array arr;
		// Get the Stocks
		auto retList = _serviceSession.getStockDataAccess().getStocks(limit);
		for (std::vector<Stock>::iterator it = retList.begin();it != retList.end(); ++it)
		{
			arr.push_back(Wt::Json::Type::ObjectType);
			Wt::Json::Object& tmp = arr.back();
			tmp["stockid"] = Wt::Json::Value((it)->getStockId());
			tmp["stockcode"] = Wt::Json::Value(Wt::WString((it)->getStockCode()));
			tmp["companyName"] = Wt::Json::Value(Wt::WString((it)->getCompanyName()));
			tmp["country"] = Wt::Json::Value(Wt::WString((it)->getCountry()));
			tmp["lastUpdate"] = Wt::Json::Value(Wt::WString((it)->getLastUpdate().toString("ddMMyy")));
			tmp["lastSalePrice"] = Wt::Json::Value((it)->getLastSalePrice());
			tmp["priceVolume"] = Wt::Json::Value((it)->getPriceValume());
			tmp["valueChange"] = Wt::Json::Value((it)->getValueChange());
			tmp["changePercent"] = Wt::Json::Value((it)->getChangePercent());
		}
		
		// return serialized json
		response.out() << Wt::Json::serialize(arr);
	}
};

#endif
