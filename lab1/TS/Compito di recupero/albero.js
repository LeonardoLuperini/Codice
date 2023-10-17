class BadTreeError extends Error{}

class TNode {
    constructor(valore, etichetta = "") {
        this.valore = valore
        this.etichetta = etichetta
        this.figli = []
    }

    add(...nodi) {
        this.figli = [...this.figli, ...nodi]
    }

    * visit(){
        yield this.valore
        if (this.figli.length) {
            for (let e of this.figli) {
                yield *e.visit()
            }
        }
    }
}

class BNode extends TNode {
    add(...nodi) {
        if(this.figli.length + nodi.length <= 2) {
            this.figli = [...this.figli, ...nodi]
        }
        else throw new BadTreeError()
    }
}

const   n0=new TNode(0,"radice"),
        n1=new TNode(1,"sx"),
        n11=new TNode(11),
        n12=new TNode(12),
        n2=new TNode(2,"centro"),
        n3=new TNode(3,"dx"),
        n31=new TNode(31),
        n32=new TNode(32),
        n33=new TNode(33),
        n34=new TNode(34),
        n341=new TNode(341,"nipotino")

n0.add(n1,n2,n3)
n1.add(n11,n12)
n3.add(n31,n32,n33)
n34.add(n341)
n3.add(n34)

console.log([...n0.visit()])