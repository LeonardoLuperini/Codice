//! INFORMAZIONI IMPORTANTI

//! Potete assumere che i valori passati dal chiamante siano corretti: ovvero, tutti gli
//! archi faranno riferimento a nodi che fanno parte del grafo

//* ------------------------------- INTERFACE -------------------------------

interface GNodeI {
    label: number | string
}

interface GEdgeI {
    from: GNode
    to: GNode
}

interface GraphI {
    nodes: GNode[]
    edges: GEdge[]
}

interface StateI extends GNodeI{
    final: boolean
}

interface TransitionI<E> extends GEdgeI{
    evt: (e: E) => boolean
    act?: () => void
}

//* ------------------------------- CLASSI GRAFO -------------------------------

class GNode {
    label: number | string

    constructor(label: number | string) {
        this.label = label
    }
}

class GEdge { // Arco orientato
    from: GNode
    to: GNode


    constructor(from: GNode, to: GNode) {
        this.from = from
        this.to = to
    }
}

class Graph {
    nodes: GNode[]
    edges: GEdge[]


    constructor(nodes: GNode[], edges: GEdge[]) {
        this.nodes = nodes
        this.edges = edges
    }
}

//* ------------------------------- CLASSI AUTOMA -------------------------------

class State extends GNode {
    final: boolean

    constructor(label: number | string, final: boolean = false){
        super(label)
        this.final = final
    }

}

class Transition<E> extends GEdge {
    evt: (e: E) => boolean
    act?: () => void

    declare from: State
    declare to: State
    constructor(from: State, to: State, evt: (e: E) => boolean, act?: () => void) {
        super(from, to)
        this.evt = evt
        this.act = act
    }
}

class Automata<E> extends Graph {
    states: State[]
    transitions: Transition<E>[]
    initial: State
    state: State

    declare nodes: State[]
    declare edges: Transition<E>[]
    constructor(states: State[], transitions: Transition<E>[], initial: State) {
        super(states, transitions)
        this.states = this.nodes
        this.transitions = this.edges //? va bene? esiste un altro modo per cambiare il nome?
        this.initial = initial
        this.state = initial
    }

    init(): void {
        this.state = this.initial
    }

    done(): boolean {
        return this.state.final
    }

    step(e: E): boolean {
        for (let t of this.transitions){
            if (t.from == this.state){
                if (t.evt(e)){
                    if (t.act) t.act()
                    this.state = t.to
                    return true
                }
    
            }
        }
        return false
    }
}

//* ------------------------------- FUNZIONI -------------------------------

function connected(g: Graph): boolean { //? E' connesso un grafo con un solo nodo?
    var res: boolean = true
    var vis: GNode[] = []
    var coda: GNode[] = [g.nodes[0]]
    
    while (coda.length != 0) {
        vis.push(coda[0])
        for(let e of g.edges) {
            if (e.to == coda[0]){
                if (!(coda.includes(e.from) || vis.includes(e.from))) coda.push(e.from)
            }
            else if (e.from == coda[0]){
                if (!(coda.includes(e.to) || vis.includes(e.to))) coda.push(e.to)
            }
        }
        coda.shift()
    }
    
    for (let v of g.nodes){
        if( !(vis.includes(v)) ) res = false
    }

    return res
}

//* ------------------------------- PROVE E DICHIARZIONI VARIE -------------------------------

let si = new State("iniziale")
let s1 = new State(1)
let s2 = new State(2)
let sf = new State("finale", true)
let t1 = new Transition(si, s1, n => n % 2 == 0)
let t2 = new Transition(si, s2, n => n % 2 == 1)
let t3 = new Transition(s1, sf, n => n < 0, () => {console.log("e")})
let t4 = new Transition(s2, sf, n => n < 0, () => {console.log("o")})
let t5 = new Transition(s1, s2, n => true)
let t6 = new Transition(s2, s1, n => true)

let a = new Automata<number>([si,s1,s2,sf], [t1,t2,t3,t4,t5,t6], si)

console.log(a.nodes[0])
console.log(a.states[0])
console.log(a.nodes[0] === a.states[0]) //! Sto duplicando le cose! Va bene o no?
console.log(t1.to)

console.log("\n\n\n")
console.log(a.state)
console.log(a.states.length)
a.step(7)
console.log(a.state)
a.step(7)
console.log(a.state)
a.step(-4)
console.log(a.state)
console.log(a.done())
console.log(a.state.label)
console.log(a.transitions)
console.log(a.edges)
