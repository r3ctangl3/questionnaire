//
// Created by elizaveta on 04.05.2025.
//

#include "Application.h"

namespace application {

Application::Application( int argc, char* argv[] )
    : QApplication( argc, argv )
    , engine( new QQmlApplicationEngine( this ) )
    , authorization( new authorization::Authorization( this ) )
    , windowsManager( new windows::WindowsManager( this ) )
{
    engine->addImportPath("qrc:/" );
    //entry point to get further properties of nested classes i.e. Application pointer
    engine->rootContext()->setContextProperty( "backend", this );

    authorization->setup();
    windowsManager->setup( engine );
}

void Application::authorize() const noexcept
{
    windowsManager->showLoginWindow();
}

application::authorization::Authorization* Application::getAuthorization() const noexcept
{
    return authorization;
}

}
