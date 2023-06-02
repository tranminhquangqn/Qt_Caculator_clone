import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    id:root
    visible: true
    width: 450
    height: 650
    property var cacheWidth: width
    property var cacheHeight: height
    title: qsTr("Calculator")
    color: "#202020"
//    flags: Qt.FramelessWindowHint
    property bool isFrameless: false
    property bool isMemory: rightpanel.isMemory
    flags: isFrameless ? Qt.FramelessWindowHint : 0

    Historypanel{
        id: rightpanel
        width: 350
        height:parent.height
        anchors.right: parent.right
        anchors.top:parent.top
        visible: root.width>=700?true:false
    }
    Rectangle{
        id:mainview
        width: rightpanel.visible?parent.width-rightpanel.width:parent.width
        height: parent.height
        anchors.left:parent.left
        anchors.bottom: parent.bottom

        Rectangle {
            id:header
            height: 65
            width: parent.width
            anchors.top:parent.top
            anchors.left:parent.left
            color: "#202020"


            Button {
                id: toolButton
                height: parent.height
                width: parent.height
                z:100
                background: Rectangle{
                    radius: 15
                    color: "#202020"
                }
                contentItem: Text {
                    text: "\u2630"
                    color:"white"

                    font.pixelSize: Qt.application.font.pixelSize * 1.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onClicked: {
                    if(drawer.position===0)
                        drawer.open()
                    else
                        drawer.close()
                    console.log(stackView.depth)
                }
                Rectangle{
                    id:toolButtonOverlay
                    height: parent.height-15
                    width: parent.height-15
                    radius:10
                    anchors.centerIn:parent
                    opacity:toolButton.hovered?0.1:0
                }
            }
            Label {
                id: mainfunc
                text: stackView.currentItem.title
                color:"white"
                anchors.left: toolButton.right
                anchors.leftMargin: 10
                anchors.verticalCenter:parent.verticalCenter
                font.pixelSize: Qt.application.font.pixelSize * 1.8
            }
            Button {
                id: keepButton
                height: parent.height
                width: parent.height
                anchors.left: mainfunc.right
                background: Rectangle{
                    radius: 15
                    color: "#202020"
                }
                Image {
                    source: isFrameless?"qrc:/keepReverseIcon.jpg":"qrc:/keepIcon.jpg"
                    anchors.centerIn: parent
                }

                onClicked: {
                    if(!isFrameless){
                        cacheHeight=root.height
                        cacheWidth=root.width
                    root.width=350
                    root.height=550
                    }
                    else{
                        root.width=cacheWidth
                        root.height=cacheHeight
                    }

                    isFrameless = !isFrameless

                }
                Rectangle{
                    id:keepButtonOverlay
                    height: parent.height-20
                    width: parent.height-20
                    radius:10
                    anchors.centerIn:parent
                    opacity:keepButton.hovered?0.1:0
                }
            }
            Button {
                id: historyButton
                visible: !rightpanel.visible
                height: parent.height
                width: parent.height
                anchors.right: parent.right
                background: Rectangle{
                    radius: 15
                    color: "#202020"
                    visible: !rightpanel.visible

                }
                Image {
                    source: "qrc:/historyIcon.jpg"
                    anchors.centerIn: parent
                    visible: !rightpanel.visible

                }
                onClicked: {
                    if(historyDrawer.position===0)
                        historyDrawer.open()
                    else
                        historyDrawer.close()
                    console.log(stackView.depth)
                }
                Rectangle{
                    id:historyButtonOverlay
                    height: parent.height-15
                    width: parent.height-15
                    radius:10
                    anchors.centerIn:parent
                    opacity:historyButton.hovered?0.1:0
                }
            }

        }

        Rectangle{
            id: page
            width:parent.width
            height:parent.height-header.height
            anchors.bottom: parent.bottom
            anchors.left:parent.left
            Drawer {
                id: drawer
                width: mainview.width * 0.6
                height: parent.height
                background: Rectangle {
                    color: "#2c2c2c"
                    radius: 15
                }
                Rectangle{
                    id:topDrawer
                    width: parent.width
                    height: 65
                    anchors.top:parent.top
                    anchors.left:parent.left
                    color: "transparent"
                    Button {
                        id: toolButtonOnDrawer
                        height: parent.height
                        width: parent.height
                        z:100
                        background: Rectangle{
                            radius: 15
                            color: "#2c2c2c"
                        }
                        contentItem: Text {
                            text: "\u2630"
                            color:"white"

                            font.pixelSize: Qt.application.font.pixelSize * 1.5
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        onClicked: {
                            if(drawer.position===0)
                                drawer.open()
                            else
                                drawer.close()
                            console.log(stackView.depth)
                        }
                        Rectangle{
                            id:toolButtonOnDrawerOverlay
                            height: parent.height-15
                            width: parent.height-15
                            radius:10
                            anchors.centerIn:parent
                            opacity:toolButtonOnDrawer.hovered?0.1:0
                        }
                    }

                }
                Rectangle{
                    id:botDrawer
                    width: parent.width
                    height: 65
                    anchors.bottom:parent.bottom
                    anchors.left:parent.left
                    color: "transparent"
                Button{
                    id:settingBtn
                    width: parent.width
                    height:65
                    background: Rectangle{
                        radius: 15
                        color: "#2c2c2c"
                    }
                    Image {

                        source: "qrc:/SettingIcon.jpg"
                        anchors.left:parent.left
                        anchors.leftMargin: 17
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text{
                        text:"Setting"
                        color:"white"
                        anchors.left:parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Rectangle{
                        id:settingBtnOverlay
                        height: parent.height-10
                        width:  parent.width-10
                        radius:10
                        anchors.centerIn:parent
                        opacity:settingBtn.hovered?0.1:0
                    }
                }

                }
                Rectangle{
                    id: calculatortext
                    width: parent.width
                    height: 30
                    anchors.top:topDrawer.bottom
                    color:"#2c2c2c"
                    Text {
                        text: "Calculator"
                        anchors.left:parent.left
                        anchors.leftMargin: 20
                        anchors.bottom:parent.bottom
                        anchors.bottomMargin: 10
                        color:"white"
                        font.pointSize: 12
                    }
                }
                Button{
                    id:drawerStandardBtn
                    height: 40
                    width: parent.width
                    anchors.top:calculatortext.bottom
                    text: "Standard"
                    onClicked: {
                        stackView.push("qrc:/Standard.qml")
                        drawer.close()
                    }
                }

            }
            StackView {
                id: stackView
                anchors.fill:parent
                focus: true
                initialItem: "qrc:/Standard.qml"

            }
            Drawer {
                id: historyDrawer
                width: parent.width
                height: parent.height*0.7
                edge :Qt.BottomEdge
                background: Rectangle {
                    color: "#202020"
                    radius: 15
                }
                Text {
                    visible: !historyDrawerLV.isHistory
                    text: "There's no history yet"
                    anchors.left:parent.left
                    anchors.leftMargin: 20
                    anchors.top:parent.top
                    anchors.topMargin: 20
                    color:"white"
                    font.pointSize: 12
                }
                HistoryListView{
                    id:historyDrawerLV
                    anchors.fill:parent
                    visible:isHistory
                }
                Rectangle{
                    color: "#202020"
                    width: parent.width
                    height: 65
                    anchors.bottom: parent.bottom
                    anchors.left :parent.left
                    visible: historyDrawerLV.isHistory
                    Button {
                        id: historDraweryClsButton
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
                            historyDrawerLV.clearHistory()
                        }
                        Rectangle{
                            id:historDraweryClsButtonOverlay
                            height: parent.height-15
                            width: parent.height-15
                            radius:10
                            anchors.centerIn:parent
                            opacity:historDraweryClsButton.hovered?0.1:0
                        }
                    }

                }

                ////////////////////////////////////////////////////////////////

            }

        }
    }


}
