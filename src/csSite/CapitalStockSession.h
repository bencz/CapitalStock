#ifndef _CSSESSION_H
#define _CSSESSION_H

#include "repository/UserRepository.h"
#include "repository/StockRepository.h"

class CapitalStockSession
{
public:
	CapitalStockSession(const std::string& baseWebApiUrl)
		 : _userLoged(false)
	{
		_userRepository = new UserRepository(baseWebApiUrl);
		_stockRepository = new StockRepository(baseWebApiUrl);
	}
	
	UserRepository* getUserRepository()
	{
		return _userRepository;
	}

	StockRepository* getStockRepository()
	{
		return _stockRepository;
	}

	bool isUserLoged() const
	{
		return _userLoged;
	}

	void setUserLoged()
	{
		_userLoged = _userRepository->getUserIsValid();
	}

	void doLogOut()
	{
		_userLoged = false;
		_userRepository->setUserName("");
		_userRepository->setUserPassword("");
		_userRepository->setUserIsValid(false);
	}

	~CapitalStockSession()
	{
		delete _userRepository;
		delete _stockRepository;
	}

private:
	UserRepository* _userRepository;
	StockRepository* _stockRepository;

	// contains a information if user is loged or not
	bool _userLoged;
};

#endif