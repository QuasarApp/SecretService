//#
//# Copyright (C) 2021-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "SecretDB.h"

#include <secretdatabase.h>


namespace QASecret {

bool init() {
    initSecretDBResources();
    return true;
}

QSharedPointer<IDataBase> database() {
    auto db = QSharedPointer<SecretDataBase>::create();
    db->initSqlDb();

    return db;
}


}
