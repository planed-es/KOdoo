#include "countrystatecollection.h"

extern OdooService *odooService;

CountryStateCollection::CountryStateCollection(QObject *parent)
    : QOdooCollection<QOdooCountryState>{*odooService, parent}
{
    QOdooSearchQuery query;

    query.fields(QOdooCountryState().propertyNames());
    setQuery(query);
    connect(this, &CountryStateCollection::countryIdChanged, this, &CountryStateCollection::queryChanged);
}

void CountryStateCollection::setModels(const QVector<QOdooCountryState *> &list)
{
    QVector<QOdooCountryState *> selection;

    qDebug() << "CountryStateCollection::setModels" << list.size();
    for (QOdooCountryState *model : list) {
        if (model->countryId() == _countryId)
            selection.push_back(model);
    }
    QOdooCollection<QOdooCountryState>::setModels(selection);
    qDebug() << "-> selected models" << _models.size() << "using countryId" << _countryId;
}
