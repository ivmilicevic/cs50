import cs50


while True:
    print("Height: ", end="")
    pyramid_height = cs50.get_int()
    if pyramid_height > 0 and pyramid_height < 24:
        break
    
total_columns = pyramid_height

for row in range(pyramid_height):
    number_hashes = 1 + row
    number_spaces = total_columns - number_hashes
    print(" " * number_spaces, end="")
    print("#" * number_hashes, end="")
    print("  ", end="")
    print("#" * number_hashes, end="")
    print(" " * number_spaces, end="")
    print()
