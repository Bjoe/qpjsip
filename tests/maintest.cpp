
#include <QCoreApplication>
#include <QString>
#include <QByteArray>
#include <iostream>
#include <pjsua-lib/pjsua.h>

#include "config.h"

#include "pjerror.h"
#include "engine.h"
#include "loggingconfiguration.h"
#include "mediaconfiguration.h"
#include "transportconfiguration.h"
#include "accountconfiguration.h"

using namespace qpjsua;

void output(const PjError &anError, const QString &aMessage)
{
    QByteArray output = aMessage.toLatin1();
    if(anError.getStatus() != PJ_SUCCESS) {
        output = QString("%1 Code: %2").arg(anError.getMessage()).arg(anError.getStatus()).toLatin1();
    }
    std::cout << output.constData() << std::endl;
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    LoggingConfiguration loggingConfiguration = LoggingConfiguration::build()
            .withConsoleLevel(4);

    TransportConfiguration transportConfiguration = TransportConfiguration::build()
            .withPort(5060);

    MediaConfiguration mediaConfiguration = MediaConfiguration::build();

    AccountCredential credential = AccountCredential::build()
            .withRealm("*")
            .withScheme("Digest")
            .withUsername("XXXXXX")
            .withPasswordType(PJSIP_TRANSPORT_UDP)
            .withPassword("XXXXX");
    AccountConfiguration accountConfiguration = AccountConfiguration::build()
            .withRegistrationUri("sip:reg.de")
            .withSipUrl("sip:foo@reg.de")
            .addCredential(credential)
            .addProxy("sip:proxy.de");

    Engine engine = Engine::Builder::create()
            .withLoggingConfiguration(loggingConfiguration)
            .withMediaConfiguration(mediaConfiguration)
            .withTransportConfiguration(transportConfiguration)
            .build();

    output(engine.lastError(), "Create Engine");
    if(engine.isValid() == false) {
        return 1;
    }

    engine.addAccount(accountConfiguration);

    output(engine.lastError(), "Add account");
    if(engine.isValid() == false) {
        return 1;
    }

    app.exec();

    return 0;
}
