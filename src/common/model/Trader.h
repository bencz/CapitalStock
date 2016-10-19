//#ifndef  _TRADER_H
//#define  _TRADER_H
//
//#include <string>
//#include <Wt/Dbo/Dbo>
//#include <Wt/Dbo/WtSqlTraits>
//
//namespace dbo = Wt::Dbo;
//
//class Trader
//{
//public:
//#ifdef IS_WEB_SERVICE
//	template<class Action>
//	void persist(Action& a)
//	{
//		dbo::field(a, _balanceCash, "balance");
//		dbo::belongsTo(a, _user);
//	}
//#endif
//
//	//Get balanceCash
//	double getBalanceCash() { return _balanceCash; }
//
//	// Set balanceCash
//	void setBalanceCash(double value) { _balanceCash = value; }
//
//private:
//	double _balanceCash;
//
//#ifdef IS_WEB_SERVICE
//public:
//	// Relation with user table
//	dbo::ptr<User> _user;
//#endif
//};
//
//#endif