#include "Decorations.h"

Object3D deadTreeObj;
Object3D brown_ShroomObj;
Object3D red_ShroomObj;
Object3D bushObj;
Object3D rockObj;
Object3D treeObj;
Object3D chainTreeObj;

vector<Object3D> decorationList;

int maxDecorations = 50;
vector<int> randXList;
vector<int> randZList;
vector<int> randIndexList;
vector<int> randScaleList;

/// Variables for displaying decorations
int scale;
int index;
void DrawDecorations()
{
	ReadOBJfile("data/3D Objects/Decorations/Dead_Tree.obj", &deadTreeObj);
	ReadOBJfile("data/3D Objects/Decorations/Red_Mushroom.obj", &red_ShroomObj);
	ReadOBJfile("data/3D Objects/Decorations/Brown_Mushroom.obj", &brown_ShroomObj);
	ReadOBJfile("data/3D Objects/Decorations/Bush.obj", &bushObj);
	ReadOBJfile("data/3D Objects/Decorations/Rock.obj", &rockObj);
	ReadOBJfile("data/3D Objects/Decorations/Tree.obj", &treeObj);
	ReadOBJfile("data/3D Objects/Decorations/Chained_Tree.obj", &chainTreeObj);

	ReadOBJfile("data/3D Objects/Portal.obj", &portal);

	decorationList.push_back(deadTreeObj);
	decorationList.push_back(red_ShroomObj);
	decorationList.push_back(brown_ShroomObj);
	decorationList.push_back(bushObj);
	decorationList.push_back(rockObj);
	decorationList.push_back(treeObj);
	decorationList.push_back(treeObj);//for dying tree texture
	decorationList.push_back(chainTreeObj);
}

//Future mod: limit no. of trees
void genDecorationsPositions()
{
	int xRand;
	int zRand;
	int index;
	int scale;
	srand(time(NULL));
	for (int i = 0; i < 50; ++i)
	{
		xRand = rand() % 24200 + 6431;
		zRand = rand() % 29000 + 10600;
		index = rand() % 8;
		scale = rand() % 300 + 100;

		if (index == 5)
			index += rand() % 1;

		randXList.push_back(xRand);
		randZList.push_back(zRand);
		randIndexList.push_back(index);
		randScaleList.push_back(scale);
		//printf("xRand = %d, zRand = %d, scale = %d, index = %d\n", xRand, zRand, scale, index);
	}
}

void DisplayDecorations()
{
	for (int i = 0; i < randIndexList.size(); ++i)
	{
		index = randIndexList.at(i);
		scale = randScaleList.at(i);
		glPushMatrix();
		glTranslatef(randXList.at(i), 10000.0, randZList.at(i));
		glScalef(scale, scale, scale);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(decorationTextureHelp(index)));
		draw3DObject(decorationList.at(index));
		glPopMatrix();
	}
}

int decorationTextureHelp(int index)
{
	switch (index)
	{
	case 0:
		return Dead_Tree;
	case 1:
		return Red_Mushroom;
	case 2:
		return Brown_Mushroom;
	case 3:
		return Bush;
	case 4:
		return Rock;
	case 5:
		return Tree;
	case 6:
		return Dying_Tree;
	case 7:
		return Chained_Tree;
	}
}


map<string, Object3D> characterModelMap;
map<string, int> modelTextureMap;

Object3D golum;
Object3D Earthgolum;
Object3D Watergolum;
Object3D Firegolum;
Object3D skeleton;
Object3D wizard;
Object3D zombie;
Object3D samurai; 
Object3D berserker; 
Object3D shield;
Object3D monk;
Object3D swashbuckler;
Object3D archer;
Object3D artillery;
Object3D bard;
Object3D cleric;
Object3D druid;

Object3D LavaBoss;
Object3D EarthBoss;
Object3D WaterBoss;
Object3D AirBoss;

Object3D AnimatedArmor;

Object3D AirGolum;

Object3D FireMage;
Object3D TelekineticMage;
Object3D SummoningMage;
Object3D AirMage;
Object3D WaterMage;

Object3D stun;

int characterScale = 50;
bool displayCharacters;

void initPlayerModels() {

	// read a text file and store the results in a vector of datatype strings
	vector<string> filenames;

	// string containing the path to the textfile 
	string filePath = "data/3D Objects/CharacterModels/filenames.txt";  //     data/3D Objects/CharacterModels/filenames.txt

	ifstream fileOpenerStream;
	fileOpenerStream.open(filePath);

	if (!fileOpenerStream)
	{
		cout << "Could not open file!!!!" << endl;
	}
	// read
	getFileNames(filenames, fileOpenerStream);


	// read the object files and store
	ReadObjectModels(filenames);
	displayCharacters = false;
}


void getFileNames(vector<string>& fileNames, ifstream& inFile)
{
	while (!inFile.eof())
	{
		string line;
		getline(inFile, line);

		if (line.length() != 0)
		{
			fileNames.push_back(line);
		}
	}
}



void ReadObjectModels(vector<string>& fileNames) {

	//   data/3D Objects/CharacterModels/

	//string path = "data/3D Objects/CharacterModels/";


	ReadOBJfile("data/3D Objects/CharacterModels/golum.obj", &golum);
	characterModelMap["Golum"] = golum;

	ReadOBJfile("data/3D Objects/CharacterModels/Earthgolum.obj", &Earthgolum);
	characterModelMap["EarthGolum"] = Earthgolum;
	modelTextureMap["EarthGolum"] = 250; 

	ReadOBJfile("data/3D Objects/CharacterModels/watergolum.obj", &Watergolum);
	characterModelMap["WaterGolum"] = Watergolum;
	modelTextureMap["WaterGolum"] = 251;

	ReadOBJfile("data/3D Objects/CharacterModels/firegolum.obj", &Firegolum);
	characterModelMap["FireGolum"] = Firegolum;
	modelTextureMap["FireGolum"] = 252;

	ReadOBJfile("data/3D Objects/CharacterModels/skeleton.obj", &skeleton);
	characterModelMap["Skeleton"] = skeleton;
	modelTextureMap["Skeleton"] = 253; 

	ReadOBJfile("data/3D Objects/CharacterModels/wizard.obj", &wizard);
	characterModelMap["Wizard"] = wizard;
	modelTextureMap["Wizard"] = 249;
	
	ReadOBJfile("data/3D Objects/CharacterModels/zombie.obj", &zombie);
	characterModelMap["Zombie"] = zombie;
	modelTextureMap["Zombie"] = 248;

	ReadOBJfile("data/3D Objects/CharacterModels/samurai.obj", &samurai);
	characterModelMap["Samurai"] = samurai;
	modelTextureMap["Samurai"] = 254;

	ReadOBJfile("data/3D Objects/CharacterModels/berserker.obj", &berserker);
	characterModelMap["Berserker"] = berserker;
	modelTextureMap["Berserker"] = 255;

	ReadOBJfile("data/3D Objects/CharacterModels/shield.obj", &shield);
	characterModelMap["Shield"] = shield;
	modelTextureMap["Shield"] = 256;

	characterModelMap["Mage"] = wizard;
	modelTextureMap["Mage"] = 249;

	ReadOBJfile("data/3D Objects/CharacterModels/monk.obj", &monk);
	characterModelMap["Monk"] = monk;
	modelTextureMap["Monk"] = 257;

	ReadOBJfile("data/3D Objects/CharacterModels/swashbuckler.obj", &swashbuckler);
	characterModelMap["Swashbuckler"] = swashbuckler;
	modelTextureMap["Swashbuckler"] = 258;

	ReadOBJfile("data/3D Objects/CharacterModels/archer.obj", &archer);
	characterModelMap["Archer"] = archer;
	modelTextureMap["Archer"] = 259;

	ReadOBJfile("data/3D Objects/CharacterModels/artillery.obj", &artillery);
	characterModelMap["Artillery"] = artillery;
	modelTextureMap["Artillery"] = 260;

	ReadOBJfile("data/3D Objects/CharacterModels/bard.obj", &bard);
	characterModelMap["Bard"] = bard;
	modelTextureMap["Bard"] = 261;

	ReadOBJfile("data/3D Objects/CharacterModels/cleric.obj", &cleric);
	characterModelMap["Cleric"] = cleric;
	modelTextureMap["Cleric"] = 262;

	ReadOBJfile("data/3D Objects/CharacterModels/druid.obj", &druid);
	characterModelMap["Druid"] = druid;
	modelTextureMap["Druid"] = 263;

	ReadOBJfile("data/3D Objects/Effects/stun.obj", &stun);
	modelTextureMap["Stun"] = Stun + 1;
	characterModelMap["Stun"] = stun;

	characterModelMap["Tree"] = treeObj;
	modelTextureMap["Tree"] = Tree + 1;

	ReadOBJfile("data/3D Objects/CharacterModels/LavaBoss.obj", &LavaBoss);
	characterModelMap["LavaBoss"] = LavaBoss;
	modelTextureMap["LavaBoss"] = 269; 

	ReadOBJfile("data/3D Objects/CharacterModels/EarthBoss.obj", &EarthBoss);
	characterModelMap["EarthBoss"] = EarthBoss;
	modelTextureMap["EarthBoss"] = 270;

	ReadOBJfile("data/3D Objects/CharacterModels/WaterBoss.obj", &WaterBoss);
	characterModelMap["WaterBoss"] = WaterBoss;
	modelTextureMap["WaterBoss"] = 271;

	ReadOBJfile("data/3D Objects/CharacterModels/AirBoss.obj", &AirBoss);
	characterModelMap["AirBoss"] = AirBoss;
	modelTextureMap["AirBoss"] = 272;

	ReadOBJfile("data/3D Objects/CharacterModels/AnimatedArmor.obj", &AnimatedArmor);
	characterModelMap["AnimatedArmor"] = AnimatedArmor;
	modelTextureMap["AnimatedArmor"] = 273;

	ReadOBJfile("data/3D Objects/CharacterModels/AirGolum.obj", &AirGolum);
	characterModelMap["AirGolum"] = AirGolum;
	modelTextureMap["AirGolum"] = 274;

	ReadOBJfile("data/3D Objects/CharacterModels/FireMage.obj", &FireMage);
	characterModelMap["FireMage"] = FireMage;
	modelTextureMap["FireMage"] = 275;

	ReadOBJfile("data/3D Objects/CharacterModels/TelekineticMage.obj", &TelekineticMage);
	characterModelMap["TelekineticMage"] = TelekineticMage;
	modelTextureMap["TelekineticMage"] = 276;

	ReadOBJfile("data/3D Objects/CharacterModels/SummoningMage.obj", &SummoningMage);
	characterModelMap["SummoningMage"] = SummoningMage;
	modelTextureMap["SummoningMage"] = 277;

	ReadOBJfile("data/3D Objects/CharacterModels/AirMage.obj", &AirMage);
	characterModelMap["AirMage"] = AirMage;
	modelTextureMap["AirMage"] = 278;

	ReadOBJfile("data/3D Objects/CharacterModels/WaterMage.obj", &WaterMage);
	characterModelMap["WaterMage"] = WaterMage;
	modelTextureMap["WaterMage"] = 279;

}

void DisplayPlayerModel(string className, int posX, int posY, int posZ) {

	//cout << modelTextureMap[className] << endl;

	glPushMatrix();
		glTranslatef(posX, posY, posZ);
	//	glScalef(characterScale, characterScale, characterScale);
		glBindTexture(GL_TEXTURE_2D, modelTextureMap[className]); // change this once all the textures are ready
		draw3DObject(characterModelMap[className]);
	glPopMatrix();

}

void playerEffects(Player& pc) {

	if (pc.getStun() > 0)
	{
		glPushMatrix();
			glTranslatef(pc.getPosX(), 1, pc.getPosZ());
			glScalef(50.0, 50.0, 50.0);
			glBindTexture(GL_TEXTURE_2D, modelTextureMap["Stun"]);
			draw3DObject(stun);
		glPopMatrix();
	}
}

void enemyEffects(Enemy& ec) {

	if (ec.getStun() > 0)
	{
		glPushMatrix();
			glTranslatef(ec.getPosX(),1, ec.getPosZ());
			glScalef(50.0, 50.0, 50.0);
			glBindTexture(GL_TEXTURE_2D, modelTextureMap["Stun"]);
			draw3DObject(stun);
		glPopMatrix();
	}


}