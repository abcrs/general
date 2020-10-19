(* Type of key/vals that go into Treemaps. Includes key and value
   type, key comparison function, and a string function for easy
   display. *)
module type KEYVAL_SIG =
sig
  type key_t
  type value_t
  val compare_keys : key_t -> key_t -> int
  val keyval_string : key_t -> value_t -> string
end

module Make (KVMod : KEYVAL_SIG) =
struct
  type treemap =
      | Empty
      | Node of {
            key   : KVMod.key_t;
            value : KVMod.value_t;
            left  : treemap;
            right : treemap;
          }
  ;;

  let empty = Empty;;

  let rec add map key value =
    match map with
    | Empty ->
       Node{key=key; value=value;
            left=Empty; right=Empty}
    | Node(node) ->
       let diff = KVMod.compare_keys key node.key in
       if diff = 0 then
         Node{node with value=value}
       else if diff < 0 then
         Node{node with left=(add node.left key value)}
       else
         Node{node with right=(add node.right key value)}
  ;;

  let tree_string map =
    let buf = Buffer.create 256 in

    let rec build tree depth =
      match tree with
      | Empty -> ()
      | Node(node) ->
         build node.right (depth+1);
         for i=1 to depth do
           Buffer.add_string buf "  ";
         done;
         let temp_string = KVMod.keyval_string node.key node.value in   (* Creates a temp string to make use of the keyval_string function *)
         let datastr =
           Printf.sprintf "%2d: %s\n" depth temp_string
         in
         Buffer.add_string buf datastr;
         build node.left (depth+1);
    in

    build map 0;
    Buffer.contents buf
  ;;

  let rec getopt map key =
    match map with
    | Empty       -> None
    | Node(node)  -> let diff = KVMod.compare_keys key node.key in
                     if diff = 0 then
                       Some node.value
                     else if diff < 0 then
                       getopt node.left key
                     else
                       getopt node.right key
  ;;

  let contains_key map str =
    if (getopt map str) = None then false else true
  ;;

  let rec iter func map =
    match map with
    | Empty      -> ()
    | Node(node) ->
        iter func node.left;
        func node.key node.value;
        iter func node.right
  ;;

  let rec fold func cur map =
    match map with
    | Empty      -> cur
    | Node(node) ->
        let left_cur = fold func cur node.left in
        let new_cur = func left_cur node.key node.value in
        let right_branch = fold func new_cur node.right in
        right_branch
  ;;

  let to_string map =
    let buf = Buffer.create 256 in
    let rec build tree =
      match tree with
      | Empty -> ()
      | Node(node) ->
         build node.left;
         let temp_string = KVMod.keyval_string node.key node.value in   (* Creates a temp string to make use of the keyval_string function *)
         let k_v_str = Printf.sprintf "%s, " temp_string in
         Buffer.add_string buf k_v_str;
         build node.right
    in
    Buffer.add_string buf "[";
    build map;
    let len = Buffer.length buf in
    if len = 1 then
      Buffer.add_string buf "]"
    else
      begin
        Buffer.truncate buf (len-2);
        Buffer.add_string buf "]";
      end;
    Buffer.contents buf
  ;;

  let rec findmin_keyval map =
    match map with
    | Empty      -> failwith "No minimum in an empty tree"
    | Node(node) ->
        if node.left = Empty then
          (node.key,node.value)
        else
          findmin_keyval node.left
  ;;

  let rec remove_key map key =
    match map with
    | Empty       -> map
    | Node(node)  ->
      let diff = KVMod.compare_keys key node.key in
      if diff < 0 then
        Node{node with left=(remove_key node.left key)}
      else if diff > 0 then
        Node{node with right=(remove_key node.right key)}
      else
        begin
          match (node.left,node.right) with
          | (Empty,Empty)     -> Empty
          | (left_n,Empty)    -> left_n
          | (Empty,right_n)   -> right_n
          | (left_n,right_n)  ->
            let (new_key,new_value) = findmin_keyval right_n in
            Node{key=new_key; value=new_value; left=left_n; right=(remove_key right_n new_key)}
        end;
  ;;
end
