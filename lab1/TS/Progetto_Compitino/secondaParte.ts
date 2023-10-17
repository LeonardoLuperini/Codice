/*
//! INFORMAZIONI IMPORTANTI

//! Potete assumere che i valori passati dal chiamante siano corretti: ovvero, tutti gli
//! archi faranno riferimento a nodi che fanno parte del grafo

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


console.log("hey")
let n1 = new GNode(1), n2 = new GNode(2), n3 = new GNode(3), n4 = new GNode(4)
let e1 = new GEdge(n1,n2), e2 = new GEdge(n1,n3), e3 = new GEdge(n3,n4)
let g1 = new Graph([n1,n2,n3,n4],[e1,e2,e3])
let g2 = new Graph([n1,n2,n3,n4],[e1,e3])
console.log(connected(g1))
console.log(connected(g2))

/*
let n1=new GNode(0), n2=new GNode("due"), n3=new GNode("tre")
let e1=new GEdge(n1,n2), e2=new GEdge(n1,n3)
let g=new Graph([n1,n2,n3],[e1,e2])
console.log(g.edges.length)
console.log(g.nodes[1] === n2)
console.log(g.nodes[0].label)
console.log(g.edges[0].from === n1)
*/
