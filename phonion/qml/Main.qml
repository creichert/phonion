
import QtQuick 2.0

Rectangle  {

    /* If height is needed, for development, then
     * use these values.
     *
     * Derive all other measurements from parent
     * measurement to get resolution independence.
     */
    width: 320; height: 480
    color: "white"

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

    Home {
        width: parent.width
        anchors.top: statusbar.bottom
        anchors.bottom: toolbar.top
        objectName: "apparea"
    }

    StatusBar {
        id: statusbar
        anchors.top: parent.top
    }

    ToolBar {
        id: toolbar
        anchors.bottom:  parent.bottom

        // Border line
        Rectangle {
            color: "black"
            anchors.top: parent.top
            width: parent.width; height: 1
        }
    }
}
