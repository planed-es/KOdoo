#include "odoosettings.h"
#include <QOdoo.h>

extern OdooService *odooService;

OdooSettings *OdooSettings::_self = nullptr;

OdooSettings::OdooSettings(QObject *parent)
    : QObject{parent}
{
    _self = this;
}

void OdooSettings::authenticate()
{
    odooService = new OdooService(QUrl(_url));
    odooService->enableFaults(true);
    odooService->authenticate(_database, _username, _password, [this](bool success) {
        if (success)
            emit authenticated();
        else
            emit authenticationFailure();
    });
}
