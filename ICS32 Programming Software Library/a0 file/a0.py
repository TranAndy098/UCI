n = int(input())
i = 1
while i < n:
    if i == 1:
        print("+-+")
        print("| |")
        print("+-+-+")
    if i + 1 == n:
        a = "  "
        b = i * a
        print(b + "| |")
        print(b + "+-+")
    else:
        a = "  "
        b = i * a
        print(b + "| |")
        print(b + "+-+-+")
    i += 1
