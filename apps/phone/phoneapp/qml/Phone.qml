
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
        onTriggered: { console.log(voipclient.connected())
                       if (voipclient.connected()) {
                           info.text = "Latency: " + voipclient.latency()
                       }
                     }
    }

    Text {
        // TODO: Property bind voipclient.latency here.
        id: info
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: toonion.top
        renderType: Text.NativeRendering
    }

    TextInput {
        id: toonion
        // test service.
        text: "rtasbxxhle55nnin"
        maximumLength: 16
        anchors.bottom: callbutton.top
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: TextInput.AlignHCenter
        font.pointSize: 10
        renderType: Text.NativeRendering
    }

    Button {
        id: callbutton
        text: "Call"

        anchors.right: parent.right
        anchors.bottom: keyboard.top

        onClicked: { console.log("Call: " + toonion.text)
                     if (toonion.text.length == 16) {
                         timer.start()
                         voipclient.call(toonion.text)
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
                     voipclient.end()
                     timer.stop()
                     info.text = ""
                   }
    }

    DialPad {
        id: keyboard
        anchors.bottom: parent.bottom
        onLetterClicked: toonion.text += letter
    }
}
