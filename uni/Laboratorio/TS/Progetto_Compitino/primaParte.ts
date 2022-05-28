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

let n1=new GNode(0), n2=new GNode("due"), n3=new GNode("tre")
let e1=new GEdge(n1,n2), e2=new GEdge(n1,n3)
let g=new Graph([n1,n2,n3],[e1,e2])
console.log(g.edges.length)
console.log(g.nodes[1] === n2)
console.log(g.nodes[0].label)
console.log(g.edges[0].from === n1)

//* FINITO

*/