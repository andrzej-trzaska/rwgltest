/* Return 1 if strings are equal, 0 if not */
/* Make sure we don't ever pass the given end (E) */
int StrEqual (char *A, char *B, char *E, int count) {
    int c = 0;

    while ((c < count) && (A != E)) {
        if (A[c] != B[c]) return 0;

        c++;
    }
    if (A == E)
        return 0;
    else
        return 1;
}

/* Return 1 if the character is dead space, 0 if not */
int IsNumeric(char A) {
    if (A == '.') return 1;
    if (A == '-') return 1;
    if ((A >= 0x30) && (A <= 0x39)) return 1;

    return 0;
}

/* Return 1 if the character is dead space, 0 if not */
int IsDeadSpace(char A) {
    if (A < 33)
        return 1;
    else
        return 0;
}

/* Return 1 if the character is a newline/linefeed, 0 if not */
int IsEOL(char A) {
    if (A == 10)
        return 1;
    else
        return 0;
}
