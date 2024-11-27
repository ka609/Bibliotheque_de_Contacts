#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contactmanager.h" // Assurez-vous que cette classe existe et gère les contacts

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonAdd_clicked();
    void on_buttonModify_clicked();
    void on_buttonDelete_clicked();
    void on_buttonSearch_clicked();
    void on_buttonSort_clicked();
    void on_buttonSave_clicked();

private:
    Ui::MainWindow *ui;

    // Gestion des contacts
    ContactManager contactManager;

    // Méthodes utilitaires
    void loadContacts();        // Charger les contacts depuis un fichier
    void updateTable();         // Mettre à jour la table avec les contacts
    void clearInputFields();    // Réinitialiser les champs de saisie
};

#endif // MAINWINDOW_H
