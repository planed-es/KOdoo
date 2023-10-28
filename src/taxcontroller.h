#ifndef TAXCONTROLLER_H
#define TAXCONTROLLER_H

#include "modelcontroller.h"
#include <QOdooTax.h>
#include <QtQml/qqml.h>

class TaxController : public ModelControllerInterface
{
    Q_OBJECT
    QML_NAMED_ELEMENT(TaxController)
public:
    explicit TaxController(QObject * = nullptr);

    Q_INVOKABLE void create();
    Q_INVOKABLE void load(int id);
};

#endif // TAXCONTROLLER_H
