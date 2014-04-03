
#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QQmlIncubator>
#include <QQmlIncubationController>
#include <QQuickItem>

class AppIncubator : public QQmlIncubator
{
public:
    AppIncubator(QQuickItem* apparea, IncubationMode mode = AsynchronousIfNested)
      : QQmlIncubator(mode)
      , _apparea(apparea) {
    }

    ~AppIncubator() {
        qDebug() << " DELETING APP INCUBATOR";
    }

    void statusChanged(Status status) {
        qDebug() << "Status: " << status;
        switch (status) {
        case Ready: {
            QQuickItem* app = qobject_cast<QQuickItem*>(object());
            if (app) { app->setParentItem(_apparea); app->setParent(_apparea); }
            QQmlProperty(app, "anchors.fill").write(QVariant::fromValue(_apparea));
            break;
          }
        case Null:
        case Loading:
        case Error:
        default:
            break;
        }
    }

private:
    // Using QPointer deletes the object, I think.
    QQuickItem* _apparea;
};

class PhonionIncubationController : public QObject, public QQmlIncubationController
{
public:
    PhonionIncubationController(QObject* parent = 0)
      : QObject(parent) {

        startTimer(16);
    }

protected:
    virtual void timerEvent(QTimerEvent *) {
        incubateFor(5);
    }
};
