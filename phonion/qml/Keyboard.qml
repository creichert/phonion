
import QtQuick 2.0

Grid {
    id: keyboard

    property string keys: "0123456789abcdefghijklmnopqrstuvwsyz"

    signal hideKeyboard()
    signal letterClicked(string letter)

    rows: 5
    columns: 8
    spacing: 1
    Repeater {
        model: keys.length
        Button {
            width: 25; height: 55
            text: keys.charAt( index )
            onClicked: { letterClicked(text) }
        }
    }
}
