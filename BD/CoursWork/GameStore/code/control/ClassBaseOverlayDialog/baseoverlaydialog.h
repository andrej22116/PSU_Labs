#ifndef BASEOVERLAYDIALOG_H
#define BASEOVERLAYDIALOG_H

#include <QWidget>

class BaseOverlayDialog : public QWidget
{
    Q_OBJECT
public:
    explicit BaseOverlayDialog(QWidget* parent = nullptr, QWidget* blurTarget = nullptr);

public slots:
    virtual void showDialog();
    virtual void hideDialog();

private:
    bool eventFilter(QObject* obj, QEvent* ev) override;

private:
    QWidget* blurTarget;
};

#endif // BASEOVERLAYDIALOG_H
