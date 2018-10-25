module CloseEvent = {
  module Impl = (T: {type t;}) => {
    [@bs.get] external wasClean: T.t => bool = "";
    [@bs.get] external code: T.t => int = "";
    [@bs.get] external reason: T.t => string = "";
  };

  type t;

  include Webapi.Dom.Event.Impl({
    type nonrec t = t;
  });
  include Impl({
    type nonrec t = t;
  });

  [@bs.new] external make: string => t = "CloseEvent";
  /* TODO: Add options type (CloseEventInit) */
  [@bs.new]
  external makeWithOptions: (string, Js.t({..})) => t = "CloseEvent";
};

module WebSocket = {
  type t;

  [@bs.deriving jsConverter]
  type readyState =
    | [@bs.as 0] Connecting
    | [@bs.as 1] Open
    | [@bs.as 2] Closing
    | [@bs.as 3] Closed
    | Unknown;

  [@bs.new] external create: string => t = "WebSocket";

  [@bs.get] external readyState: t => int = "";
  let readyState = t =>
    switch (readyStateFromJs(t->readyState)) {
    | Some(rs) => rs
    | None => Unknown
    };

  [@bs.send] external sendString: (t, string) => unit = "send";
  [@bs.send]
  external sendArrayBuffer: (t, Js.Typed_array.array_buffer) => unit = "send";
  [@bs.send] external close: t => unit = "";

  [@bs.set]
  external setOnMessage: (t, WebMessagingRe.MessageEvent.t => unit) => unit =
    "onmessage";
  [@bs.set] external setOnOpen: (t, Dom.event => unit) => unit = "onopen";
  [@bs.set] external setOnError: (t, Dom.event => unit) => unit = "onerror";
  [@bs.set] external setOnClose: (t, CloseEvent.t => unit) => unit = "onclose";
};