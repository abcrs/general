open Printf;;

module StringStringKV = struct
  type key_t = string;;
  type value_t = string;;
  let compare_keys = String.compare;;       (* Simply uses String.compare *)
  let keyval_string key value = sprintf "{%s -> %s}" key value;;
end;;

module StringStringMap = Treemap.Make(StringStringKV);;

module IntpairBoolKV = struct
  type key_t = int * int;;
  type value_t = bool;;
  let compare_keys key1 key2 =
    match key1,key2 with
    | (a,c),(b,d) when a = b -> c - d       (* If the first ints in they keys are equal, uses second ints to compare *)
    | (a,_),(b,_)            -> a - b;;     (* Otherwise just compares the first int in each key to the other *)
  let keyval_string key value =
    match key with
    | (a,b) -> sprintf "{%d > %d : %b}" a b value;;
end;;

module IntpairBoolMap = Treemap.Make(IntpairBoolKV);;
