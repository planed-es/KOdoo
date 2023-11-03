#ifndef ACCOUNTCOLLECTION_H
#define ACCOUNTCOLLCETION_H

#include <QOdooAccount.h>
#include <QOdooCollection.h>
#include <QQmlListProperty>
#include <QtQml/qqml.h>

class AccountCollection : public QOdooCollection<QOdooAccount>
{
    Q_OBJECT
    QML_NAMED_ELEMENT(AccountCollection)
public:
    explicit AccountCollection(QObject *parent = nullptr);

    Q_INVOKABLE void filter(const QVariantMap &);
};

#endif // ACCOUNTCOLLECTION_H
