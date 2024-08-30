#include "crypto.h"
#include "database.h"
#include "utils.h"
#include "widget.h"


#include <QApplication>
#include <QByteArray>
#include <QIcon>
#include <QSize>
#include <QString>
#include <QTextStream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextStream out(stdout);

    quest::Crypto crypto;
    if (!crypto.ok())
    {
        ERROR("Filed to create crypto instance");
        return 1;
    }

    QString salt = crypto.generate_random_salt();
    out << "Salt. size=" << salt.size() << ", val=" << salt << Qt::endl;

    QString passwd("password");
    crypto.evaluate_key(passwd);
    crypto.generate_keystreams(1, 1);

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
            copy :memory: db to the disk
            remove previous db from disk

        crypto interface:
        +   init -> every time [made in constructor, so crypto is always inited]
        +   generate salt -> only first run, oneshot
            set_salt -> every run, oneshot
            decrypt -> every run, repeatable
            encrypt -> every run, repeatable
        +   generate_keystreams(password, salt, decrypt_nonce) -> every run, oneshot (return encrypt_nonce)
     */

    // quest::Database db;

    return a.exec();
}
