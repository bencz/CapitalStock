#ifndef _MODELS_H
#define _MODELS_H

#include <string>
#include <Wt/Dbo/Dbo>
#include <Wt/WDateTime>
#include <Wt/Dbo/WtSqlTraits>

namespace dbo = Wt::Dbo;

class User;
class UserDetails;
class Transaction;
class Trader;
class Stock;
class Portfolio;

// ---------------------------------
// User model
// ---------------------------------
class User
{
public:
	enum AccessLevel
	{
		Admin,
		NormalUser
	};

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, _userName, "userName");
		dbo::field(a, _password, "password");
		dbo::field(a, _accessLevel, "accessLevel");
		dbo::field(a, _creationDateTime, "creationdate");
		dbo::field(a, _lastAccess, "lastaccess");
		dbo::hasOne(a, _userTrader);
		dbo::hasOne(a, _userDetails);
	}

	// Get & Set for userName
	std::string getUserName()
	{
		return _userName;
	}
	void setUserName(std::string userName)
	{
		_userName = userName;
	}

	// Set for password
	void setPassword(std::string password)
	{
		_password = password;
	}

	// Get & Set for accessLevel
	AccessLevel getAccessLevel()
	{
		return _accessLevel;
	}
	void setAccessLevel(AccessLevel accessLevel)
	{
		_accessLevel = accessLevel;
	}

	// Get & Set for UserCreatioDateTime
	Wt::WDateTime getCreationDateTime()
	{
		return _creationDateTime;
	}
	void setCreationDateTime(Wt::WDateTime creationDateTime)
	{
		_creationDateTime = creationDateTime;
	}

	// Get & Set for Last Access
	Wt::WDateTime getLastAccess()
	{
		return _lastAccess;
	}
	void setLastAccess(Wt::WDateTime lastAccess)
	{
		_lastAccess = lastAccess;
	}
private:
	std::string _userName;
	std::string _password;
	AccessLevel _accessLevel;
	Wt::WDateTime _creationDateTime;
	Wt::WDateTime _lastAccess;

public:
	dbo::weak_ptr<Trader> _userTrader;
	dbo::weak_ptr<UserDetails> _userDetails;
};

// ---------------------------------
// User Details model
// ---------------------------------
class UserDetails
{
public:
	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, _name, "name");
		dbo::field(a, _lastname, "lastname");
		dbo::field(a, _age, "age");
		dbo::field(a, _country, "country");
		dbo::field(a, _city, "city");
		dbo::belongsTo(a, _user);
		dbo::hasMany(a, _transactions, dbo::ManyToOne);
		dbo::hasMany(a, _portfolio, dbo::ManyToOne);
	}

	// Get for Name
	std::string getName() { return _name; }
	// Set for Name
	void setName(std::string name) { _name = name; }

	// Get for lastname
	std::string getLastname() { return _lastname; }
	// Set for lastname
	void setLastname(std::string surName) { _lastname = surName; }

	// Get for Surname
	std::string getEmail() { return _email; }
	// Set for Surname
	void setEmail(std::string email) { _email = email; }

	// Get for Age
	int getAge() { return _age; }
	// Set for Age
	void setAge(int age) { _age = age; }

	// Get for country
	std::string getCountry() { return _country; }
	// Set for country
	void setCountry(std::string country) { _country = country; }

	// Get for city
	std::string getCity() { return _city; }
	// Set for city
	void setCity(std::string city) { _city = city; }


private:
	std::string _name;
	std::string _lastname;
	std::string _email;
	std::string _country;
	std::string _city;
	int _age;

public:
	dbo::ptr<User> _user;
	dbo::collection<dbo::ptr<Portfolio>> _portfolio;
	dbo::collection<dbo::ptr<Transaction>> _transactions;
};

// ---------------------------------
// Transactions model
// ---------------------------------
class Transaction
{
public:
	enum TransactionStatus
	{
		EXECUTED = 0,
		PENDING = 1,
		CANCELED = 99
	};

	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, _quantity, "quantity");
		dbo::field(a, _transactionDate, "transactionDate");
		dbo::belongsTo(a, _userDetails);
		dbo::belongsTo(a, _stock);
	}

	// Get quantity
	int getQuantity() { return _quantity; }
	// Set quantity
	void setQuantity(int quantity) { _quantity = quantity; }

	// Get transaction date
	Wt::WDateTime& getTransactionDate() { return _transactionDate; }
	// Set transaction date
	void setTransactionDate(Wt::WDateTime& dateTime) { _transactionDate = dateTime; }

	// Get TransactionStatus
	TransactionStatus getTransactionStatus() { return _transactionStatus; }
	// Set TransactionStatus
	void setTransactionStatus(TransactionStatus transactionStatus) { _transactionStatus = transactionStatus; }

private:
	int _quantity;
	Wt::WDateTime _transactionDate;
	TransactionStatus _transactionStatus;

public:
	dbo::ptr<UserDetails> _userDetails;
	dbo::ptr<Stock> _stock;
};

// ---------------------------------
// Trader model
// ---------------------------------
class Trader
{
public:
	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, _balanceCash, "balance");
		dbo::belongsTo(a, _user);
	}

	//Get balanceCash
	double getBalanceCash() { return _balanceCash; }

	// Set balanceCash
	void setBalanceCash(double value) { _balanceCash = value; }

private:
	double _balanceCash;

public:
	// Relation with user table
	dbo::ptr<User> _user;
};

// ---------------------------------
// Stock model
// ---------------------------------
class Stock
{
public:
	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, _stockcode, "stockcode");
		dbo::field(a, _companyName, "companyname");
		dbo::field(a, _lastSalePrice, "lastsaleprice");
		dbo::field(a, _volume, "volume");
		dbo::field(a, _priceVolume, "pricevolume");
		dbo::field(a, _lastUpdate, "lastupdate");
		dbo::field(a, _country, "country");
		dbo::field(a, _valueChange, "valuechange");
		dbo::field(a, _changePercent, "changepercent");
		dbo::hasMany(a, _transactions, dbo::ManyToOne);
		dbo::belongsTo(a, _portfolio);
	}

	// get stockcode id
	int getStockId() { return _stockId; }
	// set stockcode
	void setStockId(int stockId) { _stockId = stockId; }

	// get stockcode
	std::string getStockCode() { return _stockcode; }
	// set stockcode
	void setStockCode(std::string stockcode) { _stockcode = stockcode; }

	// get company name
	std::string getCompanyName() { return _companyName; }
	// set company name
	void setCompanyName(std::string companyName) { _companyName = companyName; }

	// get country name
	std::string getCountry() { return _country; }
	// set country name
	void setCountry(std::string country) { _country = country; }

	// Get transaction date
	Wt::WDateTime& getLastUpdate() { return _lastUpdate; }
	// Set transaction date
	void setLastUpdate(Wt::WDateTime& lastUpdate) { _lastUpdate = lastUpdate; }

	// get volume
	double getVolume() { return _volume; }
	// set volume
	void setVolume(double value) { _volume = value; }

	// get lastSalePrice
	double getLastSalePrice() { return _lastSalePrice; }
	// set lastSalePrice
	void setLastSalePrice(double value) { _lastSalePrice = value; }

	// get volume
	double getPriceValume() { return _priceVolume; }
	// set volume
	void setPriceVolume(double priceValue) { _priceVolume = priceValue; }

	// get volume
	double getValueChange() { return _valueChange; }
	// set value change
	void setValueChange(double valueChange) { _valueChange = valueChange; }

	// get change percent
	double getChangePercent() { return _changePercent; }
	// set change percent
	void setChangePercent(double changePercent) { _changePercent = changePercent; }

private:
	int _stockId;
	std::string _stockcode;
	std::string _companyName;
	std::string _country;
	Wt::WDateTime _lastUpdate;
	double _volume;
	double _lastSalePrice;
	double _priceVolume;
	double _valueChange;
	double _changePercent;

public:
	dbo::ptr<Portfolio> _portfolio;
	dbo::collection<dbo::ptr<Transaction>> _transactions;
};

// ---------------------------------
// Portfolio model
// ---------------------------------
class Portfolio
{
public:
	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a, _quantity, "quantity");
		dbo::field(a, _totalCost, "totalcost");
		dbo::belongsTo(a, _userDetails);
		dbo::hasOne(a, _stock);
	}

	// Get quantity
	double getQuantity() { return _quantity; }
	// Set quantity
	void setQuantity(double quantity) { _quantity = quantity; }

	// Get total cost
	double getTotalCost() { return _totalCost; }
	// Set total cost
	void setTotalCost(double totalCost) { _totalCost = totalCost; }

private:
	double _quantity;
	double _totalCost;

public:
	dbo::ptr<UserDetails> _userDetails;
	dbo::weak_ptr<Stock> _stock;
};


#endif