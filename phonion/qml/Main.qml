
import QtQuick 2.0
import "." // QTBUG-34418

Rectangle  {

    /* If height is needed, for development, then
     * use these values.
     *
     * Derive all other measurements from parent
     * measurement to get resolution independence.
     */
    width: 320; height: 480
    color: Style.window.background

    FontLoader {
        source: Style.fontawesome.source
    }

    /* Global Notification Handler. */
    NotificationArea {
        id: notifications
        anchors.top: parent.top
        Connections {
            target: notifier
            onMessageNotification: {
                if (!msg.fromme()) {
                    notifications.text = msg.buddy() + ": " + msg.text()
                    notifications.show()
                }
            }
        }
    }

    Image {
        anchors.fill: parent
        source: "qrc:/img/bg.jpg"
    }

    Home {
        width: parent.width
        anchors.top: statusbar.bottom
        anchors.bottom: toolbar.top
        objectName: "apparea"
    }

    StatusBar {
        id: statusbar
        anchors.top: parent.top
        color: "transparent"
    }

    ToolBar {
        id: toolbar
        anchors.bottom:  parent.bottom
        opacity: 0.5

        // Border line
        Rectangle {
            color: Style.border.color.normal
            anchors.top: parent.top
            width: parent.width; height: Style.border.width.normal
        }
    }
}
