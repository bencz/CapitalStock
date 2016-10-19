//#ifndef  _USER_DETAILS_H
//#define  _USER_DETAILS_H
//
//#include <string>
//#include <Wt/Dbo/Dbo>
//#include <Wt/Dbo/WtSqlTraits>
//
//
//#ifdef IS_WEB_SERVICE
//class User;
//#include "Portfolio.h"
//#endif
//
//namespace dbo = Wt::Dbo;
//
//class UserDetails
//{
//public:
//#ifdef IS_WEB_SERVICE
//	template<class Action>
//	void persist(Action& a)
//	{
//		dbo::field(a, _name, "name");
//		dbo::field(a, _lastname, "lastname");
//		dbo::field(a, _age, "age");
//		dbo::field(a, _country, "country");
//		dbo::field(a, _city, "city");
//		dbo::belongsTo(a, _user);
//		dbo::hasMany(a, _transactions, dbo::ManyToOne);
//		dbo::hasMany(a, _portfolio, dbo::ManyToOne);
//	}
//#endif
//
//	// Get for Name
//	std::string getName() { return _name; }
//	// Set for Name
//	void setName(std::string name) { _name = name; }
//
//	// Get for lastname
//	std::string getLastname() { return _lastname; }
//	// Set for lastname
//	void setLastname(std::string surName) { _lastname = surName; }
//
//	// Get for Surname
//	std::string getEmail() { return _email; }
//	// Set for Surname
//	void setEmail(std::string email) { _email = email; }
//
//	// Get for Age
//	int getAge() { return _age; }
//	// Set for Age
//	void setAge(int age) { _age = age; }
//
//	// Get for country
//	std::string getCountry() { return _country; }
//	// Set for country
//	void setCountry(std::string country) { _country = country; }
//
//	// Get for city
//	std::string getCity() { return _city; }
//	// Set for city
//	void setCity(std::string city) { _city = city; }
//
//
//private:
//	std::string _name;
//	std::string _lastname;
//	std::string _email;
//	std::string _country;
//	std::string _city;
//	int _age;
//
//#ifdef IS_WEB_SERVICE
//public:
//	dbo::ptr<User> _user;
//	dbo::collection<dbo::ptr<Portfolio>> _portfolio;
//	dbo::collection<dbo::ptr<Transaction>> _transactions;
//#endif
//};
//
//#endif