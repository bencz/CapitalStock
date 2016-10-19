//#ifndef  _TRANSACTION_H
//#define  _TRANSACTION_H
//
//#include <string>
//#include <Wt/Dbo/Dbo>
//#include <Wt/Dbo/WtSqlTraits>
//#include <Wt/WDateTime>
//
//#ifdef IS_WEB_SERVICE
//class Stock;
//class UserDetails;
//
//namespace dbo = Wt::Dbo;
//#endif
//
//class Transaction
//{
//public:
//	enum TransactionStatus
//	{
//		EXECUTED = 0,
//		PENDING = 1,
//		CANCELED = 99
//	};
//	
//#ifdef IS_WEB_SERVICE
//	template<class Action>
//	void persist(Action& a)
//	{
//		dbo::field(a, _quantity, "quantity");
//		dbo::field(a, _transactionDate, "transactionDate");
//		dbo::belongsTo(a, _userDetails);
//		dbo::belongsTo(a, _stock);
//	}
//#endif
//
//	// Get quantity
//	int getQuantity() { return _quantity; }
//	// Set quantity
//	void setQuantity(int quantity) { _quantity = quantity; }
//
//	// Get transaction date
//	Wt::WDateTime& getTransactionDate() { return _transactionDate; }
//	// Set transaction date
//	void setTransactionDate(Wt::WDateTime& dateTime) { _transactionDate = dateTime; }
//
//	// Get TransactionStatus
//	TransactionStatus getTransactionStatus() { return _transactionStatus; }
//	// Set TransactionStatus
//	void setTransactionStatus(TransactionStatus transactionStatus) { _transactionStatus = transactionStatus; }
//
//private:
//	int _quantity;
//	Wt::WDateTime _transactionDate;
//	TransactionStatus _transactionStatus;
//
//#ifdef IS_WEB_SERVICE
//public:
//	dbo::ptr<UserDetails> _userDetails;
//	dbo::ptr<Stock> _stock;
//#endif
//};
//
//#endif