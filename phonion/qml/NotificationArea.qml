
import QtQuick 2.0

Rectangle {
    id: notificationArea

    // actual notification text
    property alias text: notificationText.text

    // fade time for fade in and out
    property int fadetime: 100

    // colors and background of the notification area
    property alias textcolor: notificationText.color
    property alias backgroundcolor: notificationArea.color
    property alias backgroundimage: notificationImage.source

    // time the notification is shown in ms
    property alias visibilitytime: notificationTimer.interval

    // signal to show the notification
    signal show();

    onShow: {
        notificationInAnimation.start();
        notificationInOpacity.start()
        notificationArea.visible = true;
        notificationTimer.running = true;
    }

    anchors.left: parent.left
    anchors.leftMargin: 5
    anchors.right: parent.right
    anchors.rightMargin: 5

    height: 40

    color: "black"

    visible: false
    z: 100

    border.color: "transparent"
    radius: 10

    // background image
    Image {
        id: notificationImage
        source:  ""

        anchors.fill: parent
    }

    // notification text
    Text {
        id: notificationText
        text: ""
        elide: Text.ElideRight
        maximumLineCount: 1

        anchors {
            left: parent.left;
            leftMargin: 10;
            right: parent.right;
            rightMargin: 10;
            verticalCenter: parent.verticalCenter;
        }

        font.family: "Sans Serif"
        font.pixelSize: 12

        wrapMode: Text.WordWrap
        textFormat: Text.RichText

        color: "white"
    }

    // slide in animation
    PropertyAnimation {
        id: notificationInAnimation;
        target: notificationArea;
        property: "height";
        from: 0;
        to: 30;
        duration: notificationArea.fadetime
    }

    // fade in animation
    NumberAnimation {
        id: notificationInOpacity
        target: notificationArea
        properties: "opacity"
        from: 0
        to: 0.9
        duration: notificationArea.fadetime
    }

    // slide out animation
    PropertyAnimation {
        id: notificationOutAnimation;
        target: notificationArea;
        property: "height";
        from: 30;
        to: 0;
        duration: notificationArea.fadetime
    }

    // fade out animation
    NumberAnimation {
        id: notificationOutOpacity
        target: notificationArea
        properties: "opacity"
        from: 0.9
        to: 0
        duration: notificationArea.fadetime

        //onRunningChanged:{
        //    if (!numAni.running) {
        //        notificationArea.visible = false;
        //        console.log("numAni Animation completed");
        //    } else {
        //        console.log("numAni Animation started");
        //    }
        //}
    }

    // notification timer
    Timer {
        id: notificationTimer
        interval: 1000
        running: false
        repeat:  false

        onTriggered: {
            notificationOutAnimation.start();
            notificationOutOpacity.start();
        }
    }
}
