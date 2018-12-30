#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "code/control/ClassBaseOverlayDialog/baseoverlaydialog.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public BaseOverlayDialog
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget* parent = nullptr, QWidget* blurTarget = nullptr);
    ~LoginWidget() override;

public slots:
    void showDialog() override;

private slots:
    void onTryAuthorize();

private:
    void testEditFields();

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
