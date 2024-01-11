BEGIN TRANSACTION;

CREATE TABLE IF NOT EXISTS "Records" (
        "hash"    VARCHAR NOT NULL UNIQUE,
        "alias"   VARCHAR DEFAULT NULL UNIQUE,
        "data"    BLOB NOT NULL
);

COMMIT;
