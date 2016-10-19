#ifndef _HOMEVIEW_H
#define _HOMEVIEW_H

#include "CapitalStockImpl.h"
#include "../CapitalStockSession.h"

#include <string>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WLineEdit>

class HomeView
{
public:
	HomeView(Wt::WContainerWidget* parent);

	// Create the home view
	// - CapitalStockSession* session = session instance
	// - CapitalStockImpl* csImplementation = caller instance ( used to make the page redirection )
	void bindHomeView(CapitalStockSession* session, CapitalStockImpl* csImplementation);

private:
	Wt::WContainerWidget* _parent;
};

#endif
