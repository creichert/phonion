
#include <QObject>
#include <QString>

#include "message.h"

Message::Message(const QString& buddy, const QString& text, bool fromme, QObject* parent)
  : QObject(parent)
  , _buddy(buddy)
  , _text(text)
  , _fromme(fromme)
{
}
