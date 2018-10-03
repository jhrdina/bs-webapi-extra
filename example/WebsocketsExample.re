open WebapiExtra;

let readyStateToString =
  fun
  | Dom.WebSocket.Connecting => "Connecting"
  | Open => "Open"
  | Closing => "Closing"
  | Closed => "Closed"
  | Unknown => "Unknown";

let run = () => {
  open Dom.WebSocket;
  let ws = create("ws://localhost:7777");
  Js.log("WS created... " ++ (ws->readyState |> readyStateToString));
  ws
  ->setOnMessage(e => {
      Js.log(e);
      Js.log("WS message received: " ++ e->Dom.MessageEvent.data);
    });
  ws
  ->setOnError(e => {
      Js.log(e);
      Js.log("WS error..." ++ (ws->readyState |> readyStateToString));
    });
  ws
  ->setOnOpen(_ =>
      Js.log("WS opened... " ++ (ws->readyState |> readyStateToString))
    );
  ws->setOnClose(e => Js.log(e));
  open Webapi.Dom;
  let maybeBtn = document |> Document.getElementById("send-ws-msg-btn");
  switch (maybeBtn) {
  | Some(btn) =>
    btn |> Element.addClickEventListener(_ => ws->sendString("Hello"))
  | None => ()
  };
};