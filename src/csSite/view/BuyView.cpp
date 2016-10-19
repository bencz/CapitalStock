#include "BuyView.h"

BuyView::BuyView(Wt::WContainerWidget * parent) 
	: _parent(parent)
{
	_parent->clear();
}

void BuyView::bindBuyView(CapitalStockSession* session, CapitalStockImpl* csImplementation)
{
}