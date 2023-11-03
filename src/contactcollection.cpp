#include "contactcollection.h"

extern OdooService *odooService;

ContactCollection::ContactCollection(QObject *parent)
    : QOdooCollection<QOdooPartner>{*odooService, parent}
{
    QOdooSearchQuery query;

    query.limit(10);
    query.fields(QOdooPartner().propertyNames());
    setQuery(query);
}

void ContactCollection::filter(const QVariantMap &params)
{
    QOdooSearchQuery query;

    query.fields(QOdooPartner().propertyNames());
    query.limit(limit());
    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it.key() == "name")
            query.where("name").like(it.value().toString());
    }
    setQuery(query);
}
