# inf=open("2016.csv",'r')
# inf=open("2017.csv",'r')
# Program takes in data from a .csv of NFL games by season
# It analyzes results from the games, by team
# Determing the average points each team allowed
# in home and away games, averaging the results
# Goal of program is to show how "homefield advantage" affects scores

# Create two sets to handle data for teams when away and when home
teamAway={}
teamHome={}
inf.readline()

# Read through .csv
for line in inf:
    line=line.split(",")
    # Determine the winning and losing score of a game
    winScore=float(line[8])
    loseScore=float(line[9])

    # Determine which team, winner or loser, was home
    # Add stats to relevant sets
    if line[5]=='@':
        if line[4] in teamAway:
            teamAway[line[4]]+=loseScore
        else:
            teamAway[line[4]]=loseScore
        if line[6] in teamHome:
            teamHome[line[6]]+=winScore
        else:
            teamHome[line[6]]=winScore
    else:
        if line[4] in teamHome:
            teamHome[line[4]]+=loseScore
        else:
            teamHome[line[4]]=loseScore
        if line[6] in teamAway:
            teamAway[line[6]]+=winScore
        else:
            teamAway[line[6]]=winScore

# Iterate through teams, and print average of results
# Repeat for teams away stats and home stats
for k in teamAway:
    ppg=teamAway[k]/8.0
    print(k+"\t"+str(ppg))
print("\n")
for k in teamHome:
    ppg=teamHome[k]/8.0
    print(k+"\t"+str(ppg))
