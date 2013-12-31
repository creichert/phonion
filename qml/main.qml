
import QtQuick 2.0

Rectangle  {
    width: 210; height: 400
    color: "white"

    // Used to switch between qml views. Should be
    // the only instance of Loader.
    Loader {
        id: loader
        anchors.top: homeButton.bottom
        anchors.bottom:  parent.bottom
        anchors.left:  parent.left
        anchors.right:  parent.right
        source: "qrc:/qml/home.qml"
    }

    Text {
        id: homeButton
        text: "Home"
        MouseArea {
            anchors.fill: parent
            onClicked: loader.source = "qrc:/qml/home.qml"
        }
    }
}

