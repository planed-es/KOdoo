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
};

class ProductTemplateCollection : public QOdooCollection<QOdooProductTemplate>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ProductTemplateCollection)
public:
    explicit ProductTemplateCollection(QObject *parent = nullptr);
};

#endif // PRODUCTCOLLECTION_H
