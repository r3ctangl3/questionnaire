//
// Created by elizaveta on 04.05.2025.
//

#include "Application.h"

namespace application {

Application::Application( int& argc, char** argv )
    : QApplication( argc, argv )
    , engine( new QQmlApplicationEngine( this ) )
    , authorization( new authorization::Authorization( this ) )
    , windowsManager( new windows::WindowsManager( engine, this ) )
{
    //thread safety connection type
    connect( this, &Application::aboutToQuit, this, &Application::onAboutToQuit, Qt::QueuedConnection );
    connect( engine, &QQmlApplicationEngine::quit, this, &Application::quit, Qt::QueuedConnection );
    engine->addImportPath("qrc:/ui" );
    engine->addImportPath("qrc:/style" );
    //entry point to get further properties of nested classes i.e. Application pointer
    engine->rootContext()->setContextProperty( "backend", this );

    authorization->initialize();
    windowsManager->initialize();
}

void Application::onAboutToQuit()
{
    //todo closing handler
}

application::authorization::Authorization* Application::getAuthorization() const noexcept
{
    return authorization;
}

}
