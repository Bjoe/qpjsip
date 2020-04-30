
#include <QtTest/QtTest>
#include "testconfig.h"

#include <QString>
#include <pjsua-lib/pjsua.h>

#include "loggingconfiguration.h"

namespace tests {

class LoggingConfigurationTest : public QObject
{
    Q_OBJECT

private slots:
    void testBuild();
};

void LoggingConfigurationTest::testBuild()
{
    qpjsua::LoggingConfiguration loggingConfiguration = qpjsua::LoggingConfiguration::build()
            .withConsoleLevel(4);
}

}

QTEST_MAIN(tests::LoggingConfigurationTest)
#include "loggingconfigurationtest.moc"
