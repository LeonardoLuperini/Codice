/*
Si scriva una funzione waves(a,m) che, dati due array a e m di interi > 0, implementi nel suo corpo le seguenti due fasi (nell'ordine indicato):

1. Fase “salti”: Partendo dall’indice i = 0 dell’array m, si aggiunga l’elemento di m in posizione i+m[i] all’array a, si aggiorni l'indice i a tale posizione (i+m[i]).
                 Questo step corrisponde a un singolo salto.
                 Si iteri poi il processo a partire dalla posizione aggiornata.
                 La fase salti si conclude quando si salta ad un elemento al di fuori dell'array.
                 A questo punto si chiuda questa fase ordinando l’array a in ordine crescente;

2. Fase “onde”: Partendo dall’indice i = 0 dell’array a (risultante dalla fase precedente), si scambi una coppia di elementi adiacenti (in posizione i e i+1) 
                per ogni salto effettuato con successo.
                Dopo lo scambio ci si sposti all'elemento in posizione i+2 per effettuare lo scambio successivo (con i+3).


La funzione restituisce l’array a risultante dall'esecuzione delle 2 fasi.

Esempio:
    
    waves([1,3,5,6,7,8,9], [1,2,0,4,0,0,0,10]) => [2,1,4,3,6,5,7,8,9,10]
*/

function waves(a, m) {
    var counter = 0

    //Salti
    for (let i = 0; i + m[i] < m.length; i += m[i]) {
        a.push(m[i + m[i]])
        counter++
    }
    a.sort((a, b) => a - b)

    //Onde
    let i = 0
    for (; counter > 0; counter--) {
        if (i + 1 >= a.length) break
        else [a[i], a[i + 1]] = [a[i + 1], a[i]]
        i += 2
    }
    
    return a
}

console.log(waves([1, 3, 5, 6, 7, 8, 9],[4, 9, 1, 0]))