BEGIN {
    FS = "[\t|]"
}
{
    for(i = 2; i<=NF; i++){
        split($i, a, ":")
        if($i != "")
            count[a[1]]++
    }
}
END {
    total = 0
    for (err in count){
        total++
        print err, "appears", count[err], "times"}
    print "number of unique error-codes in the file is: ", total
}