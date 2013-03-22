
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



    Engine engine = Engine::create(loggingConfiguration, mediaConfiguration);
    engine.start(transportConfiguration);


    AccountCredential credential = AccountCredential::build()
            .withRealm("*")
            .withScheme("Digest")
            .withUsername("1551930e12")
            .withPasswordType(PJSIP_TRANSPORT_UDP)
            .withPassword("K6I0QC");
    AccountConfiguration accountConfiguration = AccountConfiguration::build()
            .withRegistrationUri("sip:sipgate.de")
            .withSipUrl("sip:1551930e12@sipgate.de")
            .addCredential(credential)
            .addProxy("sip:proxy.live.sipgate.de");


    engine.addAccount(accountConfiguration);


    app.exec();

    return 0;
}
