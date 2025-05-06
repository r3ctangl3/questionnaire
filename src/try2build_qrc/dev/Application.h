//
// Created by elizaveta on 04.05.2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Authorization.h"
#include "WindowsManager.h"

namespace application
{

class Application final : public QApplication
{
    Q_OBJECT
    Q_PROPERTY( application::authorization::Authorization* authorization READ getAuthorization CONSTANT )

public:
    explicit Application( int argc, char* argv[ ] );

    void authorize() const noexcept; //todo naming (help)

private:
    application::authorization::Authorization* getAuthorization() const noexcept;

private:
    QPointer< QQmlApplicationEngine > engine;

    //classes have parent (Application). Removal of parent will release their memory
    authorization::Authorization* authorization;
    windows::WindowsManager* windowsManager;
};

}

#endif