#このシュミレーションでは扉を1,2,3と数字に置き換えて扱う。
import random

total=0#試行回数
win=0#当たりの回数

#100000回シュミレーション
for count in range(100000):
    #あたりの扉を設定
    hitDoor=random.randint(1,3)
    #プレイヤーの選択した扉を設定
    playerSelect=random.randint(1,3)
    #正解でもない、プレイヤーも選択していない扉の番号を見つける。その扉をshowDoorとなづける
    for i in range(1,4):
        if hitDoor!=i and playerSelect!=i:
            showDoor=i
            break
    #プレイヤーの選択を変更させる。
    for i in range(1,4):
        if showDoor!=i and playerSelect!=i:
            playerSelect=i
            break
    if hitDoor==playerSelect:
        win+=1
    total+=1
ration=win/total*100
print(f"{ration}%")