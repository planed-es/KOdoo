#include "productcontroller.h"
#include <odoo-qt/QOdooProductTemplate.h>

ProductController::ProductController(QObject *parent)
    : ModelControllerInterface{parent}
{
}

void ProductController::create()
{
    if (productTemplate)
        ModelControllerInterface::create<QOdooProductTemplate>();
    else
        ModelControllerInterface::create<QOdooProduct>();
}

void ProductController::load(int id)
{
    if (productTemplate)
        ModelControllerInterface::load<QOdooProductTemplate>(id);
    else
        ModelControllerInterface::load<QOdooProduct>(id);
}
