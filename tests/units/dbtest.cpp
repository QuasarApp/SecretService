//#
//# Copyright (C) 2024-2024 QuasarApp.
//# Distributed under the GPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#include "dbtest.h"
#include "heart.h"
#include <SecretDB.h>

DBTest::DBTest() {

}

DBTest::~DBTest() {

}

void DBTest::test() {
    QH::init();
    DBSecret::init();
    auto database = DBSecret::database();

    QVERIFY2(!database->getRecordByAlias("test"), "should be empty on first run");
    QVERIFY2(!database->getRecordByAlias(""), "should be empty on first run");

    QVERIFY2(!database->getRecordByHash(""), "should be empty on first run");

    QSharedPointer<DBSecret::iRecord> result;
    QVERIFY2((result = database->getRecordByAlias("test", true)), "must creat a new empty record");

    QVERIFY2(!database->getRecordByAlias("test"),
             "still should be empty because the getRecordByAlias with creation option do not save object into database");

    QVERIFY2(result->getAlias() == "test", "verify alias");
    QVERIFY2(result->getData().isEmpty(), "verify alias");
    QVERIFY2(result->getHash().isEmpty(), "verify alias");

    auto dataHash = result->setData("secret");

    QVERIFY2(result->getAlias() == "test", "verify configured record");
    QVERIFY2(result->getData() == "secret", "verify configured record");
    QVERIFY2(result->getHash() == QCryptographicHash::hash("secret",
                                                           QCryptographicHash::Sha256).toBase64(QByteArray::Base64UrlEncoding),
             "verify configured record");
    QVERIFY2(result->getHash() == dataHash,
             "verify configured record");

    database->saveRecord(result);

    auto result2 = database->getRecordByAlias("test");

    QVERIFY2(result2->getAlias() == result->getAlias(), "should be some as a prev object");
    QVERIFY2(result2->getHash() == result->getHash(), "should be some as a prev object");
    QVERIFY2(result2->getData() == result->getData(), "should be some as a prev object");

    result2 = database->getRecordByHash(dataHash);

    QVERIFY2(result2->getAlias() == result->getAlias(), "should be some as a prev object");
    QVERIFY2(result2->getHash() == result->getHash(), "should be some as a prev object");
    QVERIFY2(result2->getData() == result->getData(), "should be some as a prev object");
}
