
#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "testconfig.h"

#include <pjsua-lib/pjsua.h>

#include "accountinfo.h"

namespace tests {

class AccountInfoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void test();
};

void AccountInfoTest::test()
{
    pjsua_acc_id accId = 1;
    pjsua_acc_info accInfo;

    accInfo.id = accId;
    char statusText[] = "status_text";
    accInfo.status_text = pj_str(statusText);
    accInfo.has_registration = PJ_TRUE;
    accInfo.status = PJSIP_SC_OK;
    accInfo.reg_last_err = 2;

    qpjsua::AccountInfo accountInfo(accInfo);

    QCOMPARE(accountInfo.getId(), 1);
    QCOMPARE(accountInfo.getStatusText(), QString("status_text"));
    pjsip_status_code status = PJSIP_SC_OK;
    QCOMPARE(accountInfo.getStatus(), status);
    QCOMPARE(accountInfo.getLastError(), 2);
    QVERIFY(accountInfo.hasRegistartion());
}

}

QTEST_MAIN(tests::AccountInfoTest)
#include "moc_accountinfotest.cpp"
