
import QtQuick 2.0


Rectangle {

    property int seconds: 0

    Button {
        text: "tvtcxcxssrxrbhkq.onion"
        onClicked: { console.log("Calling friend.")
                     toonion.text = text
                   }
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true
        onTriggered: seconds++
    }

    Text {
        id: elapsedtime
        text: seconds
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

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
                     if (toonion.text.length == 16) {
                         voipclient.call(toonion.text)
                         seconds = 0; timer.start()
                     } else {
                         console.log("Call to onion " + toonion.text + " failed. Incorrectly formatted.")
                     }
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
                     timer.stop()
                   }
    }

    DialPad {
        id: keyboard
        anchors.bottom: parent.bottom
        onLetterClicked: toonion.text += letter
    }
}
