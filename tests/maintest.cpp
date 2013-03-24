
#include <QCoreApplication>

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
    tests::Output *output = new tests::Output();

    LoggingConfiguration loggingConfiguration = LoggingConfiguration::build()
            .withConsoleLevel(4)
            .withLogOutput(output, SLOT(onLog(int,QString)));

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

    Engine *engine = Engine::Builder::create()
            .withLoggingConfiguration(loggingConfiguration)
            .withMediaConfiguration(mediaConfiguration)
            .withTransportConfiguration(transportConfiguration)
            .build();

    output->out(engine->lastError(), "Create Engine");
    if(engine->isValid() == false) {
        return 1;
    }

    engine->addAccount(accountConfiguration);

    output->out(engine->lastError(), "Add account");
    if(engine->isValid() == false) {
        return 1;
    }

    app.exec();

    return 0;
}
