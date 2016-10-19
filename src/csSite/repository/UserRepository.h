#ifndef _USERREPOSITORY_H
#define _USERREPOSITORY_H

#include <string>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>

#include "../webApiAccess/UserWebApiAccess.h"
#include "../../common/StringHelper.h"

class UserRepository : public UserWebApiAccess
{
public:
	UserRepository(const std::string& baseWebApiUr)
		: UserWebApiAccess(baseWebApiUr),
		 _userIsValid(false)
	{
	}

	~UserRepository()
	{
		delete _userDetails;
	}

	// Autenticate the user name and password
	// - const std::string& username = User name to authenticate
	// - const std::string& password = Username password ( NOT cryptografed!! )
	bool authenticateUser(const std::string& username, const std::string& password)
	{
		validadeUser(username, encrypt(std::string(password)));
		if (this->getErrorLevel() != this->REQUEST_SUCCESS)
			return false;

		Wt::Json::Object resultObject;
		Wt::Json::parse(this->getResponseValue(), resultObject);
		_userIsValid = (bool)resultObject.get("success");

		if (_userIsValid)
		{
			setUserName(username);
			setUserPassword(encrypt(std::string(password)));
		}

		// Set the last access of user as now
		setUserLastAccessAsNow();

		return (_userIsValid);
	}

	// This method make the call of the method "createNewUser" from UserWebApiAccess class
	// This method process the json result of UserWebApiAccess method call
	// - const std::string username = new user name
	// - const std::string password = new user password ( NOT ENCRYPTED!! )
	std::string registerUser(const std::string username, const std::string password, UserDetails& userDetails)
	{
		createNewUser(username, encrypt(std::string(password)), userDetails);
		if (this->getErrorLevel() != this->REQUEST_SUCCESS)
			return "Impossible register";

		Wt::Json::Object resultObject;
		Wt::Json::parse(this->getResponseValue(), resultObject);

		// Make the new user valid, to alow the login in the instance
		_userIsValid = (bool)resultObject.get("success");
		if ((bool)resultObject.get("success") == true)
		{
			setUserName(username);
			setUserPassword(encrypt(std::string(password)));
			return "";
		}
		else
			return (std::string)resultObject.get("reasonText");
	}

	// Get total of money of user
	double getUserCash()
	{
		getTotalCashOfUser(getUserName(), getUserPassword());
		if (this->getErrorLevel() != this->REQUEST_SUCCESS)
			return -1;

		Wt::Json::Object resultObject;
		Wt::Json::parse(this->getResponseValue(), resultObject);
		if ((bool)resultObject.get("success") == true)
			return (double)resultObject.get("value");
		else
			return -1;
	}

	// Get user details
	UserDetails* getUserDetails()
	{
		//if (_userDetails == nullptr)
		//{
			requestUserDetails(getUserName(), getUserPassword());
			if (this->getErrorLevel() != this->REQUEST_SUCCESS)
				return nullptr;

			Wt::Json::Object resultObject;
			Wt::Json::parse(this->getResponseValue(), resultObject);
			if ((bool)resultObject.get("success") == false)
				return nullptr;

			_userDetails = new UserDetails();
			_userDetails->setName((std::string)resultObject.get("name"));
			_userDetails->setLastname((std::string)resultObject.get("lastname"));
			_userDetails->setEmail((std::string)resultObject.get("email"));
			_userDetails->setCountry((std::string)resultObject.get("country"));
			_userDetails->setCity((std::string)resultObject.get("city"));
			_userDetails->setAge((int)resultObject.get("age"));
		//}

		return _userDetails;
	}

	// Set the last access of user
	void setUserLastAccessAsNow()
	{
		setLastAccesAsNow(getUserName(), getUserPassword());
	}

	// Return if use is valid
	bool getUserIsValid() const { return _userIsValid; }
	// Set user valid
	void setUserIsValid(bool userIsValid) { _userIsValid = userIsValid; }

	// Get user name
	std::string getUserName() { return _userName; }
	// Set user name
	void setUserName(std::string userName) { _userName = userName; }

	// Get user password
	std::string getUserPassword() { return _userPassword; }
	// Set user password
	void setUserPassword(std::string password) { _userPassword = password; }

private:
	bool _userIsValid;
	std::string _userName;
	std::string _userPassword;
	UserDetails* _userDetails;
};

#endif