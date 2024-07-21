import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Text{
        id: txt
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Ваше отношение к миру"
    }

    ListView{
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        width: txt.width
        anchors.top: txt.bottom
        anchors.horizontalCenter: txt.horizontalCenter
        model: ["HelloWorld", "GoodbyeWorld", "I don't like world"]

        delegate: Item{
            height: chBox.height
            CheckBox{
                id: chBox
                anchors.left: parent.left
                width: 32
                height: 32
            }

            Text{
                anchors.left: chBox.right
                anchors.leftMargin: 10
                anchors.verticalCenter: chBox.verticalCenter
                text: modelData
            }
        }
    }
}

