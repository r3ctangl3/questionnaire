import QtQuick 6.0
import QtQuick.Controls 6.0

Item{
    id: root
    readonly property bool accountExists: backend ? backend.authorization.accountExists : false

    Loader{
        anchors.centerIn: parent

        source: accountExists ? "qrc:/Login.qml" : "qrc:/SingUp.qml"
    }

}
