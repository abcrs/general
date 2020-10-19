module type ELEM_SIG = sig
  type element;;
  val compare : element -> element -> int;;
  val elem_string : element -> string;;
end;;

module Make (ElMod : ELEM_SIG) =
struct

  module ElemKeyVal = struct
    type key_t = ElMod.element;;
    type value_t = ();;                                           (* value_t is not important, and thus can be type unit *)
    let compare_keys = ElMod.compare;;
    let keyval_string key_t value_t = ElMod.elem_string key_t;;   (* Because value is not important, a call is made to ElMod.elem_string with just key_t *)
  end

  module ElTreemap = Treemap.Make(ElemKeyVal);;             (* ElTreemap is made using the Treemap.Make functor and the ElemKeyVal defined above *)

  let empty = ElTreemap.empty;;

  let add set elem = ElTreemap.add set elem ();;            (* The value passed in is unit, because, again, not relevant to the sets *)

  let tree_string set = ElTreemap.tree_string set;;         (* ElTreemap.tree_string can simply be called passing set as the map *)

  let getopt set elem =                                     (* Because value is type unit, and getopt returns Some value, some changing needs to happen *)
    let test_opt = ElTreemap.getopt set elem in             (* If ElTreemap.getopt returns Some (), that means a match is found *)
      match test_opt with                                   (* Using match/with, we then can return Some elem if Some () is returned from getopt*)
      | Some _ -> Some elem
      | None   -> None
  ;;

  let contains set elem = ElTreemap.contains_key set elem;; (* ElTreemap.contains_key can simply be called passing set as the map and elem as the key *)

  let iter func set =
    let helper key_t value_t = func key_t in                (* To satisfy the requirements of ElTreemap.iter, a helper function is made *)
    ElTreemap.iter helper set                               (* It takes the value_t, but does nothing with it, instead just using the func and key_t from the set *)
  ;;

  let fold func init set =
    let helper init key_t value_t = func init key_t in      (* Similar to iter, fold uses a helper to ignore the value but still get the desired output *)
    ElTreemap.fold helper init set
  ;;

  let to_string set = ElTreemap.to_string set;;             (* ElTreemap.to_string can simply be called passing set as the map *)

  let remove set elem = ElTreemap.remove_key set elem;;     (* ElTreemap.remove_key can simply be called passing set as the map and elem as the key *)
end;;

(* Random question: are comments preferred in the style used in this file (to the right of the functions, explaining lines)
   Or are they preferred in the style I used in ssmap.ml, where the function is explained in a comment block before the definition of the function?
*)
