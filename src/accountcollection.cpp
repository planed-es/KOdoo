#include "accountcollection.h"

extern OdooService *odooService;

AccountCollection::AccountCollection(QObject *parent)
    : QOdooCollection<QOdooAccount>{*odooService, parent}
{
    QOdooSearchQuery query;

    query.fields(QOdooAccount().propertyNames());
    setQuery(query);
}

void AccountCollection::filter(const QVariantMap &params)
{
    QOdooSearchQuery query;

    query.fields(QOdooAccount().propertyNames());
    query.limit(limit());
    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it.key() == "code")
            query.where("code").like(it.value().toString() + "%", QOdooSearchQuery::ExactMatch);
        else if (it.key() == "name")
            query.where("name").like(it.value().toString());
    }
    setQuery(query);
}
