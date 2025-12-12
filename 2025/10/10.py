import numpy as np
from scipy.optimize import milp, LinearConstraint, Bounds

from typing import List

with open("input.txt") as f:
    lines = f.readlines()


fewest_presses = 0
for line in lines:
    line: List[str] = line.split()

    final_state = line[0][1:-1]
    m = len(final_state)

    # Ab = c
    A_t = []
    for i in range(1, len(line) - 1):
        line[i] = line[i][1:-1]
        line[i] = [int(num_str) for num_str in line[i].split(",")]
        A_t.append([int(j in line[i]) for j in range(0, m)])
    A_t = np.array(A_t)
    A = A_t.T
    m, n = A.shape

    jolts = np.array([int(num_str) for num_str in line[-1][1:-1].split(",")])

    obj = np.ones(n)

    result = milp(
        c=np.ones(n),
        constraints=LinearConstraint(A, jolts, jolts),
        bounds=Bounds(lb=0, ub=np.inf),
        integrality=obj,
    )

    if result.success:
        fewest_presses += int(sum(result.x))


print(int(fewest_presses))
