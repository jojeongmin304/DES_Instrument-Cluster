import QtQuick

Item {
    width: 1920
    height: 1080

    property real actualSpeed: 72

    Image {
        id: backGround
        //x: 0
        //y: 0
        //width: 1920
        //height: 1080
        anchors.fill: parent
        source: "assets/BackGround.png"
        sourceSize.height: 1080
        sourceSize.width: 1920
        fillMode: Image.PreserveAspectFit

        Image {
            id: rightCircle
            x: 1182
            y: 337
            width: 490
            height: 485
            source: "assets/RightCircle.png"
            fillMode: Image.PreserveAspectFit

            Image {
                id: rightOutCircle
                x: -155
                y: -133
                width: 800
                height: 750
                source: "assets/RightOutCircle.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        LeftCluster {
            id: leftCluster
            x: 70
            y: 205

            //leftCluster의 Speed 프로퍼티에 실제 속도 값을 전달
            speed: actualspeed
        }
    }

}
