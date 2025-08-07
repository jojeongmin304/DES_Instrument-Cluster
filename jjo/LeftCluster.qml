import QtQuick

Item {
    width: 800
    height: 750
    visible: true

    property real speed: 0

    Image {
        id: leftCircle
        x: 155
        y: 133
        width: 490
        height: 485
        //anchors.fill: parent
        anchors.centerIn: leftOutCircle  //바깥 원 중앙에 배치
        source: "assets/LeftCircle.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: leftOutCircle
        //x: 0
        //y: 0
        //width: 800
        //height: 750
        anchors.fill: parent
        source: "assets/LeftOutCircle.png"
        fillMode: Image.PreserveAspectFit

        Text {
            //x: 310
            //y: 315
            //width: 180
            //height: 120
            anchors.centerIn: parent
            color: "#ffffff"
            //text: qsTr("72")
            font.pixelSize: 75
            text: Math.round(speed)  //반올림 해서 바인딩
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true

            Text {
                id: text2
                x: -26
                y: 66
                width: 100
                height: 60
                color: "#d7d8d9"
                text: qsTr("km/h")
                font.pixelSize: 40
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

}
