//
// Created by elizaveta on 04.05.2025.
//

#include "WindowsManager.h"

namespace application
{
namespace windows
{
namespace
{
constexpr auto LOGIN_PATH = "qrc:/Authorization.qml";
}

WindowsManager::WindowsManager( QObject* parent ) :
    QObject( parent )
    , splash( new QQuickWindow, &QQuickWindow::deleteLater ) //IMPORTANT! Delete ALL QObjects using deleteLater()!
    , master( new QQuickWindow, &QQuickWindow::deleteLater )
{
}

void WindowsManager::setup( const QPointer< QQmlApplicationEngine >& engine )
{
    auto deletef = &QQuickWindow::deleteLater;
    //todo separate window initialization & component creating
    //splash->setFlags( Qt::SplashScreen | Qt::FramelessWindowHint ); //splash screen configurations
    splash->setHeight( 600 );
    splash->setWidth( 800 );

    QQmlComponent loginComponent( engine, QUrl( LOGIN_PATH ) );
    const auto& created = loginComponent.create();
    if( !created )
    {
        qDebug() << "QQmlComponent creation failed " << loginComponent.errors(); //todo make exception
    }

    const auto& loginItem = qobject_cast< QQuickItem* >( created );
    if( !loginItem )
    {
        qDebug() << "QQuickItem creation failed "; //todo exception
    }

    loginItem->setParentItem( splash->contentItem() );
    const auto& anchors = qvariant_cast< QObject* >( loginItem->property( "anchors" ) );
    if( !anchors ){ qDebug() << "Property 'anchors' not found"; }
    anchors->setProperty( "fill", QVariant::fromValue( loginItem->parentItem() ) );
}

void WindowsManager::showLoginWindow() noexcept //todo temporary method for differ creation and display
{
    splash->show();
}
} // windows
} // application
