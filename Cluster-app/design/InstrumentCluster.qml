import QtQuick 2.15

Item {
    // Remove fixed dimensions, let it scale with parent
    property int actualSpeed: ViewModel.speed
    property int actualCapacity: ViewModel.capacity

    Image {
        id: backGround
        source: "qrc:/asset/BackGround.png"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }
    
    LeftCluster {
        id: leftCluster
        // Use anchors instead of absolute positioning
        anchors {
            left: parent.left
            // leftMargin: parent.width * 0.036  // 70/1920 ≈ 0.036
            top: parent.top
			bottom: parent.bottom
            // topMargin: parent.height * 0.19   // 205/1080 ≈ 0.19
        }
        // Scale the cluster size relative to parent
        width: parent.width * 0.42  // Approximate ratio
        height: parent.height * 0.69

        speed: actualSpeed
    }

    RightCluster {
        id: rightCluster
        // Use anchors for right positioning
        anchors {
            right: parent.right
            // rightMargin: parent.width * 0.046  // (1920-1027-800)/1920 ≈ 0.046
            top: parent.top
			bottom: parent.bottom
            // topMargin: parent.height * 0.19    // Same as left cluster
        }
        // Scale the cluster size relative to parent
        width: parent.width * 0.42
        height: parent.height * 0.69

        capacity: actualCapacity
    }
}
