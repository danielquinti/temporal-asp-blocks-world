#Group members: Daniel Quintillán Quintillán, Sergio García Cascón.
#Emails: daniel.quintillan@udc.es, sergio.gcascon@udc.es
import sys
import subprocess
def facts(towers,goal,num_blocks):
	aux=""
	if goal:
		for tower in towers:
			i=0
			tower=tower.split(' ')[:-1]
			for number in tower:
				if i==0:
					aux+="g("+number+','+str(i)+').\n'
				else:
					aux+="g("+number+','+str(tower[i-1])+').\n'
				i+=1
	else:
		aux+="#program initial. % At timepoint t=0\n"
		for tower in towers:
			i=0
			tower=tower.split(' ')[:-1]
			for number in tower:
				if i==0:
					aux+="on("+number+','+str(i)+').\n'
				else:
					aux+="on("+number+','+str(tower[i-1])+').\n'
				i+=1
	return aux


def parse(input_file_name):
	input_file = open(input_file_name,'r')
	text=input_file.read()
	lines = text.split("\n")
	input_file.close()

	#the first two lines represent the dimensions of the problem
	num_blocks = int(lines[0])
	description=text[2:].split('\n\n')
	initial_towers=description[0].split('\n')
	goal=description[1]
	goal_towers=description[1][:-1].split('\n')
	processed=""
	processed+=facts(initial_towers,0,num_blocks)
	processed+=facts(goal_towers,1,num_blocks)
	output_file_name="concrete_problem.lp"
	output_file = open(output_file_name,'w')
	output_file.write(processed)
	output_file.close()


if __name__ == '__main__':
	parse(sys.argv[1])
	subprocess.call("telingo --verbose=0 blocks_world.lp concrete_problem.lp > result.txt",shell=True)
	result_file=open("result.txt","r")
	result=result_file.readlines()
	result_file.close()
	actions=result[3::2]
	actions_string=""
	for action in actions:
		action= action.replace('  o(move','m').replace(')\n','\n')
		actions_string+=action
	result_file=open("result.txt","w")
	result_file.write(actions_string)
	result_file.close()
	subprocess.call("cd checker/chk && make && cd ../../ && ./checker/chk/checker "+ sys.argv[1] +" result.txt",shell=True)