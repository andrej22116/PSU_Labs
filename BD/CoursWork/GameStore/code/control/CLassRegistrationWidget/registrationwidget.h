#ifndef REGISTRATIONWIDGET_H
#define REGISTRATIONWIDGET_H

#include "code/control/ClassBaseOverlayDialog/baseoverlaydialog.h"

namespace Ui {
class RegistrationWidget;
}

class RegistrationWidget : public BaseOverlayDialog
{
    Q_OBJECT

public:
    explicit RegistrationWidget(QWidget* parent = nullptr, QWidget* blurTarget = nullptr);
    ~RegistrationWidget();

public slots:
    void showDialog() override;

private slots:
    void onTryRegistration();

private:
    void testEditFields();

private:
    Ui::RegistrationWidget *ui;
};

#endif // REGISTRATIONWIDGET_H
