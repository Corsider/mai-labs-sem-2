#!/usr/bin/env awk

BEGIN {
    FS=":"
    SUM=0
    COUNT=0
    ISH=0
    PC=0
}

{
    if ($1 ~ NAME) {
        SUM = SUM + $2
        COUNT = COUNT + 1
        ISH = ISH + $3
    }
}

END {
    PC = ISH / COUNT * 100
    print NAME "'s average homework mark - " SUM / COUNT
    print NAME " was at " PC "% of lessons"
    if (PC < 50) {
        print "That's AWFUL!"
    } else if (PC >= 50 && PC < 75) {
        print "That's BAD!"
    } else if (PC >= 75 && PC <= 95) {
        print "That's GOOD!"
    } else {
        print "That's EXCELLENT!"
    }
}
