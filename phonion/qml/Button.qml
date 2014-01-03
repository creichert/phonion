
import QtQuick 2.0

Rectangle  {
    id: container

    property string text: ""

    signal clicked

    width: buttonLabel.width
    height: buttonLabel.height

    MouseArea  {
        id: mouseArea
        anchors.fill: parent
        onClicked: container.clicked();
    }

    Text  {
        id: buttonLabel
        anchors.centerIn: container
        color: activePalette.buttonText
        text: container.text
    }
}
