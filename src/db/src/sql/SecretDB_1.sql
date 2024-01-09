BEGIN TRANSACTION;

CREATE TABLE IF NOT EXISTS "ProcessedIds" (
        "id"	BIGINT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS "Orders" (
        "id"            INTEGER NOT NULL PRIMARY KEY,
        "time"          INTEGER NOT NULL,
        "finishTime"    INTEGER NOT NULL,
        "accepted"      BOOLEAN NOT NULL DEFAULT false,
        "done"          BOOLEAN NOT NULL DEFAULT false,
        "delivered"     BOOLEAN NOT NULL DEFAULT false,
        "courier"       INTEGER DEFAULT NULL,
        "receiver"      INTEGER DEFAULT NULL,
        "manufacturer"  INTEGER DEFAULT NULL,
        "data"          BLOB NOT NULL,

        FOREIGN KEY (courier) REFERENCES Users(id)
            ON DELETE CASCADE
            ON UPDATE CASCADE,

        FOREIGN KEY (receiver) REFERENCES Users(id)
            ON DELETE CASCADE
            ON UPDATE CASCADE,

        FOREIGN KEY (manufacturer) REFERENCES Users(id)
            ON DELETE CASCADE
            ON UPDATE CASCADE
);

COMMIT;
