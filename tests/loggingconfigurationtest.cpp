
#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "testconfig.h"

#include <QString>
#include <pjsua-lib/pjsua.h>

#include "loggingconfiguration.h"

namespace tests {

class LoggingConfigurationTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testBuild();
};

void LoggingConfigurationTest::testBuild()
{
    qpjsua::LoggingConfiguration loggingConfiguration = qpjsua::LoggingConfiguration::build()
            .withConsoleLevel(4);

    pjsua_logging_config configuration = loggingConfiguration.getPjsuaLoggingConfig();
    uint level = 4;
    QCOMPARE(configuration.console_level, level);
}

}

QTEST_MAIN(tests::LoggingConfigurationTest)
#include "moc_loggingconfigurationtest.cxx"
