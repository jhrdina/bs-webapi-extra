type t = CommonDomInterfacesTypesRe.domStringList;

[@bs.get] external length: t => int = "";
[@bs.send.pipe: t] external item: int => string = "";
[@bs.send.pipe: t] external contains: string => bool = "";