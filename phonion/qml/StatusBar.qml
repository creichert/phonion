
import QtQuick 2.0
import "." // QTBUG-34418

Rectangle {

    width: parent.width; height: 20

    Text {
        color: Style.font.color
        font.family: Style.fontawesome.family
        text: Style.fontawesome.icon.signal
        renderType: Text.NativeRendering
    }

    Text {
        id: time
        property variant now: new Date()
        text: Qt.formatDateTime(now, "hh:mm")
        color: Style.font.color
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
        color: Style.font.color
        font.family: Style.fontawesome.family
        text: "100%"
        anchors.right:  parent.right
        renderType: Text.NativeRendering
    }
}
