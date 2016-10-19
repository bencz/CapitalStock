#ifndef _LOGINVIEW_H
#define _LOGINVIEW_H

#include "CapitalStockImpl.h"
#include "../CapitalStockSession.h"

#include <string>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WLineEdit>

class LoginView
{
public:
	LoginView(Wt::WContainerWidget* parent);

	// Create the login view
	// - CapitalStockSession* session = session instance
	// - CapitalStockImpl* csImplementation = caller instance ( used to make the page redirection )
	void bindLoginView(CapitalStockSession* session, CapitalStockImpl* csImplementation);

private:
	// Execute the login process
	// - std::string username = user name
	// - std::string password = password 
	// - CapitalStockSession* session = session instance
	bool doLogin(std::string username, std::string password, CapitalStockSession* session);

private:
	Wt::WContainerWidget* _parent;
};

#endif