#include "modelcontroller.h"

extern OdooService *odooService;

ModelControllerInterface::ModelControllerInterface(QObject *parent)
    : QObject{parent}
{
}

OdooService &ModelControllerInterface::service()
{
    return *odooService;
}

void ModelControllerInterface::save()
{
    if (model) {
        model->save(*odooService, [this]() {
            qDebug() << "Model was saved" << model->id();
            emit modelSaved();
        });
    }
}

void ModelControllerInterface::requestPropertyRefresh()
{
    if (model) {
        model->requestPropertyRefresh();
        emit modelChanged();
    }
}
