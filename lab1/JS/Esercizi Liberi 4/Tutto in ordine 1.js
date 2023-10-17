/*Scrivere una funzione isSorted1(a), con a un array di numeri. 
La funzione restituisce true se l'array è ordinato in senso
strettamente crescente, e false altrimenti.*/

function isSorted1(a) {
    for (let i = 0; i < a.length - 1; i++)
        if (a[i] >= a[i + 1]) return false
    return true
}

var isSorted1a = (a) => a.every( (e, i, a) => (i>0)? e > a[i-1] : true )

console.log(isSorted1([-21, -2, 0, 4, 6, 210]))
console.log(isSorted1([2, 6, 8, 8, 9, 21]))
console.log(isSorted1([2, 6, 8, 9, 10, -42]))
console.log(isSorted1a([-21, -2, 0, 4, 6, 210]))
console.log(isSorted1a([2, 6, 8, 8, 9, 21]))
console.log(isSorted1a([2, 6, 8, 9, 10, -42]))