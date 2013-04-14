#ifndef TESTS_OUTPUT_H
#define TESTS_OUTPUT_H

#include <QObject>
#include <QString>

#include "pjsua-lib/pjsua.h"

#include "pjerror.h"

#include "callinfo.h"

namespace tests {

class Output : public QObject
{
    Q_OBJECT
public:
    explicit Output(QObject *parent = 0);
    void out(const qpjsua::PjError &anError, const QString &aMessage);

public slots:
    void onLog(int level, QString message);
    void onIncomingCall(pjsua_acc_id accountId, qpjsua::CallInfo aCallInfo);
    void onCallState(qpjsua::CallInfo aCallInfo);
    void onCallMediaState(qpjsua::CallInfo aCallInfo);
    void onRegStarted(pjsua_acc_id accountId, bool renew);

private:
    void callInfoOut(qpjsua::CallInfo aCallInfo);
    void accountInfoOut(pjsua_acc_id accountId);
};

} // namespace tests

#endif // TESTS_OUTPUT_H
