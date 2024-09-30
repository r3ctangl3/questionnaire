#include "database.h"
#include "utils.h"


namespace quest
{


extern QList<QString> db_create_structure_queries;


const QString Database::db_name_on_disk_("databases/main.sqlite");
const QString Database::db_name_on_disk_backup_("databases/main.sqlite.backup");
const QString Database::db_name_on_disk_new_("databases/main.sqlite.new");
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

        if (!QFileInfo::exists(db_name_on_disk_))
        {
            rc = create_database();
            if (!rc)
            {
                ERROR("create_database()");
                break;
            }
        }

        rc = init_database();
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
    // we discard saving result because we can
    // do nothing if something goes wrong inside
    // the destructor. Therefore save_database()
    // function should be called explicitely before
    // the program is over to have the opportunity
    // to handle error. Destructor should just be.

    save_database();
    return;
}


bool Database::save_database()
{
    bool rc = false;

    QSqlQuery query(db_);
    QFile db_on_disk(db_name_on_disk_);
    QFile db_on_disk_backup(db_name_on_disk_backup_);
    QFile db_on_disk_new(db_name_on_disk_new_);

    do
    {
        // first of all we have to save in-memory database to on-disk

        rc = encrypt_database();
        if (!rc)
        {
            ERROR("encrypt_database()");
            break;
        }

        rc = query.exec(QString("VACUUM INTO '%1'").arg(db_name_on_disk_new_));
        if (!rc)
        {
            ERROR(query.lastError().text().toStdString());
            break;
        }

        // now we rotate on-disk backup: current main database becomes backup

        if (db_on_disk_backup.exists())
        {
            rc = db_on_disk_backup.remove();
            if (!rc)
            {
                ERROR(query.lastError().text().toStdString());
                break;
            }
        }

        if (db_on_disk.exists())
        {
            rc = db_on_disk.rename(db_name_on_disk_backup_);
            if (!rc)
            {
                ERROR(query.lastError().text().toStdString());
                break;
            }
        }

        // now we rename new on-disk database to be the main one

        rc = db_on_disk_new.rename(db_name_on_disk_);
        if (!rc)
        {
            ERROR(query.lastError().text().toStdString());
            break;
        }

        INFO("Database encrypted and placed to disk");

    } while (0);

    return rc;
}


bool Database::set_nonce(uint32_t nonce)
{
    QSqlQuery query(db_);

    bool rc = query.exec(QString("PRAGMA user_version = %1").arg(nonce));
    if (!rc)
    {
        ERROR(query.lastError().text().toStdString());
    }

    return rc;
}


uint32_t Database::get_nonce()
{
    bool rc = false;
    uint32_t nonce = 0;
    QSqlQuery query(db_);

    do
    {
        rc = query.exec(QString("PRAGMA user_version"));
        if (!rc)
        {
            ERROR(query.lastError().text().toStdString());
            break;
        }

        rc = query.isActive();
        if (!rc)
        {
            ERROR(query.lastError().text().toStdString());
            break;
        }

        rc = query.first();
        if (!rc)
        {
            ERROR(query.lastError().text().toStdString());
            break;
        }

        nonce = query.value(0).toUInt();

    } while (0);

    return nonce;
}


bool Database::init_database()
{
    bool rc = false;

    // for disk database resources to be correctly destroyed:
    // https://doc.qt.io/qt-6/qsqldatabase.html#removeDatabase
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", conn_name_on_disk_);
        db.setConnectOptions(db_connect_options_);
        db.setDatabaseName(QFileInfo(db_name_on_disk_).absoluteFilePath());

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

            rc = decrypt_database();
            if (!rc)
            {
                ERROR("decrypt_database()");
                break;
            };

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
        db.setDatabaseName(QFileInfo(db_name_on_disk_).absoluteFilePath());

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
            if (!rc)
            {
                QFile(db_name_on_disk_).remove();
            }

            db.close();
        }
    }

    QSqlDatabase::removeDatabase(conn_name_on_disk_);

    return rc;
}


bool Database::create_db_path()
{
    QDir dir = QFileInfo(db_name_on_disk_).absoluteDir();

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
    bool rc = true;
    QSqlQuery query(db);

    for (const auto& q : db_create_structure_queries)
    {
        rc = query.exec(q);
        if (!rc)
        {
            ERROR(query.lastError().text().toStdString());
            break;
        }
    }

    query.exec("INSERT INTO Tests VALUES (0, '0', '00'), (1, '1', '11')");      // TODO: [debug] remove

    return rc;
}


bool Database::decrypt_database()
{
    // TODO: [impl] implement decryption

    return true;
}


bool Database::encrypt_database()
{
    // TODO: [impl] implement encryption

    return true;
}


} // namespace quest
