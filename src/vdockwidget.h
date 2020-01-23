#ifndef VDOCKWIDGET_H
#define VDOCKWIDGET_H

#include <QDockWidget>
#include <QDebug>
#include <QKeyEvent>

class QKeyEvent;

class VDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit VDockWidget(const QString &title, QWidget *parent = Q_NULLPTR);

protected:
    void keyPressEvent(QKeyEvent *p_event) Q_DECL_OVERRIDE;

    void focusOutEvent(QFocusEvent *p_event) Q_DECL_OVERRIDE;
};

#endif // VDOCKWIDGET_H
