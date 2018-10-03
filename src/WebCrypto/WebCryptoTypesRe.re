type algorithm;
type crypto;
type hashAlgorithmIdentifier = Js.t({.});

[@bs.deriving jsConverter]
type keyUsage = [
  | [@bs.as "encrypt"] `Encrypt
  | [@bs.as "decrypt"] `Decrypt
  | [@bs.as "sign"] `Sign
  | [@bs.as "verify"] `Verify
  | [@bs.as "deriveKey"] `DeriveKey
  | [@bs.as "deriveBits"] `DeriveBits
  | [@bs.as "wrapKey"] `WrapKey
  | [@bs.as "unwrapKey"] `UnwrapKey
];

type rsaHashedKeyGenParams = Js.t({.});
type rsaHashedImportParams = Js.t({.});
type rsaKeyGenParams = Js.t({.});
type subtleCrypto;
type cryptoKeyPair;
type cryptoKey;
type rsaPssParams;

type rsaOtherPrimesInfo = {
  .
  "d": Js.Nullable.t(string),
  "r": Js.Nullable.t(string),
  "t": Js.Nullable.t(string),
};

type jsonWebKey = {
  .
  "alg": option(string),
  "crv": option(string),
  "d": option(string),
  "dp": option(string),
  "dq": option(string),
  "e": option(string),
  "ext": option(bool),
  "k": option(string),
  "key_ops": option(array(string)),
  "kty": option(string),
  "n": option(string),
  "oth": option(array(rsaOtherPrimesInfo)),
  "p": option(string),
  "q": option(string),
  "qi": option(string),
  "use": option(string),
  "x": option(string),
  "y": option(string),
};

type algorithmIdentifier = {name: string};

/* Converters */

let keyUsagesToJs = usages => usages |> Array.map(keyUsageToJs);