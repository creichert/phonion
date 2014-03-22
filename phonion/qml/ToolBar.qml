
import QtQuick 2.0

Rectangle {

    width: parent.width; height: 40
    Button {
        id: homeButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        text: "Home"
        onClicked: phonion.home()
    }
}
