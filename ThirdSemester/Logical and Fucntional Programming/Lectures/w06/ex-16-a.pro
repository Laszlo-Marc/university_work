% FIVE HOUSES

% There are 15 facts and 2 questions:
% Who has a zebra and who drinks water?
%
%  1) There are 5 colored houses in a row, each with an owner, an animal, a cigarette, a drink.
%  2) The English lives in the red house.
%  3) The Spanish has a dog.
%  4) They drink coffee in the green house.
%  5) The Ukrainian drinks tea.
%  6) The green house is next to the white house.
%  7) The Winston smoker has a serpent.
%  8) In the yellow house they smoke Kool.
%  9) In the middle house they drink milk.
% 10) The Norwegian lives in the first house from the left.
% 11) The Chesterfield smoker lives near the man with the fox.
% 12) In the house near the house with the horse they smoke Kool.
% 13) The Lucky Strike smoker drinks juice.
% 14) The Japanese smokes Kent.
% 15) The Norwegian lives near the blue house.
%
% We represent the houses as a list with 5 lists from left to right:
% Sol = [[Man, Animal, Cigarette, Drink, Color], [..],[..],[..],[..] ]

write_list([]).
write_list([H|T]) :-
  write(H), nl,
  write_list(T).

next_to(X,Y,[X,Y|_]).
next_to(X,Y,[_|L]) :-
  next_to(X,Y,L).

near(X,Y,L) :- next_to(X,Y,L).
near(X,Y,L) :- next_to(Y,X,L).

start:- 
  Sol = [_,_,_,_,_],                              % 1
	member([english,_,_,_,red],Sol), 		            % 2
	member([spanish,dog,_,_,_],Sol),  		          % 3
	member([_,_,_,coffee,green],Sol),		            % 4
	member([ukrainian,_,_,tea,_],Sol),		          % 5 
	near([_,_,_,_,white],[_,_,_,_,green], Sol),     % 6
	member([_,snake,winston,_,_],Sol), 		          % 7
	member([_,_,kool,_,yellow],Sol),		            % 8
	Sol= [_,_,[_,_,_,milk,_],_,_],			            % 9	
  Sol= [[norwegian,_,_,_,_],_,_,_,_],   	        % 10
	near([_,_,chesterfield,_,_],[_,fox,_,_,_],Sol), % 11
	near([_,_,kool,_,_],[_,horse,_,_,_], Sol),	    % 12
	member([_,_,lucky,juice,_],Sol),			          % 13
	member([japanese,_,kent,_,_],Sol),			        % 14
	near([norwegian,_,_,_,_],[_,_,_,_,blue],Sol), 	% 15
	member([_,_,_,water,_],Sol),  	                % someone drinks water
	member([_,zebra,_,_,_],Sol),	                  % someone has a zebra
	write_list(Sol).  			
