#ifndef Database_H
#define Database_H


#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>


#include <memory>


namespace quest
{


class Database
{
private:

    static const QFileInfo db_name_on_disk_;
    static const QString db_name_in_memory_;
    static const QString conn_name_on_disk_;
    static const QString conn_name_in_memory_;
    static const QString db_connect_options_;    // required for VACUUM to work properly

    QSqlDatabase db_;   // in-memory database handler

public:

    Database();

    ~Database();

private:

    bool init_database();

    bool create_database();

    bool create_db_path();

    bool set_database_structure(const QSqlDatabase& db);

};


}


#endif // Database_H
