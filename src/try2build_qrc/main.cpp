#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlComponent>
#include <QQuickItem>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath( "qrc:/" );

    const QUrl url( QStringLiteral( "qrc:/main.qml" ) );
    QQmlComponent component( &engine );

    component.loadUrl( url );
    const auto rootObject = component.create();
    const auto rootItem = qobject_cast< QQuickItem* >( rootObject );

    QQuickWindow mainWindow;
    mainWindow.setHeight( 600 );
    mainWindow.setWidth( 800 );
    mainWindow.setTitle( "Try2Build" );

    const auto& contentItem = mainWindow.contentItem();

    rootItem->setParentItem( contentItem );
    rootItem->setProperty( "anchors.left", QVariant::fromValue( contentItem->property("left") ) );
    rootItem->setProperty( "anchors.right", QVariant::fromValue( contentItem->property("right") ) );
    rootItem->setProperty( "anchors.top", QVariant::fromValue( contentItem->property("top") ) );
    rootItem->setProperty( "anchors.bottom", QVariant::fromValue( contentItem->property("bottom") ) );

    mainWindow.show();

    return app.exec();
}
