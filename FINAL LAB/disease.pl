% Define symptoms
symptom(fever).
symptom(cough).
symptom(sore_throat).
symptom(runny_nose).

% Define diseases and their symptoms
disease(flu, [fever, cough, sore_throat, runny_nose]).
disease(cold, [cough, sore_throat, runny_nose]).

% Rules to determine if a person is sick
is_sick(Person, Disease) :-
    symptom(S),
    \+ has_symptom(Person, S),
    disease(Disease, Symptoms),
    member(S, Symptoms).

% Ask for symptoms and check if the person is sick
diagnose(Person, Disease) :-
    write('Welcome! Let\'s check if you have the flu or a cold.\n'),
    ask_symptom(Person, fever),
    ask_symptom(Person, cough),
    ask_symptom(Person, sore_throat),
    ask_symptom(Person, runny_nose),
    
    (is_sick(Person, Disease) -> 
        write('\nBased on your symptoms, you might have '), 
        write(Disease), 
        write('.\n');
        write('\nBased on your symptoms, you seem to be healthy. However, if you feel unwell, it\'s best to consult a doctor.\n')
    ),
    retractall(has_symptom(Person, _)).

ask_symptom(Person, Symptom) :-
    write('Do you have '), 
    write(Symptom), 
    write('? (yes/no): '),
    read(Answer),
    (Answer = yes -> assert(has_symptom(Person, Symptom)); true).
