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
    std::cout << msg.constData() << std::endl;
}

void Output::onLog(int level, QString message)
{
    std::cout << "Level " << level << " " << message.toLatin1().constData() << std::endl;
}

void Output::onIncomingCall(pjsua_acc_id accountId, pjsua_call_id callId)
{
    accountInfoOut(accountId);
    callInfoOut(callId);
}

void Output::onCallState(pjsua_call_id callId)
{
    callInfoOut(callId);}

void Output::onCallMediaState(pjsua_call_id callId)
{
    callInfoOut(callId);
}

void Output::onRegStarted(pjsua_acc_id accountId, bool renew)
{
    Q_UNUSED(renew);
    accountInfoOut(accountId);
}

void Output::callInfoOut(pjsua_call_id callId)
{
    pjsua_call_info callInfo;
    pjsua_call_get_info(callId, &callInfo);

    std::cout << "Local Info: " << callInfo.local_info.ptr << std::endl;
    std::cout << "Local contact: " << callInfo.local_contact.ptr << std::endl;
    std::cout << "Remote Info: " << callInfo.remote_info.ptr << std::endl;
    std::cout << "Remote contact: " << callInfo.remote_contact.ptr << std::endl;
    std::cout << "Media status: " << callInfo.media_status << std::endl;
    std::cout << "State: " << callInfo.state << std::endl;
    std::cout << "State Text: " << callInfo.state_text.ptr << std::endl;
}

void Output::accountInfoOut(pjsua_acc_id accountId)
{
    pjsua_acc_info accountInfo;
    pjsua_acc_get_info(accountId, &accountInfo);

    if(accountInfo.has_registration == PJ_TRUE) {
        std::cout << "Client is registered";
    } else {
        std::cout << "Client is not registered";
    }
    std::cout << "Status: " << accountInfo.status << std::endl;
    std::cout << "Status Text: " << accountInfo.status_text.ptr << std::endl;
    std::cout << "Reg last error: " << accountInfo.reg_last_err << std::endl;
}

} // namespace tests
