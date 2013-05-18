#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "testconfig.h"

#include <QString>
#include <pjsua-lib/pjsua.h>

#include "accountconfiguration.h"

namespace tests {

class AccountConfigurationTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testBuild();
};

void AccountConfigurationTest::testBuild()
{
    qpjsua::AccountCredential *credential = qpjsua::AccountCredential::build()
            .withScheme("Digest")
            .withRealm("*")
            .withUsername("barfoo")
            .withPasswordType(PJSIP_CRED_DATA_PLAIN_PASSWD)
            .withPassword("foobar")
            .create();
    qpjsua::AccountConfiguration *configuration = qpjsua::AccountConfiguration::build()
            .withAllowContactRewrite(true)
            .withSipUrl("sip:fooo@bar.de")
            .withRegistrationUri("sip:bar.de")
            .withRtpPort(2000)
            .addProxy("sip:proxy.example.com")
            .addCredential(credential)
            .create();
    delete configuration;
    delete credential;
}

}

QTEST_MAIN(tests::AccountConfigurationTest)
#include "moc_accountconfigurationtest.cpp"
