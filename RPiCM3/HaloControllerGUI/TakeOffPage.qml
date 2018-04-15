import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0

Item {
    width: 480
    height: 320
    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: "white"

        Button {
            id: backButton
            x: 0
            y: 0
            text: qsTr("Back")
            font.pixelSize: 20
            onClicked: stack.pop()
        }

        Image {
            id: arrow
            x: 70
            y: 48
            width: 114
            height: 94
            source: "images/arrow.png"
        }

        Button {
            x: 252
            y: 39
            width: 182
            height: 74
            text: "Takeoff"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 53
            Layout.preferredWidth: 151
            font.pixelSize: 30
            onClicked: {
                backend.takeoff()
                stack.push("FlightPage.qml")
            }
        }

        Slider {
            id: slider
            live: true
            x: 243
            y: 158
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            value: 0.5
            onValueChanged: {
                text2.update()
            }
        }

        RowLayout {
            x: 220
            y: 216
            width: 246
            height: 51


            Text {
                id: text1
                text: qsTr("Hover Height:")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 30
            }

            Text {
                id: text2
                text: (slider.value*2).toFixed(1) + "m"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 30
            }
        }
    }


}
