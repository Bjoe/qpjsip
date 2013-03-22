#ifndef QPJSUA_MEDIACONFIGURATION_H
#define QPJSUA_MEDIACONFIGURATION_H

#include "pjsua.h"

namespace qpjsua {

class MediaConfiguration
{
public:
    static MediaConfiguration build();

    pjsua_media_config getPjsuaMediaConfig() const
    {
        return configuration;
    }

private:
    pjsua_media_config configuration;

    MediaConfiguration();
};

} // namespace qpjsua

#endif // QPJSUA_MEDIACONFIGURATION_H
