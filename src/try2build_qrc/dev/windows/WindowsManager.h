//
// Created by elizaveta on 04.05.2025.
//

#ifndef WINDOWSMANAGER_H
#define WINDOWSMANAGER_H

#include <QObject>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <memory>

#include "splash/Splash.h"

namespace application
{
namespace windows
{

class WindowsManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowsManager( QPointer< QQmlApplicationEngine > engine, QObject* parent );

    void initialize();

private:
    QPointer< QQmlApplicationEngine > engine;

    std::unique_ptr< splash::Splash, std::function< void( QObject* ) > > splash;
    //std::unique_ptr< QQuickWindow, std::function< void( QObject* ) > > master;
};
} // windows
} // application

#endif //WINDOWSMANAGER_H
