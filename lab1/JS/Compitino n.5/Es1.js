/*
Si scriva una funzione JavaScript kids(T) che, dato un albero k-ario T definito come visto a lezione, in cui però ogni nodo può avere anche altre proprietà oltre a val e figli, lo modifichi in modo che, dopo la chiamate a kids(T), la proprietà val di ogni nodo Q di T abbia come valore un array di stringhe, che contenga l'insieme di tutte le chiavi di tutti i nodi del sottoalbero radicato in Q, ordinate in ordine lessicografico.


*/

function kids(T) {
    T.val = []
    for(i in T){
        if (i != "val" && i != "figli"){
            T.val.push(i)
            console.log(i)
        }
        if(T.figli){
            for(e of T.figli){
                kids(e)
                T.val.push(e.val)
            }
        }
    }
}


var T={ figli: [
    { val: 3, frizza: true, figli: [
      {fanta: 1},
      {cola: 3, figli: [
        {zero: 1},
        {light: 1},
        {diet: 1, felice: false}
      ]},
      {sprite: 2}
    ]}
  ]}

kids(T)
console.log(T.val)