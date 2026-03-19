sentence=input()
words=sentence.split()

longestWord=max(words,key=len)
print(len(longestWord))