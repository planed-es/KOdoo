#ifndef COUNTRYCOLLECTION_H
#define COUNTRYCOLLECTION_H

#include <QtQml/qqml.h>
#include <odoo-qt/QOdooCollection.h>
#include <odoo-qt/QOdooCountry.h>

class CountryCollection : public QOdooCollection<QOdooCountry>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(CountryCollection)
public:
    explicit CountryCollection(QObject *parent = nullptr);
};

#endif // COUNTRYCOLLECTION_H
