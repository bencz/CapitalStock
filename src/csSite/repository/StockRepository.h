#ifndef _STOCKREPOSITORY_H
#define _STOCKREPOSITORY_H

#include <string>
#include <Wt/Json/Array>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/WDateTime>

#include "../webApiAccess/StockWebApiAccess.h"
#include "../../common/StringHelper.h"
//#include "../../common/model/Stock.h"
#include "../../common/model/Models.h"

class StockRepository : public StockWebApiAccess
{
public:
	StockRepository(const std::string& baseWebApiUr)
		: StockWebApiAccess(baseWebApiUr)
	{
	}

	// get the list with details of stocks
	// - int limit = how much itens you want
	std::vector<Stock> getListStock(int limit)
	{
		std::vector<Stock> retVector;
		// execute the method to criate and execute the webapi call
		getStockList(limit);
		if (this->getErrorLevel() != this->REQUEST_SUCCESS)
			return retVector;

		Wt::Json::Value resultValue;
		Wt::Json::Array resultArray;
		Wt::Json::parse(this->getResponseValue(), resultValue);
		resultArray = resultValue;
		for (Wt::Json::Array::iterator it = resultArray.begin(); it != resultArray.end(); ++it)
		{
			Wt::Json::Object obj = *it;

			// Convert the date
			std::string date = obj.get("lastUpdate").toString();
			Wt::WDateTime dt = Wt::WDateTime(toPosixDate(date, "%d%m%y"));

			Stock stk;
			stk.setStockId((int)obj.get("stockid"));
			stk.setStockCode(obj.get("stockcode").toString());
			stk.setCompanyName(obj.get("companyName").toString());
			stk.setCountry(obj.get("country").toString());
			stk.setLastUpdate(dt);
			stk.setLastSalePrice((double)(obj.get("lastSalePrice").toNumber()));
			stk.setPriceVolume((double)(obj.get("priceVolume").toNumber()));
			stk.setValueChange((double)(obj.get("valueChange").toNumber()));
			stk.setChangePercent((double)(obj.get("changePercent").toNumber()));
			retVector.push_back(stk);
		}

		return retVector;
	}
};

#endif