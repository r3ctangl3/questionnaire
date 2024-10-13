import QtQuick 2.0
import QtQuick.Controls 2.15

Popup {
    id: root
    property bool openCloseState

    onOpenCloseStateChanged: openCloseState ? open() : close()
    onAboutToHide: disableFocus()

    width: 0; height: 0
    opacity: 0.0
    closePolicy: Popup.CloseOnPressOutsideParent
}
