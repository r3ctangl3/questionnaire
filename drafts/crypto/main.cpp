#include "crypto.h"
#include "database.h"
#include "utils.h"
#include "widget.h"


#include <QApplication>
#include <QByteArray>
#include <QIcon>
#include <QList>
#include <QSize>
#include <QString>
#include <QTextStream>


static void database_test(QTextStream& out);
static void crypto_test(QTextStream& out);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextStream out(stdout);

    Widget window;
    QSize size(400, 140);
    QIcon icon("icon.png");
    QString title("GuiApp");
    QString tip("ToolTip");
    window.resize(size);
    window.setWindowIcon(icon);
    window.setWindowTitle(title);
    window.setToolTip(tip);
    window.show();

    crypto_test(out);
    // database_test(out);

    return a.exec();
}


void database_test(QTextStream& out)
{
    quest::Database db;
}


void crypto_test(QTextStream& out)
{
    quest::Crypto crypto;
    if (!crypto.ok())
    {
        ERROR("Filed to create crypto instance");
        return;
    }

    QString salt = crypto.generate_random_salt();
    out << "Salt. size=" << salt.size() << ", val=" << salt << Qt::endl;

    crypto.set_salt(salt);

    // QString passwd("password");
    // crypto.evaluate_key(passwd);
    // crypto.generate_keystreams(1, 1);

    /*
        password                // from UI
        key                     // from password
        salt                    // from DB (generate one time)
        salt enrypted           // from DB (encrypted every time)
        nonce                   // from DB, to DB (generate every time)

        db flow
            init [static] -> open, create tables, set nonce (0), set controls (plain salt, encrypted salt (the same)), close
            load [object] -> open, check password, :memory:, close, decrypt, work, set nonce (crypto), encrypt salt, encrypt db, save, close

        init crypto
        detect first launch
            if first launch -> ask new password, generate and save salt, init db
        ask password
        load db
        crypto: generate keystreams
        check password
            if first launch -> new password, entered password
            else -> decrypted db.control, encrypted db.control
        ...
        ...
        ...
        finishing program:
            encrypt salt with new keystream
            encrypt clients' data with new keystream
            set new nonce

        crypto interface:
        +   init -> every time [made in constructor, so crypto is always inited]
        +   generate salt -> only first run, oneshot
        +   set_salt -> every run, oneshot
            decrypt -> every run, repeatable
            encrypt -> every run, repeatable
        +   generate_keystreams(password, salt, decrypt_nonce) -> every run, oneshot (return encrypt_nonce)
    */
}

