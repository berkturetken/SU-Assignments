#Berk Turetken
#02.05.2020
#IF100, Take-Home Exam #4

def getPartyName(partyOrder, partyNamesList):
  promptedQuestion = "Please enter the name of the " + partyOrder + " party: " 
  partyName = input(promptedQuestion)
  partyName = partyName.capitalize()
  indexOfSpace = partyName.find(" ")
  asciiNumber = ord(partyName[0])
  
  while(indexOfSpace != -1 or asciiNumber < 65 or asciiNumber > 122 or (asciiNumber > 90 and asciiNumber < 97) or partyName in partyNamesList):
    if(partyName in partyNamesList):
      promptedQuestion = partyName + " already exists. Please enter again: "
    else:
      promptedQuestion = "Invalid party name. Please enter again: "
  
    partyName = input(promptedQuestion)
    partyName = partyName.capitalize()
    indexOfSpace = partyName.find(" ")
    asciiNumber = ord(partyName[0])
  
  partyNamesList.append(partyName)


def getMenuOption():
  validOptions = ["1", "2", "3", "4"]
  print("\nMenu:\n1. Enter results for a new city.\n2. Change results of a specific city.\n3. Show current results.\n4. Exit.\n")
  selectedOption = input("Select one of the options (1-4): ")

  while(selectedOption not in validOptions):
    selectedOption = input("You have entered an invalid input for menu selection. Please enter again: ")
  return selectedOption


def getNewResults(citiesAndResults):
  isExist = False
  cityName = input("Please enter the name of the city: ")

  while(not cityName.isalpha()):
    cityName = input("Invalid city name. Please enter again: ")

  cityName = cityName.capitalize()
  for i in range(len(citiesAndResults)):
    if(citiesAndResults[i][0] == cityName):
      isExist = True
  
  if(isExist):
    print("You cannot enter  " + cityName + "  since this city has already been entered. If you want",
          "you can update the results of this city by using the 2nd menu option." )
  else:
    promptedQuestion = "Please enter results for " + cityName + ": "
    resultsForThatCity = input(promptedQuestion)
    resultsForThatCity = resultsForThatCity.split("-")

    firstPartyResult = float(resultsForThatCity[0])
    secondPartyResult = float(resultsForThatCity[1])
    thirdPartyResult = float(resultsForThatCity[2])

    cityAndResults = [cityName, firstPartyResult, secondPartyResult, thirdPartyResult]
    citiesAndResults.append(cityAndResults)


def changeResults(citiesAndResults):
  isExist = False
  i = 0
  cityName = input("Please enter the name of the city: ")
  while(not cityName.isalpha()):
    cityName = input("Invalid city name. Please enter again: ")
  
  cityName = cityName.capitalize()
  for i in range(len(citiesAndResults)):
    if(citiesAndResults[i][0] == cityName):
      isExist = True
      break
  
  #Is space done intentionally or not???
  if(not isExist):
    print("You cannot change the result of ", cityName, " since no result has been entered for this city yet.")
  else:
    #Valid change
    promptedQuestion = "Please enter results for " + cityName + ": "
    updatedResultsForThatCity = input(promptedQuestion)
    updatedResultsForThatCity = updatedResultsForThatCity.split("-")

    updatedFirstPartyResult = float(updatedResultsForThatCity[0])
    updatedSecondPartyResult = float(updatedResultsForThatCity[1])
    updatedThirdPartyResult = float(updatedResultsForThatCity[2])

    citiesAndResults[i][1] = updatedFirstPartyResult
    citiesAndResults[i][2] = updatedSecondPartyResult
    citiesAndResults[i][3] = updatedThirdPartyResult
    

def showResults(citiesAndResults, partyNamesList):
  if not citiesAndResults:
    print("No information available yet...")
  else:
    for i in range(len(citiesAndResults)):
      leadingResult = 0
      leadingPartyIndices = []
      cityName = citiesAndResults[i][0]
      if(citiesAndResults[i][1] >= leadingResult):
        leadingPartyIndices.append(0)
        leadingResult = citiesAndResults[i][1]
      
      if(citiesAndResults[i][2] >= leadingResult):
        if(citiesAndResults[i][2] > leadingResult):
          leadingPartyIndices.pop()
        leadingPartyIndices.append(1)
        leadingResult = citiesAndResults[i][2]

      if(citiesAndResults[i][3] >= leadingResult):
        if(citiesAndResults[i][3] > leadingResult):
          leadingPartyIndices.pop()
        leadingPartyIndices.append(2)
        leadingResult = citiesAndResults[i][3]

      firstPartyResult = citiesAndResults[i][1]
      secondPartyResult = citiesAndResults[i][2]
      thirdPartyResult = citiesAndResults[i][3]

      if(len(leadingPartyIndices) == 1):
        index = leadingPartyIndices[0]
        print(cityName, firstPartyResult, secondPartyResult, thirdPartyResult, "-->", partyNamesList[index], "is leading")
      elif(len(leadingPartyIndices) == 2):
        index1 = leadingPartyIndices[0]
        index2 = leadingPartyIndices[1]
        print(cityName, firstPartyResult, secondPartyResult, thirdPartyResult, "-->", partyNamesList[index1], partyNamesList[index2], "are leading")
      else: #len(leadingPartyIndices) == 3
        index1 = leadingPartyIndices[0]
        index2 = leadingPartyIndices[1]
        index3 = leadingPartyIndices[2]
        print(cityName, firstPartyResult, secondPartyResult, thirdPartyResult, "-->", partyNamesList[index1], partyNamesList[index2], partyNamesList[index3], "are leading")

#############################
## DO NOT MODIFY THIS CELL ##
## JUST RUN THIS WHEN YOU COMPLETE YOUR FUNCTIONS ##
#############################
####### MAIN PROGRAM ########
#############################

print("Welcome to this virtual local elections Python program.\n")

# get the names of the parties
partyNames = []                               # stores the valid party names
promptData = ["first", "second", "third"]
for i in range(3):
  getPartyName(promptData[i], partyNames)

# dataset variable initialization
citiesAndResults = []                         # stores the city-results information

# display the menu, get user's option, and process accordingly
option = getMenuOption()
while option != "4":
  if option == "1":
    getNewResults(citiesAndResults)           # function call to update citiesAndResults with a new city
  elif option == "2":
    changeResults(citiesAndResults)            # function call to update citiesAndResults for an existing city
  elif option == "3":
    showResults(citiesAndResults, partyNames) # function call to display current election results
  option = getMenuOption()
 
print("**********\nTerminating, good bye dear citizen!!! Do not forget to vote in elections :)")