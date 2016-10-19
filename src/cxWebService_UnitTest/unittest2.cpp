#include "stdafx.h"
#include "CppUnitTest.h"

#include "../csWebService/ServiceSession.h"
#include "../csWebService/dal/UserDataAccess.h"

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>

namespace dbo = Wt::Dbo;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace cxWebService_UnitTest
{
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(Check_if_stock_exist)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);
		
			Assert::AreEqual(false, (bool)serviceSession.getStockDataAccess().stockCodeExist("test"));
		
			delete webServiceDb;
		}
		
		TEST_METHOD(Create_Stok)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);
		
			Wt::WDateTime date = Wt::WDateTime(toPosixDate(std::string("05/05/16"), "%m/%d/%y"));
		
			serviceSession.getUserDataAccess().createNewUser("testusr", "testusr", User::AccessLevel::Admin);
			auto retCode = serviceSession.getStockDataAccess().insertNewStock("testusr", "testusr", "test", "no-company", 15.5, 143.43, 456, 45, 46.8, date);
		
			Assert::AreEqual((int)retCode, (int)StockDataAccess::NewStockErrorLevel::SUCCESS);
		
		
			delete webServiceDb;
		}
		
		TEST_METHOD(Check_if_stok_exist_after_create)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);
		
			Wt::WDateTime date = Wt::WDateTime(toPosixDate(std::string("05/05/16"), "%m/%d/%y"));
		
			serviceSession.getUserDataAccess().createNewUser("testusr", "testusr", User::AccessLevel::Admin);
			auto retCode = serviceSession.getStockDataAccess().insertNewStock("testusr", "testusr", "test", "no-company", 15.5, 143.43, 456, 45, 46.8, date);
			Assert::AreEqual(true, (bool)serviceSession.getStockDataAccess().stockCodeExist("test"));
		
			Assert::AreEqual((int)retCode, (int)StockDataAccess::NewStockErrorLevel::SUCCESS);
		
		
			delete webServiceDb;
		}
	};
}