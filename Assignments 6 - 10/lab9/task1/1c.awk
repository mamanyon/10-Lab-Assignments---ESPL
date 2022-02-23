BEGIN{
    FS = "[\t,]"
}
{
    print $2
}