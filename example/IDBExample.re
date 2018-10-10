open WebapiExtra.Dom;

type t = {
  mutable db: option(IDBDatabase.t),
  dbName: string,
  objectStoreName: string,
};

let make = (dbName, objectStoreName) => {db: None, dbName, objectStoreName};

exception DatabaseAlreadyOpen;
let open_ = s =>
  Js.Promise.make((~resolve, ~reject) => {
    let req = indexedDB |> IDBFactory.open_(s.dbName, 1);
    req->IDBOpenDBRequest.setOnSuccess(_ => {
      s.db = req |> IDBOpenDBRequest.result;
      resolve(. Js.undefined);
    });
    req->IDBOpenDBRequest.setOnError(evt => {
      Js.log(evt);
      reject(. Not_found);
    });
    req->IDBOpenDBRequest.setOnBlocked(evt => {
      Js.log(evt);
      reject(. DatabaseAlreadyOpen);
    });
    req->IDBOpenDBRequest.setOnUpgradeNeeded(_ => {
      let db = req |> IDBOpenDBRequest.result;
      if (!(
            db
            |> IDBDatabase.objectStoreNames
            |> DOMStringList.contains(s.objectStoreName)
          )) {
        db
        |> IDBDatabase.createObjectStoreWithOptions(
             s.objectStoreName,
             IDBObjectStoreParameters.make(~autoIncrement=true, ()),
           )
        |> ignore;
      };
      s.db = Some(db);
    });
  });
exception KeyStoreNotOpen;
let saveKey = (id, thisPeer, s) =>
  Js.Promise.make((~resolve, ~reject) =>
    switch (s.db) {
    | Some(db) =>
      let transaction =
        db |> IDBDatabase.transaction([|s.objectStoreName|], ReadWrite);
      transaction->IDBTransaction.setOnError(evt => {
        Js.log(evt);
        reject(. Not_found);
      });
      transaction->IDBTransaction.setOnAbort(evt => {
        Js.log(evt);
        /* TODO: some real error please... */
        reject(. Not_found);
      });
      transaction->IDBTransaction.setOnComplete(_ => resolve(. Js.undefined));

      let objectStore =
        transaction |> IDBTransaction.objectStore(s.objectStoreName);
      objectStore |> IDBObjectStore.putWithKey(thisPeer, id) |> ignore;
    | None => reject(. KeyStoreNotOpen)
    }
  );

let getKey = (id, s) =>
  Js.Promise.make((~resolve, ~reject) =>
    switch (s.db) {
    | Some(db) =>
      let transaction =
        db |> IDBDatabase.transaction([|s.objectStoreName|], ReadOnly);
      let objectStore =
        transaction |> IDBTransaction.objectStore(s.objectStoreName);

      let request = objectStore |> IDBObjectStore.get(id);
      request->IDBRequest.setOnSuccess(_ =>
        resolve(. request |> IDBRequest.result)
      );
      request->IDBRequest.setOnError(_
        /* TODO: some real error please... */
        => reject(. Not_found));
    | None => reject(. KeyStoreNotOpen)
    }
  );

let close = s =>
  Js.Promise.make((~resolve, ~reject) =>
    switch (s.db) {
    | Some(db) =>
      db |> IDBDatabase.close;
      s.db = None;
      resolve(. Js.undefined);
    | None => reject(. KeyStoreNotOpen)
    }
  );

module StringMap = Map.Make(String);
type testVariant =
  | A
  | B(int);
type testRec = {
  a: string,
  d: testVariant,
  e: testVariant,
};

let run = () => {
  let then_ = Js.Promise.then_;
  let key = "normalObject";
  let s = make("testDB", "testObjectStore");
  s
  |> open_
  |> then_(_ => s |> getKey(idbKeyOfString(key)))
  |> then_(maybeResult =>
       (
         switch (maybeResult) {
         | Some(result) => Js.log2("DB Read a value:", result)
         | None => Js.log("Empty value")
         }
       )
       |> Js.Promise.resolve
     )
  |> Js.Promise.catch(_ =>
       Js.log("Could not read a value at " ++ key) |> Js.Promise.resolve
     )
  |> then_(_ => {
       Js.log("Saving data");
       s
       |> saveKey(
            idbKeyOfString(key),
            {"someUtfString": {js|Mušomut|js}, "someNumber": 42},
          );
     })
  |> then_(_ =>
       s
       |> saveKey(
            idbKeyOfString("map"),
            StringMap.(empty |> add("b", "totok") |> add("c", "Mechto")),
          )
     )
  |> then_(_ =>
       s |> saveKey(idbKeyOfString("record"), {a: "woooo", d: A, e: B(58)})
     )
  |> then_(_ => Js.log("Data saved") |> Js.Promise.resolve)
  |> Js.Promise.catch(_ =>
       Js.log("Data saving failed") |> Js.Promise.resolve
     )
  |> then_(_ => s |> close);
};