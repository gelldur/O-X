import QtQuick 2.0

Rectangle {
    id: field
    state: "_"

    Text {
        id: mark
        text: parent.state
        color: "#ece9ed"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 66
        font.bold: true
    }

    color: "#363943"
    border { width: 1; color: "#434753" }
    radius: 20

    states: [
        State {
            name: "_"
            PropertyChanges {
                target: mark
                text: " "
                opacity: 0
            }
        },
        State {
            name: "O"
            PropertyChanges {
                target: mark
                text: "O"
                opacity: 1
            }
        },
        State {
            name: "X"
            PropertyChanges {
                target: mark
                text: "X"
                opacity: 1
            }
        }
    ]
    transitions: Transition {
        NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                easing.type: Easing.InExpo
                duration: 250
            }
        ColorAnimation {
                property: "color"
                from: "#ece9ed"
                to: "#34c1a8"
                easing.type: Easing.InExpo
                duration: 250
            }
        }
}
