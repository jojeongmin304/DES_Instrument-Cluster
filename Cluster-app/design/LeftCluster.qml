import QtQuick 2.15

Item {
    id: leftcluster
    visible: true

    property real speed: 0

    //화면에 부드럽게 표시될 값
    property real displayedSpeed: 0

    // 숫자 변화를 부드럽게 만들어주는 애니메이션 객체
    NumberAnimation on displayedSpeed {
        id: smoothAnimation
        duration: 1000 // 1초 동안 부드럽게 변화
        easing.type: Easing.InOutQuad // 시작과 끝을 부드럽게 처리
    }

    // speed 속성(실제 값)이 변경될 때마다 자동으로 호출됨
    onSpeedChanged: {
        smoothAnimation.from = displayedSpeed // 현재 표시되는 값에서 시작
        smoothAnimation.to = speed           // 새로운 목표 값으로 이동
        smoothAnimation.start()              // 애니메이션 시작!
    }

    // Outer shadow circle
    Image {
        id: leftOutCircle
        anchors.fill: parent
        source: "qrc:/asset/LeftOutCircle.png"
        fillMode: Image.PreserveAspectFit
    }

    // Central blue circle
    Image {
        id: leftCircle
        // Make it proportional to the outer circle
        width: parent.width * 0.61   // 490/800 ≈ 0.61
        height: parent.height * 0.65 // 485/750 ≈ 0.65
        anchors.centerIn: parent
        source: "qrc:/asset/LeftCircle.png"
        fillMode: Image.PreserveAspectFit
    }

    // Speed value text
    Text {
        anchors.centerIn: parent
        color: "#ffffff"
        font.pixelSize: parent.height * 0.1  // Relative font size
        text: Math.floor(displayedSpeed)
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
    }
    
    // Unit text (cm/s)
    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.verticalCenter
            topMargin: parent.height * 0.11  // Relative positioning below center
        }
        color: "#d7d8d9"
        text: qsTr("cm/s")
        font.pixelSize: parent.height * 0.053  // Relative font size
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}


// import QtQuick 2.15


// //이 컴포넌트는 독립적으로 존재, 절대좌표를 사용하지 않는다.
// Item {
//     id: leftcluster
//     width: leftOutCircle.width
//     height: leftOutCircle.height
//     visible: true

//     property real speed: 0

//     // 바깥 음영 원
//     Image {
//         id: leftOutCircle
//         //x: 0
//         //y: 0
//         width: 800
//         height: 750
//         anchors.fill: parent
//         source: "qrc:/asset/LeftOutCircle.png"
//         fillMode: Image.PreserveAspectFit

//     // 게이지나 바늘 이미지 추가할 예정
//     }

//     //  중앙 파란 원
//     Image {
//         id: leftCircle
//         //x: 155
//         //y: 133
//         width: 490
//         height: 485
//         //anchors.fill: parent
//         anchors.centerIn: leftOutCircle  //바깥 원 중앙에 배치
//         source: "qrc:/asset/LeftCircle.png"
//         fillMode: Image.PreserveAspectFit
//     }

//     // -----텍스트 요소들------
//     //실제 속도 값 표시 텍스트
//     Text {
//         //x: 310
//         //y: 315
//         //width: 180
//         //height: 120
//         anchors.centerIn: parent
//         color: "#ffffff"
//         //text: qsTr("72")
//         font.pixelSize: 75
//         text: Math.round(speed)  //반올림 해서 바인딩
//         horizontalAlignment: Text.AlignHCenter
//         verticalAlignment: Text.AlignVCenter
//         font.bold: true
//     }
//     //단위(km/h) 표시 텍스트
//     Text {
//         x: 353
//         y: 398
//         width: 100
//         height: 60
//         color: "#d7d8d9"
//         text: qsTr("cm/s")
//         font.pixelSize: 40
//         horizontalAlignment: Text.AlignHCenter
//         verticalAlignment: Text.AlignVCenter
//     }

// }
