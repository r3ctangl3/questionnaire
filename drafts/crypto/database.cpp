#include "database.h"
#include "utils.h"


namespace quest
{


const QFileInfo Database::finfo_("databases/main.sqlite");


Database::Database() : db_(QSqlDatabase::addDatabase("QSQLITE"))
{
    db_.setDatabaseName(finfo_.absoluteFilePath());

    if (!Database::finfo_.exists())
    {
        Database::create_database();
    }

    Database::init_database();

    return;
}


Database::~Database()
{
    // remove old backup if exists

    // rename database to finfo_.absoluteFilePath() + ".backup"

    // encrypt :memory: database

    // save :memory: database to file _finfo.absoluteFilePath()

    INFO("Database encrypted and placed to disk");

    return;
}


void Database::init_database()
{
    bool rc = false;

    do
    {
        // open database

        // ask for admin password

        // check if password suits

        // make database :memory: copy

        // close database

        // decrypt :memory: database

        INFO("Database inited and loaded to memory");

    } while(0);

    return;
}


void Database::create_database()
{
    bool rc = false;

    do
    {
        rc = Database::create_db_path();
        if (!rc)
        {
            ERROR("create_db_path()");
            break;
        }

        rc = db_.open();
        if (!rc)
        {
            ERROR("open()");
            break;
        }

        set_database_structure();

        INFO("Database created");

    } while (0);

    return;
}


bool Database::create_db_path()
{
    QDir dir = Database::finfo_.absoluteDir();

    if (!dir.exists())
    {
        if (!dir.mkdir(dir.absolutePath()))
        {
            return false;
        }
    }

    return true;
}


void Database::set_database_structure()
{
    bool        rc;
    QString     str;
    QSqlQuery   query;

    str = "CREATE TABLE test (      "
          "    id int privary key,  "
          "    string varchar(20)   "
          ")                        ";

    rc = query.exec(str);
    if (!rc)
    {
        ERROR("create table");
        return;
    }

    str = "INSERT INTO test         "
          "VALUES                   "
          " (0, 'Ivan'),            "
          " (1, 'Petr')             ";

    rc = query.exec(str);
    if (!rc)
    {
        ERROR("insert into");
        return;
    }
}

}
