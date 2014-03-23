
import QtQuick 2.0
import "." // QTBUG-34418

Rectangle {
    id: keyboard

    height: parent.height / 1.75

    property string numkeys: "234567"
    property string alphakeys: "qwertyuiopasdfghjklzxcvbnm"

    signal hideKeyboard()
    signal letterClicked(string letter)

    Grid {
        id: numgrid

        columns: 6
        rows: 1
        spacing: 1
        Repeater {
            model: numkeys.length
            Button {
                width: 52; height: 60
                radius: 4
                border.color: Style.border.color.normal
                border.width: Style.border.width.normal
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
                width: 31; height: 25
                radius: 4
                border.color: Style.border.color.normal
                border.width: Style.border.width.normal
                text: alphakeys.charAt( index )
                onClicked: { letterClicked(text) }
            }
        }
    }
}
