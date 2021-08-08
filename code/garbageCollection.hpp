bool deletePlayerTorpedo()
{
	bool foundSomethingToDelete = false;
	if (playerCampaignInfo != nullptr && showPurchaseScreen)
	{
		std::list<torpedo>::iterator it;
		// Make iterate point to begining and incerement it one by one till it reaches the end of list.
		for (it = playerCampaignInfo->m_playerTorpedos->begin(); it != playerCampaignInfo->m_playerTorpedos->end(); it++)
		{
			if (it->markedForDeletion())
			{
				cout << "marked for deletion" << endl;
				playerCampaignInfo->m_playerTorpedos->erase(it);
				foundSomethingToDelete = true;
				break;
			}
			//i++;
	    	// Access the object through iterator
	    	//int id = it->id;
	    	//std::string name = it->name;
	    
	    	//Print the contents
	    	//std::cout << id << " :: " << name << std::endl;
		}
		/*for (int i = 0; i < playerCampaignInfo->m_playerTorpedos->size(); i++)
		{
			if (playerCampaignInfo->m_playerTorpedos->at(i).markedForDeletion())
			{
				playerCampaignInfo->m_playerTorpedos->erase(playerCampaignInfo->m_playerTorpedos->begin() + i);
			}
		}*/
	}

	return foundSomethingToDelete;
}

void deletePlayerTorpedos()
{
	if (deleteTorpedosNotify)
	{
		int deletedThings = 0;
		while(deletePlayerTorpedo())
		{
			deletedThings++;
		}

		cout << "deleted " << deletedThings << " player torpedos from list" << endl;
		deleteTorpedosNotify = false;
	}
}