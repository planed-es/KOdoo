#ifndef PRODUCTCOLLECTION_H
#define PRODUCTCOLLECTION_H

#include <QOdooCollection.h>
#include <QOdooProduct.h>
#include <QOdooProductTemplate.h>
#include <QQmlListProperty>
#include <QtQml/qqml.h>

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
