#include "MainWindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QString appDir = QCoreApplication::applicationDirPath();
    app.addLibraryPath(appDir + "/plugins");
    app.addLibraryPath(appDir + "/platforms");
    app.addLibraryPath(appDir + "/imageformats");

    app.setApplicationName("Image Viewer");
    app.setOrganizationName("YourCompany");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
