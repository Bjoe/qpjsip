
#include <QtTest/QtTest>

#include "testcoverageobject.h"

#include "testconfig.h"

namespace tests {
  
class ExampleTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testExample();
};

void ExampleTest::initTestCase()
{
}

void ExampleTest::testExample()
{
    QVERIFY(true);
}

}

QTEST_MAIN(tests::ExampleTest)
#include "moc_exampletest.cpp"
