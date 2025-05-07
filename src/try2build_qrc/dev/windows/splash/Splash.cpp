//
// Created by elizaveta on 06.05.2025.
//

#include "Splash.h"

#include <QQuickItem>

namespace application {
namespace windows {
namespace splash {

namespace {
//@formatter: off
    constexpr auto PATH = "qrc:/ui/Authorization.qml";
//@formatter: on
}

Splash::Splash( QWindow* parent )
    : QQuickWindow( parent )
{

}

void Splash::initialize( const QPointer<QQmlApplicationEngine>& engine )
{
    if( engine.isNull() )
    {
        qDebug() << "Splash initialize failed";
        return;
    }
    setFlags( Qt::SplashScreen | Qt::FramelessWindowHint ); //splash screen configurations
    setHeight( 600 );
    setWidth( 500 );
    setColor( "transparent" );

    QQmlComponent component( engine, QUrl( PATH ) );
    auto&& created = component.create();
    if( !created )
    {
        qDebug() << "QQmlComponent creation failed " << component.errors(); //todo make exception
    }

    const auto& embeddedItem = qobject_cast< QQuickItem* >( created );
    if( !embeddedItem )
    {
        qDebug() << "Convertation failed "; //todo exception
    }
    embeddedItem->setParentItem( contentItem() );

    const auto& anchors = qvariant_cast< QObject* >( embeddedItem->property( "anchors" ) );
    if( !anchors ){ qDebug() << "Property 'anchors' not found"; }
    anchors->setProperty( "fill", QVariant::fromValue( embeddedItem->parentItem() ) );
}

} // windows
} // view
} // application