#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <GameController.h>

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<GameController>("com.GameController", 1, 0, "GameController");

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}
