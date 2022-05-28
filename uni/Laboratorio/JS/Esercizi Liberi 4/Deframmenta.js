/*Scrivere una funzione deframmenta(a), con a array di numeri.
La funzione restituisce una copia dell'array a da cui sono state eliminate
le occorrenze dei numeri quando queste non sono ripetute in sequenza
(ovvero in posizioni contigue dell'array) almeno una volta.
Ad esempio dato l'array a = [1,1,2,3,3,3,2,2,4] la chiamata deframmenta(a)
restituisce [1,1,3,3,3,2,2], dove gli elementi in posizione 2 e 4 
sono stati eliminati in quanto non ripetuti in sequenza.*/

var deframmenta1 = (a) => a.filter( (e, i, a) => (e == a[i - 1] || e == a[i + 1]) )

console.log(deframmenta1([1, 1, 2, 3, 3, 3, 2, 2, 4]))
console.log(deframmenta1([0, 0, 0, 0, 0, 1, 0, 1, 1]))
console.log(deframmenta1([1, 0]))