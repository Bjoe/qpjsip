
#include <QtTest/QtTest>
#include "testcoverageobject.h"
#include "testconfig.h"

#include <pjsua-lib/pjsua.h>

#include "callinfo.h"

namespace tests {

class CallInfoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void test();
};

void CallInfoTest::test()
{
    pjsua_call_id callId = 1;
    pjsua_call_info callInfo;
    callInfo.id = callId;
    char callIdStr[] = "call_id";
    callInfo.call_id = pj_str(callIdStr);
    char localInfo[] = "local_info";
    callInfo.local_info = pj_str(localInfo);
    char localContact[] = "local_contact";
    callInfo.local_contact = pj_str(localContact);
    char remoteInfo[] = "remote_info";
    callInfo.remote_info = pj_str(remoteInfo);
    char remoteContact[] = "remote_contact";
    callInfo.remote_contact = pj_str(remoteContact);
    char stateText[] = "state_text";
    callInfo.state_text = pj_str(stateText);

    pjsua_call_media_status mediaStatus = PJSUA_CALL_MEDIA_ACTIVE;
    callInfo.media_status = mediaStatus;

    pjsip_inv_state invState = PJSIP_INV_STATE_CALLING;
    callInfo.state = invState;

    qpjsua::CallInfo call(callInfo);

    QCOMPARE(call.getId(), 1);
    QCOMPARE(call.getCallId(), QString("call_id"));
    QCOMPARE(call.getLocalInfo(), QString("local_info"));
    QCOMPARE(call.getLocalContact(), QString("local_contact"));
    QCOMPARE(call.getRemoteInfo(), QString("remote_info"));
    QCOMPARE(call.getRemoteContact(), QString("remote_contact"));
    QCOMPARE(call.getStateText(), QString("state_text"));

    pjsua_call_media_status status = PJSUA_CALL_MEDIA_ACTIVE;
    QCOMPARE(call.getMediaStatus(), status);

    pjsip_inv_state state = PJSIP_INV_STATE_CALLING;
    QCOMPARE(call.getInviteState(), state);
}

}

QTEST_MAIN(tests::CallInfoTest)
#include "moc_callinfotest.cpp"


