#ifndef TAXCOLLECTION_H
#define TAXCOLLECTION_H

#include <QQmlListProperty>
#include <QtQml/qqml.h>
#include <odoo-qt/QOdooCollection.h>
#include <odoo-qt/QOdooTax.h>

class TaxCollection : public QOdooCollection<QOdooTax>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(TaxCollection)
public:
    explicit TaxCollection(QObject *parent = nullptr);
};

#endif // TAXCOLLECTION_H
