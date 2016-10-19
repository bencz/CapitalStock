#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WServer>

#include "view/CapitalStockView.h"

#define WEBAPIURL "http://127.0.0.1:8081/"

class CapitalStokApplication : public Wt::WApplication
{
public:
	CapitalStokApplication(const Wt::WEnvironment& env)
		: Wt::WApplication(env)
	{
		root()->addWidget(new CapitalStockView("/", WEBAPIURL));
	}
};

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
	return new CapitalStokApplication(env);
}

int main(int argc, char *argv[])
{
	try
	{
		Wt::WServer server(argc, argv);
		server.addEntryPoint(Wt::Application, createApplication);
		server.run();
	}
	catch (Wt::WServer::Exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
}