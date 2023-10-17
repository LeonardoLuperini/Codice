type cbool = true | 1 | false | 0
type returnObj<T> = {"yes": T[], "no": T[] }
function setaccio<T>(a: T[], f: (e: T) => cbool ):returnObj<T> {
    var res: returnObj<T> = {"yes": [], "no": []}
    for (let e of a){
        if (f(e)) res.yes.push(e)
        else res.no.push(e)
    }
    return res
}