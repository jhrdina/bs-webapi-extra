type idbTransaction;
type idbObjectStore;
type idbObjectStoreParameters;
type idbRequest('response);
type idbDatabase;
type idbOpenDBRequestLike('response);
type idbOpenDBRequest = idbOpenDBRequestLike(idbDatabase);
type idbFactory;
type idbKey = Js.Json.t;
let idbKeyOfInt: int => idbKey = i => Js.Json.number(float_of_int(i));
let idbKeyOfString: string => idbKey = s => Js.Json.string(s);

/* Not implemented: */
type idbCursor;
type idbCursorDirection;
type idbCursorWithValue;
type idbIndex;

type idbTransactionMode =
  | ReadOnly
  | ReadWrite
  | VersionChange;
let encodeIdbTransactionMode =
  fun
  | ReadOnly => "readonly"
  | ReadWrite => "readwrite"
  | VersionChange => "versionchange";