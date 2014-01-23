
import QtQuick 2.0

Rectangle {

    width: parent.width; height: 20
    //anchors.horizontalCenter: parent.horizontalCenter

    Text {
        text: "wifi"
    }

    Text {
        text: "time"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        text: "batt"
        anchors.right:  parent.right
    }
}
