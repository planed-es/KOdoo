#ifndef ACCOUNTCONTROLLER_H
#define ACCOUNTCONTROLLER_H

#include "modelcontroller.h"
#include <QtQml/qqml.h>
#include <odoo-qt/QOdooAccount.h>

class AccountController : public ModelControllerInterface
{
    Q_OBJECT
    QML_NAMED_ELEMENT(AccountController)
public:
    explicit AccountController(QObject *parent = nullptr);

    Q_INVOKABLE void create();
    Q_INVOKABLE void load(int id);
};

#endif
