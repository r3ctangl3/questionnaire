#include "dev/Application.h"

int main(int argc, char *argv[])
{
    application::Application::setAttribute( Qt::AA_UseSoftwareOpenGL, true );
    QQuickWindow::setDefaultAlphaBuffer( true );

    application::Application testLab( argc, argv );

    const auto result = testLab.exec();
    return result;
}
