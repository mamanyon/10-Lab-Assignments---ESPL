BEGIN{
    FS= "[\t,]"
}
{
    total_vax[$1]+= $3/$4
}
END{
    for( company in total_vax)
        print company"|"total_vax[company]
}