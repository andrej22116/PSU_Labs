#include "modalmessageoverlaywidget.h"
//#include <QPainter>
//#include <QBoxLayout>
//#include <QPushButton>

#include <QEvent>
#include <QResizeEvent>

ModalMessageOverlayWidget::ModalMessageOverlayWidget(QWidget* parent)
    : QWidget(parent)
{
    if (parent)
    {
        parent->installEventFilter(this);
        this->resize(parent->size());
    }

    this->setStyleSheet(".QWidget { background-color: rgba(255, 255, 255, 220); } ");
}

ModalMessageOverlayWidget::~ModalMessageOverlayWidget()
{
}

void ModalMessageOverlayWidget::showModal()
{
    if (this->isVisible())
    {
        return;
    }

    this->setVisible(true);
}


void ModalMessageOverlayWidget::hideModal()
{
    if (!this->isVisible())
    {
        return;
    }

    this->setVisible(false);
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
