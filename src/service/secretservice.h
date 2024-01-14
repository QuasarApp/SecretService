//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef SECRETSERVICE_H
#define SECRETSERVICE_H

#include <patronum.h>

/**
 * @brief The SecretService class main class
 */
class SecretService: public Patronum::Service<QCoreApplication>
{

public:
    SecretService(int argc, char **argv);

    bool onStart() override;

    void onStop() override;

    void handleReceiveData(const QHash<QString, Patronum::Feature> &data) override;
    bool handleReceive(const Patronum::Feature &data) override;
    QSet<Patronum::Feature> supportedFeatures() override;

};

#endif // SECRETSERVICE_H
