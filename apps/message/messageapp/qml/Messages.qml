
import QtQuick 2.0

Rectangle  {

    anchors.fill: parent

    Loader {
        id: messageapploader
        anchors.fill: parent
        source: "qrc:/qml/MessageBuddyList.qml"
    }
}
