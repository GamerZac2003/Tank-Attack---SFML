import pandas, matplotlib
import matplotlib.pyplot as plt
import json



colorArr = [
    (0/255.0, 0/255.0, 255/255.0    ,0.75),
    (255/255.0, 0/255.0, 0/255.0    ,0.75),
    (0/255.0, 255/255.0, 0/255.0    ,0.75),
    (255/255.0, 255/255.0, 0/255.0  ,0.75),
    (255/255.0, 32/255.0, 128/255.0 ,0.75),
    (128/255.0, 0/255.0, 255/255.0  ,0.75),
    (0/255.0, 255/255.0, 255/255.0  ,0.75),
    (128/255.0, 48/255.0, 0/255.0   ,0.75),
    (64/255.0, 64/255.0, 64/255.0   ,0.75),
    (255/255.0, 128/255.0, 0/255.0  ,0.75),
    (0/255.0, 255/255.0, 128/255.0  ,0.75),
    (150/255.0, 119/255.0, 75/255.0 ,0.75),
    (128/255.0, 0/255.0, 64/255.0   ,0.75),
    (0/255.0, 128/255.0, 255/255.0  ,0.75),
    (200/255.0, 200/255.0, 200/255.0,0.75),
    (1/255.0, 1/255.0, 1/255.0      ,0.75)
]

figure, axis = plt.subplots(2, 2)


file = open("TankPop.json")
x = json.load(file)
team_no = len(x[0])
for team in range(team_no):
    array_x = []
    array_y = []
    array_col = []
    for j in range(len(x)):
    	array_x.append(x[j][team])
    	array_y.append(j)
    
    axis[0][0].plot(array_y, array_x, c=colorArr[team])
    axis[0][0].set_ylabel("Tank Population")
    




file = open("FortPop.json")
x = json.load(file)
team_no = len(x[0])
for team in range(team_no):
    array_x = []
    array_y = []
    array_col = []
    for j in range(len(x)):
        array_x.append(x[j][team])
        array_y.append(j)

        

    axis[0][1].plot(array_y, array_x, c=colorArr[team])
    axis[0][1].set_ylabel("Fort Population")



file = open("SpecialTankPop.json")
x = json.load(file)
team_no = len(x[0])
for team in range(team_no):
    array_x = []
    array_y = []
    array_col = []
    for j in range(len(x)):
        array_x.append(x[j][team])
        array_y.append(j)
        

    axis[1][0].plot(array_y, array_x, c=colorArr[team])
    axis[1][0].set_ylabel("Special Tank Population")


file = open("SpecialFortPop.json")
x = json.load(file)
team_no = len(x[0])
for team in range(team_no):
    array_x = []
    array_y = []
    array_col = []
    for j in range(len(x)):
        array_x.append(x[j][team])
        array_y.append(j)
        

    axis[1][1].plot(array_y, array_x, c=colorArr[team])
    axis[1][1].set_ylabel("Special Fort Population")





plt.show()


# Plot ScatterGraph for Tanks Killed/Lost
figure, axis = plt.subplots(1)

TanksKilled_file = open("TanksKilled.json")
TanksLost_file = open("TanksLost.json")

killed_json = json.load(TanksKilled_file)
lost_json = json.load(TanksLost_file)
team_no = len(killed_json[0])
for team in range(team_no):
    killed_array = []
    lost_array = []
    for j in range(len(killed_json)):
        killed_array.append(killed_json[j][team])
        lost_array.append(lost_json[j][team])

   

    axis.plot(lost_array, killed_array, c=colorArr[team])
    axis.set_xlabel("Tanks Lost")
    axis.set_ylabel("Tanks Killed")

plt.show()

# 
figure, axis = plt.subplots(1,2)


for team in range(team_no):
    killed_array = []
    lost_array = []
    normal_array = []

    for i in range(len(killed_json)):
        killed_array.append(killed_json[i][team])
        lost_array.append(lost_json[i][team])
        normal_array.append(i)

    axis[0].plot(normal_array, killed_array, c=colorArr[team])
    axis[1].plot(normal_array, lost_array, c=colorArr[team])

axis[0].set_ylabel("Tanks Killed")
axis[1].set_ylabel("Tanks Lost")

plt.show()




# Plot Average Tank Age
figure, axis = plt.subplots(1)
AverageAgeData = open("AverageTankAge.json")
AverageAgeJsonData = json.load(AverageAgeData)


for team in range(team_no):
    AverageAgeArray = []
    for i in range(len(AverageAgeJsonData)):
        AverageAgeArray.append([AverageAgeJsonData[i][team]])
    axis.plot(normal_array, AverageAgeArray, c=colorArr[team])
    axis.set_ylabel("Average Tank Age (ms)")
    axis.set_xlabel("Time (ticks)")

plt.show()


# Plot Average Tank Age
figure, axis = plt.subplots(1)
TerritoryData = open("Territory.json")
TerritoryJsonData = json.load(TerritoryData)


for team in range(team_no):
    TerritoryArray = []
    for i in range(len(TerritoryJsonData)):
        TerritoryArray.append([TerritoryJsonData[i][team]])
    axis.plot(normal_array, TerritoryArray, c=colorArr[team])
    axis.set_ylabel("Territory Tiles")
    axis.set_xlabel("Time (ticks)")

plt.show()