#include "dev/Application.h"

int main(int argc, char *argv[])
{

    application::Application app( argc, argv ); //todo static or singletone?
    app.authorize();
    return app.exec();

}
