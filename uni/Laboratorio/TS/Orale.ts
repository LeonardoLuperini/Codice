/*
calsse figura 
sotto classe rettangolo
sotto classe cerchio
scribvere una FUNZIONE CHE DATO UN ARRAY DI FIGURE RESTITUISCA UN ARRAY IN CUI OGNI ELEMENTo È SOSTITUITO DALL'ALTRA CLASSE DI PARI AREA
*/

class Figura {
    area: number
    constructor(area: number) {
        this.area = area
    }
}

class Rettangolo extends Figura {
    base: number
    constructor(area: number, base: number) {
        super(area)
        this.base = base 
    }
}

class Cerchio extends Figura {
    raggio: number
    constructor(area: number, raggio: number) {
        super(area)
        this.raggio = raggio
    }
}

function inverti(figure: Figura[]) {
    for (var i = 0; i < figure.length; i++){
        if (figure[i] instanceof Cerchio) {
            figure[i]
        }
        else if (figure[i] instanceof Rettangolo) {
             
        }
    }
}