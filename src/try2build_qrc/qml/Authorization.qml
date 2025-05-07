import QtQuick 6.0
import QtQuick.Controls 6.0
import Qt5Compat.GraphicalEffects

Rectangle{
    id: root
    readonly property bool accountExists: backend ? backend.authorization.accountExists : false

    layer.enabled: true
    layer.effect: OpacityMask{
        anchors.fill: parent
        maskSource: Rectangle{
            radius: 40
            implicitHeight: root.height
            implicitWidth: root.width
        }
    }
    Rectangle{
        anchors{ left: parent.left; right: parent.right; top: parent.top }
        color: "#50a6d9"
        implicitHeight: 170
        Image
        {
            anchors.centerIn: parent
            height: 150
            width: 150
            source: "qrc:/style/icons/Logo.svg"
            smooth: true
            mipmap: true
            antialiasing: true
            ColorOverlay{
                anchors.fill: parent
                color: "white"
                source: parent
                antialiasing: true
                cached: true
                smooth: true
            }
        }
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

    Loader{
        anchors.centerIn: parent

        source: accountExists ? "qrc:/ui/Login.qml" : "qrc:/ui/SingUp.qml"
    }

}
