module Navigator = {
  type t = NavigatorTypesRe.navigator;

  [@bs.get] external onLine: t => bool = "";
};

[@bs.get]
external navigator: Webapi.Dom.Window.t => NavigatorTypesRe.navigator = "";

[@bs.set]
external setOnOnline: (Webapi.Dom.Window.t, Webapi.Dom.Event.t => unit) => unit =
  "ononline";
[@bs.set]
external setOnOffline:
  (Webapi.Dom.Window.t, Webapi.Dom.Event.t => unit) => unit =
  "onoffline";

include NavigatorTypesRe;