#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Configuration initiale de la table
    ui->tableWidgetContacts->setColumnCount(4);
    ui->tableWidgetContacts->setHorizontalHeaderLabels({"Nom", "Téléphone", "Email", "Adresse"});
    ui->tableWidgetContacts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetContacts->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetContacts->horizontalHeader()->setStretchLastSection(true);

    loadContacts();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateTable() {
    // Supprimer toutes les lignes de la table
    ui->tableWidgetContacts->setRowCount(0);

    // Récupérer les contacts et les afficher dans la table
    auto contacts = contactManager.getContacts();
    for (const auto& contact : contacts) {
        int row = ui->tableWidgetContacts->rowCount();
        ui->tableWidgetContacts->insertRow(row);
        ui->tableWidgetContacts->setItem(row, 0, new QTableWidgetItem(contact.getName()));
        ui->tableWidgetContacts->setItem(row, 1, new QTableWidgetItem(contact.getPhone()));
        ui->tableWidgetContacts->setItem(row, 2, new QTableWidgetItem(contact.getEmail()));
        ui->tableWidgetContacts->setItem(row, 3, new QTableWidgetItem(contact.getAddress()));
    }
}

void MainWindow::on_buttonAdd_clicked() {
    // Vérifier que tous les champs sont remplis
    if (ui->lineEditName->text().isEmpty() || ui->lineEditPhone->text().isEmpty() ||
        ui->lineEditEmail->text().isEmpty() || ui->lineEditAddress->text().isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }

    // Ajouter un nouveau contact
    Contact contact(
        ui->lineEditName->text(),
        ui->lineEditPhone->text(),
        ui->lineEditEmail->text(),
        ui->lineEditAddress->text()
        );
    contactManager.addContact(contact);
    updateTable();

    // Réinitialiser les champs
    clearInputFields();
    QMessageBox::information(this, "Succès", "Contact ajouté avec succès.");
}

void MainWindow::on_buttonModify_clicked() {
    int row = ui->tableWidgetContacts->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un contact à modifier.");
        return;
    }

    // Vérifier que tous les champs sont remplis
    if (ui->lineEditName->text().isEmpty() || ui->lineEditPhone->text().isEmpty() ||
        ui->lineEditEmail->text().isEmpty() || ui->lineEditAddress->text().isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }

    // Modifier le contact sélectionné
    Contact contact(
        ui->lineEditName->text(),
        ui->lineEditPhone->text(),
        ui->lineEditEmail->text(),
        ui->lineEditAddress->text()
        );
    contactManager.modifyContact(row, contact);
    updateTable();

    // Réinitialiser les champs
    clearInputFields();
    QMessageBox::information(this, "Succès", "Contact modifié avec succès.");
}

void MainWindow::on_buttonDelete_clicked() {
    int row = ui->tableWidgetContacts->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un contact à supprimer.");
        return;
    }

    // Confirmation avant suppression
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation", "Êtes-vous sûr de vouloir supprimer ce contact ?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        contactManager.deleteContact(row);
        updateTable();
        QMessageBox::information(this, "Succès", "Contact supprimé avec succès.");
    }
}

void MainWindow::on_buttonSearch_clicked() {
    QString name = ui->lineEditName->text();

    // Réinitialiser la vue si le champ de recherche est vide
    if (name.isEmpty()) {
        updateTable();
        return;
    }

    // Afficher les résultats de recherche
    auto results = contactManager.searchContacts(name);
    ui->tableWidgetContacts->setRowCount(0);
    for (const auto& contact : results) {
        int row = ui->tableWidgetContacts->rowCount();
        ui->tableWidgetContacts->insertRow(row);
        ui->tableWidgetContacts->setItem(row, 0, new QTableWidgetItem(contact.getName()));
        ui->tableWidgetContacts->setItem(row, 1, new QTableWidgetItem(contact.getPhone()));
        ui->tableWidgetContacts->setItem(row, 2, new QTableWidgetItem(contact.getEmail()));
        ui->tableWidgetContacts->setItem(row, 3, new QTableWidgetItem(contact.getAddress()));
    }
}

void MainWindow::on_buttonSort_clicked() {
    contactManager.sortContacts();
    updateTable();
    QMessageBox::information(this, "Succès", "Contacts triés avec succès.");
}

void MainWindow::on_buttonSave_clicked() {
    if (contactManager.saveToFile("contacts.txt")) {
        QMessageBox::information(this, "Succès", "Contacts sauvegardés avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la sauvegarde des contacts.");
    }
}

void MainWindow::loadContacts() {
    if (contactManager.loadFromFile("contacts.txt")) {
        updateTable();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger les contacts depuis le fichier.");
    }
}

void MainWindow::clearInputFields() {
    ui->lineEditName->clear();
    ui->lineEditPhone->clear();
    ui->lineEditEmail->clear();
    ui->lineEditAddress->clear();
}
