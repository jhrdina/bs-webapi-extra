open WebapiExtra.Dom;

let run = () => {
  let window = Webapi.Dom.window;
  Js.log2("Navigator onLine:", window |> navigator |> Navigator.onLine);
  window->setOnOnline(_ => Js.log("Got online"));
  window->setOnOffline(_ => Js.log("Got offline"));
};