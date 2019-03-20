#include "WaitAnimationOverlayWidget.hpp"
#include <QGridLayout>


WaitAnimationOverlayWidget::WaitAnimationOverlayWidget(int maxSize, QWidget* parent) :
    ModalMessageOverlayWidget(parent),
    _indicator(new QProgressIndicator{ parent })
{
    auto layout = new QGridLayout{ this };
    layout->addWidget( _indicator );
    setLayout(layout);

    _indicator->setMaximumSize(maxSize, maxSize);

    hide();
}

void WaitAnimationOverlayWidget::showModal()
{
    ModalMessageOverlayWidget::showModal();
    _indicator->startAnimation();
}

void WaitAnimationOverlayWidget::hideModal()
{
    ModalMessageOverlayWidget::hideModal();
    _indicator->stopAnimation();
}
