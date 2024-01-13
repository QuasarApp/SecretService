//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef KEYSTORAGE_H
#define KEYSTORAGE_H

#include "SecretDB/idatabase.h"
#include "qaservice.h"
#include <QHash>

namespace QASecret {


/**
 * @brief The KeyStorage class the storage store seccrets values on the simple key - value table. Where value is secrete and key is a sha256(secret) hash.
 */
class KeyStorage: public QuasarAppUtils::Service<KeyStorage>
{
public:
    KeyStorage(const QSharedPointer<DBSecret::IDataBase>& db);

    /**
     * @brief add adds to storage new value, and return access key.
     * @param value This is value to save.
     * @param alias This is simple alias for get key.
     * @return access key of @a value.
     */
    QByteArray add(const QByteArray& value, const QString& alias = {});

    /**
     * @brief remove This method remove secret from storage by key.
     * @param key This is sha256 key of secret
     */
    void remove(const QByteArray& key);

    /**
     * @brief remove This method remove seccret value by alias.
     * @param alias
     */
    void remove(const QString& alias);

    /**
     * @brief get return value by access key.
     * @param key this is access key of value.
     * @return secret value
     */
    QByteArray get(const QByteArray& key);

    /**
     * @brief get return value by alias of key.
     * @param key this is access key of value.
     * @return secret value
     */
    QByteArray get(const QString& alias);

private:
    QSharedPointer<DBSecret::IDataBase> _db;

};
}
#endif // KEYSTORAGE_H
