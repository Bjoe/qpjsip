#include "transportconfiguration.h"

namespace qpjsua {

TransportConfiguration::TransportConfiguration() : configuration()
{
    pjsua_transport_config_default(&configuration);
}

TransportConfiguration TransportConfiguration::build()
{
    return TransportConfiguration();
}

TransportConfiguration &TransportConfiguration::withPort(int aPort)
{
    configuration.port = aPort;
    return *this;
}

pj_status_t TransportConfiguration::create() const
{
    return pjsua_transport_create(PJSIP_TRANSPORT_UDP, &configuration, NULL);
}

} // namespace qpjsua
