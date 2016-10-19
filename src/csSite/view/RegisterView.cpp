#include "RegisterView.h"
#include "../Paths.h"
#include "../../common/StringHelper.h"
//#include "../../common/model/UserDetails.h"
#include "../../common/model/Models.h"

#include <Wt/WIntValidator>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WSpinBox>
#include <Wt/WText>
#include <Wt/WLengthValidator>

RegisterView::RegisterView(Wt::WContainerWidget* parent)
	: _parent(parent)
{
	_parent->clear();
}

void RegisterView::bindRegisterView(CapitalStockSession * session, CapitalStockImpl * csImplementation)
{
	Wt::WTemplate *t = new Wt::WTemplate(Wt::WString::tr("cs-register-form"), _parent);
	t->addFunction("id", &Wt::WTemplate::Functions::id);

	/*----------------------------------------------*/
	// create the text validator
	Wt::WLengthValidator* textValidator = new Wt::WLengthValidator();
	textValidator->setMandatory(true);
	textValidator->setMinimumLength(4);
	textValidator->setMaximumLength(256);

	// create the int validator
	Wt::WIntValidator* intValidator = new Wt::WIntValidator(16, 150);
	intValidator->setMandatory(true);
	/*----------------------------------------------*/

	/*----------------------------------------------*/
	// Create the LineEdit for username and bind it with template
	Wt::WLineEdit* userNameEdit = new Wt::WLineEdit();
	userNameEdit->setValidator(textValidator);
	t->bindWidget("user-name", userNameEdit);

	// Create the LineEdit for password and bind it with template
	Wt::WLineEdit* passwordEdit = new Wt::WLineEdit();
	passwordEdit->setValidator(textValidator);
	passwordEdit->setEchoMode(Wt::WLineEdit::EchoMode::Password);
	t->bindWidget("password", passwordEdit);

	// Create the LineEdit for re-typed password and bind it with template
	Wt::WLineEdit* password2Edit = new Wt::WLineEdit();
	password2Edit->setValidator(textValidator);
	password2Edit->setEchoMode(Wt::WLineEdit::EchoMode::Password);
	t->bindWidget("password-retype", password2Edit);

	// Create the LineEdit for first name and bind it with template
	Wt::WLineEdit* firstNameEdit = new Wt::WLineEdit();
	firstNameEdit->setValidator(textValidator);
	t->bindWidget("first-name", firstNameEdit);

	// Create the LineEdit for last name and bind it with template
	Wt::WLineEdit* lastNameEdit = new Wt::WLineEdit();
	lastNameEdit->setValidator(textValidator);
	t->bindWidget("last-name", lastNameEdit);

	// Create the Spinbox for age and bind it with template
	Wt::WSpinBox* ageSpinBox = new Wt::WSpinBox();
	ageSpinBox->setMinimum(16);
	ageSpinBox->setMaximum(150);
	ageSpinBox->setValidator(intValidator);
	t->bindWidget("age", ageSpinBox);

	// Create the LineEdit for email and bind it with template
	Wt::WLineEdit* emailEdit = new Wt::WLineEdit();
	emailEdit->setValidator(textValidator);
	t->bindWidget("email", emailEdit);

	// Create the LineEdit for country and bind it with template
	Wt::WLineEdit* countryEdit = new Wt::WLineEdit();
	countryEdit->setValidator(textValidator);
	t->bindWidget("country", countryEdit);

	// Create the LineEdit for city and bind it with template
	Wt::WLineEdit* cityEdit = new Wt::WLineEdit();
	cityEdit->setValidator(textValidator);
	t->bindWidget("city", cityEdit);

	// Create the error box
	Wt::WText* errorText = new Wt::WText();
	errorText->setInline(false);
	errorText->hide();
	errorText->setStyleClass("alert alert-danger");
	t->bindWidget("registration-error", errorText);

	// Create the registration button
	Wt::WPushButton *button = new Wt::WPushButton("Register");
	t->bindWidget("button", button);
	/*----------------------------------------------*/

	/************************************************/
	// Event handle
	/************************************************/
	button->clicked().connect(std::bind([=]() {
		errorText->hide();

		// Validate username edit
		if (userNameEdit->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Invalid user name");
			userNameEdit->setFocus();
			return;
		}

		// Validate password edit
		if (passwordEdit->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Invalid password");
			passwordEdit->setFocus();
			return;
		}

		// Validate retype password edit
		if (password2Edit->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Invalid retype password");
			password2Edit->setFocus();
			return;
		}

		// Validate name edit
		if (firstNameEdit->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Type your name");
			firstNameEdit->setFocus();
			return;
		}

		// Validate lastname edit
		if (lastNameEdit->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Type last name");
			lastNameEdit->setFocus();
			return;
		}

		// Validate agespin
		if (ageSpinBox->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Invalid age");
			ageSpinBox->setFocus();
			return;
		}

		// Validate username edit
		if (emailEdit->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Type an email");
			emailEdit->setFocus();
			return;
		}

		// Validate country edit
		if (countryEdit->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Type the country");
			countryEdit->setFocus();
			return;
		}

		// Validate vity edit
		if (cityEdit->validate() != Wt::WValidator::Valid)
		{
			errorText->show();
			errorText->setText("Type the city");
			cityEdit->setFocus();
			return;
		}

		// Check if password as the same
		if (passwordEdit->text() != password2Edit->text())
		{
			errorText->show();
			errorText->setText("Password not match");
			passwordEdit->setFocus();
			return;
		}

		// Create the model of user Details
		UserDetails usrDet;
		usrDet.setName(firstNameEdit->text().toUTF8().c_str());
		usrDet.setLastname(lastNameEdit->text().toUTF8().c_str());
		usrDet.setEmail(emailEdit->text().toUTF8().c_str());
		usrDet.setCountry(countryEdit->text().toUTF8().c_str());
		usrDet.setCity(cityEdit->text().toUTF8().c_str());
		std::string age = std::string(ageSpinBox->text().toUTF8().c_str());
		usrDet.setAge(toInt(age));

		// do the registration
		std::string result = doRegistration(
			userNameEdit->text().toUTF8().c_str(),
			passwordEdit->text().toUTF8().c_str(),
			usrDet,
			session);

		if (trim(result).size() != 0)
		{
			errorText->show();
			errorText->setText(result);
			errorText->setFocus();
		}
		else
		{
			// do the login!! :)
			session->setUserLoged();
			wApp->setInternalPath(csImplementation->getBasePath() + std::string(PATH_HOME), true);
		}
	}));
	
	cityEdit->enterPressed().connect(std::bind([=]() {
		button->clicked().emit(Wt::WMouseEvent());
	}));
}

std::string RegisterView::doRegistration(std::string username, std::string password, UserDetails& userDetails, CapitalStockSession * session)
{
	std::string result = session->getUserRepository()->registerUser(username, password, userDetails);
	return result;
}
