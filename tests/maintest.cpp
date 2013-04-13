
#include <QCoreApplication>
#include <QSettings>

#include <pjsua-lib/pjsua.h>

#include "config.h"

#include "output.h"

#include "pjerror.h"
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
    QString realm = settings.value("realm").toString();
    QString scheme = settings.value("scheme").toString();
    QString username = settings.value("username").toString();
    QString password = settings.value("password").toString();
    QString registration = settings.value("registration").toString();
    QString sip = settings.value("sip").toString();
    QString proxy = settings.value("proxy").toString();

    tests::Output *output = new tests::Output();

    LoggingConfiguration loggingConfiguration = LoggingConfiguration::build()
            .withConsoleLevel(4)
            .withLogOutput(output, SLOT(onLog(int,QString)));

    TransportConfiguration transportConfiguration = TransportConfiguration::build()
            .withPort(5160);

    MediaConfiguration mediaConfiguration = MediaConfiguration::build();

    AccountCredential credential = AccountCredential::build()
            .withRealm(realm)
            .withScheme(scheme)
            .withUsername(username)
            .withPasswordType(PJSIP_CRED_DATA_PLAIN_PASSWD)
            .withPassword(password);
    AccountConfiguration accountConfiguration = AccountConfiguration::build()
            .withRegistrationUri("sip:" + registration)
            .withSipUrl("sip:" + sip)
            .addCredential(credential)
            .addProxy("sip:" + proxy);

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
                    SIGNAL(incomingCall(pjsua_acc_id, pjsua_call_id)),
                    SLOT(onIncomingCall(pjsua_acc_id, pjsua_call_id)),
                    Qt::QueuedConnection);
    output->connect(engine,
                    SIGNAL(callState(pjsua_call_id)),
                    SLOT(onCallState(pjsua_call_id)),
                    Qt::QueuedConnection);
    output->connect(engine,
                    SIGNAL(callMediaState(pjsua_call_id)),
                    SLOT(onCallMediaState(pjsua_call_id)),
                    Qt::QueuedConnection);
    output->connect(engine,
                    SIGNAL(regStarted(pjsua_acc_id, bool)),
                    SLOT(onRegStarted(pjsua_acc_id, bool)),
                    Qt::QueuedConnection);

    engine->addAccount(accountConfiguration);

    output->out(engine->lastError(), "Add account");
    if(engine->isValid() == false) {
        return 1;
    }

    app.exec();

    delete engine;
    return 0;
}
