import QtQuick 2.0

Rectangle {
    id: button
    width: 100
    height: 20
    color: "#ADD8E6"
    radius: 2
    property alias text: buttontext
    signal clicked

    property bool selected

    Text {
        id: buttontext
        anchors.centerIn: parent
        text: "Test"
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onClicked: button.clicked()
    }

    Rectangle {
        id: underlineRect

        visible: button.selected
        height: 2
        width: button.width
        color: "black"
        anchors.bottom: parent.bottom
    }

    Behavior on selected {PropertyAnimation {properties: "selected"; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 0.5}}
}
