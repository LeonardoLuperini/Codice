(* Find the last but one (last and penultimate) elements of a list. *)

let rec last_two_v1 list =
    match list with
    | [] -> None
    | a::[] -> None
    | a::b::[] -> Some (a, b)
    | w::ws -> last_two_v1 ws
;;

let rec last_two_v2 list =
    match list with
    | [] | [_] -> None
    | [x; y] -> Some (x, y)
    | _ :: t -> last_two_v2 t
;;

last_two_v1 ["a"; "b"; "c"; "d"];;
last_two_v1 ["a"];;

last_two_v2 ["a"; "b"; "c"; "d"];;
last_two_v2 ["a"];;
