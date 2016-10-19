#ifndef  _USERDATAACCESS_H
#define  _USERDATAACCESS_H

//#include "../../common/model/User.h"
//#include "../../common/model/Trader.h"
//#include "../../common/model/UserDetails.h"
#include "../../common/model/Models.h"
#include "../../common/StringHelper.h"

#include <string>
#include <vector>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/Session>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace dbo = Wt::Dbo;
namespace pt = boost::posix_time;

#define INITIAL_CASH_VALUE 100000.00

// The class UserDataAccess controlls all the user data, for read and write
class UserDataAccess
{
// Public variables
public:
	enum NewUserErrorLevel
	{
		EMPTY_USER_NAME = 0,
		EMPTY_PASSWORD = 1,
		USER_EXIST = 2,
		IMPOSSIBLE_TO_CREATE_THE_NEW_USER = 3,
		IMPOSSIBLE_TO_CREATE_THE_USER_DETAILS = 4,
		SUCCESS = 5
	};

// Public methods
public:
	UserDataAccess(dbo::Session& session) 
		: _session(session)
	{
		initNewUserErrorLevelTexts();
	}

	// Create a new User
	// - std::string userName = User name to be created
	// - std::string password = Password of new username
	// - User::AccessLevel accessLevel = Access level of the new userName
	NewUserErrorLevel createNewUser(std::string userName, std::string password, User::AccessLevel accessLevel)
	{
		NewUserErrorLevel canCreateErrorCode = canCreateTheUser(userName, password);
		if (canCreateErrorCode != NewUserErrorLevel::SUCCESS)
			return canCreateErrorCode;

		// Try to create the new user
		try
		{
			dbo::Transaction transaction(_session);
			User* usr = new User();
			usr->setUserName(userName);
			usr->setPassword(password);
			usr->setAccessLevel(accessLevel);
			usr->setCreationDateTime(Wt::WDateTime(pt::second_clock::local_time()));
			dbo::ptr<User> userPtr = _session.add(usr);

			// Insert the defaul value of money to trade
			// The default value is: U$ 100.000,00
			Trader* trd = new Trader();
			trd->setBalanceCash(INITIAL_CASH_VALUE);
			usr->_userTrader = trd;

			transaction.commit();
			return NewUserErrorLevel::SUCCESS;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return NewUserErrorLevel::IMPOSSIBLE_TO_CREATE_THE_NEW_USER;
		}
	}

	// Create a new User details
	// - std::string userName = User name to be created
	// - std::string password = Password of new username
	// - std::string name = name of the new user
	// - std::string lastName = last name of user
	// - std::string email = email of new user
	// - std::string countr = country of new user
	// - std::string city = city of new user
	// - int age = age of new user
	NewUserErrorLevel createUserDetails(std::string userName, std::string password, std::string name, 
		      std::string lastName, std::string email, std::string country, std::string city, int age)
	{
		NewUserErrorLevel canCreateErrorCode = canCreateTheUser(userName, password);
		if (canCreateErrorCode != NewUserErrorLevel::SUCCESS && canCreateErrorCode != NewUserErrorLevel::USER_EXIST)
			return canCreateErrorCode;

		try
		{
			dbo::Transaction transaction(_session);
			dbo::ptr<User> usr = _session.find<User>()
				.where("userName = ?").bind(userName)
				.where("password = ?").bind(password);

			UserDetails* usrDet = new UserDetails();
			usrDet->setName(name);
			usrDet->setLastname(lastName);
			usrDet->setEmail(email);
			usrDet->setCountry(country);
			usrDet->setCity(city);
			usrDet->setAge(age);
			usr.modify()->_userDetails = usrDet;

			transaction.commit();
			return NewUserErrorLevel::SUCCESS;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return NewUserErrorLevel::IMPOSSIBLE_TO_CREATE_THE_USER_DETAILS;
		}
	}

	// check if user exist, based in userName and password
	// - std::string userName = User name to use to check
	// - std::string password = Password to use to check
	bool userExist(std::string userName, std::string password)
	{
		dbo::Transaction transaction(_session);
		int count = _session.query<int>("select count(1) from users")
			.where("userName = ?").bind(userName)
			.where("password = ?").bind(password);
		return count == 1;
	}

	// check if exist a user with 'userName'
	// - std::string userName = userName to check
	bool userNameExist(std::string userName)
	{
		dbo::Transaction transaction(_session);
		int count = _session.query<int>("select count(1) from users")
			.where("userName = ?").bind(userName);
		return count == 1;
	}

	// Return the user ID
	// - std::string userName = User name to be created
	// - std::string password = Password of new username
	int getUserId(std::string userName, std::string password)
	{
		dbo::Transaction transaction(_session);
		int userId = _session.query<int>("select id from users")
			.where("userName = ?").bind(userName)
			.where("password = ?").bind(password);
		
		return userId;
	}

	// Return text information of error level
	// - NewUserErrorLevel errorLevel = error to return text representation
	std::string getNewUserErrorLevelText(NewUserErrorLevel errorLevel)
	{
		return NewUserErrorLevelText[(int)errorLevel];
	}

	// Return how much money to user have
	// - std::string userName = User name of the user
	// - std::string password = Password of user
	double getTotalCash(std::string userName, std::string password)
	{
		dbo::Transaction transaction(_session);
		double totalCash = _session.query<double>("SELECT trader.balance FROM trader INNER JOIN users ON trader.users_id = users.id")
			.where("users.userName = ?").bind(userName)
			.where("users.password = ?").bind(password);
		return totalCash;
	}

	// Check if user is an admin
	// - std::string userName = user name to check
	bool userIsAdmin(std::string userName)
	{
		dbo::Transaction transaction(_session);
		User::AccessLevel accessLevel = _session.query<User::AccessLevel>("select accessLevel from users")
			.where("userName = ?").bind(userName);
		return accessLevel == User::AccessLevel::Admin;
	}

	// Set the last access of the use
	// return true if success
	// - std::string userName = User name of the user
	// - std::string password = Password of user
	double setLastAccess(std::string userName, std::string password)
	{
		try
		{
			dbo::Transaction transaction(_session);
			dbo::ptr<User> usr = _session.find<User>()
				.where("users.userName = ?").bind(userName)
				.where("users.password = ?").bind(password);

			usr.modify()->setLastAccess(Wt::WDateTime(pt::second_clock::local_time()));
			transaction.commit();

			return true;
		}
		catch (std::exception& e)
		{
			return false;
		}
	}

	// Return user details
	// - std::string userName = User name of the user
	// - std::string password = Password of user
	void getUserDetails(std::string userName, std::string password, UserDetails* userDetails)
	{
		try
		{
			dbo::Transaction transaction(_session);
			dbo::ptr<User> usr = _session.find<User>()
				.where("users.userName = ?").bind(userName)
				.where("users.password = ?").bind(password);

			UserDetails* usrPtr = (usr->_userDetails).modify();
			//UserDetails usrDet;
			userDetails->setAge(usrPtr->getAge());
			userDetails->setCity(usrPtr->getCity());
			userDetails->setCountry(usrPtr->getCountry());
			userDetails->setEmail(usrPtr->getEmail());
			userDetails->setLastname(usrPtr->getLastname());
			userDetails->setName(usrPtr->getName());
			//return usrDet;
		}
		catch (std::exception& e)
		{

		}
	}

// private methods
private:
	// check possible basic erros in when try to create the new user
	NewUserErrorLevel canCreateTheUser(std::string userName, std::string password)
	{
		if (trim(userName).size() == 0)
			return NewUserErrorLevel::EMPTY_USER_NAME;

		if (trim(password).size() == 0)
			return NewUserErrorLevel::EMPTY_PASSWORD;

		if (userNameExist(userName))
			return NewUserErrorLevel::USER_EXIST;

		return NewUserErrorLevel::SUCCESS;
	}

	// initialize the text informations of errors in create new user
	void initNewUserErrorLevelTexts()
	{
		NewUserErrorLevelText.push_back("Empty user name");
		NewUserErrorLevelText.push_back("Empty password");
		NewUserErrorLevelText.push_back("There is already a user with this user name");
		NewUserErrorLevelText.push_back("Impossible to create the new user");
		NewUserErrorLevelText.push_back("Impossible to create the new user details");
		NewUserErrorLevelText.push_back("New user created successfully");
	}

// Private variables
private:
	dbo::Session& _session;
	std::vector<std::string> NewUserErrorLevelText;
};

#endif