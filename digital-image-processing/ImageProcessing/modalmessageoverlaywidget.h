#ifndef MODALMESSAGEOVERLAYWIDGET_H
#define MODALMESSAGEOVERLAYWIDGET_H

#include <QWidget>

class ModalMessageOverlayWidget : public QWidget
{
public:
    explicit ModalMessageOverlayWidget(QWidget* parent = nullptr);
    ~ModalMessageOverlayWidget() override;

public slots:
    virtual void showModal();
    virtual void hideModal();

private:
    bool eventFilter(QObject* obj, QEvent* ev) override;
};

#endif // MODALMESSAGEOVERLAYWIDGET_H
