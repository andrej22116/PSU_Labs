#include "baseoverlaydialog.h"
#include <QGraphicsBlurEffect>
#include <QEvent>
#include <QResizeEvent>


BaseOverlayDialog::BaseOverlayDialog(QWidget* parent, QWidget* blurTarget) : QWidget(parent)
{
    if (parent) {
        parent->installEventFilter(this);
        this->resize(parent->size());
    }

    this->blurTarget = blurTarget;
    this->hide();
}

void BaseOverlayDialog::showDialog()
{
    auto effect = new QGraphicsBlurEffect(blurTarget);
    effect->setBlurHints(QGraphicsBlurEffect::BlurHint::PerformanceHint);
    effect->setBlurRadius(24);
    blurTarget->setGraphicsEffect(effect);
    this->show();
}

void BaseOverlayDialog::hideDialog()
{
    this->hide();
    blurTarget->setGraphicsEffect(nullptr);
}

bool BaseOverlayDialog::eventFilter(QObject* obj, QEvent* ev)
{
    if (obj == parent()) {
        if (ev->type() == QEvent::Resize) {
           resize(dynamic_cast<QResizeEvent*>(ev)->size());
        }
    }
    return QWidget::eventFilter(obj, ev);
}
