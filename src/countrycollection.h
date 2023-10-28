#ifndef COUNTRYCOLLECTION_H
#define COUNTRYCOLLECTION_H

#include <QOdooCollection.h>
#include <QOdooCountry.h>
#include <QtQml/qqml.h>

class CountryCollection : public QOdooCollection<QOdooCountry>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(CountryCollection)
public:
    explicit CountryCollection(QObject *parent = nullptr);
};

#endif // COUNTRYCOLLECTION_H
