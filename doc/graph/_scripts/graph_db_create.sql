-- ^^graph_db_create.sql

BEGIN TRANSACTION;


CREATE TABLE CallT
(   SourceFile  TEXT NOT NULL,
    CallingFunc TEXT NOT NULL,
    CalledFunc  TEXT NOT NULL
);


CREATE TABLE FuncNameT
(   FuncName    TEXT NOT NULL,
    FormatName  TEXT NOT NULL
);


CREATE TABLE FormatT
(   FormatName  TEXT NOT NULL,
    FormatText  TEXT,
    Notes       TEXT
);


CREATE VIEW FuncFormatV AS
    SELECT
        FuncNameT.FuncName,
        FuncNameT.FormatName,
        FormatT.FormatText
    FROM FuncNameT INNER JOIN FormatT
    ON FuncNameT.FormatName = FormatT.FormatName;


CREATE VIEW NodeV AS
    SELECT
        SourceFile,
        '~1"' || _Names_.FuncName || '" [' || FuncFormatV.FormatText || '];'
        AS Node
    FROM
    (   SELECT SourceFile, FuncName FROM
        (   SELECT SourceFile, CallingFunc AS FuncName FROM CallT
            UNION
            SELECT SourceFile, CalledFunc AS FuncName FROM CallT
        )
        GROUP BY SourceFile, FuncName
    ) AS _Names_
    INNER JOIN FuncFormatV
    ON _Names_.FuncName = FuncFormatV.FuncName
    WHERE FuncFormatV.FormatName <> "REMOVE";


CREATE VIEW LinkV AS
    SELECT
        SourceFile,
        '~1"' || CallingFunc || '" -> "' || CalledFunc || '";'
        AS Link
    FROM CallT LEFT JOIN FuncNameT
    ON CallT.CalledFunc = FuncNameT.FuncName
    WHERE (FuncNameT.FormatName IS NULL)
    OR FuncNameT.FormatName <> "REMOVE";


COMMIT TRANSACTION;

--eof--
