//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "keystorage.h"
#include <QCryptographicHash>

namespace QASecret {

KeyStorage::KeyStorage(const QSharedPointer<DBSecret::IDataBase> &db) {
    _db = db;
}

QByteArray KeyStorage::add(const QByteArray &value, const QString &alias) {

    if (auto record = _db->getRecordByAlias(alias, true)) {
        record->setData(value);
        if (_db->saveRecord(record)) {
            return record->getHash();
        }
    }

    return {};
}

void KeyStorage::remove(const QByteArray &key) {
    _db->removeRecordByKey(key);
}

void KeyStorage::remove(const QString &alias) {
    _db->removeRecordByAlias(alias);
}

QByteArray KeyStorage::get(const QByteArray &key) {
    if (auto&& result = _db->getRecordByHash(key)) {
        return result->getData();

    }

    return "";
}

QByteArray KeyStorage::get(const QString &alias) {
    if (auto&& result = _db->getRecordByAlias(alias)) {
        return result->getData();

    }

    return "";
}
}
