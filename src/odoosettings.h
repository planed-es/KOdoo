#ifndef ODOOSETTINGS_H
#define ODOOSETTINGS_H

#include <QObject>

class OdooSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url MEMBER _url NOTIFY urlChanged)
    Q_PROPERTY(QString database MEMBER _database NOTIFY databaseChanged)
    Q_PROPERTY(QString username MEMBER _username NOTIFY usernameChanged)
    Q_PROPERTY(QString password MEMBER _password NOTIFY passwordChanged)
public:
    explicit OdooSettings(QObject *parent = nullptr);

    static OdooSettings &get()
    {
        return *_self;
    }

    const QString &url() const
    {
        return _url;
    }
    const QString &database() const
    {
        return _database;
    }
    const QString &username() const
    {
        return _username;
    }
    const QString &password() const
    {
        return _password;
    }

    Q_INVOKABLE void authenticate();

signals:
    void urlChanged();
    void databaseChanged();
    void usernameChanged();
    void passwordChanged();
    void authenticated();
    void authenticationFailure();

private:
    static OdooSettings *_self;
    QString _url, _database, _username, _password;
};

#endif // ODOOSETTINGS_H
