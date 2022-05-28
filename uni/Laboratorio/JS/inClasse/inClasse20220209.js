//* Espressioni-classe

class Persona { //! Super-classe di Studente e Super-classe di StMagistrale
    constructor (nome, eta) {
        this.nome = nome
        this.eta = eta
    }

    compleanno() {
        this.eta++
    }
}

var PersonaEC = class {
    constructor (nome, eta) {
        this.nome = nome
        this.eta = eta
    }

    compleanno() {
        this.eta++
    }
}

//* Ereditarietà

class Studente extends Persona { //! Sotto-classe di Persona e Super-classe di StMegistrale
    laurea() {
        return "Evviva!"
    }
}

class StMegistrale extends Persona { //! Sotto-classe di Studente
    constructor(nome, eta, triennale){
        super(nome, eta) //? costruttore di studente
        this.triennale = triennale
    }

    laurea() {
        return super.laurea + ", Evviva Galattico" //? chiama il metodo laurea di studente
    }
}

// !!! NON STANDARD !!! Dichiarazioni di campo

class PersonaProva {
    nome = "anonimo"
    eta = -1
    /* ecc.. */
}

//* Membri privati (Standard dal 2022)

class C {
    #privato() { /* Codice */ }
    pubblico() { /* Qui si puo usare this.#privato() */ }
}

//* Membri statici
class Auto {
    static metodo(){ /* Codice */  } //? Le istanza non hanno il metodo segnato con static ma invece la classe Auto lo può usare
}

//* UML -> linguaggio di modellazione 

// * Get e Set

var oggetto = { get x() {return 1}, set x() {;} }

oggetto.x // returna 1
oggetto.x = 5
oggetto.x // returna 1