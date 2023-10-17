(* Scrivere una funzione sum n che calcoli ricorsivamente la somma di tutti i numeri da 0 a n. Usarla poi per calcolare sum 1000000 *)

let rec sum_acc a n =
    if n = 1 then a else sum_acc (a+n) (n-1) in
let sum = (sum_acc 0) in

print_int(sum 1000000);;
