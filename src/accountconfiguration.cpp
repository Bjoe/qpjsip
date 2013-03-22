#include "accountconfiguration.h"

#include <QByteArray>

namespace qpjsua {

AccountConfiguration::AccountConfiguration()
    : sipUrl(""), registrationUri(""),
      proxys(), credentials()
{
}

AccountConfiguration AccountConfiguration::build()
{
    return AccountConfiguration();
}

AccountConfiguration &AccountConfiguration::withSipUrl(const QString &aSipUrl)
{
    sipUrl = aSipUrl.toLatin1();
    return *this;
}

AccountConfiguration &AccountConfiguration::withRegistrationUri(const QString &anUri)
{
    registrationUri = anUri.toLatin1();
    return *this;
}

AccountConfiguration &AccountConfiguration::addProxy(const QString &aProxyUrl)
{
    proxys.append(aProxyUrl.toLatin1());
    return *this;
}

AccountConfiguration &AccountConfiguration::addCredential(const AccountCredential aCredential)
{
    credentials.append(aCredential);
    return *this;
}

pj_status_t AccountConfiguration::create()
{
    pjsua_acc_config accountConfig;
    pjsua_acc_config_default(&accountConfig);

    accountConfig.id = pj_str(sipUrl.data());
    accountConfig.reg_uri = pj_str(registrationUri.data());

    accountConfig.proxy_cnt = proxys.size();
    for(int i = 0; i < proxys.size(); ++i) {
        QByteArray proxy = proxys.at(i);
        accountConfig.proxy[i] = pj_str(proxy.data());
    }

    accountConfig.cred_count = credentials.size();
    for(int i = 0; i < credentials.size(); ++i) {
        AccountCredential credential = credentials.at(i);
        accountConfig.cred_info[i].realm = pj_str(credential.realm.data());
        accountConfig.cred_info[i].scheme = pj_str(credential.scheme.data());
        accountConfig.cred_info[i].username = pj_str(credential.username.data());
        accountConfig.cred_info[i].data_type = credential.type;
        accountConfig.cred_info[i].data = pj_str(credential.password.data());
    }
    pjsua_acc_id account_id;

    return pjsua_acc_add(&accountConfig, PJ_TRUE, &account_id);
}



AccountCredential::AccountCredential()
    : realm(""), scheme(""), username(""), password(""), type(0)
{}

AccountCredential AccountCredential::build()
{
    return AccountCredential();
}

AccountCredential &AccountCredential::withRealm(const QString &aRealm)
{
    realm = aRealm.toLatin1();
    return *this;
}

AccountCredential &AccountCredential::withScheme(const QString &aScheme)
{
    scheme = aScheme.toLatin1();
    return *this;
}

AccountCredential &AccountCredential::withUsername(const QString &anUsername)
{
    username = anUsername.toLatin1();
    return *this;
}

AccountCredential &AccountCredential::withPasswordType(int aType)
{
    type = aType;
    return *this;
}

AccountCredential &AccountCredential::withPassword(const QString &aPassword)
{
    password = aPassword.toLatin1();
    return *this;
}

} // namespace qpjsua
