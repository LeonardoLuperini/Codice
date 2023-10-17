function calc1([op, val, ...values]) {
    switch (op){
        case "+":
            return values.reduce((prev, curr) => prev + curr, val)
        case "-":
            return values.reduce((prev, curr) => prev - curr, -val)
        case "*":
            return values.reduce((prev, curr) => prev * curr, val)
        case "/":
            return values.reduce((prev, curr) => prev / curr, val)
    }
}

console.log( calc1(["/",64,2,2,4]) )