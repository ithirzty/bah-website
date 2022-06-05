function higlightDecl(decl) {
    res = decl.replace(/(.+)(\(.+)/, "<func>$1</func>(")
    
    rest = decl.split("(", 2)[1].split(")", 2)
    argsWrapper = rest[0]
    args = argsWrapper.split(", ")
    
    for (i in args) {
        args[i] = args[i].replace(/(\w+)\s*(.+)/, "<var>$1</var> <type>$2</type>")
    }


    res += args.join(", ")+") <type>"+(rest.length == 2 ? rest[1] : "")+"</type>"
    return res
}

function sanitizeComments(c, tabsI) {
    tabs = ""
    for(i=0; i < tabsI; i++) {
        tabs += "    "
    }
    c = c.replace(/(\/\/\s*)/gm, "<br>"+tabs+"// ")
    return c
}