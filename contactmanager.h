#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include "contact.h"
#include <QList>
#include <QString>

class ContactManager {
public:
    void addContact(const Contact& contact); // Ajouter un contact
    bool modifyContact(int index, const Contact& contact); // Modifier un contact
    bool deleteContact(int index); // Supprimer un contact
    QList<Contact> searchContacts(const QString& name) const; // Rechercher un contact
    void sortContacts(); // Trier les contacts
    bool saveToFile(const QString& filename) const; // Sauvegarder dans un fichier
    bool loadFromFile(const QString& filename); // Charger depuis un fichier

    QList<Contact> getContacts() const; // Récupérer tous les contacts
    bool isDuplicate(const Contact& contact) const; // Vérifier si un contact existe déjà

private:
    QList<Contact> contacts; // Liste des contacts
};

#endif // CONTACTMANAGER_H
