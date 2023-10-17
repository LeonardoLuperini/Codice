const rand = (max) => Math.floor(Math.random() * max)
const matricolaGen = () => rand(1000000) 


function* esameGen() {
    const MATERIE = [
        {materia: "ProgAlg", cfu: 15},
        {materia: "Analisi", cfu: 12},
        {materia: "FDI", cfu: 9},
        {materia: "Laboratorio", cfu: 12},
        {materia: "Algebra Lineare", cfu: 6},
    ]
    const votoGen = () => {
        var res = {}
        res.voto = rand(13) + 18
        res.lode = false
        if (res.voto == 30) res.lode = (rand(10)%2 == 0)
        return res
    }
    while (true) yield {...MATERIE[rand(MATERIE.length)], ...votoGen()}
}

class Studente {
    constructor(numMat, nome, {cognome = "", corso = ""}) {
        this.numMat = numMat
        this.nome = nome
        this.cognome = cognome
        this.corso = corso
        this.carriera = []
    }
    
    passato(esame) {
        this.carriera.push(esame)
    }

    media() {
        return this.carriera.reduce((prev, curr)=> 
                        prev + ((curr.lode)? curr.voto + 2 : curr.voto) * curr.cfu, 0) //Numeratore
                                            /                                          //  Diviso
        this.carriera.reduce((prev, curr)=> prev + curr.cfu, 0)                        //Denominatore
    }
}

var paolo = new Studente(matricolaGen(), "paolo", {cognome : "peri"})

paolo.passato(esameGen().next().value)
paolo.passato(esameGen().next().value)
paolo.passato(esameGen().next().value)
console.log(paolo)
console.log(paolo.media())