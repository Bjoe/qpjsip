#include "accountinfo.h"

namespace qpjsua {

AccountInfo::AccountInfo() : accountInfo()
{
}

AccountInfo::AccountInfo(pjsua_acc_info anAccountInfo)
    : accountInfo(anAccountInfo)
{
}

pjsua_acc_id AccountInfo::getId() const
{
    return accountInfo.id;
}

bool AccountInfo::hasRegistartion() const
{
    return (accountInfo.has_registration == PJ_TRUE);
}

QString AccountInfo::getStatusText() const
{
    return pj_strbuf(&accountInfo.status_text);
}

pjsip_status_code AccountInfo::getStatus() const
{
    return accountInfo.status;
}

pj_status_t AccountInfo::getLastError() const
{
    return accountInfo.reg_last_err;
}

} // namespace qpjsua
