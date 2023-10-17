(* Write a function last : 'a list -> 'a option that returns the last element of a list *)
let rec last list =
    match list with
    | [] -> None
    | e::[] -> Some (e)
    | w::ws -> last ws
;;

last ["a" ; "b" ; "c" ; "d"];;
last [];;
