import cs50

while True:
    print("O hai! How much change is owed? ", end="")
    total_dollars = cs50.get_float()
    if total_dollars > 0:
        break
    
total = int(total_dollars * 100)
coins = 0

coin_values = [25, 10, 5, 1]
for x in coin_values:
    if(total % x < x):
        coins += total // x
        total = total % x
    
print(coins)