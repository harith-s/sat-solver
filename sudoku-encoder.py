import numpy

f = open("sudoku.cnf", mode="w")
n = 3
f.write(f"p cnf {n**6} 6\n")

sqn = n**2
fn = n**4
# number of variables is 9**3 = 729

# let
# vble % 9 -> number in the box
# (vble // 9) % 9 -> column
# ((vble // 81) % 9 -> row

# l = [i for i in range(729)]
# for vble in l:
#     print((vble % 9 )+ 1, ((vble // 9) % 9) + 1, ((vble // 81) % 9) + 1)


# initial_state = [(1,8,1),(2,1,4),(3,2,2),(4,5,5),(4,7,4),(4,9,7),(5,3,8),(5,7,3),(6,3,1),(6,5,9),(7,1,3),(7,4,4),(7,7,2),(8,2,5),(8,4,1),(9,4,8),(9,6,6)]
# initial_state = [(1,3,4), (1,4,3),(4,1,2),(4,2,3)]
initial_state = [(1,1,1),(1,2,2),(2,4,1),(3,2,3),(3,4,4),(4,3,3)]
initial_state =[]
fi = open("clues.txt")
# n = int(fi.readline().strip('\n'))
for line in fi:
    l = [int(i) for i in line.split(',')]
    initial_state.append(tuple(l))
print(initial_state)

for i in initial_state:
    row, column, val = i[0] - 1, i[1] - 1, i[2] - 1
    # print(row, column, val)
    f.write(f"{val + sqn*column + fn * row + 1} ")
    f.write("0\n")


for row in range(sqn):
    for column in range(sqn):
        for val1 in range(sqn):
            for val2 in range(sqn):
                if val1 < val2:
                    f.write(f"{-(val1 + sqn*column + fn * row + 1)} {-(val2 + sqn*column + fn* row + 1)} 0\n")

for value in range(sqn):
    for row in range(sqn):
        for column in range(sqn):
            for column2 in range(sqn):
                if column < column2:
                    f.write(f"{-(value + sqn*column + fn * row + 1)} {-(value + sqn*column2 + fn* row + 1)} 0\n")
for value in range(sqn):
    for column in range(sqn):
        for row in range(1,sqn):
            for row2 in range(sqn):
                if row < row2:
                    f.write(f"{-(value + sqn*column + fn * row + 1)} {-(value + sqn*column + fn* row2 + 1)} 0\n")

string = ""
for i in range(n**6):
    if (i % sqn == 0 and i != 0) :
        f.write(string + "0\n")
        string = ""
    string = string + str(i + 1) + " "

f.write(string + "0\n")

for row in range(sqn):
    for val in range(sqn):
        string = ""
        for column in range(sqn):
            string += f"{val + sqn*column + fn* row + 1} "
        string += "0\n"
        f.write(string)
        string = ""
# f.write("\n")
for column in range(sqn):
    for val in range(sqn):
        string = ""
        for row in range(sqn):
            string += f"{val + sqn*column + fn * row + 1} "
        string += "0\n"
        f.write(string)
        string = ""
# f.write("done")

for value in range(sqn):
    clauses= ["" for i in range(sqn)]
    for row in range(sqn):
        for column in range(sqn):
            i = column // n
            j = row // n
            clauses[n * i + j] += f"{value + sqn*column + fn * row + 1} "
    # print(clauses)
    # print(value)
    for clause in clauses:
        f.write(clause)
        f.write("0\n")
        

    
