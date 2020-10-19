(* multimanager.ml : main function to allow manipulation of multiple
   lists of sorted, unique elements.  *)

open Printf;;

(* Help string to be printed for the "help" command. *)
let help_string =
  let lines = [
      "MULTI MANAGER";
      "Maintains multiple sorted lists of unique elements..";
      "";
      "--PROGRAM COMMANDS--:";
      "  help           : print this help message";
      "  quit           : quit the program";
      "";
      "--CURRENT LIST COMMANDS--";
      "The following commands modify the current list";
      "  show           : print the current list to the screen";
      "  clear          : set the list to empty, preserves undo history";
      "  add <elem>     : add elem to the list";
      "  remove <elem>  : remove elem from list";
      "  mergein <file> : load the sorted list in the named file and merge with current list (undoable)";
      "  save           : save the current list using the name of the list as the save file";
      "  saveas <file>  : save the current list to the given file name; keeps the list name the same";
      "  undo           : undo the last operation restoring list to a previous state";
      "  redo           : redo the last undone operation restoring list to a previous state";
      "";
      "--LIST MANAGEMENT COMMANDS--";
      "The following commands will fail if a list name is already in use (new/open) or no present (close/edit/merge)";
      "  lists          : prints the lists that are currently open";
      "  edit <list>    : set the named list to the current list";
      "  new <list>     : create a new empty list and switch to it";
      "  open <file>    : create a new list named after the file specified; load the contents of the file into it and switch to it";
      "  close <list>   : close the list with given name and remove it from the open documents; cannot close the current list";
      "  merge <list>   : merge the named list contents into the current list";
      "";
      "--BULK OPERATIONS--";
      "The following commands act upon all open lists";
      "  showall        : print all lists labelled with their list name";
      "  saveall        : save all open lists; use filenames identical the list names (not undoable)";
      "  addall <elem>  : add elem to all open lists; each list can undo this individually";
      "  mergeall       : merge the contents of all lists into the current list; undoable";
    ] in
  String.concat "\n" lines
;;

(* Tracks the global state associated with the application. This
   binding uses a series of statements to initialize the global state
   to have a default empty list named 'default.txt' which is the
   current document and the only entry in the doccol. *)
let global : string list Doccol.doccol =
  let default_doc = Document.make [] in
  let default_name = "default.txt" in
  Doccol.make default_name default_doc
;;

(* Set to true to end execution of the program *)
let quit_now = ref false;;

(* val execute_command : string array -> unit
   Execute a single command which is the 0th element of the argument
   array tokens.  If the command has additional parameters these will
   be in tokens.(1), tokens.(2), etc.  Makes use of functions in Util,
   Sortedlist, Document, doccol, and Bulkops to implement each
   command. *)
let rec execute_command tokens =
  let cmd = tokens.(0) in       (* 0th element is command *)
  match cmd with
  (* ---PROGRAM COMMANDS-- *)
  | "help" ->
     printf "%s\n" help_string;
  | "quit" ->
     quit_now := true;

  (* --CURRENT LIST COMMANDS-- *)
  (* Each command makes use of either Sortedlist.insert, Sortedlist.remove, Sortedlist.merge,
     Util.strlist_to_file, Util.strlist_from_file, or a combination of methods to create a new list.
     This new list is set as the curdoc.current using Document.set in the case of insert, remove, and merge, and strlist_from_file. Util.strlist_to_file saves a new file.
     Also has ability to undo or redo the last command, but checks to make sure undo/redo is possible, otherwise prints error. *)
  | "show" ->
     printf "--BEG LIST--\n";
     Sortedlist.print global.curdoc.current;
     printf "--END LIST--\n";
  | "clear" ->
     Document.set global.curdoc [];
  | "add" ->
     let new_list = Sortedlist.insert global.curdoc.current tokens.(1) in
     Document.set global.curdoc new_list;
  | "remove" ->
     let new_list = Sortedlist.remove global.curdoc.current tokens.(1) in
     Document.set global.curdoc new_list;
  | "save" ->
     Util.strlist_to_file global.curdoc.current global.curname;
  | "saveas" ->
     Util.strlist_to_file global.curdoc.current tokens.(1);
  | "load" ->
     let new_list = Util.strlist_from_file tokens.(1) in
     Document.set global.curdoc new_list;
  | "mergein" ->
     let new_list = Util.strlist_from_file tokens.(1) in
     let big_list = Sortedlist.merge new_list global.curdoc.current in
     Document.set global.curdoc big_list;
  | "undo" ->
    let test = Document.undo global.curdoc in
    if test = false then
      printf "WARNING: undo list empty, no changes made\n";
  | "redo" ->
  let test = Document.redo global.curdoc in
  if test = false then
    printf "WARNING: redo list empty, no changes made\n";

  (* --LIST MANAGEMENT COMMANDS-- *)
  (* Each command uses Doccol functions to execute.
     edit, new, and open use Doccol.switch to change the currently available document.
     Close closes some other document that is not the currently open one.
     Merge merges another document's current list with the current document.
     Each command (other than lists) checks to make sure the command can actually be executed before executing,
     as to not raise any exceptions or create any errors. *)
  | "lists" ->
    let str = Doccol.string_of_doccol global in
    Printf.printf "%s" str;
  | "edit" ->
    (let test = Doccol.switch global tokens.(1) in
    match test with
    | true  ->  ()
    | false ->  Printf.printf "ERROR: list '%s' does not exist\n" tokens.(1);)
  | "new" ->
    (let test = Doccol.has global tokens.(1) in
    match test with
    | true  ->  Printf.printf "ERROR: list '%s' already exists\n" tokens.(1);
    | false ->  let new_doc = Document.make [] in
                ignore(Doccol.add global tokens.(1) new_doc);
                ignore(Doccol.switch global tokens.(1));)
  | "open" ->
    (let test = Doccol.has global tokens.(1) in
    match test with
    | true  ->  printf "ERROR: list '%s' already exists\n" tokens.(1);
    | false ->  let new_list = Util.strlist_from_file tokens.(1) in
                let new_doc = Document.make new_list in
                ignore(Doccol.add global tokens.(1) new_doc);
                ignore(Doccol.switch global tokens.(1));)
  | "close" ->
    (let test = Doccol.has global tokens.(1) in
    if tokens.(1) = global.curname then
      (Printf.printf "ERROR: cannot close the current list\n";)
    else
      match test with
      | false ->  Printf.printf "ERROR: list '%s' does not exist\n" tokens.(1);
      | true  ->  ignore(Doccol.remove global tokens.(1));)
  | "merge" ->
    (let test = Doccol.has global tokens.(1) in
    match test with
    | false ->  Printf.printf "ERROR: list '%s' does not exist\n" tokens.(1);
    | true  ->  let merge_list = List.assoc tokens.(1) global.docs in
                let big_list = Sortedlist.merge (global.curdoc.current) (merge_list.current) in
                Document.set global.curdoc big_list;)

  (* --BULK OPERATIONS-- *)
  (* Each command uses a Bulkops function to execute, most by simply calling that function with the global doccol.
     mergeall holds the return value from the Bulkops.mergeall, and then merges it with the current list using Sortedlist.merge.
     This second merge could be redundant, but will account for the current list having been edited.
     Then uses Document.set to make the current list this new, merged list. *)
  | "showall" ->
    Bulkops.showall global;
  | "saveall" ->
    Bulkops.saveall global;
  | "addall" ->
    Bulkops.addall global tokens.(1);
  | "mergeall" ->
    let bigger_list = Bulkops.mergeall global in
    let biggest_list = Sortedlist.merge (global.curdoc.current) bigger_list in
    Document.set global.curdoc biggest_list;

  (* Catch-all *)
  | _ ->
     printf "Unknown command '%s'\n" tokens.(0)
;;

(*********************************************************************************
   Code beyond this point should not require modification though it
   may be interesting to examine.
*)
let echo  = ref false;;         (* command echoing on/off  *)
let debug = ref false;;         (* turn on/off debug printing *)

(* Options accepted by the program *)
let options = Arg.([
  ("-echo",  Set(echo),  "Turn on command echoing (default: off)");
  ("-debug", Set(debug), "Turn on debug printing  (default: off)");
]);;

(* Do nothing with extra command line arguments *)
let handle_extra_args arg = ();;

(* Simple usage message for Arg.parse *)
let usage = sprintf "usage: %s [options]" Sys.argv.(0);;

(* main routine *)
let _ =
  Arg.parse options handle_extra_args usage;    (* parse command line options *)
  begin try
      while !quit_now = false do                (* loop until quit command is issued *)
        printf "(%s)> " global.curname;         (* print prompt *)
        let line = read_line () in              (* read a line of input from stdin *)
        if !echo then                           (* if echoing is on, print the line *)
          printf "%s\n" line;
        let tokens =                            (* split line into tokens on spaces *)
          Array.of_list (Str.split (Str.regexp " +") line) in
        let ntok = Array.length tokens in
        if !debug then                          (* possibly print debuggin info on tokens *)
          begin
            printf "'%s' has %d tokens\n" line ntok;
            for i=0 to ntok-1 do
              printf "%d : %s\n" i tokens.(i);
            done
          end;
        if ntok>0 then
          try execute_command tokens;           (* execute a command *)
          with e ->                             (* out of bounds access, file not found, etc. doesn't kill program *)
            let excstring = Printexc.to_string e in
            printf "Error with '%s': %s\n" line excstring;
      done;
    with
    | End_of_file -> ()                         (* end of input reached *)
  end;
  printf "\nLists multi-managed!\n";
;;