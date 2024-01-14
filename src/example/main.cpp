//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "params.h"
#include <QASecret.h>
#include <QCoreApplication>
#include <QTimer>
#include <QASecret/keystorage.h>


int main(int argc, char * argv[]) {

    QCoreApplication app(argc, argv);
    QASecret::init();

    auto service = QASecret::KeyStorage::instance();

    QTimer::singleShot(0, nullptr, [service]() {
        auto hash = service->add("val");
        auto val = service->get(hash);

        if (val == "val") {
            QuasarAppUtils::Params::log("All is fine!", QuasarAppUtils::Info);
        }

        QCoreApplication::quit();
    });


    return app.exec();
}
