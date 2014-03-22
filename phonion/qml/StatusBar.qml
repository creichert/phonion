
import QtQuick 2.0

Rectangle {

    width: parent.width; height: 20

    Text {
        text: "wifi"
        renderType: Text.NativeRendering
    }

    Text {
        id: time
        property variant now: new Date()
        text: Qt.formatDateTime(now, "hh:mm")
        anchors.horizontalCenter: parent.horizontalCenter
        renderType: Text.NativeRendering
        Timer {
            interval: 60000
            running: true
            repeat: true
            onTriggered: time.now = new Date()
        }
    }

    Text {
        text: "batt"
        anchors.right:  parent.right
        renderType: Text.NativeRendering
    }
}
