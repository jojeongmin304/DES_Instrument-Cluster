import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text {
        id: text1
        x: 114
        y: 117
        width: 128
        height: 135
        font.pixelSize: 12
    }
}
