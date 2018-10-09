module IDBObjectStore = {
  type t = IDBTypesRe.idbObjectStore;
  module Impl = (T: {type t;}) => {
    [@bs.get] external autoIncrement: T.t => bool = "";
    [@bs.get]
    external indexNames: T.t => CommonDomInterfacesRe.domStringList = "";
    [@bs.get] external keyPath: T.t => array(string) = "";

    [@bs.get] external transaction: T.t => IDBTypesRe.idbTransaction = "";

    [@bs.send.pipe: T.t]
    external add: 'a => IDBTypesRe.idbRequest(IDBTypesRe.idbKey) = "";
    [@bs.send.pipe: T.t]
    external addWithKey:
      ('a, IDBTypesRe.idbKey) => IDBTypesRe.idbRequest(IDBTypesRe.idbKey) =
      "add";
    [@bs.send.pipe: T.t] external clear: unit = "";
    [@bs.send.pipe: T.t]
    external count: unit => IDBTypesRe.idbRequest(int) = "";
    [@bs.send.pipe: T.t]
    external countWithKey: IDBTypesRe.idbKey => IDBTypesRe.idbRequest(int) =
      "count";
    [@bs.send.pipe: T.t]
    external createIndex: (string, array(string)) => IDBTypesRe.idbIndex = "";
    [@bs.send.pipe: T.t]
    external createIndexWithOptions:
      (string, array(string), Js.t({..})) => IDBTypesRe.idbIndex =
      "createIndex";
    [@bs.send.pipe: T.t]
    external delete: IDBTypesRe.idbKey => IDBTypesRe.idbRequest(unit) = "";
    [@bs.send.pipe: T.t] external deleteIndex: string => unit = "";
    [@bs.send.pipe: T.t]
    external get: IDBTypesRe.idbKey => IDBTypesRe.idbRequest(option('a)) =
      "";
    [@bs.send.pipe: T.t]
    external getAll:
      (~query: IDBTypesRe.idbKey=?, ~count: int=?) =>
      IDBTypesRe.idbRequest(array('a)) =
      "";
    [@bs.send.pipe: T.t]
    external getAllKeys:
      (~query: IDBTypesRe.idbKey=?, ~count: int=?) =>
      IDBTypesRe.idbRequest(array(IDBTypesRe.idbKey)) =
      "";
    [@bs.send.pipe: T.t]
    external getKey:
      IDBTypesRe.idbKey => IDBTypesRe.idbRequest(option(IDBTypesRe.idbKey)) =
      "";
    [@bs.send.pipe: T.t] external index: string => IDBTypesRe.idbIndex = "";
    [@bs.send.pipe: T.t]
    external openCursor:
      (
        ~range: IDBTypesRe.idbKey=?,
        ~direction: IDBTypesRe.idbCursorDirection=?
      ) =>
      IDBTypesRe.idbRequest(option(IDBTypesRe.idbCursorWithValue)) =
      "";
    [@bs.send.pipe: T.t]
    external openKeyCursor:
      (
        ~query: IDBTypesRe.idbKey=?,
        ~direction: IDBTypesRe.idbCursorDirection=?
      ) =>
      IDBTypesRe.idbRequest(option(IDBTypesRe.idbCursor)) =
      "";
    [@bs.send.pipe: T.t]
    external put: 'a => IDBTypesRe.idbRequest(IDBTypesRe.idbKey) = "";
    [@bs.send.pipe: T.t]
    external putWithKey:
      ('a, IDBTypesRe.idbKey) => IDBTypesRe.idbRequest(IDBTypesRe.idbKey) =
      "put";
  };
  include Impl({
    type nonrec t = t;
  });
};

module IDBObjectStoreParameters = {
  type t = IDBTypesRe.idbObjectStoreParameters;
  [@bs.obj]
  external make: (~autoIncrement: bool=?, ~keyPath: string=?, unit) => t = "";
};

module IDBDatabase = {
  module Impl = (T: {type t;}) => {
    [@bs.get] external name: T.t => string = "";
    [@bs.get]
    external objectStoreNames: T.t => CommonDomInterfacesTypesRe.domStringList =
      "";

    [@bs.set]
    external setOnAbort: (T.t, Dom.event => unit) => unit = "onabort";
    [@bs.set]
    external setOnClose: (T.t, Dom.event => unit) => unit = "onclose";
    [@bs.set]
    external setOnError: (T.t, Dom.event => unit) => unit = "onerror";
    [@bs.set]
    external setOnVersionChange: (T.t, Dom.event => unit) => unit =
      "onversionchange";

    [@bs.get] external version: T.t => int = "";

    [@bs.send.pipe: T.t] external close: unit = "";
    [@bs.send.pipe: T.t]
    external createObjectStore: string => IDBTypesRe.idbObjectStore = "";
    [@bs.send.pipe: T.t]
    external createObjectStoreWithOptions:
      (string, IDBTypesRe.idbObjectStoreParameters) =>
      IDBTypesRe.idbObjectStore =
      "createObjectStore";
    [@bs.send.pipe: T.t] external deleteObjectStore: string => unit = "";
    [@bs.send.pipe: T.t]
    external transaction: (array(string), string) => IDBTypesRe.idbTransaction =
      "";
    let transaction = (storeNames, mode) =>
      transaction(storeNames, mode |> IDBTypesRe.encodeIdbTransactionMode);
  };

  type t = IDBTypesRe.idbDatabase;

  include Impl({
    type nonrec t = t;
  });
};

module IDBTransaction = {
  module Impl = (T: {type t;}) => {
    [@bs.get] external db: T.t => IDBTypesRe.idbDatabase = "";
    [@bs.get] external error: T.t => Js.Exn.t = "";
    [@bs.get] external mode: T.t => IDBTypesRe.idbTransactionMode = "";
    [@bs.get]
    external objectStoreNames: T.t => CommonDomInterfacesTypesRe.domStringList =
      "";

    [@bs.set]
    external setOnAbort: (T.t, Dom.event => unit) => unit = "onabort";
    [@bs.set]
    external setOnComplete: (T.t, Dom.event => unit) => unit = "oncomplete";
    [@bs.set]
    external setOnError: (T.t, Dom.event => unit) => unit = "onerror";

    [@bs.send.pipe: T.t] external abort: unit = "";
    [@bs.send.pipe: T.t]
    external objectStore: string => IDBTypesRe.idbObjectStore = "";
  };

  /* TODO: Extend EventTarget */
  type t = IDBTypesRe.idbTransaction;

  include Impl({
    type nonrec t = t;
  });
};

module IDBRequest = {
  module Impl = (T: {type t('r);}) => {
    [@bs.get] external error: T.t('r) => option(Js.Exn.t) = "";

    [@bs.set]
    external setOnError: (T.t('r), Dom.event => unit) => unit = "onerror";
    [@bs.set]
    external setOnSuccess: (T.t('r), Dom.event => unit) => unit = "onsuccess";

    [@bs.get] external result: T.t('r) => 'r = "";
  };

  type t('result) = IDBTypesRe.idbRequest('result);

  include Impl({
    type nonrec t('r) = t('r);
  });
};

module IDBOpenDBRequest = {
  module Impl = (T: {type t;}) => {
    [@bs.set]
    external setOnBlocked: (T.t, Dom.event => unit) => unit = "onblocked";
    [@bs.set]
    external setOnUpgradeNeeded: (T.t, Dom.event => unit) => unit =
      "onupgradeneeded";
  };

  type t = IDBTypesRe.idbOpenDBRequest;

  include IDBRequest.Impl({
    type nonrec t('result) =
      IDBTypesRe.idbOpenDBRequestLike(IDBTypesRe.idbDatabase);
  });
  include Impl({
    type nonrec t = t;
  });
};

module IDBFactory = {
  type t = IDBTypesRe.idbFactory;
  [@bs.send.pipe: t]
  external deleteDatabase: string => IDBTypesRe.idbOpenDBRequest = "";
  [@bs.send.pipe: t]
  external open_: (string, int) => IDBTypesRe.idbOpenDBRequest = "";
};

[@bs.val] [@bs.scope "window"] external indexedDB: IDBTypesRe.idbFactory = "";

include IDBTypesRe;