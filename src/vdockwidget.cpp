#include "vdockwidget.h"

VDockWidget::VDockWidget(const QString &title, QWidget *parent)
    : QDockWidget(title, parent)
{
}

void VDockWidget::keyPressEvent(QKeyEvent *p_event)
{
    switch (p_event->key()) {
        case Qt::Key_Escape:
            if(isFloating()) {
                setVisible(false);
            }
            return;
    }

    QWidget::keyPressEvent(p_event);
}

void VDockWidget::focusOutEvent(QFocusEvent *p_event)
{
    if(p_event->lostFocus()) {
        auto *parent = (QDockWidget*)parentWidget();
        if(parent->isFloating()) {
            parent->setVisible(false);
        }
    }
    QWidget::focusOutEvent(p_event);
}
