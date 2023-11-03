#include "productcollection.h"

extern OdooService *odooService;

static void decorateQuery(QOdooSearchQuery &query, const QVariantMap &params)
{
    query.fields(QOdooProduct().propertyNames());
    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it.key() == "name")
            query.where("name").like(it.value().toString());
    }
}

ProductCollection::ProductCollection(QObject *parent)
    : QOdooCollection<QOdooProduct>{*odooService, parent}
{
    QOdooSearchQuery query;

    // query.where("name") != QString("tintin");
    query.limit(10);
    query.fields(QOdooProduct().propertyNames());
    setQuery(query);
}

void ProductCollection::filter(const QVariantMap &params)
{
    QOdooSearchQuery query;

    query.limit(limit());
    decorateQuery(query, params);
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

void ProductTemplateCollection::filter(const QVariantMap &params)
{
    QOdooSearchQuery query;

    query.limit(limit());
    decorateQuery(query, params);
    setQuery(query);
}
