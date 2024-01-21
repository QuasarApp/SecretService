//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "secretdatabase.h"
#include <QCoreApplication>
#include "record.h"
#include <QCryptographicHash>
#include <dbobjectsrequest.h>
#include <sqldb.h>

namespace  DBSecret {

SecretDataBase::SecretDataBase() {

    addDBPatch({
        0,
        1,
        [](const QH::iObjectProvider* database) -> bool {
            return database->doSql(":/src/sql/SecretDB_1.sql");
        }
    });

}

QVariantMap SecretDataBase::defaultDbParams() const {
    return QH::DataBase::defaultDbParams();
}

QSharedPointer<iRecord>
SecretDataBase::getRecordByAlias(const QString &alias, bool ifNotExistsCreate) {
    return getById<Record>(alias, &Record::setAlias, ifNotExistsCreate);
}

QSharedPointer<iRecord>
SecretDataBase::getRecordByHash(const QByteArray &hash, bool ifNotExistsCreate) {
    return getById<Record>(hash, &Record::setHash, ifNotExistsCreate);
}

bool SecretDataBase::saveRecord(const QSharedPointer<iRecord> &record) {
    return db()->replaceObject(record.staticCast<Record>(), true);
}

bool SecretDataBase::removeRecordByAlias(const QString &alias) {
    return deleteById<Record>(alias, &Record::setAlias);
}

bool SecretDataBase::removeRecordByKey(const QByteArray &hash) {
    return deleteById<Record>(hash, &Record::setHash);
}

}
