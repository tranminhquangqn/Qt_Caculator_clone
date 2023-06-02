import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id:memoListview
    property string historyLogStr:"There's nothing saved in memory"
    property bool isMemory:false
    function clearMemory(){
        memoryLog.clear()
        isMemory=false
    }
    anchors.fill:parent
    color: "#202020"
    Connections{
        target:standard
        ignoreUnknownSignals: true
        onSendMemoLog:{
            memoryLog.append({MemoTopLog: String(MemoLog)})
            isMemory=true
        }
    }
    ListModel{
        id:memoryLog
    }
    ListView{
        id: memoryListView
        visible: isMemory
        anchors.fill: parent
        model:memoryLog

        delegate: Button {
            id:memorylogbtn
            width: parent.width
            height: 80
            Text{
                text:MemoTopLog
                font.pointSize: 18
                opacity: enabled ? 1.0 : 0.3
                color: "white"
                anchors.top: parent.top
                anchors.right:parent.right
                anchors.topMargin: 10
                anchors.rightMargin: 15
            }

            background: Rectangle {
                anchors.fill:parent
                opacity: enabled ? 1 : 0.3
                color: memorylogbtn.hovered ? memorylogbtn.down ? "#26282e" : "#3b3b3b" : "#202020"
                border.color: "#202020"
                border.width: 1.5
                radius: 7
            }
        }

    }
}
