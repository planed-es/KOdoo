#ifndef CONTACTCONTROLLER_H
#define CONTACTCONTROLLER_H

#include "modelcontroller.h"
#include <QtQml/qqml.h>
#include <odoo-qt/QOdooPartner.h>

class ContactController : public ModelControllerInterface
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ContactController)
public:
    explicit ContactController(QObject *parent = nullptr);

    Q_INVOKABLE void create();
    Q_INVOKABLE void load(int id);
};

#endif // CONTACTCONTROLLER_H
