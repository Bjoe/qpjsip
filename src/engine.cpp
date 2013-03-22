#include "engine.h"

#include <QString>
#include <QByteArray>

#include <QDebug>


namespace qpjsua {

Engine::Engine()
{
}

Engine::~Engine()
{
    //pjsua_destroy();
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

Engine Engine::Builder::build() const
{
    Engine engine;

    pj_status_t status = pjsua_create();
    if(status != PJ_SUCCESS) {
        qDebug() << "Error create pjsua " << status;
        pjsua_destroy();
        return engine;
    }
    qDebug() << "pjsua create";

    pjsua_config config;
    pjsua_config_default(&config);

    config.cb.on_incoming_call = &on_incoming_call;
    config.cb.on_call_state = &on_call_state;
    config.cb.on_call_media_state = &on_call_media_state;
    config.cb.on_reg_started = &on_reg_started;
    config.cb.on_transport_state = &on_transport_state;

    pjsua_logging_config loggingConfig;
    pjsua_logging_config_default(&loggingConfig);
    loggingConfig.console_level = loggingConfiguration.getConsoleLevel();

    pjsua_media_config mediaConfig;
    pjsua_media_config_default(&mediaConfig);

    status = pjsua_init(&config, &loggingConfig, &mediaConfig);
    if(status != PJ_SUCCESS) {
        qDebug() << "Error init pjsua " << status;
        pjsua_destroy();
        return engine;
    }
    qDebug() << "pjsua init";

    pjsua_transport_config transportConfig;
    pjsua_transport_config_default(&transportConfig);

    transportConfig.port = transportConfiguration.getPort();

    status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &transportConfig, NULL);
    if(status != PJ_SUCCESS) {
        qDebug() << "Error transport pjsua " << status;
        pjsua_destroy();
        return engine;
    }
    qDebug() << "pjsua transport create";

    status = pjsua_start();
    if(status != PJ_SUCCESS) {
        qDebug() << "Error start pjsua " << status;
        pjsua_destroy();
        return engine;
    }
    qDebug() << "pjsua started";
}

void Engine::addAccount(AccountConfiguration &anAccountConfiguration) const
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

    pj_status_t status = pjsua_acc_add(&accountConfig, PJ_TRUE, &account_id);

    if(status != PJ_SUCCESS) {
        qDebug() << "Error pjsua account add " << status;
        pjsua_destroy();
        return;
    }
    qDebug() << QString("pjsua account"); // add %1").arg(account_id);
}


void Engine::on_call_state(pjsua_call_id call_id, pjsip_event *event)
{
    pjsua_call_info callInfo;
    pjsua_call_get_info(call_id, &callInfo);
}

void Engine::on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata)
{
    pjsua_call_info callInfo;
    pjsua_call_get_info(call_id, &callInfo);

    qDebug() << QString("Incoming call from %1").arg(callInfo.state_text.ptr, callInfo.state_text.slen);
}

void Engine::on_call_media_state(pjsua_call_id call_id)
{
    qDebug() << QString("on_call_media call_id %1").arg(call_id);
}

void Engine::on_reg_started(pjsua_acc_id acc_id, pj_bool_t renew)
{
    qDebug() << QString("on_reg_started acc_id %1").arg(acc_id);
}

void Engine::on_transport_state(pjsip_transport *tp, pjsip_transport_state state, const pjsip_transport_state_info *info)
{
    qDebug() << QString("on_transport_state state %1").arg(state);
}

} // namespace qpjsua
