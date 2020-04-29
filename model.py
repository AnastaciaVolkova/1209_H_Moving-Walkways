import threading
import sys
import numpy as np
import queue


d_range = 100
num_threads = 8
num_cases = 100


# Limak goes with speed 1.
# Energy is neigther accumulated, nor consumed.
def normal_walk(l1, s1, l2, s2):
    t1 = l1/(s1+1)
    t2 = l2/(s2+1)
    return t1 + t2


def accelerated_walk(l1, s1, l2, s2, d1, d2):
    if d1 > 0:
        raise ValueError("Exception: d1 is positive")
    if d1 < -1:
        raise ValueError("Exception: d1 is less than -1")

    if d2 < -1 or d2 > 1:
        raise ValueError("Exception: d2 is out of [-1, 1]")

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
def create_test_cases():
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
    return np.round(test_cases, 10)


def create_test_cases_wp():
    test_cases = create_test_cases()
    test_cases[:, :, 3] = 0
    return test_cases


def solver(l1, s1, l2, s2):
    tn = normal_walk(l1, s1, l2, s2)
    tmin = tn
    usefull_case = None
    for di in range(0, d_range + 1):
        d1 = -di / d_range
        for dj in range(0, d_range + 1):
            d2 = dj / d_range
            t = accelerated_walk(l1, s1, l2, s2, d1, d2)
            if tmin - t > 1e-9:
                usefull_case = [l1, s1, l2, s2, t, d1, d2]
                tmin = t
    if usefull_case is not None:
        return " ".join(["{:.10f}".format(uc) for uc in usefull_case])
    else:
        return "{0:.10f} {1:.10f} {2:.10f} {3:.10f} {4:.10f} {5:.10f} {6:.10f}".format(l1, s1, l2, s2, tn, 0, 0)


def solver_t(test_cases_queue, lock):
    lock.acquire()
    if not test_cases_queue.empty():
        tc = test_cases_queue.get()
    else:
        tc = None
    lock.release()
    while tc is not None:
        l1, s1, l2, s2 = tc
        res = solver(l1, s1, l2, s2)
        test_cases_queue.task_done()
        lock.acquire()
        if not test_cases_queue.empty():
            tc = test_cases_queue.get()
        else:
            tc = None
        print(res)
        lock.release()


def main():
    if len(sys.argv) == 5:
        l1 = float(sys.argv[1])
        s1 = float(sys.argv[2])
        l2 = float(sys.argv[3])
        s2 = float(sys.argv[4])
        print(solver(l1, s1, l2, s2))
    else:
        np.random.seed(0)
        test_cases_wp = create_test_cases_wp()
        test_cases_ww = create_test_cases()

        test_cases = np.concatenate((test_cases_wp, test_cases_ww), axis=0)

        lock = threading.Lock()
        test_cases_queue = queue.Queue()

        for tc_row in test_cases:
            for tc in tc_row:
                test_cases_queue.put(tc)

        thread_solver = []
        for t in range(num_threads):
            t = threading.Thread(target=solver_t, args=(test_cases_queue, lock))
            thread_solver.append(t)

        for t in thread_solver:
            t.start()

        for t in thread_solver:
            t.join()


if __name__ == "__main__":
    main()
