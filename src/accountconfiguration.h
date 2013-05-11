#ifndef QPJSUA_ACCOUNTCONFIGURATION_H
#define QPJSUA_ACCOUNTCONFIGURATION_H

#include <QString>
#include <QByteArray>
#include <QList>

#include "engine.h"

namespace qpjsua {

class AccountCredential;

class AccountConfiguration
{
public:
    ~AccountConfiguration();

    class Builder
    {
    public:
        Builder &withSipUrl(const QString &aSipUrl);
        Builder &withRegistrationUri(const QString &anUri);
        Builder &withRtpPort(unsigned aPort);
        Builder &addProxy(const QString &aProxyUrl);
        Builder &addCredential(AccountCredential *aCredential);

        AccountConfiguration *create();

    private:
        Builder(AccountConfiguration *anInstance) : instance(anInstance) {}
        AccountConfiguration *instance;

        friend class AccountConfiguration;
    };

    static Builder build();

private:
    QByteArray sipUrl;
    QByteArray registrationUri;
    QList<QByteArray *> proxys;
    QList<AccountCredential *> credentials;
    unsigned port;

    AccountConfiguration();

    friend class Engine;
};

class AccountCredential
{
public:
    class Builder
    {
    public:
        Builder &withRealm(const QString &aRealm);
        Builder &withScheme(const QString &aScheme);
        Builder &withUsername(const QString &anUsername);
        Builder &withPasswordType(int aType);
        Builder &withPassword(const QString &aPassword);

        AccountCredential *create();

    private:
        Builder(AccountCredential *anInstance) : instance(anInstance) {}
        AccountCredential *instance;

        friend class AccountCredential;
    };

    static Builder build();

private:
    QByteArray realm;
    QByteArray scheme;
    QByteArray username;
    QByteArray password;
    int type;

    AccountCredential();

    friend class Engine;
};


} // namespace qpjsua

#endif // QPJSUA_ACCOUNTCONFIGURATION_H
