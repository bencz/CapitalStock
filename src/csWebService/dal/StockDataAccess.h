#ifndef _STOCKDATAACCESS_H
#define _STOCKDATAACCESS_H

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/Session>
#include <Wt/WDateTime>

#include "UserDataAccess.h"
//#include "../../common/model/Stock.h"
#include "../../common/model/Models.h"

// The class StockDataAccess controlls all the stock data for read and write
class StockDataAccess
{
	// Public methods
public:
	enum NewStockErrorLevel
	{
		USER_NOT_EXIST = 1,
		USER_IS_NOT_ADMIN = 2,
		STOCK_CODE_ALREADY_EXISTS = 3,
		FAIL_TO_INSERT = 4,
		SUCCESS = 5
	};

	// struct to hold the stock data returned by query
	//struct Stocks
	//{
	//	std::string _stockCode;
	//	std::string _companyName;
	//	double _lastSaleValue, _valueChange, _changePercent;
	//	double _volume, _priceVolume;
	//
	//	Stocks(std::string stockCode, std::string companyName, double lastSaleValue, double valueChange, double changePercent, double volume, double priceVolume)
	//		: _stockCode(stockCode), _companyName(companyName),
	//		_lastSaleValue(lastSaleValue), _valueChange(valueChange), _changePercent(changePercent),
	//		_volume(volume), _priceVolume(priceVolume)
	//	{ }
	//};

	StockDataAccess(UserDataAccess& userDataAccess, dbo::Session& session)
		: _session(session),
		_userDataAccess(userDataAccess)
	{
	}

	// !!! HOT FIX
	// Create a struct to send all this data to this method, 
	// this will make the code more readble
	NewStockErrorLevel insertNewStock(
		std::string userName,
		std::string password,
		std::string stockCode,
		std::string companyName,
		double lastSaleValue,
		double valueChange,
		double changePercent,
		double volume,
		double priceVolume,
		Wt::WDateTime lastUpdate)
	{
		if (!_userDataAccess.userExist(userName, password))
			return NewStockErrorLevel::USER_NOT_EXIST;

		if (!_userDataAccess.userIsAdmin(userName))
			return NewStockErrorLevel::USER_IS_NOT_ADMIN;

		if (stockCodeExist(stockCode))
			return NewStockErrorLevel::STOCK_CODE_ALREADY_EXISTS;

		try
		{
			dbo::Transaction transaction(_session);
			Stock* stock = new Stock();
			stock->setStockCode(stockCode);
			stock->setCompanyName(companyName);
			stock->setLastSalePrice(lastSaleValue);
			stock->setValueChange(valueChange);
			stock->setChangePercent(changePercent);
			stock->setVolume(volume);
			stock->setPriceVolume(priceVolume);
			stock->setLastUpdate(lastUpdate);

			dbo::ptr<Stock> stockPtr = _session.add(stock);
			transaction.commit();
			return NewStockErrorLevel::SUCCESS;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return NewStockErrorLevel::FAIL_TO_INSERT;
		}
	}

	// Get stock return a list with all informations of a stock
	std::vector<Stock> getStocks(int limit)
	{
		std::vector<Stock> retVal;

		dbo::Transaction transaction(_session);
		typedef dbo::collection<dbo::ptr<Stock>> StockData;
		StockData stockData = _session.find<Stock>().limit(limit);
		for (StockData::const_iterator it = stockData.begin(); it != stockData.end(); ++it)
		{
			dbo::ptr<Stock> stkPtr = *it;
			Stock* stk = stkPtr.modify();
			stk->setStockId(stkPtr.id());
			retVal.push_back(*stk);
		}

		return retVal;
	}

	// Check if a stock code exist
	// - std::string stockCode =  stock code to verify
	bool stockCodeExist(std::string stockCode)
	{
		dbo::Transaction transaction(_session);
		int count = _session.query<int>("select count(1) from stock")
			.where("stockcode = ?").bind(stockCode);
		return count == 1;
	}

	// Private variables
private:
	dbo::Session& _session;
	UserDataAccess& _userDataAccess;
};

#endif