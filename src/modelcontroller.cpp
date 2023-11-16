#include "modelcontroller.h"

extern OdooService *odooService;

ModelControllerInterface::ModelControllerInterface(QObject *parent)
    : QObject{parent}
{
  connect(odooService, &OdooService::faultReceived, this, [this](QXMLRpcFault fault)
  {
    emit errorReceived(fault.message());
  });
}

OdooService &ModelControllerInterface::service()
{
    return *odooService;
}

void ModelControllerInterface::save()
{
    QXMLRpcClient::debugMode = true;
    if (model) {
        model->save(*odooService, [this]() {
            QXMLRpcClient::debugMode = false;
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
