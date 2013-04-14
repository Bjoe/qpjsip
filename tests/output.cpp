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

void Output::onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo)
{
    std::cout << ">>> onIncomingCall <<< " << std::endl;
    accountInfoOut(anAccountInfo);
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

void Output::onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew)
{
    Q_UNUSED(renew);
    std::cout << ">>> onRegStarted <<< " << std::endl;
    accountInfoOut(anAccountInfo);
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

void Output::accountInfoOut(qpjsua::AccountInfo anAccountInfo)
{
    QTextStream out(stdout);
    if(anAccountInfo.hasRegistartion()) {
        out << ">>> Client is registered\n";
    } else {
        out << ">>> Client is not registered\n";
    }

    out << ">>> Status Text: " << anAccountInfo.getStatusText() << "\n";
    out << ">>> Status: " << anAccountInfo.getStatus() << "\n";
    out << ">>> Reg last error: " << anAccountInfo.getLastError() << "\n";
}

} // namespace tests
