class FixedBuffer<T> {
    buffer: T[] = [] 
    n: number

    constructor (n: number){
        this.n = n
    }

    put(...values:T[]){
        for(let e of values){
            if (this.buffer.length < this.n){
                this.buffer.push(e)
            }
        }
    }
}