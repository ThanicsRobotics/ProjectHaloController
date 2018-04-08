import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: homePage
    width: 480
    height: 320
    Image {
        id: logo
        source: "images/logo.jpg"
        width: homePage.width/2
        height: homePage.height
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
    }
    Button {
        x: 289
        y: 125
        width: 151
        height: 53
        text: "Start Flight"
        font.pixelSize: 20
        onClicked: {
            stack.push("TakeOffPage.qml")
        }
    }
    Button {
        x: 289
        y: 201
        width: 151
        height: 53
        text: "Power Off"
        font.pixelSize: 20
        onClicked: Qt.quit()
    }
}
