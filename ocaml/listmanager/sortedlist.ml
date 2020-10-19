(* Inserts element in order into the list
   If it arrives at the end of the list, simply adds the element to the end
   If it is a duplicate of an element in the list, returns the original list.
   The last pattern matched is assumed to be elem > hd,
   so the function is recursively called on just the tail to continue checking. *)
let rec insert list elem =
  match list with
  | []                      ->  [elem]
  | hd :: tl when elem < hd ->  elem :: hd :: tl
  | hd :: tl when elem = hd ->  list
  | hd :: tl                ->  hd :: (insert tl elem)
;;

(* Searches through list and removes element if found.
   If end of list is reached, return original list.
   If the current hd value is greater than the element, the element must not be in the list,
     so the original list can be returned.
   The last pattern matched assumes the element is greater than the current hd,
     so the function is recursively called on just the tail to continue checking. *)
let rec remove list elem =
  match list with
  | []                      -> []
  | hd :: tl when elem = hd -> tl
  | hd :: tl when elem < hd -> list
  | hd :: tl                -> hd :: (remove tl elem)
;;

(* Prints a list line by line. If the list is empty, returns unit.
   If there is more than just the hd on the list, print the hd
     and call print again on the tl. *)
let rec print strlist =
  match strlist with
  | []        ->  ()
  | hd :: []  ->  Printf.printf "%s\n" hd;
  | hd :: tl  ->  Printf.printf "%s\n" hd; print tl
;;

(* Merges two lists together, one element at a time have the result list be in order.
   If one list is empty, simply add the rest of the other list to the end of the result list.
   If the hds of both lists are the same, add one to the result list and ignore the other one.
     This removes duplicates from the result list.
   If lista's head is less than listb's head, add lista's head to the result list.
     Then call merge again with lista's tail and the entirety of listb.
   The last pattern assumes that listb's head is less than lista's head,
     because any other result would've already matched.
     Add listb's head to the result list and call merge with listb's tail and all of lista. *)
let rec merge lista listb =
  match lista,listb with
  | ([],[])                             ->  []
  | [],(bhd::btl)                       ->  listb
  | (ahd::atl),[]                       ->  lista
  | (ahd::atl),(bhd::btl) when ahd<bhd  ->  ahd :: (merge atl listb)
  | (ahd::atl),(bhd::btl) when ahd=bhd  ->  ahd :: (merge atl btl)
  | (ahd::atl),(bhd::btl)               ->  bhd :: (merge lista btl)
;;
