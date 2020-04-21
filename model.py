import os
import sys
import numpy as np

d_range = 40

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

    energy = -t1 * d1

    if d2 == 0:
        t2 = l2 / (s2 + 1)
    else:
        t21 = energy / d2

        l21 = t21 * (s2 + 1 + d2)

        if l21 > l2:
            t21 = l2/(s2+1+d2)
            t22 = 0
        else:
            l22 = l2 - l21
            t22 = l22/(s2+1)
        t2 = t21 + t22

    t = t1 + t2
    return t


# Test cases:
# The values of lengths and speeds much bigger or equal to 1
def CreateTestCases():
    num_cases = 100
    test_cases = np.empty((num_cases, 16, 4))
    func_bits = (lambda: 10*np.random.rand(num_cases),
                 lambda: 100 + 100*np.random.rand(num_cases))
    for i in range(16):
        bits = list("{:04b}".format(i))
        bits = [int(b) for b in bits]
        tc = np.array([func_bits[bits[b]]() for b in range(4)])
        tc = tc.transpose()
        tc = tc.reshape((num_cases, 1, 4))
        test_cases[:, i:i+1, :] = tc
    return test_cases

def main():
    if len(sys.argv) == 5:
        l1 = int(sys.argv[1])
        s1 = int(sys.argv[2])
        l2 = int(sys.argv[3])
        s2 = int(sys.argv[4])
    else:
        test_cases = CreateTestCases()
        for tc_row in test_cases:
            for tc in tc_row:
                l1, s1, l2, s2 = tc
                tn = NormalWalk(l1, s1, l2, s2)
                tmin = tn
                usefull_case = None
                for di in range(0, d_range+1):
                    d1 = -di / d_range
                    for dj in range(0, d_range):
                        d2 = dj / d_range
                        t = AcceleratedWalk(l1, s1, l2, s2, d1, d2)
                        if tmin-t>1e-6:
                            usefull_case = tc.tolist() + [d1, d2, tmin, t]
                            tmin = t
                if usefull_case is not None:
                    print(usefull_case)


if __name__ == "__main__":
    main()
