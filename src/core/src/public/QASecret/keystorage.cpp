//#
//# Copyright (C) 2023-2023 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "keystorage.h"
#include <QCryptographicHash>

namespace QASecret {

KeyStorage::KeyStorage() {}

QByteArray KeyStorage::add(const QByteArray &value, const QString &alias) {
    QByteArray&& key = QCryptographicHash::hash(value, QCryptographicHash::Sha256);
    _storage[key] = value;
    _aliases[alias] = value;

    return key;
}

void KeyStorage::remove(const QByteArray &key) {
    _storage.remove(key);
}

void KeyStorage::remove(const QString &alias) {
    _aliases.remove(alias);
}

QByteArray KeyStorage::get(const QByteArray &key) {
    auto&& result = _storage.value(key);

    return result;
}

QByteArray KeyStorage::get(const QString &alias) {
    auto&& result = _aliases.value(alias);

    return result;
}
}
