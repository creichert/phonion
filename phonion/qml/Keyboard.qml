import QtQuick 2.0

Rectangle {
    id: keyboard

    height: 105

    property string numkeys: "0123456789"
    property string alphakeys: "qwertyuiopasdfghjklzxcvbnm"

    signal hideKeyboard()
    signal letterClicked(string letter)

    Grid {
        id: numgrid

        columns: 10
        spacing: 1
        Repeater {
            model: numkeys.length
            Button {
                width: 20; height: 25
                border.color: "black"
                border.width: 1
                radius: 4
                text: numkeys.charAt( index )
                onClicked: { letterClicked(text) }
            }
        }
    }

    Grid {
        id: alphagrid

        anchors.top: numgrid.bottom
        anchors.topMargin: 1

        columns: 10
        spacing: 1
        Repeater {
            model: alphakeys.length
            Button {
                width: 20; height: 25
                border.color: "black"
                border.width: 1
                radius: 4
                text: alphakeys.charAt( index )
                onClicked: { letterClicked(text) }
            }
        }
    }
}
