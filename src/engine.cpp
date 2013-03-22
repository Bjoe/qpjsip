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

Engine Engine::create(const LoggingConfiguration &aLoggingConfiguration, const MediaConfiguration &aMediaConfiguration)
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

    pjsua_logging_config loggingConfig = aLoggingConfiguration.getPjsuaLoggingConfig();
    pjsua_media_config mediaConfig = aMediaConfiguration.getPjsuaMediaConfig();
    status = pjsua_init(&config, &loggingConfig, &mediaConfig);
    if(status != PJ_SUCCESS) {
        qDebug() << "Error init pjsua " << status;
        pjsua_destroy();
        return engine;
    }
    qDebug() << "pjsua init";
    return engine;
}

void Engine::start(const TransportConfiguration &aTransportConfiguration) const
{
    pj_status_t status = aTransportConfiguration.create();
    if(status != PJ_SUCCESS) {
        qDebug() << "Error transport pjsua " << status;
        pjsua_destroy();
        return;
    }
    qDebug() << "pjsua transport create";

    status = pjsua_start();
    if(status != PJ_SUCCESS) {
        qDebug() << "Error start pjsua " << status;
        pjsua_destroy();
        return;
    }
    qDebug() << "pjsua started";

}

void Engine::addAccount(const AccountConfiguration &anAccountConfiguration) const
{
    pj_status_t status = anAccountConfiguration.create();
    if(status != PJ_SUCCESS) {
        qDebug() << "Error pjsua account add " << status;
        pjsua_destroy();
        return;
    }
    qDebug() << QString("pjsua account"); // add %1").arg(account_id);
}


void Engine::init()
{
    QString sipUser("xxxxxxx");
    QString sipDomain("xxxxx");
    QString sipPassword("xxxxx");
    QString sipProxy("xxxxxxxxxxxxxx");
    int port = 5060;

    pj_status_t status = pjsua_create();
    if(status != PJ_SUCCESS) {
        qDebug() << "Error create pjsua " << status;
        pjsua_destroy();
        return;
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
    loggingConfig.console_level = 4;

    pjsua_media_config mediaConfig;
    pjsua_media_config_default(&mediaConfig);

    status = pjsua_init(&config, &loggingConfig, &mediaConfig);
    if(status != PJ_SUCCESS) {
        qDebug() << "Error init pjsua " << status;
        pjsua_destroy();
        return;
    }
    qDebug() << "pjsua init";

    pjsua_transport_config transportConfig;
    pjsua_transport_config_default(&transportConfig);

    transportConfig.port = port;

    status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &transportConfig, NULL);
    if(status != PJ_SUCCESS) {
        qDebug() << "Error transport pjsua " << status;
        pjsua_destroy();
        return;
    }
    qDebug() << "pjsua transport create";

    status = pjsua_start();
    if(status != PJ_SUCCESS) {
        qDebug() << "Error start pjsua " << status;
        pjsua_destroy();
        return;
    }
    qDebug() << "pjsua started";

    QByteArray id = QString("sip:%1@%2").arg(sipUser).arg(sipDomain).toLatin1();
    QByteArray uri = QString("sip:%1").arg(sipDomain).toLatin1();
    QByteArray realm = sipDomain.toLatin1();
    QByteArray username = sipUser.toLatin1();
    QByteArray password = sipPassword.toLatin1();
    QByteArray proxy = QString("sip:%1").arg(sipProxy).toLatin1();

    pjsua_acc_config accountConfig;
    pjsua_acc_config_default(&accountConfig);

    accountConfig.id = pj_str(id.data());
    accountConfig.reg_uri = pj_str(uri.data());
    accountConfig.proxy_cnt = 1;
    accountConfig.proxy[0] = pj_str(proxy.data());
    accountConfig.cred_count = 1;
    accountConfig.cred_info[0].realm = pj_str("*"); //realm.data());
    accountConfig.cred_info[0].scheme = pj_str("Digest");
    accountConfig.cred_info[0].username = pj_str(username.data());
    accountConfig.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    accountConfig.cred_info[0].data = pj_str(password.data());

    pjsua_acc_id account_id;

    status = pjsua_acc_add(&accountConfig, PJ_TRUE, &account_id);
    if(status != PJ_SUCCESS) {
        qDebug() << "Error pjsua account add " << status;
        pjsua_destroy();
        return;
    }
    qDebug() << QString("pjsua account add %1").arg(account_id);
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
