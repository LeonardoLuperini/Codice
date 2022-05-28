interface Matrix<T>{
    row: number
    col: number
    m: T[][]
}

class AnyMatrix<T> implements Matrix<T>{
    row: number
    col: number
    m: T[][]

    constructor(v:T, r = 1, c = 1) {
        if (r > 0) this.row = r
        else throw Error(`the minimum number of row is 1 and you sent ${r}`)
        if (c > 0) this.col = c
        else throw Error(`the minimum number of row is 1 and you sent ${r}`)
        this.m = []
        for (let i = 0; i < this.row; i++) {
            this.m[i] = []
            for (let j = 0; j < this.col; j++) {
                this.m[i][j] = v
            }
        }
    }

    setAll(dati: T[][]): boolean{
        if (dati.length != this.row || dati[0].length != this.col) return false
        else {
            for (let i = 0; i < this.row; i++) {
                this.m[i] = [...dati[i]]
            }
            return true
        }
    }

    setCrescente(c:T) {
        if (typeof c == "number"){
            for (let i = 0; i < this.row; i++) {
                for (let j = 0; j < this.col; j++) {
                    this.m[i][j] = c
                    c++
                }
            }
        }
        else throw Error("Errore questa funzione vale solo per le matrici di tipo number")
    }

    transpose() {
        var nMat = new AnyMatrix(this.m[0][0], this.col, this.row)
        for (let i = 0; i < this.row; i++) {
            for (let j = 0; j < this.col; j++) {
                nMat.m[j][i] = this.m[i][j]
            }
        }
        return nMat
    }
    
    stampa() {
        for(let x of this.m){
            console.log(x)
        }
    }
}

var tabella = new AnyMatrix(0,4,3)
var tabella1 = new AnyMatrix(1,4,3)
var dati = tabella1.m
tabella.setAll(dati)
tabella.stampa()
tabella.setCrescente(1)
tabella.stampa()
var nMat = tabella.transpose()
nMat.stampa()