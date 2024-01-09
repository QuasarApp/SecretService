//#
//# Copyright (C) 2023-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "image.h"

namespace  QASecret {

Image::Image() {}

const QString &Image::getId() const {
    return _id;
}

void Image::setId(const QString &id) {
    _id = id;
}

const QByteArray &Image::getImage() const {
    return _image;
}

void Image::setImage(const QByteArray &source) {
    _image = source;
}

QH::PKG::DBObject* Image::createDBObject() const {
    return new Image();
}

bool Image::fromSqlRecord(const QSqlRecord& q) {
    _id = q.value("id").toString();
    _image = q.value("data").toByteArray();
    return true;
}

QString Image::table() const {
    return "Images";
}

QH::PKG::DBVariantMap Image::variantMap() const {
    return {
        {"id", {_id, QH::PKG::MemberType::PrimaryKey}},
        {"data", {_image, QH::PKG::MemberType::InsertUpdate}}
    };
}

QString Image::primaryKey() const {
    return "id";
}

QVariant Image::primaryValue() const {
    return _id;
}
}
