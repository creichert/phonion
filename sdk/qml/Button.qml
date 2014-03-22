
import QtQuick 2.0

Rectangle  {
    id: container

    property string text: ""
    property int fontpixelsize: 16

    signal clicked

    width: buttonLabel.width; height: buttonLabel.height

    MouseArea  {
        id: mouseArea
        anchors.fill: parent
        onClicked: container.clicked();
    }

    Text  {
        id: buttonLabel
        anchors.centerIn: container
        text: container.text
        font.pixelSize: fontpixelsize
        renderType: Text.NativeRendering
    }
}
