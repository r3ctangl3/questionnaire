import QtQuick 6.0
import QtQuick.Controls

Item {
    id: root

    property alias input: input_field
    property string descriptionText: ""
    property bool showPassword: false
    property bool eyeIconEnabled: true

    implicitHeight: {
        if (descriptionText.trim() === 0) {
            return input_field.implicitHeight
        } else {
            return input_field.implicitHeight + description.implicitHeight + input_field.anchors.topMargin;
        }
    }

    CCLLabel {
        id: description
        anchors{ left: parent.left; right: parent.right; top: parent.top; leftMargin: 6 }
        text: root.descriptionText
        textStyle: EnumUtils.FontSize.Small
        textColor: EnumUtils.FontColor.Hovered
    }

    TextField {
        id: input_field
        anchors{ top: description.bottom; left: parent.left; right: parent.right
                  topMargin: 6 }
        implicitHeight: 55
        echoMode: root.showPassword ? TextInput.Normal : TextInput.Password
        font.family: "Inter"
        color: "#144866"
        font.pixelSize: 18
        leftPadding: 12
        rightPadding: eye_icon.anchors.rightMargin + eye_icon.implicitWidth + 6

        Observer{
            observe: input_field.focus
            handlerFunction: function (){ input_field.focus = false }
        }

        background: Rectangle {
            implicitHeight: input.implicitHeight
            implicitWidth: input.implicitWidth
            color: "#DCEEFA"
            border.color: input_field.focus || input_field.hovered ? "#88BFDF" : "transparent"
            border.width: 1
            radius: 12
        }

        cursorDelegate: Rectangle{
            width: 2
            color: "#144866"

            Timer {
                interval: 700
                running: input_field.focus
                onRunningChanged: {
                    if( !running ){ parent.visible = false }
                    else{ parent.visible = true }
                }
                repeat: true
                onTriggered: parent.visible = !parent.visible
            }
        }

        CCLIcon{
            id: eye_icon
            anchors{ verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: 16 }
            implicitHeight: 24
            implicitWidth: 29
            enabled: root.eyeIconEnabled
            color: icon_handler.containsMouse ? "#9FD4F0" : "#83C1E7"
            iconSource: root.showPassword ? "qrc:/style/icons/eye_open.svg" : "qrc:/style/icons/eye_close.svg"

            MouseArea{
                id: icon_handler
                anchors.fill: parent
                hoverEnabled: true
                onClicked: root.showPassword = !root.showPassword
            }
        }
    }
}