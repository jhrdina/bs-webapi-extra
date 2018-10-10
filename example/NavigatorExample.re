open WebapiExtra.Dom;

let run = () => {
  let window = Webapi.Dom.window;
  Js.log2("Navigator onLine:", window |> navigator |> Navigator.onLine);
  window |> addOnlineEventListener(_ => Js.log("Got online"));
  window |> addOfflineEventListener(_ => Js.log("Got offline"));
};