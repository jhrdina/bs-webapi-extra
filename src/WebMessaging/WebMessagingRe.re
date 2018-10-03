module MessageEvent = {
  module Impl = (T: {type t;}) => {
    /* TODO: Support other data types */
    [@bs.get] external data: T.t => string = "";
    [@bs.get] external origin: T.t => string = "";
    [@bs.get] external lastEventId: T.t => string = "";
    /* [@bs.get] external source: T.t => Dom.messagePort = ""; */
    /* [@bs.get] external ports: T.t => array(Dom.messagePort) = ""; */
  };

  type t = WebMessagingTypesRe.messageEvent;

  include Webapi.Dom.Event.Impl({
    type nonrec t = t;
  });
  include Impl({
    type nonrec t = t;
  });

  [@bs.new] external make: string => t = "MessageEvent";
  [@bs.new]
  external makeWithOptions: (string, Js.t({..})) => t = "MessageEvent";
};

include WebMessagingTypesRe;