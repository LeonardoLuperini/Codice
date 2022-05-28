class NonCantaError extends Error{}

class Eurovision {
    constructor() {
        this.insieme = []
        this.semiUno = []
        this.semiDue = []
        this.semifinalenumero = 1
    }

    iscrivi(c) {
        if (c.canta instanceof Function) {
            this.insieme.push[c]
            this.semifinalenumero = 1
        }
        else throw new NonCantaError()
    }

    semifinale(n) {
        if (n == 1) {
            while(Math.ceil(this.insieme.length/2) > this.semiUno.length){
                var r = Math.floor(Math.random() * this.insieme.length)

                if (!this.semiUno.includes(this.insieme[r])) {
                    this.semiUno.push(this.insieme[r])
                }
            }

            for (let e in this.insieme){
                if (!this.semiUno.includes(this.insieme[r])){
                    this.semiDue.push(this.insieme[r])
                }
            }
            this.semifinalenumero = 2
            return this.semiUno
        }
        
        else if (n == 2 && this.semifinalenumero == 2) {
            var temp = []
            while(this.semiDue.length > temp.length){
                var r = Math.floor(Math.random() * this.semiDue.length)

                if (!temp.includes(this.semiDue[r])) {
                    temp.push(this.semiDue[r])
                }
            }

            return this.semiDue
        }
    }
}

let cantore={ canta: ()=>console.log("sooool") }
let cantore1={ canta: ()=>console.log("sooool") }
let cantore2={ canta: ()=>console.log("sooool") }
let cantore3={ canta: ()=>console.log("sooool") }
let cantore4={ canta: ()=>console.log("sooool") }
let cantore5={ canta: ()=>console.log("sooool") }
let cane={ canta: false }
let sam={ suona: "piano" }
let e=new Eurovision()
e.iscrivi(cantore)
e.iscrivi(cantore1)
e.iscrivi(cantore2)
e.iscrivi(cantore3)
e.iscrivi(cantore4)
e.iscrivi(cantore5)
//e.iscrivi(cane)

e.iscrivi(cantore)

console.log(e.semifinale(1))