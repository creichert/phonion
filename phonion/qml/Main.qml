
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

                /* TODO: Implement a system to test which 'qmlfile:buddy'
                 * combo is open. We can propogate value up from the signal
                 * with a Notification object and if both conditions are met
                 * we do not need to push a notification; presumably, because
                 * user is using that app with that buddy.
                 */
                notifications.text = msg
                notifications.show()
            }
        }
    }

    // Used to switch between qml views. Should be
    // the only instance of Loader.
    Loader {
        id: loader
        width: parent.width
        anchors.top: statusbar.bottom
        anchors.bottom: toolbar.top
        source: "qrc:/qml/Home.qml"
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
