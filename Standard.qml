import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


Item {
    id:standardRoot

    property string title: "Standard"
    property string recentView:""
    property string result: "0"

    //Display result
    Connections{
        target:standard
        ignoreUnknownSignals: true
        onSendRecent:{
            recentView=qsTr(String(recentStr))
        }
    }
    Connections{
        target:standard
        ignoreUnknownSignals: true
        onSendResult:{
            result=qsTr(String(botShowStr))
        }
    }
    Connections{
        target:standard
        ignoreUnknownSignals: true
        onLockDashboard:{

        }
    }

    //View
    Rectangle{
        id:showResult
        width: parent.width
        height: parent.height*0.25
        color: "#202020"
        anchors.left: parent.left
        Text{
            text:recentView
            color:"gray"
            font.pointSize: 20
            anchors.right:parent.right
            anchors.rightMargin: 20
            anchors.top:parent.top
            anchors.topMargin: 10
            elide: Text.ElideRight
        }
        Text{
            text:result
            color:"white"
            font.pointSize: result.length<11?45:30
            anchors.right:parent.right
            anchors.rightMargin: 10
            anchors.bottom:parent.bottom
            anchors.bottomMargin: 25
            //                horizontalAlignment: Text.AlignHCenter
            //                verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
    }
    Rectangle{
        id:dashboard
        width: parent.width
        height: parent.height-showResult.height
        anchors.bottom: parent.bottom
        anchors.left:parent.left
        color:"#202020"

        Rectangle{
            id: topDashboard
            width: parent.width
            height:35
            anchors.bottom: bottomDashboard.top
            anchors.left:parent.left
            color:"#202020"
            StandardTopBtnList{
                id:listTopBtn
            }
            GridView {
                id: gridTopButton

                anchors.fill: parent
                interactive:false
                property var columns: 5
                cellWidth: parent.width/columns
                cellHeight:parent.height
                model:listTopBtn
                delegate: Button {
                    id: topdashbtn
                    text: btnLabel
                    width: gridTopButton.cellWidth
                    height: gridTopButton.cellHeight
                    contentItem: Text {
                        text: topdashbtn.text
                        font.pointSize: 14
                        opacity: enabled ? 1.0 : 0.3
//                        color: topdashbtn.down ? "gray" : "white"
                        color: if(index==0||index==1) {
                                   if(!isMemory){
                                   "#323232"
                                   }
                                   else{
                                       topdashbtn.down ? "gray" : "white"
                                   }
                               }
                                   else{
                                   topdashbtn.down ? "gray" : "white"
                               }
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        id:btnBackground
                        anchors.fill:parent
                        opacity: enabled ? 1 : 0.3
//                        color: topdashbtn.hovered ? topdashbtn.down ? "#26282e" : prsColor : btnColor
                        color: if(index==0||index==1) {
                                   if(!isMemory){
                                   btnColor
                                   }
                                   else{
                                       color: topdashbtn.hovered ? topdashbtn.down ? "#26282e" : prsColor : btnColor
                                   }
                               }
                                   else{
                                   color: topdashbtn.hovered ? topdashbtn.down ? "#26282e" : prsColor : btnColor
                               }



                        border.color: "#202020"
                        border.width: 1.5
                        radius: 7
                    }

                    onClicked:{
                        switch (index){
                        case 0: // MC
                            standard.buttonMCClicked()
                            break;
                        case 1: // MR
                            standard.buttonMRClicked()
                            break;
                        case 2: // M+
                            standard.buttonMplClicked()
                            break;
                        case 3: // M-
                            standard.buttonMmnClicked()
                            break;
                        case 4: // MS
                            standard.buttonMSClicked()
                            break;
                        }
                    }
                }
            }
        }



        Rectangle{
            id: bottomDashboard
            property var dashBoardMargin: 4
            width: parent.width-dashBoardMargin*2
            height:parent.height-topDashboard.height
            anchors.margins: dashBoardMargin
            anchors.bottom: parent.bottom
            anchors.left:parent.left
            color:"#202020"

            StandardBtnList{
                id:listBtn
            }
            GridView {
                id: gridButton
                anchors.fill: parent
                interactive:false
                property var columns: 4
                property var rows:6
                cellWidth: parent.width/columns
                cellHeight:parent.height/rows
                model:listBtn
                delegate: Button {
                    id: button
                    text: btnLabel
                    width: gridButton.cellWidth
                    height: gridButton.cellHeight
                    contentItem: Text {
                        text: button.text
                        font.pointSize: 18
                        opacity: enabled ? 1.0 : 0.3
                        color: button.down ? "gray" : "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        id:botbtnBackground
                        anchors.fill:parent
                        opacity: enabled ? 1 : 0.3
                        color: button.hovered ? button.down ? "#26282e" : prsColor : btnColor
                        border.color: "#202020"
                        border.width: 1.5
                        radius: 7
                    }

                    onClicked:{
                        switch (index){
                        case 0: // %
                            standard.buttonPercentClicked()
                            break;
                        case 1: // CE
                            standard.buttonCEClicked()
                            break;
                        case 2: // C
                            standard.buttonCClicked()
                            break;
                        case 3: // DEL
                            standard.buttonDelClicked()
                            break;
                        case 4: // 1/x
                            standard.buttonFracClicked()
                            break;
                        case 5: // x^2
                            standard.buttonP2Clicked()
                            break;
                        case 6: // sqrt(x)
                            standard.buttonSqrtClicked()
                            break;
                        case 7: // /
                            standard.buttonDivClicked()
                            break;
                        case 8: // 7
                            standard.button7Clicked()
                            break;
                        case 9: // 8
                            standard.button8Clicked()
                            break;
                        case 10: // 9
                            standard.button9Clicked()
                            break;
                        case 11: // *
                            standard.buttonMulClicked()
                            break;
                        case 12: // 4
                            standard.button4Clicked()
                            break;
                        case 13: // 5
                            standard.button5Clicked()
                            break;
                        case 14: // 6
                            standard.button6Clicked()
                            break;
                        case 15: // -
                            standard.buttonMinusClicked()
                            break;
                        case 16: // 1
                            standard.button1Clicked()
                            break;
                        case 17: // 2
                            standard.button2Clicked()
                            break;
                        case 18: // 3
                            standard.button3Clicked()
                            break;
                        case 19: // +
                            standard.buttonPlusClicked()
                            break;
                        case 20: // +/-
                            standard.buttonNegateClicked()
                            break;
                        case 21: // 0
                            standard.button0Clicked()
                            break;
                        case 22: // .
                            standard.buttonDotClicked()
                            break;
                        case 23: // =
                            standard.buttonEqualClicked()
                            break;
                        }
                    }
                }
            }
        }
    }
    Item {
//        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            if (event.key === Qt.Key_A) {
                 console.log("pressed");
                gridButton.toggleButton(2)

//                event.accepted = true;
            }
        }
    }
}
