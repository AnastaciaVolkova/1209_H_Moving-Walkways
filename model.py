import os
import sys

# Limak goes with speed 1.
# Energy is neigther accumulated, nor consumed.
def NormalWalk(l1, s1, l2, s2):
    t1 = l1/(s1+1)
    t2 = l2/(s2+1)
    return t1 + t2

def AcceleratedWalk(l1, s1, l2, s2, d1, d2):
    if d1 > 0:
        raise "Exception: d1 is positive"
    if d1 < -1:
        raise "Exception: d1 is less than -1"

    if d2 < -1 or d2 > 1:
        raise "Exception: d2 is out of [-1, 1]"

    t1 = l1/(s1+1+d1)

    energy = t1 * d1

    if d2 == 0:
        t2 = l2 / (s2 + 1)
    else:
        t21 = energy / d2

        l21 = t21 * (s2 + 1 + d2)

        if l21 > l:
            t21 = l/(s2+1+d2)
            t22 = 0
        else:
            l22 = l - l21
            t22 = l22/(s2+1)
        t2 = t21 + t22

    t = t1 + t2
    return t


def main():
    l1 = int(sys.argv[1])
    s1 = int(sys.argv[2])
    l2 = int(sys.argv[3])
    s2 = int(sys.argv[4])
    print(NormalWalk(l1, s1, l2, s2))
    print(AcceleratedWalk(l1, s1, l2, s2, 0, 0))


if __name__ == "__main__":
    main()
