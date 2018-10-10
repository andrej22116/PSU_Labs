#ifndef LOGINORREGISTERDIALOG_H
#define LOGINORREGISTERDIALOG_H

#include <QStateMachine>
#include <QObject>

#include "../ClassModalMessageOverlayWidget/modalmessageoverlaywidget.h"

class LoginOrRegisterDialog : public ModalMessageOverlayWidget
{
    Q_OBJECT

    QStateMachine* _stateMachine;
    QState* _authorization;
    QState* _registration;

    QWidget* _blurTarget;

public:
    explicit LoginOrRegisterDialog(QWidget* parent, QWidget* blurTarget = nullptr);
    ~LoginOrRegisterDialog() override;

public slots:
    void showLoginDialog();
    void showRegisterDialog();

private slots:
    void cancelDialog();

signals:
    void onShowLoginDialog();
    void onShowRegisterDialog();

};

#endif // LOGINORREGISTERDIALOG_H
