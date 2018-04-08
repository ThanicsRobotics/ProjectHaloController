import QtQuick 2.9
import QtQuick.Controls 2.3

Item {
    width: 480
    height: 320

    Rectangle {
        anchors.fill: parent
        color: "white"

        Button {
            id: landButton
            x: 23
            y: 64
            width: 154
            height: 66
            text: qsTr("Land")
            font.pixelSize: 20
            onClicked: stack.pop()
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
        }

        ProgressBar {
            id: progressBar1
            x: 305
            y: 141
            width: 100
            value: 0.5
            rotation: 90
        }

        ProgressBar {
            id: progressBar2
            x: 352
            y: 141
            width: 100
            rotation: 270
            value: 0.5
        }
    }
}
