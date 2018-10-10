#include "modalmessageoverlaywidget.h"
//#include <QPainter>
//#include <QBoxLayout>
//#include <QPushButton>

#include <QEvent>
#include <QResizeEvent>


#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>

ModalMessageOverlayWidget::ModalMessageOverlayWidget(QWidget* parent)
    : QWidget(parent)
{
    if (parent)
    {
        parent->installEventFilter(this);
        this->resize(parent->size());
    }

    auto opacityEffect = new QGraphicsOpacityEffect();
    this->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0);
    animation_show.setTargetObject(opacityEffect);
    animation_show.setPropertyName("opacity");
    animation_hide.setTargetObject(opacityEffect);
    animation_hide.setPropertyName("opacity");

    this->setStyleSheet(".QWidget { background-color: rgba(0,0,0, 150); } ");

    connect(&animation_hide, &QAbstractAnimation::finished, this, &ModalMessageOverlayWidget::endHide);

    /*
    auto button = new QPushButton("Закрыть!");
    auto layout = new QBoxLayout(QBoxLayout::TopToBottom);

    button->setFont({"times,times new roman", 32});
    button->setWindowOpacity(0.5);

    layout->addWidget(button);
    this->setLayout(layout);

    connect(button, &QPushButton::pressed, this, &ModalMessageOverlayWidget::hideModal);
    */
}

ModalMessageOverlayWidget::~ModalMessageOverlayWidget()
{
    if (_bluredWidget)
    {
        _bluredWidget->setGraphicsEffect(nullptr);
    }
}

void ModalMessageOverlayWidget::showModal(QWidget* whatBluring)
{
    if (this->isVisible())
    {
        return;
    }

    _bluredWidget = whatBluring;
    if (_bluredWidget)
    {
        auto blur = new QGraphicsBlurEffect();
        blur->setBlurRadius(18);
        blur->setBlurHints(QGraphicsBlurEffect::AnimationHint);
        _bluredWidget->setGraphicsEffect(blur);
    }

    setShowAnimation();
    animation_show.start();
}


void ModalMessageOverlayWidget::hideModal()
{
    if (!this->isVisible())
    {
        return;
    }

    setHideAnimation();
    animation_hide.start();
}


void ModalMessageOverlayWidget::setShowAnimation()
{
    animation_show.setDuration(160);
    animation_show.setStartValue(0.0);
    animation_show.setEndValue(1.0);
    show();
}


void ModalMessageOverlayWidget::setHideAnimation()
{
    animation_hide.setDuration(100);
    animation_hide.setStartValue(1.0);
    animation_hide.setEndValue(0.0);
}


void ModalMessageOverlayWidget::endHide()
{
    if (_bluredWidget)
    {
        _bluredWidget->setGraphicsEffect(nullptr);
    }

    this->hide();
}



bool ModalMessageOverlayWidget::eventFilter(QObject* obj, QEvent* ev)
{
    if (obj == parent())
    {
        if (ev->type() == QEvent::Resize)
        {
           resize(static_cast<QResizeEvent*>(ev)->size());
        }
    }
    return QWidget::eventFilter(obj, ev);
}
