#include "contact.h"

Contact::Contact(const QString &name, const QString &phone, const QString &email, const QString &address)
    : name(name), phone(phone), email(email), address(address) {}

QString Contact::getName() const {
    return name;
}

void Contact::setName(const QString &newName) {
    name = newName;
}

QString Contact::getPhone() const {
    return phone;
}

void Contact::setPhone(const QString &newPhone) {
    phone = newPhone;
}

QString Contact::getEmail() const {
    return email;
}

void Contact::setEmail(const QString &newEmail) {
    email = newEmail;
}

QString Contact::getAddress() const {
    return address;
}

void Contact::setAddress(const QString &newAddress) {
    address = newAddress;
}
