

#include <QtTest/QtTest>
#include "testconfig.h"

#include <QString>
#include <pjsua-lib/pjsua.h>

#include "transportconfiguration.h"

namespace tests {

class TransportConfigurationTest : public QObject
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
#include "transportconfigurationtest.moc"
