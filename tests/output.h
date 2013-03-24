#ifndef TESTS_OUTPUT_H
#define TESTS_OUTPUT_H

#include <QObject>
#include <QString>

#include "pjerror.h"

namespace tests {

class Output : public QObject
{
    Q_OBJECT
public:
    explicit Output(QObject *parent = 0);
    void out(const qpjsua::PjError &anError, const QString &aMessage);

public slots:
    void onLog(int level, QString message);
};

} // namespace tests

#endif // TESTS_OUTPUT_H
