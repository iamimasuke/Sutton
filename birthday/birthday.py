import random
import csv

rate = []

success = 0

for i in range(2, 40):
    score = 0
    total = 0
    for count in range(1000) :
        dates = set()
        for date in range(i):
            dates.add(random.randint(1,365))
        if len(dates) != i:
            score += 1
        total  += 1
   
    rate.append((i, score / total * 100))
    
    if  (score / total * 100)> 50 and success ==0:
        print(f"{i}人目で50%の確率を超えました")
        success = 1
    




with open('./birthday.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    for row in rate:
        writer.writerow(row)