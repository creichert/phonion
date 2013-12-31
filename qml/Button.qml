
import QtQuick 2.0

Rectangle {
    width: 30; height: 20
    signal clicked

    Text {
        anchors.fill: parent
        text: "Send"
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        onClicked: { clicked; console.log("clicked...") }
    }

    Component.onCompleted: {
        ma.clicked.connect(clicked)
    }
}
