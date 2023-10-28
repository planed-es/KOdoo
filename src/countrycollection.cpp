#include "countrycollection.h"

extern OdooService *odooService;

CountryCollection::CountryCollection(QObject *parent)
    : QOdooCollection<QOdooCountry>{*odooService, parent}
{
    QOdooSearchQuery query;

    query.fields(QOdooCountry().propertyNames());
    setQuery(query);
}
