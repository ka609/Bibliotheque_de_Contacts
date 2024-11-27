#include "contactmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <algorithm>

void ContactManager::addContact(const Contact& contact) {
    if (!isDuplicate(contact)) {
        contacts.append(contact);
    } else {
        qWarning() << "Contact déjà existant : " << contact.getName();
    }
}

bool ContactManager::modifyContact(int index, const Contact& contact) {
    if (index >= 0 && index < contacts.size()) {
        contacts[index] = contact;
        return true;
    }
    return false;
}

bool ContactManager::deleteContact(int index) {
    if (index >= 0 && index < contacts.size()) {
        contacts.removeAt(index);
        return true;
    }
    return false;
}

QList<Contact> ContactManager::searchContacts(const QString& name) const {
    QList<Contact> results;
    for (const auto& contact : contacts) {
        if (contact.getName().contains(name, Qt::CaseInsensitive)) {
            results.append(contact);
        }
    }
    return results;
}

void ContactManager::sortContacts() {
    std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
        return a.getName().toLower() < b.getName().toLower();
    });
}

bool ContactManager::saveToFile(const QString& filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Impossible d'ouvrir le fichier en écriture : " << filename;
        return false;
    }

    QTextStream out(&file);
    for (const auto& contact : contacts) {
        out << contact.getName() << ";" << contact.getPhone() << ";"
            << contact.getEmail() << ";" << contact.getAddress() << "\n";
    }
    file.close();
    return true;
}

bool ContactManager::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Impossible d'ouvrir le fichier en lecture : " << filename;
        return false;
    }

    contacts.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        if (fields.size() == 4) {
            contacts.append(Contact(fields[0], fields[1], fields[2], fields[3]));
        }
    }
    file.close();
    return true;
}

QList<Contact> ContactManager::getContacts() const {
    return contacts;
}

bool ContactManager::isDuplicate(const Contact& contact) const {
    for (const auto& existingContact : contacts) {
        if (existingContact.getName().toLower() == contact.getName().toLower() &&
            existingContact.getPhone() == contact.getPhone()) {
            return true;
        }
    }
    return false;
}
