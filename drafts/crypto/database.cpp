#include "database.h"
#include "utils.h"


namespace quest
{


const QFileInfo Database::finfo_("databases/main.sqlite");


Database::Database()
{
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

    // rename database to _finfo.absoluteFilePath() + ".backup"

    // encrypt :memory: database

    // save :memory: database to file _finfo.absoluteFilePath()

    INFO("Database encrypted and placed to disk");

    return;
}


void Database::init_database()
{
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

        // create database first time and set its structure

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


}
