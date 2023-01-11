(* Scrivere una funzione ordered l che restituisca true se e solo se l è una lista ordinata. *)

let rec ordered l =
    match l with
    | [] -> true
    | e::[] -> true
    | a::b::ls -> if a <= b then ordered ls else false
;;

let print_bool b =
    if b then print_string "true\n" else print_string "false\n"
;;

print_bool (ordered [1; 2; 4; 10]);;
print_bool (ordered [1; 2; 11; 10]);;
