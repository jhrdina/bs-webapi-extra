open WebapiExtra.Dom;

let algorithm = "RSASSA-PKCS1-v1_5";
let hash = "SHA-256";

let arrayBufferToBase64 = buffer =>
  Js.Typed_array.(
    Uint8Array.fromBuffer(buffer)
    |> Uint8Array.reduce(
         (. binary, b) => binary ++ Js.String.fromCharCode(b),
         "",
       )
    |> Webapi.Base64.btoa
  );

let stringToArrayBuffer = str =>
  TextEncoder.create()
  ->TextEncoder.encode(str)
  ->Js.Typed_array.Uint8Array.buffer;

exception JWKMissingKeys(string);
exception InternalError(string);
/* https://tools.ietf.org/html/rfc7638 */
let fingerprintForRSAJWK = (jwk: jsonWebKey) =>
  switch (jwk##e, jwk##kty, jwk##n) {
  | (Some(e), Some(kty), Some(n)) =>
    switch (Js.Json.stringifyAny({"e": e, "kty": kty, "n": n})) {
    | Some(str) =>
      str
      |> stringToArrayBuffer
      |> crypto->Crypto.subtle->SubtleCrypto.digest(hash)
      |> Js.Promise.then_(digestArrayBuffer =>
           Js.Promise.resolve(arrayBufferToBase64(digestArrayBuffer))
         )
    | None => Js.Promise.reject @@ InternalError("Stringify failed.")
    }
  | _ =>
    Js.Promise.reject @@
    JWKMissingKeys("JWK must contain all of the following keys: e, kty, n.")
  };

type state = {
  keyPair1: cryptoKeyPair,
  keyPair1Fingerprint: string,
  keyPair2: cryptoKeyPair,
};

let run = () => {
  let subtle = crypto->Crypto.subtle;
  let strToSign = "Pleeeee";
  let then_ = Js.Promise.then_;
  let thenl = cb =>
    Js.Promise.then_(v => {
      Js.log(v);
      cb(v);
    });

  subtle
  ->SubtleCrypto.generateKeyPair(
      RsaHashedKeyGenParams.make(
        ~name=algorithm,
        ~modulusLength=2048,
        ~publicExponent=Js.Typed_array.Uint8Array.make([|0x01, 0x00, 0x01|]),
        ~hash=HashAlgorithmIdentifier.make(~name=hash),
      ),
      false,
      [|`Sign, `Verify|],
    )
  |> then_(keyPair =>
       subtle
       ->SubtleCrypto.sign(
           algorithm,
           keyPair->CryptoKeyPair.privateKey,
           stringToArrayBuffer(strToSign),
         )
       |> then_(signature =>
            subtle
            ->SubtleCrypto.verify(
                algorithm,
                keyPair->CryptoKeyPair.publicKey,
                signature,
                stringToArrayBuffer("hasdf"),
              )
          )
       |> thenl(_ =>
            fingerprintForRSAJWK(
              JsonWebKey.create(~e="e", ~n="n", ~kty="kty", ()),
            )
          )
       |> thenl(_ =>
            subtle->SubtleCrypto.exportKey(keyPair->CryptoKeyPair.publicKey)
          )
     )
  |> thenl(jwk =>
       fingerprintForRSAJWK(jwk)
       |> thenl(_ =>
            subtle
            ->SubtleCrypto.importKey(
                jwk,
                RsaHashedImportParams.make(
                  ~name=algorithm,
                  ~hash=HashAlgorithmIdentifier.make(~name=hash),
                ),
                true,
                [|`Verify|],
              )
          )
     )
  |> thenl(subtle->SubtleCrypto.exportKey)
  |> thenl(fingerprintForRSAJWK)
  |> thenl(Js.Promise.resolve);
};

run();