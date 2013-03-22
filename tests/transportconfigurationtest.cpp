

#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "testconfig.h"

#include <QString>
#include <pjsua-lib/pjsua.h>

#include "transportconfiguration.h"

namespace tests {

class TransportConfigurationTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testBuild();
};

void TransportConfigurationTest::testBuild()
{
    qpjsua::TransportConfiguration::build()
            .withPort(5060);
}

}

QTEST_MAIN(tests::TransportConfigurationTest)
#include "moc_transportconfigurationtest.cxx"
