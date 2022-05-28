function calcT([op, val, ...values]) {
    val = ((Array.isArray(val))? calcT(val) : val)
    switch (op){
        case "+":
            return values.reduce((prev, curr) => prev + ((Array.isArray(curr))? calcT(curr) : curr), val)
        case "-":
            return values.reduce((prev, curr) => prev - ((Array.isArray(curr))? calcT(curr) : curr), val)
        case "*":
            return values.reduce((prev, curr) => prev * ((Array.isArray(curr))? calcT(curr) : curr), val)
        case "/":
            return values.reduce((prev, curr) => prev / ((Array.isArray(curr))? calcT(curr) : curr), val)
    }
}

console.log( calcT(["/",64, ["*",["+",2,2],4] ]) )