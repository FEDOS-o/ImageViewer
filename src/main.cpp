#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    app.setApplicationName("Image Viewer");
    app.setOrganizationName("YourCompany");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}