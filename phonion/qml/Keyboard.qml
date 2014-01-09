import QtQuick 2.0

Rectangle {
    id: keyboard

    height: 175

    property string numkeys: "0123456789"
    property string alphakeys: " qwertyuiopasdfghjklzxcvbnm"

    signal hideKeyboard()
    signal letterClicked(string letter)

    Grid {
        id: numgrid

        columns: 10
        spacing: 1
        Repeater {
            model: numkeys.length
            Button {
                width: 15; height: 45
                text: numkeys.charAt( index )
                onClicked: { letterClicked(text) }
            }
        }
    }

    Grid {
        id: alphagrid

        anchors.top: numgrid.bottom

        columns: 10
        spacing: 1
        Repeater {
            model: alphakeys.length
            Button {
                width: 15; height: 45
                text: alphakeys.charAt( index )
                onClicked: { letterClicked(text) }
            }
        }
    }
}
