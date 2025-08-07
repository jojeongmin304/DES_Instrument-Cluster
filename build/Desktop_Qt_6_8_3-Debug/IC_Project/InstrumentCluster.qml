import QtQuick

Item {
    width: 1920
    height: 1080

    Image {
        id: backGround
        x: 0
        y: 0
        width: 1920
        height: 1080
        source: "assets/BackGround.png"
        sourceSize.height: 1080
        sourceSize.width: 1920
        fillMode: Image.PreserveAspectFit

        Image {
            id: leftCircle
            x: 225
            y: 337
            width: 490
            height: 485
            source: "assets/LeftCircle.png"
            fillMode: Image.PreserveAspectFit

            Image {
                id: leftOutCircle
                x: -155
                y: -133
                width: 800
                height: 750
                source: "assets/LeftOutCircle.png"
                fillMode: Image.PreserveAspectFit

                Text {
                    id: speedText
                    x: 320
                    y: 305
                    width: 160
                    height: 120
                    color: "#ffffff"
                    text: qsTr("72")
                    font.pixelSize: 100
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                }

                Text {
                    id: scaleText
                    x: 320
                    y: 419
                    width: 160
                    height: 80
                    color: "#eaeaeb"
                    text: qsTr("km/h")
                    font.pixelSize: 50
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.bold: false
                    styleColor: "#dedede"
                }
            }
        }

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
    }

}
