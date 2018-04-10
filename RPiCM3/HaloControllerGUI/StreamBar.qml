import QtQuick 2.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

ProgressBar {
    id: control
    width: 100
    value: 1
    contentItem: Item {
        implicitWidth: 100
        implicitHeight: 5
        Rectangle {
            id: bar
            width: control.visualPosition * parent.width
            height: parent.height
            radius: 5
        }

        LinearGradient {
            anchors.fill: bar
            start: Qt.point(0,0)
            end: Qt.point(bar.width, 0)
            source: bar
            gradient: Gradient {
                GradientStop {position: 0.0; color: "#17a81a"}
                GradientStop {id: grad; position: 0.5; color: Qt.lighter("#17a81a",2)}
                GradientStop {position: 1.0; color: "#17a81a"}
            }
            PropertyAnimation {
                target: grad
                property: "position"
                from: 0.1
                to: 0.9
                duration: 1000
                running: true
                loops: Animation.Infinite
            }
        }
        LinearGradient {
            anchors.fill: bar
            start: Qt.point(0,0)
            end: Qt.point(0,bar.height)
            source: bar
            gradient: Gradient {
                GradientStop {position: 0.0; color: Qt.rgba(0,0,0,0)}
                GradientStop {position: 0.5; color: Qt.rgba(1,1,1,0.3)}
                GradientStop {position: 1.0; color: Qt.rgba(0,0,0,.05)}
            }

        }
    }

    PropertyAnimation {
        target: control
        property: "value"
        from: 0
        to: 1
        duration: 5000
        running: true
        loops: Animation.Infinite
    }
}
