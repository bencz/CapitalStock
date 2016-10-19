#include "ServiceSession.h"
#include "..\common\StringHelper.h"
#include "FileHelper.h"

//#include "..\common\model\User.h"
//#include "..\common\model\Trader.h"
//#include "..\common\model\UserDetails.h"
//#include "..\common\model\Portfolio.h"
//#include "..\common\model\Transaction.h"
//#include "..\common\model\Stock.h"
#include "..\common\model\Models.h"

#include "CSVParser\CSVParser.h"

#include <Wt/WDateTime>
#include <Wt/Dbo/FixedSqlConnectionPool>
#include <Wt/Dbo/backend/Sqlite3>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

ServiceSession::ServiceSession(dbo::SqlConnectionPool& connectionPool)
	: _connectionPool(connectionPool),
	  _userDataAccess(*this),
	 _stockDataAccess(_userDataAccess, *this)
{
	setConnectionPool(_connectionPool);
	_connectionPool.getConnection();

	mapClass<User>("users");
	mapClass<UserDetails>("userdetails");
	mapClass<Portfolio>("portfolio");
	mapClass<Trader>("trader");
	mapClass<Transaction>("transaction");
	mapClass<Stock>("stock");

	try
	{
		// Create the tables, if not exist
		dbo::Transaction t(*this);
		createTables();
		t.commit();
	}
	catch (std::exception& e)
	{
		//std::cerr << e.what() << std::endl;
		std::cerr << "Using existing database" << std::endl;
		return;
	}

	// Try to create a user
	try
	{
		// Create the default user
		_userDataAccess.createNewUser(ADMIN_USERNAME, copmuteMd5(computeSHA1(ADMIN_PASSWORD)), User::Admin);
		// Create the user details
		_userDataAccess.createUserDetails(ADMIN_USERNAME, copmuteMd5(computeSHA1(ADMIN_PASSWORD)), 
			"Admin", "", "admin@cs.com", "Brazil", "Sao Paulo", 30);
	}
	catch (std::exception& e)
	{
		//std::cerr << e.what() << std::endl;
		std::cerr << "Impossible to create an user";
	}

	// try to create the stocks
	try
	{
		std::string fileName = "output.txt";
		if (fileExist(fileName))
		{
			CSVParser* csvParser = new CSVParser(fileName);
			csvParser->parseCsv(';');

			// Naviagete into the vector matrix to get all the csv data
			for (int i = 0;i < csvParser->getCsvContent().size();i++)
			{
				Wt::WDateTime lastUpdate = Wt::WDateTime(toPosixDate(csvParser->getCsvContent()[i][7], "%m/%d/%y"));

				try
				{
					_stockDataAccess.insertNewStock(
						ADMIN_USERNAME,
						copmuteMd5(computeSHA1(ADMIN_PASSWORD)),
						csvParser->getCsvContent()[i][0],  // Stock code
						csvParser->getCsvContent()[i][1],  // Company name
						toDouble(csvParser->getCsvContent()[i][2]), // Last value
						toDouble(csvParser->getCsvContent()[i][3]), // Value change
						toDouble(csvParser->getCsvContent()[i][4]), // Value change percent
						toDouble(csvParser->getCsvContent()[i][5]), // Volume
						toDouble(csvParser->getCsvContent()[i][6]), // Price volume
						lastUpdate); // Last update
				}
				catch (std::exception& e)
				{
					std::cerr << e.what() << std::endl;
					std::cerr << "Fail to insert stock register" << std::endl;
				}
			}

			delete csvParser;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Impossible to create the stocks";
	}
}

ServiceSession::~ServiceSession()
{
}

// Return the instance of UserDataAccess
UserDataAccess& ServiceSession::getUserDataAccess()
{
	return _userDataAccess;
}

StockDataAccess& ServiceSession::getStockDataAccess()
{
	return _stockDataAccess;
}

// Create the pool of connections
dbo::SqlConnectionPool* ServiceSession::createConnectionPool(const std::string& sqliteDb)
{
	dbo::backend::Sqlite3* connection = new dbo::backend::Sqlite3(sqliteDb);
	connection->setDateTimeStorage(Wt::Dbo::SqlDateTime, Wt::Dbo::backend::Sqlite3::PseudoISO8601AsText);
	return new dbo::FixedSqlConnectionPool(connection, 30);
}
