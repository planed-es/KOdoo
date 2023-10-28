#include "contactcontroller.h"

ContactController::ContactController(QObject *parent)
    : ModelControllerInterface{parent}
{
}

void ContactController::create()
{
    ModelControllerInterface::create<QOdooPartner>();
}

void ContactController::load(int id)
{
    ModelControllerInterface::load<QOdooPartner>(id);
}
