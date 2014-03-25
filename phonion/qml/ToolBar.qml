
import QtQuick 2.0
import "." // QTBUG-34418

Rectangle {

    width: parent.width; height: Style.toolbar.height

    Image {
        id: homeButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/img/home.jpg"
        width: 40; height: 40
        MouseArea {
            opacity: 1.0
            anchors.fill: parent
            onClicked: {
                         { //TODO: Hacks. add function to "swap style"
                           Style.font.color = "white"
                           statusbar.color = "transparent"
                           Phonion.home()
                         }
                       }
        }
    }
}
