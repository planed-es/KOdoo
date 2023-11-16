#ifndef COUNTRYSTATECOLLECTION_H
#define COUNTRYSTATECOLLECTION_H

#include <QtQml/qqml.h>
#include <odoo-qt/QOdooCollection.h>
#include <odoo-qt/QOdooCountryState.h>

class CountryStateCollection : public QOdooCollection<QOdooCountryState>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(CountryStateCollection)
    Q_PROPERTY(unsigned long countryId MEMBER _countryId NOTIFY countryIdChanged)
public:
    explicit CountryStateCollection(QObject *parent = nullptr);

    void setModels(const QVector<QOdooCountryState *> &) override;

signals:
    void countryIdChanged();

private:
    QOdooModel::IdType _countryId = 0;
};

#endif // COUNTRYSTATECOLLECTION_H
