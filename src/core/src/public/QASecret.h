//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "QASecret/global.h"
#include <QString>

inline void initSecretServiceResources() { Q_INIT_RESOURCE(secretcore); }

namespace QASecret {

/**
 * @brief init main initialize method of The SecretService library
 * @return true if library initialized successfull
 */
bool SECRETSERVICE_EXPORT init();

/**
 * @brief version This method return string value of a library version
 * @return string value of a library version
 */
QString SECRETSERVICE_EXPORT version();

};
