#include <iostream>
#include <string>
#include "TeamStats.h"

using namespace std;

int main() {
    //TeamStats arr
  TeamStats teams[] = {
      TeamStats("Mountain House", 0.418, 163, 0.347, 2.92, 0.931),
      TeamStats("Los Banos", 0.387, 186, 0.354, 1.59, 0.931),
      TeamStats("Ceres", 0.409, 172, 0.373, 2.63, 0.88),
      TeamStats("Lathrop", 0.384, 149, 0.332, 4.69, 0.887),
      TeamStats("Johansen", 0.322, 104, 0.281, 6.36, 0.78),
      TeamStats("Grace Davis", 0.398, 104, 0.366, 3.48, 0.83),
      TeamStats("Beyer", 0.394, 104, 0.354, 4.87, 0.84),
      TeamStats("Pacheco", 0.412, 138, 0.342, 5.46, 0.901)
  };

    int size = sizeof(teams) / sizeof(teams[0]);

    // sort teams based on each category using quicksort
    TeamStats::quickSort(teams, 0, size - 1, TeamStats::compareOBP);
    TeamStats::printSortedStats(teams, size, "OBP");

    TeamStats::quickSort(teams, 0, size - 1, TeamStats::compareLOB);
    TeamStats::printSortedStats(teams, size, "LOB");

    TeamStats::quickSort(teams, 0, size - 1, TeamStats::compareSLG);
    TeamStats::printSortedStats(teams, size, "SLG");

    TeamStats::quickSort(teams, 0, size - 1, TeamStats::compareERA);
    TeamStats::printSortedStats(teams, size, "ERA");

    TeamStats::quickSort(teams, 0, size - 1, TeamStats::compareFieldPercentage);
    TeamStats::printSortedStats(teams, size, "Field Percentage");

    //  min and max values for each statistic
    double minOBP = TeamStats::findMin(teams, size, &TeamStats::obp);
    double maxOBP = TeamStats::findMax(teams, size, &TeamStats::obp);

    double minLOB = TeamStats::findMin(teams, size, &TeamStats::lob);
    double maxLOB = TeamStats::findMax(teams, size, &TeamStats::lob);

    double minSLG = TeamStats::findMin(teams, size, &TeamStats::slg);
    double maxSLG = TeamStats::findMax(teams, size, &TeamStats::slg);

    double minERA = TeamStats::findMin(teams, size, &TeamStats::era);
    double maxERA = TeamStats::findMax(teams, size, &TeamStats::era);

    double minFieldPercentage = TeamStats::findMin(teams, size, &TeamStats::fieldPercentage);
    double maxFieldPercentage = TeamStats::findMax(teams, size, &TeamStats::fieldPercentage);

  
 

  
    // display composite scores for each team
    cout << "Composite Scores for Each Team:" << endl;
    for (int i = 0; i < size; ++i) {
        double compositeScore = TeamStats::calculateCompositeScore(teams[i], minOBP, maxOBP, minLOB, maxLOB, minSLG, maxSLG, minERA, maxERA, minFieldPercentage, maxFieldPercentage);
        cout << teams[i].teamName << ":\t" << compositeScore << endl;
    }
    cout << endl;

  // team names along with their indices
  cout << "Team Index\tTeam Name" << endl;
  for (int i = 0; i < size; ++i) {
      cout << i << "\t\t" << teams[i].teamName << endl;
  }
    int teamIndex1, teamIndex2;
    cout << "Enter the index of the first team: ";
    cin >> teamIndex1;
    cout << "Enter the index of the second team: ";
    cin >> teamIndex2;

    //  composite score for the selected teams
    double compositeScoreTeam1 = TeamStats::calculateCompositeScore(teams[teamIndex1], minOBP, maxOBP, minLOB, maxLOB, minSLG, maxSLG, minERA, maxERA, minFieldPercentage, maxFieldPercentage);
    double compositeScoreTeam2 = TeamStats::calculateCompositeScore(teams[teamIndex2], minOBP, maxOBP, minLOB, maxLOB, minSLG, maxSLG, minERA, maxERA, minFieldPercentage, maxFieldPercentage);

    // total composite score
    double totalCompositeScore = compositeScoreTeam1 + compositeScoreTeam2;

    //  percentage chance for each team
    double percentChanceTeam1 = (compositeScoreTeam1 / totalCompositeScore) * 100;
    double percentChanceTeam2 = (compositeScoreTeam2 / totalCompositeScore) * 100;

    // estimated percentage chance for each team
    cout << teams[teamIndex1].teamName << " has a " << percentChanceTeam1 << "% chance to win." << endl;
    cout << teams[teamIndex2].teamName << " has a " << percentChanceTeam2 << "% chance to win." << endl;

    return 0;
}

