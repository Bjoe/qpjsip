#include "callinfo.h"

namespace qpjsua {

CallInfo::CallInfo() : callInfo()
{}

CallInfo::CallInfo(pjsua_call_info aCallInfo)
    : callInfo(aCallInfo)
{
}

pjsua_call_id CallInfo::getId() const
{
    return callInfo.id;
}

QString CallInfo::getCallId() const
{
    return pj_strbuf(&callInfo.call_id);
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

pjsua_conf_port_id CallInfo::getConferenceSlot() const
{
    return callInfo.conf_slot;
}

} // namespace qpjsua
