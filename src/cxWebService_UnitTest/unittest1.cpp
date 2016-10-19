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
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(CreateUser)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);

			Assert::AreEqual(5, (int)serviceSession.getUserDataAccess().createNewUser("testusr", "aaaaa", User::AccessLevel::Admin));

			delete webServiceDb;
		}

		TEST_METHOD(CreateUserDetails)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);

			Assert::AreEqual(5, (int)serviceSession.getUserDataAccess().createNewUser("testusr", "aaaaa", User::AccessLevel::Admin));
			Assert::AreEqual(5, (int)serviceSession.getUserDataAccess().createUserDetails("testusr", "aaaaa", "Teste", "Teste lastname", "aaaaa", "country", "city", 50));

			delete webServiceDb;
		}

		TEST_METHOD(UserExist)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);

			Assert::AreEqual(5, (int)serviceSession.getUserDataAccess().createNewUser("testusr", "aaaaa", User::AccessLevel::Admin));
			Assert::AreEqual(true, (bool)serviceSession.getUserDataAccess().userExist("testusr", "aaaaa"));


			delete webServiceDb;
		}

		TEST_METHOD(UserNameExist)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);

			Assert::AreEqual(5, (int)serviceSession.getUserDataAccess().createNewUser("testusr", "aaaaa", User::AccessLevel::Admin));
			Assert::AreEqual(true, (bool)serviceSession.getUserDataAccess().userNameExist("testusr"));


			delete webServiceDb;
		}

		TEST_METHOD(GetUserId)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);

			Assert::AreEqual(5, (int)serviceSession.getUserDataAccess().createNewUser("testusr", "aaaaa", User::AccessLevel::Admin));
			Assert::AreEqual(2, (int)serviceSession.getUserDataAccess().getUserId("testusr", "aaaaa"));


			delete webServiceDb;
		}

		TEST_METHOD(GetErrorLevelMessage_0)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);

			Assert::AreEqual(0, (int)serviceSession.getUserDataAccess().createNewUser("", "aaaaa", User::AccessLevel::Admin));
			Assert::AreEqual(std::string("Empty user name"), serviceSession.getUserDataAccess().getNewUserErrorLevelText(UserDataAccess::NewUserErrorLevel::EMPTY_USER_NAME));


			delete webServiceDb;
		}

		TEST_METHOD(GetErrorLevelMessage_1)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);

			Assert::AreEqual(1, (int)serviceSession.getUserDataAccess().createNewUser("testusr", "", User::AccessLevel::Admin));
			Assert::AreEqual(std::string("Empty password"), serviceSession.getUserDataAccess().getNewUserErrorLevelText(UserDataAccess::NewUserErrorLevel::EMPTY_PASSWORD));


			delete webServiceDb;
		}

		TEST_METHOD(GetErrorLevelMessage_2)
		{
			Wt::Dbo::SqlConnectionPool* webServiceDb = ServiceSession::createConnectionPool(":memory:");
			ServiceSession serviceSession(*webServiceDb);

			Assert::AreEqual(2, (int)serviceSession.getUserDataAccess().createNewUser("admin", "aaaa", User::AccessLevel::Admin));
			Assert::AreEqual(std::string("There is already a user with this user name"), serviceSession.getUserDataAccess().getNewUserErrorLevelText(UserDataAccess::NewUserErrorLevel::USER_EXIST));


			delete webServiceDb;
		}
	};
}