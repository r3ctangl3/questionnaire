//
// Created by elizaveta on 04.05.2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include <QQmlContext>
#include <QFontDatabase>
#include <QQmlApplicationEngine>

#include "Authorization.h"
#include "windows/WindowsManager.h"

namespace application
{

class Application final : public QApplication
{
    Q_OBJECT
    Q_PROPERTY( application::authorization::Authorization* authorization READ getAuthorization CONSTANT )

public:
    explicit Application( int& argc, char** argv );

private slots:
    void onAboutToQuit();

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
