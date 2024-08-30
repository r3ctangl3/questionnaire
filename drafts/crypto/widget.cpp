#include "widget.h"


#include <QApplication>
#include <QDir>
#include <QFrame>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>


/*
    What widget is:
    https://doc.qt.io/qt-6/widgets-tutorial.html

    Widget::connect description:
    https://doc.qt.io/qt-6/qobject.html#connect
 */


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // Different cursors
    //
    // QFrame* frame1 = new QFrame(this);
    // frame1->setFrameStyle(QFrame::Box);
    // frame1->setCursor(Qt::WaitCursor);
    // QFrame* frame2 = new QFrame(this);
    // frame2->setFrameStyle(QFrame::Box);
    // frame2->setCursor(Qt::PointingHandCursor);
    // QGridLayout* grid = new QGridLayout(this);
    // grid->addWidget(frame1, 0, 0);
    // grid->addWidget(frame2, 0, 1);
    // QWidget::setLayout(grid);

    // Interactive buttons. Connect whith the same class
    //
    // QPushButton* increment_button = nullptr;
    // QPushButton* decrement_button = nullptr;
    // QGridLayout* grid = nullptr;
    // QPushButton* quit_button = nullptr;
    // try
    // {
    //     increment_button = new QPushButton("+", this);
    //     decrement_button = new QPushButton("-", this);
    //     grid = new QGridLayout(this);
    //     label_ = new QLabel("0", this);
    //     // Widgets creation order is essential. If create quit button
    //     // after grid and don't add to it, the button is not clicable
    //     quit_button = new QPushButton("Quit", this);
    // }
    // catch (const std::bad_alloc& e)
    // {
    //     qApp->quit();
    // }
    // grid->addWidget(increment_button, 0, 0);
    // grid->addWidget(decrement_button, 0, 1);
    // grid->addWidget(label_, 1, 1);
    // QWidget::setLayout(grid);
    // QWidget::connect(increment_button, &QPushButton::clicked, this, &Widget::increment);
    // QWidget::connect(decrement_button, &QPushButton::clicked, this, &Widget::decrement);
    // quit_button->setGeometry(300, 185, 75, 40);
    // QWidget::connect(quit_button, &QPushButton::clicked, qApp, &QApplication::quit);

    file_ = new QFile("log.txt");
    // if (!file_->open(QIODevice::WriteOnly | QIODevice::Append))
    if (!file_->open(QIODevice::WriteOnly))
        qApp->exit();
    out_ = new QTextStream(file_);

    ledit_ = new QLineEdit(this);
    QFormLayout* layout = new QFormLayout(this);
    layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addRow("Enter:", ledit_);

    QPushButton* save_button = new QPushButton("Save", this);
    save_button->setGeometry(300, 85, 75, 40);
    QWidget::connect(save_button, &QPushButton::clicked, this, &Widget::save);


    // 1. Deploynment (create tables, etc.) is done while installation in other bin file or by running the same app whith flags?
    // 2. Qt SQL documentation
    // 3. Read and try: https://habr.com/ru/articles/128836/
    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main");
    db.setDatabaseName("databases/main.sqlite");
    bool rc = db.open();
    if (!rc)
    {
        (*out_) << "open() main db failed: " << db.lastError().text() << Qt::endl;
        qApp->quit();
    }
    QSqlQuery query(db);
    rc = query.exec("CREATE TABLE aaa (id int, text varchar(16))");
    if (!rc)
    {
        (*out_) << "create table aaa failed: " << query.lastError().text() << Qt::endl;
        qApp->quit();
    }
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE", "main1");
    db1.setDatabaseName("databases/main.sqlite");
    rc = db1.open();
    if (!rc)
    {
        (*out_) << "open() main db1 failed: " << db1.lastError().text() << Qt::endl;
        qApp->quit();
    }
    QSqlQuery query1(db1);
    rc = query1.exec("INSERT INTO aaa (id, text) VALUES (0, 'zero'), (1, 'one')");
    if (!rc)
    {
        (*out_) << "insert values into aaa failed: " << query1.lastError().text() << Qt::endl;
        qApp->quit();
    }
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "another");
    db2.setDatabaseName("databases/another.sqlite");
    rc = db2.open();
    if (!rc)
    {
        (*out_) << "open() main db failed: " << db2.lastError().text() << Qt::endl;
        qApp->quit();
    }
    QSqlQuery query2(db2);
    rc = query2.exec("CREATE TABLE aaa (id int, text varchar(16))");
    if (!rc)
    {
        (*out_) << "create table aaa failed: " << query2.lastError().text() << Qt::endl;
        qApp->quit();
    }
    */
    // Tasks:
    //     scheme to another editor
    //     installer binary
    //     deploy db


}


Widget::~Widget()
{
    file_->close();
    delete file_;
    delete out_;
}


void Widget::increment()
{
    label_->setText(QString::number(label_->text().toInt() + 1));
}


void Widget::decrement()
{
    label_->setText(QString::number(label_->text().toInt() - 1));
}


void Widget::save()
{
    // QString str = ledit_->text();
    // *out_ << str << Qt::endl;
    // QChar* c1 = str.data();
    // QChar* c2 = c1 + 1;
    // *out_ << c1->unicode() << " " << c2->unicode() << Qt::endl;
    // *out_ << (int16_t)(c1->unicode()) << " " << (int16_t)(c2->unicode()) << Qt::endl;
    // c1->unicode() = c1->unicode() ^ c2->unicode();
    // c2->unicode() = c1->unicode() ^ c2->unicode();
    // c1->unicode() = c1->unicode() ^ c2->unicode();
    // *out_ << c1->unicode() << " " << c2->unicode() << Qt::endl;
    // *out_ << (int16_t)(c1->unicode()) << " " << (int16_t)(c2->unicode()) << Qt::endl;
    // *out_ << str << Qt::endl;
    // QChar *data = str.data();
    // while (!data->isNull()) {
    //     *out_ << data->unicode() << "_" << Qt::endl;
    //     ++data;
    // }

    *out_ << ledit_->text() << Qt::endl;
    ledit_->clear();
}
