#ifndef _CAPITALSTOCKIMPL_H
#define _CAPITALSTOCKIMPL_H

#include <string>
#include <Wt/WCompositeWidget>
#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WLink>
#include <Wt/WBootstrapTheme>
#include <Wt/WNavigationBar>
#include <Wt/WMenu>

#include "../CapitalStockSession.h"

// Avoid circular dependency
class CapitalStockView;

class CapitalStockImpl : public Wt::WContainerWidget
{
public:
	CapitalStockImpl(const std::string& basePath, const std::string& baseWebApiUrl, CapitalStockView* capitalStockView);
	~CapitalStockImpl();

	// set the internal base path and refresh the page
	void setInternalBasePath(const std::string& basePath);
	// Get _basePath
	std::string getBasePath();
	// Re-create the nav-menu after login
	void recreateNavigationMenu();

// Private methods
private:
	// refresh page
	void refresh();
	// handle and URL is changed
	void handlePathChange(const std::string urlPath);
	// create the navigation menu
	void bindNavigationMenu();
	// Create OR update the user details on top of page
	void bindUserDetailsContainer();
	// Create the login form
	void createLoginView();
	// Create the register form
	void createRegisterView();
	// Create the home view
	void createHomeView();
	// Create the buy view
	void createBuyView(int stockId);
	// Execute logout event
	void userLogOut();

	// Accessors to every view components private fields ( just GETs )
	Wt::WContainerWidget* getRoot() { return _root; }
	Wt::WTemplate* getFooter() { return _footer; }
	Wt::WContainerWidget* getTop() { return _top; }
	Wt::WContainerWidget* getContent() { return _content; }
	Wt::WContainerWidget* getUserDetailsContainer() { return _userDetailsContainer;  }
	Wt::WNavigationBar* getNavigationMenu() { return _navigation; }

	// Accessor to basePath
	void setBasePath(const std::string basePath) { _basePath = basePath; }

	// Accessor to session
	CapitalStockSession* getSession() { return _session; }

// Private variables
private:
	std::string _basePath;

	// View components
	Wt::WContainerWidget* _root;
	Wt::WTemplate* _footer;
	Wt::WContainerWidget* _top;
	Wt::WContainerWidget* _userDetailsContainer;
	Wt::WContainerWidget* _content;
	Wt::WNavigationBar* _navigation;

	// Session instance
	CapitalStockSession* _session;
};

#endif