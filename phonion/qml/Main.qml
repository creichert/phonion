
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

    // Used to switch between qml views. Should be
    // the only instance of Loader.
    Loader {
        id: loader
        anchors.top: homeButton.bottom
        anchors.bottom:  parent.bottom
        anchors.left:  parent.left
        anchors.right:  parent.right
        source: "qrc:/qml/Home.qml"
    }

    Button {
        id: homeButton
        text: "Home"
        onClicked: loader.source = "qrc:/qml/Home.qml"
    }
}
