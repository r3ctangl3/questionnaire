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

namespace application
{
namespace windows
{
class WindowsManager : public QObject
{
    Q_OBJECT

public:
    explicit WindowsManager( QObject* parent );

    void setup( const QPointer< QQmlApplicationEngine >& engine );
    void showLoginWindow() noexcept;

private:
    struct Deleter
    {
        Deleter() = default;

        void operator()( QQuickWindow* window ) const noexcept
        {
            window->deleteLater();
        };
    };

private:
    std::unique_ptr< QQuickWindow, std::function< void( QObject* ) > > splash;
    std::unique_ptr< QQuickWindow, std::function< void( QObject* ) > > master;
};
} // windows
} // application

#endif //WINDOWSMANAGER_H
