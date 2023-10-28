#ifndef INVOICECOLLECTION_H
#define INVOICECOLLECTION_H

#include <QOdooCollection.h>
#include <QOdooInvoice.h>
#include <QtQml/qqml.h>

class InvoiceCollection : public QOdooCollection<QOdooInvoice>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(InvoiceCollection)
    Q_PROPERTY(QOdooInvoice::MoveType moveType MEMBER moveType NOTIFY moveTypeChanged)
public:
    explicit InvoiceCollection(QObject *parent = nullptr);

    Q_INVOKABLE void filter(const QVariantMap &);

signals:
    void moveTypeChanged();

private slots:
    void updateQuery();

private:
    void decorateQuery(QOdooSearchQuery &);

    QOdooInvoice::MoveType moveType = QOdooInvoice::NoMoveType;
};

#endif
