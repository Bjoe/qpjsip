#include "accountconfiguration.h"

namespace qpjsua {

AccountConfiguration::AccountConfiguration()
    : sipUrl(""), registrationUri(""),
      proxys(), credentials()
{
}

AccountConfiguration::~AccountConfiguration()
{
    while(proxys.isEmpty() == false) {
        delete proxys.takeFirst();
    }
}

AccountConfiguration::Builder AccountConfiguration::build()
{
    return Builder(new AccountConfiguration());
}

AccountConfiguration::Builder &AccountConfiguration::Builder::withSipUrl(const QString &aSipUrl)
{
    instance->sipUrl = aSipUrl.toLatin1();
    return *this;
}

AccountConfiguration::Builder &AccountConfiguration::Builder::withRtpPort(unsigned aPort)
{
    instance->port = aPort;
    return *this;
}

AccountConfiguration::Builder &AccountConfiguration::Builder::withRegistrationUri(const QString &anUri)
{
    instance->registrationUri = anUri.toLatin1();
    return *this;
}

AccountConfiguration::Builder &AccountConfiguration::Builder::addProxy(const QString &aProxyUrl)
{
    instance->proxys.append(new QByteArray(aProxyUrl.toLatin1()));
    return *this;
}

AccountConfiguration::Builder &AccountConfiguration::Builder::addCredential(AccountCredential *aCredential)
{
    instance->credentials.append(aCredential);
    return *this;
}

AccountConfiguration *AccountConfiguration::Builder::create()
{
    return instance;
}


AccountCredential::AccountCredential()
    : realm(""), scheme(""), username(""), password(""), type(0)
{}

AccountCredential::Builder AccountCredential::build()
{
    return Builder(new AccountCredential());
}

AccountCredential::Builder &AccountCredential::Builder::withRealm(const QString &aRealm)
{
    instance->realm = aRealm.toLatin1();
    return *this;
}

AccountCredential::Builder &AccountCredential::Builder::withScheme(const QString &aScheme)
{
    instance->scheme = aScheme.toLatin1();
    return *this;
}

AccountCredential::Builder &AccountCredential::Builder::withUsername(const QString &anUsername)
{
    instance->username = anUsername.toLatin1();
    return *this;
}

AccountCredential::Builder &AccountCredential::Builder::withPasswordType(int aType)
{
    instance->type = aType;
    return *this;
}

AccountCredential::Builder &AccountCredential::Builder::withPassword(const QString &aPassword)
{
    instance->password = aPassword.toLatin1();
    return *this;
}

AccountCredential *AccountCredential::Builder::create()
{
    return instance;
}

} // namespace qpjsua
