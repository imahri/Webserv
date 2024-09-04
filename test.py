# !/usr/bin/env python
# import cgi

print("Content-type: text/html\r\n\r\n")

def factorial(n):
    if n == 0 or n == 1:
        return 1
    else:
        return n * factorial(n - 1)

number = 150  # Predefined number

result = factorial(number)
print(f"The factorial of {number} is {result}.")