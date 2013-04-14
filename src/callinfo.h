#ifndef QPJSUA_CALLINFO_H
#define QPJSUA_CALLINFO_H

#include <pjsua-lib/pjsua.h>
#include <QString>

namespace qpjsua {

class CallInfo
{
public:
    CallInfo();
    CallInfo(pjsua_call_id aCallId, pjsua_call_info aCallInfo);

    pjsua_call_id getId() const;
    QString getCallId() const;
    QString getLocalInfo() const;
    QString getLocalContact() const;
    QString getRemoteInfo() const;
    QString getRemoteContact() const;
    QString getStateText() const;
    pjsua_call_media_status getMediaStatus() const;
    pjsip_inv_state getInviteState() const;

private:
    pjsua_call_id callId;
    pjsua_call_info callInfo;
};

} // namespace qpjsua

#endif // QPJSUA_CALLINFO_H
