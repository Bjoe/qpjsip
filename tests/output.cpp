#include "output.h"

#include <QByteArray>
#include <QTextStream>
#include <iostream>

namespace tests {

Output::Output(QObject *parent) :
    QObject(parent)
{
}

void Output::out(const qpjsua::PjError &anError, const QString &aMessage)
{
    QByteArray msg = aMessage.toLatin1();
    if(anError.getStatus() != PJ_SUCCESS) {
        msg = QString("%1 Code: %2").arg(anError.getMessage()).arg(anError.getStatus()).toLatin1();
    }
    std::cout << ">>> Output: " << msg.constData() << std::endl;
}

void Output::onLog(int level, QString message)
{
    std::cout << ">>> Log >>> Level " << level << " >>> " << message.toLatin1().constData() << std::endl;
}

void Output::onIncomingCall(pjsua_acc_id accountId, qpjsua::CallInfo aCallInfo)
{
    std::cout << ">>> onIncomingCall <<< " << std::endl;
    accountInfoOut(accountId);
    callInfoOut(aCallInfo);
}

void Output::onCallState(qpjsua::CallInfo aCallInfo)
{
    std::cout << ">>> onCallState <<< " << std::endl;
    callInfoOut(aCallInfo);
}

void Output::onCallMediaState(qpjsua::CallInfo aCallInfo)
{
    std::cout << ">>> onCallMediaState <<< " << std::endl;
    callInfoOut(aCallInfo);
}

void Output::onRegStarted(pjsua_acc_id accountId, bool renew)
{
    Q_UNUSED(renew);
    std::cout << ">>> onRegStarted <<< " << std::endl;
    accountInfoOut(accountId);
}

void Output::callInfoOut(qpjsua::CallInfo aCallInfo)
{
    QTextStream out(stdout);
    out << ">>> Call-ID: " << aCallInfo.getCallId() << "\n";
    out << ">>> Local Info: " << aCallInfo.getLocalInfo() << "\n";
    out << ">>> Local contact: " << aCallInfo.getLocalContact() << "\n";
    out << ">>> Remote Info: " << aCallInfo.getRemoteInfo() << "\n";
    out << ">>> Remote contact: " << aCallInfo.getRemoteContact() << "\n";
    out << ">>> State Text: " << aCallInfo.getStateText() << "\n";
    out << ">>> Media status: " << aCallInfo.getMediaStatus() << "\n";
    out << ">>> State: " << aCallInfo.getInviteState() << "\n";
}

void Output::accountInfoOut(pjsua_acc_id accountId)
{
    pjsua_acc_info accountInfo;
    pjsua_acc_get_info(accountId, &accountInfo);

    if(accountInfo.has_registration == PJ_TRUE) {
        std::cout << ">>> Client is registered" << std::endl;
    } else {
        std::cout << ">>> Client is not registered" << std::endl;
    }

    const char *statusText = pj_strbuf(&accountInfo.status_text);
    if(statusText) {
        std::cout << ">>> Status Text: " << statusText << std::endl;
    }

    std::cout << ">>> Status: " << accountInfo.status << std::endl;
    std::cout << ">>> Reg last error: " << accountInfo.reg_last_err << std::endl;
}

} // namespace tests
