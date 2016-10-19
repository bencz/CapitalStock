#include <Wt/WServer>
#include <Wt/WResource>
#include <Wt/Http/Response>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>

#include "ServiceSession.h"
#include "RestRequests/User/RestAuthenticateUser.h"
#include "RestRequests/User/RestCreateNewUser.h"
#include "RestRequests/User/RestGetTotalCash.h"
#include "RestRequests/User/RestSetLastAccess.h"
#include "RestRequests/User/RestGetUserDetails.h"

#include "RestRequests/Stock/RestGetStocksTable.h"

#include "../common/WebApiUrl.h"

namespace dbo = Wt::Dbo;

class ResourcesInitializers
{
public:
	ResourcesInitializers(Wt::WServer& server, ServiceSession& serviceSession)
		: _server(server), 
		 _serviceSession(serviceSession)
	{
		createResourcesForUsers();
		createResourcesForStocks();
	}

private:
	void createResourcesForUsers()
	{
		_getAuthentication = new RestAuthenticateUser(_serviceSession);// Create the instance for Authentication
		_createNewUser = new RestCreateNewUser(_serviceSession);       // Create the instance for user registration
		_getTotalCashOfUser = new RestGetTotalCash(_serviceSession);   // Create the instance to get total money of user
		_setLastAccess = new RestSetLastAccess(_serviceSession);       // Create the instance to set the user last access
		_getUserDetails = new RestGetUserDetails(_serviceSession);     // Create the instance to get the user details

		// Set the resouce to redirect to correclty instance for users
		_server.addResource(_getAuthentication, URL_AUTHENTICATE);
		_server.addResource(_createNewUser, URL_CREATEUSER);
		_server.addResource(_getTotalCashOfUser, URL_GETCASH);
		_server.addResource(_setLastAccess, URL_SETLASTACCESS);
		_server.addResource(_getUserDetails, URL_GETUSERDETAILS);
	}

	void createResourcesForStocks()
	{
		_getStockList = new RestGetStocksTable(_serviceSession); // create the instance to get a list of stocks

		// Set the resources
		_server.addResource(_getStockList, URL_GETSTOCKLIMIT);
	}

private:
	Wt::WServer& _server;
	ServiceSession& _serviceSession;

	// Variables of user rest system
	RestAuthenticateUser* _getAuthentication;
	RestCreateNewUser* _createNewUser;
	RestGetTotalCash* _getTotalCashOfUser;
	RestSetLastAccess* _setLastAccess;
	RestGetUserDetails* _getUserDetails;


	// Variables of stock system
	RestGetStocksTable* _getStockList;
};

int main(int argc, char **argv)
{
	try
	{
		Wt::WServer server(argv[0]);
		server.setServerConfiguration(argc, argv);

		// Create the db pool connection
		Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(server.appRoot() + "capitalStock.db");
		ServiceSession serviceSession(*webServiceDb);

		// Create all the resources for users
		ResourcesInitializers resInit(server, serviceSession);

		if (server.start())
		{
			Wt::WServer::waitForShutdown();
			server.stop();
		}

		delete webServiceDb;
	}
	catch (Wt::WServer::Exception& e)
	{
		std::cerr << "WServer exception" << std::endl << e.what() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}