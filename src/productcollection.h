#ifndef PRODUCTCOLLECTION_H
#define PRODUCTCOLLECTION_H

#include <QQmlListProperty>
#include <QtQml/qqml.h>
#include <odoo-qt/QOdooCollection.h>
#include <odoo-qt/QOdooProduct.h>
#include <odoo-qt/QOdooProductTemplate.h>

class ProductCollection : public QOdooCollection<QOdooProduct>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ProductCollection)
public:
    explicit ProductCollection(QObject *parent = nullptr);

    Q_INVOKABLE void filter(const QVariantMap &);
};

class ProductTemplateCollection : public QOdooCollection<QOdooProductTemplate>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ProductTemplateCollection)
public:
    explicit ProductTemplateCollection(QObject *parent = nullptr);

    Q_INVOKABLE void filter(const QVariantMap &);
};

#endif // PRODUCTCOLLECTION_H
