
import QtQuick 2.0

pragma Singleton

/* Global QML Style Object */
QtObject {

    property QtObject border: QtObject{

        property QtObject color: QtObject{
            property color disabled: "red";
            property color focus: "blue";
            property color normal: "gray";
        }

        property QtObject width: QtObject{
            property int big: 3;
            property int normal: 1;
        }
    }

    property QtObject font: QtObject{

    }

    property QtObject window: QtObject{
        property color background: "white";
    }
 
}
