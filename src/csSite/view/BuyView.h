#ifndef _BUYVIEW_H
#define _BUYVIEW_H

#include "CapitalStockImpl.h"
#include "../CapitalStockSession.h"

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WLineEdit>

class BuyView
{
public:
	BuyView(Wt::WContainerWidget* parent);

	void bindBuyView(CapitalStockSession* session, CapitalStockImpl* csImplementation);

private:
	Wt::WContainerWidget* _parent;
};

#endif