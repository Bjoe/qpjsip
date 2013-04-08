
#include <QtTest/QtTest>

#include <pj/types.h>

#include "testcoverageobject.h"

#include "testconfig.h"

#include "pjerror.h"

namespace tests {

class PjErrorTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testError();
};

void PjErrorTest::testError()
{
    qpjsua::PjError error;

    QCOMPARE(error.getMessage(), QString(""));
    QCOMPARE(error.getStatus(), PJ_SUCCESS);

    error.setMessage("foo");
    error.setStatus(1);
    QCOMPARE(error.getMessage(), QString("foo"));
    QCOMPARE(error.getStatus(), 1);
}

}

QTEST_MAIN(tests::PjErrorTest)
#include "moc_pjerrortest.cpp"

