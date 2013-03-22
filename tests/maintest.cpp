
#include <QCoreApplication>
#include <pjsua-lib/pjsua.h>

#include "config.h"

#include "engine.h"
#include "loggingconfiguration.h"
#include "mediaconfiguration.h"
#include "transportconfiguration.h"
#include "accountconfiguration.h"

using namespace qpjsua;

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



    Engine engine = Engine::create(loggingConfiguration, mediaConfiguration);
    engine.start(transportConfiguration);
    engine.addAccount(accountConfiguration);


    app.exec();

    return 0;
}
