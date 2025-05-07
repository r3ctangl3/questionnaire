//
// Created by elizaveta on 06.05.2025.
//

#ifndef SPLASH_H
#define SPLASH_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickWindow>

namespace application {
namespace windows {
namespace splash {

class Splash : public QQuickWindow
{
    Q_OBJECT

public:
    explicit Splash( QWindow* parent );

    void initialize( const QPointer<QQmlApplicationEngine>& engine );
};

} // windows
} // view
} // application

#endif //SPLASH_H
