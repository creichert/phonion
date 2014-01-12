
import QtQuick 2.0


Rectangle {

    TextInput {
        id: toonion
        maximumLength: 16
        anchors.bottom: callbutton.top
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: TextInput.AlignHCenter
        font.pointSize: 10
    }

    Button {
        id: callbutton
        text: "Call"

        anchors.right: parent.right
        anchors.bottom: keyboard.top

        onClicked: { console.log("Call: " + toonion.text)
                     voipclient.call(toonion.text)
                   }
    }

    Button {
        id: cancelbutton
        text: "Cancel"

        anchors.top: toonion.bottom
        anchors.bottom: keyboard.top

        onClicked: { console.log("Cancel")
                     toonion.text = ""
                     voipclient.end()
                   }
    }

    Keyboard {
        id: keyboard
        anchors.bottom: parent.bottom
        onLetterClicked: toonion.text += letter
    }
}
