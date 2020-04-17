# 1209_H_Moving-Walkways
Solution of problem from codeforces.com (1209_H)
Problem description is here
https://codeforces.com/problemset/problem/1209/H
## Solution
Before working out algorithm, it is worth making clear the following situations:
### Path - Path
Limak should go with maximum possible speed. Accumulating energy is useless.

### Walkway - Path
Limak should spend on highway extensive energy.

### Walkway - Walkway 
If first walkway has speed lower than second walkway, Limak should go with speed 1.
If first walkway has speed higher than second walkway, Limak should stay.

The detailed information is in
[ProblemDescription.odt.](https://github.com/AnastaciaVolkova/1209_H_Moving-Walkways/blob/master/ProblemDescription.odt.) 