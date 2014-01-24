
import QtQuick 2.0

Rectangle {

    width: parent.width; height: 20

    Text {
        text: "wifi"
    }

    Text {
        id: time
        property variant now: new Date()
        text: Qt.formatDateTime(now, "hh:mm:ss")
        anchors.horizontalCenter: parent.horizontalCenter
        Timer {
            interval: 1000
            running: true
            repeat: true
            onTriggered: time.now = new Date()
        }
    }

    Text {
        text: "batt"
        anchors.right:  parent.right
    }
}
