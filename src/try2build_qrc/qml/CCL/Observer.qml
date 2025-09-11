import QtQuick 6.0
import QtQuick.Controls

Popup{
    id: root

    property bool observe
    property var handlerFunction: function( ){}
    visible: true
    onObserveChanged:{
        if( root.observe ){ root.open() }
    }

    onAboutToHide: handlerFunction()

    closePolicy: Popup.CloseOnPressOutsideParent
    width: 0
    height: 0
    z: 99
    x: 0
    y: 0
}
