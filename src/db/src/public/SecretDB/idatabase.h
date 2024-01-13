//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef IDATABASE_H
#define IDATABASE_H

#include <QSet>
#include <QSharedPointer>
#include "global.h"
#include "irecord.h"


namespace  DBSecret {
/**
 * @brief The IDataBase class Main database
 */
class SECRETDB_EXPORT IDataBase
{
public:
    IDataBase();

    /**
     * @brief Get a user by their ID.
     * @param id The ID of the user to retrieve.
     * @param ifNotExistsCreate - this option will create a new object if object with @a id is not existst into database. But object wil not save into database.
     * @return A QSharedPointer to the user object if found, nullptr otherwise.
     */
    virtual QSharedPointer<iRecord> getRecordByAlias(const QString& alias, bool ifNotExistsCreate = false) = 0;

    /**
     * @brief getRecordByHash Get record by hash.
     * @param hash The hash of the user to retrieve.
     * @param ifNotExistsCreate - this option will create a new object if object with @a id is not existst into database. But object wil not save into database.
     * @return A QSharedPointer to the user object if found, nullptr otherwise.
     */
    virtual QSharedPointer<iRecord> getRecordByHash(const QByteArray& hash, bool ifNotExistsCreate = false) = 0;

    /**
     * @brief saveRecord This method save a record object into database.
     * @param record - this is object tah will be saved into database
     * @return true if the object will save
     */
    virtual bool saveRecord(const QSharedPointer<iRecord>& record) = 0;

    /**
     * @brief removeRecordByAlias This method will remove record by alias.
     * @param alias alias of the record that will be removed.
     * @return true if function finished succesful else false.
     */
    virtual bool removeRecordByAlias(const QString& alias) = 0;

    /**
     * @brief removeRecordByKey This method will remove record by hash key.
     * @param hash is the key of the record that will be removed.
     * @return true if function finished succesful else false.
     */
    virtual bool removeRecordByKey(const QByteArray& hash) = 0;
};
}


#endif // IDATABASE_H
