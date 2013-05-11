#include "transportconfiguration.h"

namespace qpjsua {

TransportConfiguration::TransportConfiguration() : port(0)
{
}

TransportConfiguration TransportConfiguration::build()
{
    return TransportConfiguration();
}

TransportConfiguration &TransportConfiguration::withPort(unsigned aPort)
{
    port = aPort;
    return *this;
}

unsigned TransportConfiguration::getPort() const
{
    return port;
}

} // namespace qpjsua
