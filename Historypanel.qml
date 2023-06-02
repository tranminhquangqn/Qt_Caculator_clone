import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3



Rectangle{
    width: 600
    height: parent.height
    color: "#202020"
    property bool isMemory: memoryLV.isMemory
    Rectangle{
        id:topPanelBar
        width: parent.width
        height: 65
        color: "#202020"
        z:1
        TabBar {
            id: bar
            width: parent.width*0.6
            height:parent.height
            background: Rectangle {
                color:"transparent"
            }
            TabButton {
                text: qsTr("History")
                id:historytab

                contentItem: Text {
                    text: historytab.text
                    font: historytab.font
                    opacity: enabled ? 1.0 : 0.3

                    color: historytab.hovered?historytab.down ? "#323232" : "gray":"white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    //                    elide: Text.ElideRight
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -8
                }

                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color:"transparent"
                }
            }
            TabButton {
                id:memorytab
                text: qsTr("Memory")
                contentItem: Text {
                    text: memorytab.text
                    font: memorytab.font
                    opacity: enabled ? 1.0 : 0.3
                    color: memorytab.hovered?memorytab.down ? "#323232" : "gray":"white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -8
                }

                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color:"transparent"

                }
            }
        }

        Rectangle {
            id : decorator;
            property real targetX: bar.currentItem.x + bar.currentItem.width/2-width/2
            anchors.bottom: bar.bottom;
            anchors.bottomMargin: 8
            width: 30
            height: 4;
            color: "#4cc2ff"
            radius:4
            NumberAnimation on x {
                duration: 200;
                to: decorator.targetX
                running: decorator.x != decorator.targetX
            }
        }
    }
    StackLayout {
        width: parent.width
        height: parent.height-bar.height
        currentIndex: bar.currentIndex
        anchors.top:topPanelBar.bottom
        Rectangle {
            color: "#202020"
            anchors.fill:parent
            Text {
                visible: !historyLV.isHistory
                text: "There's no history yet"
                anchors.left:parent.left
                anchors.leftMargin: 10
                anchors.top:parent.top
                anchors.topMargin: 10
                color:"white"
                font.pointSize: 12
            }
            HistoryListView{
                id:historyLV
                anchors.fill:parent
                visible:isHistory
            }
            Rectangle {
                color: "#202020"
                width: parent.width
                height: 65
                anchors.bottom: parent.bottom
                anchors.left :parent.left
                visible: historyLV.isHistory
                Button {
                    id: historyClsButton
                    height: parent.height
                    width: parent.height
                    anchors.right: parent.right
                    background: Rectangle{
                        radius: 15
                        color: "#202020"

                    }
                    Image {
                        source: "qrc:/trashIcon.jpg"
                        anchors.centerIn: parent

                    }
                    onClicked: {
                        historyLV.clearHistory()
                    }
                    Rectangle{
                        id:historyClsButtonOverlay
                        height: parent.height-15
                        width: parent.height-15
                        radius:10
                        anchors.centerIn:parent
                        opacity:historyClsButton.hovered?0.1:0
                    }
                }
            }
        }
        Rectangle {
            color: "#202020"
            anchors.fill:parent
            Text {
                visible: !memoryLV.isMemory
                text: "There's nothing saved in memory"
                anchors.left:parent.left
                anchors.leftMargin: 10
                anchors.top:parent.top
                anchors.topMargin: 10
                color:"white"
                font.pointSize: 12
            }
            MemoryListView{
                id:memoryLV
                anchors.fill:parent
                visible:isMemory
            }
            Rectangle {
                color: "#202020"
                width: parent.width
                height: 65
                anchors.bottom: parent.bottom
                anchors.left :parent.left
                visible: memoryLV.isMemory
                Button {
                    id: memoryClsButton
                    height: parent.height
                    width: parent.height
                    anchors.right: parent.right
                    background: Rectangle{
                        radius: 15
                        color: "#202020"

                    }
                    Image {
                        source: "qrc:/trashIcon.jpg"
                        anchors.centerIn: parent

                    }
                    onClicked: {
                        memoryLV.clearMemory()
                    }
                    Rectangle{
                        id:memoryClsButtonOverlay
                        height: parent.height-15
                        width: parent.height-15
                        radius:10
                        anchors.centerIn:parent
                        opacity:memoryClsButton.hovered?0.1:0
                    }
                }
            }
        }
    }
}
