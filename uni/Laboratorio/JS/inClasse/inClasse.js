// * Generatori
// * yield -> sta per produci

// * produce tutti i numeri nell intarvallo [a,b)
function* range(a, b) {var i = a; while (i<b) yield i++}
// * restituisce un oggetto fromato da value : valore di value, 
// * done : bool e dei metodi tipo next() che fa avanza il generatore

// for( i of range(0,5)) console.log(i)

// * Generatori inifiniti

function* gen_fib() {
    var i = 1
    var j = 1
    yield 1
    yield 1
    while (true){
        let temp = i
        i = j
        j += temp
        yield j
    }
}

for (i of gen_fib()) console.log(i)