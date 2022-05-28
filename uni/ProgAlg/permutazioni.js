function perm(p,n,k) {
    if (k == n-1) console.log(p)
    else for (var i=k; i<n; i++) {
        var temp = 0
        temp = p[i]
        p[i] = p[k]
        p[k] = temp
        perm(p,n,k+1)
        temp = p[i]
        p[i] = p[k]
        p[k] = temp
    }
}

perm([1,2], 2, 0)