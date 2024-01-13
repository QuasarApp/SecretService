//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "record.h"

#include <QCryptographicHash>

namespace  DBSecret {

Record::Record() {}


QH::PKG::DBObject* Record::createDBObject() const {
    return new Record();
}

bool Record::fromSqlRecord(const QSqlRecord& q) {
    _hash = q.value("hash").toByteArray();
    _data = q.value("data").toByteArray();
    _alias = q.value("alias").toString();

    return true;
}

QString Record::table() const {
    return "Records";
}

QH::PKG::DBVariantMap Record::variantMap() const {
    return {
        {"hash",  {_hash,  QH::PKG::MemberType::PrimaryKey}},
        {"alias", {_alias, static_cast<QH::PKG::MemberType>(static_cast<int>(QH::PKG::MemberType::InsertUpdate) |
                                                            static_cast<int>(QH::PKG::MemberType::Unique))}},
        {"data",  {_data,  QH::PKG::MemberType::Insert}}

    };
}

QString Record::primaryKey() const {
    if (_hash.size())
        return "hash";

    return "alias";
}

QVariant Record::primaryValue() const {
    if (_hash.size())
        return _hash;

    return _alias;
}

const QString &Record::getAlias() const {
    return _alias;
}

void Record::setAlias(const QString &alias) {
    _alias = alias;
}

const QByteArray &Record::getHash() const {
    return _hash;
}

void Record::setHash(const QByteArray &source) {
    _hash = source;
}

const QByteArray &Record::getData() const {
    return _data;
}

const QByteArray &Record::setData(const QByteArray &newData) {
    _data = newData;
    setHash(QCryptographicHash::hash(_data, QCryptographicHash::Sha256).toBase64(QByteArray::Base64UrlEncoding));
    return getHash();
}

}
