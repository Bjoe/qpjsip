#ifndef QPJSUA_ACCOUNTINFO_H
#define QPJSUA_ACCOUNTINFO_H

#include <QString>
#include <pjsua-lib/pjsua.h>

namespace qpjsua {

class AccountInfo
{
public:
    AccountInfo();
    AccountInfo(pjsua_acc_info anAccountInfo);

    pjsua_acc_id getId() const;
    bool hasRegistartion() const;
    QString getStatusText() const;
    pjsip_status_code getStatus() const;
    pj_status_t getLastError() const;

private:
    pjsua_acc_info accountInfo;
};

} // namespace qpjsua

#endif // QPJSUA_ACCOUNTINFO_H
