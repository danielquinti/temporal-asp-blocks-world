#program dynamic. % Transition from t-1 to t

%Executability axioms
% Only one of the available actions can be selected
1{o(A):'action(A)}1.

%Effect axioms
% Unmoved blocks remain on the same blocks.
on(X,Y) :- 'on(X,Y), not o(move(X,_)).
% Moving a block places it on top of another one.
on(X,Y) :- o(move(X,Y)).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#program always. % Any timepoint t=0..n-1
% A block X is arranged if the block Y underneath it is arranged and
% the description of the goal contains g(X,Y)
% As a base case for the recursion, 0 is always arranged
arranged(X):-on(X,Y),_g(X,Y),arranged(Y).
arranged(0).

% Only two actions are created for each block
% In order to move it onto the table (represented as 0) the block
% must neither be already on the table nor already arranged.
% Blocks with anything on them cannot be moved to the table
% either.
action(move(X,0)):-on(X,Y), Y!=0, not arranged(X), not on(_,X).
% A block X can only be moved towards the block on which it sits 
% on the goal(Y). In addition, X and Y cannot have anything over
% them 
action(move(X,Y)):-_g(X,Y),not on(_,X),not on(_,Y).

#show o/1.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#program final. % Last timepoint t=n-1
:-_g(X,Y), not on(X,Y).