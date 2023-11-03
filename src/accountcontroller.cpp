#include "accountcontroller.h"

AccountController::AccountController(QObject *parent)
    : ModelControllerInterface{parent}
{
}

void AccountController::create()
{
    ModelControllerInterface::create<QOdooAccount>();
}

void AccountController::load(int id)
{
    ModelControllerInterface::load<QOdooAccount>(id);
}
