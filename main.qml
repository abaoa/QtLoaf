import QtQuick 2.15
import QtQuick.Window 2.15

import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 120
    height: 120
    id: root
    title: qsTr("")
    color : "#000"

    Repeater{
        model: 5
        id: repeater
        Rectangle {
            property real radius1: 60
            property real dx: root.width / 2 //圆心坐标
            property real dy: root.height / 2
            property real cx: radius1 * Math.sin(percent*6.283185307179) + dx //各个圆点的实时坐标
            property real cy: radius1 * Math.cos(percent*6.283185307179) + dy
            property real percent: 1
            id: dot
            width: 15
            height: 15
            radius: 100
            color: "white"
            opacity: 0
            x: cx
            y: cy
            SequentialAnimation on percent {
                PauseAnimation { duration: 200 * index }
                loops: Animation.Infinite
                running: true
                ParallelAnimation {
                    NumberAnimation { target: dot; property: "opacity";from: 0;to: 1; duration: 200}
                    NumberAnimation { duration: 200; from: 1+index*0.05; to: 0.75}
                }

                NumberAnimation { duration: 60; from: 0.75; to: 0.7}
                NumberAnimation { duration: 140; from: 0.7; to: 0.65}
                NumberAnimation { duration: 160; from: 0.65; to: 0.6}

                NumberAnimation { duration: 200; from: 0.6;  to: 0.55}
                NumberAnimation { duration: 200; from: 0.55;  to: 0.5}

                NumberAnimation { duration: 200; from: 0.5;  to: 0.45}
                NumberAnimation { duration: 100; from: 0.45;  to: 0.4}
                NumberAnimation { duration: 50; from: 0.4;  to: 0.35}
                NumberAnimation { duration: 30; from: 0.35;  to: 0.3}
                NumberAnimation { duration: 180; from: 0.3;  to: 0}
                NumberAnimation { duration: 200; from: 1;    to: 0.75}

                NumberAnimation { duration: 60; from: 0.75; to: 0.7}
                NumberAnimation { duration: 140; from: 0.7; to: 0.65}
                NumberAnimation { duration: 160; from: 0.65; to: 0.6}

                NumberAnimation { duration: 200; from: 0.6;  to: 0.55}
                NumberAnimation { duration: 200; from: 0.55;  to: 0.5}
                NumberAnimation { duration: 200; from: 0.5;  to: 0.45}
                NumberAnimation { duration: 100; from: 0.45;  to: 0.4}
                NumberAnimation { duration: 50; from: 0.4;  to: 0.35}
                NumberAnimation { duration: 30; from: 0.35;  to: 0.3}
                NumberAnimation { duration: 180; from: 0.3;  to: 0}
                NumberAnimation { target: dot; duration: 50; property: "opacity"; from: 1; to: 0}

                PauseAnimation { duration: (repeater.count - index - 1) * 200}
            }
        }
        }

}

