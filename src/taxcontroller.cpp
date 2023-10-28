#include "taxcontroller.h"

TaxController::TaxController(QObject *parent)
    : ModelControllerInterface{parent}
{
}

void TaxController::create()
{
    ModelControllerInterface::create<QOdooTax>();
}

void TaxController::load(int id)
{
    ModelControllerInterface::load<QOdooTax>(id);
}
