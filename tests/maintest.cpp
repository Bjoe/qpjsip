
#include <QCoreApplication>
#include <QSettings>

#include <pjsua-lib/pjsua.h>

#include "config.h"

#include "output.h"

#include "pjerror.h"
#include "callinfo.h"
#include "accountinfo.h"
#include "engine.h"
#include "loggingconfiguration.h"
#include "mediaconfiguration.h"
#include "transportconfiguration.h"
#include "accountconfiguration.h"

using namespace qpjsua;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName("devolab");
    QCoreApplication::setOrganizationDomain("devolab.de");
    QCoreApplication::setApplicationName("QPjsua Example");

    QSettings settings;
    //settings.setValue("foo", "bar");
    unsigned sipPort = settings.value("sip.port").toUInt();

    tests::Output *output = new tests::Output();

    LoggingConfiguration loggingConfiguration = LoggingConfiguration::build()
            .withConsoleLevel(4)
            .withLogOutput(output, SLOT(onLog(int,QString)));

    TransportConfiguration transportConfiguration = TransportConfiguration::build()
            .withPort(sipPort);

    MediaConfiguration mediaConfiguration = MediaConfiguration::build();

    Engine *engine = Engine::Builder::create()
            .withLoggingConfiguration(loggingConfiguration)
            .withMediaConfiguration(mediaConfiguration)
            .withTransportConfiguration(transportConfiguration)
            .build();
    output->out(engine->lastError(), "Create Engine");
    if(engine->isValid() == false) {
        return 1;
    }
    output->connect(engine,
                    SIGNAL(incomingCall(qpjsua::AccountInfo, qpjsua::CallInfo)),
                    SLOT(onIncomingCall(qpjsua::AccountInfo, qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    output->connect(engine,
                    SIGNAL(callState(qpjsua::CallInfo)),
                    SLOT(onCallState(qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    output->connect(engine,
                    SIGNAL(callMediaState(qpjsua::CallInfo)),
                    SLOT(onCallMediaState(qpjsua::CallInfo)),
                    Qt::QueuedConnection);
    output->connect(engine,
                    SIGNAL(regStarted(qpjsua::AccountInfo, bool)),
                    SLOT(onRegStarted(qpjsua::AccountInfo, bool)),
                    Qt::QueuedConnection);


    QString realm = settings.value("realm").toString();
    QString scheme = settings.value("scheme").toString();
    QString username = settings.value("username").toString();
    QString password = settings.value("password").toString();
    QString registration = settings.value("registration").toString();
    QString sip = settings.value("sip").toString();
    QString proxy = settings.value("proxy").toString();
    unsigned rtpPort = settings.value("rtp.port").toUInt();

    AccountCredential *credential = AccountCredential::build()
            .withRealm(realm)
            .withScheme(scheme)
            .withUsername(username)
            .withPasswordType(PJSIP_CRED_DATA_PLAIN_PASSWD)
            .withPassword(password)
            .create();
    AccountConfiguration *accountConfiguration = AccountConfiguration::build()
            .withRegistrationUri("sip:" + registration)
            .withSipUrl("sip:" + sip)
            .withRtpPort(rtpPort)
            .addCredential(credential)
            .addProxy("sip:" + proxy)
            .create();

    engine->addAccount(accountConfiguration);

    output->out(engine->lastError(), "Add account");
    if(engine->isValid() == false) {
        return 1;
    }

    app.exec();

    delete engine;
    delete accountConfiguration;
    delete credential;
    return 0;
}
