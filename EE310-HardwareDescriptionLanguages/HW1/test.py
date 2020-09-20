import random

N = 50

A3 = [0]*N
A2 = [0]*N
A1 = [0]*N
A0 = [0]*N
B3 = [0]*N
B2 = [0]*N
B1 = [0]*N
B0 = [0]*N
C3 = [0]*N
C2 = [0]*N
C1 = [0]*N
C0 = [0]*N

for i in range(N):
    A3[i] = random.randint(0, 255)
    A2[i] = random.randint(0, 255)
    A1[i] = random.randint(0, 255)
    A0[i] = random.randint(0, 255)
    B3[i] = random.randint(0, 255)
    B2[i] = random.randint(0, 255)
    B1[i] = random.randint(0, 255)
    B0[i] = random.randint(0, 255)
    C3[i] = (((A3[i]*B0[i]) % 256) + ((A2[i]*B1[i]) % 256) + ((A1[i]*B2[i]) % 256) + ((A0[i]*B3[i]) % 256)) % 256
    C2[i] = (((((A2[i]*B0[i]) % 256) + ((A1[i]*B1[i]) % 256) + ((A0[i]*B2[i]) % 256)) % 256) - ((A3[i]*B3[i]) % 256)) % 256
    C1[i] = (((((A1[i]*B0[i])%256) + ((A0[i]*B1[i])%256)) % 256) - ((((A3[i]*B2[i])%256) + ((A2[i]*B3[i])%256)) % 256)) % 256
    C0[i] = (((A0[i]*B0[i]) % 256) - ((((A3[i]*B1[i])%256) + ((A2[i]*B2[i])%256) + ((A1[i]*B3[i])%256)) % 256)) % 256


#Generating txt files
first_file = open("A3.txt", "w")
second_file = open("A2.txt", "w")
third_file = open("A1.txt", "w")
fourth_file = open("A0.txt", "w")
fifth_file = open("B3.txt", "w")
sixth_file = open("B2.txt", "w")
seventh_file = open("B1.txt", "w")
eighth_file = open("B0.txt", "w")
ninth_file = open("C3.txt", "w")
tenth_file = open("C2.txt", "w")
eleventh_file = open("C1.txt", "w")
twelveth_file = open("C0.txt", "w")

#Writing generated data into txt files
for i in range(N):
    first_file.write( format(A3[i], '#010b')[2:] + "\n")
    second_file.write( format(A2[i], '#010b')[2:] + "\n")
    third_file.write( format(A1[i], '#010b')[2:] + "\n")
    fourth_file.write( format(A0[i], '#010b')[2:] + "\n")
    fifth_file.write( format(B3[i], '#010b')[2:] + "\n")
    sixth_file.write( format(B2[i], '#010b')[2:] + "\n")
    seventh_file.write( format(B1[i], '#010b')[2:] + "\n")
    eighth_file.write( format(B0[i], '#010b')[2:] + "\n")
    ninth_file.write( format(C3[i], '#010b')[2:] + "\n")
    tenth_file.write( format(C2[i], '#010b')[2:] + "\n")
    eleventh_file.write( format(C1[i], '#010b')[2:] + "\n")
    twelveth_file.write( format(C0[i], '#010b')[2:] + "\n")

#Closing txt files
first_file.close()
second_file.close()
third_file.close()
fourth_file.close()
fifth_file.close()
sixth_file.close()
seventh_file.close()
eighth_file.close()
ninth_file.close()
tenth_file.close()
eleventh_file.close()
twelveth_file.close()