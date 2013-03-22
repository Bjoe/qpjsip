#include "mediaconfiguration.h"

namespace qpjsua {

MediaConfiguration::MediaConfiguration() : configuration()
{
    pjsua_media_config_default(&configuration);
}

MediaConfiguration MediaConfiguration::build()
{
    return MediaConfiguration();
}

} // namespace qpjsua
