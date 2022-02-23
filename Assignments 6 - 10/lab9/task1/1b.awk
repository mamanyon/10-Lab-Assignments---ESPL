BEGIN {
    FS = "[\t,]"
    split(d, date,"/")
    if(company != ""){
        bool = 1
    }
    else{
        company = "all companies"
        bool = 0
        }
    total = 0
}
{
    if(bool == 1 && company != $1){
        next
    }
    split($2, date2,"/")
    if(date[3] < date2[3]){
        next
    }
    if(date[3] == date2[3] && date[2] < date2[2]){
        next
    }
    if(date[3] == date2[3] && date[2] == date2[2] && date[1] < date2[1]){
        next
    }
    total += $3
}
END {
    print "Total number of vaccines in israel on", d, "by",company, "is:", total
}