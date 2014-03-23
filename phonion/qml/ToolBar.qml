
import QtQuick 2.0
import "." // QTBUG-34418

Rectangle {

    width: parent.width; height: 40
    opacity: parent.opacity
    Button {
        id: homeButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "transparent"

        fontpixelsize: 28
        fontfamily: Style.fontawesome.family
        text: Style.fontawesome.icon.home
        onClicked: phonion.home()
    }
}
