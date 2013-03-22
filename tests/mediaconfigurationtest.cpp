
#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "testconfig.h"

#include <QString>
#include <pjsua-lib/pjsua.h>

#include "mediaconfiguration.h"

namespace tests {

class MediaConfigurationTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testBuild();
};

void MediaConfigurationTest::testBuild()
{
    qpjsua::MediaConfiguration mediaConfiguration = qpjsua::MediaConfiguration::build();
    pjsua_media_config configuration = mediaConfiguration.getPjsuaMediaConfig();
    uint count = 1;
    QCOMPARE(configuration.thread_cnt, count);
}

}

QTEST_MAIN(tests::MediaConfigurationTest)
#include "moc_mediaconfigurationtest.cxx"
