#include <QString>
#include <QList>


// This source file is used only in database.cpp
// just to move hardcoded database structure outside
// of database management source code.



namespace quest
{


QList<QString> db_create_structure_queries =
{
    "CREATE TABLE Control (                                 "
    "   salt_decrypted varchar(16),                         "       // see SALT_WCHAR
    "   salt_encrypted varchar(16)                          "       // see SALT_WCHAR
    ")                                                      ",

    "CREATE TABLE Clients (                                 "
    "   id              int primary key,                    "
    "   name_given      varchar(32),                        "
    "   name_middle     varchar(32),                        "
    "   name_last       varchar(32),                        "
    "   birth_date      TEXT,                               "       // TODO: [?] how is date stored
    "   comment         TEXT                                "
    ")                                                      ",

    "CREATE TABLE Tests (                                   "
    "   id              int primary key,                    "
    "   title           TEXT,                               "
    "   description     TEXT                                "
    ")                                                      ",

    "CREATE TABLE TestQueue (                               "
    "   id              int primary key,                    "
    "   client_id       int,                                "
    "   test_id         int,                                "
    "   priority        int,                                "
    "   date            TEXT,                               "       // TODO: [?] how is date stored
    "   FOREIGN KEY (client_id) REFERENCES Clients (id),    "
    "   FOREIGN KEY (test_id) REFERENCES Tests (id)         "
    ")                                                      ",

    "CREATE TABLE Results (                                 "
    "   id              int primary key,                    "
    "   client_id       int,                                "
    "   test_id         int,                                "
    "   date            TEXT,                               "       // TODO: [?] how is date stored
    "   result          TEXT,                               "
    "   FOREIGN KEY (client_id) REFERENCES Clients (id),    "
    "   FOREIGN KEY (test_id) REFERENCES Tests (id)         "
    ")                                                      ",

    "CREATE TABLE Answers (                                 "
    "   result_id       int,                                "
    "   question        int,                                "
    "   answers         TEXT,                               "
    "   FOREIGN KEY (result_id) REFERENCES RESULTS (id)     "
    ")                                                      "
};


} // namespace quest
