#include "TeamStats.h"
#include <limits>

#include <iostream>

using namespace std;

//contrsuctor
TeamStats::TeamStats(std::string name, double obp_val, double lob_val, double slg_val, double era_val, double fieldPercentage_val)
    : teamName(name), obp(obp_val), lob(lob_val), slg(slg_val), era(era_val), fieldPercentage(fieldPercentage_val) {}

// func definitions
bool TeamStats::compareOBP(const TeamStats &a, const TeamStats &b) {
    return a.obp > b.obp;
}

bool TeamStats::compareLOB(const TeamStats &a, const TeamStats &b) {
    return a.lob < b.lob;
}

bool TeamStats::compareSLG(const TeamStats &a, const TeamStats &b) {
    return a.slg > b.slg;
}

bool TeamStats::compareERA(const TeamStats &a, const TeamStats &b) {
    return a.era < b.era;
}

bool TeamStats::compareFieldPercentage(const TeamStats &a, const TeamStats &b) {
    return a.fieldPercentage > b.fieldPercentage;
}

double TeamStats::findMin(const TeamStats teams[], int size, double TeamStats::*member) {
    double minVal = std::numeric_limits<double>::max();
    for (int i = 0; i < size; ++i) {
        if (teams[i].*member < minVal) {
            minVal = teams[i].*member;
        }
    }
    return minVal;
}

double TeamStats::findMax(const TeamStats teams[], int size, double TeamStats::*member) {
    double maxVal = std::numeric_limits<double>::lowest();
    for (int i = 0; i < size; ++i) {
        if (teams[i].*member > maxVal) {
            maxVal = teams[i].*member;
        }
    }
    return maxVal;
}

double TeamStats::minMaxNormalization(double value, double minValue, double maxValue) {
    return (value - minValue) / (maxValue - minValue);
}

double TeamStats::calculateCompositeScore(const TeamStats &team, double minOBP, double maxOBP, double minLOB, double maxLOB,
                                           double minSLG, double maxSLG, double minERA, double maxERA, double minFieldPercentage, double maxFieldPercentage) {
    double normalizedOBP = minMaxNormalization(team.obp, minOBP, maxOBP);
    double normalizedLOB = minMaxNormalization(team.lob, minLOB, maxLOB);
    double normalizedSLG = minMaxNormalization(team.slg, minSLG, maxSLG);
    double normalizedERA = minMaxNormalization(team.era, minERA, maxERA);
    double normalizedFieldPercentage = minMaxNormalization(team.fieldPercentage, minFieldPercentage, maxFieldPercentage);

    double compositeScore = (normalizedOBP * 0.25) + (normalizedLOB * 0.1) + (normalizedSLG * 0.25) + (normalizedERA * 0.25) + (normalizedFieldPercentage * 0.15);
    return compositeScore;
}

// util functions
void TeamStats::swap(TeamStats &a, TeamStats &b) {
    TeamStats temp = a;
    a = b;
    b = temp;
}

int TeamStats::partition(TeamStats arr[], int low, int high, bool (*compare)(const TeamStats&, const TeamStats&)) {
    TeamStats pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (compare(arr[j], pivot)) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void TeamStats::quickSort(TeamStats arr[], int low, int high, bool (*compare)(const TeamStats&, const TeamStats&)) {
    if (low < high) {
        int pi = partition(arr, low, high, compare);
        quickSort(arr, low, pi - 1, compare);
        quickSort(arr, pi + 1, high, compare);
    }
}


void TeamStats:: printSortedStats(const TeamStats *sortedStats, int size, const string& category) {
    cout << "Sorted by " << category  << endl;
    for (int i = 0; i < size; ++i) {
        if (category == "OBP")
            cout << sortedStats[i].teamName << "\t" << sortedStats[i].obp << endl;
        else if (category == "LOB")
            cout << sortedStats[i].teamName << "\t" << sortedStats[i].lob << endl;
        else if (category == "SLG")
            cout << sortedStats[i].teamName << "\t" << sortedStats[i].slg << endl;
        else if (category == "ERA")
            cout << sortedStats[i].teamName << "\t" << sortedStats[i].era << endl;
        else if (category == "Field Percentage")
            cout << sortedStats[i].teamName << "\t" << sortedStats[i].fieldPercentage << endl;
    }
    cout << endl;
}
