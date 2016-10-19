#include "CapitalStockView.h"

CapitalStockView::CapitalStockView(const std::string& basePath, const std::string& baseWebApiUrl, Wt::WContainerWidget* parent)
	: Wt::WCompositeWidget(parent)
{
	_impl = new CapitalStockImpl(basePath, baseWebApiUrl, this);
	setImplementation(_impl);
}

void CapitalStockView::setInternalBasePath(const std::string& basePath)
{
	_impl->setInternalBasePath(basePath);
}

CapitalStockView::~CapitalStockView()
{
}
