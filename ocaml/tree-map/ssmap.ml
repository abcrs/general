(* ssmap.ml: Provides types and functions for a map from string keys
   to string values. Internally uses a binary search tree sorted on
   the keys. *)

open Printf;;

(* Algebraic type for a persistent binary search tree key/value
   mappings.
*)
type ssmap =
  | Empty               (* no data: bottom of tree   *)
  | Node of {           (* node of anonymous record  *)
      key   : string;   (* key for this node         *)
      value : string;   (* value associated with key *)
      left  : ssmap;    (* left branch               *)
      right : ssmap;    (* right branch              *)
    }
;;

(* Empty map value. Could use Ssmap.Empty but it is standard libary
   convention to provide a binding called "empty" for this. *)
let empty = Empty;;

(* val add : ssmap -> string-> string -> ssmap

   let newmap = add map key value in ...

   Returns a new map with key bound to value. If key is already
   present, its binding is re-assigned to the given value.
*)
let rec add map key value =
  match map with
  | Empty ->                                             (* bottom of tree: didn't find *)
     Node{key=key; value=value;                          (* make a new node with key/val binding *)
          left=Empty; right=Empty}
  | Node(node) ->                                        (* at a node *)
     let diff = String.compare key node.key in           (* compute a difference *)
     if diff = 0 then                                    (* 0 indicates equal *)
       Node{node with value=value}                       (* replace value binding with new value *)
     else if diff < 0 then                               (* negative indicates str less than data *)
       Node{node with left=(add node.left key value)}    (* create a new node with new left branch *)
     else                                                (* positive indicates str greater than data *)
       Node{node with right=(add node.right key value)}  (* create new node with new right branch *)
;;

(* val tree_string : ssmap -> string

   let s = tree_string map in ...

   Use a Buffer (extensible string) and a right-to-left in-order
   traversal of the internal tree to construct a string version of the
   map. Nodes are indented according to their depth: root is left-most
   with children farther to the right. Each data element is preceded
   by its integer depth. Right-most elements appear at the top while
   left-most elements appear at the bottom. This means elements read
   in REVERSE order from top to bottom and that mentally rotating the
   tree clockwise gives appropriate left/right branch positions.
*)
let tree_string map =
  let buf = Buffer.create 256 in                    (* extensibel character buffer *)

  let rec build tree depth =                        (* recursive helper *)
    match tree with
    | Empty -> ()                                   (* out of tree, done with this branch *)
    | Node(node) ->                                 (* have a node *)
       build node.right (depth+1);                  (* recurse on right branch *)
       for i=1 to depth do                          (* indent according to depth of this node *)
         Buffer.add_string buf "  ";
       done;
       let datastr =                                (* string with depth and data  *)
         sprintf "%2d: {%s -> %s}\n" depth node.key node.value
       in
       Buffer.add_string buf datastr;               (* add to buffer *)
       build node.left (depth+1);                   (* recurse on left branch *)
  in                                                (* end helper *)

  build map 0;                                      (* recurse from root *)
  Buffer.contents buf                               (* return string from Buffer *)
;;

(* Uses match/with to determine if map is empty, returns None if it is
   Otherwise checks key with current node.key
   Returns Some node.value if it is a match
   Looks down left (if key<node.key) or right (if key>node.key) branch if not a match
*)
let rec getopt map key =
  match map with
  | Empty       -> None
  | Node(node)  -> let diff = String.compare key node.key in
                   if diff = 0 then
                     Some node.value
                   else if diff < 0 then
                     getopt node.left key
                   else
                     getopt node.right key
;;

(* Uses getopt to find if a match exists, returns true if it does false if not *)
let contains_key map str =
  if (getopt map str) = None then false else true
;;

(* Uses match/with to determine if node empty, returns () if it is
   Otherwise uses iter func on node.left, then uses func on current node's key/value
   Then uses iter func on node.right to traverse the map in order
*)
let rec iter func map =
  match map with
  | Empty      -> ()
  | Node(node) ->
      iter func node.left;
      func node.key node.value;
      iter func node.right
;;

(* Same as iter function, except has a return value not unit, so it returns cur when empty
   Binds call to node.left, then uses that value and binds func call on current key/value
   Then uses this value during call to node.right, and returns the result after the right branch traversal
*)
let rec fold func cur map =
  match map with
  | Empty      -> cur
  | Node(node) ->
      let left_cur = fold func cur node.left in
      let new_cur = func left_cur node.key node.value in
      let right_branch = fold func new_cur node.right in
      right_branch
;;

(* Builds string with Buffer, starts with "["
   Helper function builds values for each key/value pair in tree
   Adds "]" on the end, and removes extraneous ", " if it exists
*)
let to_string map =
  let buf = Buffer.create 256 in
  let rec build tree =
    match tree with
    | Empty -> ()
    | Node(node) ->
       build node.left;
       let k_v_str = sprintf "{%s -> %s}, " node.key node.value in
       Buffer.add_string buf k_v_str;
       build node.right
  in
  Buffer.add_string buf "[";
  build map;
  let len = Buffer.length buf in
  if len = 1 then                       (* This is the case where map is empty *)
    Buffer.add_string buf "]"
  else
    begin                               (* Map wasn't empty, and an extra ", " exists *)
      Buffer.truncate buf (len-2);
      Buffer.add_string buf "]";
    end;
  Buffer.contents buf
;;

(* Uses match/with to determine if map is empty, raises exception if it is
   Otherwise looks at node.left to determine if current node is a leaf, returns node.key,node.value if it is
   If branch continues, call findmin_keyval on node.left
*)
let rec findmin_keyval map =
  match map with
  | Empty      -> failwith "No minimum in an empty tree"
  | Node(node) ->
      if node.left = Empty then
        (node.key,node.value)
      else
        findmin_keyval node.left
;;

(* Uses match/with to determine if map is empty, returns map if it is
   Compares key parameter with node.key, and travels down left branch if it is less than, or right branch if it is greater than
   If key = node.key, determines if current node is a leaf or has branches with a second match/with
   If it has just one branch, replace current node with that branch
   If it has two branches, finds the minimum key on the right branch, replaces current node with that key/value
   Then removes that minimum key/value node from the map
*)
let rec remove_key map key =
  match map with
  | Empty       -> map          (* Empty map means empty was passed in, or they key passed in doesn't exist in map *)
  | Node(node)  ->
    let diff = String.compare key node.key in
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
