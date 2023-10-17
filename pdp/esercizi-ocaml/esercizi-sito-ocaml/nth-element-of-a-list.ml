(* Find the N'th element of a list *)

let rec nth list n = 
    if List.length list < n then None
    else Some(List.nth list n)
;;

nth ["a"; "b"; "c"; "d"; "e"] 4;;
nth ["a"] 2;;
