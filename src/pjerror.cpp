#include "pjerror.h"

namespace qpjsua {

PjError::PjError() : message(""), status(PJ_SUCCESS)
{
}

void PjError::setMessage(const QString &aMessage)
{
    message = aMessage;
}

void PjError::setStatus(pj_status_t aStatus)
{
    status = aStatus;
}

QString PjError::getMessage() const
{
    return message;
}

pj_status_t PjError::getStatus() const
{
    return status;
}

} // namespace qpjsua
