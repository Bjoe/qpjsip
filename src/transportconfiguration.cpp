#include "transportconfiguration.h"

namespace qpjsua {

TransportConfiguration::TransportConfiguration() : port(0)
{
}

TransportConfiguration TransportConfiguration::build()
{
    return TransportConfiguration();
}

TransportConfiguration &TransportConfiguration::withPort(int aPort)
{
    port = aPort;
    return *this;
}

} // namespace qpjsua
