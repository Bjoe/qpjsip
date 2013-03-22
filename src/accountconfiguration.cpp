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
