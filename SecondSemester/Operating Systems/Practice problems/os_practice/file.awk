BEGIN {
    c=0;
    v=0;
}

$0 ~ /[aeiouAEIOU]$/ {
    v++;
}

$0 ~ /[a-zA-Z]$/ && $0 ~ /[^aeiouAEIOU]$/ {
    c++;
}

END {
    print "Number of lines ending with vowel: "v;
    print "Number of lines ending with consonant: "c;
}

