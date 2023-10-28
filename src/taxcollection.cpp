#include "taxcollection.h"

extern OdooService *odooService;

TaxCollection::TaxCollection(QObject *parent)
    : QOdooCollection<QOdooTax>{*odooService, parent}
{
    QOdooSearchQuery query;

    query.where("active") == true;
    query.limit(9999);
    query.fields(QOdooTax().propertyNames());
    setQuery(query);
}
