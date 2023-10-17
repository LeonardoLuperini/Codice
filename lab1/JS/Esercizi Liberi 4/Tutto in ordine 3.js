/*Scrivere una funzione isSorted3(a), con a un array di numeri.
La funzione restituisce true se l'array è ordinato in senso strettamente crescente,
e false altrimenti. Occorre gestire anche il caso in cui a sia sparso
(ovvero, include elementi empty) e in cui alcuni elementi siano i valori “speciali”
NaN e ±Infinity (gli NaN vanno ignorati, mentre gli infiniti positivi o negativi
devono occupare il loro posto naturale nell’ordinamento).*/

function isSorted3(a) {
    var c
    for (let i = 0; i < a.length - 1; i += c) {
        c = 1
        while (!(a[i])) i++
        while (!(a[i + c])) c++
        //console.log(`confronto fra ${a[i]} e ${a[i+c]}`)
        if (a[i] >= a[i + c]) {
            return false
        }
    }
    return true
}

let a = [-21, -2, 0, 4, 6, 210]
a[1] = NaN
delete a[2]
a.push(Infinity)
console.log(isSorted3(a) + "\n")
a[2] = -Infinity
console.log(isSorted3(a))