#ifndef  _SERVICE_SESSION_H
#define  _SERVICE_SESSION_H

#include <string>

#include <Wt/Dbo/Session>

#include "dal/UserDataAccess.h"
#include "dal/StockDataAccess.h"

namespace dbo = Wt::Dbo;

class ServiceSession : public dbo::Session
{
public:
	ServiceSession(dbo::SqlConnectionPool& connectionPool);
	~ServiceSession();

	// get the instance of UserDataAccess
	UserDataAccess& getUserDataAccess();
	// get the instance of StockDataAccess
	StockDataAccess& getStockDataAccess();

	// Create the pool of connections
	static dbo::SqlConnectionPool* createConnectionPool(const std::string& sqliteDb);

private:
	dbo::SqlConnectionPool& _connectionPool;
	UserDataAccess _userDataAccess;
	StockDataAccess _stockDataAccess;
};

#endif // !_SERVICE_SESSION_H