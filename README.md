# Village Cheif

## Pitch
Village Cheif Manager
A prompt periodically appears requiring a choice
The choice affect the development of the village
Score is quality of life and number of villagers

## Graphics
Background has four states, spring, summer, autumn, winter
Number of houses scales with number of villagers
Choice menu is themed with the season

## Gameplay

One prompt is:
() one season
() one month
() one week

Village starts with a number of villagers
() Gender? a number of male and females

The choices are rolled from a pool of choices
Choices have tags that modify the chance for them to be rolled out
Events have a chance of being rolled

## Villager Simulation

(V) Track pregnant women
(V) Track age of villagers (with a bin system)
(V) Track productivity of villagers, reduced by sickness, hunger, exposure
(V) Track fields for food
(V)

Meters:
- Water quality
- Food Stored
- Materials
- Labour
- Fields
- Tilled Fields


## Events
name: "Expand Fields", tag:spring, tag:food, field: 1, materials: -2, labour: 3, text: "Build {field} additional field, costs {materials} Materials and {labour}"
name: "Winter Storm", tag:winter, tag:event, tag:disaster, tag:rare, temperature:-3, weather:-2, text: "Strong storm hits the village"
name: "Hunt", tag:job, food:+1, labour: 1, text: "Venture in the woods to hunt game"
name: "Chop Woods", tag:job, materials: +1, text: "Chop trees and get construction materials"

## SIMPLER

Villager Meters
- Population
- Well Being
- Labour

Environment Meters
- Season
- Weather

Resource Meters
- Fields
- Food
- Wood

Choices (none)
-

Events (none)
-

