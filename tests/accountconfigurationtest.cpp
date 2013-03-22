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
    qpjsua::AccountCredential credential = qpjsua::AccountCredential::build()
            .withScheme("Digest")
            .withRealm("*")
            .withUsername("barfoo")
            .withPasswordType(PJSIP_CRED_DATA_PLAIN_PASSWD)
            .withPassword("foobar");
    qpjsua::AccountConfiguration::build()
            .withSipUrl("sip:fooo@bar.de")
            .withRegistrationUri("sip:bar.de")
            .addProxy("sip:proxy.example.com")
            .addCredential(credential);
            //.create();
}

}

QTEST_MAIN(tests::AccountConfigurationTest)
#include "moc_accountconfigurationtest.cxx"
