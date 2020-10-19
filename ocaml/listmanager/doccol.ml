(* doccol.ml: Type and functions for a collection of named documents.
   Tracks a current document and its name along with an association
   list of all docs in the collection.  Preserves uniqueness of names
   in the collection. Makes use of built-in List functions to
   ad/remove/get docs from the association list. *)

(* Type to track a collection of named documents in an association
   list. *)

open Document

type 'a doccol = {
  mutable count   : int;                                  (* count of docs in list *)
  mutable curdoc  : 'a Document.document;                 (* current list being edited *)
  mutable curname : string;                               (* name of current list *)
  mutable docs    : (string * 'a Document.document) list; (* association list of names/docs *)
};;

(* Creates a new doccol with initialized values using the passed in parameters as the curdoc and curname.
   Uses 1 as the count, and creates an association list with 1 element that is the passed in name,doc.
   Returns the new doccol. *)
let make name doc =
  let doccol = {count = 1;
                curdoc = doc;
                curname = name;
                docs = [(name,doc)]}
  in
  doccol
;;

(* Adds a new doc to the passed in doccol.
   Checks if passed in name exists in doccol.docs association list. If it is, return false.
   If it is not in the list, increment the count and create new doccol.docs association list
   with the passed in name,doc as the head. Return true.
   Makes use of mutable data types and the <- assignment operator to update a document. *)
let add doccol name doc =
  let test = List.assoc_opt name doccol.docs in
  match test with
  | Some _  ->  false
  | None    ->  begin
                  doccol.count <- doccol.count+1;
                  doccol.docs <- (name,doc)::doccol.docs;
                  true
                end;
;;

(* Removes a doc from the passed in doccol.
   Checks if the passed in name is either the curdoc or does not exist in the doccol.docs
   association list. If either of those are true, return false.
   If the name does exist in the association list,
   use List.remove_assoc to remove that element from the list. Return true.
   Makes use of mutable data types and the <- assignment operator to update a document. *)
let remove doccol name =
  if doccol.curname = name then
    false
  else
    begin
      let test = List.assoc_opt name doccol.docs in
      match test with
      | None    ->  false
      | Some _  ->  begin
                      doccol.count <- doccol.count-1;
                      doccol.docs <- List.remove_assoc name doccol.docs;
                      true
                    end;
    end;
;;

(* Uses List.assoc_opt to determine if passed in name exists in the doccol.docs association list.
   Returns true if it is found, and false if it is not. *)
let has doccol name =
  let test = List.assoc_opt name doccol.docs in
  match test with
  | None    ->  false
  | Some _  ->  true
;;

(* Switches the doccol.curname and doccol.curdoc with the passed in name.
   Searches for the passed in name in the doccol.docs association list, returns false if not found.
   If it is found, uses that name as the new doccol.curname. Uses List.assoc to find the document value
   associated with the passed in name, and sets that as the doccol.curdoc. Returns true.
   Makes use of mutable data types and the <- assignment operator to update a document. *)
let switch doccol name =
  let test = List.assoc_opt name doccol.docs in
  match test with
  | None    ->  false
  | Some _  ->  begin
                  doccol.curname <- name;
                  doccol.curdoc <- List.assoc name doccol.docs;
                  true
                end;
;;

(* Creates a string of the total number of docs in the doccol and all of the names contained in the doccol.
   Uses List.fold_left to turn the doccol.docs association list into a list of names, each on their own line.
   Concats the number of docs string and list of names, and returns result string. *)
let string_of_doccol doccol =
  let names = List.fold_left (fun sent (w,_)-> sent^(Printf.sprintf "- %s\n" w)) "" doccol.docs in
  let num = Printf.sprintf "%d docs\n" doccol.count in
  num^names
;;
