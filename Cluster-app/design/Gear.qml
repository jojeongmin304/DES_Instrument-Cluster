import QtQuick 2.15

Item {
    id: gear

    width: gearBackground.width
    height: gearBackground.height

    property string gear: "D"

    //색 튜닝
    property color baseColor: "#e8e9ee" //평상시
    property color highlightColor: "#ffffff" //진한흰색
    property int holdMs: 250  //하이라이트 유지 시간
    property int fadeMs: 800  //연하게 서서히 돌아가는 시간

    Image {
        id: gearBackground
        width: 450
        height: 380
        anchors.centerIn: parent

        source: "qrc:/asset/Gear.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: gearText
        anchors.centerIn: parent
        color: baseColor
        text: gear  //기어 표시
        font.pixelSize: parent.height * 0.2
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: false
    }

    //기어 값이 바뀔 때 하이라이트
    onGearChanged: flash.restart()

    SequentialAnimation {
        id: flash
        running: false
        loops: 1
        //즉시 진한 흰색으로
        PropertyAction { target: gearText; property: "color"; value: highlightColor }
        //잠깐 유지
        PauseAnimation { duration: holdMs }
        // 서서히 연한 색으로 복귀
        ColorAnimation {
            target: gearText
            property: "color"
            to: baseColor
            duration: fadeMs
            easing.type: Easing.InOutQuad
        }
    }
}
