#pragma once
class testAll {
public:
	//Repository tests
	static void testGetArray();
	static void testInitializeRepo();
	static void testGetSize();
	static void testAddRepo();
	static void testCheckTutorialExistence();
	static void testDeleteTutorial();
	static void testUpdateLikes();
	static void testUpdateDuration();
	static void testAllRepo();

	//Service tests
	static void testGetRepository();
	static void testGetUserRepository();
	static void testInitializeService();
	static void testAddService();
	static void testDeleteService();
	static void testGetSizeService();
	static void testUpdateLikesService();
	static void testUpdateDurationService();
	static void testAllService();
	

	//Tutorial tests
	static void testSetTitle();
	static void testSetPresenter();
	static void testSetLink();
	static void testSetLikes();
	static void testSetDuration();
	static void testGetTitle();
	static void testGetPresenter();
	static void testGetLink();
	static void testGetLikes();
	static void testGetDuration();
	static void testAllTutorial();

	//Validation tests
	static void testValidateTitle();
	static void testValidatePresenter();
	static void testValidateDuration();
	static void testValidateLikes();
	static void testValidateLink();
	static void testAllValidate();

	static void testAbsolutelyEverything();
};