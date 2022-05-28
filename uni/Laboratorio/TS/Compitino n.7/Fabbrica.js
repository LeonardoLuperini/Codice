class IllegalOptionsError extends Error{}

class Fabbrica {
    nProdotti = 0;
    static nFabbriche = 0;

    constructor(prodotto){
        Fabbrica.nFabbriche++
        this.prodotto = prodotto
    }

    produci(opzioni = {}){
        this.nProdotti++
        var prod = {}
        prod = {...this.prodotto}
        for (let key in opzioni){
            if (prod[key]){
                if (prod[key] != opzioni[key]) throw IllegalOptionsError()
            }
            else {
                prod[key] = opzioni[key]
            }
        }
        return prod
    }

    
    get nProdotti() { return Fabbrica.nProdotti}
    get nFabbriche() { return Fabbrica.nFabbriche }
    //get prodotto() { return this.prodotto}
    //set prodotto(){}
}

var f1=new Fabbrica({modello: "500"})
var p1 = f1.produci({colore: "verde"})
var p2 = f1.produci({cambio: "auto"})
var f2=new Fabbrica({gusto: "limone"})
var f1=new Fabbrica({modello: "500"})
var f2=new Fabbrica({gusto: "limone"})

console.log(f1.nFabbriche)
console.log(f1.nProdotti)