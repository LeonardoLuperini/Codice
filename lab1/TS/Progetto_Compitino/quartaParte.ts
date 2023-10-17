//! INFORMAZIONI IMPORTANTI
//! Potete assumere che i valori passati dal chiamante siano corretti: ovvero, tutti gli
//! archi faranno riferimento a nodi che fanno parte del grafo

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

class Transition extends GEdge {
    evt: <E>(e: E) => boolean
    act?: () => void

    declare from: State
    declare to: State
    constructor(from: State, to: State, evt: <E>(e: E) => boolean, act?: () => void) {
        super(from, to)
        this.evt = evt
        this.act = act
    }
}

class Automata extends Graph {
    states: State[]
    transitions: Transition[]
    initial: State
    state: State

    constructor(states: State[], transitions: Transition[], initial: State) {
        super(states, transitions)
        this.states = states
        this.transitions = transitions
        this.initial = initial
        this.state = initial
    }

    init(): void {
        this.state = this.initial
    }

    done(): boolean {
        return this.state.final
    }

    step<E>(e: E): boolean {
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

//* ------------------------------- PARSER -------------------------------

class Parser extends Automata {

    constructor(states: State[], transitions: Transition[], initial: State) {
        super(states, transitions, initial)
    }

    accept(s: string){
        this.init()
        let sArr = s.split("")
        for (let c of sArr){
			console.log(c)
            if( this.state.final ) return false
            if( !( this.step<string>(c) ) ) return false
        }
        return this.state.final
    }
}

//* ------------------------------- FUNZIONI -------------------------------

function connected(g: Graph): boolean {
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
