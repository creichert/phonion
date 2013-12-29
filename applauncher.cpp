
#include <QProcess>

#include "applauncher.h"

void AppLauncher::launch(int index)
{
    switch (index) {
    case Message:
        launchMessage();
        qDebug() << "Message";
        break;
    case Call:
        launchCall();
        qDebug() << "Call";
        break;
    case Browse:
        launchBrowse();
        qDebug() << "Browse";
        break;
    default:
        qDebug() << "" << " " << index;
    }
}

void AppLauncher::launchMessage()
{
    QProcess* p = new QProcess;
    p->start("torchat");
}

void AppLauncher::launchCall()
{
    QProcess* p = new QProcess;
    p->start("mumble");
}

void AppLauncher::launchBrowse()
{
    // Implement.
}
