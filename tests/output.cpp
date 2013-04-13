#include "output.h"

#include <QByteArray>
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

void Output::onIncomingCall(pjsua_acc_id accountId, pjsua_call_id callId)
{
    std::cout << ">>> onIncomingCall <<< " << std::endl;
    accountInfoOut(accountId);
    callInfoOut(callId);
}

void Output::onCallState(pjsua_call_id callId)
{
    std::cout << ">>> onCallState <<< " << std::endl;
    callInfoOut(callId);
}

void Output::onCallMediaState(pjsua_call_id callId)
{
    std::cout << ">>> onCallMediaState <<< " << std::endl;
    callInfoOut(callId);
}

void Output::onRegStarted(pjsua_acc_id accountId, bool renew)
{
    Q_UNUSED(renew);
    std::cout << ">>> onRegStarted <<< " << std::endl;
    accountInfoOut(accountId);
}

void Output::callInfoOut(pjsua_call_id callId)
{
    pjsua_call_info callInfo;
    pjsua_call_get_info(callId, &callInfo);

    const char *localInfo = pj_strbuf(&callInfo.local_info);
    if(localInfo) {
        std::cout << ">>> Local Info: " << localInfo << std::endl;
    }

    const char *localContact = pj_strbuf(&callInfo.local_contact);
    if(localContact) {
        std::cout << ">>> Local contact: " << localContact << std::endl;
    }

    const char *remoteInfo = pj_strbuf(&callInfo.remote_info);
    if(remoteInfo) {
        std::cout << ">>> Remote Info: " << remoteInfo << std::endl;
    }

    const char *remoteContact = pj_strbuf(&callInfo.remote_contact);
    if(remoteContact) {
        std::cout << ">>> Remote contact: " << remoteContact << std::endl;
    }

    const char *stateText = pj_strbuf(&callInfo.state_text);
    if(stateText) {
        std::cout << ">>> State Text: " << stateText << std::endl;
    }

    std::cout << ">>> Media status: " << callInfo.media_status << std::endl;
    std::cout << ">>> State: " << callInfo.state << std::endl;
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
