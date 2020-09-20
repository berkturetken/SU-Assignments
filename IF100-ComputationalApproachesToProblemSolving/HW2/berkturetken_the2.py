# Berk Turetken
# 21.03.2020
# Updated on 01.04.2020
# IF100, Take-Home Exam #2


def isInteger(checked_input):
    if(checked_input.isdigit()):
        return True
    else:
        return False


def convertToInteger(number):
    number = int(number)
    return number


def isValidLetterGradeEquivalance(course_letter_grade_equivalance):
    length = len(course_letter_grade_equivalance)
    colons_count = course_letter_grade_equivalance.count(":")
    semicolons_count = course_letter_grade_equivalance.count(";")

    if(course_letter_grade_equivalance.find(":") != 0 and
       course_letter_grade_equivalance.find(";") != 0 and
       course_letter_grade_equivalance.rfind(":") != length-1 and
       course_letter_grade_equivalance.rfind(";") != length-1 and
       colons_count == semicolons_count+1):
        return True
    else:
        return False 


def letterGradeCheck(letter_grades, course1_letter_grade_equivalance, course2_letter_grade_equivalance):
    #For our specific case;
    #course1_letter_grade_equivalance = SPS_101_letter_grade_equivalance
    #course2_letter_grade_equivalance = AL_102_letter_grade_equivalance
    length = len(letter_grades)
    if(letter_grades.count(",") == 1 and
       letter_grades.find(",") != 0 and
       letter_grades.rfind(",") != length-1):
        SPS101_grade = letter_grades.split(",")[0].strip() + ":"
        AL102_grade = letter_grades.split(",")[1].strip()

        if(AL102_grade == "-"):
            AL102_grade = "C:"
        else:
            AL102_grade += ":"

        if (course1_letter_grade_equivalance.find(SPS101_grade) < 0):
            return 2
        elif (course2_letter_grade_equivalance.find(AL102_grade) < 0):
            return 3
        else:
            return 1
    else:
        return 0


def isGpaValid(GPA):
    if(GPA <= 4 and GPA >= 0):
        if(GPA < 2.2):
            return 0
        else:
            return 1
    else:
        return -1


def getPointScale(course_Letter_Grade, course_letter_point_grades):
    point = 0
    length = len(course_Letter_Grade)
    index = course_letter_point_grades.index(course_Letter_Grade)
    point_index = index + length

    course_letter_point_grades = course_letter_point_grades[point_index:]
    border = course_letter_point_grades.find(";")

    if(border < 0):
        point = course_letter_point_grades
    else:
        point = course_letter_point_grades[:border]
    return float(point)


# Main Code starts here
current_term = input("Please enter your current term: ")

if(not isInteger(current_term)):
    print("Invalid input for the current term.")
else:
    #If the current term input consists of only digits
    current_term = convertToInteger(current_term)
    if current_term < 1:
        print("Invalid input for the current term.")
    elif current_term == 1:
        print("Your Erasmus score cannot be calculated before the 2nd term.")
    else:
        #If the current term input is greater or equal to 2
        total_credits = input("Please enter the total credits you earned before: ")
        if(not isInteger(total_credits)):
            print("Invalid input for the credits earned before.")
        else:
            #If the total credit input consists of only digits
            total_credits = convertToInteger(total_credits)
            if(not(current_term == 2 and total_credits >= 34)
                and not(current_term == 3 and total_credits >= 49)
                and not(current_term > 3 and total_credits >= 58)):
                print(
                    "Your Erasmus score cannot be calculated before you took the required amount of credits.")
            else:
                #If the total credit input meets the requirements
                SPS101_letter_grade_equivalents = input("Please enter the SPS101 letter grade equivalents: ")
                SPS101_letter_grade_equivalents = SPS101_letter_grade_equivalents.upper()
                if(not isValidLetterGradeEquivalance(SPS101_letter_grade_equivalents)):
                    print("Invalid input for SPS101 letter grade sequence.")
                else:
                    #If SPS101 letter grade equivalent input is a valid input
                    AL102_letter_grade_equivalents = input("Please enter the AL102 letter grade equivalents: ")
                    AL102_letter_grade_equivalents = AL102_letter_grade_equivalents.upper()
                    if(not isValidLetterGradeEquivalance(AL102_letter_grade_equivalents)):
                        print("Invalid input for AL102 letter grade sequence.")
                    else:
                        #If AL102 letter grade equivalent input is a valid input
                        SPS101_AL102_letter_grades = input("Please enter your SPS101 and AL102 letter grades: ")
                        SPS101_AL102_letter_grades = SPS101_AL102_letter_grades.upper()
                        if(letterGradeCheck(SPS101_AL102_letter_grades, SPS101_letter_grade_equivalents, AL102_letter_grade_equivalents) == 0):
                            print("Invalid input for SPS101 and AL102 letter grades.")
                        elif(letterGradeCheck(SPS101_AL102_letter_grades, SPS101_letter_grade_equivalents, AL102_letter_grade_equivalents) == 2):
                            print("Your SPS101 letter grade couldn't be found in point-scale.")
                        elif(letterGradeCheck(SPS101_AL102_letter_grades, SPS101_letter_grade_equivalents, AL102_letter_grade_equivalents) == 3):
                            print("Your AL102 letter grade couldn't be found in point-scale.")
                        else:
                            #If user's SPS101 and AL102 letter grades are valid
                            current_GPA = float(input("Please enter your current GPA: "))
                            if(isGpaValid(current_GPA) == -1):
                                print("Your GPA needs to be in between 0-4.")
                            elif(isGpaValid(current_GPA) == 0):
                                print("Your GPA needs to be at least 2.2.")
                            else:
                                #If current GPA input is valid for erasmus program
                                SPS101_letter_grade = SPS101_AL102_letter_grades.split(",")[0].strip() + ":"
                                AL102_letter_grade = SPS101_AL102_letter_grades.split(",")[1].strip()

                                # Below code is not looking good...
                                if(AL102_letter_grade == "-"):
                                    AL102_letter_grade = "C:"
                                else:
                                    AL102_letter_grade += ":"

                                english_score = (getPointScale(SPS101_letter_grade, SPS101_letter_grade_equivalents)) * 0.4 \
                                              + (getPointScale(AL102_letter_grade, AL102_letter_grade_equivalents) * 0.6)
                                erasmus_score = (current_GPA * 25 * 0.5) + (english_score * 0.5)
                                print("Your final Erasmus score is, ", erasmus_score, ".", sep="")