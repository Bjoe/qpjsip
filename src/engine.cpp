#include "engine.h"

#include <QMetaType>
#include <QString>
#include <QByteArray>

namespace qpjsua {

static Engine *instance = 0;

Engine::Engine(QObject *parent) : QObject(parent), error(), status(PJ_SUCCESS)
{
}

Engine::~Engine()
{
    pjsua_call_hangup_all();
    pjsua_destroy();
    instance = 0;
}

Engine::Builder Engine::Builder::create()
{
    return Builder();
}

Engine::Builder::Builder()
    : mediaConfiguration(MediaConfiguration::build()),
      loggingConfiguration(LoggingConfiguration::build()),
      transportConfiguration(TransportConfiguration::build())
{}

Engine::Builder &Engine::Builder::withLoggingConfiguration(const LoggingConfiguration &aLoggingConfiguration)
{
    loggingConfiguration = aLoggingConfiguration;
}

Engine::Builder &Engine::Builder::withMediaConfiguration(const MediaConfiguration &aMediaConfiguration)
{
    mediaConfiguration = aMediaConfiguration;
}

Engine::Builder &Engine::Builder::withTransportConfiguration(const TransportConfiguration &aTransportConfiguration)
{
    transportConfiguration = aTransportConfiguration;
}

Engine *Engine::Builder::build(QObject *parent) const
{
    qRegisterMetaType<pjsua_acc_id>("pjsua_acc_id");
    qRegisterMetaType<pjsua_call_id>("pjsua_call_id");

    Engine *engine = new Engine(parent);
    instance = engine;

    if(engine->checkStatus("pjsua create", pjsua_create()) == false) {
        return engine;
    }

    pjsua_config config;
    pjsua_config_default(&config);

    config.cb.on_incoming_call = &on_incoming_call_wrapper;
    config.cb.on_call_state = &on_call_state_wrapper;
    config.cb.on_call_media_state = &on_call_media_state_wrapper;
    config.cb.on_reg_started = &on_reg_started_wrapper;
    config.cb.on_transport_state = &on_transport_state_wrapper;

    pjsua_logging_config loggingConfig;
    pjsua_logging_config_default(&loggingConfig);
    loggingConfig.decor = loggingConfig.decor & ~PJ_LOG_HAS_NEWLINE;
    loggingConfig.console_level = loggingConfiguration.getConsoleLevel();
    loggingConfig.cb = &logger_callback_wrapper;
    const QObject *receiver = loggingConfiguration.getReceiver();
    if(receiver) {
        receiver->connect(engine, SIGNAL(log(int,QString)), loggingConfiguration.getMember(), Qt::QueuedConnection);
    }
    pjsua_media_config mediaConfig;
    pjsua_media_config_default(&mediaConfig);

    if(engine->checkStatus("pjsua init", pjsua_init(&config, &loggingConfig, &mediaConfig)) == false) {
        return engine;
    }

    pjsua_transport_config transportConfig;
    pjsua_transport_config_default(&transportConfig);

    transportConfig.port = transportConfiguration.getPort();

    if(engine->checkStatus("pjsua transport", pjsua_transport_create(PJSIP_TRANSPORT_UDP, &transportConfig, NULL)) == false) {
        return engine;
    }

    if(engine->checkStatus("pjsual start", pjsua_start()) == false) {
        return engine;
    }
    return engine;
}

void Engine::addAccount(AccountConfiguration &anAccountConfiguration)
{
    pjsua_acc_config accountConfig;
    pjsua_acc_config_default(&accountConfig);

    accountConfig.id = pj_str(anAccountConfiguration.sipUrl.data());
    accountConfig.reg_uri = pj_str(anAccountConfiguration.registrationUri.data());

    accountConfig.proxy_cnt = anAccountConfiguration.proxys.size();
    for(int i = 0; i < anAccountConfiguration.proxys.size(); ++i) {
        QByteArray proxy = anAccountConfiguration.proxys.at(i); // TODO is a copy ?
        accountConfig.proxy[i] = pj_str(proxy.data());
    }

    accountConfig.cred_count = anAccountConfiguration.credentials.size();
    for(int i = 0; i < anAccountConfiguration.credentials.size(); ++i) {
        AccountCredential credential = anAccountConfiguration.credentials.at(i);
        accountConfig.cred_info[i].realm = pj_str(credential.realm.data());
        accountConfig.cred_info[i].scheme = pj_str(credential.scheme.data());
        accountConfig.cred_info[i].username = pj_str(credential.username.data());
        accountConfig.cred_info[i].data_type = credential.type;
        accountConfig.cred_info[i].data = pj_str(credential.password.data());
    }
    pjsua_acc_id account_id;

    if(checkStatus("Add account", pjsua_acc_add(&accountConfig, PJ_TRUE, &account_id)) == false) {
        return;
    }
}

bool Engine::isValid() const
{
    return status == PJ_SUCCESS;
}

PjError Engine::lastError() const
{
    return error;
}

bool Engine::checkStatus(const QString &aMessage, pj_status_t aStatus)
{
    bool ret = true;
    status = aStatus;
    if(aStatus != PJ_SUCCESS) {
        pjsua_destroy();
        error.setStatus(aStatus);
        error.setMessage(QString("%1 failed.").arg(aMessage));
        ret = false;
    }
    return ret;
}

void Engine::logger_callback_wrapper(int level, const char *data, int len)
{
    if(instance) {
        instance->logger_callback(level, data, len);
    }
}

void Engine::logger_callback(int level, const char *data, int len)
{
    Q_UNUSED(len);
    emit log(level, data);
}

void Engine::on_call_state_wrapper(pjsua_call_id call_id, pjsip_event *event)
{
    if(instance) {
        instance->on_call_state(call_id, event);
    }
}

void Engine::on_call_state(pjsua_call_id call_id, pjsip_event *event)
{
    Q_UNUSED(event);
    emit callState(call_id);
}

void Engine::on_incoming_call_wrapper(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata)
{
    if(instance) {
        instance->on_incoming_call(acc_id, call_id, rdata);
    }
}

void Engine::on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata)
{
    Q_UNUSED(rdata);
    emit incomingCall(acc_id, call_id);
}

void Engine::on_call_media_state_wrapper(pjsua_call_id call_id)
{
    if(instance) {
        instance->on_call_media_state(call_id);
    }
}

void Engine::on_call_media_state(pjsua_call_id call_id)
{
    emit callMediaState(call_id);
}

void Engine::on_reg_started_wrapper(pjsua_acc_id acc_id, pj_bool_t renew)
{
    if(instance) {
        instance->on_reg_started(acc_id, renew);
    }
}

void Engine::on_reg_started(pjsua_acc_id acc_id, pj_bool_t renew)
{
    bool _renew = false;
    if(renew == PJ_TRUE) {
        _renew = true;
    }
    emit regStarted(acc_id, _renew);
}

void Engine::on_transport_state_wrapper(pjsip_transport *tp, pjsip_transport_state state, const pjsip_transport_state_info *info)
{
}

} // namespace qpjsua
