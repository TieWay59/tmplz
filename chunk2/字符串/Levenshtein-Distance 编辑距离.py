import math

# https://www.jianshu.com/p/a617d20162cf
def Levenshtein_Distance(str1, str2):
    """
    计算字符串 str1 和 str2 的编辑距离
    :param str1
    :param str2
    :return:
    """
    matrix = [[i + j for j in range(len(str2) + 1)] for i in range(len(str1) + 1)]

    for i in range(1, len(str1) + 1):
        for j in range(1, len(str2) + 1):
            if (str1[i - 1] == str2[j - 1]):
                d = 0
            else:
                d = 1

            matrix[i][j] = min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + d)

    return matrix[len(str1)][len(str2)]

# num's bit format.
def bindigits(num, bits):
    s = bin(num & int("1"*bits, 2))[2:]
    return ("{0:0>%s}" % (bits)).format(s)

if __name__ == "__main__":


    for i in range(0,255):
        if(Levenshtein_Distance("1010", bindigits(i, 4))>2):
            print(bindigits(i, 4))
            print(Levenshtein_Distance("10101010", bindigits(i, 4)))
