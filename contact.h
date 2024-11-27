#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class Contact {
public:
    Contact(const QString& name, const QString& phone, const QString& email, const QString& address);

    QString getName() const;
    QString getPhone() const;
    QString getEmail() const;
    QString getAddress() const;

    void setName(const QString& name);
    void setPhone(const QString& phone);
    void setEmail(const QString& email);
    void setAddress(const QString& address);

private:
    QString name;
    QString phone;
    QString email;
    QString address;
};

#endif // CONTACT_H
