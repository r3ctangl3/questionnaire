#include <QGuiApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine; //to APPLICATION CLASS
    engine.addImportPath( "qrc:/" );
    const QUrl url(QStringLiteral("qrc:/Durka/main.qml")); //WINDOW DELEGATES

    engine.load(url); //WINDOW DELEGATE
    return app.exec();
}
