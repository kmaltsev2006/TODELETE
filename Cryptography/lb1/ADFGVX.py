CHARS = "ADFGVX"

GRID = [
    ["N", "A", "1", "C", "3", "H"],
    ["8", "T", "B", "2", "O", "M"],
    ["E", "5", "W", "R", "P", "D"],
    ["4", "F", "X", "K", "G", "7"],
    ["I", "J", "Z", "Y", "U", "V"],
    ["6", "Q", "S", "L", "0", "9"],
]


def get_pos(c):
    c = c.upper()
    for r, row in enumerate(GRID):
        if c in row:
            return CHARS[r] + CHARS[row.index(c)]
    raise ValueError(f"Character {c!r} not found in grid")


def get_char(r_ch, c_ch):
    r_ch = r_ch.upper()
    c_ch = c_ch.upper()
    if r_ch not in CHARS or c_ch not in CHARS:
        raise ValueError(f"Invalid coordinates: {r_ch}{c_ch}")
    return GRID[CHARS.index(r_ch)][CHARS.index(c_ch)]


def normalize_key(key):
    key = key.upper().replace(" ", "")
    if not key:
        raise ValueError("Key must not be empty")
    return key


def enc(s, key):
    key = normalize_key(key)
    s = s.upper().replace(" ", "")

    mid = "".join(get_pos(c) for c in s)

    m = len(key)
    cols = [[] for _ in range(m)]

    for i, ch in enumerate(mid):
        cols[i % m].append(ch)

    order = sorted(range(m), key=lambda i: (key[i], i))

    return "".join("".join(cols[i]) for i in order)


def dec(s, key):
    key = normalize_key(key)
    s = s.upper().replace(" ", "")

    m = len(key)
    n = len(s)

    if n % 2 != 0:
        raise ValueError("Ciphertext length must be even")

    base = n // m
    rem = n % m
    col_lens = [base + (1 if i < rem else 0) for i in range(m)]

    order = sorted(range(m), key=lambda i: (key[i], i))

    cols = [None] * m
    idx = 0

    for i in order:
        ln = col_lens[i]
        cols[i] = list(s[idx:idx + ln])
        idx += ln

    mid_chars = []
    col_pos = [0] * m

    for i in range(n):
        col = i % m
        mid_chars.append(cols[col][col_pos[col]])
        col_pos[col] += 1

    mid = "".join(mid_chars)

    return "".join(
        get_char(mid[i], mid[i + 1])
        for i in range(0, len(mid), 2)
    )


if __name__ == "__main__":
    KEY = "SECRET"
    msg = "HELLO2026"

    res_enc = enc(msg, KEY)
    print(res_enc)

    res_dec = dec(res_enc, KEY)
    print(res_dec)