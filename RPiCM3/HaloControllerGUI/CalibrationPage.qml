import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    width: 480
    height: 320

    Rectangle {
        anchors.fill: parent
        color: "white"

        Label {
            text: "Move joysticks\nto center"
            horizontalAlignment: Text.AlignHCenter
            font.weight: Font.Normal
            font.pixelSize: 28
            anchors.centerIn: parent
        }

        Rectangle {
            id: joystick1
            y: 110
            width: 100
            height: width
            radius: width/2
            color: "white"
            border.color: "blue"
            border.width: 5
            anchors.left: parent.left
            anchors.leftMargin: 30

            Rectangle {
                id: joystick1_center
                width: 20
                height: width
                radius: width/2
                color: "black"
                anchors.centerIn: parent
            }

            PropertyAnimation {
                target: joystick1_center
                from: joystick1.x + 15
                to: joystick1.x + joystick1.width - 15
                duration: 1000
                running: true
                loops: Animation.Infinite
            }
        }

        Rectangle {
            id: joystick2
            y: 110
            width: 100
            height: width
            color: "white"
            radius: width/2
            border.color: "blue"
            border.width: 5
            anchors.right: parent.right
            anchors.rightMargin: 30

            Rectangle {
                id: joystick2_center
                width: 20
                height: width
                radius: width/2
                color: "black"
                anchors.centerIn: parent
            }
        }
    }
}
