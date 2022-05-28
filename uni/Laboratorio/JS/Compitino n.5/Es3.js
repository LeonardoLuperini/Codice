class Corpo {
    constructor(mass) {
        this.mass = mass
        this.pos = 0
        this.vel = 0
        this.acc = 0
    }

    get position(){
        return this.pos
    }

    get speed(){
        return this.vel
    }

    get accel(){
        return this.acc
    }

    set force(f){
        this.acc = f/this.mass
    }
    
    passaunsecondo() {
        this.pos += this.vel
        this.vel += this.acc
    }
}

var palla=new Corpo(2)
console.log(palla.position)
palla.passaunsecondo()
console.log(palla.position)
palla.force = 6
palla.passaunsecondo()
console.log(palla.position)
console.log(palla.accel)
console.log(palla.vel)
palla.passaunsecondo()
console.log(palla.position)
palla.passaunsecondo()
console.log(palla.position)
palla.passaunsecondo()
console.log(palla.speed)
palla.force = -5
palla.passaunsecondo()
console.log(palla.position)
palla.passaunsecondo()
console.log(palla.position)


