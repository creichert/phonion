
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

    NotificationArea {
        id: notifications
        anchors.top: parent.top
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
