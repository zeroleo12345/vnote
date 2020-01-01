#include "vapplication.h"

VApplication::VApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
}

void VApplication::setWindow(VMainWindow * window)
{
    this->window = window;
    connect(this, &QApplication::applicationStateChanged, this, &VApplication::onApplicationStateChanged);
}

void VApplication::onApplicationStateChanged(Qt::ApplicationState state)
{
#if defined(Q_OS_MACOS) || defined(Q_OS_MAC)
    if(state == Qt::ApplicationActive) {
        this->window->show();
        // Need to call raise() in macOS.
        this->window->raise();
    }
#endif
}

