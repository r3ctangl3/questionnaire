import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

/*
    пока все будет страшненько и кривенько. Ждем дезигнс от Лили
    Потом окно авторизации нужно убрать с main и как-то администрировать
    показ окон плюсов
*/


Window {
    id: root
    width: 1024
    height: 768
    visible: true
    title: qsTr("Авторизация")
    color: "#97bfd1"
    Rectangle{
        id: container
        anchors.centerIn: parent
        width: 384; height: 410
        color: "#3f8fb0"
        radius: 8

        Rectangle{
            id: logo
            anchors.left: parent.left; anchors.top: parent.top
            anchors.leftMargin: 16; anchors.topMargin: 16
            width: 100; height: 75
            color: "white"
            Text{ anchors.centerIn: parent; text: "типа лого" }
        }
        //USE REPEATER  FOR LABELES
        Label{
            //TODO CUSTOMIZE
            id: title
            anchors.top: logo.bottom; anchors.left: parent.left; anchors.right: parent.right
            anchors.leftMargin: 18; anchors.topMargin: 32
            horizontalAlignment: Text.AlignLeft
            color: "#dedede"
            font.bold: true
            font.pointSize: 20

            text: "Авторизация"
        }

        Label{
            id: description
            anchors{ left: parent.left; right: parent.right; top: title.bottom
                     leftMargin: 18; rightMargin: 16; topMargin: 24 }
            horizontalAlignment: Text.AlignLeft
            color: "#dedede"
            text: "Введите пароль"
            font.pointSize: 16
        }

        TextField{
            id: txtField
            anchors{ left: parent.left; right: parent.right; top: description.bottom
                     leftMargin: 16; rightMargin: 16; topMargin: 24 }
            height: 48
            focus: false

            FocusDisabler{
                 function disableFocus(){ parent.focus = false }
                 openCloseState: parent.focus
            }
        }

        Button{
            anchors{ top: txtField.bottom; left: parent.left
                     leftMargin: 16; topMargin: 24 }
            height: 64; width: 192
            text: "типа кнопка"
        }
    }
}
