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
        function anticipata() {
            if (this.figli.length) {
                for (let e of this.figli) {
                    e.visit()
                }
            }   
        }
        anticipata()
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