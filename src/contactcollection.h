#ifndef CONTACTCOLLECTION_H
#define CONTACTCOLLECTION_H

#include <QQmlListProperty>
#include <QtQml/qqml.h>
#include <odoo-qt/QOdooCollection.h>
#include <odoo-qt/QOdooPartner.h>

class ContactCollection : public QOdooCollection<QOdooPartner>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ContactCollection)
public:
    explicit ContactCollection(QObject *parent = nullptr);

    Q_INVOKABLE void filter(const QVariantMap &);
};

#endif // CONTACTCOLLECTION_H
