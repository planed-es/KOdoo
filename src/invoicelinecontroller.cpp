#include "invoicelinecontroller.h"

InvoiceLineController::InvoiceLineController(QObject *parent)
    : ModelControllerInterface{parent}
{
    connect(this, &InvoiceLineController::modelChanged, this, &InvoiceLineController::onModelChanged);
}

void InvoiceLineController::create()
{
    QOdooInvoiceLine *line = new QOdooInvoiceLine(this);

    model = line;
    emit modelChanged();
}

void InvoiceLineController::load(int id)
{
    assert(invoice != nullptr);
    model = invoice->lineAt(id - 1);
    emit modelChanged();
}

void InvoiceLineController::onModelChanged()
{
    QOdooInvoiceLine *line = qobject_cast<QOdooInvoiceLine *>(model);

    connect(line, &QOdooInvoiceLine::productIdChanged, this, &InvoiceLineController::refreshProduct);
    connect(line, &QOdooInvoiceLine::accountIdChanged, this, &InvoiceLineController::refreshAccount);
    refreshProduct();
    refreshAccount();
}

void InvoiceLineController::refreshProduct()
{
    QOdooInvoiceLine *line = qobject_cast<QOdooInvoiceLine *>(model);

    fetchProduct(line->productId());
}

void InvoiceLineController::fetchProduct(QOdooModel::IdType id)
{
    if (id == 0)
        return;
    service().fetch<QOdooProduct>(id, [this](QOdooProduct *result) {
        if (result) {
            product = result;
            product->setParent(this);
            emit productChanged();
        }
    });
}

void InvoiceLineController::refreshAccount()
{
    QOdooInvoiceLine *line = qobject_cast<QOdooInvoiceLine *>(model);

    fetchAccount(line->accountId());
}

void InvoiceLineController::fetchAccount(QOdooModel::IdType id)
{
    if (id == 0)
        return;
    service().fetch<QOdooAccount>(id, [this](QOdooAccount *result) {
        if (result) {
            account = result;
            account->setParent(this);
            emit accountChanged();
        }
    });
}
