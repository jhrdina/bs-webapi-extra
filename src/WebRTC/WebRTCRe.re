module RTCIceCandidate = {
  type t;
  [@bs.new] external create: unit => t = "RTCIceCandidate";
};

module RTCPeerConnectionIceEvent = {
  type t;
  [@bs.get] external getCandidate: t => RTCIceCandidate.t = "candidate";
};

module RTCIceConnectionStateChangeEvent = {
  type t;
  [@bs.get] external getIceConnectionState: t => string = "iceConnectionState";
};

module RTCErrorEvent = {
  type t;
  [@bs.get] external getMessage: t => string = "message";
};

module RTCMessageEvent = {
  type t;
  [@bs.get] external getData: t => string = "data";
  [@bs.get] external getMessage: t => string = "message";
};

module RTCDataChannel = {
  type t;
  type optionsT;
  [@bs.set]
  external setOnError: (t, RTCErrorEvent.t => unit) => unit = "onerror";
  [@bs.set] external setOnOpen: (t, unit => unit) => unit = "onopen";
  [@bs.set] external setOnClose: (t, unit => unit) => unit = "onclose";
  [@bs.set]
  external setOnMessage: (t, RTCMessageEvent.t => unit) => unit = "onmessage";
  [@bs.send] external send: (t, string) => unit = "send";
  [@bs.obj]
  external makeOptions: (~ordered: bool, ~maxRetransmitTime: float) => optionsT =
    "";
};

module RTCDataChannelEvent = {
  type t;
  [@bs.get] external getChannel: t => RTCDataChannel.t = "channel";
};

module RTCOffer = {
  type t;
  type optionsT;
  [@bs.obj]
  external makeOptions:
    (~offerToReceiveAudio: bool, ~offerToReceiveVideo: bool) => optionsT =
    "";
};

module RTCSdpType = {
  type t =
    | Offer
    | Pranswer
    | Answer
    | Rollback
    | Unknown;

  let encode =
    fun
    | Offer => "offer"
    | Pranswer => "pranswer"
    | Answer => "answer"
    | Rollback => "rollback"
    | Unknown => "";

  let decode =
    fun
    | "offer" => Offer
    | "pranswer" => Pranswer
    | "answer" => Answer
    | "rollback" => Rollback
    | _ => Unknown;
};

module RTCIceConnectionState = {
  type t =
    | New
    | Checking
    | Connected
    | Completed
    | Disconnected
    | Failed
    | Closed
    | Unknown;

  let encode =
    fun
    | New => "new"
    | Checking => "checking"
    | Connected => "connected"
    | Completed => "completed"
    | Disconnected => "disconnected"
    | Failed => "failed"
    | Closed => "closed"
    | Unknown => "";

  let decode =
    fun
    | "new" => New
    | "checking" => Checking
    | "connected" => Connected
    | "completed" => Completed
    | "disconnected" => Disconnected
    | "failed" => Failed
    | "closed" => Closed
    | _ => Unknown;
};

module RTCSessionDescription = {
  type t;
  [@bs.get] external getType: t => string = "type";
  let getType = t => RTCSdpType.decode(getType(t));
  [@bs.get] external sdp: t => string = "";
};

module RTCConfiguration = {
  type rtcIceServer = {. "urls": string};
  type t = {. "iceServers": array(rtcIceServer)};
};

module RTCPeerConnection = {
  type t;
  [@bs.new] external create: unit => t = "RTCPeerConnection";
  [@bs.new]
  external createWithConfig: RTCConfiguration.t => t = "RTCPeerConnection";
  [@bs.set]
  external setOnIceCandidate: (t, RTCPeerConnectionIceEvent.t => unit) => unit =
    "onicecandidate";
  [@bs.set]
  external setOnIceConnectionStateChange:
    (t, RTCIceConnectionStateChangeEvent.t => unit) => unit =
    "oniceconnectionstatechange";
  [@bs.set]
  external setOnDataChannel: (t, RTCDataChannelEvent.t => unit) => unit =
    "ondatachannel";
  [@bs.send]
  external addIceCandidate:
    (t, RTCIceCandidate.t) => Js_promise.t(unit) /*string*/ =
    "addIceCandidate";
  [@bs.send]
  external createDataChannel:
    (t, ~channelName: string, ~options: RTCDataChannel.optionsT) =>
    RTCDataChannel.t =
    "createDataChannel";
  [@bs.send]
  external createOffer:
    (t, ~options: RTCOffer.optionsT) => Js_promise.t(RTCSessionDescription.t) /*string*/ =
    "createOffer";
  [@bs.send]
  external createDefaultOffer: t => Js_promise.t(RTCOffer.t) /*string*/ =
    "createOffer";
  [@bs.send]
  external createAnswer: t => Js_promise.t(RTCSessionDescription.t) /*string*/ =
    "createAnswer";
  [@bs.send]
  external setLocalDescription:
    (t, RTCSessionDescription.t) => Js_promise.t(unit) /*string*/ =
    "setLocalDescription";
  [@bs.get] external localDescription: t => RTCSessionDescription.t = "";
  [@bs.send]
  external setRemoteDescription:
    (t, RTCSessionDescription.t) => Js_promise.t(unit) /*string*/ =
    "setRemoteDescription";
  [@bs.get] external remoteDescription: t => RTCSessionDescription.t = "";
  [@bs.get] external iceConnectionState: t => string = "";
  let iceConnectionState = t =>
    iceConnectionState(t) |> RTCIceConnectionState.decode;
  [@bs.send] external close: t => unit = "close";
};