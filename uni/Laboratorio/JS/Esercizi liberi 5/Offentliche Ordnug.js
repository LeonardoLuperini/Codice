function ordnung(a) {
    return a.map(e => e.sort((a,b) => a-b)).sort((a,b) => {
        for (var i = 0; i < Math.min(a.length, b.length)-1 && a[i]-b[i] == 0;i++) {}
        if (a[i]-b[i] == 0) return a.length - b.length
        return a[i] - b[i]
    })
}


console.log(ordnung( [[5,1,3],[1,5,2,7],[3,4],[3]] ))