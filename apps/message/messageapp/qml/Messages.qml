
import QtQuick 2.0

Rectangle  {

    Loader {
        id: messageapploader
        anchors.fill: parent
        source: "qrc:/qml/MessageBuddyList.qml"
    }
}
