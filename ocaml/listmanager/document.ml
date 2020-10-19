(* document.ml: Defines a "document" type which tracks a current state
   along with undo/redo history.  The document type is polymorphic
   meaning data can be any type such as 'int document' or 'string list
   document'. *)

(* document type declaration. *)
type 'a document = {
    mutable current    : 'a ;       (* current document state *)
    mutable undo_stack : 'a list;   (* past states that can be reached via undo *)
    mutable redo_stack : 'a list;   (* undone states that can be reached via redo *)
};;

let make initial =
  let document = {current = initial;
                  undo_stack = [];
                  redo_stack = []}
  in
  document
;;

(* Adds current as the head of the undo_stack list, and sets the current as the passed in data.
   Makes use of mutable data types and the <- assignment operator to update a document. *)
let set document data =
  document.undo_stack <- document.current::document.undo_stack;
  document.current <- data;
  document.redo_stack <- []
;;

(* If undo_stack is not the empty list, first takes the current and makes it the head of the redo_stack list.
   Then takes the head of the undo_stack and makes it the current. Finally changes the undo_stack list to no longer contain the current,
   which was the head of the previous undo_stack list.
   Makes use of mutable data types and the <- assignment operator to update the document. *)
let undo document =
  if document.undo_stack=[] then
    false
  else
    begin
      document.redo_stack <- document.current::document.redo_stack;
      document.current <- List.hd document.undo_stack;
      document.undo_stack <- List.tl document.undo_stack;
      true
    end;
;;

(* Does essentially the opposite of undo. Takes current and makes it the head of the undo_stack list,
   then takes the head of the redo_stack list and makes it current,
   and then changes the redo_stack list to be just the tail of the previous one.
   Makes use of mutable data types and the <- assignment operator to update a document. *)
let redo document =
if document.redo_stack=[] then
  false
else
  begin
    document.undo_stack <- document.current::document.undo_stack;
    document.current <- List.hd document.redo_stack;
    document.redo_stack <- List.tl document.redo_stack;
    true
  end;
;;
