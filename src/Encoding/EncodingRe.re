module TextEncoder = {
  type t = EncodingTypesRe.textEncoder;
  [@bs.new] external create: unit => t = "TextEncoder";
  [@bs.send] external encode: (t, string) => Js.Typed_array.Uint8Array.t = "";
};

module TextDecoder = {
  type t = EncodingTypesRe.textDecoder;
  [@bs.new] external create: unit => t = "TextDecoder";
  /* TODO: create with options */
  [@bs.send] external decode: (t, Js.Typed_array.array_buffer) => string = "";
  [@bs.send]
  external decodeWithOptions:
    (t, Js.Typed_array.array_buffer, EncodingTypesRe.textDecodeOptions) =>
    string =
    "";
};

include EncodingTypesRe;