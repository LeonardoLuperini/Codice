function integra(f, a, b) {
    return (n) => {
        let temp = 0
        for (let i = 1; i < n; i++) {
            temp += f(a + i * ((b - a) / n))
        }

        return ((b - a) / n) * (((f(a) + f(b)) / 2) + temp)
    }
}

console.log(integra(x=>x**x,1,2.5)(10))