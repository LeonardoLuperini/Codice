(* Scrivere una funzione drop n l che prende un intero e una lista, e scarta tutti gli elementi di l con indice multiplo di n. 
Usare sia la ricorsione che fold_left o fold_right *)

let rec drop_index i n l =
    match l with
    | [] -> []
    | e::es -> if (i mod n) = 0 then drop_index (i+1) n es else e::drop_index (i+1) n es
;;

let drop = (drop_index 1)
;;

let rec print_int_list l =
    match l with
    | [] -> ()
    | e::es -> print_int e ; print_string "\n" ; print_int_list es
in

print_int_list (drop 2 [1; 2; 3; 17; 42])
;;

drop 2 [1; 2; 3; 17; 42]
;;
