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