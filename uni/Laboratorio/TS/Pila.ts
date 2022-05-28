class Pila<T> {
    pila: T[] = []
    ptrv: number = 0

    push(e: T): number {
        this.pila[this.ptrv] = e
        this.ptrv++
        return this.pila.length
    }

    pop(): T | null{
        if (this.pila.length > 0) this.ptrv--
        var temp = this.pila.pop()
        if (temp == undefined) return null
        else return temp
    }

    top(): T{ return this.pila[this.ptrv-1] }

    size(): number{ return this.pila.length }

    reset(): 0{
        this.pila = []
        this.ptrv = 0
        return 0
    }

    merge(p: Pila<T>): number{
        this.pila = this.pila.concat( p.pila.reverse() )
        this.ptrv = this.pila.length
        return this.pila.length
    }

    // al posto del .toString() potrei anche usare questo: .reduce((prev, curr) => (prev != "")? prev + "," + curr : prev + curr, "")
    print(){
        var temp = [...this.pila]
        return temp.reverse().toString()
    }
}

var p = new Pila()
var p1 = new Pila()

console.log(p.pop())
console.log(p.push("ciao"))
console.log(p.print())
console.log(p.push("come"))
console.log(p.push("va"))
console.log(p.push("oggi"))
console.log(p.print())
console.log(p.size())
console.log(p.top())
console.log(p.print())
p1.push("oggi")
p1.push("bene")
console.log(p1.print())
console.log(p.merge(p1))
console.log(p.print())