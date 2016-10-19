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
#include <Wt/WStackedWidget>
#include <Wt/WBorderLayout>
#include <Wt/WPopupMenu>

#include "LoginView.h"
#include "RegisterView.h"
#include "CapitalStockView.h"
#include "HomeView.h"
#include "../Paths.h"

CapitalStockImpl::CapitalStockImpl(const std::string& basePath, const std::string& baseWebApiUrl, CapitalStockView* capitalStockView)
	: _basePath(basePath)
{
	Wt::WBootstrapTheme* wtBootstrapTheme = new Wt::WBootstrapTheme();
	wtBootstrapTheme->setVersion(Wt::WBootstrapTheme::Version3);
	wtBootstrapTheme->setResponsive(true);

	Wt::WApplication* app = wApp;
	app->setTheme(wtBootstrapTheme);
	app->setTitle("Capital Stock");
	app->messageResourceBundle().use(Wt::WApplication::appRoot() + "capitalstock");
	app->useStyleSheet("/css/capitalStok.css");
	app->internalPathChanged().connect(this, &CapitalStockImpl::handlePathChange);

	// Create the instance for session
	_session = new CapitalStockSession(baseWebApiUrl);

	// create the root node of page
	_root = this;
	getRoot()->setId("root");

	// Create the navigation menu
	_top = new Wt::WContainerWidget(getRoot());
	getTop()->setId("navigationBar");
	bindNavigationMenu();

	// Create the container with user details
	_userDetailsContainer = new Wt::WContainerWidget(getRoot());
	getUserDetailsContainer()->setId("userdetails");

	// Create the page content
	_content = new Wt::WContainerWidget(getRoot());
	getContent()->setId("content");
	getContent()->setHtmlTagName("div");

	// Create the footer of page
	_footer = new Wt::WTemplate(Wt::WString::tr("cs-footer"), getRoot());
	getFooter()->setId("footer");

	// Redirect to home page, in this page will be make every check to show the correcly values
	// If user are not loged, will show a message to register
	wApp->setInternalPath("/" + std::string(PATH_HOME));
	refresh();
}

CapitalStockImpl::~CapitalStockImpl()
{
	clear();
}

// change the base path and, if necessary, create the correclty view
void CapitalStockImpl::setInternalBasePath(const std::string& basePath)
{
	setBasePath(basePath);
	refresh();
}

// Refresh the base-path
void CapitalStockImpl::refresh()
{
	handlePathChange(wApp->internalPath());
}

// !!!!!!!!!!!! IMPORTANT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// -- THIS METHOD IS USED BY WT TO HANDLE THA PATH CHANGES
// -- DON'T USE THIS METHOD TO CHANGE THE PATH, FOR THIS, USE THE METHOD 
// -- setInternalBasePath(const std::string& basePath)
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// process the internal base redirection and execute the creation of correcty view
// const std::string urlPath = new base path
void CapitalStockImpl::handlePathChange(const std::string urlPath)
{
	Wt::WApplication* app = wApp;

	if (app->internalPathMatches(getBasePath()))
	{
		std::string path = app->internalPathNextPart(getBasePath());

		if (path.empty() || path == PATH_HOME)
			createHomeView();
		else if (path == PATH_LOGIN)
			createLoginView();
		else if (path == PATH_REGISTER)
			createRegisterView();
		else if (path == PATH_LOGOUT)
			userLogOut();
		else if (path == PATH_MYPROFILE) { }
		else if (path == PATH_BUY)
		{
			std::string stockIdCode = app->internalPathNextPart(getBasePath() + path + '/');
		}
		else
			_content->clear();
	}
}

// Create the naviagion menu
void CapitalStockImpl::bindNavigationMenu()
{
	getTop()->clear();

	Wt::WNavigationBar* navigation = new Wt::WNavigationBar(getTop());
	navigation->setTitle("Capital Stock", "http://www.google.com/search?q=Capital+Stock");
	navigation->setResponsive(true);

	Wt::WStackedWidget *contentsStack = new Wt::WStackedWidget(getTop());
	contentsStack->addStyleClass("contents");

	// Left-aligned menu.
	Wt::WMenu *leftMenu = new Wt::WMenu(contentsStack, getTop());
	navigation->addMenu(leftMenu, Wt::AlignLeft);
	leftMenu->addItem("Home")->setLink(Wt::WLink(Wt::WLink::InternalPath, "/" + std::string(PATH_HOME)));

	// Right-aligned menu
	Wt::WMenu *rightMenu = new Wt::WMenu(contentsStack, getTop());
	navigation->addMenu(rightMenu, Wt::AlignRight);

	// Create diff menu itens if user are loged or not
	if (getSession()->isUserLoged())
	{
		// Create a pop-up menu for "the user profile"
		Wt::WPopupMenu* popup = new Wt::WPopupMenu();
		popup->addItem("My portifolio")->setLink(Wt::WLink(Wt::WLink::InternalPath, "/" + std::string(PATH_MYPROFILE)));
		popup->addSeparator();
		popup->addItem("My profile");

		Wt::WMenuItem* menuItem = new Wt::WMenuItem("My profile");
		menuItem->setMenu(popup);

		rightMenu->addItem(menuItem);
		rightMenu->addItem("logout")->setLink(Wt::WLink(Wt::WLink::InternalPath, "/" + std::string(PATH_LOGOUT)));
	}
	else
	{
		rightMenu->addItem("Login")->setLink(Wt::WLink(Wt::WLink::InternalPath, "/" + std::string(PATH_LOGIN)));
		rightMenu->addItem("Register")->setLink(Wt::WLink(Wt::WLink::InternalPath, "/" + std::string(PATH_REGISTER)));
	}

	getTop()->addWidget(contentsStack);
}

// Create OR update the user details on top of page
void CapitalStockImpl::bindUserDetailsContainer()
{
	if (!getSession()->isUserLoged())
	{
		getUserDetailsContainer()->clear();
		return;
	}

	UserDetails* usrdet = getSession()->getUserRepository()->getUserDetails();
	std::string name = usrdet->getName();
	std::string lastName = usrdet->getLastname();
	std::string fullName = name + " " + lastName;

	Wt::WTemplate *t = new Wt::WTemplate(Wt::WString::tr("cs-user-details"), getUserDetailsContainer());
	Wt::WText* userFullName = new Wt::WText();
	userFullName->setText(fullName);
	t->bindWidget("userfullname", userFullName);

	Wt::WText* userCash = new Wt::WText();
	userCash->setText(toString(getSession()->getUserRepository()->getUserCash()));
	t->bindWidget("totalcash", userCash);
}

// Create the login view
void CapitalStockImpl::createLoginView()
{
	// Only show login view if user are not loged, otherwise the user is redirected to home
	if (!getSession()->isUserLoged())
	{
		// create login view instance
		LoginView loginView(getContent());
		loginView.bindLoginView(getSession(), this);
	}
	else
		wApp->setInternalPath("/" + std::string(PATH_HOME), true);
}

// Create the register view
void CapitalStockImpl::createRegisterView()
{
	// only show the register view if user are not loged
	if (!getSession()->isUserLoged())
	{
		// create register view instance
		RegisterView registerView(getContent());
		registerView.bindRegisterView(getSession(), this);
	}
	else
		wApp->setInternalPath("/" + std::string(PATH_HOME), true);
}

// Create the home view
void CapitalStockImpl::createHomeView()
{
	HomeView homeView(getContent());
	homeView.bindHomeView(getSession(), this);

	// recreate the nav. menu if user are loged
	recreateNavigationMenu();
	bindUserDetailsContainer();
}

// Create the buy view
void CapitalStockImpl::createBuyView(int stockId)
{

}

// execute the logout
void CapitalStockImpl::userLogOut()
{
	// Only execute the logout if user are loged...
	if (getSession()->isUserLoged())
		getSession()->doLogOut();
	
	wApp->setInternalPath("/" + std::string(PATH_HOME), true);
}

// Get the base path
std::string CapitalStockImpl::getBasePath()
{
	return _basePath;
}

// recreate the navigation menu
void CapitalStockImpl::recreateNavigationMenu()
{
	bindNavigationMenu();
}
