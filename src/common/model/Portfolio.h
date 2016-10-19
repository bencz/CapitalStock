//#ifndef  _PORTFOLIO_H
//#define  _PORTFOLIO_H
//
//#include <string>
//#include <Wt/Dbo/Dbo>
//#include <Wt/Dbo/WtSqlTraits>
//
//#ifdef IS_WEB_SERVICE
//#include "Stock.h"
//class UserDetails;
//
//namespace dbo = Wt::Dbo;
//#endif
//
//class Portfolio
//{
//public:
//#ifdef IS_WEB_SERVICE
//	template<class Action>
//	void persist(Action& a)
//	{
//		dbo::field(a, _quantity, "quantity");
//		dbo::field(a, _totalCost, "totalcost");
//		dbo::belongsTo(a, _userDetails);
//		dbo::hasOne(a, _stock);
//	}
//#endif
//
//	// Get quantity
//	double getQuantity() { return _quantity; }
//	// Set quantity
//	void setQuantity(double quantity) { _quantity = quantity; }
//
//	// Get total cost
//	double getTotalCost() { return _totalCost; }
//	// Set total cost
//	void setTotalCost(double totalCost) { _totalCost = totalCost; }
//
//private:
//	double _quantity;
//	double _totalCost;
//
//#ifdef IS_WEB_SERVICE
//public:
//	dbo::ptr<UserDetails> _userDetails;
//	dbo::weak_ptr<Stock> _stock;
//#endif
//};
//
//#endif