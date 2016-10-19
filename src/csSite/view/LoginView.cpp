#include "LoginView.h"
#include "CapitalStockView.h"
#include "../Paths.h"

#include <Wt/WIntValidator>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WLengthValidator>

LoginView::LoginView(Wt::WContainerWidget* parent)
	: _parent(parent)
{
	_parent->clear();
}

void LoginView::bindLoginView(CapitalStockSession* session, CapitalStockImpl* csImplementation)
{
	Wt::WTemplate *t = new Wt::WTemplate(Wt::WString::tr("cs-login-form"), _parent);
	t->addFunction("id", &Wt::WTemplate::Functions::id);

	// Create the validator
	Wt::WLengthValidator *v = new Wt::WLengthValidator();
	v->setMandatory(true);
	v->setMinimumLength(4);
	v->setMaximumLength(15);

	// Create the LineEdit for username and bind it with template
	Wt::WLineEdit* usernameEdit = new Wt::WLineEdit();
	usernameEdit->setValidator(v);
	t->bindWidget("username", usernameEdit);

	// Create the LineEdit for password and bind it with template
	Wt::WLineEdit* passwordEdit = new Wt::WLineEdit();
	passwordEdit->setEchoMode(Wt::WLineEdit::EchoMode::Password);
	passwordEdit->setValidator(v);
	t->bindWidget("password", passwordEdit);

	// Create the login button
	Wt::WPushButton *button = new Wt::WPushButton("Login");
	t->bindWidget("button", button);

	// Error message
	Wt::WText* errorText = new Wt::WText();
	errorText->setInline(false);
	errorText->hide();
	errorText->setStyleClass("alert alert-danger");
	t->bindWidget("login-error", errorText);

	button->clicked().connect(std::bind([=]() {
		errorText->hide();
		// Validate the user name text field
		if (usernameEdit->validate() == Wt::WValidator::Invalid)
		{
			errorText->show();
			errorText->setText("Invalid user name");
			usernameEdit->setFocus();
			return;
		}
		else if (usernameEdit->validate() == Wt::WValidator::InvalidEmpty)
		{
			errorText->show();
			errorText->setText("Type a user name");
			usernameEdit->setFocus();
			return;
		}

		// Validate the user name password field
		if (passwordEdit->validate() == Wt::WValidator::Invalid)
		{
			errorText->show();
			errorText->setText("Type a password");
			passwordEdit->setFocus();
			return;
		}
		else if (passwordEdit->validate() == Wt::WValidator::InvalidEmpty)
		{
			errorText->show();
			errorText->setText("Type a password");
			passwordEdit->setFocus();
			return;
		}

		// Everything is fine here :)
		bool userIsValid = doLogin(usernameEdit->text().toUTF8().c_str(), passwordEdit->text().toUTF8().c_str(), session);
		if (!userIsValid)
		{
			errorText->show();
			errorText->setText("User name or password are invalid!");
			usernameEdit->setFocus();
		}
		else
		{
			csImplementation->recreateNavigationMenu();
			wApp->setInternalPath(csImplementation->getBasePath() + std::string(PATH_HOME), true);
		}
	}));

	passwordEdit->enterPressed().connect(std::bind([=]() {
		button->clicked().emit(Wt::WMouseEvent());
	}));
}

bool LoginView::doLogin(std::string username, std::string password, CapitalStockSession* session)
{
	session->getUserRepository()->authenticateUser(username, password);
	if (!session->getUserRepository()->getUserIsValid())
		return false;

	session->setUserLoged();
	return true;
}
