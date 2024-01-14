//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include <SecretDB/idatabase.h>

#include <database.h>

#ifndef BOTDATABASE_H
#define BOTDATABASE_H

namespace  DBSecret {

class SecretDataBase: public IDataBase, public QH::DataBase
{
public:
    SecretDataBase();
    QVariantMap defaultDbParams() const override;

    // IDataBase interface
public:
    QSharedPointer<iRecord> getRecordByAlias(const QString &alias, bool ifNotExistsCreate) override;
    QSharedPointer<iRecord> getRecordByHash(const QByteArray &hash, bool ifNotExistsCreate) override;
    bool saveRecord(const QSharedPointer<iRecord> &record) override;

    bool removeRecordByAlias(const QString &alias) override;
    bool removeRecordByKey(const QByteArray &hash) override;
};
}
#endif // BOTDATABASE_H
