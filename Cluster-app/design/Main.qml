import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: instrumentcluster
    width: 1024
    height: 600
    visible: true
    title: qsTr("Instrument Cluster")
    
    // Set window flags for frameless window
    ///flags: Qt.FramelessWindowHint

	// cursor÷Shape: Qt.BlankCursor
    
    // Set fullscreen mode
    ///visibility: Window.FullScreen

    InstrumentCluster {
        id: instrumentCluster
        anchors.fill: parent
        // anchors.margins: 10  // Add some padding if needed
    }
}
