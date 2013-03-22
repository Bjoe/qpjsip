#include "accountconfiguration.h"

#include <QByteArray>

namespace qpjsua {

char *convert(const QString &aString)
{
    QByteArray bytes = aString.toLatin1();
    char *config = bytes.data();
    int sleng = strlen(config)+1;
    char *ret = new char[sleng];
    memcpy(ret, config, sleng);
    return ret;
}

pjsip_cred_info getCredential(AccountCredential anAccountCredential)
{
    return anAccountCredential.credential;
}

AccountConfiguration::AccountConfiguration() : configuration()
{
    pjsua_acc_config_default(&configuration);
}

AccountConfiguration::~AccountConfiguration()
{
    //free(accountConfiguration);
}

AccountConfiguration AccountConfiguration::build()
{
    return AccountConfiguration();
}

AccountConfiguration &AccountConfiguration::withSipUrl(const QString &aSipUrl)
{
    configuration.id = pj_str(convert(aSipUrl));
    return *this;
}

AccountConfiguration &AccountConfiguration::withRegistrationUri(const QString &anUri)
{
    configuration.reg_uri = pj_str(convert(anUri));
    return *this;
}

AccountConfiguration &AccountConfiguration::addProxy(const QString &aProxyUrl)
{
    int count = configuration.proxy_cnt++;
    configuration.proxy[count] = pj_str(convert(aProxyUrl));
    return *this;
}

AccountConfiguration &AccountConfiguration::addCredential(const AccountCredential aCredential)
{
    int count = configuration.cred_count++;
    configuration.cred_info[count] = getCredential(aCredential);
    return *this;
}

pj_status_t AccountConfiguration::create() const
{
    pjsua_acc_id accountId; // TODO
    return pjsua_acc_add(&configuration, PJ_TRUE, &accountId);
}



AccountCredential::AccountCredential() : credential()
{}

AccountCredential::~AccountCredential()
{
    //delete credential;
}

AccountCredential AccountCredential::build()
{
    return AccountCredential();
}

AccountCredential &AccountCredential::withRealm(const QString &aRealm)
{
    credential.realm = pj_str(convert(aRealm));
    return *this;
}

AccountCredential &AccountCredential::withScheme(const QString &aScheme)
{
    credential.scheme = pj_str(convert(aScheme));
    return *this;
}

AccountCredential &AccountCredential::withUsername(const QString &anUsername)
{
    credential.username = pj_str(convert(anUsername));
    return *this;
}

AccountCredential &AccountCredential::withPasswordType(int aType)
{
    credential.data_type = aType;
    return *this;
}

AccountCredential &AccountCredential::withPassword(const QString &aPassword)
{
    credential.data = pj_str(convert(aPassword));
    return *this;
}

} // namespace qpjsua
