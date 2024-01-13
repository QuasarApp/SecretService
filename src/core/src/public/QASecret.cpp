//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "QASecret.h"

#include <QASecret/keystorage.h>
#include <SecretDB.h>

namespace QASecret {

bool init() {
    initSecretServiceResources();
    DBSecret::init();

    KeyStorage::initService(std::make_unique<KeyStorage>(DBSecret::database()));

    return true;
}

QString version() {
    return SECRETSERVICE_VERSION;
}


}
