import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id:histListview
    property string historyLogStr:"There's no history yet"
    property bool isHistory:false
    function clearHistory(){
        historyLog.clear()
        isHistory=false
    }
    anchors.fill:parent
    color: "#202020"
    Connections{
        target:standard
        ignoreUnknownSignals: true
        onSendHistLog:{
            historyLog.append({HistTopLog: String(HistTopLog),HistBotLog: String(HistBotLog)})
            isHistory=true
        }
    }
    ListModel{
        id:historyLog
    }
    ListView{
        id:historyListView
        visible: isHistory
        anchors.fill: parent
        model:historyLog

        delegate: Button {
            id:histlogbtn
            width: parent.width
            height: 80
            Text{
                text:HistTopLog
                font.pointSize: 14
                opacity: enabled ? 1.0 : 0.3
                color: "gray"
                anchors.top: parent.top
                anchors.right:parent.right
                anchors.topMargin: 10
                anchors.rightMargin: 15
            }
            Text{
                text:HistBotLog
                font.pointSize: 18
                opacity: enabled ? 1.0 : 0.3
                color: histlogbtn.down ? "gray" : "white"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.rightMargin: 15
                anchors.right:parent.right
            }

            background: Rectangle {
                id:btnBackground
                anchors.fill:parent
                opacity: enabled ? 1 : 0.3
                color: histlogbtn.hovered ? histlogbtn.down ? "#26282e" : "#3b3b3b" : "#202020"
                border.color: "#202020"
                border.width: 1.5
                radius: 7
            }
        }

    }
}
