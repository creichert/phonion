
import QtQuick 2.0
import "." // QTBUG-34418

Rectangle  {
    id: container

    property string text: ""
    property int fontpixelsize: 16
    property string fontfamily: "Helvetica"
    property color fontcolor: Style.font.color

    signal clicked

    width: buttonLabel.width; height: buttonLabel.height

    MouseArea  {
        id: mouseArea
        anchors.fill: parent
        onClicked: container.clicked();
    }

    Text  {
        id: buttonLabel
        color: parent.fontcolor
        anchors.centerIn: container
        text: container.text
        font.pixelSize: fontpixelsize
        font.family: fontfamily
        renderType: Text.NativeRendering
    }
}
