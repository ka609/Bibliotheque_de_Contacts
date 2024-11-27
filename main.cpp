#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    try {
        // Création de la fenêtre principale
        MainWindow mainWindow;
        mainWindow.show();

        // Exécution de l'application
        return app.exec();
    } catch (const std::exception &e) {
        // Gestion des exceptions standard
        QMessageBox::critical(nullptr, "Erreur fatale", QString("Une erreur est survenue : %1").arg(e.what()));
        return -1;
    } catch (...) {
        // Gestion des exceptions inconnues
        QMessageBox::critical(nullptr, "Erreur inconnue", "Une erreur inconnue s'est produite.");
        return -1;
    }
}
