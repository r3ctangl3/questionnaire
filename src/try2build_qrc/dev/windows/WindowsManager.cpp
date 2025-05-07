//
// Created by elizaveta on 04.05.2025.
//

#include "WindowsManager.h"

#include "splash/Splash.h"

namespace application
{
namespace windows
{
namespace
{
constexpr auto LOGIN_PATH = "qrc:/qml/Authorization.qml";
}

WindowsManager::WindowsManager( QPointer<QQmlApplicationEngine> engine, QObject* parent ) :
    QObject( parent )
    , engine( std::move( engine ) )
    , splash( new splash::Splash( nullptr ), &QQuickWindow::deleteLater ) //IMPORTANT! Delete ALL QObjects using deleteLater()!
    //, master( new QQuickWindow, &QQuickWindow::deleteLater )
{
}

void WindowsManager::initialize()
{
    splash->initialize( engine );
    splash->show();
}

} // windows
} // application
