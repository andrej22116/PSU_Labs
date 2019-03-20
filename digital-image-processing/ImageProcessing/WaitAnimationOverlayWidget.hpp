#ifndef WAITANIMATIONOVERLAYWIDGET_HPP
#define WAITANIMATIONOVERLAYWIDGET_HPP


#include "modalmessageoverlaywidget.h"
#include "QProgressIndicator.h"


class WaitAnimationOverlayWidget : public ModalMessageOverlayWidget
{
public:
    WaitAnimationOverlayWidget(int maxSize, QWidget* parent = nullptr);
    ~WaitAnimationOverlayWidget() override {}

    void showModal() override;
    void hideModal() override;

private:
    QProgressIndicator* _indicator;
};

#endif // WAITANIMATIONOVERLAYWIDGET_HPP
