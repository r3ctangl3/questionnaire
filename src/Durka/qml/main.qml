import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Durka.custom 1.0

Window {
    id: root
    width: 1024
    height: 768
    visible: true
    title: qsTr("Авторизация")
    color: "#97bfd1"

    MyRectangle{
        anchors.centerIn: parent
    }

}
