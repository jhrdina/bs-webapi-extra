/* ===================================== */
/* MODULES                               */
/* ===================================== */

module CryptoKeyPair = {
  type t = WebCryptoTypesRe.cryptoKeyPair;
  [@bs.new] external create: unit => t = "CryptoKeyPair";
  [@bs.get] external publicKey: t => WebCryptoTypesRe.cryptoKey = "";
  [@bs.set]
  external setPublicKey: (t, WebCryptoTypesRe.cryptoKey) => unit = "publicKey";
  [@bs.get] external privateKey: t => WebCryptoTypesRe.cryptoKey = "";
  [@bs.set]
  external setPrivateKey: (t, WebCryptoTypesRe.cryptoKey) => unit =
    "privateKey";
};

module Algorithm = {
  module Impl = (T: {type t;}) => {
    [@bs.get] external name: T.t => string = "";
    [@bs.set] external setName: (T.t, string) => unit = "name";
  };
  type t = WebCryptoTypesRe.algorithm;
  include Impl({
    type nonrec t = t;
  });
};

module RsaKeyGenParams = {
  module Impl = (T: {type t;}) => {
    [@bs.get] external modulusLength: T.t => int = "";
    [@bs.set] external setModulusLength: (T.t, int) => unit = "modulusLength";
    [@bs.get] external publicExponent: T.t => Js.Typed_array.Uint8Array.t = "";
    [@bs.set]
    external setPublicExponent: (T.t, Js.Typed_array.Uint8Array.t) => unit =
      "publicExponent";
  };
  type t = WebCryptoTypesRe.rsaKeyGenParams;
  include Algorithm.Impl({
    type nonrec t = t;
  });
  include Impl({
    type nonrec t = t;
  });
  let make = (~name, ~modulusLength, ~publicExponent) => {
    let a: t = Js.Obj.empty();
    a->setName(name);
    a->setModulusLength(modulusLength);
    a->setPublicExponent(publicExponent);
    a;
  };
};

module AlgorithmIdentifier = {
  type t = WebCryptoTypesRe.algorithmIdentifier;
  include Algorithm.Impl({
    type nonrec t = t;
  });
};

module HashAlgorithmIdentifier = {
  type t = WebCryptoTypesRe.hashAlgorithmIdentifier;
  /* include AlgorithmIdentifier.Impl({
       type nonrec t = t;
     }); */
  include Algorithm.Impl({
    type nonrec t = t;
  });
  let make = (~name) => {
    let a = Js.Obj.empty();
    a->setName(name);
    a;
  };
};

module RsaHashedImportParams = {
  module Impl = (T: {type t;}) => {
    [@bs.get]
    external hash: T.t => WebCryptoTypesRe.hashAlgorithmIdentifier = "";
    [@bs.set]
    external setHash: (T.t, WebCryptoTypesRe.hashAlgorithmIdentifier) => unit =
      "hash";
  };

  type t = WebCryptoTypesRe.rsaHashedImportParams;

  include Algorithm.Impl({
    type nonrec t = t;
  });
  include Impl({
    type nonrec t = t;
  });

  let make = (~name, ~hash) => {
    let a: t = Js.Obj.empty();
    a->setName(name);
    a->setHash(hash);
    a;
  };
};

module JsonWebKey = {
  type t = WebCryptoTypesRe.jsonWebKey;
  let create:
    (
      ~alg: string=?,
      ~crv: string=?,
      ~d: string=?,
      ~dp: string=?,
      ~dq: string=?,
      ~e: string=?,
      ~ext: bool=?,
      ~k: string=?,
      ~key_ops: array(string)=?,
      ~kty: string=?,
      ~n: string=?,
      ~oth: array(WebCryptoTypesRe.rsaOtherPrimesInfo)=?,
      ~p: string=?,
      ~q: string=?,
      ~qi: string=?,
      ~use: string=?,
      ~x: string=?,
      ~y: string=?,
      unit
    ) =>
    t =
    (
      ~alg=?,
      ~crv=?,
      ~d=?,
      ~dp=?,
      ~dq=?,
      ~e=?,
      ~ext=?,
      ~k=?,
      ~key_ops=?,
      ~kty=?,
      ~n=?,
      ~oth=?,
      ~p=?,
      ~q=?,
      ~qi=?,
      ~use=?,
      ~x=?,
      ~y=?,
      (),
    ) => {
      "alg": alg,
      "crv": crv,
      "d": d,
      "dp": dp,
      "dq": dq,
      "e": e,
      "ext": ext,
      "k": k,
      "key_ops": key_ops,
      "kty": kty,
      "n": n,
      "oth": oth,
      "p": p,
      "q": q,
      "qi": qi,
      "use": use,
      "x": x,
      "y": y,
    };
};

module RsaHashedKeyGenParams = {
  module Impl = (T: {type t;}) => {
    [@bs.get]
    external hash: T.t => WebCryptoTypesRe.hashAlgorithmIdentifier = "";
    [@bs.set]
    external setHash: (T.t, WebCryptoTypesRe.hashAlgorithmIdentifier) => unit =
      "hash";
  };

  type t = WebCryptoTypesRe.rsaHashedKeyGenParams;

  include Algorithm.Impl({
    type nonrec t = t;
  });
  include RsaKeyGenParams.Impl({
    type nonrec t = t;
  });
  include Impl({
    type nonrec t = t;
  });

  let make = (~name, ~modulusLength, ~publicExponent, ~hash) => {
    let a: t = Js.Obj.empty();
    a->setName(name);
    a->setModulusLength(modulusLength);
    a->setPublicExponent(publicExponent);
    a->setHash(hash);
    a;
  };
};

module Crypto = {
  type t = WebCryptoTypesRe.crypto;

  let getRandomValues = array => array;
  [@bs.get] external subtle: t => WebCryptoTypesRe.subtleCrypto = "subtle";
};

module SubtleCrypto = {
  type t = WebCryptoTypesRe.subtleCrypto;

  let keyUsagesToJs = usages =>
    usages |> Array.map(WebCryptoTypesRe.keyUsageToJs);

  [@bs.send]
  external encrypt:
    (
      t,
      WebCryptoTypesRe.algorithmIdentifier,
      WebCryptoTypesRe.cryptoKey,
      Js.Typed_array.array_buffer
    ) =>
    Js.Promise.t(Js.Typed_array.array_buffer) =
    "";

  [@bs.send]
  external generateKey:
    (t, WebCryptoTypesRe.algorithmIdentifier, bool, array(string)) =>
    Js.Promise.t(WebCryptoTypesRe.cryptoKey) =
    "";
  [@bs.send]
  external generateKeyPair:
    (t, WebCryptoTypesRe.rsaHashedKeyGenParams, bool, array(string)) =>
    Js.Promise.t(WebCryptoTypesRe.cryptoKeyPair) =
    "generateKey";
  let generateKeyPair = (t, params, extractable, usages) =>
    generateKeyPair(t, params, extractable, usages |> keyUsagesToJs);

  [@bs.send]
  external sign:
    (t, string, WebCryptoTypesRe.cryptoKey, Js.Typed_array.ArrayBuffer.t) =>
    Js.Promise.t(Js.Typed_array.array_buffer) =
    "";

  [@bs.send]
  external verify:
    (
      t,
      string,
      WebCryptoTypesRe.cryptoKey,
      /* signature */
      Js.Typed_array.array_buffer,
      /* data */
      Js.Typed_array.array_buffer
    ) =>
    Js.Promise.t(bool) =
    "";

  [@bs.send]
  external digest:
    (t, string, Js.Typed_array.array_buffer) =>
    Js.Promise.t(Js.Typed_array.array_buffer) =
    "";

  [@bs.send]
  external exportKey:
    (t, [@bs.as "jwk"] _, WebCryptoTypesRe.cryptoKey) =>
    Js.Promise.t(WebCryptoTypesRe.jsonWebKey) =
    "";

  [@bs.send]
  external importKey:
    (
      t,
      [@bs.as "jwk"] _,
      WebCryptoTypesRe.jsonWebKey,
      WebCryptoTypesRe.rsaHashedImportParams,
      bool,
      array(string)
    ) =>
    Js.Promise.t(WebCryptoTypesRe.cryptoKey) =
    "";
  let importKey = (t, jwk, params, extractable, usages) =>
    importKey(t, jwk, params, extractable, usages |> keyUsagesToJs);
};

/* ===================================== */
/* GLOBALS                               */
/* ===================================== */

[@bs.val] [@bs.scope "window"] external crypto: Crypto.t = "crypto";

include WebCryptoTypesRe;