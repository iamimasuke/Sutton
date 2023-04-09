total=0
win=0

for count in range(100000):
    hitDoor=random.randint(1,3)
    playerSelect=random.randint(1,3)
    for i in range(1,4):
        if(hitDoor!=i and playerSelect!=i):
            showDoor=i
            break
    for i in range(1,4):
        if(showDoor!=i and playerSelect!=i):
            playerSelect=i
            break
    if(hitDoor==playerSelect):
        win+=1
    total+=1
ration=win/total
print(win,total)
print(ration)