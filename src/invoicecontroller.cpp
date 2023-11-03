#include "invoicecontroller.h"
#include <QDebug>

using namespace std;

InvoiceController::InvoiceController(QObject *parent)
    : ModelControllerInterface{parent}
{
    connect(this, &ModelControllerInterface::modelChanged, this, &InvoiceController::onModelChanged);
    connect(this, &ModelControllerInterface::modelChanged, this, &InvoiceController::linesChanged);
    connect(this, &ModelControllerInterface::modelChanged, this, &InvoiceController::moveTypeChanged);
    lineColumnList << new QOdooTableColumn("accountId", "Account", bind(&InvoiceController::accountColumn, this, placeholders::_1), this);
    lineColumnList << new QOdooTableColumn("name", "Name", this);
    lineColumnList << new QOdooTableColumn("quantity", "Quantity", this);
    lineColumnList << new QOdooTableColumn("priceUnit", "Price Unit", this);
    lineColumnList << new QOdooTableColumn("taxIds", "Taxes", this);
}

void InvoiceController::create()
{
    QOdooInvoice *invoice = new QOdooInvoice(this);

    invoice->setMoveType(moveType);
    model = invoice;
    emit modelChanged();
}

void InvoiceController::addLine()
{
    QOdooInvoice *invoice = qobject_cast<QOdooInvoice *>(model);

    if (invoice) {
        invoice->lineAt(invoice->lineCount());
        emit linesChanged();
    }
}

void InvoiceController::removeLine(int index)
{
    QOdooInvoice *invoice = qobject_cast<QOdooInvoice *>(model);

    if (invoice) {
        invoice->deleteLineAt(index);
        emit linesChanged();
    }
}

void InvoiceController::load(int id)
{
    ModelControllerInterface::load<QOdooInvoice>(id, [this](QOdooInvoice *result) {
        moveType = result->moveType();
        emit moveTypeChanged();
    });
}

void InvoiceController::onModelChanged()
{
    QOdooInvoice *invoice = qobject_cast<QOdooInvoice *>(model);

    connect(invoice, &QOdooInvoice::partnerIdChanged, this, &InvoiceController::refreshPartner);
    refreshPartner();
}

void InvoiceController::refreshPartner()
{
    QOdooInvoice *invoice = qobject_cast<QOdooInvoice *>(model);

    fetchPartner(invoice->partnerId());
}

void InvoiceController::fetchPartner(QOdooModel::IdType id)
{
    if (id == 0)
        return;
    service().fetch<QOdooPartner>(id, [this](QOdooPartner *result) {
        if (result) {
            partner = result;
            partner->setParent(this);
            emit partnerChanged();
        }
    });
}

void InvoiceController::fetchAccount(QOdooModel::IdType id)
{
    if (id == 0)
        return;
    service().fetch<QOdooAccount>(id, [this, id](QOdooAccount *result) {
        qDebug() << "Finished fetching account" << id << result;
        if (result) {
            result->setParent(this);
            accounts.insert(id, result);
            emit lineColumnList.at(0)->propertyChanged();
        }
    });
}

QVariant InvoiceController::accountColumn(const QOdooModel *model)
{
    const QOdooInvoiceLine *account = qobject_cast<const QOdooInvoiceLine *>(model);
    if (model) {
        auto it = accounts.find(account->accountId());

        if (it != accounts.end())
            return it.value()->name();
        fetchAccount(account->accountId());
        return QString("...");
    }
    return QString("N/A");
}

void InvoiceController::lineChanged(const QOdooInvoiceLine *)
{
    for (auto *column : lineColumnList)
        emit column->propertyChanged();
}

int countInvoiceLines(QQmlListProperty<QOdooInvoiceLine> *property)
{
    auto *invoice = reinterpret_cast<QOdooInvoice *>(property->data);

    return invoice ? invoice->lineCount() : 0;
}

QOdooInvoiceLine *atInvoiceLines(QQmlListProperty<QOdooInvoiceLine> *property, int at)
{
    auto *invoice = reinterpret_cast<QOdooInvoice *>(property->data);

    return invoice ? invoice->lineAt(at) : nullptr;
}

QQmlListProperty<QOdooInvoiceLine> InvoiceController::lines()
{
    return QQmlListProperty<QOdooInvoiceLine>(this, model, &countInvoiceLines, &atInvoiceLines);
}

QQmlListProperty<QOdooTableColumn> InvoiceController::lineColumns()
{
    return QQmlListProperty<QOdooTableColumn>(this, &lineColumnList);
}
