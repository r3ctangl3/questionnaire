import QtQuick 6.0
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import CCL 1.0

Rectangle{
    id: root
    readonly property bool accountExists: backend ? backend.authorization.accountExists : false
    color: "#88BFDF"
    layer.enabled: true
    layer.effect: OpacityMask{
        anchors.fill: parent
        maskSource: Rectangle{
            radius: 15
            implicitHeight: root.height
            implicitWidth: root.width
        }
    }

    CCLIcon{
        id: logo
        anchors{ top: parent.top; horizontalCenter: parent.horizontalCenter; topMargin: 27 }
        iconSource: "qrc:/style/icons/Logo.svg"
        color: "white"
        implicitHeight: 120
        implicitWidth: 125
    }

    Rectangle{
        anchors{ bottom: parent.bottom; left: parent.left; right: parent.right
                 leftMargin: 7; rightMargin: 7; bottomMargin: 7 }
        color: "#FFFFFF"
        radius: 15
        implicitWidth: 535
        implicitHeight: 418

        CCLLabel{
            id: header
            anchors{ top: parent.top; left: parent.left; right: parent.right; topMargin: 14 }
            textStyle: EnumUtils.FontSize.Regular
            text:"Это ваш первый вход\nПридумайте надежный пароль"
            horizontalAlignment: Text.AlignHCenter
        }

        CCLPasswordField{
            id: ldld
            anchors{ left: parent.left; right: parent.right; top: header.bottom
                leftMargin: 29; rightMargin: anchors.leftMargin; topMargin: 32 }
            descriptionText: "Пароль"
        }

        CCLPasswordField{
            anchors{ left: parent.left; right: parent.right; top: ldld.bottom
                leftMargin: 29; rightMargin: anchors.leftMargin; topMargin: 32 }
            descriptionText: "Подтверждение пароля"
        }

        /*TextFiewhiteld{
            id: input
            anchors{ left: parent.left; right: parent.right; top: header.bottom
                     leftMargin: 29; rightMargin: anchors.leftMargin; topMargin: 62 }
            implicitHeight: 55
            echoMode: TextInput.Password
            background: Rectangle{
                implicitHeight: input.implicitHeight
                implicitWidth: input.implicitWidth
                color: "#DCEEFA"
                radius: 12
            }
            font.family: "Inter"
            font.pixelSize: 16
            leftPadding: 10
        }*/
    }

    Button
    {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        implicitHeight: 50
        implicitWidth: 200
        text: "Временный выход"
        onClicked: Qt.quit()
    }

    /*Loader{
        anchors.centerIn: parent

        source: accountExists ? "qrc:/ui/Login.qml" : "qrc:/ui/SingUp.qml"
    }*/

}
