#ifndef _REGISTERVIEW_H
#define _REGISTERVIEW_H

#include "CapitalStockImpl.h"
#include "../CapitalStockSession.h"
//#include "../../common/model/UserDetails.h"
#include "../../common/model/Models.h"

#include <Wt/WContainerWidget>
#include <Wt/WIntValidator>
#include <Wt/WLengthValidator>

class RegisterView
{
public:
	RegisterView(Wt::WContainerWidget* parent);

	// Create the register view
	// - CapitalStockSession* session = session instance
	// - CapitalStockImpl* csImplementation = caller instance ( used to make the page redirection )
	void bindRegisterView(CapitalStockSession* session, CapitalStockImpl* csImplementation);

private:
	// HOTFIX - use the user model to reduze the number of parameters
	//        - and turn the code more readble
	// Register the new user
	std::string doRegistration(std::string username, std::string password, UserDetails& userDetails, CapitalStockSession* session);

private:
	Wt::WContainerWidget* _parent;
};

#endif // !_REGISTERVIEW_H
