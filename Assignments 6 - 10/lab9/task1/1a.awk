BEGIN {
    FS = "[\t,]"
}
{
    count[$1] = $3 + count[$1]
}
END {
    for (company in count){
        print company ":", count[company], "vaccines."}
}