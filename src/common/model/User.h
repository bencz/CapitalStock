//#ifndef  _USER_H
//#define  _USER_H
//
//#include <string>
//#include <Wt/Dbo/Dbo>
//#include <Wt/WDateTime>
//#include <Wt/Dbo/WtSqlTraits>
//
//#ifdef IS_WEB_SERVICE
//#include "UserDetails.h"
//#include "Trader.h"
//
//namespace dbo = Wt::Dbo;
//#endif
//
//class User
//{
//public:
//	enum AccessLevel
//	{
//		Admin,
//		NormalUser
//	};
//
//#ifdef IS_WEB_SERVICE
//	template<class Action>
//	void persist(Action& a)
//	{
//		dbo::field(a, _userName, "userName");
//		dbo::field(a, _password, "password");
//		dbo::field(a, _accessLevel, "accessLevel");
//		dbo::field(a, _creationDateTime, "creationdate");
//		dbo::field(a, _lastAccess, "lastaccess");
//		dbo::hasOne(a, _userTrader);
//		dbo::hasOne(a, _userDetails);
//	}
//#endif
//
//	// Get & Set for userName
//	std::string getUserName()
//	{
//		return _userName;
//	}
//	void setUserName(std::string userName)
//	{
//		_userName = userName;
//	}
//
//	// Set for password
//	void setPassword(std::string password)
//	{
//		_password = password;
//	}
//
//	// Get & Set for accessLevel
//	AccessLevel getAccessLevel()
//	{
//		return _accessLevel;
//	}
//	void setAccessLevel(AccessLevel accessLevel)
//	{
//		_accessLevel = accessLevel;
//	}
//
//	// Get & Set for UserCreatioDateTime
//	Wt::WDateTime getCreationDateTime()
//	{
//		return _creationDateTime;
//	}
//	void setCreationDateTime(Wt::WDateTime creationDateTime)
//	{
//		_creationDateTime = creationDateTime;
//	}
//
//	// Get & Set for Last Access
//	Wt::WDateTime getLastAccess()
//	{
//		return _lastAccess;
//	}
//	void setLastAccess(Wt::WDateTime lastAccess)
//	{
//		_lastAccess = lastAccess;
//	}
//private:
//	std::string _userName;
//	std::string _password;
//	AccessLevel _accessLevel;
//	Wt::WDateTime _creationDateTime;
//	Wt::WDateTime _lastAccess;
//
//#ifdef IS_WEB_SERVICE
//public:
//	dbo::weak_ptr<Trader> _userTrader;
//	dbo::weak_ptr<UserDetails> _userDetails;
//#endif
//};
//
//#endif // ! _USER_H