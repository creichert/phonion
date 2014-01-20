
#include "buddy.h"

Buddy::Buddy(const QString& onion, const QString& displayName, QObject* parent)
  : QObject(parent)
  , _onion(onion)
  , _displayName(displayName)
{
}
