//#ifndef  _STOCK_H
//#define  _STOCK_H
//
//#include <string>
//#include <Wt/Dbo/Dbo>
//#include <Wt/Dbo/WtSqlTraits>
//#include <Wt/WDateTime>
//
//#ifdef IS_WEB_SERVICE
//#include "User.h"
//#include "Transaction.h"
//class Portfolio;
//
//namespace dbo = Wt::Dbo;
//#endif
//
//class Stock
//{
//public:
//#ifdef IS_WEB_SERVICE
//	template<class Action>
//	void persist(Action& a)
//	{
//		dbo::field(a, _stockcode, "stockcode");
//		dbo::field(a, _companyName, "companyname");
//		dbo::field(a, _lastSalePrice, "lastsaleprice");
//		dbo::field(a, _volume, "volume");
//		dbo::field(a, _priceVolume, "pricevolume");
//		dbo::field(a, _lastUpdate, "lastupdate");
//		dbo::field(a, _country, "country");
//		dbo::field(a, _valueChange, "valuechange");
//		dbo::field(a, _changePercent, "changepercent");
//		dbo::hasMany(a, _transactions, dbo::ManyToOne);
//		dbo::belongsTo(a, _portfolio);
//	}
//#endif
//
//	// get stockcode id
//	int getStockId() { return _stockId; }
//	// set stockcode
//	void setStockId(int stockId) { _stockId = stockId; }
//
//	// get stockcode
//	std::string getStockCode() { return _stockcode; }
//	// set stockcode
//	void setStockCode(std::string stockcode) { _stockcode = stockcode; }
//
//	// get company name
//	std::string getCompanyName() { return _companyName; }
//	// set company name
//	void setCompanyName(std::string companyName) { _companyName = companyName; }
//
//	// get country name
//	std::string getCountry() { return _country; }
//	// set country name
//	void setCountry(std::string country) { _country = country; }
//
//	// Get transaction date
//	Wt::WDateTime& getLastUpdate() { return _lastUpdate; }
//	// Set transaction date
//	void setLastUpdate(Wt::WDateTime& lastUpdate) { _lastUpdate = lastUpdate; }
//
//	// get volume
//	double getVolume() { return _volume; }
//	// set volume
//	void setVolume(double value) { _volume = value; }
//
//	// get lastSalePrice
//	double getLastSalePrice() { return _lastSalePrice; }
//	// set lastSalePrice
//	void setLastSalePrice(double value) { _lastSalePrice = value; }
//
//	// get volume
//	double getPriceValume() { return _priceVolume; }
//	// set volume
//	void setPriceVolume(double priceValue) { _priceVolume = priceValue; }
//
//	// get volume
//	double getValueChange() { return _valueChange; }
//	// set value change
//	void setValueChange(double valueChange) { _valueChange = valueChange; }
//
//	// get change percent
//	double getChangePercent() { return _changePercent; }
//	// set change percent
//	void setChangePercent(double changePercent) { _changePercent = changePercent; }
//
//private:
//	int _stockId;
//	std::string _stockcode;
//	std::string _companyName;
//	std::string _country;
//	Wt::WDateTime _lastUpdate;
//	double _volume;
//	double _lastSalePrice;
//	double _priceVolume;
//	double _valueChange;
//	double _changePercent;
//
//#ifdef IS_WEB_SERVICE
//public:
//	dbo::ptr<Portfolio> _portfolio;
//	dbo::collection<dbo::ptr<Transaction>> _transactions;
//#endif
//};
//
//#endif