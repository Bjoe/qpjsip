#ifndef QPJSUA_ENGINE_H
#define QPJSUA_ENGINE_H

#include <pjsua-lib/pjsua.h>

#include "loggingconfiguration.h"
#include "mediaconfiguration.h"
#include "transportconfiguration.h"
#include "accountconfiguration.h"
#include "pjerror.h"

namespace qpjsua {

class AccountConfiguration;
class MediaConfiguration;
class TransportConfiguration;

class Engine
{
public:
    ~Engine();

    void addAccount(AccountConfiguration &anAccountConfiguration);

    bool isValid() const;
    PjError lastError() const;

private:
    PjError error;
    pj_status_t status;
    bool checkStatus(const QString &aMessage, pj_status_t aStatus);

    static void on_call_state(pjsua_call_id call_id, pjsip_event *event);
    static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata);
    static void on_call_media_state(pjsua_call_id call_id);
    static void on_reg_started(pjsua_acc_id acc_id, pj_bool_t renew);
    static void on_transport_state(pjsip_transport *tp, pjsip_transport_state state, const pjsip_transport_state_info *info);

    Engine();

public:
    class Builder
    {
    public:
        static Builder create();
        Builder &withMediaConfiguration(const MediaConfiguration &aMediaConfiguration);
        Builder &withLoggingConfiguration(const LoggingConfiguration &aLoggingConfiguration);
        Builder &withTransportConfiguration(const TransportConfiguration &aTransportConfiguration);
        Engine build() const;

    private:
        MediaConfiguration mediaConfiguration;
        LoggingConfiguration loggingConfiguration;
        TransportConfiguration transportConfiguration;

        Builder();
    };
};

} // namespace qpjsua

#endif // QPJSUA_ENGINE_H
