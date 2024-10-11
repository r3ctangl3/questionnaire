#include "crypto.h"
#include "database.h"
#include "utils.h"
#include "widget.h"


#include <QApplication>
#include <QByteArray>
#include <QFile>
#include <QIcon>
#include <QList>
#include <QRegularExpression>
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
    QString filePath = "output.txt";
    QFile file(filePath);

    quest::Crypto* crypto = quest::Crypto::instance();
    if (!crypto->ok()) {
        ERROR("Failed to create crypto instance");
        return;
    }

    QString passwd("password");

    crypto->generate_random_salt();
    crypto->evaluate_key(passwd);
    crypto->generate_keystreams(1, 1, 42);

    uint32_t nonce = crypto->get_encrypt_nonce();
    qDebug() << "Nonce: decrypt = 42, encrypt =" << nonce;

    QString data("Иванов Иван Иванович проходил тест и показал следующий результат");

    QString plain = data;

    crypto->encrypt(plain);
    qDebug() << plain;

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream fout(&file);
        fout << plain;
        file.close();
    }

    QString cypher;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream fin(&file);
        cypher = fin.readAll();
        file.close();
    }

    crypto->decrypt(cypher);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream fout(&file);
        fout << Qt::endl << cypher;
        file.close();
    }

    qDebug() << ((data == cypher) ? "OK" : "Error");

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

