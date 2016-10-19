#include "HomeView.h"
#include "../Paths.h"

#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WAnchor>
#include <Wt/WContainerWidget>
#include <Wt/WLink>

HomeView::HomeView(Wt::WContainerWidget* parent)
	: _parent(parent)
{
	_parent->clear();
}

void HomeView::bindHomeView(CapitalStockSession* session, CapitalStockImpl* csImplementation)
{
	Wt::WTemplate *t = new Wt::WTemplate(Wt::WString::tr("cs-home-form"), _parent);

	Wt::WTable* table = new Wt::WTable();
	table->setHeaderCount(1);	
	table->setWidth(Wt::WLength("100%"));
	table->addStyleClass("table form-inline");
	table->toggleStyleClass("table-bordered", true);
	table->toggleStyleClass("table-condensed", true);
	t->bindWidget("table", table);
	
	table->elementAt(0, 0)->addWidget(new Wt::WText("Code"));
	table->elementAt(0, 1)->addWidget(new Wt::WText("Company"));
	table->elementAt(0, 2)->addWidget(new Wt::WText("Value"));
	table->elementAt(0, 3)->addWidget(new Wt::WText("Updated"));

	if (session->isUserLoged())
		table->elementAt(0, 4)->addWidget(new Wt::WText("Buy"));

	int row = 1;
	// Get the elements
	std::vector<Stock> elements = session->getStockRepository()->getListStock(20);
	for (std::vector<Stock>::iterator it = elements.begin();it != elements.end();++it)
	{
		Stock stk = *it;
		table->elementAt(row, 0)->addWidget(new Wt::WText(stk.getStockCode()));
		table->elementAt(row, 1)->addWidget(new Wt::WText(stk.getCompanyName()));
		table->elementAt(row, 2)->addWidget(new Wt::WText(toString(stk.getLastSalePrice())));
		table->elementAt(row, 3)->addWidget(new Wt::WText(stk.getLastUpdate().toString("MM/dd/yy")));
		if (session->isUserLoged())
		{
			std::string internalPathStr = "/" + std::string(PATH_BUY) + "/" + std::to_string(stk.getStockId());
			table->elementAt(row, 4)->addWidget(new Wt::WAnchor(Wt::WLink(Wt::WLink::InternalPath, internalPathStr), "Buy"));
		}
		row++;
	}
}
