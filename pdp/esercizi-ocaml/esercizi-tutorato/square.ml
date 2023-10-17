(* Scrivere una funzione square_evens l che prende una lista l e restituisce una lista l', contenente solo gli elementi pari di l, elevati al quadrato. *)

let rec square_evens l =
    match l with
    | [] -> []
    | e::es -> if (e mod 2) = 0 then (e*e)::(square_evens es) else (square_evens es)
in
let rec print_int_list l =
    match l with
    | [] -> ()
    | e::es -> print_int e ; print_string "\n" ; print_int_list es
in

print_int_list (square_evens [4; 1; 5; 4; 10])
;; 
