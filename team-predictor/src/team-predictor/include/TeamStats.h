#ifndef TEAMSTATS_H
#define TEAMSTATS_H

#include <string>

class TeamStats {
public:
    std::string teamName;
    double obp;
    double lob;
    double slg;
    double era;
    double fieldPercentage;

    TeamStats(std::string name, double obp_val, double lob_val, double slg_val,
              double era_val, double fieldPercentage_val);

    // function prototypes
    static bool compareOBP(const TeamStats &a, const TeamStats &b);
    static bool compareLOB(const TeamStats &a, const TeamStats &b);
    static bool compareSLG(const TeamStats &a, const TeamStats &b);
    static bool compareERA(const TeamStats &a, const TeamStats &b);
    static bool compareFieldPercentage(const TeamStats &a, const TeamStats &b);
    static double findMin(const TeamStats teams[], int size, double TeamStats::*member);
    static double findMax(const TeamStats teams[], int size, double TeamStats::*member);
    static double minMaxNormalization(double value, double minValue, double maxValue);
    static double calculateCompositeScore(const TeamStats &team, double minOBP,
                                           double maxOBP, double minLOB, double maxLOB,
                                           double minSLG, double maxSLG, double minERA,
                                           double maxERA, double minFieldPercentage,
                                           double maxFieldPercentage);
    // util function prototypes
    static void swap(TeamStats &a, TeamStats &b);
    static int partition(TeamStats arr[], int low, int high, bool (*compare)(const TeamStats&, const TeamStats&));
    static void quickSort(TeamStats arr[], int low, int high, bool (*compare)(const TeamStats&, const TeamStats&));
    static void printSortedStats(const TeamStats *sortedStats, int size, const std::string& category);
};

#endif // TEAMSTATS_H

