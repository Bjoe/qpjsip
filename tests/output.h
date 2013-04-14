#ifndef TESTS_OUTPUT_H
#define TESTS_OUTPUT_H

#include <QObject>
#include <QString>

#include "pjsua-lib/pjsua.h"

#include "pjerror.h"

#include "callinfo.h"
#include "accountinfo.h"

namespace tests {

class Output : public QObject
{
    Q_OBJECT
public:
    explicit Output(QObject *parent = 0);
    void out(const qpjsua::PjError &anError, const QString &aMessage);

public slots:
    void onLog(int level, QString message);
    void onIncomingCall(qpjsua::AccountInfo anAccountInfo, qpjsua::CallInfo aCallInfo);
    void onCallState(qpjsua::CallInfo aCallInfo);
    void onCallMediaState(qpjsua::CallInfo aCallInfo);
    void onRegStarted(qpjsua::AccountInfo anAccountInfo, bool renew);

private:
    void callInfoOut(qpjsua::CallInfo aCallInfo);
    void accountInfoOut(qpjsua::AccountInfo anAccountInfo);
};

} // namespace tests

#endif // TESTS_OUTPUT_H
