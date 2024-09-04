#include "database.h"
#include "utils.h"


namespace quest
{


const QFileInfo Database::db_name_on_disk_("databases/main.sqlite");
const QString Database::db_name_in_memory_("file::memory:");
const QString Database::conn_name_on_disk_("on-disk-db");
const QString Database::conn_name_in_memory_("in-memory-db");
const QString Database::db_connect_options_("QSQLITE_OPEN_URI;QSQLITE_ENABLE_SHARED_CACHE");


Database::Database() : db_(QSqlDatabase::addDatabase("QSQLITE", conn_name_in_memory_))
{
    bool rc = false;

    db_.setConnectOptions (db_connect_options_);
    db_.setDatabaseName(db_name_in_memory_);

    do
    {
        rc = db_.open();
        if (!rc)
        {
            ERROR(db_.lastError().text().toStdString());
            break;
        }

        if (!Database::db_name_on_disk_.exists())
        {
            rc = Database::create_database();
            if (!rc)
            {
                ERROR("create_database()");
                break;
            }
        }

        rc = Database::init_database();
        if (!rc)
        {
            ERROR("init_database()");
            break;
        }

        rc = true;

    } while (0);

    if (!rc)
    {
        // TODO: [impl] raise exception in case of error
        ERROR("Database()");
    }

    return;
}


Database::~Database()
{
    // TODO: [debug] remove ---------------------------------

    QSqlQuery query(db_);

    if (!query.exec("INSERT INTO test VALUES (2, 'Andrej')"))
    {
        ERROR(query.lastError().text().toStdString());
        return;
    };

    if (!query.exec("VACUUM INTO 'databases/new.sqlite'"))
    {
        ERROR(query.lastError().text().toStdString());
        return;
    }


    // ------------------------------------------------------

    // remove old backup if exists

    // rename database to finfo_.absoluteFilePath() + ".backup"

    // encrypt :memory: database

    // save :memory: database to file _finfo.absoluteFilePath()

    INFO("Database encrypted and placed to disk");

    return;
}


bool Database::init_database()
{
    bool rc = false;

    // for disk database resources to be correctly destroyed:
    // https://doc.qt.io/qt-6/qsqldatabase.html#removeDatabase
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", conn_name_on_disk_);
        db.setConnectOptions(db_connect_options_);
        db.setDatabaseName(db_name_on_disk_.absoluteFilePath());

        do
        {
            rc = db.open();
            if (!rc)
            {
                ERROR("open()");
                break;
            }

            QSqlQuery query(db);

            rc = query.exec(QString("VACUUM INTO '%1'").arg(db_name_in_memory_));
            if (!rc)
            {
                ERROR(query.lastError().text().toStdString());
                break;
            }

            INFO(db_.tables().size());

            INFO("Database inited and loaded to memory");

            rc = true;

        } while(0);

        if (db.isOpen())
        {
            db.close();
        }
    }

    QSqlDatabase::removeDatabase(conn_name_on_disk_);

    return rc;
}


bool Database::create_database()
{
    bool rc = false;

    // for disk database resources to be correctly destroyed:
    // https://doc.qt.io/qt-6/qsqldatabase.html#removeDatabase
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", conn_name_on_disk_);
        db.setDatabaseName(db_name_on_disk_.absoluteFilePath());

        do
        {
            rc = Database::create_db_path();
            if (!rc)
            {
                ERROR("create_db_path()");
                break;
            }

            rc = db.open();
            if (!rc)
            {
                ERROR("open()");
                break;
            }

            rc = set_database_structure(db);
            if (!rc)
            {
                ERROR("set_database_structure()");
                break;
            }

            INFO("Database created");

        } while (0);

        if (db.isOpen())
        {
            db.close();
        }
    }

    QSqlDatabase::removeDatabase(conn_name_on_disk_);

    return rc;
}


bool Database::create_db_path()
{
    QDir dir = Database::db_name_on_disk_.absoluteDir();

    if (!dir.exists())
    {
        if (!dir.mkdir(dir.absolutePath()))
        {
            return false;
        }
    }

    return true;
}


bool Database::set_database_structure(const QSqlDatabase& db)
{
    bool        rc;
    QString     str;
    QSqlQuery   query(db);

    do
    {
        str = "CREATE TABLE test (      "
              "    id int privary key,  "
              "    string varchar(20)   "
              ")                        ";

        rc = query.exec(str);
        if (!rc)
        {
            ERROR("create table");
            break;
        }

        str = "INSERT INTO test         "
              "VALUES                   "
              " (0, 'Ivan'),            "
              " (1, 'Petr')             ";

        rc = query.exec(str);
        if (!rc)
        {
            ERROR("insert into");
            break;
        }

    } while (0);

    return rc;
}

}
