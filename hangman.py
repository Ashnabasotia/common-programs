import random

stream=open("words.txt",'r')
words=stream.read().split()

#size = size of word
def Select(size):
	selected=words[random.randint(0,len(words))]
	if(len(selected)<size):
		return Select(size)
	else:
		return selected

#word to cutoff , %of cuts in range 0-1 
def Cutoff(word,cuts):
	done_cuts=0
	word_=""
	lis=[]
	length=len(word)
	for i in range(0,length):lis.append(i)
	random.shuffle(lis)
	#print(lis)
	lis=lis[0:int(length*cuts)]
	#print(lis)
	for i in range(0,length):
		if(i not in lis):
			word_+="-"
		else:
			word_+=word[i]
	return word_

def start_game(iter):
	for i in range(iter):hangman()

def checkHangman(word,shown):
	chances=5
	while(chances>0):
		letter=input()
		found=0
		for i in range(len(word)):
			if(letter==word[i] and shown[i]=='-'):
				found=1
				break
		if(found==1):
			words=""
			for i in range(len(word)):
				if(word[i]==letter and shown[i]=='-'):
					words+=word[i]
				else:
					words+=shown[i]
			shown=words
			if(shown==word):
				return 1
			print(shown)
		else:
			chances-=1
			print("Wrong Guess "+str(chances)+" chances left")
			print(shown)
	return 0

def hangman():
	print("guess this word")
	word=Select(5)
	display=Cutoff(word,0.70)
	print(display)
	result=checkHangman(word,display)
	if(result==1):
		print(word)
		print("You Won")
	else:
		print("You Lost ,The word was "+word)

start_game(1)
