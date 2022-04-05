from decimal import *

def is_decimal(s):
    try:
        Decimal(s)
        return True
    except:
        return False

def average(file):
    f = open(file, "r")
    dest = open("average_result_proteins_approx_mut.txt", "x")
    count = 1
    sum = 0
    try:
        for i in f:
            if is_decimal(i):
                num = Decimal(i)
                if count == 3:
                    sum = sum + num
                    avg = (sum / 3).quantize(Decimal('.01'))
                    sum = 0
                    count = 1
                    dest.write(str(avg) + "\n")
                else:
                    sum = sum + num
                    count += 1
            else:
                aux = i.split(" ")
                aux = aux[0] + "\n"
                dest.write(aux)
    finally:
        f.close()
        dest.close()

def main():
    average("result_proteins_approx_mut.txt")

if __name__ == "__main__":
    main()
