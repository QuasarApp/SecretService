//#
//# Copyright (C) 2021-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "QASecret.h"

#include <QASecret/keystorage.h>


namespace QASecret {

bool init() {
    initSecretServiceResources();

    KeyStorage::initService();

    return true;
}

QString version() {
    return SECRETSERVICE_VERSION;
}


}
