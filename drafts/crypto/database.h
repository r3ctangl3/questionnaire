#ifndef Database_H
#define Database_H


#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QString>


#include <memory>


namespace quest
{


class Database
{
private:

    static const QFileInfo finfo_;

    std::unique_ptr<QSqlDatabase> db_ = nullptr;

public:

    Database();

    ~Database();

private:

    void init_database();

    void create_database();

    bool create_db_path();

};


}


#endif // Database_H
