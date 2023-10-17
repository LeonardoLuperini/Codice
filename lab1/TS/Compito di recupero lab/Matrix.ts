type int = number & {set: "N"}

function toInt(n: number | int): int;
function toInt(n: number[] | int[]): void;
function toInt(n: number | int | number[] | int[]): int | void {
    if (n instanceof Array) {
        for(let e of n) toInt(e)
    }
    else return (n | 0) as int // Per fare l'operazione di or JS trasforma il numero in un Intero a 32bit e quindi rimuove i decimali
}

class GeneralMatrix <T> {
    r: int
    c: int
    m: T[][]

    constructor(r: number, c: number, m: T[][] = []) {
        this.r = toInt(r)
        this.c = toInt(c)
        if (m.length > r) throw new RangeError("The matrix passed have too many rows")
        for (let row in m) if (m[row].length > c) throw new RangeError(`The matrix passed have too many columns at row ${row}`) 
        this.m = m
    }
}

class MatrixI extends GeneralMatrix<int> {
    constructor(r: number, c: number, m: number[][] = []) {
        for (let row of m) toInt(row)
        super(r, c, m as int[][])
    }

    unzip(): void {
        for(let row = 0; row < this.r; row++) {
            if (!this.m[row]) this.m[row] = [] 
            for (let col = 0; col < this.c; col++) {
                if (!this.m[row][col]) this.m[row][col] = toInt(0)
            }
        }
    }

    zip(): void {
        for(let row = 0; row < this.r; row++) {
            if (!this.m[row]) continue
            for (let col = this.c - 1; col >= 0; col--) {
                if (this.m[row][col] == 0 && !this.m[row][col+1]) this.m[row].splice(col,1)
            }
            if (this.m[row].length == 0) {
                this.m.splice(row,1)
                row -= 1
            }
        }
    }

    print(): void {
        for (let row in this.m) {
            console.log(row , this.m[row])
        }
        console.log()
    }

    sum(m: MatrixI): MatrixI {
        var res = new MatrixI(this.r, this.c, [])
        
        this.unzip()
        m.unzip()
        res.unzip()

        if (this.r == m.r && this.c == m.c) {
            for (let row = 0; row < res.r; row++){
                for (let col = 0; col < res.c; col++) {
                    res.m[row][col] = (this.m[row][col] + m.m[row][col]) as int
                }           
            }
        }
        return res
    }

    multiply() {
        var res = new MatrixI(this.r, this.c, [])
    }
}


var mat1 = new MatrixI(2, 2, [[1]])
var mat2 = new MatrixI(2, 2, [[],[0,1]])
var mat3 = mat1.sum(mat2)
mat3.print()

