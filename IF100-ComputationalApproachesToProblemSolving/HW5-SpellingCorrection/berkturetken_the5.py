#Berk Turetken
#18.05.2020
#IF100, Take-Home Exam #5

def levenshtein(str1, str2):
  size_x = len(str1) + 1
  size_y = len(str2) + 1
  matrix = []
  for i in range(size_x):
    temp = [0]*size_y
    matrix.append(temp)
  for i in range(size_x):
    matrix[i][0] = i
  for i in range(size_y):
    matrix[0][i] = i
  for x in range(1, size_x):
      for y in range(1, size_y):
          if str1[x-1] == str2[y-1]:
              matrix [x][y] = min(matrix[x-1][y] + 1, matrix[x-1][y-1], matrix[x][y-1] + 1)
          else:
            matrix [x][y] = min(matrix[x-1][y] + 1, matrix[x-1][y-1] + 1, matrix[x][y-1] + 1)
  return(matrix[size_x - 1][size_y - 1])


def preprocessingFile(toBeReadFile, wordDict):
  inFile = open(toBeReadFile, 'r')
  for line in inFile:
    line = line.replace('.', '')
    line = line.replace(',', '')    
    line = line.replace('!', '')
    line = line.replace('?', '')
    line = line.replace(':', '')
    line = line.replace('"', '')
    line_without_punctuation = line.replace(';', '')
    
    preprocessedLine = line_without_punctuation.lower()
    for word in preprocessedLine.split():
      if (word in wordDict):
        wordDict[word] += 1
      else:
        wordDict[word] = 1

  inFile.close()


def spellingCheck(usersString, wordDict):
  isChange = False
  minDist = float('inf')
  occurance = 0
  predictedString = ""
  predictedWord = ""

  for word in usersString.split():
    if(word not in wordDict):
      isChange = True
      for k, v in wordDict.items():
        currDist = levenshtein(word, k)
        if(currDist < minDist):
          predictedWord = k
          minDist = currDist
          occurance = v
        elif(currDist == minDist and v > occurance):
          predictedWord = k
          occurance = v
        elif(currDist == minDist and v == occurance and k < predictedWord):
          predictedWord = k
      predictedString += " " + predictedWord
    else:
      predictedString += " " + word  
    
    minDist = float('inf')
    occurance = 0
  
  predictedString = predictedString.strip()   #remove the first blank part from the string

  if(isChange):
    print("Did you mean: " + predictedString)
  else:
    print("String you entered is correctly written!")

#Main program
toBeReadFile = 'book.txt'
wordDict = {}
preprocessingFile(toBeReadFile, wordDict)

string_to_spell_check = input("Please enter the word/words you want to check: ")
while(string_to_spell_check != "exit()"):
  spellingCheck(string_to_spell_check, wordDict)
  string_to_spell_check = input("Please enter the word/words you want to check: ")

print("See you next time...")