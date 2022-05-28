import { spawn } from "child_process"

type xo = "X" | "O"
type stato = "ok" | "no" | "pari" | "tris"

type move = void | {res: stato, last: xo}

interface TicTacToe{
    move(i: number,j: number): move

}

class TicTacToe implements TicTacToe{
    matrix: string[][] = [[],[],[]]
    char: xo = "X"
    mosse: number = 0
    fine: boolean = false

    setMove(i: number, j: number) {
        this.matrix[i][j] = this.char
        this.mosse++
    }

    swapChar(){
        if (this.char == "X") this.char = "O"
        else this.char = "X"
    }
    
    inside(i: number, j: number): boolean {
        return (i>=0 && i<=2) && (j>=0 && j<=2)
    }
    
    free(i: number, j: number): boolean{
        return this.matrix[i][j] == undefined
    }
    
    legal(i: number, j: number): boolean{
        return this.inside(i,j) && this.free(i,j)
    }

    winRow(i: number, c: xo): boolean {
        var w: boolean = true
        for (var a = 0; a<3; a++){ //controlla riga 
            if (this.matrix[i][a] != c) w = false 
        }
        return w
    }

    winCol(j: number, c: xo): boolean {
        var w: boolean = true
        for(let a = 0; a<3; a++){ //controlla colonna
            if (this.matrix[a][j] != c) w = false 
        }
        return w
    }

    winFDiag(i: number, j: number, c: xo): boolean{
        var w: boolean = true
        for (var a = 0; a<3; a++){ //controlla la diagonale principale
            if(this.matrix[a][a] != c) w = false
        }
        return w
    }

    winSDiag(i: number, j: number, c: xo): boolean{
        var w: boolean = true
        for (var a = 0; a<3; a++){ //controlla la diagonale secondaria
            for (var b = 0; b<3; b++){
                if((a+b == 2) && this.matrix[a][b] != c) w = false
            }
        }
        return w
    }
    
    win(i: number, j: number, c: xo): boolean {
        if (this.mosse >= 5) {
            return this.winRow(i,c) || this.winCol(j,c) || this.winFDiag(i,j,c) || this.winSDiag(i,j,c)
        }
        return false
    }

    move(i: number, j: number): move {
        if(this.legal(i,j)){
            var oldChar: xo = this.char
            this.setMove(i,j)
            this.swapChar()
            if (this.win(i,j, oldChar)) return {res: "tris", last: oldChar}
            else if(this.mosse == 9) return {res: "pari", last: oldChar}
            else return {res: "ok", last: oldChar}
        }
        else return {res: "no", last: this.char}
    }

    reset(){

    }
}

var t = new TicTacToe()


console.log(t.move(0,0))
console.log(t.move(2,2))
console.log(t.move(0,0))
console.log(t.move(0,0))
console.log(t.move(2,2))
console.log(t.move(1,1))
console.log(t.move(0,2))
console.log(t.move(1,0))
console.log(t.move(1,2))

