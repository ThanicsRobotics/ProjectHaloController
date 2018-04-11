import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 480
    height: 320
    title: qsTr("Hello World")



    StackView {
        id: stack
        initialItem: "HomePage.qml"
    }

}
