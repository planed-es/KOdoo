#ifndef PRODUCTCONTROLLER_H
#define PRODUCTCONTROLLER_H

#include "modelcontroller.h"
#include <QOdooProduct.h>
#include <QtQml/qqml.h>

class ProductController : public ModelControllerInterface
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ProductController)
    Q_PROPERTY(bool productTemplate MEMBER productTemplate NOTIFY productTemplateChanged)
public:
    explicit ProductController(QObject *parent = nullptr);

    Q_INVOKABLE void create();
    Q_INVOKABLE void load(int id);

signals:
    void productTemplateChanged();

private:
    bool productTemplate = false;
};

#endif // PRODUCTCONTROLLER_H
