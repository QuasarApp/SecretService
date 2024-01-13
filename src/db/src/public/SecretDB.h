//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "SecretDB/global.h"
#include "SecretDB/idatabase.h"
#include <QSharedPointer>
#include <QString>

inline void initSecretDBResources() { Q_INIT_RESOURCE(SecretDB); }

namespace DBSecret {

/**
 * @brief init main initialize method of The YourTimeDeliviry library
 * @return true if library initialized successfull
 */
bool SECRETDB_EXPORT init();

QSharedPointer<IDataBase> SECRETDB_EXPORT database();


};
