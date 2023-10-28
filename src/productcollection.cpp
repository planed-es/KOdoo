#include "productcollection.h"

extern OdooService *odooService;

ProductCollection::ProductCollection(QObject *parent)
    : QOdooCollection<QOdooProduct>{*odooService, parent}
{
    QOdooSearchQuery query;

    // query.where("name") != QString("tintin");
    query.limit(10);
    query.fields(QOdooProduct().propertyNames());
    setQuery(query);
}

ProductTemplateCollection::ProductTemplateCollection(QObject *parent)
    : QOdooCollection<QOdooProductTemplate>{*odooService, parent}
{
    QOdooSearchQuery query;

    query.offset(10);
    query.limit(10);
    query.fields(QOdooProduct().propertyNames());
    setQuery(query);
}
