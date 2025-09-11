import QtQuick 6.0
import QtQuick.Controls 6.0

Label{
    id: root

    property int textStyle: EnumUtils.FontSize.Regular
    property int textColor: EnumUtils.FontColor.Normal

    horizontalAlignment: Text.AlignLeft
    elide: Text.ElideRight
    text: ""
    font.family: "Inter"
    font.pixelSize: {
        switch ( textStyle )
        {
            case( EnumUtils.FontSize.Small ): { return 20; }
            case( EnumUtils.FontSize.Regular ): { return 24; }
            case( EnumUtils.FontSize.Large ): { return 28; }
        }
    }
    color: {
        switch ( textColor )
        {
            case( EnumUtils.FontColor.Normal ): { return "#144866"; }
            case( EnumUtils.FontColor.Hovered ): { return "#718096" ; }
        }
    }
}