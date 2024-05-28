% Facts about the animals
animal(lion).
animal(elephant).
animal(zebra).
animal(penguin).
animal(kangaroo).

% Habitats
habitat(lion, savannah).
habitat(elephant, savannah).
habitat(zebra, savannah).
habitat(penguin, antarctica).
habitat(kangaroo, australia).

% Diets
diet(lion, carnivore).
diet(elephant, herbivore).
diet(zebra, herbivore).
diet(penguin, carnivore).
diet(kangaroo, herbivore).

% Rule to check if two animals share the same habitat
shares_habitat(Animal1, Animal2) :-
    habitat(Animal1, Habitat),
    habitat(Animal2, Habitat),
    Animal1 \= Animal2.

% Rule to recommend animals that live in the same habitat
recommend_same_habitat :-
    write('Enter the name of an animal: '),
    read(Animal),
    findall(OtherAnimal, shares_habitat(Animal, OtherAnimal), Animals),
    write('Animals that share the same habitat as '), write(Animal), write(':'), nl,
    print_animals(Animals).

% Helper rule to print the list of animals
print_animals([]).
print_animals([Animal|Rest]) :-
    write('- '), write(Animal), nl,
    print_animals(Rest).

% Start the recommendation system
:- recommend_same_habitat.
