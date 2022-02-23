BEGIN {
    FS = "[\t]"
}
{
    if($1 != "")
        total +=1
    print $1
}
END {
    print "Total number of students is:",total
}