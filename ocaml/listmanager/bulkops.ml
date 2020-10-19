open Document;;
open Doccol;;

(* Uses List.iter to visit every open doc in the doccol parameter passed in.
   Helper function takes tuple and prints the list name,
   and then uses Sortedlist.print to print the associated document lists. *)
let showall doccol =
 let help (nm,dc) =
  Printf.printf "--List %s--\n"nm;
  Sortedlist.print dc.current in
 List.iter help doccol.docs
;;

(* Uses List.iter to save each document to a file, using the associated list name
   as the file name. Helper function uses Util.strlist_to_file to do this. *)
let saveall doccol =
  let help (nm,dc) =
    Util.strlist_to_file dc.current nm in
  List.iter help doccol.docs
;;

(* Uses List.map to transform each list in the passed in doccol by adding one element.
   Helper function sorted-adds the element in using Sortedlist.insert, creating a new list
   Then uses Document.set to add this new list to each document, so that it can be updated.
   Finally, the doccol.docs is updated with these updated documents that have the correct undo/redo lists. *)
let addall doccol elem =
  let help (nm,dc) =
    let updated_list = Sortedlist.insert dc.current elem in
    Document.set dc updated_list;
    (nm,dc) in
  let new_docs = List.map help doccol.docs in
  doccol.docs <- new_docs;
;;

(* Uses List.fold_left to create one giant list from all open lists.
   Helper function starts with an empty list, and then uses Sortedlist.merge
   to keep the large list sorted. Returns the large list. *)
let mergeall doccol =
  let help big_list (nm,dc) =
    let bigger_list = Sortedlist.merge big_list dc.current in
    bigger_list in
  List.fold_left help [] doccol.docs
;;
