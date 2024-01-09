//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#ifndef IRECORD_H
#define IRECORD_H

#include "global.h"

namespace QASecret {

/**
 * @brief The iRecord class This is main interface for all records of database
 */
class SECRETDB_EXPORT iRecord
{
public:
    iRecord();

    /**
     * @brief getAlias returns alias of the record.
     * @return record alias.
     */
    virtual const QString& getAlias() const = 0;

    /**
     * @brief setAlias This method sets new alias for record.
     * @param alias is a new vlaue of record
     */
    virtual void setAlias(const QString& alias) = 0;

    /**
     * @brief getHash return hash of data
     * @return hash of record
     */
    virtual const QByteArray& getHash() const = 0;

    /**
     * @brief setHash This method sets new hash of record.
     * @param source is raw data sources of iamge.
     */
    virtual void setHash(const QByteArray& source) = 0;

    /**
     * @brief getData This  method returns data of the record.
     * @return source secret data of record
     */
    virtual const QByteArray& getData() const = 0;

    /**
     * @brief setData This method sets new data of record.
     * @param newData this is new value of data.
     */
    virtual void setData(const QByteArray& newData) = 0;

};

}
#endif // IRECORD_H
