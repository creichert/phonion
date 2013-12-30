
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QProcess>
#include <QString>
#include <QStringRef>

#include "applauncher.h"

AppLauncher::AppLauncher()
  : _proc(new QProcess())
{
    // Use QFileInfo and also check against security key.
    //QFile f("/var/lib/tor/hidden_service/hostname");
    QFile f("test_hostname");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    _addr = f.read(16);
    qDebug() << "Identified onion: " << _addr;
}

QString AppLauncher::onion()
{
    return QString("%1 - %2 - %3 - %4").arg(_addr.mid(0,4))
                                 .arg(_addr.mid(4,4))
                                 .arg(_addr.mid(8,4))
                                 .arg(_addr.mid(12,4));
}

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
        break;
    }
}

void AppLauncher::launchMessage()
{
    _proc->kill();
    _proc->start("mumble");
}

void AppLauncher::launchCall()
{
    _proc->kill();
    _proc->start("mumble");
}

void AppLauncher::launchBrowse()
{
    _proc->kill();
    // Implement.
}
