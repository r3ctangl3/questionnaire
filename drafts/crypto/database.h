#ifndef Database_H
#define Database_H


#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>


#include <memory>


namespace quest
{


class Database
{
private:

    static const QFileInfo finfo_;

    QSqlDatabase db_;

public:

    Database();

    ~Database();

private:

    void init_database();

    void create_database();

    bool create_db_path();

    void set_database_structure();

};


}


#endif // Database_H
