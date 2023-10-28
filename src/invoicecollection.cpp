#include "invoicecollection.h"

extern OdooService *odooService;

InvoiceCollection::InvoiceCollection(QObject *parent)
    : QOdooCollection<QOdooInvoice>{*odooService, parent}
{
    updateQuery();
}

void InvoiceCollection::updateQuery()
{
    QOdooSearchQuery query;

    decorateQuery(query);
    setQuery(query);
}

void InvoiceCollection::decorateQuery(QOdooSearchQuery &query)
{
    query.fields(QOdooInvoice().propertyNames());
    query.limit(limit());
    if (moveType != QOdooInvoice::NoMoveType)
        query.where("move_type") == QOdooInvoice::valueFor(moveType);
}

void InvoiceCollection::filter(const QVariantMap &params)
{
    QOdooSearchQuery query;

    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it.key() == "name" || it.key() == "ref")
            query.where(it.key()).like(it.value().toString());
        else if (it.key() == "fromDate")
            query.where("date") >= it.value().toDate();
        else if (it.key() == "toDate")
            query.where("date") <= it.value().toDate();
    }
    decorateQuery(query);
    setQuery(query);
}
