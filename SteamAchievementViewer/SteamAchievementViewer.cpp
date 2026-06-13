#include <iostream>
#include "steam_api.h"
#include <windows.h>
#include <fstream>
#include <vector>


int main()
{
    // Asking user for their game's appID
    int appID;
    std::cout << "Please enter your game's APPID: ";
    std::cin >> appID;

    // Writing appID to "steam_appid.txt"
    const std::string appIDTXT = "steam_appid.txt";
    std::ofstream outputAppID(appIDTXT);
    outputAppID << appID;
    outputAppID.close();

    // Initialize the Steamworks API
    if (!SteamAPI_Init())
    {
        std::cout << "Steamworks API failed to initialize!\n";
        std::cout << "Make sure the Steam client is running and logged in, or make sure you have input the correct Steam APPID.\n";
        return 1;
    }

    std::cout << "Steamworks API initialized successfully!\n\n";

    // Fetch the CSteamID object for the local user
    CSteamID localPlayerID = SteamUser()->GetSteamID();

    // Convert the object to a standard 64-bit integer (SteamID64)
    uint64 steamID64 = localPlayerID.ConvertToUint64();

    // Requesting user's stats
    SteamUserStats()->RequestUserStats(steamID64);
    Sleep(1000);

    // Fetching number of achievements for the selected game
    const int numOfAchievements = SteamUserStats()->GetNumAchievements();
    std::vector<std::string> unlockedAchievements;
    int size = 0;

    // Creating the "Achievements.json" file
    const std::string outputFileName = "Achievements.json";
    std::ofstream outputFile(outputFileName);
    outputFile << '[' << std::endl;

    std::cout << "Processing " << numOfAchievements << " achievements..." << std::endl;

    // Reading each achievement; If user has unlocked achievement, add it to unlockedAchievements array
    for (int i = 0; i < numOfAchievements; i++) {
        const char* achiName = SteamUserStats()->GetAchievementName(i);
        bool hasUnlocked = false;
        if (SteamUserStats()->GetAchievement(achiName, &hasUnlocked) && hasUnlocked) {
            unlockedAchievements.push_back(achiName);
            size++;
        }
    }

    // Exporting unlocked achievements
    std::cout << "Exporting " << size << " unlocked achievements..." << std::endl;

    for (int i = 0; i < size; i++) {
        const char* achievementName = unlockedAchievements[i].c_str();
        const char* achievementPublicName = SteamUserStats()->GetAchievementDisplayAttribute(achievementName, "name");
        const char* achievementPublicDesc = SteamUserStats()->GetAchievementDisplayAttribute(achievementName, "desc");
        outputFile << "\t{" << std::endl;
        outputFile << "\t\t\"Name\": " << '\"' << achievementPublicName << "\"," << std::endl;
        outputFile << "\t\t\"Description\": " << '\"' << achievementPublicDesc << "\"" << std::endl;
        if (i == size - 1) {
            outputFile << "\t}" << std::endl;
        }
        else {
            outputFile << "\t}," << std::endl;
        }
    }

    // Finishing and closing "Achievements.json" file
    outputFile << ']' << std::endl;
    outputFile.close();

    std::cout << "Your unlocked achievements have been exported to \"Achievements.json\"." << std::endl;

    SteamAPI_Shutdown();
    std::system("pause");
    return 0;
}