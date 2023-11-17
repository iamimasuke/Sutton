import random

def diceGame():
    score = 100
    while True:
        print(f"あなたの今のスコアは{score}です。ゲームを続けますか？")
        q = input("y/n？:")
        if q == "n":
            break
        else:
           dice = random.randint(1,6) 
           if dice == 1:
               score = 0
               print('残念！1が出ました')
               break
           else:
               score += dice
    print(f"あなたの総合スコアは{score}です")

diceGame()


        