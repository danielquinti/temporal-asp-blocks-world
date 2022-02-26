https://www.dc.fi.udc.es/~cabalar/kr/2020/ex2.html
The general Blocks World problem representation is stored
in the file "blocks_world.lp". To represent and test the 
examples provided in the website, the script "parser.py" 
needs to be located in the same folder as the "checker"
uncompressed folder and executed like so:
>python3 parser.py example_file_path

The script parses the dom0X.txt file and transforms its
contents into ASP code, which is stored in the file "concrete_problem.lp". 
Then, telingo is called and the output of the internal 
call is redirected towards "result.txt" and processed to 
fit the preconditions of the checker.
Finally, the checker is built and executed to print 
whether the model is valid or not.

The average execution times we've obtained in our computers 
for each domain are listed below:

 · dom01, dom02, dom03 and dom04: nearly instantaneous.
 · dom05: ~ 9 seconds.
 · dom06: ~ 63 seconds.
