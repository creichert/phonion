
import QtQuick 2.0
import "." // QTBUG-34418

Rectangle  {

    color: "transparent"
    Component  {

        id: delegate
        Rectangle  {

            width: grid.cellWidth; height: grid.cellHeight
            color: "transparent"
            Rectangle {
                id: iconrect

                width: parent.width / 1.5; height: parent.height / 1.5
                color: "transparent"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                radius: 6

                Image  {
                    id: appIcon
                    source: icon

                    width: parent.width - 5; height: parent.height - 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: { grid.currentIndex = index
                                 Phonion.launch(index)
                               }
                }
            }

            Text  {
                anchors { top: iconrect.bottom;
                          horizontalCenter: parent.horizontalCenter
                        }
                color: Style.font.color
                text: name
                renderType: Text.NativeRendering
            }
        }
    }

    GridView  {
        id: grid
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter

        cellWidth: width / 2; cellHeight: height / 3.5
        model: appmodel
        delegate: delegate
    }

    Text {
        id: onion
        color: Style.font.color
        font.pointSize: 12
        text: Phonion.onion()
        anchors.bottom: grid.bottom
        anchors.horizontalCenter: grid.horizontalCenter
        renderType: Text.NativeRendering
    }
}
