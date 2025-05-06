//
// Created by elizaveta on 04.05.2025.
//

#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QtCore>
#include <QObject>

namespace application
{
namespace authorization
{
//IMPORTANT! nested namespaces broke Q_PROPERTY system

class Authorization : public QObject //add signal-slot system. QML required
{
    Q_OBJECT                         //also for signal-slot system. QML required
    Q_PROPERTY( bool accountExists READ getAccountExists NOTIFY accountExistsChanged ) //qml visible

public:
    explicit Authorization( QObject* parent );

    void setup();

private:
    bool getAccountExists() const noexcept; //READ required. Makes visible 'accountExists' in QML

signals:
    void accountExistsChanged();            //Notify that property changes from c++. Useless for CONSTANT property

private:
    //todo add crypto member
    bool accountExists;
};
} // authorization
} // application

#endif //AUTHORIZATION_H
