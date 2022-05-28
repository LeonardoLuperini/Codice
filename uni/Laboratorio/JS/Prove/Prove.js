function spitOut(a, p){
    console.log(a.filter(p).join())
}

spitOut([12,7,14,0,561], e => (e%3 == 0))