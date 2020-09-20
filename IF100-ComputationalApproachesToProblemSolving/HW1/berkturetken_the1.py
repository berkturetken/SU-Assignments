#Berk Turetken
#10.03.2020
#IF100, Take-Home Exam #1

#Taking the necessary inputs from the user
length_of_door_lock = input("Please enter the number of digits in padd-lock: ")
length_of_computer_password = input("Please enter the password length of the PC: ")
data_size = input("Please enter the file size you want to transfer (GB): ")

#Calculating time of the tasks according to the homework file
crack_time_of_door = pow(10, int(length_of_door_lock)) / 1000
crack_time_of_computer = pow(14, int(length_of_computer_password)) / 600000
time_for_data_transfer = float(data_size) * 1024 / 60

total_time = crack_time_of_door + crack_time_of_computer + time_for_data_transfer

#Extracting the hours from total_time(total_time is in terms of seconds)
hour = total_time // 3600
if (hour > 0):
    total_time -= int(hour) * 3600

#Extracting the minutes from total_time
minutes = total_time // 60
if(minutes > 0):
    total_time -= int(minutes) * 60

#Extracting the seconds from total_time
seconds = total_time

print("You need to distract the guard's attention for %d hour(s), %d minute(s) and %.2f second(s)." % (hour, minutes, seconds))