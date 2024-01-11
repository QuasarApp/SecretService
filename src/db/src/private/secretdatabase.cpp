//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "secretdatabase.h"
#include <QCryptographicHash>
#include <dbobjectsrequest.h>
#include <sqldb.h>

namespace  QASecret {

SecretDataBase::SecretDataBase() {

    addDBPatch({
        0,
        1,
        [](const QH::iObjectProvider* database) -> bool {
            return database->doSql(":/src/sql/SecretDB_1.sql");
        }
    });

}

QSharedPointer<iRecord>
SecretDataBase::getRecordByAlias(const QString &alias, bool ifNotExistsCreate) {

}

QSharedPointer<iRecord>
SecretDataBase::getRecordByHash(const QByteArray &hash, bool ifNotExistsCreate) {

}

bool SecretDataBase::saveRecord(const QSharedPointer<iRecord> &record) {

}

}
