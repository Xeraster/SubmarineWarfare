thing :: thing()
{

}

thing :: thing(uint32_t seed)
{
	uint32_t newSeed = seed;
	if (seed == 0) newSeed = rand() % 10000;
	int type = betterRand(newSeed+1) % 8;
	//cout << "type = " << type << endl;

	if (type == 0) inventoryComponent = getRandomJunk(inventoryItemDatabase, newSeed+2);
	else if (type == 1) inventoryComponent = getRandomFood(inventoryItemDatabase, newSeed+2);
	else if (type == 2) inventoryComponent = getRandomUpgradePart(inventoryItemDatabase, newSeed+2);
	else if (type == 3) inventoryComponent = getRandomSexItem(inventoryItemDatabase, newSeed+2);
	else if (type == 4) inventoryComponent = getRandomDrug(inventoryItemDatabase, newSeed+2);
	else if (type == 5) inventoryComponent = getRandomMagicItem(inventoryItemDatabase, newSeed+2);
	else if (type == 6) inventoryComponent = getRandomScienceItem(inventoryItemDatabase, newSeed+2);
	else if (type == 7) inventoryComponent = getRandomSkillItem(inventoryItemDatabase, newSeed+2);
	else if (type == 8) inventoryComponent = getRandomCraftingResource(inventoryItemDatabase, newSeed+2);

	//moved to inventoryItem class
	//findAndSetTexture();


}

//0 = junk. 1 = food. 2 = upgrade part. 3 = sex toy. 4 = drugs. 5 = magic related. 6 = scientific. 7 = skill related (ex: a book). 8 = crafting resource
thing :: thing(int type, uint32_t seed)
{
	uint32_t newSeed = seed;
	if (seed == 0) newSeed = rand() % 10000;

	if (type == 0) inventoryComponent = getRandomJunk(inventoryItemDatabase, newSeed+2);
	else if (type == 1) inventoryComponent = getRandomFood(inventoryItemDatabase, newSeed+2);
	else if (type == 2) inventoryComponent = getRandomUpgradePart(inventoryItemDatabase, newSeed+2);
	else if (type == 3) inventoryComponent = getRandomSexItem(inventoryItemDatabase, newSeed+2);
	else if (type == 4) inventoryComponent = getRandomDrug(inventoryItemDatabase, newSeed+2);
	else if (type == 5) inventoryComponent = getRandomMagicItem(inventoryItemDatabase, newSeed+2);
	else if (type == 6) inventoryComponent = getRandomScienceItem(inventoryItemDatabase, newSeed+2);
	else if (type == 7) inventoryComponent = getRandomSkillItem(inventoryItemDatabase, newSeed+2);
	else if (type == 8) inventoryComponent = getRandomCraftingResource(inventoryItemDatabase, newSeed+2);

	//moved to inventoryItem class
	//findAndSetTexture();
}

thing :: thing(string named)
{

}

thing :: thing(inventoryItem *itemType)
{

}

thing& thing :: operator=(thing& other)
{
	inventoryComponent = other.inventoryComponent;
	xPos = other.getX();
	yPos = other.getY();
	tex = other.tex;
//	SDL_RenderCopy(tex, other.getTexture());

	return *this;
}

void thing :: findAndSetTexture()
{
	//vector<textureEntry*> *textureDatabase
	int i = 0;
	bool foundTexture = false;
	//cout << "creating a new " << getName() << endl;
	while (!foundTexture && i < textureDatabase->size())
	{
		//cout << "compare " << textureDatabase->at(i)->getName() << " to " << getName() << endl;
		if (textureDatabase->at(i)->getName() == inventoryComponent->getTextureName())
		{	
			//cout << "match found" << endl;
			foundTexture = true;
			tex = textureDatabase->at(i)->tex;
		}
		i++;
	}

	if (!foundTexture) tex = errorTexture;
}

ostream& operator<<(ostream& os, thing item)
{
	os << "Thing name: " << item.getName() << endl;
	os << "Thing description: " << item.getDescription() << endl;
	os << "Thing tooltip: " << item.getTooltip() << endl;
	os << "x pos: " << item.getX() << endl;
	os << "y pos: " << item.getY() << endl;
	return os;
}