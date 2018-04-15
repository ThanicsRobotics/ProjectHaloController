import QtQuick 2.9
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

Item {
    width: 480
    height: 320

    Rectangle {
        anchors.fill: parent
        color: "white"

        Button {
            id: landButton
            x: 23
            y: 52
            width: 154
            height: 66
            text: qsTr("Land")
            font.pixelSize: 20
            onClicked: {
                backend.land()
                stack.pop()
            }
        }

        ProgressBar {
            id: flightTimeBar
            x: 41
            y: 280
            width: 400
            height: 15
            value: 0.5
        }

        Switch {
            id: switch1
            x: 32
            y: 136
            width: 136
            height: 83
            text: qsTr("Gear")
            font.pixelSize: 20
            onClicked: backend.operateLandingGear(1)
        }

        StreamBar {
            x: 305
            y: 141
            rotation: 90
        }

        StreamBar {
            x: 352
            y: 141
            rotation: 270
        }
    }
}
