#include "callinfo.h"

namespace qpjsua {

CallInfo::CallInfo() : callId(), callInfo()
{}

CallInfo::CallInfo(pjsua_call_id aCallId, pjsua_call_info aCallInfo)
    : callId(aCallId), callInfo(aCallInfo)
{
}

pjsua_call_id CallInfo::getCallId() const
{
    return callId;
}

QString CallInfo::getLocalInfo() const
{
    return pj_strbuf(&callInfo.local_info);
}

QString CallInfo::getLocalContact() const
{
    return pj_strbuf(&callInfo.local_contact);
}

QString CallInfo::getRemoteInfo() const
{
    return pj_strbuf(&callInfo.remote_info);
}

QString CallInfo::getRemoteContact() const
{
    return pj_strbuf(&callInfo.remote_contact);
}

QString CallInfo::getStateText() const
{
    return pj_strbuf(&callInfo.state_text);
}

pjsua_call_media_status CallInfo::getMediaStatus() const
{
    return callInfo.media_status;
}

pjsip_inv_state CallInfo::getInviteState() const
{
    return callInfo.state;
}

} // namespace qpjsua
