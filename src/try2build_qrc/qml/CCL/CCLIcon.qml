import QtQuick 6.0
import QtQuick.Controls 6.0
import Qt5Compat.GraphicalEffects

ColorOverlay {
    id: root
    property string iconSource: ""
    smooth: true
    antialiasing: true
    cached: true

    source: Image{
        source: root.iconSource
        smooth: true
        mipmap: true
        antialiasing: true
        cache: true
    }
}