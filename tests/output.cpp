#include "output.h"

#include <QByteArray>

namespace tests {

Output::Output(QObject *parent) :
    QObject(parent), outStream(stdout)
{
}

void Output::out(const qpjsua::PjError &anError, const QString &aMessage)
{
    QString message = aMessage;
    if(anError.getStatus() != PJ_SUCCESS) {
        message = QString("%1 Code: %2").arg(anError.getMessage()).arg(anError.getStatus());
    }
    outStream << ">>> Output: " << message << "\n";
    outStream.flush();
}

void Output::onLog(int level, QString message)
{
    outStream << ">>> Log >>> Level " << level << " >>> " << message << "\n";
    outStream.flush();
}

void Output::onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo)
{
    outStream << ">>> onIncomingCall <<< \n";
    accountInfoOut(anAccountInfo);
    callInfoOut(aCallInfo);
}

void Output::onCallState(qpjsua::CallInfo aCallInfo)
{
    outStream << ">>> onCallState <<< \n";
    callInfoOut(aCallInfo);
}

void Output::onCallMediaState(qpjsua::CallInfo aCallInfo)
{
    outStream << ">>> onCallMediaState <<< \n";
    callInfoOut(aCallInfo);
}

void Output::onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew)
{
    Q_UNUSED(renew);
    outStream << ">>> onRegStarted <<< \n";
    accountInfoOut(anAccountInfo);
}

void Output::callInfoOut(qpjsua::CallInfo aCallInfo)
{
    outStream << ">>> Call-ID: " << aCallInfo.getCallId() << "\n";
    outStream << ">>> Local Info: " << aCallInfo.getLocalInfo() << "\n";
    outStream << ">>> Local contact: " << aCallInfo.getLocalContact() << "\n";
    outStream << ">>> Remote Info: " << aCallInfo.getRemoteInfo() << "\n";
    outStream << ">>> Remote contact: " << aCallInfo.getRemoteContact() << "\n";
    outStream << ">>> State Text: " << aCallInfo.getStateText() << "\n";
    outStream << ">>> Media status: " << aCallInfo.getMediaStatus() << "\n";
    outStream << ">>> State: " << aCallInfo.getInviteState() << "\n";
    outStream.flush();
}

void Output::accountInfoOut(qpjsua::AccountInfo anAccountInfo)
{
    if(anAccountInfo.hasRegistartion()) {
        outStream << ">>> Client is registered\n";
    } else {
        outStream << ">>> Client is not registered\n";
    }

    outStream << ">>> Status Text: " << anAccountInfo.getStatusText() << "\n";
    outStream << ">>> Status: " << anAccountInfo.getStatus() << "\n";
    outStream << ">>> Reg last error: " << anAccountInfo.getLastError() << "\n";
    outStream.flush();
}

} // namespace tests
