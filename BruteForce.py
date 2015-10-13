import random
import os

#program to generate random test cases
#and find the failed test case of the solution using brute force solution


#generate random test cases 
def generate():
	strs=""
	N=1
	strs+=str(N)+"\n"
	for i in range(0,N):
		strs+=str(random.randint(1,100))+"\n"
	return strs

for i in range(0,100):
	strs=generate()
	p=open("inps12.txt","w")
	p.write(strs)
	p.close()
	
	proc=os.popen('bruteSolution.exe<inps12.txt')
	Act_output=proc.read()
	proc.close()
	proc2=os.popen('optimizedSol.exe<inps12.txt')
	My_output=proc2.read()
	proc2.close()
	if(Act_output!=My_output):
		print(strs)





