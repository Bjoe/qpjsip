
#include <QtTest/QtTest>
#include "testconfig.h"

#include <QString>
#include <pjsua-lib/pjsua.h>

#include "mediaconfiguration.h"

namespace tests {

class MediaConfigurationTest : public QObject
{
    Q_OBJECT

private slots:
    void testBuild();
};

void MediaConfigurationTest::testBuild()
{
    qpjsua::MediaConfiguration mediaConfiguration = qpjsua::MediaConfiguration::build();
}

}

QTEST_MAIN(tests::MediaConfigurationTest)
#include "moc_mediaconfigurationtest.cpp"
