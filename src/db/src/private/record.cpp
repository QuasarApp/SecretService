//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "record.h"

#include <QCryptographicHash>

namespace  QASecret {

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
        {"hash",  {_hash,  QH::PKG::MemberType::Unique}},
        {"alias", {_alias, static_cast<QH::PKG::MemberType>(static_cast<int>(QH::PKG::MemberType::InsertUpdate) |
                                                            static_cast<int>(QH::PKG::MemberType::Unique))}},
        {"data",  {_data,  QH::PKG::MemberType::Insert}}

    };
}

QString Record::primaryKey() const {
    return "hash";
}

QVariant Record::primaryValue() const {
    return _hash;
}

const QString &QASecret::Record::getAlias() const {
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

void Record::setData(const QByteArray &newData) {
    _data = newData;

    setHash(QCryptographicHash::hash(_data, QCryptographicHash::Sha256));
}

}
