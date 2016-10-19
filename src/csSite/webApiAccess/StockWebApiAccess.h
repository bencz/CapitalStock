#ifndef _STOCKWEBAPIACCESS_H
#define _STOCKWEBAPIACCESS_H

#include "WebApiAccess.h"
#include "../../common/WebApiUrl.h"
#include "../../common/StringHelper.h"
//#include "../../common/model/Stock.h"
#include "../../common/model/Models.h"

#include <Wt/Utils>

class StockWebApiAccess : public WebApiAccess
{
public:
	StockWebApiAccess(const std::string& baseWebApiUrl)
		: WebApiAccess(baseWebApiUrl)
	{
	}

protected:
	void getStockList(int limit)
	{
		// Create the URL to make the web request
		std::string urlUserValidation = URL_GETSTOCKLIMIT;
		urlUserValidation += "?limit=" + std::to_string(limit);
		makeRequest(urlUserValidation);
	}
};

#endif