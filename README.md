https://docs.google.com/presentation/d/1bTDHLx3WMeOVR6sS6mL75LZ9RQQP7lFy-suOy3UgReA/edit?usp=sharing

Abstract

This project is a baseball analytics program designed to predict the outcome of high school baseball games using team statistics and player data. The system analyzes key offensive, defensive, and pitching metrics to generate a composite score representing the overall strength of each team. These scores are then compared to estimate the probability that one team will defeat another.
The program also includes a player database that allows users to search for individual player statistics, retrieve team rosters, and identify the top performers on each team based on composite scores. The system demonstrates the use of several fundamental computer science concepts including sorting algorithms, hashing, normalization techniques, and object-oriented programming. 

Introduction
   
Sports analytics has become an important tool for evaluating player and team performance. At the professional level, teams rely heavily on statistical analysis to guide roster construction, player development, and game strategy. While this level of analysis is common in professional baseball, high school teams often lack access to similar analytical tools. This project was developed to apply data structure and algorithm concepts to high school baseball analytics. As a high school baseball coach, I often miss practices and games during the spring season due to school commitments. Creating this tool allows coaches and players to quickly analyze team strengths and weaknesses while gaining a competitive advantage through data-driven insights.
The program predicts game outcomes by analyzing several statistics that are commonly associated with team success. Additionally, it provides a searchable database of players that allows coaches to analyze opponents and identify key matchups.

 System Overview
 
The program consists of two primary components:
1. Team Analytics Engine
This component analyzes team statistics to calculate a composite score that represents overall team performance.
2. Player Database System
This component stores and retrieves individual player statistics using a hash table data structure.
Together, these components allow users to:
• Predict the outcome of a game between two teams
 • Analyze team statistics
 • Search for individual player statistics
 • Retrieve an entire team roster
 • Identify the top three players from a team based on performance metrics

 Team Statistics Model
 
The predictive model uses five key statistics commonly associated with baseball success.
On Base Percentage (OBP)
OBP measures how frequently a team reaches base.
OBP = (Hits + Walks + Hit By Pitch) / Plate Appearances
Teams that consistently reach base create more scoring opportunities.
Slugging Percentage (SLG)
SLG measures a team's power hitting by accounting for extra-base hits.
SLG = Total Bases / At Bats
Teams with higher slugging percentages tend to score more runs.
Earned Run Average (ERA)
ERA measures the effectiveness of a team's pitching staff.
ERA = (Earned Runs / Innings Pitched) × 9
Lower ERA values indicate stronger pitching performance.
Fielding Percentage (FP)
Fielding percentage measures defensive reliability.
FP = (Putouts + Assists) / Total Chances
Higher fielding percentages indicate fewer defensive errors.
Left On Base (LOB)
LOB measures how many baserunners a team fails to convert into runs. Teams that strand many runners often struggle to capitalize on scoring opportunities.

 Data Normalization
 
Since each statistic is measured on a different scale, normalization is required to compare them effectively.
The program uses Min-Max normalization, which scales each statistic to a value between 0 and 1.
Normalized Value =
 (Value − Min) / (Max − Min)
For statistics where lower values represent better performance (such as ERA), the formula is reversed.
Normalized Value =
 (Max − Value) / (Max − Min)
This ensures that all statistics contribute proportionally to the final composite score.

Composite Score Calculation

After normalization, each statistic is multiplied by a weight that reflects its importance in predicting team success.
Statistic
Weight
OBP 0.25
SLG 0.25
ERA 0.25
Fielding Percentage 0.15
LOB 0.10

The composite score is calculated as:
Composite Score =
(OBP × 0.25) +
 (SLG × 0.25) +
 (ERA × 0.25) +
 (Fielding % × 0.15) +
 (LOB × 0.10)
This produces a single numerical value representing the overall strength of a team.

 Game Outcome Prediction
 
The probability that a team will win is calculated using the composite scores of both teams.
Probability Team A =
ScoreA / (ScoreA + ScoreB)
Probability Team B =
ScoreB / (ScoreA + ScoreB)
This produces an estimated win probability for each team.
Example output:
Enter Team 1: Mountain House
Enter Team 2: Ceres

Mountain House has a 56.3% chance to win
Ceres has a 43.7% chance to win

Player Database System
The project includes a player database implemented using a hash table.
The database stores player objects containing:
• Player name
 • Jersey number
 • Team name
 • Batting statistics
 • Fielding statistics
The key used in the hash table combines:
Player Jersey Number + Team Name
This ensures that each key is unique.
Collision Handling - Collisions are handled using separate chaining, where each bucket in the hash table contains a linked list of player objects.
This allows multiple players to exist within the same bucket while maintaining efficient lookup times.

Player Search Features
The player database allows several types of queries.
Individual Player Lookup -
Users can search for a player using:
• Jersey number
 • Team name
The program retrieves and displays the player's statistics.
Team Roster Lookup -
Users can enter a team name to retrieve all players associated with that team.
Top Performers -
The program can also identify the top three players on a team based on their composite scores.
These scores are calculated similarly to the team model using normalized offensive and defensive statistics.
This feature allows coaches to quickly identify:
• Key hitters
 • Defensive standouts
 • Players who may influence game outcomes

 Algorithms Used
 
Quicksort -The program uses quicksort to sort team statistics. Quicksort was chosen because:
• It has an average time complexity of O(n log n)
 • It operates in-place
 • It is efficient for array-based datasets
The partition function uses a two-pointer approach with the last element serving as the pivot.

Searching -Team statistics are retrieved using linear search because the dataset is small (eight teams).
Time complexity: O(n)

Hashing- The player database uses a hash table. Average lookup complexity: O(1)
Worst case complexity (with many collisions): O(n)

Data Structures Used
The system demonstrates several core data structures.
Arrays -Used to store team statistics.
Linked Lists -Used to resolve hash table collisions.
Hash Tables -Used to store and retrieve player data efficiently.
Classes and Objects -Used to represent teams and players.

 Example Program Workflow
Load team statistics into an array.


Normalize statistics using Min-Max normalization.


Calculate composite scores for each team.


Prompt the user to enter two teams.


Compare composite scores to generate win probabilities.


Allow the user to search player data or team rosters.



 Conclusion
 
This project demonstrates how computer science concepts can be applied to real-world sports analytics problems. By combining normalization techniques, weighted statistical analysis, and efficient data structures, the system provides a practical method for predicting baseball game outcomes.
Additionally, the player database and top performer analysis tools allow coaches to analyze opponents and identify key matchups. While the model is relatively simple, it provides a foundation that could be expanded with more advanced metrics or machine learning techniques in the future.

Possible Future Improvements
• Incorporate pitching matchup analysis
 • Add strikeout and walk metrics
 • Use machine learning models for prediction
 • Expand the dataset to multiple leagues
 • Build a graphical user interface
