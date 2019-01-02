#include "messenger.h"

#include <QMessageBox>

void Messenger::error(const QString& message, QWidget* parent)
{
    QMessageBox errorMsgDialog(parent);
    errorMsgDialog.setModal(true);
    errorMsgDialog.setWindowTitle("Ошибка!");
    errorMsgDialog.setText(message);
    errorMsgDialog.setIcon(QMessageBox::Icon::Critical);
    errorMsgDialog.exec();
}
