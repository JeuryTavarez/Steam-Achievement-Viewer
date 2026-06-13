#include <iostream>
#include "steam_api.h"
#include <windows.h>
#include <fstream>
#include <vector>
#include "LinkedList.h"

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
	LinkedList unlockedAchievements;
   
    // Creating the "Achievements.json" file
    const std::string outputFileName = "Achievements.json";
    std::ofstream outputFile(outputFileName);
    outputFile << '[' << std::endl;
    
    std::cout << "Processing " << numOfAchievements << " achievements..." << std::endl;

    // Reading each achievement; If user has unlocked achievement, add it to unlockedAchievements list
    for (int i = 0; i < numOfAchievements; i++) {
        const char* achiName = SteamUserStats()->GetAchievementName(i);
        bool hasUnlocked = false;
        if (SteamUserStats()->GetAchievement(achiName, &hasUnlocked) && hasUnlocked) {
            unlockedAchievements.insert(unlockedAchievements.getLength() + 1, achiName);
        }
    }

    // Exporting unlocked achievements
	const int size = unlockedAchievements.getLength();
    std::cout << "Exporting " << size << " unlocked achievements..." << std::endl;

    Node* current = unlockedAchievements.getNodeAt(1);
    int i = 1;

    // Iterating the linked list, starting from headptr
    while (current != nullptr) {
        std::string temp = current->getItem();  
        const char* ptr = temp.c_str();          

        const char* achievementPublicName = SteamUserStats()->GetAchievementDisplayAttribute(ptr, "name");
        const char* achievementPublicDesc = SteamUserStats()->GetAchievementDisplayAttribute(ptr, "desc");

        outputFile << "\t{" << std::endl;
        outputFile << "\t\t\"Name\": " << '\"' << achievementPublicName << "\"," << std::endl;
        outputFile << "\t\t\"Description\": " << '\"' << achievementPublicDesc << "\"" << std::endl;

        if (i == size) {
            outputFile << "\t}" << std::endl;
        }
        else {
            outputFile << "\t}," << std::endl;
        }
        current = current->getNext();
        i++;
    }

    // Finishing and closing "Achievements.json" file
    outputFile << ']' << std::endl;
    outputFile.close();
    unlockedAchievements.clear();

    std::cout << "Your unlocked achievements have been exported to \"Achievements.json\"." << std::endl;

    SteamAPI_Shutdown();
    std::system("pause");
    return 0;
}