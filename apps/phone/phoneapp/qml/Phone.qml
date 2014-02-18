
import QtQuick 2.0


Rectangle {

    BuddyList {
        onBuddyClicked: { console.log("Calling Buddy " + buddy)
                          toonion.text = buddy
                        }
    }

    Timer {
        id: timer
        interval: 15000
        repeat: true
        onTriggered: info.text = "Latency: " + voipclient.latency()
    }

    Text {
        // TODO: Property bind voipclient.latency here.
        id: info
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: toonion.top
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
                         timer.start()
                     } else {
                         console.log("Call to onion " + toonion.text +
                                     " failed. Incorrectly formatted.")
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
