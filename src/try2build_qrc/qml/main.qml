import QtQuick
import custom 1.0

Item {
    anchors.fill: parent
    visible:true

    Custom{
        anchors.centerIn: parent
    }

    BlueRect{
        anchors{ left: parent.left; top: parent.top }
    }

}
