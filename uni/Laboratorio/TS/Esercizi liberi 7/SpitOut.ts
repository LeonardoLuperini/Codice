function spitOutTs<T>(a: T[], p: (e:T) => boolean ): void{
    console.log(a.filter(p).join())
}

spitOutTs([12,7,14,0,561], e => (e%3 == 0))