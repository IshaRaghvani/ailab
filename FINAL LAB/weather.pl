% Define weather conditions
weather(sunny).
weather(rainy).
weather(cloudy).
weather(windy).

% Define activities for different weather conditions
activity(sunny, 'Go for a picnic').
activity(sunny, 'Play outdoor sports').
activity(rainy, 'Watch movies at home').
activity(rainy, 'Read a book indoors').
activity(cloudy, 'Go for a walk').
activity(cloudy, 'Visit a museum').
activity(windy, 'Fly a kite').
activity(windy, 'Go windsurfing').

% Define rules to recommend activities based on weather conditions
recommend_activity :-
    write('Enter the current weather condition: '),
    read(Weather),
    findall(Activity, (weather(Weather), activity(Weather, Activity)), Activities),
    write('Recommended activities for today: '), nl,
    print_activities(Activities).

print_activities([]).
print_activities([Activity | Rest]) :-
    write('- '), write(Activity), nl,
    print_activities(Rest).
