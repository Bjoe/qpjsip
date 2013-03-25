#ifndef TESTS_OUTPUT_H
#define TESTS_OUTPUT_H

#include <QObject>
#include <QString>

#include "pjsua-lib/pjsua.h"

#include "pjerror.h"

namespace tests {

class Output : public QObject
{
    Q_OBJECT
public:
    explicit Output(QObject *parent = 0);
    void out(const qpjsua::PjError &anError, const QString &aMessage);

public slots:
    void onLog(int level, QString message);
    void onIncomingCall(pjsua_acc_id accountId, pjsua_call_id callId);
    void onCallState(pjsua_call_id callId);
    void onCallMediaState(pjsua_call_id callId);
    void onRegStarted(pjsua_acc_id accountId, bool renew);

private:
    void callInfoOut(pjsua_call_id callId);
    void accountInfoOut(pjsua_acc_id accountId);
};

} // namespace tests

#endif // TESTS_OUTPUT_H
