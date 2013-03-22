#ifndef QPJSUA_ACCOUNTCONFIGURATION_H
#define QPJSUA_ACCOUNTCONFIGURATION_H

#include <QString>
#include <QByteArray>
#include <QList>

#include "pjsua.h"

namespace qpjsua {

class AccountCredential;

class AccountConfiguration
{
public:
    static AccountConfiguration build();
    AccountConfiguration &withSipUrl(const QString &aSipUrl);
    AccountConfiguration &withRegistrationUri(const QString &anUri);
    AccountConfiguration &addProxy(const QString &aProxyUrl);
    AccountConfiguration &addCredential(const AccountCredential aCredential);
    pj_status_t create();

private:
    QByteArray sipUrl;
    QByteArray registrationUri;
    QList<QByteArray> proxys;
    QList<AccountCredential> credentials;

    AccountConfiguration();
};

class AccountCredential
{
public:
    static AccountCredential build();
    AccountCredential &withRealm(const QString &aRealm);
    AccountCredential &withScheme(const QString &aScheme);
    AccountCredential &withUsername(const QString &anUsername);
    AccountCredential &withPasswordType(int aType);
    AccountCredential &withPassword(const QString &aPassword);

private:
    QByteArray realm;
    QByteArray scheme;
    QByteArray username;
    QByteArray password;
    int type;

    AccountCredential();

    friend class AccountConfiguration;
};


} // namespace qpjsua

#endif // QPJSUA_ACCOUNTCONFIGURATION_H
