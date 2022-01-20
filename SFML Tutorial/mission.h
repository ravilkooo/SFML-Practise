#pragma once
int getCurrentMission(int x) {
	int mission;
	if (x > 0 && x < 800) { mission = 0; }
	else if (x <  1600) { mission = 1; }
	else if (x < 2400) { mission = 2; }
	else { mission = 3; }

	return mission;
}

std::string getTextMission(int currentMission) {
	std::string missionText = "";

	switch (currentMission) {
		case 0: missionText = "\nWelcome, stupy!\nThat's a first mission\nJust for... I dunow...\nFor nothing"; break;
		case 1: missionText = "\nThe second one\nWell... Ahh...\nGo forward and... Maybe...\nPut your finger in USB port"; break;
		case 2: missionText = "\nOMG! You did it!\nWhat a hero!.. Kidding...\nGo"; break;
		case 3: missionText = "\nIt's a last mission\nDo what you want\nI don't care"; break;
	}

	return missionText;
}
