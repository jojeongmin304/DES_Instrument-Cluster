import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: win
    width: 1024
    height: 600
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

// import QtQuick 2.15

// Window {
//     id: instrumentcluster
//     width: 1024
//     height: 600
//     visible: true
//     title: qsTr("Instrument Cluster")

//     InstrumentCluster {
//         id: instrumentCluster
//         //x: 0
//         //y: 0
//         anchors.centerIn: parent
//     }

// }
