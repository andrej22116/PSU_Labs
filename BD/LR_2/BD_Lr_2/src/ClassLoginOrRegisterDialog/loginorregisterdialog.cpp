#include "loginorregisterdialog.h"

#include <QStateMachine>
#include <QSignalTransition>

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QDebug>

#include <QGraphicsOpacityEffect>

LoginOrRegisterDialog::LoginOrRegisterDialog(QWidget* parent, QWidget* blurTarget) :
    ModalMessageOverlayWidget(parent),
    _blurTarget(blurTarget)
{
    auto layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    auto editLine_userFirstName = new QLineEdit();
    auto editLine_userLastName = new QLineEdit();
    auto editLine_login = new QLineEdit();
    auto editLine_password = new QLineEdit();
    auto editLine_repeatPassword = new QLineEdit();

    auto button_authorization = new QPushButton("Есть аккаунт (авторизация)");
    auto button_registracion = new QPushButton("Нет аккаунта (регистрация)");
    auto button_register = new QPushButton("Зарегестрировать");
    auto button_login = new QPushButton("Авторизоваться");

    auto button_cancel = new QPushButton("Отмена");

    connect(button_cancel, &QPushButton::pressed, this, &LoginOrRegisterDialog::cancelDialog);

    //auto lableLogin = new QLabel("Авторизация");

    QString lineEditStyleSheet = "QWidget {"
            "height: 50px;"
            //"font-size: 24px;"
            "padding-left: 10px;"
            "border-radius: 10px;"
            "background-color: rgba(0, 0, 0, 100);"
            "border: 2px solid rgb(180, 180, 235);"
            "color: rgb(255, 255, 255);"
        "};";

    editLine_password->setEchoMode(QLineEdit::Password);
    editLine_repeatPassword->setEchoMode(QLineEdit::Password);


    editLine_userFirstName->setPlaceholderText("Имя пользователя");
    editLine_userLastName->setPlaceholderText("Фамилия пользователя");
    editLine_login->setPlaceholderText("Логин");
    editLine_password->setPlaceholderText("Пароль");
    editLine_repeatPassword->setPlaceholderText("Повторите пароль");

    editLine_userFirstName->setToolTip("Укажите здесь ваше имя!");
    editLine_userLastName->setToolTip("Укажите здесь вашу фамилию!");
    editLine_login->setToolTip("Логин - ваш псевдоним.\nИспользуется для идентификации\nи для авторизации!");
    editLine_password->setToolTip("Пароль - ваш секретный ключ для входа в матрицу.\nНикому не показывайте его!");
    editLine_repeatPassword->setToolTip("Повторите здесь пароль.\nТак мы убедимся, что он корректный!");

    QSize maxSize(400, 50);
    editLine_login->setMaximumSize(maxSize);
    editLine_password->setMaximumSize(maxSize);
    button_login->setMaximumSize(maxSize);
    editLine_userFirstName->setMaximumSize(maxSize);
    editLine_userLastName->setMaximumSize(maxSize);
    editLine_repeatPassword->setMaximumSize(maxSize);
    button_registracion->setMaximumSize(maxSize);
    button_register->setMaximumSize(maxSize);
    button_authorization->setMaximumSize(maxSize);
    button_cancel->setMaximumSize(maxSize);

    editLine_login->setMinimumSize(maxSize);
    editLine_password->setMinimumSize(maxSize);
    button_login->setMinimumSize(maxSize);
    editLine_userFirstName->setMinimumSize(maxSize);
    editLine_userLastName->setMinimumSize(maxSize);
    editLine_repeatPassword->setMinimumSize(maxSize);
    button_registracion->setMinimumSize(maxSize);
    button_register->setMinimumSize(maxSize);
    button_authorization->setMinimumSize(maxSize);
    button_cancel->setMinimumSize(maxSize);


    editLine_login->setStyleSheet(lineEditStyleSheet);
    editLine_password->setStyleSheet(lineEditStyleSheet);
    editLine_userFirstName->setStyleSheet(lineEditStyleSheet);
    editLine_userLastName->setStyleSheet(lineEditStyleSheet);
    editLine_repeatPassword->setStyleSheet(lineEditStyleSheet);


    layout->addStretch();
    layout->addWidget(editLine_userFirstName, 0, Qt::AlignHCenter);
    layout->addWidget(editLine_userLastName, 0, Qt::AlignHCenter);

    layout->addSpacing(50);

    layout->addWidget(editLine_login, 0, Qt::AlignHCenter);
    layout->addWidget(editLine_password, 0, Qt::AlignHCenter);
    layout->addWidget(editLine_repeatPassword, 0, Qt::AlignHCenter);

    layout->addSpacing(50);

    layout->addWidget(button_login, 0, Qt::AlignHCenter);
    layout->addWidget(button_register, 0, Qt::AlignHCenter);
    layout->addWidget(button_registracion, 0, Qt::AlignHCenter);
    layout->addWidget(button_authorization, 0, Qt::AlignHCenter);

    layout->addSpacing(50);

    layout->addWidget(button_cancel, 0, Qt::AlignHCenter);

    layout->addStretch();


    int minHeight = 0;
    int maxHeight = 50;

    _authorization = new QState();
    _authorization->assignProperty(editLine_userFirstName, "maximumHeight", minHeight);
    _authorization->assignProperty(editLine_userFirstName, "minimumHeight", minHeight);

    _authorization->assignProperty(editLine_userLastName, "maximumHeight", minHeight);
    _authorization->assignProperty(editLine_userLastName, "minimumHeight", minHeight);

    _authorization->assignProperty(editLine_repeatPassword, "maximumHeight", minHeight);
    _authorization->assignProperty(editLine_repeatPassword, "minimumHeight", minHeight);

    _authorization->assignProperty(button_authorization, "maximumHeight", minHeight);
    _authorization->assignProperty(button_authorization, "minimumHeight", minHeight);

    _authorization->assignProperty(button_register, "maximumHeight", minHeight);
    _authorization->assignProperty(button_register, "minimumHeight", minHeight);

    _authorization->assignProperty(button_registracion, "maximumHeight", maxHeight);
    _authorization->assignProperty(button_registracion, "minimumHeight", maxHeight);

    _authorization->assignProperty(button_login, "maximumHeight", maxHeight);
    _authorization->assignProperty(button_login, "minimumHeight", maxHeight);

    _registration = new QState();
    _registration->assignProperty(editLine_userFirstName, "maximumHeight", maxHeight);
    _registration->assignProperty(editLine_userFirstName, "minimumHeight", maxHeight);

    _registration->assignProperty(editLine_userLastName, "maximumHeight", maxHeight);
    _registration->assignProperty(editLine_userLastName, "minimumHeight", maxHeight);

    _registration->assignProperty(editLine_repeatPassword, "maximumHeight", maxHeight);
    _registration->assignProperty(editLine_repeatPassword, "minimumHeight", maxHeight);

    _registration->assignProperty(button_authorization, "maximumHeight", maxHeight);
    _registration->assignProperty(button_authorization, "minimumHeight", maxHeight);

    _registration->assignProperty(button_register, "maximumHeight", maxHeight);
    _registration->assignProperty(button_register, "minimumHeight", maxHeight);

    _registration->assignProperty(button_registracion, "maximumHeight", minHeight);
    _registration->assignProperty(button_registracion, "minimumHeight", minHeight);

    _registration->assignProperty(button_login, "maximumHeight", minHeight);
    _registration->assignProperty(button_login, "minimumHeight", minHeight);



    auto authorizationTrans = _authorization->addTransition(button_registracion, &QPushButton::pressed, _registration);
    authorizationTrans->addAnimation(new QPropertyAnimation(editLine_userFirstName, "maximumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(editLine_userFirstName, "minimumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(editLine_userLastName, "maximumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(editLine_userLastName, "minimumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(editLine_repeatPassword, "maximumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(editLine_repeatPassword, "minimumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(button_authorization, "maximumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(button_authorization, "minimumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(button_register, "maximumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(button_register, "minimumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(button_registracion, "maximumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(button_registracion, "minimumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(button_login, "maximumHeight"));
    authorizationTrans->addAnimation(new QPropertyAnimation(button_login, "minimumHeight"));

    auto registrationTrans = _registration->addTransition(button_authorization, &QPushButton::pressed, _authorization);
    registrationTrans->addAnimation(new QPropertyAnimation(editLine_userFirstName, "maximumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(editLine_userFirstName, "minimumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(editLine_userLastName, "maximumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(editLine_userLastName, "minimumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(editLine_repeatPassword, "maximumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(editLine_repeatPassword, "minimumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(button_authorization, "maximumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(button_authorization, "minimumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(button_register, "maximumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(button_register, "minimumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(button_registracion, "maximumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(button_registracion, "minimumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(button_login, "maximumHeight"));
    registrationTrans->addAnimation(new QPropertyAnimation(button_login, "minimumHeight"));

    _authorization->addTransition(this, &LoginOrRegisterDialog::onShowRegisterDialog, _registration);
    _registration->addTransition(this, &LoginOrRegisterDialog::onShowLoginDialog, _authorization);

    _stateMachine = new QStateMachine(this);
    _stateMachine->addState(_authorization);
    _stateMachine->addState(_registration);
    _stateMachine->setInitialState(_authorization);

    _stateMachine->setAnimated(true);

    _stateMachine->start();
}

LoginOrRegisterDialog::~LoginOrRegisterDialog()
{
    //delete _loginWidget;
    //delete _registerWidget;
}


void LoginOrRegisterDialog::showLoginDialog()
{
    //qDebug() << "Show login dialog!";
    //_registration->addTransition(_authorization);
    emit onShowLoginDialog();
    showModal(_blurTarget);
}


void LoginOrRegisterDialog::showRegisterDialog()
{
    //_authorization->addTransition(_registration);
    emit onShowRegisterDialog();
    showModal(_blurTarget);
}


void LoginOrRegisterDialog::cancelDialog()
{
    hideModal();
}
