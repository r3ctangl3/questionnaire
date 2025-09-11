import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 6.0

ColumnLayout{
    id: root
    implicitWidth: 400
    spacing: 20

    Label{
        Layout.alignment: Qt.AlignVCenter
        text: "Авторизация"
    }

    TextField{
        Layout.fillWidth: true
        placeholderText: "Введите пароль"
    }
}