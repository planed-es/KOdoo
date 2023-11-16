#ifndef INVOICELINECONTROLLER_H
#define INVOICELINECONTROLLER_H

#include "modelcontroller.h"
#include <QtQml/qqml.h>
#include <odoo-qt/QOdooAccount.h>
#include <odoo-qt/QOdooInvoice.h>
#include <odoo-qt/QOdooInvoiceLine.h>
#include <odoo-qt/QOdooProduct.h>

class InvoiceLineController : public ModelControllerInterface
{
    Q_OBJECT
    QML_NAMED_ELEMENT(InvoiceLineController)
    Q_PROPERTY(QOdooModel *model MEMBER model NOTIFY modelChanged)
    Q_PROPERTY(QOdooInvoice *invoice MEMBER invoice NOTIFY invoiceChanged)
    Q_PROPERTY(QOdooProduct *product MEMBER product NOTIFY productChanged)
    Q_PROPERTY(QOdooAccount *account MEMBER account NOTIFY accountChanged)
public:
    explicit InvoiceLineController(QObject *parent = nullptr);

    Q_INVOKABLE void create();
    Q_INVOKABLE void load(int id);
    Q_INVOKABLE void save();
    Q_INVOKABLE void fetchProduct(QOdooModel::IdType);
    Q_INVOKABLE void fetchAccount(QOdooModel::IdType);

signals:
    void modelChanged();
    void invoiceChanged();
    void productChanged();
    void accountChanged();

private slots:
    void onModelChanged();
    void refreshProduct();
    void refreshAccount();

private:
    QOdooInvoice *invoice = nullptr;
    QOdooProduct *product = nullptr;
    QOdooAccount *account = nullptr;
};

#endif // INVOICELINECONTROLLER_H
