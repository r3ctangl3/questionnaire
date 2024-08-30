#ifndef WIDGET_H
#define WIDGET_H


#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QTextStream>
#include <QWidget>


class Widget : public QWidget
{
    Q_OBJECT    // https://stackoverflow.com/a/50197883

private:

    QLabel* label_ = nullptr;
    QLineEdit* ledit_ = nullptr;
    QFile* file_ = nullptr;
    QTextStream* out_ = nullptr;

public:

    Widget(QWidget *parent = nullptr);

    void increment();

    void decrement();

    void save();

    ~Widget();
};


#endif // WIDGET_H
