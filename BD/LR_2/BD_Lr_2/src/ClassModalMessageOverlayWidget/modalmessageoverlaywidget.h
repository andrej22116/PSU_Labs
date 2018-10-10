#ifndef MODALMESSAGEOVERLAYWIDGET_H
#define MODALMESSAGEOVERLAYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>

class ModalMessageOverlayWidget : public QWidget
{
    QWidget* _bluredWidget;

    QPropertyAnimation animation_show;
    QPropertyAnimation animation_hide;

public:
    explicit ModalMessageOverlayWidget(QWidget* parent = nullptr);
    ~ModalMessageOverlayWidget() override;

public slots:
    void showModal(QWidget* whatBluring = nullptr);
    void hideModal();

private slots:
    void endHide();

private:
    void setHideAnimation();
    void setShowAnimation();

    virtual bool eventFilter(QObject* obj, QEvent* ev) override;
};

#endif // MODALMESSAGEOVERLAYWIDGET_H
