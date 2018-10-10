module Navigator = {
  type t = NavigatorTypesRe.navigator;

  [@bs.get] external onLine: t => bool = "";
};

[@bs.get] external navigator: Dom.window => NavigatorTypesRe.navigator = "";

/* TODO: Move to window */

/* 'online' event */

[@bs.send.pipe: Dom.window]
external addOnlineEventListener:
  ([@bs.as "online"] _, Dom.event => unit) => unit =
  "addEventListener";
[@bs.send.pipe: Dom.window]
external addOnlineEventListenerWithOptions:
  (
    [@bs.as "online"] _,
    Dom.event => unit,
    {
      .
      "capture": bool,
      "once": bool,
      "passive": bool,
    }
  ) =>
  unit =
  "addEventListener"; /* not widely supported */
[@bs.send.pipe: Dom.window]
external addOnlineEventListenerUseCapture:
  ([@bs.as "online"] _, Dom.event => unit, [@bs.as {json|true|json}] _) => unit =
  "addEventListener";
[@bs.send.pipe: Dom.window]
external removeOnlineEventListener:
  ([@bs.as "online"] _, Dom.event => unit) => unit =
  "removeEventListener";
[@bs.send.pipe: Dom.window]
external removeOnlineEventListenerWithOptions:
  (
    [@bs.as "online"] _,
    Dom.event => unit,
    {
      .
      "capture": bool,
      "passive": bool,
    }
  ) =>
  unit =
  "removeEventListener"; /* not widely supported */
[@bs.send.pipe: Dom.window]
external removeOnlineEventListenerUseCapture:
  ([@bs.as "online"] _, Dom.event => unit, [@bs.as {json|true|json}] _) => unit =
  "removeEventListener";

/* 'offline' event */

[@bs.send.pipe: Dom.window]
external addOfflineEventListener:
  ([@bs.as "offline"] _, Dom.event => unit) => unit =
  "addEventListener";
[@bs.send.pipe: Dom.window]
external addOfflineEventListenerWithOptions:
  (
    [@bs.as "offline"] _,
    Dom.event => unit,
    {
      .
      "capture": bool,
      "once": bool,
      "passive": bool,
    }
  ) =>
  unit =
  "addEventListener"; /* not widely supported */
[@bs.send.pipe: Dom.window]
external addOfflineEventListenerUseCapture:
  ([@bs.as "offline"] _, Dom.event => unit, [@bs.as {json|true|json}] _) =>
  unit =
  "addEventListener";
[@bs.send.pipe: Dom.window]
external removeOfflineEventListener:
  ([@bs.as "offline"] _, Dom.event => unit) => unit =
  "removeEventListener";
[@bs.send.pipe: Dom.window]
external removeOfflineEventListenerWithOptions:
  (
    [@bs.as "offline"] _,
    Dom.event => unit,
    {
      .
      "capture": bool,
      "passive": bool,
    }
  ) =>
  unit =
  "removeEventListener"; /* not widely supported */
[@bs.send.pipe: Dom.window]
external removeOfflineEventListenerUseCapture:
  ([@bs.as "offline"] _, Dom.event => unit, [@bs.as {json|true|json}] _) =>
  unit =
  "removeEventListener";

include NavigatorTypesRe;