
#include <QtTest/QtTest>

#include <pj/types.h>

#include "testconfig.h"

#include "pjerror.h"

namespace tests {

class PjErrorTest : public QObject
{
    Q_OBJECT

private slots:
    void testError();
};

void PjErrorTest::testError()
{
    qpjsua::PjError error;

    QCOMPARE(error.getMessage(), QString(""));
    QCOMPARE(error.getStatus(), static_cast<pj_status_t>(PJ_SUCCESS));

    error.setMessage("foo");
    error.setStatus(1);
    QCOMPARE(error.getMessage(), QString("foo"));
    QCOMPARE(error.getStatus(), 1);
}

}

QTEST_MAIN(tests::PjErrorTest)
#include "pjerrortest.moc"

