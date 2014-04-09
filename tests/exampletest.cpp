
#include <QtTest/QtTest>

#include "testconfig.h"

namespace examples {
  
class ExampleTest : public QObject
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

QTEST_MAIN(examples::ExampleTest)
#include "moc_exampletest.cpp"
