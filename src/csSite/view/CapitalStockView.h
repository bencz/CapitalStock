#ifndef _CAPITALSTOCKSITE_H
#define _CAPITALSTOCKSITE_H

#include <string>
#include <Wt/WCompositeWidget>
#include <Wt/WContainerWidget>

#include "../CapitalStockSession.h"
#include "CapitalStockImpl.h"

class CapitalStockView : public Wt::WCompositeWidget
{
public:
	CapitalStockView(const std::string& basePath, const std::string& baseWebApiUrl, Wt::WContainerWidget* parent = 0);
	~CapitalStockView();

	void setInternalBasePath(const std::string& basePath);

private:
	CapitalStockImpl* _impl;
};

#endif