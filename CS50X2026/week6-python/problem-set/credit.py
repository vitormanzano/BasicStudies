import re
from cs50 import get_string

def calculate_sum(number):
    round = 0
    otherDigits = 0
    digitsMultiplied = 0

    for digit in reversed(number):
        if round == 0:
            otherDigits += int(digit)
            round = 1
        else:
            d = int(digit) * 2
            digitsMultiplied += (d % 10) + (d // 10)
            round = 0

    return digitsMultiplied + otherDigits

def is_visa(number):
    if len(number) != 13 and len(number) != 16:
        return False
    if number[0] != "4":
        return False
    return True 

def is_american_express(number):
    if len(number) != 15:
        return False
    pattern = "^3[47]"
    result = re.match(pattern, number)
    if not result:
        return False
    return True

def is_master_card(number):
    if len(number) != 16:
        return False
    pattern = "^5[1-5]"
    result = re.match(pattern, number)
    if not result:
        return False
    return True

def print_type_card(number):
    if is_visa(number):
        print("VISA")
    elif is_american_express(number):
        print("AMEX")
    elif is_master_card(number):
        print("MASTERCARD")
    else:
        print("INVALID")

number = get_string("Number: ")
sum = calculate_sum(number)
if sum % 10 == 0:
    print_type_card(number)
else:
    print("INVALID")
