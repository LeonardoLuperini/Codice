class ArrayConTaglia extends Array{
    constructor(t,...param){
        if(t==undefined){
            super(...param)
        }
        else{
            this.taglia = t
            super(...param)
        }
    }

    push(e){
        if(this.taglia){
            if (this.length < this.taglia){
                Array.prototype.push.call(this, e)
            }
            else throw new TooBigError("Errore: non puoi inserire più elementi della taglia")
        } else  Array.prototype.push.call(this, e)
    }
}

class TooBigError extends Error {
    constructor(...param){
        super(...param)
    }
}

var at = new ArrayConTaglia()
console.log(at.taglia)
console.log(at instanceof Array)
at.push(3)
at.push(5)
console.log(at)