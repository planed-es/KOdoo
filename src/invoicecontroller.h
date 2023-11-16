#ifndef INVOICECONTROLLER_H
#define INVOICECONTROLLER_H

#include "modelcontroller.h"
#include <QQmlListProperty>
#include <QtQml/qqml.h>
#include <odoo-qt/QOdooAccount.h>
#include <odoo-qt/QOdooInvoice.h>
#include <odoo-qt/QOdooPartner.h>
#include <odoo-qt/QOdooTableModel.h>

class InvoiceController : public ModelControllerInterface
{
    Q_OBJECT
    QML_NAMED_ELEMENT(InvoiceController)
    Q_PROPERTY(QOdooInvoice::MoveType moveType MEMBER moveType NOTIFY moveTypeChanged)
    Q_PROPERTY(QQmlListProperty<QOdooInvoiceLine> lines READ lines NOTIFY linesChanged)
    Q_PROPERTY(QQmlListProperty<QOdooTableColumn> lineColumns READ lineColumns CONSTANT)
    Q_PROPERTY(QOdooPartner *partner MEMBER partner NOTIFY partnerChanged)
public:
    explicit InvoiceController(QObject *parent = nullptr);

    Q_INVOKABLE void create();
    Q_INVOKABLE void load(int id);
    Q_INVOKABLE void addLine();
    Q_INVOKABLE void removeLine(int);
    Q_INVOKABLE void fetchPartner(QOdooModel::IdType);
    Q_INVOKABLE void lineChanged(const QOdooInvoiceLine *);

signals:
    void moveTypeChanged();
    void linesChanged();
    void partnerChanged();

private slots:
    void onModelChanged();
    void refreshPartner();

private:
    QQmlListProperty<QOdooInvoiceLine> lines();
    QQmlListProperty<QOdooTableColumn> lineColumns();
    void fetchAccount(QOdooModel::IdType);
    QVariant accountColumn(const QOdooModel *);

    QOdooInvoice::MoveType moveType = QOdooInvoice::NoMoveType;
    QList<QOdooTableColumn *> lineColumnList;
    QHash<QOdooModel::IdType, QOdooAccount *> accounts;
    QOdooPartner *partner = nullptr;
};

#endif // INVOICECONTROLLER_H
