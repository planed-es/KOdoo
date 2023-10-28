#ifndef TAXCOLLECTION_H
#define TAXCOLLECTION_H

#include <QOdooCollection.h>
#include <QOdooTax.h>
#include <QQmlListProperty>
#include <QtQml/qqml.h>

class TaxCollection : public QOdooCollection<QOdooTax>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(TaxCollection)
public:
    explicit TaxCollection(QObject *parent = nullptr);
};

#endif // TAXCOLLECTION_H
