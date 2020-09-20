import random

N = 25

lens = [0]*N
A = [0]*N
B = [0]*N
C = [0]*N
# 2**(16*(lens[i] - 1))
# generating random numbers
for i in range(N):
    lens[i] = random.randint(1, 8)
    A[i] = random.randint(0, 2**(16*lens[i]) - 1)
    B[i] = random.randint(0, 2**(16*lens[i]) - 1)
    C[i] = A[i] * B[i]

#Type your project path below 
completepath = "C:/Users/dogan/Alpobaba/Alpobaba/School/2019-2020 Spring/EE 310/Labs/Lab3/Lab3_Code/lab3_code"

# generating txt files
lens_file = open(completepath + "lens.txt", "w")
A_file = open(completepath + "A.txt", "w")
B_file = open(completepath + "B.txt", "w")
C_file = open(completepath + "C.txt", "w")

# writing generated data into txt files
for i in range(N):
    format_type_lens = "{:04b}".format(lens[i])
    format_type = '#0' + str(16*lens[i]) + 'b'
    format_type_c = '#0' + str(32*lens[i]) + 'b'

    lens_file.write(format_type_lens + "\n")
    A_file.write(format(A[i], format_type)[2:] + "\n")
    B_file.write(format(B[i], format_type)[2:] + "\n")
    C_file.write(format(C[i], format_type_c)[2:] + "\n")

# closing txt file
lens_file.close()
A_file.close()
B_file.close()
C_file.close()