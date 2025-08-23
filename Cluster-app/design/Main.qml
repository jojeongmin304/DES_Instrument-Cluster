import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: win
    width: mainScreen.width
    height: mainScreen.height
    visible: true
    visibility: Window.FullScreen
    flags: Qt.FramelessWindowHint
    title: qsTr("Instrument Cluster")

    InstrumentCluster {
        id: instrumentCluster
        anchors.fill: parent
        anchors.margins: 0  // Add some padding if needed
    }
}
