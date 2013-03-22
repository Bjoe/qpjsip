#ifndef QPJSUA_ACCOUNTCONFIGURATION_H
#define QPJSUA_ACCOUNTCONFIGURATION_H

#include <QString>
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
    pj_status_t create() const;

    ~AccountConfiguration();
private:
    pjsua_acc_config configuration;

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

    ~AccountCredential();
private:
    pjsip_cred_info credential;

    AccountCredential();

    friend pjsip_cred_info getCredential(AccountCredential anAccountCredential);
};


} // namespace qpjsua

#endif // QPJSUA_ACCOUNTCONFIGURATION_H
